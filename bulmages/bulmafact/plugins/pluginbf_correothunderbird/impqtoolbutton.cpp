/***************************************************************************
 *   Copyright(C) 2008 by Arturo Martin Llado                             *
 *   amartin@conetxia.com                                                  *
 *                                                                         *
 *   Copyright(C) 2005 by Tomeu Borras Riera                              *
 *   tborras@conetxia.com                                                  *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *  (at your option) any later version.                                   *
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

#include "impqtoolbutton.h"
#include "blfunctions.h"
#include "presupuestoview.h"
#include "blfixed.h"
#include "facturaview.h"
#include "bfcompany.h"
#include "bldb.h"

///
/**
\param pres
\param ped
\param alb
\param fac
\param parent
**/
EmailThunderbirdQToolButton::EmailThunderbirdQToolButton ( PresupuestoView *pres, PedidoClienteView *ped, AlbaranClienteView *alb, FacturaView *fac , QWidget *parent ) : QToolButton ( parent )
{
    _depura ( "EmailThunderbirdQToolButton::EmailThunderbirdQToolButton", 0 );

    m_presupuestoView = pres;
    m_pedidoClienteView = ped;
    m_albaranClienteView = alb;
    m_facturaView = fac;

    setBoton();

    _depura ( "END EmailThunderbirdQToolButton::EmailThunderbirdQToolButton", 0 );
}

///
/**
**/
EmailThunderbirdQToolButton::~EmailThunderbirdQToolButton()
{
    _depura ( "EmailThunderbirdQToolButton::~EmailThunderbirdQToolButton", 0 );
    _depura ( "END EmailThunderbirdQToolButton::~EmailThunderbirdQToolButton", 0 );
}

///
/**
**/
void EmailThunderbirdQToolButton::setBoton()
{
    _depura ( "EmailThunderbirdQToolButton::setBoton", 0 );

    connect ( this, SIGNAL ( clicked() ), this, SLOT ( click() ) );

    setObjectName ( QString::fromUtf8 ( "exporta" ) );
    setStatusTip ( _ ( "Enviar por e-mail con Thunderbird al cliente" ) );
    setToolTip ( _ ( "Enviar por e-mail con Thunderbird al cliente" ) );
    setMinimumSize ( QSize ( 32, 32 ) );
    setMaximumSize ( QSize ( 32, 32 ) );
    setIcon ( QIcon ( g_confpr->valor ( CONF_PROGDATA ) + "icons/icon_mozilla-thunderbird.xpm"  ) );
    setIconSize ( QSize ( 22, 22 ) );

    _depura ( "END EmailThunderbirdQToolButton::setBoton", 0 );
}

///
/**
**/
void EmailThunderbirdQToolButton::click()
{
    _depura ( "EmailThunderbirdQToolButton::click", 0 );

    if ( m_presupuestoView != NULL ) {
        m_companyact = m_presupuestoView->mainCompany();

        QString id = m_presupuestoView->dbValue ( "idpresupuesto" );
        QString num = m_presupuestoView->dbValue ( "numpresupuesto" );
        QString ref = m_presupuestoView->dbValue ( "refpresupuesto" );
        QString idcliente = m_presupuestoView->dbValue ( "idcliente" );
        QString query = "SELECT mailcliente from cliente WHERE idcliente=" + idcliente;
        BlDbRecordSet *curs = m_companyact->loadQuery ( query );
        QString email = curs->valor ( "mailcliente" );

        if ( m_presupuestoView->generaRML() ) {
            generaPDF ( "presupuesto" );

            QString cad = "mv " + g_confpr->valor ( CONF_DIR_USER ) + "presupuesto.pdf " + g_confpr->valor ( CONF_DIR_USER ) + "presupuesto" + num + ".pdf";
            system ( cad.toAscii().data() );

            cad = "thunderbird -compose to='" + email + "',subject='Presupuesto " + num + "',body='Adjunto remito presupuesto numero " + num + ". Con referencia " + ref + "\n\n Atentamente\n',attachment='file://" + g_confpr->valor ( CONF_DIR_USER ) + "presupuesto" + num + ".pdf'";

            system ( cad.toAscii().data() );
        } // end if
    } // end if

    if ( m_pedidoClienteView != NULL ) {
        m_companyact = m_pedidoClienteView->mainCompany();

        QString id = m_pedidoClienteView->dbValue ( "idpedidocliente" );
        QString num = m_pedidoClienteView->dbValue ( "numpedidocliente" );
        QString ref = m_pedidoClienteView->dbValue ( "refpedidocliente" );

        QString idcliente = m_pedidoClienteView->dbValue ( "idcliente" );
        QString query = "SELECT mailcliente from cliente WHERE idcliente=" + idcliente;
        BlDbRecordSet *curs = m_companyact->loadQuery ( query );
        QString email = curs->valor ( "mailcliente" );

        if ( m_pedidoClienteView->generaRML() ) {
            generaPDF ( "pedidocliente" );

            QString cad = "mv " + g_confpr->valor ( CONF_DIR_USER ) + "pedidocliente.pdf " + g_confpr->valor ( CONF_DIR_USER ) + "pedidocliente" + num + ".pdf";
            system ( cad.toAscii().data() );

            cad = "thunderbird -compose to='" + email + "',subject='Pedido " + num + "',body='Adjunto remito pedido numero " + num + ". Con referencia " + ref + "\n\n Atentamente\n',attachment='file://" + g_confpr->valor ( CONF_DIR_USER ) + "pedidocliente" + num + ".pdf'";

            system ( cad.toAscii().data() );
        } // end if
    } // end if

    if ( m_albaranClienteView != NULL ) {
        m_companyact = m_albaranClienteView->mainCompany();

        QString id = m_albaranClienteView->dbValue ( "idalbaran" );
        QString num = m_albaranClienteView->dbValue ( "numalbaran" );
        QString ref = m_albaranClienteView->dbValue ( "refalbaran" );

        QString idcliente = m_albaranClienteView->dbValue ( "idcliente" );
        QString query = "SELECT mailcliente from cliente WHERE idcliente=" + idcliente;
        BlDbRecordSet *curs = m_companyact->loadQuery ( query );
        QString email = curs->valor ( "mailcliente" );

        if ( m_albaranClienteView->generaRML() ) {
            generaPDF ( "albaran" );

            QString cad = "mv " + g_confpr->valor ( CONF_DIR_USER ) + "albaran.pdf " + g_confpr->valor ( CONF_DIR_USER ) + "albaran" + num + ".pdf";
            system ( cad.toAscii().data() );

            cad = "thunderbird -compose to='" + email + "',subject='Albaran " + num + "',body='Adjunto remito albaran numero " + num + ". Con referencia " + ref + "\n\n Atentamente\n',attachment='file://" + g_confpr->valor ( CONF_DIR_USER ) + "albaran" + num + ".pdf'";

            system ( cad.toAscii().data() );
        } // end if
    } // end if

    if ( m_facturaView != NULL ) {
        m_companyact = m_facturaView->mainCompany();

        QString id = m_facturaView->dbValue ( "idfactura" );
        QString num = m_facturaView->dbValue ( "numfactura" );
        QString serie = m_facturaView->dbValue ( "codigoserie_factura" );
        QString ref = m_facturaView->dbValue ( "reffactura" );
        QString fecha = m_facturaView->dbValue ( "ffactura" );

        QString idcliente = m_facturaView->dbValue ( "idcliente" );
        QString query = "SELECT mailcliente from cliente WHERE idcliente=" + idcliente;
        BlDbRecordSet *curs = m_companyact->loadQuery ( query );
        QString email = curs->valor ( "mailcliente" );

        if ( m_facturaView->generaRML() ) {
            generaPDF ( "factura" );

            QString cad = "mv " + g_confpr->valor ( CONF_DIR_USER ) + "factura.pdf " + g_confpr->valor ( CONF_DIR_USER ) + "factura" + serie + num + ".pdf";
            system ( cad.toAscii().data() );

            cad = "thunderbird -compose to='" + email + "',subject='Factura " + num + "',body='Estimado cliente:\n\nAdjunto le enviamos la factura numero " + serie + num + " con fecha " + fecha + "\nSin otro particular reciba un cordial saludo.\n',attachment='file://" + g_confpr->valor ( CONF_DIR_USER ) + "factura" + serie + num + ".pdf'";

            system ( cad.toAscii().data() );
        } // end if
    } // end if

    _depura ( "END EmailThunderbirdQToolButton::click", 0 );
}