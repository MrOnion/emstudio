#include "abstractgaugeitem.h"

const QColor AbstractGaugeItem::colorOk = QColor::fromRgb(40, 150, 40);
const QColor AbstractGaugeItem::colorWarning = QColor::fromRgb(240, 215, 50);
const QColor AbstractGaugeItem::colorDanger = QColor::fromRgb(220, 40, 40);
const QColor AbstractGaugeItem::colorValue = QColor::fromRgb(50, 100, 50);

AbstractGaugeItem::AbstractGaugeItem(QDeclarativeItem *parent) :
    QDeclarativeItem(parent)
{
    m_title = "---";
    m_unit = "";
    m_low = 0;
    m_high = 0;
    m_decimal = 0;
}

double AbstractGaugeItem::getLow() {
    return m_low;
}

void AbstractGaugeItem::setLow(double low) {
    m_low = low;
}

double AbstractGaugeItem::getHigh() {
    return m_high;
}

void AbstractGaugeItem::setHigh(double high) {
    m_high = high;
}

double AbstractGaugeItem::getLowWarning() {
    return m_lowWarning.get();
}

void AbstractGaugeItem::setLowWarning(double lowWarning) {
    m_lowWarning = lowWarning;
}

double AbstractGaugeItem::getLowDanger() {
    return m_lowDanger.get();
}

void AbstractGaugeItem::setLowDanger(double lowDanger) {
    m_lowDanger = lowDanger;
}

double AbstractGaugeItem::getHighWarning() {
    return m_highWarning.get();
}

void AbstractGaugeItem::setHighWarning(double highWarning) {
    m_highWarning = highWarning;
}

double AbstractGaugeItem::getHighDanger() {
    return m_highDanger.get();
}

void AbstractGaugeItem::setHighDanger(double highDanger) {
    m_highDanger = highDanger;
}

QString AbstractGaugeItem::getTitle() {
    return m_title;
}

void AbstractGaugeItem::setTitle(QString title) {
    m_title = title;
}

QString AbstractGaugeItem::getUnit() {
    return m_unit;
}

void AbstractGaugeItem::setUnit(QString unit) {
    m_unit = unit;
}

int AbstractGaugeItem::getDecimal() {
    return m_decimal;
}

void AbstractGaugeItem::setDecimal(int decimal) {
    m_decimal = decimal;
}

void AbstractGaugeItem::setValue(double value) {
    m_value = value;
    update();
}

double AbstractGaugeItem::getValue() {
    return m_value;
}

bool AbstractGaugeItem::isRangeSet() {
    if (m_low == m_high) {
        return false;
    } else if (m_value < m_low || m_value > m_high) {
        return false;
    }

    return true;
}

int AbstractGaugeItem::getStatus() {
    if (isRangeSet()) {
        if (m_lowDanger) {
            if (m_value <= m_lowDanger.get()) {
                return STATUS_DANGER;
            }
        }
        if (m_highDanger) {
            if (m_value >= m_highDanger.get()) {
                return STATUS_DANGER;
            }
        }
        if (m_lowWarning) {
            if (m_value <= m_lowWarning.get()) {
                return STATUS_WARNING;
            }
        }
        if (m_highWarning) {
            if (m_value >= m_highWarning.get()) {
                return STATUS_WARNING;
            }
        }
    }

    return STATUS_OK;
}

bool AbstractGaugeItem::isHighlighted() {
    if (getStatus() == STATUS_WARNING || getStatus() == STATUS_DANGER) {
        return true;
    } else {
        return false;
    }
}

QColor AbstractGaugeItem::getStatusColor() {
    if (getStatus() == STATUS_DANGER) {
        return colorDanger;
    } else if (getStatus() == STATUS_WARNING) {
        return colorWarning;
    } else {
        return colorOk;
    }
}

void AbstractGaugeItem::geometryChanged(const QRectF &newGeometry, const QRectF &oldGeometry)
{
    Q_UNUSED(oldGeometry);
    delete m_background;
    m_background = new QImage(newGeometry.width(),newGeometry.height(),QImage::Format_ARGB32);
    this->init();
    m_redrawBackground = true;
}
