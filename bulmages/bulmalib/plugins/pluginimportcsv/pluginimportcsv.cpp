/***************************************************************************
 *   Copyright (C) 2008 by Tomeu Borras Riera                              *
 *   tborras@conetxia.com                                                  *
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


#include <QAction>
#include <QMessageBox>
#include <QStringList>
#include <QWidget>
#include <QIcon>
#include <QApplication>
#include <QObject>
#include <QProcess>

#include "pluginimportcsv.h"
#include "mypluginimportcsv.h"

#include "funcaux.h"
#include "bulmafact.h"
#include "bulmacont.h"



QMainWindow *g_bges_importcsv = NULL;
EmpresaBase *g_emp_importcsv = NULL;




void entryPoint ( QMainWindow *bges )
{
    _depura ( "Entrada del plugin ImportCSV", 0 );


    g_bges_importcsv = bges;

    mypluginimportcsv *mcont = new mypluginimportcsv;

    /// Creamos el men&uacute;.
    QAction *accion = new QAction ( "&Importacion CSV", 0 );
    accion->setStatusTip ( "Importacion CSV" );
    accion->setWhatsThis ( "Importacion CSV" );

    mcont->connect ( accion, SIGNAL ( activated() ), mcont, SLOT ( elslot() ) );

    QMenu *pPluginMenu = NULL;
    /// Miramos si existe un menu Herramientas
    pPluginMenu = bges->menuBar() ->findChild<QMenu *> ( "Herramientas" );
    /// En BulmaCont el menu de Herramientas tiene otro nombre.
    if ( !pPluginMenu ) {
        pPluginMenu = bges->menuBar() ->findChild<QMenu *> ( "menuHerramientas" );
    } // end if

    /// Creamos el men&uacute;.
    if ( !pPluginMenu ) {
        pPluginMenu = new QMenu ( "&Herramientas", bges->menuBar() );
        pPluginMenu->setObjectName ( QString::fromUtf8 ( "Herramientas" ) );
    } // end if

    pPluginMenu->addSeparator();
    pPluginMenu->addAction ( accion );

    /// A&ntilde;adimos la nueva opci&oacute;n al men&uacute; principal del programa.
    bges->menuBar() ->insertMenu ( 0, pPluginMenu );


    _depura ( "Iniciado correctamente el plugin imoprtcsv", 10 );
}




int Company_createMainWindows_Post ( Company *cmp )
{
    g_emp_importcsv = cmp;
    return 0;
}

int Empresa_createMainWindows_Post ( Empresa *cmp )
{
    g_emp_importcsv = cmp;
    return 0;
}


