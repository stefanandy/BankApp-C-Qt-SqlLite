#include "QtAdminClass.h"

QtAdminClass::QtAdminClass(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	
}

QtAdminClass::QtAdminClass(AdminAccount* admin_ ,QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	admin = admin_;
	getDbConnection();
	populateTable();
	connect(ui.unaprovedCredits, SIGNAL(clicked()), this, SLOT(unaprovedCreditsButton()));
	connect(ui.activeCreditsButton, SIGNAL(clicked()), this, SLOT(approvedCreditsButton()));
	connect(ui.refreshButton, SIGNAL(clicked()), this, SLOT(refreshButton()));
}

void QtAdminClass::getDbConnection()
{
	db = new DBManager(&QString("C:\\Users\\Lejer\\Downloads\\SQLiteDB\\UserDatabaseLite.db"));

}

void QtAdminClass::populateTable()
{
	this->ui.tableView->setModel(db->getCreditTable());
}

void QtAdminClass::unaprovedCreditsButton()
{
	unverifiedcreditsUI = new QtAdminUnverifiedCreditsUI();
	unverifiedcreditsUI->setWindowModality(Qt::ApplicationModal);
	unverifiedcreditsUI->show();
}

QtAdminClass::~QtAdminClass()
{
}

void QtAdminClass::approvedCreditsButton()
{
	approvedCreditsUI = new QtApprovedCreditsUI();
	approvedCreditsUI->setWindowModality(Qt::ApplicationModal);
	approvedCreditsUI->show();
}

void QtAdminClass::refreshButton()
{
	populateTable();
}
