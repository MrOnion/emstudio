#include <math.h>
#include <QString>
#include <QDebug>

#include "roundgaugeitem.h"

RoundGaugeItem::RoundGaugeItem(QWidget *parent)
{
    Q_UNUSED(parent);
    setFlag(QGraphicsItem::ItemHasNoContents, false);
    m_redrawBackground = true;
}

void RoundGaugeItem::init() {
    m_size = this->width();
    m_halfsize = m_size / 2;

    if (m_low < 0) {
        m_pad = fabs(m_low);
    }

    m_range = m_high - m_low;

    m_locationXY = (int (m_size * 0.05f));
    m_locationHighlightXY = (m_size * 0.12f);
    m_sizeXY = (int (m_size * 0.9f));
    m_sizeHighlightXY = (m_size * 0.77f);

    m_penArc = QPen(colorOk, (int) (m_size * 0.05f), Qt::SolidLine, Qt::FlatCap);
    m_penNeedle = QPen(colorOk, (int) (m_size * 0.04f), Qt::SolidLine, Qt::RoundCap);

    m_fontValue = QFont("helvetica", (int) (m_size * 0.12f), QFont::Bold);
    m_fontTitle = QFont("helvetica", (int) (m_size * 0.07f), QFont::Bold);
    m_fontUnit = QFont("helvetica", (int) (m_size * 0.05f), QFont::Bold);
}

void RoundGaugeItem::drawBackground() {
    QPainter painter(m_background);
    painter.setRenderHint(QPainter::Antialiasing);

    // Background fill
    painter.setPen(Qt::NoPen);
    painter.setBrush(Qt::black);
    painter.drawRect(0, 0, this->width(), this->height());

    // Arcs

    //TODO: don't draw arcs on top of each other

    m_penArc.setColor(colorOk);
    painter.setPen(m_penArc);
    painter.drawArc(m_locationXY, m_locationXY, m_sizeXY, m_sizeXY, 0, arcSize);

    m_penArc.setColor(colorWarning);
    painter.setPen(m_penArc);

    if (m_lowWarning) {
        int degreesLowWarning = (int ((m_lowWarning.get() + m_pad) * arcSize / m_range));
        painter.drawArc(m_locationXY, m_locationXY, m_sizeXY, m_sizeXY, (arcSize - degreesLowWarning), degreesLowWarning);
    }

    if (m_highWarning) {
        int degreesHighWarning = (int ((m_high - m_highWarning.get() + m_pad) * arcSize / m_range));
        painter.drawArc(m_locationXY, m_locationXY, m_sizeXY, m_sizeXY, 0, degreesHighWarning);
    }

    m_penArc.setColor(colorDanger);
    painter.setPen(m_penArc);

    if (m_lowDanger) {
        int degreesLowDanger = (int ((m_lowDanger.get() + m_pad) * arcSize / m_range));
        painter.drawArc(m_locationXY, m_locationXY, m_sizeXY, m_sizeXY, (arcSize - degreesLowDanger), degreesLowDanger);
    }

    if (m_highDanger) {
        int degreesHighDanger = (int ((m_high - m_highDanger.get() + m_pad) * arcSize / m_range));
        painter.drawArc(m_locationXY, m_locationXY, m_sizeXY, m_sizeXY, 0, degreesHighDanger);
    }

    // Highlight arc
    if (isHighlighted(m_value)) {
        m_penArc.setColor(getStatusColor(m_value));
        painter.setPen(m_penArc);
        painter.drawArc(m_locationHighlightXY, m_locationHighlightXY, m_sizeHighlightXY, m_sizeHighlightXY, 0, arcSize);
    }

    // Title
    m_penArc.setColor(Qt::white);
    painter.setPen(m_penArc);
    painter.setFont(m_fontTitle);
    QFontMetrics metrics2(m_fontTitle);
    QRect bbox = metrics2.boundingRect(m_title);

    int valueX = (int (this->width() * 0.90f - bbox.width()));
    int valueY = (int (this->height() * 0.90f));

    painter.drawText(valueX, valueY, m_title);

    // Unit
    painter.setFont(m_fontUnit);
    QFontMetrics metrics3(m_fontUnit);
    bbox = metrics3.boundingRect(m_unit);

    valueX = (int (this->width() / 2 - (bbox.width() / 2)));
    valueY = (int (this->height() * 0.35f));

    painter.drawText(valueX, valueY, m_unit);

    painter.end();
}

void RoundGaugeItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *style , QWidget *w)
{
    Q_UNUSED(style);
    Q_UNUSED(w);

    if (m_redrawBackground) {
        m_redrawBackground = false;
        this->init();
        this->drawBackground();
    }

    painter->setRenderHint(QPainter::Antialiasing);

    // Background
    painter->drawImage(0, 0, *m_background);

    // Needle
    if (isRangeSet()) {
        m_penNeedle.setColor(Qt::white);
        painter->setPen(m_penNeedle);
        float valueAmount = (float) ((m_value + m_pad - (m_low > 0 ? m_low : 0)) / m_range);

        int *needlePoints1 = GaugeUtil::getPointInArc((int) m_halfsize, (int) m_halfsize, arcSize, arcStart, (int) (m_size * 0.1f), valueAmount);
        int *needlePoints2 = GaugeUtil::getPointInArc((int) m_halfsize, (int) m_halfsize, arcSize, arcStart, (int) (m_size * 0.3f), valueAmount);

        painter->drawLine(needlePoints1[0], needlePoints1[1], needlePoints2[0], needlePoints2[1]);
    }

    // Value
    painter->setFont(m_fontValue);

    QString valueText;
    valueText = valueText.setNum(m_value, 'f', m_decimal);

    QFontMetrics metrics(m_fontValue);
    QRect bbox = metrics.boundingRect(valueText);

    int valueX = (int (this->width() * 0.90f - (float) bbox.width()));
    int valueY = (int (this->height() * 0.80f));

    painter->drawText(valueX, valueY, valueText);
}
