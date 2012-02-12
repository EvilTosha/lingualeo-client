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
	options_[tr("initial_width")] = QVariant(300);
	options_[tr("initial_height")] = QVariant(200);

	/* Setting inner fields*/
	translater_ = new Translater();
	connect(translater_, SIGNAL(wordTranslated(QString,QVariant)), this, SLOT(parseTranslates(QString,QVariant)));

	login();

	/* Creating GUI elements */
	updateStatus(tr("Login successfully done"), Notification);
	connect(translater_, SIGNAL(requestFailed(QString)), this, SLOT(updateStatus(QString)));
	connect(translater_, SIGNAL(wordAdded(QString)), this, SLOT(wordAdded(QString)));

	setWindowTitle(tr("Lingualeo client"));
	resize(options_[tr("initial_width")].toInt(), options_[tr("initial_height")].toInt());
	QWidget *widget = new QWidget(this);
	setCentralWidget(widget);
	mainLineEdit_ = new QLineEdit(this);
	mainLineEdit_->setPlaceholderText("Enter word for translate");

	translatesTreeWidget_ = new QTreeWidget(this);
	translatesTreeWidget_->setMouseTracking(true);
	translatesTreeWidget_->setColumnCount(2);
	translatesTreeWidget_->setUniformRowHeights(true);
	translatesTreeWidget_->setRootIsDecorated(false);
	translatesTreeWidget_->setSelectionBehavior(QTreeWidget::SelectRows);
	translatesTreeWidget_->setFrameStyle(QFrame::Box | QFrame::Plain);
	translatesTreeWidget_->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	translatesTreeWidget_->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	translatesTreeWidget_->setHeaderHidden(true);

	postTranslateLabel_ = new QLabel(this);
	postTranslateLabel_->hide();

	/* Input validation (only latin letters and spaces) */
	QRegExp rx("[a-zA-Z\\s]*");
	QRegExpValidator *validator = new QRegExpValidator(rx);
	mainLineEdit_->setValidator(validator);

	/* Composing layout */
	QGridLayout *layout = new QGridLayout(centralWidget());
	layout->addWidget(mainLineEdit_, 0, 0);
	layout->addWidget(translatesTreeWidget_, 1, 0);
	layout->addWidget(postTranslateLabel_, 1, 0);
	widget->setLayout(layout);
}

MainWindow::~MainWindow() {
  
}


/* Login logic */
void MainWindow::login() {
	/* GUI initialization*/
	loginDialog_ = new QDialog(this);
	QLabel *emailLabel = new QLabel(tr("E-mail"), loginDialog_);
	QLabel *passwordLabel = new QLabel(tr("Password"), loginDialog_);
	loginStatusLabel_ = new QLabel(tr("Enter your login and password for lingualeo.ru"), loginDialog_);
	emailLineEdit_ = new QLineEdit(loginDialog_);
	passwordLineEdit_ = new QLineEdit(loginDialog_);
	passwordLineEdit_->setEchoMode(QLineEdit::Password);
	emailLabel->setBuddy(emailLineEdit_);
	passwordLabel->setBuddy(passwordLineEdit_);
	QLabel *registerLabel = new QLabel(loginDialog_);
	registerLabel->setOpenExternalLinks(true);
	registerLabel->setText("<a href='http://lingualeo.ru/register/step1'>" + tr("Register") + "</a>");
	registerLabel->setAlignment(Qt::AlignLeft);
	registerLabel->setAlignment(Qt::AlignBottom);

	QPushButton *loginButton = new QPushButton(tr("Login"), loginDialog_);
	loginButton->setDefault(true);
	connect(loginButton, SIGNAL(clicked()), this, SLOT(tryLogin()));
	QPushButton *exitButton = new QPushButton(tr("Cancel"), loginDialog_);
	connect(exitButton, SIGNAL(clicked()), loginDialog_, SLOT(reject()));

	/* Layout compose */
	QGridLayout *layout = new QGridLayout(loginDialog_);
	layout->addWidget(loginStatusLabel_, 0, 0, 1, 3);
	layout->addWidget(emailLabel, 1, 0);
	layout->addWidget(emailLineEdit_, 1, 1, 1, 2);
	layout->addWidget(passwordLabel, 2, 0);
	layout->addWidget(passwordLineEdit_, 2, 1, 1, 2);
	layout->addWidget(registerLabel, 3, 0);
	layout->addWidget(loginButton, 3, 1);
	layout->addWidget(exitButton, 3, 2);

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
void MainWindow::updateStatus(QString msg, MessageType type) {
	switch (type) {
		case Error:
			msg = tr("Error: ") + msg;
			break;
		case Warning:
			msg = tr("Warning: ") + msg;
			break;
		default:
			break;
	}
	statusBar()->showMessage(msg, 3000);
}

void MainWindow::wordAdded(QString translate) {
	updateStatus(tr("Word added"), Notification);
	translatesTreeWidget_->clear();
	translatesTreeWidget_->hide();
	postTranslateLabel_->setText(translate);
	postTranslateLabel_->show();
	mainLineEdit_->setFocus();
	mainLineEdit_->selectAll();
}

void MainWindow::parseTranslates(QString word, QVariant data) {
	if (word != curWord()) {
		/* Too late (another word required) */
		return;
	}
	QStringList translates;
	QStringList votes;
	QVariantList rawTranslates = data.toMap()["translate"].toList();
	for (auto translate : rawTranslates) {
		translates.push_back(translate.toMap()["value"].toString());
		votes.push_back(QString::number(translate.toMap()["votes"].toInt()));
	}
	viewTranslates(translates, votes);
}

void MainWindow::viewTranslates(QStringList &translates, QStringList &votes) {
	if (translates.count() != votes.count()) {
		return;
	}

	const QPalette &pal = palette();
	QColor color = pal.color(QPalette::Disabled, QPalette::WindowText);

	translatesTreeWidget_->setUpdatesEnabled(false);
	translatesTreeWidget_->clear();
	for (int i = 0; i < translates.count(); ++i) {
		QTreeWidgetItem *item = new QTreeWidgetItem(translatesTreeWidget_);
		item->setText(0, translates[i]);
		item->setToolTip(0, translates[i]);
		item->setText(1, votes[i]);
		item->setTextAlignment(1, Qt::AlignRight);
		item->setTextColor(1, color);
		item->setFlags(item->flags() | Qt::ItemIsEditable);
	}
	QTreeWidgetItem *myTranslate = new QTreeWidgetItem(translatesTreeWidget_);
	myTranslate->setText(0, TRANSLATE_PLACEHOLDER_TEXT);
	myTranslate->setTextColor(0, color);
	myTranslate->setFlags(myTranslate->flags() | Qt::ItemIsEditable);

	translatesTreeWidget_->setCurrentItem(translatesTreeWidget_->topLevelItem(0));
	adjustInnerWidgets();
	//translatesTreeWidget_->adjustSize();

	postTranslateLabel_->hide();

	translatesTreeWidget_->setUpdatesEnabled(true);
	translatesTreeWidget_->setFocus();
	translatesTreeWidget_->show();
	update();
}

void MainWindow::adjustInnerWidgets() {
	translatesTreeWidget_->resizeColumnToContents(0); // needed for correct resizing of second column
	translatesTreeWidget_->resizeColumnToContents(1);
	translatesTreeWidget_->setColumnWidth(0, translatesTreeWidget_->width() - translatesTreeWidget_->columnWidth(1) - 5);
}

void MainWindow::keyReleaseEvent(QKeyEvent *event) {
	if (event->key() == Qt::Key_Enter || event->key() == Qt::Key_Return) {
		if (focusWidget() == mainLineEdit_) {
			QString word = mainLineEdit_->text();
			setCurWord(word);
			translater_->getTranslates(word, options_["include_media"].toBool());
		}
		else {
			QString translate = translatesTreeWidget_->currentItem()->text(0);
			if (translate == TRANSLATE_PLACEHOLDER_TEXT) {
				updateStatus(tr("Please enter translate"), Error);
			}
			else {
				translater_->addWord(curWord(), translate);
			}
		}
	}
}

void MainWindow::resizeEvent(QResizeEvent *event) {
	QMainWindow::resizeEvent(event);
	adjustInnerWidgets();
}

/* Getters/Setters */
QString MainWindow::curWord() const {
	return curWord_;
}

void MainWindow::setCurWord(const QString word) {
	curWord_ = word;
}
