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

#include <QMetaType>
#include <QDeclarativeContext>
#include <QFile>
#include <QDir>

#include "customgaugewidget.h"

CustomGaugeWidget::CustomGaugeWidget(QWidget *parent) :
    QDeclarativeView(parent)
{
    qmlRegisterType<RoundGaugeItem>("AviatorGauges", 0, 1, "RoundGauge");
    qmlRegisterType<BarGaugeItem>("AviatorGauges", 0, 1, "BarGauge");

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
