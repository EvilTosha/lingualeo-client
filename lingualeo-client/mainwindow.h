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

#include "translater.h"

class MainWindow : public QMainWindow {
  Q_OBJECT
  
public:
  MainWindow(QWidget *parent = 0);
  ~MainWindow();

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
	void login();
	void tryLogin();

	void parseTranslates(QString word, QVariant data);
	void viewTranslates(QStringList &translates, QStringList &votes);
	void adjustInnerWidgets();
	void updateStatus(QString msg, MessageType type = NoType);

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
};

#endif // MAINWINDOW_H
