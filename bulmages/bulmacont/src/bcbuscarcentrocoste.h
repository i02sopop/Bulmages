/***************************************************************************
 *   Copyright (C) 2004 by Tomeu Borras Riera                              *
 *   tborras@conetxia.com                                                  *
 *   http://www.iglues.org Asociación Iglues -- Contabilidad Linux         *
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

#ifndef BCBUSCARCENTROCOSTE_H
#define BCBUSCARCENTROCOSTE_H

#include "blcombobox.h"
#include "blpostgresqlclient.h"
#include "blwidget.h"


class BcCompany;


class BC_EXPORT BcBuscarCentroCosteDelegate : public BlComboBox
{
    Q_OBJECT

private:
    /// Este cursor almacena el listado de series de factura para poder trabajar con ellas.
    BlDbRecordSet *m_cursorcombo;
    QCompleter *completar;

public:
    BcBuscarCentroCosteDelegate ( QWidget *parent = 0 );
    ~BcBuscarCentroCosteDelegate();
    virtual void set ( const QString & );
};


class BC_EXPORT BcBuscarCentroCoste : public BlComboBox
{
    Q_OBJECT

private:
    BlDbRecordSet *m_cursorcombo;

public:
    BcBuscarCentroCoste ( QWidget *parent = 0, const char *name = 0 );
    ~BcBuscarCentroCoste();
    virtual void setidc_coste ( QString idc_coste );
    virtual void setFieldValue ( QString idc_coste );
    QString idc_coste();
    virtual QString fieldValue();

public slots:
    void m_activated ( int index );

signals:
    void valueChanged ( QString );
};

#endif