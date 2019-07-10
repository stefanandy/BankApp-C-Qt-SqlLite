#pragma once

#include <QWidget>
#include "ui_QtDeleteBAUI.h"
#include "DBManager.h"

class QtDeleteBAUI : public QWidget
{
	Q_OBJECT

public:
	QtDeleteBAUI(QWidget *parent = Q_NULLPTR);
	QtDeleteBAUI(QString*, QWidget *parent = Q_NULLPTR);
	void loadIBANList(QString*);
	~QtDeleteBAUI();

private slots:
	void deleteAction();

private:
	Ui::QtDeleteBAUI ui;
	
};
