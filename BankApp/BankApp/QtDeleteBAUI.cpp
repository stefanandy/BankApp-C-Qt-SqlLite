#include "QtDeleteBAUI.h"

QtDeleteBAUI::QtDeleteBAUI(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
}


QtDeleteBAUI::QtDeleteBAUI(QString* user, QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	loadIBANList(user);
	connect(ui.deleteButton, SIGNAL(clicked()), this, SLOT(deleteAction()));
}

QtDeleteBAUI::~QtDeleteBAUI()
{
}




void QtDeleteBAUI::loadIBANList(QString* user) {

	DBManager* db = new DBManager(&QString("C:\\Users\\Lejer\\Downloads\\SQLiteDB\\UserDatabaseLite.db"));
	db->comboBoxData(this->ui.comboBox, user);
	db->closeDatabase();
}


void QtDeleteBAUI::deleteAction() {
	
	DBManager* db = new DBManager(&QString("C:\\Users\\Lejer\\Downloads\\SQLiteDB\\UserDatabaseLite.db"));
	
	if (db->getBankAccountFromDB(&this->ui.comboBox->currentText())->getValue() == 0) {	
	
		db->deleteBankAccount(this->ui.comboBox);
		
	
	}else {  
	
		db->ErrorMessage(&QString("BAnk Account not empty"));
	
	}
	db->closeDatabase();

}
