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
	/* Login functions */
	void login();
	void tryLogin();

private:
	/* General */
	Translater *translater_;

	/* Login dialog GUI */
	QDialog *loginDialog_;
	QLineEdit *emailLineEdit_, *passwordLineEdit_;
	QLabel *loginStatusLabel_;

	/* MainWindow GUI */
	QLineEdit *mainLineEdit_;

};

#endif // MAINWINDOW_H
