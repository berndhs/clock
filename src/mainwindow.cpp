
#include <QDebug>
#include <QString>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "settingschange.h"
#include <QInputDialog>
#include <QIcon>
#include <QSize>
#include <QObject>
#include <math.h>
#include <iostream>
#include <unistd.h>


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
MainWindow::MainWindow(QApplication &app, QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow),
  m_app(&app),
  m_changer(Q_NULLPTR),
  m_lic(Q_NULLPTR),
  m_timeWin(Q_NULLPTR)
{
  qDebug() << Q_FUNC_INFO << __LINE__;
  ui->setupUi(this);
  ui->formatButton->setVisible(false);
  ui->quitButton->setVisible(false);
  changeFormat(false);
  qDebug() << Q_FUNC_INFO << __LINE__;
  sleep(2);
  m_curTime = QDateTime::currentDateTime().toString(m_dateFormat);
  qDebug() << Q_FUNC_INFO << __LINE__;
  ui->theTime->setText(m_curTime);
  ui->copyrightButton->setText("");
  ui->copyrightButton->setVisible(false);
  QSize s = ui->copyrightButton->size();
  qDebug() << Q_FUNC_INFO << __LINE__;
  ui->copyrightButton->setIcon(QIcon(":/rights.png"));
  ui->copyrightButton->setIconSize(s);
  updateTimer = new QTimer(this);
  m_changer =  new SettingsChange(this);
  qDebug() << Q_FUNC_INFO << __LINE__;
  m_lic = new LicenseWindow(this);
  qDebug() << Q_FUNC_INFO << __LINE__;
  connectUi();
  m_wantTimer = true;
  updateTimer->start(5000);
  QFontMetrics fm = fontMetrics();
  qDebug() << fm.width(m_curTime) << "x" << fm.height();
  installEventFilter(this);
  qDebug() << Q_FUNC_INFO << __LINE__;
  m_timeWin = new QQuickView ();
  m_timeWin->setWidth(300);
  m_timeWin->setHeight(167);
  m_timeWin->show();
  int timeX = x() + 300;
  int timeY = y() ;
  m_timeWin->setPosition(timeX,timeY);
  m_timeWin->setSource(QUrl("qrc:/TimeWin.qml"));
  qDebug() << Q_FUNC_INFO << __LINE__;
  qDebug() << Q_FUNC_INFO << " look for qml box";
  QObject * box = m_timeWin->findChild<QObject*>("TheBigBox");
  qDebug() << "\n\t box is at " << box;
  QObject * date = m_timeWin->findChild<QObject*>("TheDateText");
  qDebug() << "\n't date is at " << date;
}

MainWindow::~MainWindow()
{
  qDebug() << Q_FUNC_INFO;
  delete ui;
}

void
MainWindow::connectUi()
{
  qDebug() << Q_FUNC_INFO;
  connect (ui->quitButton,SIGNAL(released()),this,SLOT(quit()));
  connect (ui->formatButton,SIGNAL(released()),this,SLOT(changeFormat()));
  connect (updateTimer,SIGNAL(timeout()),this,SLOT(getNewTime()));
  connect (ui->copyrightButton,SIGNAL(released()),m_lic,SLOT(doShow()));
  connect (m_changer,SIGNAL(useMask(QString)),this,SLOT(setMask(QString)));
}

void
MainWindow::updateTime(QString time)
{
  ui->theTime->setText(time);
}

void
MainWindow::quit()
{
  qDebug() << Q_FUNC_INFO;
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
  qDebug() << Q_FUNC_INFO << updateTimer->isActive() << m_wantTimer;
  if (!m_wantTimer) {
    qDebug() << Q_FUNC_INFO << "what are we doing here?";
    return;
  }
  m_curTime = QDateTime::currentDateTime().toString(m_dateFormat);
  updateTime(m_curTime);
  updateTimer->start(5000);
}

void
MainWindow::setMask(QString msk)
{
  qDebug() << Q_FUNC_INFO << msk;
  m_dateFormat = msk;
}

bool
MainWindow::eventFilter(QObject *obj, QEvent *event)
{
  QEvent::Type evt = event->type();
  switch (evt) {
    case QEvent::HoverEnter:
      ui->quitButton->setVisible(true);
      ui->formatButton->setVisible(true);
      ui->copyrightButton->setVisible(true);
      return true;
      break;
    case QEvent::HoverLeave:
      ui->quitButton->setVisible(false);
      ui->formatButton->setVisible(false);
      ui->copyrightButton->setVisible(false);
      return true;
      break;
    case QEvent::Resize:
      this->resizeEvent(event);
      break;
    default:
      break;
  }
  return QObject::eventFilter(obj, event);
}

void MainWindow::resizeEvent(QEvent *evt)
{
  std::cout << Q_FUNC_INFO << std::endl;
  QResizeEvent *revt = static_cast<QResizeEvent*>(evt);
  QSize sz = revt->size();
  int hi = sz.height();
  int wd = sz.width();
  ui->theTime->setMinimumHeight(hi/2);
  ui->theTime->setMaximumHeight(hi/2);
  ui->theTime->setMinimumWidth(wd-4);
  ui->theTime->setMaximumWidth(wd-4);
  QFont fnt = ui->theTime->font();
  int px = (hi/4 > 2 ? hi/4 : 2);
  fnt.setPixelSize(px);
  ui->theTime->setFont(fnt);
}
