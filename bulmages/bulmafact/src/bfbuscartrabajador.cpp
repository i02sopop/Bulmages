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

#include "blcombobox.h"

#include "bfbuscartrabajador.h"
#include "bfcompany.h"


/** Inicializa todos los componentes a NULL para que no haya confusiones sobre
    si un elemento ha sido inicializado o no.
    Hace la conexion del SIGNAL activated con m_activated para tratar el evento.
*/
/**
\param parent
**/
BfBuscarTrabajador::BfBuscarTrabajador ( QWidget *parent )
        : BlComboBox ( parent )
{
    _depura ( "BfBuscarTrabajador::BfBuscarTrabajador", 0 );

    m_comboRecordSet = NULL;
    m_table = "trabajador";
    m_null = TRUE;

    _depura ( "END BfBuscarTrabajador::BfBuscarTrabajador", 0 );
}


/** Libera la memoria dinamica que se estaba utilizando.
*/
/**
**/
BfBuscarTrabajador::~BfBuscarTrabajador()
{
    _depura ( "BfBuscarTrabajador::~BfBuscarTrabajador", 0 );
    _depura ( "END BfBuscarTrabajador::~BfBuscarTrabajador", 0 );
}


/** Con este metodo se puede indicar al Widget cual es el trabajador seleccionado.
    Recarga el cursor de trabajadores y cuando encuentra uno con el mismo identificador
    que el que se ha pasado por parametro lo establece como elemento seleccionado.
*/
/**
\param idtrabajador
\return
**/
void BfBuscarTrabajador::setId ( QString idtrabajador )
{
    _depura ( "BfBuscarTrabajador::setidtrabajador", 0 );

    /// Si lo que se pasa como forma de pago es un valor malo cogemos la forma de pago por defecto.
    if ( idtrabajador.isEmpty() || idtrabajador == "0" ) {
        idtrabajador = g_confpr->valor ( CONF_IDTRABAJADOR_DEFECTO );
    } // end if

    if ( m_comboRecordSet != NULL ) {
        delete m_comboRecordSet;
    } // end if

    m_comboRecordSet = mainCompany() ->loadQuery ( "SELECT * FROM trabajador" );
    if ( !m_comboRecordSet ) return;
    int i = 0;
    int i1 = 0;
    clear();
    addItem ( "--" );

    while ( !m_comboRecordSet->eof() ) {
        i ++;

        if ( m_comboRecordSet->valor ( "idtrabajador" ) == idtrabajador ) {
            i1 = i;
        } // end if

        addItem ( m_comboRecordSet->valor ( "apellidostrabajador" ) + ", " + m_comboRecordSet->valor ( "nomtrabajador" ) );
        m_comboRecordSet->nextRecord();
    } // end while

    setCurrentIndex ( i1 );

    _depura ( "END BfBuscarTrabajador::setidtrabajador", 0 );
}



/** Devuelve el identificador del trabajador seleccionado
**/
/**
\return
**/
QString BfBuscarTrabajador::id()
{
    _depura ( "BfBuscarTrabajador::idtrabajador", 0 );
    _depura ( "END BfBuscarTrabajador::idtrabajador", 0 );

    if ( !m_comboRecordSet ) {
        return "0";
    } // end if

    return m_comboRecordSet->valor ( "idtrabajador", currentIndex() - 1 );
}




/** SLOT que responde a la activacion de un elemento en el QComboBox y que hace que se emita el SIGNAL valueChanged
**/
/**
\param index
**/
void BfBuscarTrabajador::m_activated ( int index )
{
    _depura ( "BfBuscarTrabajador::m_activated", 0 );

    if ( index > 0 ) {
        emit ( valueChanged ( m_comboRecordSet->valor ( "idtrabajador", index - 1 ) ) );
    } else {
        emit ( valueChanged ( "" ) );
    } // end if

    _depura ( "END BfBuscarTrabajador::m_activated", 0 );
}

/// ========================= ITEM DELEGATE ===============================0

/** Inicializa todos los componentes del Widget a NULL para que no haya posibles confusiones
    sobre si un elemento ha sido creado o no.
    Conecta el SIGNAL activated() con m_activated() para tratarlo.
*/
/**
\param parent
**/
BfBuscarTrabajadorDelegate::BfBuscarTrabajadorDelegate ( QWidget *parent )
        : BlComboBox ( parent )
{
    _depura ( "BfBuscarTrabajadorDelegate::BfBuscarTrabajadorDelegate", 0 );

    m_comboRecordSet = NULL;
    setSizeAdjustPolicy ( QComboBox::AdjustToContents );
    connect ( this, SIGNAL ( activated ( int ) ), this, SLOT ( m_activated ( int ) ) );

    _depura ( "END BfBuscarTrabajadorDelegate::BfBuscarTrabajadorDelegate", 0 );
}


/** Libera la memoria reservada.
*/
/**
**/
BfBuscarTrabajadorDelegate::~BfBuscarTrabajadorDelegate()
{
    _depura ( "BfBuscarTrabajadorDelegate::~BfBuscarTrabajadorDelegate", 0 );

    if ( m_comboRecordSet != NULL ) {
        delete m_comboRecordSet;
    } // end if

    _depura ( "END BfBuscarTrabajadorDelegate::~BfBuscarTrabajadorDelegate", 0 );
}


/** Permite indicar al Widget cual es la serie de factura seleccionada por defecto.
    Recarga cursor de serie_factura y cuando encuentra un registro cuyo codigoserie_factura coincide con el pasado
    como parametro lo establece como el registro activo por el comboBox.
*/
/**
\param cod
**/
void BfBuscarTrabajadorDelegate::set ( const QString &cod )
{
    _depura ( "BfBuscarTrabajadorDelegate::set", 0 );
    int index = 0;
    QString codigo = cod;

    if ( m_comboRecordSet != NULL ) {
        delete m_comboRecordSet;
    } // end if

    m_comboRecordSet = mainCompany() ->loadQuery ( "SELECT nomtrabajador, apellidostrabajador FROM trabajador " );
    clear();

    while ( !m_comboRecordSet->eof() ) {
        addItem ( m_comboRecordSet->valor ( "apellidostrabajador" ) + ", " + m_comboRecordSet->valor ( "nomtrabajador" ) );
        m_comboRecordSet->nextRecord();
        if ( m_comboRecordSet->valor ( "apellidostrabajador" ) + ", " + m_comboRecordSet->valor ( "nomtrabajador" ) == cod )
            index = m_comboRecordSet->currentRecord();
    } // end while

    setEditText ( cod );
    setCurrentIndex ( index );

    _depura ( "END BfBuscarTrabajadorDelegate::set", 0 );
}
