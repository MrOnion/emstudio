#ifndef ROUNDGAUGEWIDGET_H
#define ROUNDGAUGEWIDGET_H

#include <QDeclarativeView>
#include <QDeclarativePropertyMap>

#include "roundgaugeitem.h"
#include "bargaugeitem.h"

class CustomGaugeWidget : public QDeclarativeView
{
public:
    CustomGaugeWidget(QWidget *parent=0);
    QDeclarativePropertyMap propertyMap;
    void setFile(QString file);
    const QList<QString> getPropertiesInUse() { return propertylist; }
private:
    QList<QString> propertylist;
};

#endif // ROUNDGAUGEWIDGET_H
