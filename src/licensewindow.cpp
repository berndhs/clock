#include "licensewindow.h"
#include <QDebug>
#include <QString>
#include <QFile>
#include <QByteArray>

LicenseWindow::LicenseWindow(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::LicenseWindow)
{
  qDebug() << Q_FUNC_INFO;
  ui->setupUi(this);
  connect (ui->closeButton,SIGNAL(released()),this,SLOT(quit()));
}

LicenseWindow::~LicenseWindow()
{
  qDebug() << Q_FUNC_INFO;
}

void LicenseWindow::doShow()
{
  QFile fl(":/lic.txt");
  bool ok = fl.open(QFile::ReadOnly);
  if (!ok) {
    abort();
  }
  QByteArray data = fl.readAll();
  ui->licenseText->setText(QString(data));
  show();
}

void LicenseWindow::quit()
{
  hide();
}
