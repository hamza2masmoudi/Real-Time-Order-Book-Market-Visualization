#include "chart_widget.h"

ChartWidget::ChartWidget(QWidget* parent)
    : QChartView(new QChart(), parent)
{
    setRenderHint(QPainter::Antialiasing);
}