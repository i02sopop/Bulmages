/***************************************************************************
 *   Copyright (C) 2003 by Tomeu Borras Riera                              *
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

#include <unistd.h>

#include "bcdiarioimprimir2txt.h"
#include "bccompany.h"


///
/**
\param emp
**/
BcDiarioImprimir2TXT::BcDiarioImprimir2TXT ( BcCompany  *emp ) : BlMainCompanyPointer ( emp )
{
    _depura ( "BcDiarioImprimir2TXT::BcDiarioImprimir2TXT", 0 );
    fichero = NULL;
    _depura ( "END BcDiarioImprimir2TXT::BcDiarioImprimir2TXT", 0 );
}


///
/**
**/
BcDiarioImprimir2TXT::~BcDiarioImprimir2TXT()
{
    _depura ( "BcDiarioImprimir2TXT::~BcDiarioImprimir2TXT", 0 );
    _depura ( "END BcDiarioImprimir2TXT::~BcDiarioImprimir2TXT", 0 );
}


///
/**
\param finicial1
\param ffinal1
**/
void BcDiarioImprimir2TXT::inicializa1 ( char *finicial1, char *ffinal1 )
{
    _depura ( "BcDiarioImprimir2TXT::inicializa1", 0 );
    finicial = finicial1;
    ffinal = ffinal1;
    _depura ( "BcDiarioImprimir2TXT::inicializa1", 0 );
}


///
/**
\param fich
**/
void BcDiarioImprimir2TXT::inicializa2 ( char *fich )
{
    _depura ( "BcDiarioImprimir2TXT::inicializa2", 0 );
    fichero = fich;
    _depura ( "BcDiarioImprimir2TXT::inicializa2", 0 );
}


/// Se ha pulsado sobre el bot&oacute;n aceptar del formulario.
/**
**/
void BcDiarioImprimir2TXT::accept()
{
    _depura ( "BcDiarioImprimir2TXT::accept", 0 );
    float debe, haber;
    int idcuenta;
    int idasiento;
    QString fecha;
    QString fechaasiento;
    QString descripcion;
    QString concepto;
    QString codigocuenta;
    QString cad;
    BlDbRecordSet *cursoraux, *cursoraux1, *cursoraux2;

    FILE *mifile;
    mifile = fopen ( "diario.txt", "wt" );
    if ( mifile != NULL ) {
        fprintf ( mifile, "Fecha Inicial: %s, Fecha Final: %s\n", finicial, ffinal );
        fprintf ( mifile, "%5.5s %10.10s %10s %30.30s %9.2s %9.2s\n", "ASIENTO", "FECHA", "SUBCUENTA", "DESCRIPCION", "DEBE", "HABER" );
        fprintf ( mifile, "----------------------------------------------------------------------------------------------------------\n" );
        mainCompany() ->begin();
        cursoraux = mainCompany() -> loadQuery ( "SELECT * FROM asiento WHERE fecha >= '" + QString ( finicial ) + "' AND fecha <= '" + QString ( ffinal ) + "' ORDER BY fecha" );
        for ( ; !cursoraux->eof(); cursoraux->nextRecord() ) {
            fechaasiento = cursoraux->valor ( "fechaasiento" ).toAscii().constData();
            idasiento = atoi ( cursoraux->valor ( "idasiento" ).toAscii() );
            cursoraux1 = mainCompany() ->loadQuery ( "SELECT * FROM apunte where idasiento = " + cursoraux->valor ( "idasiento" ) + " ORDER BY idapunte" );
            for ( ; !cursoraux1->eof(); cursoraux1->nextRecord() ) {
                fecha = cursoraux1->valor ( 4 ).toAscii().constData();
                descripcion = cursoraux1->valor ( 5 ).toAscii().constData();
                concepto = cursoraux->valor ( 1 ).toAscii().constData();
                debe = atof ( cursoraux1->valor ( 8 ).toAscii() );
                haber = atof ( cursoraux1->valor ( 9 ).toAscii() );
                idcuenta = atoi ( cursoraux1->valor ( "idcuenta" ).toAscii() );

                cursoraux2 = mainCompany() ->loadQuery ( "SELECT * FROM cuenta WHERE idcuenta = " + cursoraux1->valor ( "idcuenta" ) );

                if ( !cursoraux2->eof() ) {
                    codigocuenta = cursoraux2->valor ( "codigo" ).toAscii().constData();
                } // end if
                cursoraux2->cerrar();
                delete cursoraux2;
                fprintf ( mifile, "%5d %-10.10s %10s %-30.30s %9.2f %9.2f\n", idasiento, fecha.toAscii().data(), codigocuenta.toAscii().data(), descripcion.toAscii().data(), debe, haber );
            } // end for
            cursoraux1->cerrar();
            delete cursoraux1;
            fprintf ( mifile, "\n" );
        } // end for
        delete cursoraux;
        mainCompany() ->commit();
        fclose ( mifile );
    } // end if

    /// Hacemos la llamada de sistema para imprimir.
    QString cadaux = g_confpr->valor ( CONF_EDITOR ) + " diario.txt";
    system ( cadaux.toAscii().constData() );
    _depura ( "END BcDiarioImprimir2TXT::accept", 0 );
}
