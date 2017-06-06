
#include <QDebug>
#include <QString>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "settingschange.h"
#include <QInputDialog>
#include <QIcon>
#include <QSize>
#include <QObject>
#include <QQuickItem>
#include <math.h>
#include <iostream>
#include <unistd.h>
#include "deliberate.h"


/****************************************************************
 * This file is distributed under the following license:
 *
 * Copyright (C) 2017, Bernd Stramm

This is free software: you can redistribute it and/or modify
it under the terms of the GNU Affero General Public License as
published by the Free Software Foundation, either version 3 of the
License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Affero General Public License for more details.

You should have received a copy of the GNU Affero General Public License
along with this program. If not, see <http://www.gnu.org/licenses/>.

 ****************************************************************/

using namespace deliberate;

MainWindow::MainWindow(QApplication &app, QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow),
  m_app(&app),
  m_changer(Q_NULLPTR),
  m_lic(Q_NULLPTR),
  m_timeWin(Q_NULLPTR)
{
  ui->setupUi(this);
  ui->formatButton->setVisible(false);
  ui->quitButton->setVisible(false);
  m_curTime = QDateTime::currentDateTime().toString(m_dateFormat);
  ui->theTime->setText(m_curTime);
  ui->copyrightButton->setText("");
  ui->copyrightButton->setVisible(false);
  QSize s = ui->copyrightButton->size();
  ui->copyrightButton->setIcon(QIcon(":/rights.png"));
  ui->copyrightButton->setIconSize(s);
  updateTimer = new QTimer(this);
  m_changer =  new SettingsChange(this);
  m_lic = new LicenseWindow(this);
  m_wantTimer = true;
  updateTimer->start(333);
  QFontMetrics fm = fontMetrics();
  qDebug() << fm.width(m_curTime) << "x" << fm.height();
  m_timeWin = new QQuickView ();
  QSize defSize(300,167);
  QSize sz = Settings().value("size",QVariant(defSize)).toSize();

  m_pixelSize = Settings().value("pix",QVariant(8.0)).toDouble();
  setPixels();
  qDebug() << " initial size" << sz;
  m_timeWin->setBaseSize(sz);
  m_timeWin->show();
  m_timeWin->setSource(QUrl("qrc:/TimeWin.qml"));
  qDebug() << Q_FUNC_INFO << __LINE__;
  qDebug() << Q_FUNC_INFO << " look for qml box";
  m_timeBigBox = m_timeWin->rootObject();
  m_timeWin->setResizeMode(QQuickView::SizeRootObjectToView);
  connectUi(m_timeBigBox);
  changeFormat(false);
  QTimer::singleShot(3000,this,SLOT(hideMain()));
}

MainWindow::~MainWindow()
{
  qDebug() << Q_FUNC_INFO;
  delete ui;
}

void
MainWindow::connectUi(QQuickItem *root)
{
  qDebug() << Q_FUNC_INFO;
  if (root) {
    connect (root,SIGNAL(quit()),
             this,SLOT(quit()));
    connect (root,SIGNAL(changeFormat()),
             this, SLOT(changeFormat()));
    connect (root,SIGNAL(showCopyright()),
             m_lic,SLOT(doShow()));
    connect (root,SIGNAL(sizeUp()),
             this, SLOT(fontSizeUp()));
    connect (root,SIGNAL(sizeDown()),
             this,SLOT(fontSizeDown()));
  } else {
    connect (ui->quitButton,SIGNAL(released()),this,SLOT(quit()));
    connect (ui->formatButton,SIGNAL(released()),this,SLOT(changeFormat()));
    connect (ui->copyrightButton,SIGNAL(released()),m_lic,SLOT(doShow()));
  }
  connect (updateTimer,SIGNAL(timeout()),this,SLOT(getNewTime()));
  connect (m_changer,SIGNAL(useMask(QString)),this,SLOT(setMask(QString)));
}

void
MainWindow::updateTime(QString time)
{
  if (m_timeBigBox) {
    m_timeBigBox->setProperty("timeValue",time);
  } else {
    ui->theTime->setText(time);
  }
}

void MainWindow::hideMain()
{
  hide();
}

void
MainWindow::quit()
{
  qDebug() << Q_FUNC_INFO;
  if (m_timeWin) {
    QSize lastSize = m_timeWin->size();
    Settings().setValue("size",lastSize);
    Settings().setValue("pix",m_pixelSize);
  }
  if (m_app) {
    m_app->quit();
  }
}

void
MainWindow::changeFormat(bool doAsk)
{
  qDebug() << Q_FUNC_INFO << doAsk;
  QString defaultFormat("on ddd\nyyyy-MM-dd\nHH:mm:ss t");
  int changeMask (0);
  QString newMask;
  if (doAsk) {
    updateTimer->stop();
    m_wantTimer = false;
    qDebug() << Q_FUNC_INFO << __LINE__ << updateTimer->isActive();
    m_changer->setWindowTitle(tr("Change Settings"));
    m_changer->setModal(true);
    m_changer->setOldMask(m_dateFormat);
    m_changer->setDefault(defaultFormat);
    changeMask = m_changer->exec();
//    newMask = QInputDialog::getText(this,QString("Change Timer Mask"),m_dateFormat);
    qDebug() << "changeMask is " << changeMask;
    if (changeMask != SettingsChange::DontChange) {
      newMask = m_changer->newMask();
    }
    updateTimer->start();
    m_wantTimer = true;
  }
  m_dateFormat=QString(defaultFormat);
  //  if (changeMask != SettingsChange::DontChange) {
  if (!newMask.isEmpty()) {
    m_dateFormat = newMask;
  }
  ;
}

void
MainWindow::getNewTime()
{
  if (!m_wantTimer) {
    qDebug() << Q_FUNC_INFO << "what are we doing here?";
    return;
  }
  m_curTime = QDateTime::currentDateTime().toString(m_dateFormat);
  updateTime(m_curTime);
  updateTimer->start(333);
}

void MainWindow::fontSizeUp()
{
  m_pixelSize += 1.0;
  setPixels();
}

void MainWindow::fontSizeDown()
{
  m_pixelSize -= 1.0;
  setPixels();
}

void
MainWindow::setMask(QString msk)
{
  qDebug() << Q_FUNC_INFO << msk;
  m_dateFormat = msk;
}

void MainWindow::setPixels()
{
  if (m_timeBigBox) {
    m_timeBigBox->setProperty("pixelSize",m_pixelSize);
  }
  Settings().setValue("pix",m_pixelSize);
}
