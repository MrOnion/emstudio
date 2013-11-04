#include <QMetaType>
#include <QDeclarativeContext>
#include <QFile>
#include <QDir>

#include "customgaugewidget.h"

CustomGaugeWidget::CustomGaugeWidget(QWidget *parent) :
    QDeclarativeView(parent)
{
    qmlRegisterType<RoundGaugeItem>("CustomGauges", 0, 1, "RoundGauge");
    qmlRegisterType<BarGaugeItem>("CustomGauges", 0, 1, "BarGauge");

    this->rootContext()->setContextProperty("propertyMap",&propertyMap);
}

void CustomGaugeWidget::setFile(QString file)
{
    setSource(QUrl::fromLocalFile(file));
    if (rootObject())
    {
        for (int i=0;i<rootObject()->childItems().size();i++)
        {
            QGraphicsObject *obj = qobject_cast<QGraphicsObject*>(rootObject()->childItems()[i]);
            if (obj)
            {
                propertylist.append(obj->property("propertyMapProperty").toString());
            }
        }
    }
}
