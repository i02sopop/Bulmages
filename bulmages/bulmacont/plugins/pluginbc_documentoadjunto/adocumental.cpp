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

#include "asiento1view.h"
#include "adocumental.h"
#include "bccompany.h"

#define COL_IDADOCUMENTAL           0
#define COL_IDASIENTO               1
#define COL_DESCRIPCIONADOCUMENTAL  2
#define COL_FECHAINTADOCUMENTAL     3
#define COL_FECHAASADOCUMENTAL      4
#define COL_ARCHIVOADOCUMENTAL      5
#define COL_ORDENASIENTO            6


///
/**
\param emp
**/
myplugin1::myplugin1 ( BcCompany *emp )
{
    _depura ( "myplugin1::myplugin1", 0 );
    empresaactual = emp;
    dbConnection = emp->bdempresa();
    _depura ( "END myplugin1::myplugin1", 0 );
}


///
/**
**/
myplugin1::~myplugin1()
{
    _depura ( "myplugin1::~myplugin1", 0 );
    _depura ( "END myplugin1::~myplugin1", 0 );
}


/// Esto debe coger un asiento y asociarle un archivo documental y abrirlo y ensenyar
/// ambas cosas.
/**
**/
void myplugin1::boton_nuevoasientodocumental()
{
    _depura ( "myplugin1::boton_nuevoasientodocumental", 10 );
    adocumental *adoc = new adocumental ( empresaactual, 0 );
    adoc->presentaprimervacio();
    Asiento1View *intapunts = empresaactual->intapuntsempresa();
    intapunts->iniciar_asiento_nuevo();
    adoc->asociaasiento ( intapunts->idasiento() );
    delete adoc;
    _depura ( "END myplugin1::boton_nuevoasientodocumental", 10 );
}


///
/**
**/
void myplugin1::boton_adjuntar()
{
    _depura ( "myplugin1::boton_adjuntar", 10 );
    adocumental *adoc = new adocumental ( empresaactual, 0 );
    adoc->setmodoconsulta();
    adoc->exec();
    /// Falta por resolver esta salvedad.
    Asiento1View *intapunts = empresaactual->intapuntsempresa();
    if ( intapunts->idasiento() != "-1" )
        adoc->asociaasiento ( intapunts->idasiento() );
    delete adoc;
    _depura ( "END myplugin1::boton_adjuntar", 10 );
}


/// Esta funcion se dispara para poner en marcha el archivo documental.
/// El archivo documental es una opcion mendiante la cual se pueden poner
/// junto a los asientos y otras entidades una serie de documentos ligados
/// como pueden ser PDF's, GIFS, archivos de sonido, etc.
/// La idea principal es que se pueda conectar un escaner y se puedan escanear
/// las imagenes de facturas para despues pasarlas.
/**
**/
void myplugin1::archDoc()
{
    _depura ( "myplugin1::archDoc", 10 );
    adocumental *adoc = new adocumental ( empresaactual, 0 );
    adoc->exec();
    delete adoc;
    _depura ( "END myplugin1::archDoc", 10 );
}


///
/**
\param emp
\param parent
**/
adocumental::adocumental ( BcCompany *emp, QWidget *parent )
        : QDialog ( parent )
{
    _depura ( "adocumental::adocumental", 10 );

    setupUi ( this );

    empresaactual = emp;
    dbConnection = emp->bdempresa();
    modo = 0;
    idadocumental = "";
    QString query;

    m_listado->setRowCount ( 0 );
    m_listado->setColumnCount ( 7 );

    QStringList cabecerasHorizontal;
    cabecerasHorizontal << _ ( "Id archivo documental" ) << _ ( "Id asiento" ) << _ ( "Descripcion" ) << _ ( "Fecha doc." ) << _ ( "Fecha asoc." ) << _ ( "Archivo" ) << _ ( "Asiento" );
    m_listado->setHorizontalHeaderLabels ( cabecerasHorizontal );

    m_listado->setColumnWidth ( COL_IDADOCUMENTAL, 200 );
    m_listado->setColumnWidth ( COL_IDASIENTO, 200 );
    m_listado->setColumnWidth ( COL_DESCRIPCIONADOCUMENTAL, 200 );
    m_listado->setColumnWidth ( COL_FECHAINTADOCUMENTAL, 50 );
    m_listado->setColumnWidth ( COL_FECHAASADOCUMENTAL, 50 );
    m_listado->setColumnWidth ( COL_ARCHIVOADOCUMENTAL, 250 );
    m_listado->setColumnWidth ( COL_ORDENASIENTO, 75 );

    m_listado->hideColumn ( COL_IDADOCUMENTAL );
    m_listado->hideColumn ( COL_IDASIENTO );
    m_listado->hideColumn ( COL_FECHAINTADOCUMENTAL );
    m_listado->hideColumn ( COL_FECHAASADOCUMENTAL );

    /// Iniciamos la presentacion.
    inicializa();
    _depura ( "END adocumental::adocumental", 10 );
}


///
/**
**/
adocumental::~adocumental()
{
    _depura ( "adocumental::~adocumental", 0 );
    _depura ( "END adocumental::~adocumental", 0 );
}


///
/**
**/
void adocumental::inicializa()
{
    _depura ( "adocumental::inicializa", 0 );
    QString query = "SELECT * FROM adocumental LEFT JOIN asiento ON adocumental.idasiento = asiento.idasiento ORDER BY ordenasiento";
    dbConnection->begin();
    BlDbRecordSet *cursoraux1 = dbConnection->loadQuery ( query, "elquery" );
    dbConnection->commit();
    m_listado->setRowCount ( cursoraux1->numregistros() );
    int i = 0;
    while ( !cursoraux1->eof() ) {
        QTableWidgetItem * nuevoItem0 = new QTableWidgetItem ( cursoraux1->valor ( "idadocumental" ) );
        m_listado->setItem ( i, COL_IDADOCUMENTAL, nuevoItem0 );
        QTableWidgetItem *nuevoItem1 = new QTableWidgetItem ( cursoraux1->valor ( "idasiento" ) );
        m_listado->setItem ( i, COL_IDASIENTO, nuevoItem1 );
        QTableWidgetItem *nuevoItem2 = new QTableWidgetItem ( cursoraux1->valor ( "descripcionadocumental" ) );
        m_listado->setItem ( i, COL_DESCRIPCIONADOCUMENTAL, nuevoItem2 );
        QTableWidgetItem *nuevoItem3 = new QTableWidgetItem ( cursoraux1->valor ( "fechaintadocumental" ) );
        m_listado->setItem ( i, COL_FECHAINTADOCUMENTAL, nuevoItem3 );
        QTableWidgetItem *nuevoItem4 = new QTableWidgetItem ( cursoraux1->valor ( "fechaasadocumental" ) );
        m_listado->setItem ( i, COL_FECHAASADOCUMENTAL, nuevoItem4 );
        QTableWidgetItem *nuevoItem5 = new QTableWidgetItem ( cursoraux1->valor ( "archivoadocumental" ) );
        m_listado->setItem ( i, COL_ARCHIVOADOCUMENTAL, nuevoItem5 );
        QTableWidgetItem *nuevoItem6 = new QTableWidgetItem ( cursoraux1->valor ( "ordenasiento" ) );
        m_listado->setItem ( i, COL_ORDENASIENTO, nuevoItem6 );
        cursoraux1->nextRecord();
        i++;
    } // end while
    delete cursoraux1;
    _depura ( "END adocumental::inicializa", 0 );
}


///
/**
\param row
**/
void adocumental::doubleclicked ( int row, int, int, const QPoint & )
{
    _depura ( "adocumental::doubleclicked", 0 );
    idadocumental = m_listado->item ( row, COL_IDADOCUMENTAL ) ->text();

    _depura ( "Archivo Documental: " + idadocumental, 10 );
    if ( modo == 0 ) { /// Es el modo edicion.
        QString archivo = m_listado->item ( row, COL_ARCHIVOADOCUMENTAL ) ->text();
        QString comando = "konqueror " + archivo + " &";
        system ( comando.toAscii().constData() );
    } else { /// Es el modo consulta.
        done ( 1 );
    } // end if
    _depura ( "END adocumental::doubleclicked", 0 );
}


///
/**
\param archivo
**/
void adocumental::newADocumental ( QString archivo )
{
    _depura ( "adocumental::newADocumental", 0 );
    QString SQLQuery = "INSERT INTO adocumental (archivoadocumental) VALUES ('" + dbConnection->sanearCadena ( archivo ) + "')";
    dbConnection->begin();
    dbConnection->runQuery ( SQLQuery );
    dbConnection->commit();
    _depura ( "END adocumental::newADocumental", 0 );
}


///
/**
\return
**/
void adocumental::boton_newadocumental()
{
    _depura ( "adocumental::boton_newadocumental", 0 );
    QString fn = QFileDialog::getOpenFileName ( this, _ ( "Elija el nombre del archivo" ),
                 g_confpr->valor ( CONF_DIR_USER ),
                 _ ( "Todos (*.*)" ) );

    if ( !fn.isEmpty() ) {
        newADocumental ( fn );
    } // end if
    inicializa();
    _depura ( "END adocumental::boton_newadocumental", 0 );
}


///
/**
\return
**/
inline QString adocumental::getidadocumental()
{
    _depura ( "adocumental::getidadocumental", 0 );
    _depura ( "END adocumental::getidadocumental", 0 );
    return ( idadocumental );
}


///
/**
\param idasiento
**/
void adocumental::asociaasiento ( QString idasiento )
{
    _depura ( "AsociaAsiento:", 10 );
    _depura ( "idasiento:" + idasiento  + ", idadocumental:" + idadocumental );
    if ( ( idadocumental != "" ) && ( idasiento != "" ) ) {
        QString SQLQuery = "UPDATE adocumental SET idasiento = " + idasiento + " WHERE idadocumental = " + idadocumental;
        _depura ( SQLQuery, 10 );
        dbConnection->begin();
        dbConnection->runQuery ( SQLQuery );
        dbConnection->commit();
    } // end if
    inicializa();
}


/// Esta funcion coge el primer archivo documental que no esta asociado a ningun asiento
/// y lo muestra asignando a idasiento su valor.
///
/**
**/
void adocumental::presentaprimervacio()
{
    _depura ( "adocumental::presentaprimervacio", 10 );
    int i = 0;
    while ( i < m_listado->rowCount() ) {
        if ( m_listado->item ( i, COL_IDASIENTO ) ->text() == "" ) {
            doubleclicked ( i, 0, 0, QPoint::QPoint ( 0, 0 ) );
        } // end if
        i++;
    } // end while
    _depura ( "END adocumental::presentaprimervacio", 10 );
}

///
/**
**/
void adocumental::boton_desasociar()
{
    _depura ( "adocumental::boton_desasociar", 0 );
    idadocumental = m_listado->item ( m_listado->currentRow(), COL_IDADOCUMENTAL ) ->text();
    if ( idadocumental != "" ) {
        QString SQLQuery = "UPDATE adocumental SET idasiento = NULL WHERE idadocumental = " + idadocumental;
        dbConnection->begin();
        dbConnection->runQuery ( SQLQuery );
        dbConnection->commit();
    } // end if
    inicializa();
    _depura ( "END adocumental::boton_desasociar", 0 );
}


///
/**
**/
void adocumental::s_deleteADocumental()
{
    _depura ( "adocumental::s_deleteADocumental", 0 );
    idadocumental = m_listado->item ( m_listado->currentRow(), COL_IDADOCUMENTAL ) ->text();
    if ( idadocumental != "" ) {
        QString SQLQuery = "DELETE FROM adocumental WHERE idadocumental = " + idadocumental;
        dbConnection->begin();
        dbConnection->runQuery ( SQLQuery );
        dbConnection->commit();
    } // end if
    inicializa();
    _depura ( "END adocumental::s_deleteADocumental", 0 );
}

///
/**
**/
void adocumental::s_saveADocumental()
{
    _depura ( "adocumental::s_saveADocumental", 0 );
    int row = m_listado->currentRow();
    idadocumental = m_listado->item ( row, COL_IDADOCUMENTAL ) ->text();
    if ( idadocumental != "" ) {
        QString Query;
        Query  = "UPDATE adocumental SET ";
        Query += "descripcionadocumental = '" + m_listado->item ( row, COL_DESCRIPCIONADOCUMENTAL ) ->text() + "'";
        Query += " WHERE idadocumental = " + idadocumental;
        dbConnection->begin();
        dbConnection->runQuery ( Query );
        dbConnection->commit();
    } // end if
    inicializa();
    _depura ( "END adocumental::s_saveADocumental", 0 );
}


///
/**
**/
void adocumental::s_agregarDirectorio()
{
    _depura ( "adocumental::s_agregarDirectorio", 0 );
    QString fn = QFileDialog::getExistingDirectory ( this, _ ( "Elija un directorio" ),
                 g_confpr->valor ( CONF_DIR_USER ),
                 QFileDialog::ShowDirsOnly
                 | QFileDialog::DontResolveSymlinks );

    QDir d ( fn );
    QFileInfoList list = d.entryInfoList();
    for ( int i = 0; i < list.size(); ++i ) {
        QFileInfo fileInfo = list.at ( i );
        newADocumental ( fileInfo.filePath() );
    } // end for

    inicializa();
    _depura ( "END adocumental::s_agregarDirectorio", 0 );
}
