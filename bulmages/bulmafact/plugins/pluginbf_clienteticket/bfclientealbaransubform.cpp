/***************************************************************************
 *   Copyright (C) 2005 by Tomeu Borras Riera                              *
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

#include <QMessageBox>
#include <QKeyEvent>
#include <QEvent>

#include "bfclientealbaransubform.h"
#include "blfunctions.h"
#include "blfixed.h"
#include "blplugins.h"


///
/**
\param parent
**/
BfClienteTicketSubForm::BfClienteTicketSubForm ( QWidget *parent )
        : BfSubForm ( parent )
{
    blDebug ( "BfClienteTicketSubForm::BfClienteTicketSubForm", 0 );
    setDbTableName ( "lalbaran" );
    setDbFieldId ( "numlalbaran" );
    /// Disparamos los plugins.
    int res = g_plugins->lanza ( "BfClienteTicketSubForm_BfClienteTicketSubForm", this );
    if ( res != 0 )
        return;
    addSubFormHeader ( "idarticulo", BlDbField::DbInt, BlDbField::DbNotNull, BlSubFormHeader::DbHideView, _ ( "Id articulo" ) );
    addSubFormHeader ( "codigocompletoarticulo", BlDbField::DbVarChar, BlDbField::DbNoSave, BlSubFormHeader::DbNone, _ ( "Codigo completo articulo" ) );
    addSubFormHeader ( "nomarticulo", BlDbField::DbVarChar, BlDbField::DbNoSave, BlSubFormHeader::DbNoWrite, _ ( "Nombre articulo" ) );
    addSubFormHeader ( "numlalbaran", BlDbField::DbInt, BlDbField::DbPrimaryKey, BlSubFormHeader::DbHideView, _ ( "Nº linea" ) );
    addSubFormHeader ( "desclalbaran", BlDbField::DbVarChar, BlDbField::DbNotNull, BlSubFormHeader::DbNone, _ ( "Descripcion" ) );
    addSubFormHeader ( "cantlalbaran", BlDbField::DbNumeric, BlDbField::DbNotNull, BlSubFormHeader::DbNone, _ ( "Cantidad" ) );
//    addSubFormHeader ( "pvplalbaran", BlDbField::DbNumeric, BlDbField::DbNotNull, BlSubFormHeader::DbNone, _ ( "P.V.P." ) );
    addSubFormHeader ( "pvpivainclalbaran", BlDbField::DbNumeric, BlDbField::DbNotNull, BlSubFormHeader::DbNone, _ ( "P.V.P." ) );
    addSubFormHeader ( "totallalbaran", BlDbField::DbNumeric, BlDbField::DbNoSave, BlSubFormHeader::DbNoWrite, _ ( "Total Linea" ) );
    addSubFormHeader ( "ivalalbaran", BlDbField::DbNumeric, BlDbField::DbNotNull, BlSubFormHeader::DbNone, _ ( "I.V.A." ) );
    addSubFormHeader ( "reqeqlalbaran", BlDbField::DbNumeric, BlDbField::DbNothing, BlSubFormHeader::DbNone, _ ( "% Recargo E.Q." ) );
    addSubFormHeader ( "descuentolalbaran", BlDbField::DbNumeric, BlDbField::DbNotNull, BlSubFormHeader::DbNone, _ ( "% Descuento" ) );
    addSubFormHeader ( "idalbaran", BlDbField::DbInt, BlDbField::DbNotNull, BlSubFormHeader::DbHideView | BlSubFormHeader::DbNoWrite, _ ( "Id albaran" ) );
    addSubFormHeader ( "ordenlalbaran", BlDbField::DbInt, BlDbField::DbNotNull, BlSubFormHeader::DbHideView, _ ( "Orden" ) );
    setInsert ( TRUE );
    setOrdenEnabled ( TRUE );
    /// Disparamos los plugins.
    g_plugins->lanza ( "BfClienteTicketSubForm_BfClienteTicketSubForm_Post", this );
    blDebug ( "END BfClienteTicketSubForm::BfClienteTicketSubForm", 0 );

}


///
/**
\param idalbaran
**/
void BfClienteTicketSubForm::cargar ( QString idalbaran )
{
    blDebug ( "BfClienteTicketSubForm::cargar", 0 );
    mdb_idalbaran = idalbaran;
    /// Disparamos los plugins.
    int res = g_plugins->lanza ( "BfClienteTicketSubForm_cargar", this );
    if ( res != 0 )
        return;

    BlSubForm::cargar ( "SELECT *, (cantlalbaran * pvpivainclalbaran)::NUMERIC(12,2) AS totallalbaran FROM lalbaran LEFT JOIN articulo ON lalbaran.idarticulo = articulo.idarticulo WHERE idalbaran=" + mdb_idalbaran + "   ORDER BY ordenlalbaran" );
    blDebug ( "END BfClienteTicketSubForm::cargar", 0 );
}

