#include "QtClientAskForCreditUI.h"

QtClientAskForCreditUI::QtClientAskForCreditUI(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	

}

QtClientAskForCreditUI::QtClientAskForCreditUI(QString* user,QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	dbOpen();
	GetComboBoxData(user);
	connect(ui.pushButton, SIGNAL(clicked()), this, SLOT(handleSendButton()));
}

QtClientAskForCreditUI::~QtClientAskForCreditUI()
{
	db->closeDatabase();
}

void QtClientAskForCreditUI::dbOpen() {
	
	db = new DBManager(&QString("C:\\Users\\Lejer\\Downloads\\SQLiteDB\\UserDatabaseLite.db"));

}

void QtClientAskForCreditUI::GetComboBoxData(QString* u) {
	
	db->comboBoxData(this->ui.comboBox, u);

}

void QtClientAskForCreditUI::handleSendButton() {
	
	double value = this->ui.textEdit->toPlainText().toDouble();
	db->creditDatabaseInsert(&this->ui.comboBox->currentText(),&value);

}
