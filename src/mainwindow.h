#ifndef MAINWINDOW_H
#define MAINWINDOW_H


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
#include <QString>
#include <QMainWindow>
#include <QDateTime>
#include <QFontMetrics>
#include <QTimer>
#include <QEvent>
#include <QResizeEvent>
#include "settingschange.h"

namespace Ui {
  class MainWindow;
}

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  explicit MainWindow(QApplication &app, QWidget *parent = 0);
  ~MainWindow();

  void connectUi();
  void updateTime(QString time);

public slots:

  void quit();
  void changeFormat(bool doAsk=true);
  void getNewTime();

  void setMask (QString msk);

protected:

  bool eventFilter(QObject *obj, QEvent *event);

  void resizeEvent(QEvent * evt);


private:
  Ui::MainWindow *ui;

  QApplication *m_app;

  QString   m_dateFormat;
  QString   m_curTime;

  QTimer    *updateTimer;
  bool      m_wantTimer;

  SettingsChange *m_changer;
};

#endif // MAINWINDOW_H
