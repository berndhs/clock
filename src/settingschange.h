#ifndef SETTINGSCHANGE_H
#define SETTINGSCHANGE_H


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
#include <QDialog>
#include <QString>

namespace Ui {
  class SettingsChange;
}

class SettingsChange : public QDialog
{
  Q_OBJECT

public:

  enum Result {
    DontChange = 0,
    UseDefault= 1,
    UseNew = 2,
    SetInitial
  };

  explicit SettingsChange(QWidget *parent = 0);
  void setDefault (QString &dFault);
  void setOldMask (QString &mask);
  ~SettingsChange();

  QString newMask() { return m_newMask; }

public slots:

  int exec();

  void useDefault();
  void okClicked();
  void cancelClicked();

signals:

  void useMask (QString newMask);

private:
  Ui::SettingsChange *ui;

  QString m_defaultMask;
  QString m_oldMask;
  QString m_newMask;
  int     m_resultWanted;
};

#endif // SETTINGSCHANGE_H
