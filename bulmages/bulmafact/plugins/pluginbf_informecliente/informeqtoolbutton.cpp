/***************************************************************************
 *   Copyright (C) 2006 by Arturo Martin Llado                             *
 *   amartin@conetxia.com                                                  *
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
#include <stdlib.h>

#include <QWidget>
#include <QFile>
#include <QTextStream>
#include <QString>
#include <QFileDialog>
#include <QMap>
#include <QList>

#include "informeqtoolbutton.h"
#include "blfunctions.h"
#include "blfixed.h"
#include "bfcompany.h"
#include "bldb.h"
#include "articulolist.h"
#include "blprogressbar.h"


///
/**
\param art
\param parent
**/
InformeQToolButton::InformeQToolButton ( ClientsList *art , QWidget *parent ) : QToolButton ( parent ), BlMainCompanyPointer()
{
    _depura ( "InformeQToolButton::InformeQToolButton", 0 );
    m_clientsList = art;
    setBoton();
    _depura ( "END InformeQToolButton::InformeQToolButton", 0 );
}


///
/**
**/
InformeQToolButton::~InformeQToolButton()
{
    _depura ( "InformeQToolButton::~InformeQToolButton", 0 );
    _depura ( "END InformeQToolButton::~InformeQToolButton", 0 );
}


///
/**
**/
void InformeQToolButton::setBoton()
{
    _depura ( "InformeQToolButton::setBoton", 0 );
    connect ( this, SIGNAL ( clicked() ), this, SLOT ( click() ) );
    setObjectName ( QString::fromUtf8 ( "exporta" ) );
    setStatusTip ( "Imprimir Catalogo" );
    setToolTip ( "Imprimir Catalogo" );
    setMinimumSize ( QSize ( 32, 32 ) );
    setIcon ( QIcon (  g_confpr->valor ( CONF_PROGDATA ) + "icons/catalogo.png" ) );
    setIconSize ( QSize ( 22, 22 ) );
    _depura ( "END InformeQToolButton::setBoton", 0 );
}


///
/**
**/
void InformeQToolButton::click()
{
    _depura ( "InformeQToolButton::click", 0 );
    // Puede que no se haya actualizado bien el company
    setMainCompany ( m_clientsList->mainCompany() );

    QString archivo = g_confpr->valor ( CONF_DIR_OPENREPORTS ) + "informeclientes.rml";
    QString archivod = g_confpr->valor ( CONF_DIR_USER ) + "informeclientes.rml";
    QString archivologo = g_confpr->valor ( CONF_DIR_OPENREPORTS ) + "logo.jpg";

    /// Copiamos el archivo.
#ifdef WINDOWS

    archivo = "copy " + archivo + " " + archivod;
#else

    archivo = "cp " + archivo + " " + archivod;
#endif

    system ( archivo.toAscii().constData() );

    /// Copiamos el logo.
#ifdef WINDOWS

    archivologo = "copy " + archivologo + " " + g_confpr->valor ( CONF_DIR_USER ) + "logo.jpg";
#else

    archivologo = "cp " + archivologo + " " + g_confpr->valor ( CONF_DIR_USER ) + "logo.jpg";
#endif

    QFile file;
    file.setFileName ( archivod );
    file.open ( QIODevice::ReadOnly );
    QTextStream stream ( &file );
    QString buff = stream.readAll();
    file.close();
    QString fitxersortidatxt = "";


    /// Sacamos los datos del cliente.
    QString SQLQuery = "SELECT * FROM cliente ";
    BlDbRecordSet *cur = mainCompany() ->loadQuery ( SQLQuery );

    /// Mostramos la barra de progreso
    BlProgressBar barra;
    barra.setRange ( 0, cur->numregistros() );
    barra.show();
    barra.setText ( _ ( "Generando Informe" ) );

    while ( !cur->eof() ) {
        QString gen = generarCliente ( cur->valor ( "idcliente" ) );
        if ( gen != "" ) {
            fitxersortidatxt += "<para><H1>Cliente: " + cur->valor ( "nomcliente" );
            fitxersortidatxt += " -- " + cur->valor ( "cifcliente" ) + "</H1></para>\n";
            fitxersortidatxt += gen;
            fitxersortidatxt += "\n<nextPage/>\n";
            fitxersortidatxt += "\n<nextFrame/>\n";
        } // end if
        cur->nextRecord();
        barra.setValue ( barra.value() + 1 );
    } // end while
    delete cur;

    buff.replace ( "[story]", fitxersortidatxt );

    if ( file.open ( QIODevice::WriteOnly ) ) {
        QTextStream stream ( &file );
        stream << buff;
        file.close();
    } // end if
    invocaPDF ( "informeclientes" );

    _depura ( "END InformeQToolButton::click", 0 );
}


///
/**
\param idcliente
\return
**/
QString InformeQToolButton::generarCliente ( QString idcliente )
{
    _depura ( "InformeQToolButton::generarCliente", 0 );
    QString fitxersortidatxt;
    /// Sacamos todas las referencias de este cliente y las guardamos en el string referencias
    QString referencias = "(";
    QString coma = "";
    QString SQLQuery = "SELECT refpresupuesto AS referencia FROM presupuesto WHERE idcliente = " + idcliente;
    SQLQuery += " UNION SELECT refpedidocliente AS referencia FROM pedidocliente WHERE idcliente = " + idcliente;
    SQLQuery += " UNION SELECT refalbaran FROM albaran AS referencia WHERE idcliente = " + idcliente;
    SQLQuery += " UNION SELECT reffactura FROM factura AS referencia WHERE idcliente = " + idcliente;
    SQLQuery += " UNION SELECT refcobro FROM cobro AS referencia WHERE idcliente = " + idcliente;
    BlDbRecordSet *cur = mainCompany() ->loadQuery ( SQLQuery );
    if ( cur->eof() ) {
        delete cur;
        return "";
    } // end if
    while ( !cur->eof() ) {
        referencias += coma + "'" + cur->valor ( "referencia" ) + "' ";
        coma = ",";
        cur->nextRecord();
    }
    delete cur;
    referencias += ")";

    /// Generacion del informe de ventas.
    fitxersortidatxt = "<spacer length=\"15\"/>";
    fitxersortidatxt += "<para>Resumen de ventas por articulo</para>\n";
    fitxersortidatxt += "<blockTable style=\"tablaresumen\" colWidths=\"9cm, 2.5cm, 2.5cm, 2.5cm, 2.5cm\" repeatRows=\"1\">\n";
    fitxersortidatxt += "<tr>\n";
    fitxersortidatxt += "    <td>" + _ ( "Articulo" ) + "</td>\n";
    fitxersortidatxt += "    <td>" + _ ( "Pres." ) + "</td>\n";
    fitxersortidatxt += "    <td>" + _ ( "Pedido" ) + "</td>\n";
    fitxersortidatxt += "    <td>" + _ ( "Entregado" ) + "</td>\n";
    fitxersortidatxt += "    <td>" + _ ( "Facturado" ) + "</td>\n";
    fitxersortidatxt += "</tr>\n";

    SQLQuery = " SELECT * FROM articulo ";
    SQLQuery += " LEFT JOIN (SELECT idarticulo, SUM(cantlpresupuesto) AS cantlpresupuestot  FROM lpresupuesto WHERE idpresupuesto IN (SELECT idpresupuesto FROM presupuesto WHERE refpresupuesto IN " + referencias + ") GROUP BY idarticulo) AS t1 ON t1.idarticulo = articulo.idarticulo ";
    SQLQuery += " LEFT JOIN (SELECT idarticulo, SUM(cantlpedidocliente) AS cantlpedidoclientet  FROM lpedidocliente WHERE idpedidocliente IN (SELECT idpedidocliente FROM pedidocliente WHERE refpedidocliente IN " + referencias + ") GROUP BY idarticulo) AS t2 ON t2.idarticulo = articulo.idarticulo ";
    SQLQuery += " LEFT JOIN (SELECT idarticulo, SUM(cantlalbaran) AS cantlalbarant  FROM lalbaran WHERE idalbaran IN (SELECT idalbaran FROM albaran WHERE refalbaran IN " + referencias + ") GROUP BY idarticulo) AS t3 ON t3.idarticulo = articulo.idarticulo ";
    SQLQuery += " LEFT JOIN (SELECT idarticulo, SUM(cantlfactura) AS cantlfacturat  FROM lfactura WHERE idfactura IN (SELECT idfactura FROM factura WHERE reffactura IN " + referencias + ") GROUP BY idarticulo) AS t4 ON t4.idarticulo = articulo.idarticulo ";
    SQLQuery += " WHERE  (cantlpresupuestot <>0 OR cantlpedidoclientet <> 0 OR cantlalbarant <> 0 OR cantlfacturat <> 0) ";
    cur = mainCompany() ->loadQuery ( SQLQuery );
    while ( !cur->eof() ) {
        fitxersortidatxt += "<tr>\n";
        fitxersortidatxt += "    <td>" + cur->valor ( "nomarticulo" ) + "</td>\n";
        fitxersortidatxt += "    <td>" + cur->valor ( "cantlpresupuestot" ) + "</td>\n";
        fitxersortidatxt += "    <td>" + cur->valor ( "cantlpedidoclientet" ) + "</td>\n";
        fitxersortidatxt += "    <td>" + cur->valor ( "cantlalbarant" ) + "</td>\n";
        fitxersortidatxt += "    <td>" + cur->valor ( "cantlfacturat" ) + "</td>\n";
        fitxersortidatxt += "</tr>\n";
        cur->nextRecord();
    } // end while
    delete cur;

    fitxersortidatxt += "</blockTable>\n";

    /// Generacion del informe de compras.
    fitxersortidatxt += "<spacer length=\"15\"/>";
    fitxersortidatxt += "<para>Resumen de compras por articulo</para>\n";
    fitxersortidatxt += "<blockTable style=\"tablaresumen\" colWidths=\"10cm, 3cm, 3cm, 3cm\" repeatRows=\"1\">\n";
    fitxersortidatxt += "<tr>\n";
    fitxersortidatxt += "    <td>" + _ ( "Articulo" ) + "</td>\n";
    fitxersortidatxt += "    <td>" + _ ( "Pedido" ) + "</td>\n";
    fitxersortidatxt += "    <td>" + _ ( "Entregado" ) + "</td>\n";
    fitxersortidatxt += "    <td>" + _ ( "Facturado" ) + "</td>\n";
    fitxersortidatxt += "</tr>\n";

    SQLQuery = " SELECT * FROM articulo ";
    SQLQuery += " LEFT JOIN (SELECT idarticulo, SUM(cantlpedidoproveedor) AS cantlpedidoproveedort  FROM lpedidoproveedor WHERE idpedidoproveedor IN (SELECT idpedidoproveedor FROM pedidoproveedor WHERE refpedidoproveedor IN " + referencias + ") GROUP BY idarticulo) AS t2 ON t2.idarticulo = articulo.idarticulo ";

    SQLQuery += " LEFT JOIN (SELECT idarticulo, SUM(cantlalbaranp) AS cantlalbaranpt  FROM lalbaranp WHERE idalbaranp IN (SELECT idalbaranp FROM albaranp WHERE refalbaranp IN " + referencias + ") GROUP BY idarticulo) AS t3 ON t3.idarticulo = articulo.idarticulo ";

    SQLQuery += " LEFT JOIN (SELECT idarticulo, SUM(cantlfacturap) AS cantlfacturapt  FROM lfacturap WHERE idfacturap IN (SELECT idfacturap FROM facturap WHERE reffacturap IN " + referencias + ") GROUP BY idarticulo) AS t4 ON t4.idarticulo = articulo.idarticulo ";
    SQLQuery += " WHERE  ( cantlpedidoproveedort <> 0 OR cantlalbaranpt <> 0 OR cantlfacturapt <> 0) ";

    cur = mainCompany() ->loadQuery ( SQLQuery );
    while ( !cur->eof() ) {
        fitxersortidatxt += "<tr>\n";
        fitxersortidatxt += "    <td>" + cur->valor ( "nomarticulo" ) + "</td>\n";
        fitxersortidatxt += "    <td>" + cur->valor ( "cantlpedidoproveedort" ) + "</td>\n";
        fitxersortidatxt += "    <td>" + cur->valor ( "cantlalbaranpt" ) + "</td>\n";
        fitxersortidatxt += "    <td>" + cur->valor ( "cantlfacturapt" ) + "</td>\n";
        fitxersortidatxt += "</tr>\n";
        cur->nextRecord();
    } // end while
    delete cur;

    fitxersortidatxt += "</blockTable>\n";

    fitxersortidatxt += "<spacer length=\"15\"/>";
    /// Generacion del informe de totales de ventas.
    fitxersortidatxt += "<para>Totales ventas</para>\n";
    fitxersortidatxt += "<blockTable style=\"tablatotales\" colWidths=\"3cm, 3cm, 3cm, 3cm, 3cm\" repeatRows=\"1\">\n";
    fitxersortidatxt += "<tr>\n";
    fitxersortidatxt += "    <td>" + _ ( "Pres." ) + "</td>\n";
    fitxersortidatxt += "    <td>" + _ ( "Pedido" ) + "</td>\n";
    fitxersortidatxt += "    <td>" + _ ( "Entregado" ) + "</td>\n";
    fitxersortidatxt += "    <td>" + _ ( "Facturado" ) + "</td>\n";
    fitxersortidatxt += "    <td>" + _ ( "Cobrado" ) + "</td>\n";
    fitxersortidatxt += "</tr>\n";

    /// Calculo de las cantidades totales en moneda.
    fitxersortidatxt += "<tr>\n";

    /// Total presupuestado.
    SQLQuery = "SELECT SUM(totalpresupuesto) AS tpres FROM presupuesto WHERE refpresupuesto IN " + referencias;
    cur = mainCompany() ->loadQuery ( SQLQuery );
    fitxersortidatxt += "    <td>" + cur->valor ( "tpres" ) + "</td>\n";
    delete cur;

    /// Total pedido.
    SQLQuery = "SELECT SUM(totalpedidocliente) AS tpedcli FROM pedidocliente WHERE refpedidocliente IN " + referencias;
    cur = mainCompany() ->loadQuery ( SQLQuery );
    fitxersortidatxt += "    <td>" + cur->valor ( "tpedcli" ) + "</td>\n";
    delete cur;

    /// Total trabajado.
    SQLQuery = "SELECT SUM(totalalbaran) AS talb FROM albaran WHERE refalbaran IN " + referencias;
    cur = mainCompany() ->loadQuery ( SQLQuery );
    fitxersortidatxt += "    <td>" + cur->valor ( "talb" ) + "</td>\n";
    delete cur;

    /// Total facturado.
    SQLQuery = "SELECT SUM(totalfactura) AS tfact FROM factura WHERE reffactura IN " + referencias;
    cur = mainCompany() ->loadQuery ( SQLQuery );
    fitxersortidatxt += "    <td>" + cur->valor ( "tfact" ) + "</td>\n";
    delete cur;

    /// Total cobrado.
    SQLQuery = "SELECT SUM(cantcobro) AS tcobro FROM cobro WHERE refcobro IN " + referencias;
    cur = mainCompany() ->loadQuery ( SQLQuery );
    fitxersortidatxt += "     <td>" + cur->valor ( "tcobro" ) + "</td>\n";
    delete cur;

    fitxersortidatxt += "</tr>\n";
    fitxersortidatxt += "</blockTable>\n";

    fitxersortidatxt += "<spacer length=\"15\"/>";
    /// Generacion del informe de totales de compras.
    fitxersortidatxt += "<para>Totales compras</para>\n";
    fitxersortidatxt += "<blockTable style=\"tablatotales\" colWidths=\" 4cm, 4cm, 4cm, 3cm\" repeatRows=\"1\">\n";
    fitxersortidatxt += "<tr>\n";
    fitxersortidatxt += "    <td>" + _ ( "Pedido" ) + "</td>\n";
    fitxersortidatxt += "    <td>" + _ ( "Entregado" ) + "</td>\n";
    fitxersortidatxt += "    <td>" + _ ( "Facturado" ) + "</td>\n";
    fitxersortidatxt += "    <td>" + _ ( "Pagado" ) + "</td>\n";
    fitxersortidatxt += "</tr>\n";

    /// Calculo de las cantidades totales en moneda.
    fitxersortidatxt += "<tr>\n";

    /// Total pedido.
    SQLQuery = "SELECT SUM(totalpedidoproveedor) AS tpedpro FROM pedidoproveedor WHERE refpedidoproveedor IN " + referencias;
    cur = mainCompany() ->loadQuery ( SQLQuery );
    fitxersortidatxt += "    <td>" + cur->valor ( "tpedpro" ) + "</td>\n";
    delete cur;

    /// Total trabajado.
    SQLQuery = "SELECT SUM(totalalbaranp) AS talbp FROM albaranp WHERE refalbaranp IN " + referencias;
    cur = mainCompany() ->loadQuery ( SQLQuery );
    fitxersortidatxt += "    <td>" + cur->valor ( "talbp" ) + "</td>\n";
    delete cur;

    /// Total facturado.
    SQLQuery = "SELECT SUM(totalfacturap) AS tfactp FROM facturap WHERE reffacturap IN " + referencias;
    cur = mainCompany() ->loadQuery ( SQLQuery );
    fitxersortidatxt += "    <td>" + cur->valor ( "tfactp" ) + "</td>\n";
    delete cur;

    /// Total cobrado.
    SQLQuery = "SELECT SUM(cantpago) AS tpago FROM pago WHERE refpago IN " + referencias;
    cur = mainCompany() ->loadQuery ( SQLQuery );
    fitxersortidatxt += "     <td>" + cur->valor ( "tpago" ) + "</td>\n";
    delete cur;

    fitxersortidatxt += "</tr>\n";
    fitxersortidatxt += "</blockTable>\n";
    _depura ( "END InformeQToolButton::generarCliente", 0 );
    return fitxersortidatxt;
}

/// ==========================================================================
/// ==========================================================================
/// ==========================================================================

///
/**
\param art
\param parent
**/
InformeArtQToolButton::InformeArtQToolButton ( ArticuloList *art , QWidget *parent ) : QToolButton ( parent ), BlMainCompanyPointer()
{
    _depura ( "InformeArtQToolButton::InformeQToolButton", 0 );
    m_articuloList = art;
    setBoton();
    _depura ( "END InformeArtQToolButton::InformeQToolButton", 0 );
}


///
/**
**/
InformeArtQToolButton::~InformeArtQToolButton()
{
    _depura ( "InformeArtQToolButton::~InformeArtQToolButton", 0 );
    _depura ( "END InformeQToolButton::~InformeQToolButton", 0 );
}


///
/**
**/
void InformeArtQToolButton::setBoton()
{
    _depura ( "InformeArtQToolButton::setBoton", 0 );
    connect ( this, SIGNAL ( clicked() ), this, SLOT ( click() ) );
    setObjectName ( QString::fromUtf8 ( "exporta" ) );
    setStatusTip ( "Imprimir Informe Resumen" );
    setToolTip ( "Imprimir Informe Resumen" );
    setMinimumSize ( QSize ( 32, 32 ) );
    setIcon ( QIcon ( g_confpr->valor ( CONF_PROGDATA ) + "icons/catalogo.png" ) );
    setIconSize ( QSize ( 22, 22 ) );
    _depura ( "END InformeArtQToolButton::setBoton", 0 );
}


///
/**
**/
void InformeArtQToolButton::click()
{
    _depura ( "InformeArtQToolButton::click", 0 );
    // Puede que no se haya actualizado bien el company
    setMainCompany ( m_articuloList->mainCompany() );

    QString archivo = g_confpr->valor ( CONF_DIR_OPENREPORTS ) + "informearticulos.rml";
    QString archivod = g_confpr->valor ( CONF_DIR_USER ) + "informearticulos.rml";
    QString archivologo = g_confpr->valor ( CONF_DIR_OPENREPORTS ) + "logo.jpg";

    /// Copiamos el archivo.
#ifdef WINDOWS

    archivo = "copy " + archivo + " " + archivod;
#else

    archivo = "cp " + archivo + " " + archivod;
#endif

    system ( archivo.toAscii().constData() );

    /// Copiamos el logo.
#ifdef WINDOWS

    archivologo = "copy " + archivologo + " " + g_confpr->valor ( CONF_DIR_USER ) + "logo.jpg";
#else

    archivologo = "cp " + archivologo + " " + g_confpr->valor ( CONF_DIR_USER ) + "logo.jpg";
#endif

    QFile file;
    file.setFileName ( archivod );
    file.open ( QIODevice::ReadOnly );
    QTextStream stream ( &file );
    QString buff = stream.readAll();
    file.close();
    QString fitxersortidatxt = generarArticulos();


    buff.replace ( "[story]", fitxersortidatxt );

    if ( file.open ( QIODevice::WriteOnly ) ) {
        QTextStream stream ( &file );
        stream << buff;
        file.close();
    } // end if
    invocaPDF ( "informearticulos" );

    _depura ( "END InformeQToolButton::click", 0 );
}


///
/**
\param idcliente
\return
**/
QString InformeArtQToolButton::generarArticulos()
{
    _depura ( "InformeQToolButton::generarCliente", 0 );
    QString fitxersortidatxt;


    /// Generacion del informe de ventas.
    fitxersortidatxt += "<blockTable style=\"tablaresumen\" colWidths=\"9cm, 1.5cm, 1.5cm, 1.5cm, 1.5cm, 1.5cm, 1.5cm, 1.5cm\" repeatRows=\"1\">\n";
    fitxersortidatxt += "<tr>\n";
    fitxersortidatxt += "    <td>" + _ ( "Articulo" ) + "</td>\n";
    fitxersortidatxt += "    <td>" + _ ( "C. Ped." ) + "</td>\n";
    fitxersortidatxt += "    <td>" + _ ( "C. Entr." ) + "</td>\n";
    fitxersortidatxt += "    <td>" + _ ( "C. Fact." ) + "</td>\n";
    fitxersortidatxt += "    <td>" + _ ( "V. Pres." ) + "</td>\n";
    fitxersortidatxt += "    <td>" + _ ( "V. Ped." ) + "</td>\n";
    fitxersortidatxt += "    <td>" + _ ( "V. Entr." ) + "</td>\n";
    fitxersortidatxt += "    <td>" + _ ( "V. Fact." ) + "</td>\n";
    fitxersortidatxt += "</tr>\n";

    QString SQLQuery = " SELECT * FROM articulo ";
    SQLQuery += " LEFT JOIN (SELECT idarticulo, SUM(cantlpresupuesto) AS cantlpresupuestot  FROM lpresupuesto   GROUP BY idarticulo) AS t1 ON t1.idarticulo = articulo.idarticulo ";
    SQLQuery += " LEFT JOIN (SELECT idarticulo, SUM(cantlpedidocliente) AS cantlpedidoclientet  FROM lpedidocliente GROUP BY idarticulo) AS t2 ON t2.idarticulo = articulo.idarticulo ";
    SQLQuery += " LEFT JOIN (SELECT idarticulo, SUM(cantlalbaran) AS cantlalbarant  FROM lalbaran GROUP BY idarticulo) AS t3 ON t3.idarticulo = articulo.idarticulo ";
    SQLQuery += " LEFT JOIN (SELECT idarticulo, SUM(cantlfactura) AS cantlfacturat  FROM lfactura GROUP BY idarticulo) AS t4 ON t4.idarticulo = articulo.idarticulo ";
    SQLQuery += " LEFT JOIN (SELECT idarticulo, SUM(cantlpedidoproveedor) AS cantlpedidoproveedort  FROM lpedidoproveedor GROUP BY idarticulo) AS t7 ON t7.idarticulo = articulo.idarticulo ";
    SQLQuery += " LEFT JOIN (SELECT idarticulo, SUM(cantlalbaranp) AS cantlalbaranpt  FROM lalbaranp GROUP BY idarticulo) AS t5 ON t5.idarticulo = articulo.idarticulo ";
    SQLQuery += " LEFT JOIN (SELECT idarticulo, SUM(cantlfacturap) AS cantlfacturapt  FROM lfacturap GROUP BY idarticulo) AS t6 ON t6.idarticulo = articulo.idarticulo ";
    SQLQuery += " WHERE  (cantlpresupuestot <>0 OR cantlpedidoclientet <> 0 OR cantlalbarant <> 0 OR cantlfacturat <> 0 OR cantlpedidoproveedort <> 0 OR cantlalbaranpt <> 0 OR cantlfacturapt <> 0) ";
    BlDbRecordSet *cur = mainCompany() ->loadQuery ( SQLQuery );

    /// Generamos la barra de progreso.
    BlProgressBar barra;
    barra.setRange ( 0, cur->numregistros() );
    barra.show();
    barra.setText ( _ ( "Generando informe" ) );

    while ( !cur->eof() ) {
        fitxersortidatxt += "<tr>\n";
        fitxersortidatxt += "    <td>" + cur->valor ( "nomarticulo" ) + "</td>\n";
        fitxersortidatxt += "    <td>" + cur->valor ( "cantlpedidoproveedort" ) + "</td>\n";
        fitxersortidatxt += "    <td>" + cur->valor ( "cantlalbaranpt" ) + "</td>\n";
        fitxersortidatxt += "    <td>" + cur->valor ( "cantlfacturapt" ) + "</td>\n";
        fitxersortidatxt += "    <td>" + cur->valor ( "cantlpresupuestot" ) + "</td>\n";
        fitxersortidatxt += "    <td>" + cur->valor ( "cantlpedidoclientet" ) + "</td>\n";
        fitxersortidatxt += "    <td>" + cur->valor ( "cantlalbarant" ) + "</td>\n";
        fitxersortidatxt += "    <td>" + cur->valor ( "cantlfacturat" ) + "</td>\n";
        fitxersortidatxt += "</tr>\n";
        cur->nextRecord();
        barra.setValue ( barra.value() + 1 );
    } // end while
    delete cur;

    fitxersortidatxt += "</blockTable>\n";

    _depura ( "END InformeQToolButton::generarArticulos", 0 );
    return fitxersortidatxt;
}

