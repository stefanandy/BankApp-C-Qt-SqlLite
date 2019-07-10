#include "QtTransactionsHistoryUI.h"

QtTransactionsHistoryUI::QtTransactionsHistoryUI(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	
}

QtTransactionsHistoryUI::QtTransactionsHistoryUI(ClientAccount* c,QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	getConnection();
	populateComboBox(&c->getUserName());
	connect(ui.pushButton,SIGNAL(clicked()),this,SLOT(showData()));
}

QtTransactionsHistoryUI::~QtTransactionsHistoryUI()
{
}


void QtTransactionsHistoryUI::populateComboBox(QString* username) {
	
	DBManager* db = new DBManager(&QString("C:\\Users\\Lejer\\Downloads\\SQLiteDB\\UserDatabaseLite.db"));
	db->comboBoxData(this->ui.comboBox,username);
	

}

void QtTransactionsHistoryUI::getConnection()
{
	DBManager* db = new DBManager(&QString("C:\\Users\\Lejer\\Downloads\\SQLiteDB\\UserDatabaseLite.db"));
}

void QtTransactionsHistoryUI::showData() {
	 
	
	this->ui.tableView->setModel(db->getTransactionsTable(&this->ui.comboBox->currentText()));
	this->ui.tableView->hideColumn(3);
	this->ui.tableView->hideColumn(4);
	

}
