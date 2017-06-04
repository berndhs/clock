
#include <QDebug>
#include <QString>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "settingschange.h"
#include <QInputDialog>
#include <QIcon>
#include <iostream>


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
  m_changer(Q_NULLPTR)
{
  qDebug() << Q_FUNC_INFO;
  ui->setupUi(this);
  ui->formatButton->setVisible(false);
  ui->quitButton->setVisible(false);
  changeFormat(false);
  m_curTime = QDateTime::currentDateTime().toString(m_dateFormat);
  ui->theTime->setText(m_curTime);
  ui->copyrightButton->setText("");
  ui->copyrightButton->setVisible(false);
  ui->copyrightButton->setIcon(QIcon(":/rights.png"));
  updateTimer = new QTimer(this);
  m_changer =  new SettingsChange(this);
  connectUi();
  m_wantTimer = true;
  updateTimer->start(500);
  QFontMetrics fm = fontMetrics();
  qDebug() << fm.width(m_curTime) << "x" << fm.height();
  installEventFilter(this);
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
  QString defaultFormat("ddd yyyy-MM-dd HH:mm:ss t");
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
  updateTimer->start(500);
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
  std::cout << Q_FUNC_INFO << std::endl;
  std::cout << "seeing " << event << " for obj " << obj
           << " in obj " << this;
  return QObject::eventFilter(obj, event);
}

void MainWindow::resizeEvent(QEvent *evt)
{
  std::cout << Q_FUNC_INFO << std::endl;
  QResizeEvent *revt = static_cast<QResizeEvent*>(evt);
  QSize sz = revt->size();
  int hi = sz.height();
  int wd = sz.width();
  ui->theTime->size().setWidth(wd-4);
  std::cout << "\t" << hi  << "x" << wd << std::endl;
  QFont fnt = ui->theTime->font();
  fnt.setPixelSize(hi/2);
  ui->theTime->setFont(fnt);
}
