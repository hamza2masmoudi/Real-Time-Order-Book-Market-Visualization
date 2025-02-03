#include "mainwindow.h"
#include "matching_engine.h"  // Backend include

#include <QtCharts/QChart>
#include <QDateTime>
#include <QDebug>
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QRandomGenerator>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      engine(new MatchingEngine),
      update_timer(new QTimer(this))
{
    engine->start();
    setupUI();
    setupChart();

    connect(update_timer, &QTimer::timeout, this, &MainWindow::update_gui);
    update_timer->start(1000); // Update the GUI every second

    // Set up a timer to simulate orders in real time.
    QTimer* simulationTimer = new QTimer(this);
    connect(simulationTimer, &QTimer::timeout, this, &MainWindow::simulateOrder);
    simulationTimer->start(500); // Generate a simulated order every 500ms
}

MainWindow::~MainWindow() {
    engine->stop();
    delete engine;
}

void MainWindow::setupUI() {
    QWidget* centralWidget = new QWidget(this);
    QVBoxLayout* mainLayout = new QVBoxLayout(centralWidget);

    // Order submission form
    QHBoxLayout* formLayout = new QHBoxLayout;
    QLabel* priceLabel = new QLabel("Price:", centralWidget);
    priceEdit = new QLineEdit(centralWidget);
    QLabel* quantityLabel = new QLabel("Quantity:", centralWidget);
    quantityEdit = new QLineEdit(centralWidget);
    sideCombo = new QComboBox(centralWidget);
    sideCombo->addItems({"Buy", "Sell"});
    submitButton = new QPushButton("Submit Order", centralWidget);

    formLayout->addWidget(priceLabel);
    formLayout->addWidget(priceEdit);
    formLayout->addWidget(quantityLabel);
    formLayout->addWidget(quantityEdit);
    formLayout->addWidget(sideCombo);
    formLayout->addWidget(submitButton);

    connect(submitButton, &QPushButton::clicked, this, &MainWindow::submitOrder);

    mainLayout->addLayout(formLayout);

    // Log/metrics label
    logLabel = new QLabel("", centralWidget);
    logLabel->setStyleSheet("color: red;");
    mainLayout->addWidget(logLabel);

    centralWidget->setLayout(mainLayout);
    setCentralWidget(centralWidget);
}

void MainWindow::setupChart() {
    QChart* chart = new QChart;
    bids_series = new QLineSeries;
    asks_series = new QLineSeries;

    bids_series->setName("Bids");
    asks_series->setName("Asks");

    chart->addSeries(bids_series);
    chart->addSeries(asks_series);
    chart->createDefaultAxes();

    depth_chart_view = new QChartView(chart);
    depth_chart_view->setRenderHint(QPainter::Antialiasing);

    // Add the chart view to the central widget's layout.
    QVBoxLayout* mainLayout = qobject_cast<QVBoxLayout*>(centralWidget()->layout());
    if (mainLayout)
        mainLayout->addWidget(depth_chart_view);
}

void MainWindow::update_gui() {
    // Update chart data
    bids_series->clear();
    asks_series->clear();

    auto& orderBook = engine->get_order_book();
    const auto& bids = orderBook.get_bids();
    const auto& asks = orderBook.get_asks();

    for (const auto& bid : bids)
        bids_series->append(bid.first, bid.second);
    for (const auto& ask : asks)
        asks_series->append(ask.first, ask.second);

    // Update performance metrics (e.g., processed orders)
    uint64_t processed = engine->getProcessedOrderCount();
    logLabel->setText(QString("Processed Orders: %1").arg(processed));
}

void MainWindow::submitOrder() {
    bool okPrice, okQty;
    double price = priceEdit->text().toDouble(&okPrice);
    double quantity = quantityEdit->text().toDouble(&okQty);

    // Validate user input
    if (!okPrice || !okQty || price <= 0 || quantity <= 0) {
        logLabel->setText("Error: Invalid order values. Price and Quantity must be positive.");
        return;
    }

    QString side = sideCombo->currentText();
    bool isBuy = (side == "Buy");

    Order order;
    static uint64_t nextOrderId = 1;
    order.id = nextOrderId++;
    order.price = price;
    order.quantity = quantity;
    order.is_bid = isBuy;
    order.type = OrderType::LIMIT;
    order.timestamp = static_cast<uint64_t>(QDateTime::currentMSecsSinceEpoch());

    engine->submit_order(order);

    // Clear inputs and error message.
    priceEdit->clear();
    quantityEdit->clear();
    logLabel->setText("");
}


void MainWindow::simulateOrder() {
    // Generate random price and quantity in a range (1.0 to 100.0 for price, 1.0 to 50.0 for quantity)
    double price = 1.0 + QRandomGenerator::global()->generateDouble() * (100.0 - 1.0);
    double quantity = 1.0 + QRandomGenerator::global()->generateDouble() * (50.0 - 1.0);

    // Randomly determine buy or sell
    bool isBuy = (QRandomGenerator::global()->bounded(0, 2) == 0);

    Order order;
    static uint64_t nextOrderId = 10000;  // Unique order ID for simulated orders
    order.id = nextOrderId++;
    order.price = price;
    order.quantity = quantity;
    order.is_bid = isBuy;
    order.type = OrderType::LIMIT;
    order.timestamp = static_cast<uint64_t>(QDateTime::currentMSecsSinceEpoch());

    engine->submit_order(order);
}