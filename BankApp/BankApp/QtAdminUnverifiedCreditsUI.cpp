#include "QtAdminUnverifiedCreditsUI.h"

QtAdminUnverifiedCreditsUI::QtAdminUnverifiedCreditsUI(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	getConnection();
	populateBox();
	connect(ui.aprovePushButton,SIGNAL(clicked()),this,SLOT(approvedButton()));
	connect(ui.getInfoPushButton, SIGNAL(clicked()), this, SLOT(getInfoButton()));
	
}

void QtAdminUnverifiedCreditsUI::populateBox()
{
	db->getUnaprovedCreditsIBAN(this->ui.comboBox);
}

void QtAdminUnverifiedCreditsUI::getConnection() {
	
	db = new DBManager(&QString("C:\\Users\\Lejer\\Downloads\\SQLiteDB\\UserDatabaseLite.db"));

}

QtAdminUnverifiedCreditsUI::~QtAdminUnverifiedCreditsUI()
{
}

void QtAdminUnverifiedCreditsUI::approvedButton()
{
	QString* iban = &this->ui.comboBox->currentText();
	db->updateCreditState(iban);
	db->updateAddCreditToBalance(iban);
	this->ui.comboBox->clear();
	populateBox();

}

void QtAdminUnverifiedCreditsUI::getInfoButton() {
	
	infoUi = new QtGetInfoUI(db->getInfoFromIBAN(&this->ui.comboBox->currentText()));
	infoUi->setWindowModality(Qt::ApplicationModal);
	infoUi->show();

}
