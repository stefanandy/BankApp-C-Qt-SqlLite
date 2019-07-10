#include "QtMakePaymentUI.h"

QtMakePaymentUI::QtMakePaymentUI(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
}


QtMakePaymentUI::QtMakePaymentUI(ClientAccount* cAcc,QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	clientAccount = cAcc;
	getConnection();
	ibanLis(&clientAccount->getUserName());
	connect(ui.pushButton, SIGNAL(clicked()), this, SLOT(checkIBAN()));
	connect(ui.sendButton, SIGNAL(clicked()), this, SLOT(sendTransaction()));
	
	
}


QtMakePaymentUI::~QtMakePaymentUI()
{
}

void QtMakePaymentUI::ibanLis(QString* user) {
	
	
	db->comboBoxData(this->ui.comboBox, user);
	
}

void QtMakePaymentUI::getConnection()
{
	 db = new DBManager(&QString("C:\\Users\\Lejer\\Downloads\\SQLiteDB\\UserDatabaseLite.db"));
}

void QtMakePaymentUI::MouseEvent(QMouseEvent* event) {
	
	if (event->MouseButtonPress == Qt::MouseButton::LeftButton ) {
		
		
		ClientAccount* c = db->getAccountFromUserOnly(&db->getUserNameFromIban(&this->ui.ibanReceiver->toPlainText()));
		this->ui.receiverFirstNameTextEdit->setPlainText(c->getFirstName());
		this->ui.receiverLastNameTextEdit->setPlainText(c->getLastName());
		this->ui.receiverFirstNameTextEdit->setEnabled(false);
		this->ui.receiverLastNameTextEdit->setEnabled(false);
		event->accept();
	}

}



void QtMakePaymentUI::checkIBAN() {
	
	
	ClientAccount* c = db->getAccountFromUserOnly(&db->getUserNameFromIban(&this->ui.ibanReceiver->toPlainText()));
	this->ui.receiverFirstNameTextEdit->setPlainText(c->getFirstName());
	this->ui.receiverLastNameTextEdit->setPlainText(c->getLastName());
	this->ui.receiverFirstNameTextEdit->setEnabled(false);
	this->ui.receiverLastNameTextEdit->setEnabled(false);
	


}

void QtMakePaymentUI::sendTransaction() {

	
	
	BankAccount* sender = db->getBankAccountFromDB(&this->ui.comboBox->currentText());
	BankAccount* receiver = db->getBankAccountFromDB(&this->ui.ibanReceiver->toPlainText());
	
	double value_ = this->ui.valueTextEdit->toPlainText().toDouble();
	
	if (sender->getValue() >= value_) {

		db->makeTransaction(&sender->getIBAN(),&receiver->getIBAN()
			,&value_, &sender->getCurrency(),&receiver->getCurrency());
		
		receiver->updateBalance(&value_);
		db->updateBankAccountBalance(receiver);

		value_ *= -1;
		sender->updateBalance(&value_);
		db->updateBankAccountBalance(sender);

	}
	else { db->ErrorMessage(&QString("NOT ENOUGHT MONEY!")); }
	


}