#include "customgaugeview.h"
#include <QMdiSubWindow>

CustomGaugeView::CustomGaugeView(QWidget *parent) :
    QWidget(parent)
{
    ui.setupUi(this);
    widget = new CustomGaugeWidget(this);
    widget->setGeometry(0,0,1200,700);
    widget->show();

    guiUpdateTimer = new QTimer(this);
    connect(guiUpdateTimer,SIGNAL(timeout()),this,SLOT(guiUpdateTimerTick()));
    guiUpdateTimer->start(250);
}

void CustomGaugeView::closeEvent(QCloseEvent *event)
{
    event->ignore();
    ((QMdiSubWindow*)this->parent())->hide();
}
void CustomGaugeView::passData(QVariantMap data)
{
    m_valueMap = data;
}
void CustomGaugeView::setFile(QString file)
{
    widget->setFile(file);
    propertiesInUse = widget->getPropertiesInUse();
}

void CustomGaugeView::guiUpdateTimerTick()
{

    QVariantMap::const_iterator i = m_valueMap.constBegin();
    while (i != m_valueMap.constEnd())
    {
        if (propertiesInUse.contains(i.key()))
        {
            widget->propertyMap.setProperty(i.key().toAscii(),i.value());
        }
        //ui.tableWidget->item(m_nameToIndexMap[i.key()],1)->setText(QString::number(i.value()));
        //qDebug() << i.key() << m_nameToIndexMap[i.key()] << i.value();
        i++;
    }

}
