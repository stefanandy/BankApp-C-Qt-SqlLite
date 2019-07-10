#pragma once

#include <QWidget>
#include "ui_QtGuiClassClient.h"

class QtGuiClassClient : public QWidget
{
	Q_OBJECT

public:
	QtGuiClassClient(QWidget *parent = Q_NULLPTR);
	~QtGuiClassClient();

private:
	Ui::QtGuiClassClient ui;
};
