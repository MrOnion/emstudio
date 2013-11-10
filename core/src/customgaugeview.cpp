/************************************************************************************
 * EMStudio - Open Source ECU tuning software                                       *
 * Copyright (C) 2013  Michael Carpenter (malcom2073@gmail.com)                     *
 *                                                                                  *
 * This file is a part of EMStudio                                                  *
 * Author: Ari "MrOnion" Karhu (ari@baboonplanet.com)                               *
 *                                                                                  *
 * EMStudio is free software; you can redistribute it and/or                        *
 * modify it under the terms of the GNU Lesser General Public                       *
 * License as published by the Free Software Foundation, version                    *
 * 2.1 of the License.                                                              *
 *                                                                                  *
 * EMStudio is distributed in the hope that it will be useful,                      *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of                   *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU                *
 * Lesser General Public License for more details.                                  *
 *                                                                                  *
 * You should have received a copy of the GNU Lesser General Public                 *
 * License along with this program; if not, write to the Free Software              *
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA   *
 ************************************************************************************/

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
