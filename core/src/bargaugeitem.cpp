#include <math.h>
#include <QString>
#include <QDebug>

#include "bargaugeitem.h"

BarGaugeItem::BarGaugeItem(QWidget *parent)
{
    Q_UNUSED(parent);
    setFlag(QGraphicsItem::ItemHasNoContents, false);
    m_redrawBackground = true;
}

void BarGaugeItem::init() {
    m_size = this->width();
    m_barSize = m_size * 0.95f;
    m_range = m_high - m_low;

    if (m_low < 0) {
        m_pad = fabs(m_low);
    }

    m_padding = (m_size - m_barSize) / 2;

    m_penBar = QPen(colorOk, (int) (m_size * 0.06f), Qt::SolidLine, Qt::FlatCap);
    m_penNeedle = QPen(colorOk, (int) (m_size * 0.04f), Qt::SolidLine, Qt::RoundCap);

    m_fontValue = QFont("helvetica", (int) (m_size * 0.12f), QFont::Bold);
    m_fontTitle = QFont("helvetica", (int) (m_size * 0.07f), QFont::Bold);
    m_fontUnit = QFont("helvetica", (int) (m_size * 0.05f), QFont::Bold);
}

void BarGaugeItem::drawBackground() {
    QPainter painter(m_background);
    painter.setRenderHint(QPainter::Antialiasing);

    // Background fill
    painter.setPen(Qt::NoPen);
    painter.setBrush(Qt::black);
    painter.drawRect(0, 0, this->width(), this->height());

    // Bar
    int locationY = this->height() / 3;

    m_penBar.setColor(colorOk);
    painter.setPen(m_penBar);
    painter.drawLine(m_padding, locationY, m_barSize + m_padding, locationY);

    m_penBar.setColor(colorWarning);
    painter.setPen(m_penBar);

    if (m_lowWarning) {
        float lengthLowWarning = (float) ((m_lowWarning.get() + m_pad) / m_range) * m_barSize + m_padding;
        painter.drawLine(m_padding, locationY, lengthLowWarning, locationY);
    }

    if (m_highWarning) {
        float lengthHighWarning = (float) ((m_high - m_highWarning.get() + m_pad) / m_range) * m_barSize;
        painter.drawLine(m_padding + m_barSize - lengthHighWarning, locationY, m_padding + m_barSize, locationY);
    }

    m_penBar.setColor(colorDanger);
    painter.setPen(m_penBar);

    if (m_lowDanger) {
        float lengthLowDanger = (float) ((m_lowDanger.get() + m_pad) / m_range) * m_barSize + m_padding;
        painter.drawLine(m_padding, locationY, lengthLowDanger, locationY);
    }

    if (m_highDanger) {
        float lengthHighDanger = (float) ((m_high - m_highDanger.get() + m_pad) / m_range) * m_barSize;
        painter.drawLine(m_padding + m_barSize - lengthHighDanger, locationY, m_padding + m_barSize, locationY);
    }

    m_penBar.setColor(Qt::white);
    painter.setPen(m_penBar);

    // Title
    painter.setFont(m_fontTitle);
    int valueX = (int (this->width() * 0.01f));
    int valueY = (int (this->height() * 0.65f));
    painter.drawText(valueX, valueY, m_title);

    // Unit
    painter.setFont(m_fontUnit);
    QFontMetrics metrics(m_fontUnit);
    QRect bbox = metrics.boundingRect(m_unit);
    valueX = (int (this->width() * 0.95f - (float) bbox.width()));
    valueY = (int (this->height() * 0.85f));
    painter.drawText(valueX, valueY, m_unit);

    painter.end();
}

void BarGaugeItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *style , QWidget *w)
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

    m_penNeedle.setColor(Qt::white);
    painter->setPen(m_penNeedle);

    // Needle
    if (isRangeSet()) {
        qDebug(">>> %d %d %d %d", (int)m_value, (int)m_pad, (int)m_range, (int)m_barSize);
        float valuePoint = ((float) ((m_value + m_pad) / m_range)) * m_barSize + m_padding;
        painter->drawLine(valuePoint, 20, valuePoint, 40);
    }

    // Value
    painter->setFont(m_fontValue);

    QString valueText;
    valueText = valueText.setNum(m_value, 'f', m_decimal);

    QFontMetrics metrics(m_fontValue);
    QRect bbox = metrics.boundingRect(valueText);

    int valueX = (int (this->width() * 0.95f - ((float) bbox.width())));
    int valueY = (int (this->height() * 0.70f));

    painter->drawText(valueX, valueY, valueText);
}
