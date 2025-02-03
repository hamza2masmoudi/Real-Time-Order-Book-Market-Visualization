#pragma once

#include <QMainWindow>
#include <QTimer>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QPushButton>
#include <QLineEdit>
#include <QComboBox>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>

class MatchingEngine;

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void update_gui();
    void submitOrder();
    void simulateOrder();  // New function for simulation

private:
    void setupUI();
    void setupChart();

    MatchingEngine* engine;
    QTimer* update_timer;

    QChartView* depth_chart_view;
    QLineSeries* bids_series;
    QLineSeries* asks_series;

    QLineEdit* priceEdit;
    QLineEdit* quantityEdit;
    QComboBox* sideCombo;
    QPushButton* submitButton;

    QLabel* logLabel;
};