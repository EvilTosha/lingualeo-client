#include <QPushButton>
#include <QStatusBar>

#include "mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent) {	
	translater_ = new Translater();
	login();

	statusBar()->showMessage(tr("Login successfully done"));
	connect(translater_, SIGNAL(requestFailed(QString)), statusBar(), SLOT(showMessage(QString)));
	mainLineEdit_ = new QLineEdit(this);

	layout()->addWidget(mainLineEdit_);

	setWindowTitle(tr("Lingualeo client"));
}

MainWindow::~MainWindow() {
  
}

void MainWindow::login() {
	/* GUI initialization*/
	loginDialog_ = new QDialog(this);
	QLabel *emailLabel = new QLabel(tr("E-mail"));
	QLabel *passwordLabel = new QLabel(tr("Password"));
	loginStatusLabel_ = new QLabel(tr("Enter your login and password for lingualeo.ru"));
	emailLineEdit_ = new QLineEdit();
	passwordLineEdit_ = new QLineEdit();
	passwordLineEdit_->setEchoMode(QLineEdit::Password);
	emailLabel->setBuddy(emailLineEdit_);
	passwordLabel->setBuddy(passwordLineEdit_);
	QPushButton *loginButton = new QPushButton(tr("Login"), loginDialog_);
	loginButton->setDefault(true);
	connect(loginButton, SIGNAL(clicked()), this, SLOT(tryLogin()));
	QPushButton *exitButton = new QPushButton(tr("Cancel"), loginDialog_);
	connect(exitButton, SIGNAL(clicked()), loginDialog_, SLOT(reject()));

	/* Layout compose */
	QGridLayout *layout = new QGridLayout(loginDialog_);
	layout->addWidget(loginStatusLabel_, 0, 0, 1, 2);
	layout->addWidget(emailLabel, 1, 0);
	layout->addWidget(emailLineEdit_, 1, 1);
	layout->addWidget(passwordLabel, 2, 0);
	layout->addWidget(passwordLineEdit_, 2, 1);
	layout->addWidget(loginButton, 3, 0);
	layout->addWidget(exitButton, 3, 1);

	emailLineEdit_->setFocus();
	loginDialog_->setLayout(layout);
	loginDialog_->setWindowTitle(tr("Authorization to lingualeo.ru"));
	loginDialog_->setModal(true);

	/* Completion logic */
	connect(translater_, SIGNAL(requestFailed(QString)), loginStatusLabel_, SLOT(setText(QString)));
	connect(translater_, SIGNAL(loginSucceed()), loginDialog_, SLOT(accept()));
	if (loginDialog_->exec()) {
		loginDialog_->close();
	}
	else {
		exit(0);
	}
}

void MainWindow::tryLogin() {
	QString email = emailLineEdit_->text();
	QString password = passwordLineEdit_->text();
	if (email == "" || password == "") {
		loginStatusLabel_->setText(tr("Please fill all fields"));
		return;
	}
	translater_->login(email, password);
}
