#include <QPushButton>
#include <QStatusBar>
#include <QValidator>
#include <QAction>
#include <QStringListModel>

#include "mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent), knownTranslateColor_(Qt::darkRed) {
	setWindowTitle(tr("Lingualeo client"));
	setWindowIcon(QIcon("resources/logo_transparent.png"));

	/* Options setup */
	options_[tr("include_media")] = QVariant(true);
	options_[tr("initial_width")] = QVariant(410);
	options_[tr("initial_height")] = QVariant(200);
	options_[tr("max_image_size")] = QVariant(QSize(110, 110));
	options_[tr("download_images")] = QVariant(true);

	/* Setting inner fields*/
	translater_ = new Translater();
	connect(translater_, SIGNAL(wordTranslated(QString,QVariant)), this, SLOT(parseTranslates(QString,QVariant)));

	showLoginDialog();

	/* Creating GUI elements */
	connect(translater_, SIGNAL(requestFailed(QString)), this, SLOT(updateStatus(QString)));
	connect(translater_, SIGNAL(wordAdded(QString)), this, SLOT(wordAdded(QString)));

	resize(options_[tr("initial_width")].toInt(), options_[tr("initial_height")].toInt());

	/* Menu elements */
	QMenu *toolsMenu = menuBar()->addMenu(tr("&Tools"));
	toolsMenu->addAction(tr("Preferances"), this, SLOT(showPreferancesDialog()));
	QMenu *helpMenu = menuBar()->addMenu(tr("&Help"));
	helpMenu->addAction(tr("About"), this, SLOT(showAboutDialog()));

	/* LineEdit for words */
	mainLineEdit_ = new QLineEdit(this);
	mainLineEdit_->setPlaceholderText(tr("Enter word for translate"));
	/* Input validation (only latin letters and spaces) */
	QRegExp rx("[a-zA-Z\\s]*");
	QRegExpValidator *validator = new QRegExpValidator(rx);
	mainLineEdit_->setValidator(validator);

	/* Central part */
	QWidget *widget = new QWidget(this);
	setCentralWidget(widget);

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

	/* Image viewer */
	imageLabel_ = new QLabel(this);
	imageLabel_->setMaximumSize(options_["max_image_size"].toSize());
	imageLabel_->show();
	connect(translater_, SIGNAL(pictureGot(QString,QPixmap*)), this, SLOT(viewImage(QString,QPixmap*)));

	/* Composing layout */
	QGridLayout *layout = new QGridLayout(centralWidget());
	layout->addWidget(mainLineEdit_, 0, 0, 1, 2);
	layout->addWidget(translatesTreeWidget_, 1, 0);
	layout->addWidget(postTranslateLabel_, 1, 0);
	layout->addWidget(imageLabel_, 1, 1);
	layout->setColumnMinimumWidth(1, 110);
	widget->setLayout(layout);
}

MainWindow::~MainWindow() {

}


/* Login logic */
void MainWindow::showLoginDialog() {
	/* GUI initialization*/
	loginDialog_ = new QDialog(this);
	loginDialog_->setWindowTitle(tr("Authorization to lingualeo.ru"));
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
	loginDialog_->setModal(true);

	/* Completion logic */
	connect(translater_, SIGNAL(requestFailed(QString)), loginStatusLabel_, SLOT(setText(QString)));
	connect(translater_, SIGNAL(loginSucceed()), loginDialog_, SLOT(accept()));
	if (loginDialog_->exec()) {
		loginDialog_->close();
		updateStatus(tr("Login successfully done"), Notification);
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
	postTranslateLabel_->setText(QString("<font color='%1'><b>%2</b></font>").arg(knownTranslateColor_.name(), translate));
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
	bool known = data.toMap()["knownWord"].toBool();
	viewTranslates(translates, votes, known);
	QString imagePath = data.toMap()["pic_url"].toString();
	translater_->getPicture(word, imagePath);
}

void MainWindow::viewTranslates(QStringList &translates, QStringList &votes, bool known) {
	if (translates.count() != votes.count()) {
		return;
		}

	const QPalette &pal = palette();
	QColor color = pal.color(QPalette::Disabled, QPalette::WindowText);

	translatesTreeWidget_->setUpdatesEnabled(false);
	translatesTreeWidget_->clear();
	for (int i = 0; i < translates.count(); ++i) {
		QTreeWidgetItem *item = new QTreeWidgetItem(translatesTreeWidget_);
		if (known && i == 0) {
			item->setTextColor(0, knownTranslateColor_);
			QFont font(item->font(0));
			font.setBold(true);
			item->setFont(0, font);
			}
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

void MainWindow::viewImage(QString word, QPixmap *image) {
	if (word != curWord()) {
		// too late
		return;
		}
	QSize maxSize = options_["max_image_size"].toSize();
	if (image->size().height() > maxSize.height() || image->size().width() > maxSize.width()) {
		imageLabel_->setPixmap((*image).scaled(maxSize , Qt::KeepAspectRatio));
		}
	else {
		imageLabel_->setPixmap(*image);
		}
	imageLabel_->show();
	update();
}

void MainWindow::adjustInnerWidgets() {
	translatesTreeWidget_->resizeColumnToContents(0); // needed for correct resizing of second column
	translatesTreeWidget_->resizeColumnToContents(1);
	translatesTreeWidget_->setColumnWidth(0, translatesTreeWidget_->width() - translatesTreeWidget_->columnWidth(1) - 10);
}

void MainWindow::showAboutDialog() {
	QDialog *aboutDialog = new QDialog(this);
	aboutDialog->setWindowTitle(tr("About lingualeo client"));
	QLabel *textLabel = new QLabel(tr("Desktop client for <a href='http://lingualeo.ru'>LinguaLeo</a> by Anton Samoylov <br/>") +
																 tr("You can contact me via email: <a href='mailto:toshaevil@gmail.com'>toshaevil@gmail.com</a><br/>") +
																 tr("Source code can be found at <a href='https://github.com/EvilTosha/lingualeo-client'>GitHub</a>"),
																 aboutDialog);
	textLabel->setOpenExternalLinks(true);
	QLabel *logoLabel = new QLabel(aboutDialog);
	logoLabel->setPixmap(QPixmap("resources/logo.jpg"));
	QGridLayout *layout = new QGridLayout(aboutDialog);
	layout->addWidget(logoLabel, 0, 0);
	layout->addWidget(textLabel, 0, 1);
	aboutDialog->setLayout(layout);
	aboutDialog->exec();
}

void MainWindow::showPreferancesDialog() {
	QDialog *preferancesDialog = new QDialog(this);
	preferancesDialog->setWindowTitle(tr("Preferances"));

	QGridLayout *layout = new QGridLayout(preferancesDialog);
	preferancesDialog->setLayout(layout);
	preferancesDialog->exec();
}

void MainWindow::keyReleaseEvent(QKeyEvent *event) {
	if (event->key() == Qt::Key_Enter || event->key() == Qt::Key_Return) {
		if (focusWidget() == mainLineEdit_) {
			QString word = mainLineEdit_->text();
			setCurWord(word);
			imageLabel_->hide();
			postTranslateLabel_->clear();
			translatesTreeWidget_->clear();
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
