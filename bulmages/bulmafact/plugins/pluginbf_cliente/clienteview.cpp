/***************************************************************************
 *   Copyright (C) 2004 by Marcos Mezo                                     *
 *   mmezo@selexco.net                                                     *
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

#include <QLineEdit>
#include <QMessageBox>
#include <QToolButton>
#include <QWidget>
#include <QComboBox>
#include <QCloseEvent>

#include "clienteview.h"
#include "company.h"
#include "funcaux.h"
#include "plugins.h"
#include "informereferencia.h"


/** Inicializa todos los componentes.
    Mete la ventana en el workSpace.
    Resetea el control de cambios.
*/
/**
\param comp
\param parent
\return
**/
ClienteView::ClienteView ( Company *comp, QWidget *parent )
        : FichaBf ( comp, parent )
{
    _depura ( "ClienteView::ClienteView", 0 );
    setupUi ( this );
    setAttribute ( Qt::WA_DeleteOnClose );
    try {

        setTitleName ( _( "Cliente" ) );
        setDBTableName ( "cliente" );
        setDBCampoId ( "idcliente" );
        addDBCampo ( "idcliente", DBCampo::DBint, DBCampo::DBPrimaryKey, _( "ID cliente" ) );
        addDBCampo ( "nomcliente", DBCampo::DBvarchar, DBCampo::DBNotNull, _( "Nombre del cliente" ) );
        addDBCampo ( "nomaltcliente", DBCampo::DBvarchar, DBCampo::DBNothing, _( "Nombre alternativo del cliente" ) );
        addDBCampo ( "cifcliente", DBCampo::DBvarchar, DBCampo::DBNothing, _( "C.I.F. del cliente" ) );
        addDBCampo ( "bancocliente", DBCampo::DBvarchar, DBCampo::DBNothing, _( "Numero cuenta corriente" ) );
        addDBCampo ( "dircliente", DBCampo::DBvarchar, DBCampo::DBNothing, _( "Direccion" ) );
        addDBCampo ( "poblcliente", DBCampo::DBvarchar, DBCampo::DBNothing, _( "Poblacion" ) );
        addDBCampo ( "idprovincia", DBCampo::DBint, DBCampo::DBNothing, _( "Provincia" ) );
        addDBCampo ( "cpcliente", DBCampo::DBvarchar, DBCampo::DBNothing, _( "Codigo postal" ) );
        addDBCampo ( "telcliente", DBCampo::DBvarchar, DBCampo::DBNothing, _( "Numero de telefono" ) );
        addDBCampo ( "teltrabcliente", DBCampo::DBvarchar, DBCampo::DBNothing, _( "Numero de telefono en el trabajo" ) );
        addDBCampo ( "movilcliente", DBCampo::DBvarchar, DBCampo::DBNothing, _( "Numero de telefono movil" ) );
        addDBCampo ( "faxcliente", DBCampo::DBvarchar, DBCampo::DBNothing, _( "Numero de fax" ) );
        addDBCampo ( "mailcliente", DBCampo::DBvarchar, DBCampo::DBNothing, _( "Direccion electronica" ) );
        addDBCampo ( "urlcliente", DBCampo::DBvarchar, DBCampo::DBNothing, _( "Identificador de presupuesto" ) );
        addDBCampo ( "faltacliente", DBCampo::DBdate, DBCampo::DBNothing, _( "Fecha de alta del cliente" ) );
        addDBCampo ( "fbajacliente", DBCampo::DBdate, DBCampo::DBNothing, _( "Fecha de baja del cliente" ) );
        addDBCampo ( "comentcliente", DBCampo::DBvarchar, DBCampo::DBNothing, _( "Comentarios" ) );
        addDBCampo ( "ecommercedatacliente", DBCampo::DBvarchar, DBCampo::DBNothing, _( "Datos de comercio electronico" ) );
        addDBCampo ( "inactivocliente", DBCampo::DBvarchar, DBCampo::DBNothing, _( "Cliente inactivo" ) );
        addDBCampo ( "regimenfiscalcliente", DBCampo::DBvarchar, DBCampo::DBNothing, _( "Regimen fiscal" ) );
        addDBCampo ( "codcliente", DBCampo::DBvarchar, DBCampo::DBNothing, _( "Codigo" ) );
        addDBCampo ( "corpcliente", DBCampo::DBvarchar, DBCampo::DBNothing, _( "Empresa" ) );
        addDBCampo ( "idforma_pago", DBCampo::DBint, DBCampo::DBNothing, _( "Forma de pago" ) );
        addDBCampo ( "recargoeqcliente", DBCampo::DBboolean, DBCampo::DBNothing, _( "Recargo de Equivalencia" ) );

        /// Disparamos los plugins.
        int res = g_plugins->lanza ( "ClienteView_ClienteView", this );
        if ( res != 0 ) {
            return;
        } // end if

        /// Datos por defecto.
        mui_idprovincia->setEmpresaBase ( empresaBase() );

    mui_idprovincia->setQuery("SELECT * FROM provincia LEFT JOIN pais ON provincia.idpais = pais.idpais ORDER BY descpais, provincia");
    mui_idprovincia->setTableName ("provincia");
    mui_idprovincia->setCampoId ("idprovincia");
    mui_idprovincia->m_valores["provincia"] = "";
    mui_idprovincia->m_valores["descpais"] = "";
        mui_idprovincia->setId ( "" );

        mui_idforma_pago->setEmpresaBase ( empresaBase() );
        mui_idforma_pago->setidforma_pago ( 0 );

        /// Metemos la ventana en el workSpace.
        meteWindow ( windowTitle(), this, FALSE );
        dialogChanges_cargaInicial();
        /// Disparamos los plugins.
        res = g_plugins->lanza ( "ClienteView_ClienteView_Post", this );
    } catch ( ... ) {
        mensajeInfo ( _( "Error al crear el cliente" ) );
    } // end try
    _depura ( "END ClienteView::ClienteView", 0 );
}


/** No precisa de acciones adicionales.
*/
/**
**/
ClienteView::~ClienteView()
{
    _depura ( "ClienteView::~ClienteView", 0 );
    empresaBase() ->refreshClientes();
    /// Disparamos los plugins.
    g_plugins->lanza ( "ClienteView_Des_ClienteView", this );
    empresaBase() ->sacaWindow ( this );
    _depura ( "END ClienteView::~ClienteView", 0 );
}


/**
* cargar
*
* Given a valid client ID this function loads the client into the
* form so that we can edit it.
*
* Otherwise it empties the form and sets it so that we can add
* a new client
*
* Si la funcion falla imprime un mensaje de error y devuelve -1
* Si todo va bien devuelve 0
**/
/**
\param idcliente
\return
**/
int ClienteView::cargarPost ( QString idcliente )
{
    _depura ( "ClienteView::cargarPost", 0 );

    /// Lanzamos los plugins de carga
    g_plugins->lanza("ClienteView_cargarPost_Post", this);

    _depura ( "END ClienteView::cargarPost", 0 );
    return 0;
}


/** SLOT que responde a la pulsacion del boton informe de cliente.
    Crea una instancia de InformeCliente, la inicializa y la lanza.
*/
/**
**/
void ClienteView::on_mui_informe_clicked()
{
    _depura ( "ClienteView::on_mui_informe_clicked", 0 );

    if ( DBvalue ( "idcliente" ).isEmpty() ) {
        mensajeInfo ( _( "Tiene que guardar el documento antes de poder imprimirlo." ) );
    } else {
        InformeCliente inf ( empresaBase() );
        inf.setCliente ( DBvalue ( "idcliente" ) );
        inf.generarInforme();
    } // end if

    _depura ( "END ClienteView::on_mui_informe_clicked", 0 );
}


/**
*/
/**
**/
void ClienteView::on_mui_cifcliente_lostFocus()
{
    _depura ( "ClienteView::on_mui_cifcliente_lostFocus", 0 );
	QChar digito;
	if (!validarCIFNIF(mui_cifcliente->text(), digito)) {
		mensajeInfo("Error en el CIF del cliente. Control:" + QString(digito));
	} // end if
    _depura ( "END ClienteView::on_mui_cifcliente_lostFocus", 0 );
}





/**
*/
/**
**/
void ClienteView::activaDocumentos()
{
    _depura ( "ClienteView::activaDocumentos", 0 );
    mui_tab->setTabEnabled ( 2, TRUE );
    mui_tab->setTabEnabled ( 3, TRUE );
    mui_tab->setTabEnabled ( 4, TRUE );
    mui_tab->setTabEnabled ( 5, TRUE );
    mui_tab->setTabEnabled ( 6, TRUE );
    _depura ( "END ClienteView::activaDocumentos", 0 );
}


/**
*/
/**
**/
void ClienteView::desactivaDocumentos()
{
    _depura ( "ClienteView::desactivaDocumentos", 0 );
    mui_tab->setTabEnabled ( 2, FALSE );
    mui_tab->setTabEnabled ( 3, FALSE );
    mui_tab->setTabEnabled ( 4, FALSE );
    mui_tab->setTabEnabled ( 5, FALSE );
    mui_tab->setTabEnabled ( 6, FALSE );
    _depura ( "END ClienteView::desactivaDocumentos", 0 );
}
