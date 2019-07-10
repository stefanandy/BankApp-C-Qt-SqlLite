#include "QtGetInfoUI.h"


QtGetInfoUI::QtGetInfoUI(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
}

QtGetInfoUI::QtGetInfoUI(ClientAccount* cacc,QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	client = cacc;
	ui.firstNameText->setPlainText(client->getFirstName());
	ui.lastNameText->setPlainText(client->getLastName());
	ui.phNumberText->setPlainText(client->getPhoneNumber());
	loadTableData();

}

void QtGetInfoUI::getConnection()
{
	db = new DBManager(&QString("C:\\Users\\Lejer\\Downloads\\SQLiteDB\\UserDatabaseLite.db"));

}

void QtGetInfoUI::loadTableData()
{
	this->ui.tableView->setModel(db->getIBANTable(&client->getUserName()));
	this->ui.tableView->hideColumn(0);
}


QtGetInfoUI::~QtGetInfoUI()
{
}
