#include "QtApprovedCreditsUI.h"

QtApprovedCreditsUI::QtApprovedCreditsUI(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	getConnection();
	populateTable();
	connect(ui.infoButton, SIGNAL(clicked()), this, SLOT(getInfoButton()));
	
}

void QtApprovedCreditsUI::getConnection()
{
	db = new DBManager(&QString("C:\\Users\\Lejer\\Downloads\\SQLiteDB\\UserDatabaseLite.db"));

}

void QtApprovedCreditsUI::populateTable()
{
	this->ui.tableView->setModel(db->getAprovedCreditsTable());

}

void QtApprovedCreditsUI::getInfoButton(){
	
	QString iban = this->ui.tableView->selectionModel()->selectedRows().first().data().toString();
	infoUi = new QtGetInfoUI(db->getInfoFromIBAN(&iban));
	infoUi->setWindowModality(Qt::ApplicationModal);
	infoUi->show();
}


QtApprovedCreditsUI::~QtApprovedCreditsUI()
{
}
