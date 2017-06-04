#include "src/settingschange.h"
#include "ui_settingschange.h"
#include <QDebug>


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

SettingsChange::SettingsChange(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::SettingsChange)
{
  ui->setupUi(this);
//  setVisible(false);
  connect (ui->okButton,SIGNAL(released()),
           this,SLOT(okClicked()));
  connect (ui->cancelButton,SIGNAL(released()),
           this,SLOT(cancelClicked()));
  connect (ui->defaultButton,SIGNAL(released()),
           this,SLOT(cancelClicked()));
}

void
SettingsChange::setOldMask(QString &mask)
{
  m_oldMask = mask;
  ui->currentMask->setText(mask);
}

void
SettingsChange::setDefault(QString &dFault)
{
  m_defaultMask = dFault;
  ui->defaultMask->setText(m_defaultMask);
}

SettingsChange::~SettingsChange()
{
  delete ui;
}

int
SettingsChange::exec()
{
  setModal(true);
  setVisible(true);
  m_resultWanted = DontChange;
  show();
  return m_resultWanted;
}

void
SettingsChange::useDefault()
{
  m_resultWanted = UseDefault;
  m_newMask = m_defaultMask;
  qDebug() << Q_FUNC_INFO << "new mask" << m_newMask;
  done(m_resultWanted);
  emit finished (m_resultWanted);
  emit useMask(m_newMask);
  qDebug() << Q_FUNC_INFO << " they want " << m_resultWanted << m_newMask;
}

void
SettingsChange::okClicked()
{
  m_resultWanted = UseNew;
  m_newMask = ui->newMaskEdit->toPlainText();
  qDebug() << Q_FUNC_INFO << "new mask" << m_newMask;
  done(m_resultWanted);
  emit finished (m_resultWanted);
  emit useMask(m_newMask);
  qDebug() << Q_FUNC_INFO << " they want " << m_resultWanted << m_newMask;
}

void
SettingsChange::cancelClicked()
{
  m_resultWanted = DontChange;
  m_newMask = "";
  qDebug() << Q_FUNC_INFO << "new mask" << m_newMask;
  done(m_resultWanted);
  emit finished (m_resultWanted);
  qDebug() << Q_FUNC_INFO << " they want " << m_resultWanted << m_newMask;
}
