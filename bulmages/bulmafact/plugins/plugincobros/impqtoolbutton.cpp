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

#include <QWidget>
#include "impqtoolbutton.h"
#include "funcaux.h"

/// Necesarios para importacion de efactura
#include <QtXml/QDomDocument>
#include <QtXml/QDomNodeList>
#include <QtXml/QDomNode>
#include <QString>
#include <QFileDialog>
#include <QMap>
#include <QList>
#include "facturaview.h"
#include "albaranclienteview.h"
#include "pedidoclienteview.h"
#include "fixed.h"
#include "company.h"
#include "dbrecord.h"
#include "cobroview.h"

///
/**
\param pres
\param ped
\param alb
\param fac
\param parent
**/
GenCobroQToolButton::GenCobroQToolButton ( QWidget *fac , QWidget *parent ) : QToolButton ( parent )
{
    _depura ( "GenCobroQToolButton::GenCobroQToolButton", 0 );
    m_object = fac;
    setBoton();
    _depura ( "END GenCobroQToolButton::GenCobroQToolButton", 0 );
}


///
/**
**/
GenCobroQToolButton::~GenCobroQToolButton()
{
    _depura ( "GenCobroQToolButton::~GenCobroQToolButton", 0 );
    _depura ( "END GenCobroQToolButton::~GenCobroQToolButton", 0 );
}


///
/**
**/
void GenCobroQToolButton::setBoton()
{
    _depura ( "GenCobroQToolButton::setBoton", 0 );
    connect ( this, SIGNAL ( clicked() ), this, SLOT ( click() ) );
    setObjectName ( QString::fromUtf8 ( "exporta" ) );
    setStatusTip ( "Generar Pago" );
    setToolTip ( "Generar Pago" );
    setMinimumSize ( QSize ( 32, 32 ) );
    setMaximumSize ( QSize (32, 32 ) );
    setIcon ( QIcon ( QString::fromUtf8 ( ":/Images/receive.svg" ) ) );
    setIconSize ( QSize ( 32, 32 ) );
    setContentsMargins (0, 0, 0, 0);
    _depura ( "END GenCobroQToolButton::setBoton", 0 );
}


///
/**
**/
void GenCobroQToolButton::click()
{
    _depura ( "ImpQToolButton::click", 0 );

    if (m_object->objectName() == "FacturaBase" ) {
		FacturaView *fpv = (FacturaView *) m_object;
		int nuevo = 1;
		/// Comprobamos que no haya ya un cobro con la misma referencia y lo ponemos
		QString query = "SELECT * FROM cobro WHERE refcobro ='"+ fpv->DBvalue("reffactura")+"'";
		cursor2 *cur = fpv->empresaBase()->cargacursor(query);
		if (cur->numregistros() > 0) {
		QMessageBox msgBox;
		msgBox.setText(tr("Ya existe un cobro con esta referencia\n"));
		msgBox.setInformativeText(tr("Desea abrir el cobro existente, registrar un nuevo cobro o salir?"));
			QPushButton *connectButton = msgBox.addButton(tr("Crear"), QMessageBox::ActionRole);
		QPushButton *openButton = msgBox.addButton(QMessageBox::Open);
		QPushButton *abortButton = msgBox.addButton(QMessageBox::Cancel);
		msgBox.setDefaultButton(QMessageBox::Cancel);
		msgBox.exec();
			/// Se ha pulsado sobre la opcion abrir
	if (msgBox.clickedButton() == openButton) {
	
				while (!cur->eof()) {
					CobroView *bud = new CobroView( (Company *) fpv->empresaBase(), 0);
					fpv->empresaBase() ->m_pWorkspace->addWindow ( bud );
					bud->cargar(cur->valor("idcobro"));
					bud->pintar();
					bud->show();
					cur->siguienteregistro();
				} // end while
				nuevo = 0;
	} // end if
	
			/// Se ha pulsado sobre la opcion cancelar
	if (msgBox.clickedButton() == abortButton)
				nuevo = 0;
		} // end if
		delete cur;
	
		/// Creacion de un cobro nuevo a partir de la factura.
		if (nuevo) {
			CobroView *bud = new CobroView(fpv->empresaBase(), 0);
			fpv->empresaBase() ->m_pWorkspace->addWindow ( bud );
			bud->setDBvalue ( "idcliente", fpv->DBvalue ( "idcliente" ) );
			bud->setDBvalue ( "cantcobro", fpv->m_totalfactura->text() );
			bud->setDBvalue ( "refcobro", fpv->DBvalue ( "reffactura" ) );
			bud->setDBvalue ( "comentcobro", fpv->DBvalue ( "descfactura" ) );
			bud->pintar();
			bud->show();
		} // end if
    }// end if


    if (m_object->objectName() == "AlbaranClienteBase" ) {
			AlbaranClienteView *fpv = (AlbaranClienteView *) m_object;
			int nuevo = 1;
			/// Comprobamos que no haya ya un cobro con la misma referencia y lo ponemos
			QString query = "SELECT * FROM cobro WHERE refcobro ='"+fpv->DBvalue("refalbaran")+"'";
			cursor2 *cur = fpv->empresaBase()->cargacursor(query);
			if (cur->numregistros() > 0) {
			QMessageBox msgBox;
			msgBox.setText(tr("Ya existe un cobro con esta referencia\n"));
			msgBox.setInformativeText(tr("Desea abrir el cobro existente, registrar un nuevo cobro o salir?"));
				QPushButton *connectButton = msgBox.addButton(tr("Crear"), QMessageBox::ActionRole);
			QPushButton *openButton = msgBox.addButton(QMessageBox::Open);
			QPushButton *abortButton = msgBox.addButton(QMessageBox::Cancel);
			msgBox.setDefaultButton(QMessageBox::Cancel);
			msgBox.exec();
				/// Se ha pulsado sobre la opcion abrir
		if (msgBox.clickedButton() == openButton) {
		
					while (!cur->eof()) {
						CobroView *bud = new CobroView( (Company *) fpv->empresaBase(), 0);
						fpv->empresaBase() ->m_pWorkspace->addWindow ( bud );
						bud->cargar(cur->valor("idcobro"));
						bud->pintar();
						bud->show();
						cur->siguienteregistro();
					} // end while
					nuevo = 0;
		} // end if
		
				/// Se ha pulsado sobre la opcion cancelar
		if (msgBox.clickedButton() == abortButton)
					nuevo = 0;
			} // end if
			delete cur;
		
			/// Creacion de un cobro nuevo a partir de la factura.
			if (nuevo) {
			CobroView *bud = new CobroView((Company *)fpv->empresaBase(), 0);
			fpv->empresaBase() ->m_pWorkspace->addWindow ( bud );
			bud->setDBvalue ( "idcliente", fpv->DBvalue ( "idcliente" ) );
			bud->setDBvalue ( "cantcobro", fpv->m_totalalbaran->text() );
			bud->setDBvalue ( "refcobro", fpv->DBvalue ( "refalbaran" ) );
			bud->setDBvalue ( "comentcobro", fpv->DBvalue ( "descalbaran" ) );
			bud->pintar();
			bud->show();
			} // end if
    }// end if


    if (m_object->objectName() == "PedidoClienteBase" ) {
			PedidoClienteView *fpv = (PedidoClienteView *) m_object;
			int nuevo = 1;
			/// Comprobamos que no haya ya un cobro con la misma referencia y lo ponemos
			QString query = "SELECT * FROM cobro WHERE refcobro ='"+fpv->DBvalue("refpedidocliente")+"'";
			cursor2 *cur = fpv->empresaBase()->cargacursor(query);
			if (cur->numregistros() > 0) {
			QMessageBox msgBox;
			msgBox.setText(tr("Ya existe un cobro con esta referencia\n"));
			msgBox.setInformativeText(tr("Desea abrir el cobro existente, registrar un nuevo cobro o salir?"));
				QPushButton *connectButton = msgBox.addButton(tr("Crear"), QMessageBox::ActionRole);
			QPushButton *openButton = msgBox.addButton(QMessageBox::Open);
			QPushButton *abortButton = msgBox.addButton(QMessageBox::Cancel);
			msgBox.setDefaultButton(QMessageBox::Cancel);
			msgBox.exec();
				/// Se ha pulsado sobre la opcion abrir
		if (msgBox.clickedButton() == openButton) {
		
					while (!cur->eof()) {
						CobroView *bud = new CobroView( (Company *) fpv->empresaBase(), 0);
						fpv->empresaBase() ->m_pWorkspace->addWindow ( bud );
						bud->cargar(cur->valor("idcobro"));
						bud->pintar();
						bud->show();
						cur->siguienteregistro();
					} // end while
					nuevo = 0;
		} // end if
		
				/// Se ha pulsado sobre la opcion cancelar
		if (msgBox.clickedButton() == abortButton)
					nuevo = 0;
			} // end if
			delete cur;
		
			/// Creacion de un cobro nuevo a partir de la factura.
			if (nuevo) {
			CobroView *bud = new CobroView( (Company *) fpv->empresaBase(), 0);
			fpv->empresaBase() ->m_pWorkspace->addWindow ( bud );
			bud->setDBvalue ( "idcliente", fpv->DBvalue ( "idcliente" ) );
			bud->setDBvalue ( "cantcobro", fpv->m_totalpedidocliente->text() );
			bud->setDBvalue ( "refcobro", fpv->DBvalue ( "refpedidocliente" ) );
			bud->setDBvalue ( "comentcobro", fpv->DBvalue ( "descpedidocliente" ) );
			bud->pintar();
			bud->show();
			} // end if
    }// end if

    _depura ( "END ImpQToolButton::click", 0 );
}

