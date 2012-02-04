#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui/QMainWindow>
#include <QLineEdit>
#include <QGridLayout>
#include <QDialog>
#include <QLabel>
#include <QListView>
#include <QKeyEvent>

#include "translater.h"

class MainWindow : public QMainWindow {
  Q_OBJECT
  
public:
  MainWindow(QWidget *parent = 0);
  ~MainWindow();

public slots:
	/* Login functions */
	void login();
	void tryLogin();

	void parseTranslates(QString word, QVariant data);
	void viewTranslates(QStringList &translates);
	void keyReleaseEvent(QKeyEvent *event);

private:
	/* General */
	Translater *translater_;
	QMap<QString, QVariant> options_;

	/* Login dialog GUI */
	QDialog *loginDialog_;
	QLineEdit *emailLineEdit_, *passwordLineEdit_;
	QLabel *loginStatusLabel_;

	/* MainWindow GUI */
	QLineEdit *mainLineEdit_;
	QListView *translatesListView_;
};

#endif // MAINWINDOW_H
