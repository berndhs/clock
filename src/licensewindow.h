#ifndef LICENSEWINDOW_H
#define LICENSEWINDOW_H


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
#include "ui_licensewindow.h"

namespace Ui {
  class LicenseWindow;
}

class LicenseWindow : public QDialog
{
  Q_OBJECT

public:
  explicit LicenseWindow(QWidget *parent = 0);
  ~LicenseWindow();

public slots:

  void doShow ();
  void quit();

private:
  Ui::LicenseWindow *ui;
};

#endif // LICENSEWINDOW_H
