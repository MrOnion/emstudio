#ifndef CUSTOMGAUGEVIEW_H
#define CUSTOMGAUGEVIEW_H

#include <QWidget>
#include <QCloseEvent>
#include "ui_datagauges.h"
#include "customgaugewidget.h"
#include "datapacketdecoder.h"

class CustomGaugeView : public QWidget
{
    Q_OBJECT
public:
    explicit CustomGaugeView(QWidget *parent = 0);
    void passData(QVariantMap data);
    void setFile(QString file);

protected:
    void closeEvent(QCloseEvent *event);

private:
    QList<QString> propertiesInUse;
    QString file;
    QTimer *guiUpdateTimer;
    DataPacketDecoder *dataPacketDecoder;
    QVariantMap m_valueMap;
    Ui::DataGauges ui;
    CustomGaugeWidget *widget;

signals:
    
public slots:

private slots:
    void guiUpdateTimerTick();
    
};

#endif // CUSTOMGAUGEVIEW_H
