/***************************************************************************
 *                                                                         *
 *   Copyright (C) 2009 Fco. Javier M. C. <fcojavmc@todo-redes.com>        *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/

#include <unistd.h>

#include <QtGui>

#include "bulmalauncher.h"


BulmaLauncher::BulmaLauncher()
{
    setWindowTitle("BulmaLauncher");

    createTrayIcon();
    trayIcon->setIcon(QIcon(":/images/iconbulmafact.png"));
    trayIcon->show();
}


BulmaLauncher::~BulmaLauncher()
{
}


void BulmaLauncher::createTrayIcon()
{
    QAction *bulmaContAction;
    QAction *bulmaFactAction;
    QAction *bulmaTPVAction;
    QAction *bulmaSetupAction;
    QAction *salirAction;

    bulmaContAction = new QAction(tr("BulmaCont"), this);
    bulmaFactAction = new QAction(tr("BulmaFact"), this);
    bulmaTPVAction = new QAction(tr("BulmaTPV"), this);
    bulmaSetupAction = new QAction(tr("BulmaSetup"), this);
    salirAction = new QAction(tr("&Salir"), this);

    connect(bulmaContAction, SIGNAL(triggered()), this , SLOT(launchBulmaCont()));
    connect(bulmaFactAction, SIGNAL(triggered()), this , SLOT(launchBulmaFact()));
    connect(bulmaTPVAction, SIGNAL(triggered()), this , SLOT(launchBulmaTPV()));
    connect(bulmaSetupAction, SIGNAL(triggered()), this , SLOT(launchBulmaSetup()));
    connect(salirAction, SIGNAL(triggered()), qApp , SLOT(quit()));

    trayIconMenu = new QMenu(this);
    trayIconMenu->addAction(bulmaContAction);
    trayIconMenu->addAction(bulmaFactAction);
    trayIconMenu->addAction(bulmaTPVAction);
    trayIconMenu->addAction(bulmaSetupAction);
    trayIconMenu->addSeparator();
    trayIconMenu->addAction(salirAction);

    trayIcon = new QSystemTrayIcon(this);
    trayIcon->setContextMenu(trayIconMenu);
}


void BulmaLauncher::launchBulmaCont()
{
    runCommand("bulmacont");
}


void BulmaLauncher::launchBulmaFact()
{
    runCommand("bulmafact");
}


void BulmaLauncher::launchBulmaTPV()
{
    runCommand("bulmatpv");
}


void BulmaLauncher::launchBulmaSetup()
{
    runCommand("bulmasetup");
}


void BulmaLauncher::runCommand(QString command)
{
    pid_t pid = fork();
    if ( pid == 0 ) {
        // In the child, do exec  
	execvp(command.toAscii(), NULL);
    } // end if
}
