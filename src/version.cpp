#include "version.h"
#include "deliberate.h"
#include <QMessageBox>
#include <QTimer>
#include <QCoreApplication>

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

namespace deliberate {

  QString ProgramVersion::VersionNumber ("0.1.0");

  QString ProgramVersion::ProgramName("Clock");
  QString ProgramVersion::copyright ("Copyright (C) 2017 Bernd Stramm");
  
  ProgramVersion::ProgramVersion (QString pgmname)
  {
    ProgramName = pgmname;
  }
  
  QString ProgramVersion::Version ()
  { 
    return ProgramName + QString (" Version " )
                   + VersionNumber + " " + QString(__DATE__) + " "
		       + QString(__TIME__)
		       + QString("\r\n")
		       + copyright;
  }

  void ProgramVersion::ShowVersionWindow ()
  {
    QString versionMessage(Version());
    QMessageBox box;
    box.setText (versionMessage);
    QTimer::singleShot(30000,&box,SLOT(accept()));
    box.exec();
  }
  
  void ProgramVersion::CLIVersion ()
  {
    myStdOut() << Version() << endl;
  }
  
  QString ProgramVersion::MyName()
  { 
    return ProgramName;
  }

}
