/***************************************************************************
 *   Copyright (C) 2004 by Tomeu Borras Riera                              *
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
#include <QCheckBox>
#include <QFile>
#include <QCheckBox>
#include <QTextStream>

#include "presupuestolist.h"
#include "company.h"
#include "presupuestoview.h"
#include "funcaux.h"
#include "plugins.h"
#include "configuracion.h"


///
/**
\param parent
\param flag
\return
**/
PresupuestoList::PresupuestoList ( QWidget *parent, Qt::WFlags flag )
        : Listado ( NULL, parent, flag )
{
    _depura ( "PresupuestoList::PresupuestoList(1)", 0 );
    setupUi ( this );
    /// Disparamos los plugins.
    int res = g_plugins->lanza ( "PresupuestoList_PresupuestoList", this );
    if ( res != 0 )
        return;
    m_idpresupuesto = "";
    setSubForm ( mui_list );
    hideBusqueda();
    iniciaForm();
    _depura ( "END PresupuestoList::PresupuestoList(1)", 0 );
}


///
/**
\param comp
\param parent
\param flag
\return
**/
PresupuestoList::PresupuestoList ( Company *comp, QWidget *parent, Qt::WFlags flag )
        : Listado ( comp, parent, flag )
{
    _depura ( "PresupuestoList::PresupuestoList(2)", 0 );
    setupUi ( this );
    /// Disparamos los plugins.
    int res = g_plugins->lanza ( "PresupuestoList_PresupuestoList", this );
    if ( res != 0 )
        return;
    m_cliente->setEmpresaBase ( comp );
    m_articulo->setEmpresaBase ( comp );
    mui_list->setEmpresaBase ( comp );
    setSubForm ( mui_list );
    presentar();
    m_idpresupuesto = "";
    empresaBase() ->meteWindow ( windowTitle(), this );
    hideBusqueda();
    iniciaForm();
    /// Hacemos el tratamiento de los permisos que desabilita botones en caso de no haber suficientes permisos.
    trataPermisos ( "presupuesto" );
    _depura ( "END PresupuestoList::PresupuestoList(2)", 0 );
}


///
/**
\return
**/
void PresupuestoList::iniciaForm()
{
    _depura ( "PresupuestoList::iniciaForm" );
    /// Disparamos los plugins.
    int res = g_plugins->lanza ( "PresupuestoList_iniciaForm", this );
    if ( res != 0 )
        return;
    mui_procesada->insertItem ( 0, tr ( "Todos los presupuestos" ) );
    mui_procesada->insertItem ( 1, tr ( "Presupuestos procesados" ) );
    mui_procesada->insertItem ( 2, tr ( "Presupuestos no procesados" ) );
    _depura ( "END PresupuestoList::iniciaForm" );
}


///
/**
**/
PresupuestoList::~PresupuestoList()
{
    _depura ( "PresupuestoList::~PresupuestoList", 0 );
    _depura ( "END PresupuestoList::~PresupuestoList", 0 );
}


///
/**
\return
**/
QString PresupuestoList::idpresupuesto()
{
    _depura ( "PresupuestoList::idpresupuesto", 0 );
    _depura ( "END PresupuestoList::idpresupuesto", 0 );
    return m_idpresupuesto;
}


///
/**
\param comp
**/
void PresupuestoList::setEmpresaBase ( Company *comp )
{
    _depura ( "PresupuestoList::setEmpresaBase", 0 );
    PEmpresaBase::setEmpresaBase ( comp );
    m_cliente->setEmpresaBase ( comp );
    m_articulo->setEmpresaBase ( comp );
    mui_list->setEmpresaBase ( comp );
    _depura ( "END PresupuestoList::setEmpresaBase", 0 );
}


///
/**
\param val
**/
void PresupuestoList::setidcliente ( QString val )
{
    _depura ( "PresupuestoList::setidcliente", 0 );
    m_cliente->setidcliente ( val );
    _depura ( "END PresupuestoList::setidcliente", 0 );
}


///
/**
\param val
**/
void PresupuestoList::setidarticulo ( QString val )
{
    _depura ( "PresupuestoList::setidarticulo", 0 );
    m_articulo->setidarticulo ( val );
    _depura ( "END PresupuestoList::setidarticulo", 0 );
}


///
/**
**/
void PresupuestoList::crear()
{
    _depura ( "PresupuestoList::crear", 0 );
    PresupuestoView * bud = new PresupuestoView((Company *)empresaBase(), 0);
    empresaBase()->m_pWorkspace->addWindow ( bud );
    bud->inicializar();
    bud->show();
    bud->mui_descpresupuesto->setFocus ( Qt::OtherFocusReason );
    _depura ( "END PresupuestoList::crear", 0 );
}


///
/**
**/
void PresupuestoList::presentar()
{
    _depura ( "PresupuestoList::presentar", 0 );

    /// Hacemos el listado y lo presentamos.
    mui_list->cargar ( "SELECT *, totalpresupuesto AS total, bimppresupuesto AS base, imppresupuesto AS impuestos FROM presupuesto LEFT JOIN  cliente ON presupuesto.idcliente=cliente.idcliente LEFT JOIN almacen ON presupuesto.idalmacen=almacen.idalmacen WHERE 1=1 " + generaFiltro() );

    /// Hacemos el calculo del total.
    cursor2 *cur = empresaBase() ->cargacursor ( "SELECT SUM(totalpresupuesto) AS total FROM presupuesto LEFT JOIN cliente ON presupuesto.idcliente=cliente.idcliente LEFT JOIN almacen ON presupuesto.idalmacen=almacen.idalmacen WHERE 1=1 " + generaFiltro() );
    /// Si por un problema de permisos este query devuelve NULL debe contemplarse el caso.
    if ( cur ) {
        m_total->setText ( cur->valor ( "total" ) );
        delete cur;
    } // end if

    _depura ( "END PresupuestoList::presentar", 0 );
}


///
/**
\return
**/
QString PresupuestoList::generaFiltro()
{
    _depura ( "PresupuestoList::generaFiltro", 0 );
    /// Tratamiento de los filtros.
    QString filtro = "";

    if ( m_filtro->text() != "" ) {
        filtro = " AND ( lower(descpresupuesto) LIKE lower('%" + m_filtro->text() + "%') ";
        filtro += " OR refpresupuesto LIKE '" + m_filtro->text() + "%' ";
        filtro += " OR lower(nomcliente) LIKE lower('%" + m_filtro->text() + "%')) ";
    } // end if

    if ( m_cliente->idcliente() != "" ) {
        filtro += " AND presupuesto.idcliente = " + m_cliente->idcliente();
    } // end if

    /// Tratamos los elementos procesados y no procesados.
    if ( mui_procesada->currentIndex() == 1 ) {
        /// Muestra solo las procesadas.
        filtro += " AND procesadopresupuesto";
    } else if ( mui_procesada->currentIndex() == 2 ) {
        /// Muestra solo las NO procesadas.
        filtro += " AND NOT procesadopresupuesto ";
    } // end if

    if ( m_articulo->idarticulo() != "" ) {
        filtro += " AND idpresupuesto IN (SELECT DISTINCT idpresupuesto FROM lpresupuesto WHERE idarticulo='" + m_articulo->idarticulo() + "')";
    }// end if

    if ( m_fechain->text() != "" )
        filtro += " AND fpresupuesto >= '" + m_fechain->text() + "' ";
    if ( m_fechafin->text() != "" )
        filtro += " AND fpresupuesto <= '" + m_fechafin->text() + "' ";
    _depura ( "END PresupuestoList::generaFiltro", 0 );
    return ( filtro );
}


///
/**
\param row
\return
**/
void PresupuestoList::editar ( int row )
{
    _depura ( "PresupuestoList::editar", 0 );
    try {
        m_idpresupuesto = mui_list->DBvalue ( QString ( "idpresupuesto" ), row );
        if ( modoEdicion() ) {
            PresupuestoView * prov = new PresupuestoView( ( Company * ) empresaBase() , 0 );
            if ( prov->cargar ( m_idpresupuesto ) ) {
                delete prov;
                return;
            }
            empresaBase() ->m_pWorkspace->addWindow ( prov );
            prov->show();
        } else {
            emit ( selected ( m_idpresupuesto ) );
        } // end if
        _depura ( "END PresupuestoList::editar", 0 );
    } catch ( ... ) {
        mensajeInfo ( tr ( "Error al editar el presupuesto" ), this );
    } // end try
}


///
/**
\return
**/
void PresupuestoList::imprimir()
{
    _depura ( "PresupuestoList::imprimir", 0 );
    mui_list->imprimirPDF ( tr ( "Presupuestos a clientes" ) );
    _depura ( "END PresupuestoList::imprimir", 0 );
}


///
/**
\return
**/
void PresupuestoList::borrar()
{
    _depura ( "PresupuestoList::borrar", 0 );
    int a = mui_list->currentRow();
    if ( a < 0 ) {
        mensajeInfo ( tr ( "Debe seleccionar una linea" ), this );
        return;
    } // end if
    try {
        m_idpresupuesto = mui_list->DBvalue ( QString ( "idpresupuesto" ) );
        if ( modoEdicion() ) {
            PresupuestoView * pv = new PresupuestoView ( ( Company * ) empresaBase(), 0);
            if ( pv->cargar ( m_idpresupuesto ) )
                throw - 1;
            pv->on_mui_borrar_clicked();
            pv->close();
        } // end if
        presentar();
    } catch ( ... ) {
        mensajeInfo ( tr ( "Error al borrar el presupuesto" ), this );
    } // end try
    _depura ( "END PresupuestoList::borrar", 0 );
}


/// =============================================================================
///                    SUBFORMULARIO
/// =============================================================================
///
/**
\param parent
\return
**/
PresupuestoListSubForm::PresupuestoListSubForm ( QWidget *parent, const char * ) : SubForm2Bf ( parent )
{
    _depura ( "PresupuestoListSubForm::PresupuestoListSubForm", 0 );
    /// Disparamos los plugins.
    int res = g_plugins->lanza ( "PresupuestoListSubForm_PresupuestoListSubForm", this );
    if ( res != 0 ) {
        _depura ( "END PresupuestoListSubForm::PresupuestoListSubForm", 0, "Salida por Plugin" );
        return;
    } // end if
    setDBTableName ( "presupuesto" );
    setDBCampoId ( "idpresupuesto" );
    addSHeader ( "idpresupuesto", DBCampo::DBint, DBCampo::DBNotNull | DBCampo::DBPrimaryKey, SHeader::DBNoView | SHeader::DBNoWrite, tr ( "ID presupuesto" ) );
    addSHeader ( "numpresupuesto", DBCampo::DBint, DBCampo::DBNoSave, SHeader::DBNone | SHeader::DBNoWrite, tr ( "Presupuesto" ) );
    addSHeader ( "fpresupuesto", DBCampo::DBdate, DBCampo::DBNoSave, SHeader::DBNone | SHeader::DBNoWrite, tr ( "Fecha" ) );
    addSHeader ( "nomcliente", DBCampo::DBvarchar, DBCampo::DBNoSave, SHeader::DBNone | SHeader::DBNoWrite, tr ( "Cliente" ) );
    addSHeader ( "refpresupuesto", DBCampo::DBvarchar, DBCampo::DBNoSave, SHeader::DBNone | SHeader::DBNoWrite, tr ( "Referencia" ) );
    addSHeader ( "base", DBCampo::DBnumeric, DBCampo::DBNoSave, SHeader::DBNone | SHeader::DBNoWrite, tr ( "Base Imponible" ) );
    addSHeader ( "impuestos", DBCampo::DBnumeric, DBCampo::DBNoSave, SHeader::DBNone | SHeader::DBNoWrite, tr ( "Impuestos" ) );
    addSHeader ( "total", DBCampo::DBnumeric, DBCampo::DBNoSave, SHeader::DBNone | SHeader::DBNoWrite, tr ( "Total" ) );
    addSHeader ( "descpresupuesto", DBCampo::DBvarchar, DBCampo::DBNoSave, SHeader::DBNone | SHeader::DBNoWrite, tr ( "Descripcion" ) );
    addSHeader ( "contactpresupuesto", DBCampo::DBvarchar, DBCampo::DBNoSave, SHeader::DBNone | SHeader::DBNoWrite, tr ( "Persona de contacto" ) );
    addSHeader ( "telpresupuesto", DBCampo::DBvarchar, DBCampo::DBNoSave, SHeader::DBNone | SHeader::DBNoWrite, tr ( "Telefono" ) );
    addSHeader ( "comentpresupuesto", DBCampo::DBvarchar, DBCampo::DBNoSave, SHeader::DBNone | SHeader::DBNoWrite, tr ( "Comentario" ) );
    addSHeader ( "codigoalmacen", DBCampo::DBvarchar, DBCampo::DBNoSave, SHeader::DBNone | SHeader::DBNoWrite, tr ( "Almacen" ) );
    addSHeader ( "idtrabajador", DBCampo::DBint, DBCampo::DBNoSave, SHeader::DBNone | SHeader::DBNoWrite, tr ( "ID trabajador" ) );
    addSHeader ( "idcliente", DBCampo::DBint, DBCampo::DBNoSave, SHeader::DBNone | SHeader::DBNoWrite, tr ( "ID cliente" ) );
    addSHeader ( "idalmacen", DBCampo::DBint, DBCampo::DBNoSave, SHeader::DBNone | SHeader::DBNoWrite, tr ( "ID almacen" ) );
    setinsercion ( FALSE );
    setDelete ( FALSE );
    setSortingEnabled ( TRUE );
    /// Disparamos los plugins.
    g_plugins->lanza ( "PresupuestoListSubForm_PresupuestoListSubForm_Post", this );
    _depura ( "END PresupuestoListSubForm::PresupuestoListSubForm", 0 );
    return;
}


///
/**
**/
void PresupuestoListSubForm::cargar()
{
    _depura ( "PresupuestoListSubForm::cargar", 0 );
    QString SQLQuery = "SELECT * FROM presupuesto";
    SubForm3::cargar ( SQLQuery );
    _depura ( "END PresupuestoListSubForm::cargar", 0 );
}


///
/**
\param query
**/
void PresupuestoListSubForm::cargar ( QString query )
{
    _depura ( "PresupuestoListSubForm::cargar", 0, query );
    SubForm3::cargar ( query );
    _depura ( "END PresupuestoListSubForm::cargar", 0 );
}