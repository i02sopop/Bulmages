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

#include "bcformapagoview.h"
#include "bccompany.h"


/// El constructor de la clase prepara las variables globales y llama a la funci&oacute;n
/// pintar.
/**
\param emp
\param parent
**/
BcFormaPagoView::BcFormaPagoView ( BcCompany *emp, QWidget *parent )
        : BcForm ( emp, parent )
{
    _depura ( "BcFormaPagoView::BcFormaPagoView", 0 );

    setTitleName ( _ ( "Forma de Pago" ) );
    /// Establecemos cual es la tabla en la que basarse para los permisos
    setDbTableName ( "fpago" );

    this->setAttribute ( Qt::WA_DeleteOnClose );
    setupUi ( this );
    m_curfpago = NULL;

    dialogChanges_setQObjectExcluido ( mui_comboFPago );

    pintar();
    dialogChanges_cargaInicial();
    emp->meteWindow ( windowTitle(), this );

    _depura ( "END BcFormaPagoView::BcFormaPagoView", 0 );
}


/// El destructor de la clase guarda los datos (por si ha habido cambios) y libera
/// la memoria que se haya ocupado. */
/**
**/
BcFormaPagoView::~BcFormaPagoView()
{
    _depura ( "BcFormaPagoView::~BcFormaPagoView", 0 );
    on_mui_guardar_clicked();
    if ( m_curfpago != NULL ) {
        delete m_curfpago;
    } /// end if
    sacaWindow();
    _depura ( "END BcFormaPagoView::~BcFormaPagoView", 0 );
}


///
/**
\param i
**/
void BcFormaPagoView::on_mui_comboFPago_currentIndexChanged ( int i )
{
    _depura ( "BcFormaPagoView::on_mui_comboFPago_currentIndexChanged", 0 );
    cambiacombo ( i );
    _depura ( "END BcFormaPagoView::on_mui_comboFPago_currentIndexChanged", 0 );
}


/// Pinta la ventana, recarga el combo y si se pasa el par&aacute;metro muestra
/// el identificador indicado. */
/**
\param idfpago
**/
void BcFormaPagoView::pintar ( QString idfpago )
{
    _depura ( "BcFormaPagoView::pintar", 0 );
    int posicion = 0;
    /// Vamos a inicializar el combo de los tipos de IVA.
    if ( m_curfpago != NULL )
        delete m_curfpago;
    QString query = "SELECT * from fpago ORDER BY nomfpago";
    m_curfpago = mainCompany() ->loadQuery ( query );
    mui_comboFPago->clear();
    int i = 0;
    while ( !m_curfpago->eof() ) {
        mui_comboFPago->insertItem ( i, m_curfpago->valor ( "nomfpago" ) );
        if ( idfpago == m_curfpago->valor ( "idfpago" ) )
            posicion = i;
        m_curfpago->nextRecord();
        i++;
    } // end while

    if ( mui_comboFPago->currentIndex() == -1 ) {
        mui_nombreFPago->setEnabled ( FALSE );
        mui_plazoPrimerPago->setEnabled ( FALSE );
        mui_numeroPlazos->setEnabled ( FALSE );
        mui_tipoPlazoPrimerPago->setEnabled ( FALSE );
        mui_plazoEntreRecibos->setEnabled ( FALSE );
        mui_tipoPlazoEntreRecibos->setEnabled ( FALSE );

        mui_nombreFPago->setText ( "" );
        mui_plazoPrimerPago->setText ( "" );
        mui_numeroPlazos->setText ( "" );
        mui_tipoPlazoPrimerPago->setText ( "" );
        mui_plazoEntreRecibos->setText ( "" );
        mui_tipoPlazoEntreRecibos->setText ( "" );
    } else {
        mui_nombreFPago->setEnabled ( TRUE );
        mui_plazoPrimerPago->setEnabled ( TRUE );
        mui_numeroPlazos->setEnabled ( TRUE );
        mui_tipoPlazoPrimerPago->setEnabled ( TRUE );
        mui_plazoEntreRecibos->setEnabled ( TRUE );
        mui_tipoPlazoEntreRecibos->setEnabled ( TRUE );

        mostrarplantilla ( posicion );
    } // end if
    _depura ( "END BcFormaPagoView::pintar", 0 );
}


/// Esta funci&oacute;n muestra la forma de pago en la ventana.
/** \param pos si es distinto de cero se busca en el combo la posici&oacute;n
    indicada sino se usa la posici&oacute;n actual del combo. */
/**
\param pos
**/
void BcFormaPagoView::mostrarplantilla ( int pos )
{
    _depura ( "BcFormaPagoView::mostrarplantilla", 0 );
    /// Si se ha modificado el contenido advertimos y guardamos.
    if ( dialogChanges_hayCambios() ) {
        if ( QMessageBox::warning ( this,
                                    _ ( "Guardar forma de pago" ),
                                    _ ( "Desea guardar los cambios?" ),
                                    QMessageBox::Ok, QMessageBox::Cancel ) == QMessageBox::Ok )
            on_mui_guardar_clicked();
    } // end if
    if ( mui_comboFPago->count() > 0 ) {
        if ( pos != 0 ) {
            mui_comboFPago->setCurrentIndex ( pos );
        } // end if
        m_posactual = mui_comboFPago->currentIndex();
        mui_nombreFPago->setText ( m_curfpago->valor ( "nomfpago", m_posactual ) );
        mui_plazoPrimerPago->setText ( m_curfpago->valor ( "plazoprimerpagofpago", m_posactual ) );
        mui_numeroPlazos->setText ( m_curfpago->valor ( "nplazosfpago", m_posactual ) );
        mui_tipoPlazoPrimerPago->setText ( m_curfpago->valor ( "tipoplazoprimerpagofpago", m_posactual ) );
        mui_plazoEntreRecibos->setText ( m_curfpago->valor ( "plazoentrerecibofpago", m_posactual ) );
        mui_tipoPlazoEntreRecibos->setText ( m_curfpago->valor ( "tipoplazoentrerecibofpago", m_posactual ) );
        /// Comprobamos cual es la cadena inicial.
        dialogChanges_cargaInicial();
    } // end if
    _depura ( "END BcFormaPagoView::mostrarplantilla", 0 );
}


/// Esta funci&oacute;n sirve para hacer el cambio sobre un centro de coste.
/**
**/
void BcFormaPagoView::cambiacombo ( int )
{
    _depura ( "BcFormaPagoView::cambiacombo", 0 );
    mostrarplantilla();
    _depura ( "END BcFormaPagoView::cambiacombo", 0 );
}


/// SLOT que responde a la pulsaci&oacute;n del bot&oacute;n de guardar el tipo de
/// IVA que se est&aacute; editando.
/** Lo que hace es que se hace un update de todos los campos. */
/**
**/
int BcFormaPagoView::guardar()
{
    _depura ( "BcFormaPagoView::on_mui_guardarFPago_clicked", 0 );
    QString idfpago = m_curfpago->valor ( "idfpago", m_posactual );
    QString query = "UPDATE fpago SET nomfpago = '" + mui_nombreFPago->text() + "', nplazosfpago = " + mui_numeroPlazos->text() + " , plazoprimerpagofpago = " + mui_plazoPrimerPago->text() + ", plazoentrerecibofpago = " + mui_plazoEntreRecibos->text() + " WHERE idfpago = " + m_curfpago->valor ( "idfpago", m_posactual );
    mainCompany() ->runQuery ( query );
    dialogChanges_cargaInicial();
    pintar ( m_curfpago->valor ( "idfpago", m_posactual ) );
    _depura ( "END BcFormaPagoView::on_mui_guardarFPago_clicked", 0 );
    return 0;
}


/// SLOT que responde a la pulsacion del boton de nuevo tipo de IVA. Inserta en la tabla
/// de IVAs.
/**
**/
void BcFormaPagoView::on_mui_crear_clicked()
{
    _depura ( "BcFormaPagoView::crear", 0 );
    /// Si se ha modificado el contenido advertimos y guardamos.
    if ( dialogChanges_hayCambios() ) {
        if ( QMessageBox::warning ( this,
                                    _ ( "Guardar forma de pago" ),
                                    _ ( "Desea guardar los cambios?" ),
                                    QMessageBox::Ok, QMessageBox::Cancel ) == QMessageBox::Ok )
            on_mui_guardar_clicked();
    } // end if
    try {
        QString query = "INSERT INTO fpago (nomfpago, nplazosfpago, plazoprimerpagofpago, plazoentrerecibofpago) VALUES ('" + _ ( "Nueva forma de pago" ) + "', 0, 0, 0)";
        mainCompany() ->begin();
        mainCompany() ->runQuery ( query );
        BlDbRecordSet *cur = mainCompany() ->loadQuery ( "SELECT max(idfpago) AS idfpago FROM fpago" );
        mainCompany() ->commit();
        pintar ( cur->valor ( "idfpago" ) );
        delete cur;
    } catch ( ... ) {
        mainCompany() ->rollback();
        return;
    } // end try
    _depura ( "END BcFormaPagoView::crear", 0 );
}


/// SLOT que responde a la pulsaci&oacute;n del bot&oacute;n de borrar un tipo de IVA.
/** Borra en la tabla de tiposiva el TIPO de IVA concreto. */
/**
\returns
**/
void BcFormaPagoView::on_mui_borrar_clicked()
{
    _depura ( "BcFormaPagoView::borrar", 0 );
    if ( mui_comboFPago->currentIndex() == -1 ) {
        mensajeInfo ( _ ( "Tiene que seleccionar una forma de pago antes de borrarla" ) );
        return;
    } else {
        switch ( QMessageBox::warning ( this,
                                        _ ( "Borrar forma de pago" ),
                                        _ ( "Se va a borrar la forma de pago.\nEsto puede ocasionar perdida de datos.\n" ),
                                        QMessageBox::Ok, QMessageBox::Cancel ) ) {
        case QMessageBox::Ok: /// Retry clicked or Enter pressed.
            mainCompany() ->runQuery ( "DELETE FROM fpago WHERE idfpago = " + m_curfpago->valor ( "idfpago", mui_comboFPago->currentIndex() ) );
            pintar();
            break;
        case QMessageBox::Cancel: /// Abort clicked or Escape pressed.
            break;
        } // end switch
    } // end if
    return;
    _depura ( "END BcFormaPagoView::borrar", 0 );
}

