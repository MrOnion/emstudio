#ifndef ROUNDGAUGEITEM_H
#define ROUNDGAUGEITEM_H

#include <QPen>
#include <QPainter>
#include <QTimer>

#include "gaugeutil.h"
#include "abstractgaugeitem.h"

class RoundGaugeItem : public AbstractGaugeItem
{

public:
    explicit RoundGaugeItem(QWidget *parent = 0);

private:
    void init();
    void drawBackground();
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *style , QWidget *w);

    static const int arcSize = 3600; //225 * 16;
    static const int arcStart = 2160; //135 * 16;

    int m_size;
    float m_halfsize;
    double m_range;
    int m_gap;

    int m_locationXY;
    int m_locationHighlightXY;
    int m_sizeXY;
    int m_sizeHighlightXY;
    QFont m_fontValue;
    QFont m_fontTitle;
    QFont m_fontUnit;
    QPen m_penArc;
    QPen m_penNeedle;

    /*
    int m_degreesLowDanger;
    int m_degreesLowWarning;
    int m_degreesHighDanger;
    int m_degreesHighWarning;
    int m_valueDeg;
    */

    QRectF m_arcLowDanger;
    QRectF m_arcLowWarning;
    QRectF m_arcHighDanger;
    QRectF m_arcHighWarning;
    QRectF m_arcValue;

signals:
    
public slots:

};

#endif // ROUNDGAUGEITEM_H
