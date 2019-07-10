#pragma once

#include <qstandarditemmodel.h>

class DataModel : public QStandardItemModel
{
	//Q_OBJECT
	int row, columns;

public:
	//DataModel(QObject *parent);
	DataModel(QStandardItemModel* );
	~DataModel();

};
