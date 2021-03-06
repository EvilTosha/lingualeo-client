#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui/QMainWindow>
#include <QLineEdit>
#include <QGridLayout>
#include <QDialog>
#include <QLabel>
#include <QListView>
#include <QKeyEvent>
#include <QTreeWidget>
#include <QTimer>
#include <QMenu>
#include <QMenuBar>

#include "translater.h"

#define TRANSLATE_PLACEHOLDER_TEXT tr("Enter your translate")

class MainWindow : public QMainWindow {
  Q_OBJECT
  
public:
  MainWindow(QWidget *parent = 0);
  ~MainWindow();

	/* Types of messages for status bar */
	enum MessageType {
		NoType,
		Notification,
		Warning,
		Error
	};

	/* Getters */
	QString curWord() const;

public slots:
	/* Login functions */
	void showLoginDialog();
	void tryLogin();

	void showAboutDialog();
	void showPreferancesDialog();

	void parseTranslates(QString word, QVariant data);
	void viewTranslates(QStringList &translates, QStringList &votes, bool known = false);
	void viewImage(QString word, QPixmap *image);
	void adjustInnerWidgets();
	void updateStatus(QString msg, MessageType type = NoType);
	void wordAdded(QString translate);

	void keyReleaseEvent(QKeyEvent *event);
	void resizeEvent(QResizeEvent *event);

	/* Setters */
	void setCurWord(const QString word);

private:
	/* General */
	Translater *translater_;
	QMap<QString, QVariant> options_;
	QString curWord_;

	/* Login dialog GUI */
	QDialog *loginDialog_;
	QLineEdit *emailLineEdit_, *passwordLineEdit_;
	QLabel *loginStatusLabel_;

	/* MainWindow GUI */
	QLineEdit *mainLineEdit_;
	QTreeWidget *translatesTreeWidget_;
	QLabel *postTranslateLabel_;
	QLabel *imageLabel_;
	const QColor knownTranslateColor_;
};

#endif // MAINWINDOW_H
