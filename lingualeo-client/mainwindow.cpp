#include <QPushButton>
#include <QStatusBar>
#include <QValidator>
#include <QAction>
#include <QStringListModel>

#include "mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent) {	
	/* Options setup */
	options_[tr("include_media")] = QVariant(true);

	/* Setting inner fields*/
	translater_ = new Translater();
	connect(translater_, SIGNAL(wordTranslated(QString,QVariant)), this, SLOT(parseTranslates(QString,QVariant)));

	login();

	statusBar()->showMessage(tr("Login successfully done"));
	connect(translater_, SIGNAL(requestFailed(QString)), statusBar(), SLOT(showMessage(QString)));

	/* Creating GUI elements */
	setWindowTitle(tr("Lingualeo client"));
	QWidget *widget = new QWidget(this);
	setCentralWidget(widget);
	mainLineEdit_ = new QLineEdit(this);
	mainLineEdit_->setPlaceholderText(tr("Enter word for translate"));
	translatesListView_ = new QListView(this);
	translatesListView_->setViewMode(QListView::ListMode);
	translatesListView_->setFlow(QListView::TopToBottom);
	translatesListView_->setMovement(QListView::Static);

	/* Debug staff */
	QStringList v {"aba", "caba", "daba"};
	viewTranslates(v);
	/* End of debug staff */

	/* Input validation (only latin letters and spaces) */
	QRegExp rx("[a-zA-Z\\s]*");
	QRegExpValidator *validator = new QRegExpValidator(rx);
	mainLineEdit_->setValidator(validator);

	/* Composing layout */
	QGridLayout *layout = new QGridLayout(centralWidget());
	layout->addWidget(mainLineEdit_, 0, 0);
	layout->addWidget(translatesListView_, 1, 0);
	widget->setLayout(layout);
}

MainWindow::~MainWindow() {
  
}


/* Login logic */
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

/* Main logic */
void MainWindow::parseTranslates(QString word, QVariant data) {
	qDebug() << "Word = " << word << endl << "Data = " << data << endl;
}

void MainWindow::viewTranslates(QStringList &translates) {
	QAbstractItemModel *model = new QStringListModel(translates);
	translatesListView_->setModel(model);
}

void MainWindow::keyReleaseEvent(QKeyEvent *event) {
	if (focusWidget() == mainLineEdit_) {
		if (event->key() == Qt::Key_Enter || event->key() == Qt::Key_Return) {
			translater_->getTranslates(mainLineEdit_->text(), options_["include_media"].toBool());
		}
	}
}
