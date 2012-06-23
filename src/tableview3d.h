#ifndef TABLEVIEW3D_H
#define TABLEVIEW3D_H

#include <QWidget>
#include "ui_tableview3d.h"

class TableView3D : public QWidget
{
	Q_OBJECT
	
public:
	explicit TableView3D(QWidget *parent = 0);
	~TableView3D();
	void passData(unsigned short locationid,QByteArray data,int physicallocation);
private:
	unsigned short m_locationId;
	unsigned short currentvalue;
	Ui::TableView3D ui;
private slots:
	void tableCurrentCellChanged(int currentrow,int currentcolumn,int prevrow,int prevcolumn);
	void tableCellChanged(int row,int column);
signals:
	void saveSingleData(unsigned short locationid,QByteArray data, unsigned short offset, unsigned short size);
};

#endif // TABLEVIEW3D_H
