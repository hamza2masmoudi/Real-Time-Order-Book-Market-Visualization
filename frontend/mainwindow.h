#pragma once

#include <QMainWindow>
#include <QTimer>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QtCharts/QCandlestickSeries>
#include <QtCharts/QCandlestickSet>
#include <QtCharts/QCategoryAxis>
#include <QPushButton>
#include <QLineEdit>
#include <QComboBox>
#include <QGroupBox>
#include <QFormLayout>
#include <QSplitter>
#include <QTableWidget>
#include <QProgressBar>
#include <QLabel>

class MatchingEngine;

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void update_gui();
    void submitOrder();
    void simulateOrder();
    void simulateLiveMarketData();

private:
    void setupUI();
    void setupChart();
    void setupAdvancedChart();

    MatchingEngine* engine;
    QTimer* update_timer;

    // Metrics Dashboard widgets
    QProgressBar* latencyBar;
    QProgressBar* throughputBar;
    QLabel* latencyLabel;
    QLabel* throughputLabel;

    // Order submission form widgets
    QLineEdit* priceEdit;
    QLineEdit* quantityEdit;
    QComboBox* sideCombo;
    QComboBox* orderTypeCombo;
    QPushButton* submitButton;
    QGroupBox* orderFormGroup;

    // We'll create two main splitters:
    // 1) mainHorizontalSplitter (left vs right)
    // 2) On the right side, a vertical splitter for the two charts
    QSplitter* mainHorizontalSplitter;
    QSplitter* rightVerticalSplitter;

    // For the left side, we won't store a separate splitter, just a layout
    // We'll also keep the trade table there.

    // Chart objects
    QChartView* depth_chart_view;
    QLineSeries* bids_series;
    QLineSeries* asks_series;

    QChartView* advanced_chart_view;
    QCandlestickSeries* candlestick_series;
    QLineSeries* moving_average_series;

    // Trade history table
    QTableWidget* tradeTable;
};