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

#include <stdio.h>

#include "pluginalbaran.h"
#include "plugins.h"
#include "company.h"
#include "funcaux.h"
#include "albaranclienteview.h"
#include "albaranclientelist.h"

#include "genalbqtoolbutton.h"


AlbaranClienteList *g_albaranClienteList=NULL;

///
/**
**/
mypluginalb::mypluginalb()
{
    _depura ( "mypluginalb::mypluginalb", 0 );
    _depura ( "END mypluginalb::mypluginalb", 0 );
}


///
/**
**/
mypluginalb::~mypluginalb()
{
    _depura ( "mypluginalb::~mypluginalb", 0 );
    _depura ( "END mypluginalb::~mypluginalb", 0 );
}


///
/**
**/
void mypluginalb::elslot()
{
    _depura ( "mypluginalb::elslot", 0 );
    if (g_albaranClienteList) {
	g_albaranClienteList->hide();
	g_albaranClienteList->show();
    }// end if
    _depura ( "END mypluginalb::elslot", 0 );
}

///
/**
**/
void mypluginalb::elslot1()
{
    _depura ( "mypluginalb::elslot1", 0 );
        AlbaranClienteView * bud = new AlbaranClienteView((Company *)empresaBase(), NULL);
        empresaBase() ->m_pWorkspace->addWindow ( bud );
        bud->show();
    _depura ( "END mypluginalb::elslot1", 0 );
}



///
/**
\param bges
**/
void mypluginalb::inicializa ( Bulmafact *bges )
{
    _depura ( "mypluginalb::inicializa", 0 );

    if ( bges->getcompany()->has_table_privilege ( "albaran", "SELECT" ) ) {

    /// Miramos si existe un menu Ventas
	QMenu *pPluginMenu = bges->newMenu("&Ventas", "menuVentas", "menuMaestro");

	/// El men&uacute; de Tarifas en la secci&oacute;n de art&iacute;culos.
	m_bges = bges;
	setEmpresaBase ( bges->getcompany() );
	QAction *planCuentas = new QAction ( tr ( "&Albaranes a Clientes" ), 0 );
	planCuentas->setIcon(QIcon ( QString::fromUtf8 ( ":/Images/client-delivery-note-list.svg" ) ));
	planCuentas->setStatusTip ( tr ( "Albaranes a Clientes" ) );
	planCuentas->setWhatsThis ( tr ( "Albaranes a Clientes" ) );
	pPluginMenu->addAction ( planCuentas );
	bges->Listados->addAction (planCuentas);
	connect ( planCuentas, SIGNAL ( activated() ), this, SLOT ( elslot() ) );

	QAction *npago = new QAction ( tr ( "&Nueva Albaran a Cliente" ), 0 );
	npago->setIcon(QIcon ( QString::fromUtf8 ( ":/Images/client-delivery-note.svg" ) ));
	npago->setStatusTip ( tr ( "Nueva Albaran a Cliente" ) );
	npago->setWhatsThis ( tr ( "Nueva Albaran a Cliente" ) );
	pPluginMenu->addAction ( npago );
	bges->Fichas->addAction (npago);
	connect ( npago, SIGNAL ( activated() ), this, SLOT ( elslot1() ) );


    }// end if
    _depura ( "END mypluginalb::inicializa", 0 );
}


///
/**
\param bges
\return
**/
int entryPoint ( Bulmafact *bges )
{
    _depura ( "Punto de Entrada del plugin de Albaranes a Clientes\n", 0 );
    mypluginalb *plug = new mypluginalb();
    plug->inicializa ( bges );
    return 0;
}


int Company_createMainWindows_Post(Company *comp) {
    if ( comp->has_table_privilege ( "albaran", "SELECT" ) ) {
	g_albaranClienteList = new AlbaranClienteList( comp, NULL );	
	comp->m_pWorkspace->addWindow ( g_albaranClienteList );
	g_albaranClienteList->hide();
    }// end if
    return 0;
}


int ClienteView_ClienteView_Post (ClienteView *prov) {
    if ( prov->empresaBase()->has_table_privilege ( "albaran", "SELECT" ) ) {
	AlbaranClienteList *albaranesList = new AlbaranClienteList( (Company *)prov->empresaBase(), NULL );
	albaranesList->setObjectName("listalbaranes");
	albaranesList->hideBusqueda();
        prov->mui_tab->addTab ( albaranesList, "Albaranes" );
    }// end if
    return 0;
}

int ClienteView_cargarPost_Post (ClienteView *prov) {
    if ( prov->empresaBase()->has_table_privilege ( "albaran", "SELECT" ) ) {
	AlbaranClienteList *albaranesList = prov->findChild<AlbaranClienteList *> ( "listalbaranes" );
        albaranesList->setidcliente ( prov->DBvalue ( "idcliente" ) );
        albaranesList->presentar();
    }// end if
    return 0;
}// end if


int BusquedaReferencia_on_mui_abrirtodo_clicked_Post (BusquedaReferencia *ref) {
    QString SQLQuery = "SELECT * FROM albaran WHERE refalbaran = '" + ref->mui_referencia->text() + "'";
    cursor2 *cur = ref->empresaBase() ->cargacursor ( SQLQuery );
    while ( !cur->eof() ) {
        AlbaranClienteView * bud = new AlbaranClienteView((Company *)ref->empresaBase(), NULL);
        ref->empresaBase() ->m_pWorkspace->addWindow ( bud );
        bud->cargar ( cur->valor ( "idfactura" ) );
        bud->show();
        cur->siguienteregistro();
    } // end while
    delete cur;
}// end if


///
/**
\param l
\return
**/
int PedidoClienteView_PedidoClienteView ( PedidoClienteView *l )
{

    _depura ( "PluginFactura_PedidoClienteView_PedidoClienteView", 0 );

    GenAlbQToolButton *mui_exporta_efactura2 = new GenAlbQToolButton ( l, l->mui_plugbotones );

    QHBoxLayout *m_hboxLayout1 = l->mui_plugbotones->findChild<QHBoxLayout *> ( "hboxLayout1" );

	if (!m_hboxLayout1) {
		m_hboxLayout1 = new QHBoxLayout ( l->mui_plugbotones );
		m_hboxLayout1->setSpacing ( 5 );
		m_hboxLayout1->setMargin ( 5 );
		m_hboxLayout1->setObjectName ( QString::fromUtf8 ( "hboxLayout1" ) );
	}// end if
    m_hboxLayout1->addWidget ( mui_exporta_efactura2 );

    _depura ( "END PluginFactura_PedidoClienteView_PedidoClienteView", 0 );

    return 0;
}


///
/**
\param l
\return
**/
int PresupuestoView_PresupuestoView ( PresupuestoView *l )
{

    _depura ( "PluginFactura_PresupuestoView_PresupuestoView", 0 );

    GenAlbQToolButton *mui_exporta_efactura2 = new GenAlbQToolButton ( l, l->mui_plugbotones );

    QHBoxLayout *m_hboxLayout1 = l->mui_plugbotones->findChild<QHBoxLayout *> ( "hboxLayout1" );

	if (!m_hboxLayout1) {
		m_hboxLayout1 = new QHBoxLayout ( l->mui_plugbotones );
		m_hboxLayout1->setSpacing ( 5 );
		m_hboxLayout1->setMargin ( 5 );
		m_hboxLayout1->setObjectName ( QString::fromUtf8 ( "hboxLayout1" ) );
	}// end if
    m_hboxLayout1->addWidget ( mui_exporta_efactura2 );

    _depura ( "END PluginFactura_PresupuestoView_PresupuestoView", 0 );

    return 0;
}

/// Esta llamada de plugin es bastante novedosa ya es una llamada que no responde a una funcion
/// Sino que se llama desde multiples partes del sistema.
int SNewAlbaranClienteView (Company *v)
{
	AlbaranClienteView *h = new AlbaranClienteView(v, 0);
	g_plugParams = h;
	return 1;
}
