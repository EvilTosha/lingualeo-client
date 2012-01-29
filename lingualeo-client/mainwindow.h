#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui/QMainWindow>
#include <QLineEdit>
#include <QGridLayout>
#include <QDialog>
#include <QLabel>

#include "translater.h"

class MainWindow : public QMainWindow{
  Q_OBJECT
  
public:
  MainWindow(QWidget *parent = 0);
  ~MainWindow();

public slots:
	void login();
	void tryLogin();
	void loginFail(QString errorMsg = "");
	void loginSuccess();

private:
	Translater *translater_;
	QDialog *loginDialog_;
	QLineEdit *emailLineEdit_, *passwordLineEdit_;
	QLabel *loginStatusLabel_;

};

#endif // MAINWINDOW_H
