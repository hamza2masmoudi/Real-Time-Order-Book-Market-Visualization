#pragma once

#include <QtCharts/QChartView>
#include <QtCharts/QChart>
#include <QPainter>

class ChartWidget : public QChartView {
    Q_OBJECT
public:
    explicit ChartWidget(QWidget* parent = nullptr);
};