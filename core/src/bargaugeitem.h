#ifndef BARGAUGEITEM_H
#define BARGAUGEITEM_H

#include <QPen>
#include <QPainter>
#include <QTimer>

#include "gaugeutil.h"
#include "abstractgaugeitem.h"

class BarGaugeItem : public AbstractGaugeItem
{
public:
    explicit BarGaugeItem(QWidget *parent = 0);

private:
    void init();
    void drawBackground();
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *style , QWidget *w);

    int m_size;
    int m_barSize;
    int m_padding;
    double m_pad;
    double m_range;

    QPen m_penBar;
    QPen m_penNeedle;
    QFont m_fontValue;
    QFont m_fontTitle;
    QFont m_fontUnit;

};

#endif // BARGAUGEITEM_H
