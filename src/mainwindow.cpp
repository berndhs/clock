#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QApplication &app, QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow),
  m_app(&app)
{
  qDebug() << Q_FUNC_INFO;
  ui->setupUi(this);
  ui->theTime->setText(QDateTime::currentDateTime().toString(Qt::ISODate));
  connectUi();
}

MainWindow::~MainWindow()
{
  qDebug() << Q_FUNC_INFO;
  delete ui;
}

void MainWindow::connectUi()
{
  qDebug() << Q_FUNC_INFO;
  connect (ui->quitButton,SIGNAL(released()),this,SLOT(quit()));
}

void MainWindow::quit()
{
  qDebug() << Q_FUNC_INFO;
  if (m_app) {
    m_app->quit();
  }
}
