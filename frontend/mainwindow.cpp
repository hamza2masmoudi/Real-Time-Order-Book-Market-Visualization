#include "mainwindow.h"
#include "matching_engine.h"

#include <QtCharts/QChart>
#include <QtCharts/QValueAxis>
#include <QtCharts/QCandlestickSeries>
#include <QtCharts/QCandlestickSet>
#include <QtCharts/QCategoryAxis>
#include <QDateTime>
#include <QDebug>
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QFormLayout>
#include <QGroupBox>
#include <QSplitter>
#include <QRandomGenerator>
#include <QStatusBar>
#include <QToolTip>
#include <QCursor>
#include <QProgressBar>
#include <QTableWidget>
#include <algorithm>

// Constructor
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      engine(new MatchingEngine),
      update_timer(new QTimer(this))
{
    engine->start();

    // Setup the main UI layout (splitters)
    setupUI();

    // Create chart objects, but do NOT attach them to the old splitter
    // We'll just set up chart objects in memory, then attach to rightVerticalSplitter
    setupChart();
    setupAdvancedChart();

    // Periodic GUI updates
    connect(update_timer, &QTimer::timeout, this, &MainWindow::update_gui);
    update_timer->start(1000);

    // Timer for simulated limit orders
    QTimer* simulationTimer = new QTimer(this);
    connect(simulationTimer, &QTimer::timeout, this, &MainWindow::simulateOrder);
    simulationTimer->start(500);

    // Timer for live market data simulation (market orders)
    QTimer* liveDataTimer = new QTimer(this);
    connect(liveDataTimer, &QTimer::timeout, this, &MainWindow::simulateLiveMarketData);
    liveDataTimer->start(300);

    statusBar()->showMessage("Ready");
}

MainWindow::~MainWindow()
{
    engine->stop();
    delete engine;
}

// 1) Create a horizontal splitter => left panel (metrics, form, table), right panel (vertical splitter for 2 charts)
void MainWindow::setupUI() 
{
    // Top-level horizontal splitter for left vs. right
    QSplitter* mainHorizontalSplitter = new QSplitter(Qt::Horizontal, this);

    // LEFT PANEL (vertical)
    QWidget* leftPanelWidget = new QWidget;
    QVBoxLayout* leftPanelLayout = new QVBoxLayout(leftPanelWidget);

    // (A) Metrics Dashboard
    QGroupBox* metricsBox = new QGroupBox("Metrics Dashboard");
    QVBoxLayout* metricsLayout = new QVBoxLayout(metricsBox);

    latencyBar = new QProgressBar;
    latencyBar->setRange(0, 2000);

    throughputBar = new QProgressBar;
    throughputBar->setRange(0, 1000);

    latencyLabel = new QLabel("Latency: 0 ms");
    throughputLabel = new QLabel("Throughput: 0 ops");

    metricsLayout->addWidget(latencyLabel);
    metricsLayout->addWidget(latencyBar);
    metricsLayout->addWidget(throughputLabel);
    metricsLayout->addWidget(throughputBar);
    metricsBox->setLayout(metricsLayout);

    // (B) Order Submission Form
    orderFormGroup = new QGroupBox("Order Submission", this);
    QFormLayout* formLayout = new QFormLayout;

    priceEdit = new QLineEdit;
    quantityEdit = new QLineEdit;
    sideCombo = new QComboBox;
    sideCombo->addItems({"Buy", "Sell"});
    sideCombo->setMinimumContentsLength(10);
    sideCombo->setSizeAdjustPolicy(QComboBox::AdjustToContents);

    orderTypeCombo = new QComboBox;
    orderTypeCombo->addItems({"Limit", "Market", "Stop-Loss", "Iceberg"});
    orderTypeCombo->setMinimumContentsLength(10);
    orderTypeCombo->setSizeAdjustPolicy(QComboBox::AdjustToContents);

    submitButton = new QPushButton("Submit Order");
    connect(submitButton, &QPushButton::clicked, this, &MainWindow::submitOrder);

    formLayout->addRow("Price:", priceEdit);
    formLayout->addRow("Quantity:", quantityEdit);
    formLayout->addRow("Side:", sideCombo);
    formLayout->addRow("Order Type:", orderTypeCombo);
    formLayout->addRow("", submitButton);
    orderFormGroup->setLayout(formLayout);

    // (C) Trade History Table
    tradeTable = new QTableWidget;
    tradeTable->setColumnCount(5);
    QStringList headers;
    headers << "Timestamp" << "Price" << "Quantity" << "Taker ID" << "Maker ID";
    tradeTable->setHorizontalHeaderLabels(headers);
    tradeTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    tradeTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    tradeTable->setSelectionMode(QAbstractItemView::SingleSelection);
    tradeTable->setMinimumHeight(200);

    // Put them all into the left panel layout
    leftPanelLayout->addWidget(metricsBox);
    leftPanelLayout->addWidget(orderFormGroup);
    leftPanelLayout->addWidget(tradeTable);
    leftPanelLayout->addStretch(1);
    leftPanelWidget->setLayout(leftPanelLayout);

    // RIGHT PANEL (vertical splitter for 2 charts)
    QSplitter* rightVert = new QSplitter(Qt::Vertical, this);

    // Add left and right to mainHorizontalSplitter
    mainHorizontalSplitter->addWidget(leftPanelWidget);
    mainHorizontalSplitter->addWidget(rightVert);

    // Let the right side expand more
    mainHorizontalSplitter->setStretchFactor(0, 0);
    mainHorizontalSplitter->setStretchFactor(1, 1);

    // Make the horizontal splitter the central widget
    setCentralWidget(mainHorizontalSplitter);

    // Apply a style
    setStyleSheet(
        "QGroupBox { font-weight: bold; margin-top: 1em; } "
        "QLineEdit, QComboBox, QPushButton { font-size: 14px; padding: 4px; }"
    );

    // Store pointer to rightVert so we can attach charts after creation
    this->rightVerticalSplitter = rightVert;
}

// 2) Depth Chart
void MainWindow::setupChart()
{
    QChart* chart = new QChart;
    bids_series = new QLineSeries;
    asks_series = new QLineSeries;

    bids_series->setName("Bids");
    asks_series->setName("Asks");
    chart->addSeries(bids_series);
    chart->addSeries(asks_series);

    // Axes
    QValueAxis* axisX = new QValueAxis;
    axisX->setTitleText("Price");
    axisX->setRange(0, 110);

    QValueAxis* axisY = new QValueAxis;
    axisY->setTitleText("Quantity");
    axisY->setRange(0, 60);

    chart->addAxis(axisX, Qt::AlignBottom);
    chart->addAxis(axisY, Qt::AlignLeft);
    bids_series->attachAxis(axisX);
    bids_series->attachAxis(axisY);
    asks_series->attachAxis(axisX);
    asks_series->attachAxis(axisY);

    chart->legend()->setVisible(true);
    chart->setTitle("Order Book Depth");

    depth_chart_view = new QChartView(chart);
    depth_chart_view->setRenderHint(QPainter::Antialiasing);
    depth_chart_view->setRubberBand(QChartView::RectangleRubberBand);
    depth_chart_view->setInteractive(true);

    // Add to the vertical splitter if available
    if (rightVerticalSplitter) {
        rightVerticalSplitter->addWidget(depth_chart_view);
    }
}

// 3) Advanced Candlestick Chart
void MainWindow::setupAdvancedChart()
{
    QChart* advChart = new QChart;
    
    // Candlestick
    candlestick_series = new QCandlestickSeries;
    candlestick_series->setName("Candlestick");

    const int numCandles = 10;
    QVector<QCandlestickSet*> candleSets;
    for (int i = 0; i < numCandles; i++) {
        double open = 50.0 + QRandomGenerator::global()->generateDouble() * 50.0;
        double close = 50.0 + QRandomGenerator::global()->generateDouble() * 50.0;
        double high = std::max(open, close) + QRandomGenerator::global()->generateDouble() * 5.0;
        double low = std::min(open, close) - QRandomGenerator::global()->generateDouble() * 5.0;
        low = std::min(low, std::min(open, close));
        high = std::max(high, std::max(open, close));
        QCandlestickSet* set = new QCandlestickSet(open, high, low, close);
        candleSets.append(set);
    }
    for (auto set : candleSets) {
        candlestick_series->append(set);
    }
    advChart->addSeries(candlestick_series);

    // Axes
    QValueAxis* axisYAdv = new QValueAxis;
    axisYAdv->setTitleText("Price");
    axisYAdv->setRange(40, 110);
    advChart->addAxis(axisYAdv, Qt::AlignLeft);
    candlestick_series->attachAxis(axisYAdv);

    QValueAxis* axisXAdv = new QValueAxis;
    axisXAdv->setTitleText("Time (Candle Index)");
    axisXAdv->setRange(0, numCandles - 1);
    advChart->addAxis(axisXAdv, Qt::AlignBottom);
    candlestick_series->attachAxis(axisXAdv);

    // Moving Average
    moving_average_series = new QLineSeries;
    moving_average_series->setName("Moving Average");
    const int windowSize = 3;
    QVector<double> closes;
    closes.reserve(numCandles);
    for (int i = 0; i < numCandles; i++) {
        closes.append(candleSets[i]->close());
    }

    for (int i = windowSize - 1; i < numCandles; i++) {
        double sum = 0;
        for (int j = i - windowSize + 1; j <= i; j++) {
            sum += closes[j];
        }
        double avg = sum / windowSize;
        moving_average_series->append(i - (windowSize / 2.0), avg);
    }
    advChart->addSeries(moving_average_series);
    moving_average_series->attachAxis(axisXAdv);
    moving_average_series->attachAxis(axisYAdv);

    advChart->legend()->setVisible(true);
    advChart->setTitle("Advanced Charting: Candlestick & Moving Average");

    advanced_chart_view = new QChartView(advChart);
    advanced_chart_view->setRenderHint(QPainter::Antialiasing);
    advanced_chart_view->setRubberBand(QChartView::RectangleRubberBand);
    advanced_chart_view->setInteractive(true);

    // Add advanced chart to the right vertical splitter
    if (rightVerticalSplitter) {
        rightVerticalSplitter->addWidget(advanced_chart_view);
    }
}

// 4) Periodic GUI Updates
void MainWindow::update_gui()
{
    // (A) Update order book
    bids_series->clear();
    asks_series->clear();

    auto& orderBook = engine->get_order_book();
    const auto& bids = orderBook.get_bids();
    const auto& asks = orderBook.get_asks();

    for (const auto& bid : bids) {
        bids_series->append(bid.first, bid.second);
    }
    for (const auto& ask : asks) {
        asks_series->append(ask.first, ask.second);
    }

    // Update Y-axis range
    QChart* chart = depth_chart_view->chart();
    if (chart) {
        double maxQty = 0;
        for (const auto& b : bids) {
            maxQty = std::max(maxQty, b.second);
        }
        for (const auto& a : asks) {
            maxQty = std::max(maxQty, a.second);
        }
        if (maxQty < 60) maxQty = 60;
        auto verticalAxes = chart->axes(Qt::Vertical);
        if (!verticalAxes.isEmpty()) {
            verticalAxes.first()->setRange(0, maxQty * 1.1);
        }
    }

    // (B) Update trade history table
    auto newTrades = orderBook.get_trades();
    for (const auto& trade : newTrades) {
        int row = tradeTable->rowCount();
        tradeTable->insertRow(row);
        tradeTable->setItem(row, 0, new QTableWidgetItem(QString::number(trade.timestamp)));
        tradeTable->setItem(row, 1, new QTableWidgetItem(QString::number(trade.price, 'f', 2)));
        tradeTable->setItem(row, 2, new QTableWidgetItem(QString::number(trade.quantity, 'f', 2)));
        tradeTable->setItem(row, 3, new QTableWidgetItem(QString::number(trade.taker_order_id)));
        tradeTable->setItem(row, 4, new QTableWidgetItem(QString::number(trade.maker_order_id)));
    }

    // (C) Update metrics
    double avgLatency = engine->getAverageLatencyMs();
    double throughput = engine->getThroughputOps();

    int latencyVal = static_cast<int>(std::min(avgLatency, 2000.0));
    int throughputVal = static_cast<int>(std::min(throughput, 1000.0));

    latencyBar->setValue(latencyVal);
    throughputBar->setValue(throughputVal);

    latencyLabel->setText(QString("Latency: %1 ms").arg(avgLatency, 0, 'f', 2));
    throughputLabel->setText(QString("Throughput: %1 ops").arg(throughput, 0, 'f', 1));

    // (D) Status bar for total processed orders
    uint64_t processed = engine->getProcessedOrderCount();
    statusBar()->showMessage(QString("Processed Orders: %1").arg(processed));
}

// 5) Submitting an Order
void MainWindow::submitOrder()
{
    bool okPrice, okQty;
    double price = priceEdit->text().toDouble(&okPrice);
    double quantity = quantityEdit->text().toDouble(&okQty);

    if (!okPrice || !okQty || price <= 0 || quantity <= 0) {
        statusBar()->showMessage("Error: Invalid order values. Price and Quantity must be positive.");
        return;
    }

    QString side = sideCombo->currentText();
    bool isBuy = (side == "Buy");
    QString orderTypeStr = orderTypeCombo->currentText();

    Order order;
    static uint64_t nextOrderId = 1;
    order.id = nextOrderId++;
    order.price = price;
    order.quantity = quantity;
    order.is_bid = isBuy;

    if (orderTypeStr == "Market") {
        order.type = OrderType::MARKET;
    } else {
        order.type = OrderType::LIMIT;
    }

    order.timestamp = static_cast<uint64_t>(QDateTime::currentMSecsSinceEpoch());
    order.submit_time = std::chrono::steady_clock::now();

    engine->submit_order(order);

    priceEdit->clear();
    quantityEdit->clear();
    statusBar()->showMessage("Order submitted.");
}

// 6) Simulate a random limit order
void MainWindow::simulateOrder()
{
    double price = 1.0 + QRandomGenerator::global()->generateDouble() * 99.0;
    double quantity = 1.0 + QRandomGenerator::global()->generateDouble() * 49.0;
    bool isBuy = (QRandomGenerator::global()->bounded(0, 2) == 0);

    Order order;
    static uint64_t nextOrderId = 10000;
    order.id = nextOrderId++;
    order.price = price;
    order.quantity = quantity;
    order.is_bid = isBuy;
    order.type = OrderType::LIMIT;
    order.timestamp = static_cast<uint64_t>(QDateTime::currentMSecsSinceEpoch());

    engine->submit_order(order);
}

// 7) Simulate a random market order
void MainWindow::simulateLiveMarketData()
{
    double price = 50.0 + QRandomGenerator::global()->generateDouble() * 50.0;
    double quantity = 1.0 + QRandomGenerator::global()->generateDouble() * 20.0;
    bool isBuy = (QRandomGenerator::global()->bounded(0, 2) == 0);

    Order order;
    static uint64_t nextOrderId = 20000;
    order.id = nextOrderId++;
    order.price = price;
    order.quantity = quantity;
    order.is_bid = isBuy;
    order.type = OrderType::MARKET;
    order.timestamp = static_cast<uint64_t>(QDateTime::currentMSecsSinceEpoch());

    engine->submit_order(order);
}