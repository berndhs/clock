#include "mainwindow.h"
#include <QApplication>
#include <QSettings>
#include "agpl2.h"
#include "version.h"
#include "deliberate.h"
#include "cmdoptions.h"


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
int main(int argc, char *argv[])
{

  QApplication a (argc, argv);
  QApplication::setOrganizationName ("BerndStramm");
  QApplication::setOrganizationDomain ("berndhs.world");
  QApplication::setApplicationName ("clock");
  deliberate::ProgramVersion pv ("Clock");
  QApplication::setApplicationVersion (pv.Version());
  QSettings  settings;
  deliberate::InitSettings ();
  deliberate::SetSettings (settings);
  settings.setValue ("program",pv.MyName());


  QStringList  configMessages;

  deliberate::CmdOptions  opts ("denada");
  opts.AddSoloOption ("debug","D",QObject::tr("show Debug log window"));
  opts.AddStringOption ("logdebug","L",QObject::tr("write Debug log to file"));

  MainWindow w(a);
  w.show();
  bool optsOk = opts.Parse (argc, argv);
  if (!optsOk) {
    opts.Usage ();
    exit(1);
  }
  if (opts.WantHelp ()) {
    opts.Usage ();
    exit (0);
    pv.CLIVersion ();
    configMessages.append (QString("Built on %1 %2")
                           .arg (__DATE__).arg(__TIME__));
    configMessages.append (QObject::tr("Build with Qt %1").arg(QT_VERSION_STR));
    configMessages.append (QObject::tr("Running with Qt %1").arg(qVersion()));
    for (int cm=0; cm<configMessages.size(); cm++) {
      deliberate::myStdOut () << configMessages[cm] << endl;
    }
    if (opts.WantVersion ()) {
      exit (0);
    }
  }
  bool showDebug = opts.SeenOpt ("debug");
  int result;


  result = a.exec();
  return result;
}
