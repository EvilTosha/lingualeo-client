#include <QPushButton>

#include "mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent) {
	translater_ = new Translater();

	login();
}

MainWindow::~MainWindow() {
  
}

void MainWindow::login() {
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


	QGridLayout *layout = new QGridLayout(loginDialog_);
	layout->addWidget(emailLabel, 0, 0);
	layout->addWidget(emailLineEdit_, 0, 1);
	layout->addWidget(passwordLabel, 1, 0);
	layout->addWidget(passwordLineEdit_, 1, 1);
	layout->addWidget(loginStatusLabel_, 2, 0, 1, 2);
	layout->addWidget(loginButton, 3, 0);
	layout->addWidget(exitButton, 3, 1);

	emailLineEdit_->setFocus();
	loginDialog_->setLayout(layout);
	loginDialog_->setWindowTitle(tr("Authorization to lingualeo.ru"));
	loginDialog_->setModal(true);
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
		loginFail(tr("Please fill all fields"));
		return;
	}
	translater_->login(email, password);
}

void MainWindow::loginFail(QString errorMsg) {
	loginStatusLabel_->setText(tr("Login failed : ") + errorMsg);
}

void MainWindow::loginSuccess() {
	qDebug() << "Login Success";
	loginDialog_->accept();
}
