/***************************************************************************
 *   Copyright (C) 2008 by Tomeu Borras Riera                              *
 *   tborras@conetxia.com                                                  *
 *   http://www.iglues.org                                                 *
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

#ifndef IMPORTCSV_H
#define IMPORTCSV_H


#include <QLineEdit>
#include <QLabel>
#include <QCheckBox>
#include <QWidget>
#include <QMap>

#include "ui_importcsvbase.h"
#include "postgresiface2.h"
#include "blwidget.h"


class EmpresaBase;




/** Ventana de ficha de cobro.
    Se encarga de la presentacion de la ficha de cobro y del tratamiento de eventos producidos
    en dicha ventana.
    Deriva de Ficha para metodos comunes a todas las ventanas.
    Deriva de Cobro para el manejo de la Base de datos. */


class ImportCSV : public BLWidget, public Ui_ImportCSVBase
{
    Q_OBJECT
private:
    QList<QString> m_claves;
public:
    ImportCSV ( EmpresaBase *, QWidget * );
    ~ImportCSV();
    void rellenarTablas();
    void procesarLinea ( const QString &linea );
public slots:
    void on_mui_aceptar_clicked();
    void on_mui_combotablas_activated ( const QString & text );
    void on_mui_buscarArchivo_clicked();
    void on_mui_cabeceras_stateChanged ( int state );
};


#endif
