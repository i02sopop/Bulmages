/***************************************************************************
 *   Copyright (C) 2008 by Ricardo Diaz de la Calle <richard@galdi.es>     *
 *   Copyright (C) 2008 by Adelaida Clavaguera Mora <laida@alaxarxa.net>   *
 *   Copyright (C) 2008 by Leopold Palomo Avellaneda <leo@alaxarxa.net>    *
 *   Copyright (C) 2006 by Fco. Javier M. C. >fcojavmc@todo-redes.com>     *
 *   Copyright (C) 2005 by Tomeu Borras Riera <tborras@conetxia.com>       *
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

#include <QtCore/QString>
#include "pluginbc_cuentasanuales2ods.h"
#include "blprogressbar.h"

///
/**
**/
QString PluginBc_CuentasAnuales2ODS::cuentaAnualCAPGC07()
{
    BlProgressBar barra;
    barra.setRange ( 0, 21 );
    barra.setValue ( 0 );
    barra.show();
    barra.setText ( _ ( "Calculando Balance y Resultados" ) );

    QString ejercicioActual = ejercicioActual_fechaBalance.right ( 4 );
    QString ejercicioAnterior = ejercicioAnterior_fechaBalance.right ( 4 );
    QList <QString> meses; // Para poder indexar los meses de ejercicio segun la fecha pasada
    meses  << _ ( "Enero" ) << _ ( "Febrero" ) << _ ( "Marzo" ) << _ ( "Abril" ) << _ ( "Mayo" ) << _ ( "Junio" ) << _ ( "Julio" ) << _ ( "Agosto" ) << _ ( "Septiembre" ) << _ ( "Octubre" ) << _ ( "Noviembre" ) << _ ( "Diciembre" );
    unsigned int mesInicio = 0;
    unsigned int mesFin = ejercicioActual_fechaBalance.mid ( 3, 2 ).toInt() - 1;

    QString codigoPython = QString ( "\
#!/usr/bin/python\n\
# -*- coding: utf8 -*-\n\
\n\
import ooolib\n\
\n\
# Crea el documento\n\
doc = ooolib.Calc(\"Activo\")\n\
\n\
doc.set_column_property(1, 'width', '0.5in')\n\
doc.set_column_property(2, 'width', '5in')\n\
doc.set_cell_property('bold', True)\n\
doc.set_cell_value(2, 2, 'string', 'BALANCE DE SITUACIÓN')\n\
doc.set_cell_value(2, 3, 'string', '" + QDateTime::currentDateTime().toString() + "')\n\
doc.set_cell_value(4, 2, 'string', 'ACTIVO')\n\
doc.set_cell_value(2, 5, 'string', 'Periodo: de " + meses.at ( mesInicio ) + " a " + meses.at ( mesFin ) + "')\n\
doc.set_cell_value(3, 5, 'string', '" + ejercicioActual + "')\n\
doc.set_cell_value(4, 5, 'string', '" + ejercicioAnterior + "')\n\
doc.set_cell_property('bold', False)\n\
\
doc.set_cell_property('bold', True)\n\
doc.set_cell_value(2, 7, 'string', 'A) Accionistas (socios) por desembolsos no exigidos')\n\
doc.set_cell_value(3, 7, 'float', '" + ( saldoCuenta ( 190 ) + saldoCuenta ( 191 ) + saldoCuenta ( 192 ) + saldoCuenta ( 193 ) + saldoCuenta ( 194 ) + saldoCuenta ( 195 ) + saldoCuenta ( 196 ) ).toQString ( '.' ) + "')\n\
doc.set_cell_value(4, 7, 'float', '" + ( saldoCuentaAnt ( 190 ) + saldoCuentaAnt ( 191 ) + saldoCuentaAnt ( 192 ) + saldoCuentaAnt ( 193 ) + saldoCuentaAnt ( 194 ) + saldoCuentaAnt ( 195 ) + saldoCuentaAnt ( 196 ) ).toQString ( '.' ) + "')\n\
doc.set_cell_property('bold', False)\n\
" );

                                     barra.setValue ( barra.value() + 1 );

                                     codigoPython.append ( "\
                                     \
                                     doc.set_cell_property ( 'bold', True ) \n\
                                     doc.set_cell_value ( 2, 9, 'string', 'B) Inmovilizado' ) \n\
                                     doc.set_cell_value ( 3, 9, 'formula', '=C10+C11+C21+C29+C38' ) \n\
                                     doc.set_cell_value ( 4, 9, 'formula', '=D10+D11+D21+D29+D38' ) \n\
                                     doc.set_cell_property ( 'bold', False ) \n\
                                     doc.set_cell_value ( 2, 10, 'string', '   I.   Gastos de establecimiento' ) \n\
                                     doc.set_cell_value ( 3, 10, 'float', '" + saldoCuenta ( 20 ).toQString ( '.' ) + "' ) \n\
                                     doc.set_cell_value ( 4, 10, 'float', '" + saldoCuentaAnt ( 20 ).toQString ( '.' ) + "' ) \n\
                                     \
                                     doc.set_cell_value ( 2, 11, 'string', '   II.  Inmovilizaciones inmateriales' ) \n\
                                     doc.set_cell_value ( 3, 11, 'formula', '=SUM(C12:C20)' ) \n\
                                     doc.set_cell_value ( 4, 11, 'formula', '=SUM(D12:D20)' ) \n\
                                     \
                                     doc.set_cell_value ( 2, 12, 'string', '       1. Gastos de investigacion y desarrollo' ) \n\
                                     doc.set_cell_value ( 3, 12, 'float', '" + saldoCuenta ( 210 ).toQString ( '.' ) + "' ) \n\
                                     doc.set_cell_value ( 4, 12, 'float', '" + saldoCuentaAnt ( 210 ).toQString ( '.' ) + "' ) \n\
                                     \
                                     doc.set_cell_value ( 2, 13, 'string', '       2. Concesiones, patentes, licencias, marcas y similares' ) \n\
                                     doc.set_cell_value ( 3, 13, 'float', '" + ( saldoCuenta ( 211 ) + saldoCuenta ( 212 ) ).toQString ( '.' ) + "' ) \n\
                                     doc.set_cell_value ( 4, 13, 'float', '" + ( saldoCuentaAnt ( 211 ) + saldoCuentaAnt ( 212 ) ).toQString ( '.' ) + "' ) \n\
                                     \
                                     doc.set_cell_value ( 2, 14, 'string', '       3. Fondo de comercio' ) \n\
                                     doc.set_cell_value ( 3, 14, 'float', '" + saldoCuenta ( 213 ).toQString ( '.' ) + "' ) \n\
                                     doc.set_cell_value ( 4, 14, 'float', '" + saldoCuentaAnt ( 213 ).toQString ( '.' ) + "' ) \n\
                                     \
                                     doc.set_cell_value ( 2, 15, 'string', '       4. Derechos de traspaso' ) \n\
                                     doc.set_cell_value ( 3, 15, 'float', '" + saldoCuenta ( 214 ).toQString ( '.' ) + "' ) \n\
                                     doc.set_cell_value ( 4, 15, 'float', '" + saldoCuentaAnt ( 214 ).toQString ( '.' ) + "' ) \n\
                                     \
                                     doc.set_cell_value ( 2, 16, 'string', '       5. Aplicaciones informaticas' ) \n\
                                     doc.set_cell_value ( 3, 16, 'float', '" + saldoCuenta ( 215 ).toQString ( '.' ) + "' ) \n\
                                     doc.set_cell_value ( 4, 16, 'float', '" + saldoCuentaAnt ( 215 ).toQString ( '.' ) + "' ) \n\
                                     \
                                     doc.set_cell_value ( 2, 17, 'string', '       6. Anticipos para inmovilizaciones inmateriales' ) \n\
                                     doc.set_cell_value ( 3, 17, 'float', '" + saldoCuenta ( 219 ).toQString ( '.' ) + "' ) \n\
                                     doc.set_cell_value ( 4, 17, 'float', '" + saldoCuentaAnt ( 219 ).toQString ( '.' ) + "' ) \n\
                                     \
                                     doc.set_cell_value ( 2, 18, 'string', '       7. Provisiones' ) \n\
                                     doc.set_cell_value ( 3, 18, 'float', '" + saldoCuenta ( 291 ).toQString ( '.' ) + "' ) \n\
                                     doc.set_cell_value ( 4, 18, 'float', '" + saldoCuentaAnt ( 291 ).toQString ( '.' ) + "' ) \n\
                                     \
                                     doc.set_cell_value ( 2, 19, 'string', '       8. Derechos sobre bienes en regimen de arrendamiento financiero' ) \n\
                                     doc.set_cell_value ( 3, 19, 'float', '" + saldoCuenta ( 217 ).toQString ( '.' ) + "' ) \n\
                                     doc.set_cell_value ( 4, 19, 'float', '" + saldoCuentaAnt ( 217 ).toQString ( '.' ) + "' ) \n\
                                     \
                                     \
                                     doc.set_cell_value ( 2, 20, 'string', '       9. Amortizaciones' ) \n\
                                     doc.set_cell_value ( 3, 20, 'float', '" + saldoCuenta ( 281 ).toQString ( '.' ) + "' ) \n\
                                     doc.set_cell_value ( 4, 20, 'float', '" + saldoCuentaAnt ( 281 ).toQString ( '.' ) + "' ) \n\
                                     \
                                     doc.set_cell_value ( 2, 21, 'string', '   III. Inmovilizaciones materiales' ) \n\
                                     doc.set_cell_value ( 3, 21, 'formula', '=SUM(C22:C28)' ) \n\
                                     doc.set_cell_value ( 4, 21, 'formula', '=SUM(D22:D28)' ) \n\
                                     \
                                     doc.set_cell_value ( 2, 22, 'string', '       1. Terrenos y construcciones' ) \n\
                                     doc.set_cell_value ( 3, 22, 'float', '" + ( saldoCuenta ( 220 ) + saldoCuenta ( 221 ) ).toQString ( '.' ) + "' ) \n\
                                     doc.set_cell_value ( 4, 22, 'float', '" + ( saldoCuentaAnt ( 220 ) + saldoCuentaAnt ( 221 ) ).toQString ( '.' ) + "' ) \n\
                                     \
                                     doc.set_cell_value ( 2, 23, 'string', '       2. Instalaciones tecnicas y maquinaria' ) \n\
                                     doc.set_cell_value ( 3, 23, 'float', '" + ( saldoCuenta ( 222 ) + saldoCuenta ( 223 ) ).toQString ( '.' ) + "' ) \n\
                                     doc.set_cell_value ( 4, 23, 'float', '" + ( saldoCuentaAnt ( 222 ) + saldoCuentaAnt ( 223 ) ).toQString ( '.' ) + "' ) \n\
                                     \
                                     doc.set_cell_value ( 2, 24, 'string', '       3. Otras instalaciones, utillaje y mobiliario' ) \n\
                                     doc.set_cell_value ( 3, 24, 'float', '" + ( saldoCuenta ( 224 ) + saldoCuenta ( 225 ) + saldoCuenta ( 226 ) ).toQString ( '.' ) + "' ) \n\
                                     doc.set_cell_value ( 4, 24, 'float', '" + ( saldoCuentaAnt ( 224 ) + saldoCuentaAnt ( 225 ) + saldoCuentaAnt ( 226 ) ).toQString ( '.' ) + "' ) \n\
                                     \
                                     doc.set_cell_value ( 2, 25, 'string', '       4. Anticipos e inmovilizaciones materiales en curso' ) \n\
                                     doc.set_cell_value ( 3, 25, 'float', '" + saldoCuenta ( 23 ).toQString ( '.' ) + "' ) \n\
                                     doc.set_cell_value ( 4, 25, 'float', '" + saldoCuentaAnt ( 23 ).toQString ( '.' ) + "' ) \n\
                                     \
                                     doc.set_cell_value ( 2, 26, 'string', '       5. Otro inmobilizado' ) \n\
                                     doc.set_cell_value ( 3, 26, 'float', '" + ( saldoCuenta ( 227 ) + saldoCuenta ( 228 ) + saldoCuenta ( 229 ) ).toQString ( '.' ) + "' ) \n\
                                     doc.set_cell_value ( 4, 26, 'float', '" + ( saldoCuentaAnt ( 227 ) + saldoCuentaAnt ( 228 ) + saldoCuentaAnt ( 229 ) ).toQString ( '.' ) + "' ) \n\
                                     \
                                     doc.set_cell_value ( 2, 27, 'string', '       6. Provisiones' ) \n\
                                     doc.set_cell_value ( 3, 27, 'float', '" + saldoCuenta ( 292 ).toQString ( '.' ) + "' ) \n\
                                     doc.set_cell_value ( 4, 27, 'float', '" + saldoCuentaAnt ( 292 ).toQString ( '.' ) + "' ) \n\
                                     \
                                     doc.set_cell_value ( 2, 28, 'string', '       7. Amortizaciones' ) \n\
                                     doc.set_cell_value ( 3, 28, 'float', '" + saldoCuenta ( 282 ).toQString ( '.' ) + "' ) \n\
                                     doc.set_cell_value ( 4, 28, 'float', '" + saldoCuentaAnt ( 282 ).toQString ( '.' ) + "' ) \n\
                                     \
                                     doc.set_cell_value ( 2, 29, 'string', '   IV.  Inmovilizaciones financieras' ) \n\
                                     doc.set_cell_value ( 3, 29, 'formula', '=SUM(C30:C37)' ) \n\
                                     doc.set_cell_value ( 4, 29, 'formula', '=SUM(D30:D37)' ) \n\
                                     \
                                     doc.set_cell_value ( 2, 30, 'string', '       1. Participaciones en empresas del grupo' ) \n\
                                     doc.set_cell_value ( 3, 30, 'float', '" + saldoCuenta ( 240 ).toQString ( '.' ) + "' ) \n\
                                     doc.set_cell_value ( 4, 30, 'float', '" + saldoCuentaAnt ( 240 ).toQString ( '.' ) + "' ) \n\
                                     \
                                     doc.set_cell_value ( 2, 31, 'string', '       2. Creditos a empresas del grupo' ) \n\
                                     doc.set_cell_value ( 3, 31, 'float', '" + ( saldoCuenta ( 242 ) + saldoCuenta ( 244 ) + saldoCuenta ( 246 ) ).toQString ( '.' ) + "' ) \n\
                                     doc.set_cell_value ( 4, 31, 'float', '" + ( saldoCuentaAnt ( 242 ) + saldoCuentaAnt ( 244 ) + saldoCuentaAnt ( 246 ) ).toQString ( '.' ) + "' ) \n\
                                     \
                                     doc.set_cell_value ( 2, 32, 'string', '       3. Participaciones en empresas asociadas' ) \n\
                                     doc.set_cell_value ( 3, 32, 'float', '" + saldoCuenta ( 241 ).toQString ( '.' ) + "' ) \n\
                                     doc.set_cell_value ( 4, 32, 'float', '" + saldoCuentaAnt ( 241 ).toQString ( '.' ) + "' ) \n\
                                     \
                                     doc.set_cell_value ( 2, 33, 'string', '       4. Creditos a empresas asociadas' ) \n\
                                     doc.set_cell_value ( 3, 33, 'float', '" + ( saldoCuenta ( 243 ) + saldoCuenta ( 245 ) + saldoCuenta ( 247 ) ).toQString ( '.' ) + "' ) \n\
                                     doc.set_cell_value ( 4, 33, 'float', '" + ( saldoCuentaAnt ( 243 ) + saldoCuentaAnt ( 245 ) + saldoCuentaAnt ( 247 ) ).toQString ( '.' ) + "' ) \n\
                                     \
                                     doc.set_cell_value ( 2, 34, 'string', '       5. Cartera de valores a largo plazo' ) \n\
                                     doc.set_cell_value ( 3, 34, 'float', '" + ( saldoCuenta ( 250 ) + saldoCuenta ( 251 ) + saldoCuenta ( 256 ) ).toQString ( '.' ) + "' ) \n\
                                     doc.set_cell_value ( 4, 34, 'float', '" + ( saldoCuentaAnt ( 250 ) + saldoCuentaAnt ( 251 ) + saldoCuentaAnt ( 256 ) ).toQString ( '.' ) + "' ) \n\
                                     \
                                     doc.set_cell_value ( 2, 35, 'string', '       6. Otros creditos' ) \n\
                                     doc.set_cell_value ( 3, 35, 'float', '" + ( saldoCuenta ( 252 ) + saldoCuenta ( 253 ) + saldoCuenta ( 254 ) + saldoCuenta ( 257 ) + saldoCuenta ( 258 ) ).toQString ( '.' ) + "' ) \n\
                                     doc.set_cell_value ( 4, 35, 'float', '" + ( saldoCuentaAnt ( 252 ) + saldoCuentaAnt ( 253 ) + saldoCuentaAnt ( 254 ) + saldoCuentaAnt ( 257 ) + saldoCuentaAnt ( 258 ) ).toQString ( '.' ) + "' ) \n\
                                     \
                                     doc.set_cell_value ( 2, 36, 'string', '       7. Depositos y fianzas constituidos a largo plazo' ) \n\
                                     doc.set_cell_value ( 3, 36, 'float', '" + ( saldoCuenta ( 260 ) + saldoCuenta ( 265 ) ).toQString ( '.' ) + "' ) \n\
                                     doc.set_cell_value ( 4, 36, 'float', '" + ( saldoCuentaAnt ( 260 ) + saldoCuentaAnt ( 265 ) ).toQString ( '.' ) + "' ) \n\
                                     \
                                     doc.set_cell_value ( 2, 37, 'string', '       8. Provisiones' ) \n\
                                     doc.set_cell_value ( 3, 37, 'float', '" + ( ( saldoCuenta ( 293 ) ) + ( saldoCuenta ( 294 ) ) + ( saldoCuenta ( 295 ) ) + ( saldoCuenta ( 296 ) ) + ( saldoCuenta ( 297 ) ) + ( saldoCuenta ( 298 ) ) ).toQString ( '.' ) + "' ) \n\
                                     doc.set_cell_value ( 4, 37, 'float', '" + ( ( saldoCuentaAnt ( 293 ) ) + ( saldoCuentaAnt ( 294 ) ) + ( saldoCuentaAnt ( 295 ) ) + ( saldoCuentaAnt ( 296 ) ) + ( saldoCuentaAnt ( 297 ) ) + ( saldoCuentaAnt ( 298 ) ) ).toQString ( '.' ) + "' ) \n\
                                     \
                                     doc.set_cell_value ( 2, 38, 'string', '   V.   Acciones propias' ) \n\
                                     doc.set_cell_value ( 3, 38, 'float', '" + saldoCuenta ( 198 ).toQString ( '.' ) + "' ) \n\
                                     doc.set_cell_value ( 4, 38, 'float', '" + saldoCuentaAnt ( 198 ).toQString ( '.' ) + "' ) \n\
                                     \
                                     " );

                                     barra.setValue ( barra.value() + 1 );

                                     codigoPython.append ( "\
                                     \
                                     doc.set_cell_property ( 'bold', True ) \n\
                                     doc.set_cell_value ( 2, 40, 'string', 'C) Gastos a distribuir en varios ejercicios' ) \n\
                                     doc.set_cell_value ( 3, 40, 'float', '" + saldoCuenta ( 27 ).toQString ( '.' ) + "' ) \n\
                                     doc.set_cell_value ( 4, 40, 'float', '" + saldoCuentaAnt ( 27 ).toQString ( '.' ) + "' ) \n\
                                     doc.set_cell_property ( 'bold', False ) \n\
                                     " );

                                     barra.setValue ( barra.value() + 1 );

                                     codigoPython.append ( "\
                                     \
                                     doc.set_cell_property ( 'bold', True ) \n\
                                     doc.set_cell_value ( 2, 42, 'string', 'D) Activo circulante' ) \n\
                                     doc.set_cell_value ( 3, 42, 'formula', '=C43+C44+C52+C60+C69+C70+C71' ) \n\
                                     doc.set_cell_value ( 4, 42, 'formula', '=D43+D44+D52+D60+D69+D70+D71' ) \n\
                                     doc.set_cell_property ( 'bold', False ) \n\
                                     \
                                     doc.set_cell_value ( 2, 43, 'string', '   I.   Accionistas por desembolsos exigidos' ) \n\
                                     doc.set_cell_value ( 3, 43, 'float', '" + saldoCuenta ( 558 ).toQString ( '.' ) + "' ) \n\
                                     doc.set_cell_value ( 4, 43, 'float', '" + saldoCuentaAnt ( 558 ).toQString ( '.' ) + "' ) \n\
                                     \
                                     doc.set_cell_value ( 2, 44, 'string', '   II.  Existencias' ) \n\
                                     doc.set_cell_value ( 3, 44, 'formula', '=SUM(C45:C51)' ) \n\
                                     doc.set_cell_value ( 4, 44, 'formula', '=SUM(D45:D51)' ) \n\
                                     \
                                     doc.set_cell_value ( 2, 45, 'string', '       1. Comerciales' ) \n\
                                     doc.set_cell_value ( 3, 45, 'float', '" + saldoCuenta ( 30 ).toQString ( '.' ) + "' ) \n\
                                     doc.set_cell_value ( 4, 45, 'float', '" + saldoCuentaAnt ( 30 ).toQString ( '.' ) + "' ) \n\
                                     \
                                     doc.set_cell_value ( 2, 46, 'string', '       2. Materias primas y otros aprovisionamientos' ) \n\
                                     doc.set_cell_value ( 3, 46, 'float', '" + ( saldoCuenta ( 31 ) + saldoCuenta ( 32 ) ).toQString ( '.' ) + "' ) \n\
                                     doc.set_cell_value ( 4, 46, 'float', '" + ( saldoCuentaAnt ( 31 ) + saldoCuentaAnt ( 32 ) ).toQString ( '.' ) + "' ) \n\
                                     \
                                     doc.set_cell_value ( 2, 47, 'string', '       3. Productos en curso y semiterminados' ) \n\
                                     doc.set_cell_value ( 3, 47, 'float', '" + ( saldoCuenta ( 33 ) + saldoCuenta ( 34 ) ).toQString ( '.' ) + "' ) \n\
                                     doc.set_cell_value ( 4, 47, 'float', '" + ( saldoCuentaAnt ( 33 ) + saldoCuentaAnt ( 34 ) ).toQString ( '.' ) + "' ) \n\
                                     \
                                     doc.set_cell_value ( 2, 48, 'string', '       4. Productos terminados' ) \n\
                                     doc.set_cell_value ( 3, 48, 'float', '" + saldoCuenta ( 35 ).toQString ( '.' ) + "' ) \n\
                                     doc.set_cell_value ( 4, 48, 'float', '" + saldoCuentaAnt ( 35 ).toQString ( '.' ) + "' ) \n\
                                     \
                                     doc.set_cell_value ( 2, 49, 'string', '       5. Subproductos, residuos y materiales recuperados' ) \n\
                                     doc.set_cell_value ( 3, 49, 'float', '" + saldoCuenta ( 36 ).toQString ( '.' ) + "' ) \n\
                                     doc.set_cell_value ( 4, 49, 'float', '" + saldoCuentaAnt ( 36 ).toQString ( '.' ) + "' ) \n\
                                     \
                                     doc.set_cell_value ( 2, 50, 'string', '       6. Anticipos' ) \n\
                                     doc.set_cell_value ( 3, 50, 'float', '" + saldoCuenta ( 407 ).toQString ( '.' ) + "' ) \n\
                                     doc.set_cell_value ( 4, 50, 'float', '" + saldoCuentaAnt ( 407 ).toQString ( '.' ) + "' ) \n\
                                     \
                                     doc.set_cell_value ( 2, 51, 'string', '       7. Provisiones' ) \n\
                                     doc.set_cell_value ( 3, 51, 'float', '" + ( saldoCuenta ( 39 ) ).toQString ( '.' ) + "' ) \n\
                                     doc.set_cell_value ( 4, 51, 'float', '" + ( saldoCuentaAnt ( 39 ) ).toQString ( '.' ) + "' ) \n\
                                     \
                                     doc.set_cell_value ( 2, 52, 'string', '   III. Deudores' ) \n\
                                     doc.set_cell_value ( 3, 52, 'formula', '=SUM(C53:C59)' ) \n\
                                     doc.set_cell_value ( 4, 52, 'formula', '=SUM(D53:D59)' ) \n\
                                     \
                                     doc.set_cell_value ( 2, 53, 'string', '       1. Clientes por ventas y prestaciones de servicios' ) \n\
                                     doc.set_cell_value ( 3, 53, 'float', '" + ( saldoCuenta ( 430 ) + saldoCuenta ( 431 ) + saldoCuenta ( 435 ) - saldoCuenta ( 436 ) ).toQString ( '.' ) + "' ) \n\
                                     doc.set_cell_value ( 4, 53, 'float', '" + ( saldoCuentaAnt ( 430 ) + saldoCuentaAnt ( 431 ) + saldoCuentaAnt ( 435 ) - saldoCuentaAnt ( 436 ) ).toQString ( '.' ) + "' ) \n\
                                     \
                                     doc.set_cell_value ( 2, 54, 'string', '       2. Empresas del grupo, deudores' ) \n\
                                     doc.set_cell_value ( 3, 54, 'float', '" + ( saldoCuenta ( 432 ) + saldoCuenta ( 551 ) ).toQString ( '.' ) + "' ) \n\
                                     doc.set_cell_value ( 4, 54, 'float', '" + ( saldoCuentaAnt ( 432 ) + saldoCuentaAnt ( 551 ) ).toQString ( '.' ) + "' ) \n\
                                     \
                                     doc.set_cell_value ( 2, 55, 'string', '       3. Empresas asociadas, deudores' ) \n\
                                     doc.set_cell_value ( 3, 55, 'float', '" + ( saldoCuenta ( 433 ) + saldoCuenta ( 552 ) ).toQString ( '.' ) + "' ) \n\
                                     doc.set_cell_value ( 4, 55, 'float', '" + ( saldoCuentaAnt ( 433 ) + saldoCuentaAnt ( 552 ) ).toQString ( '.' ) + "' ) \n\
                                     \
                                     doc.set_cell_value ( 2, 56, 'string', '       4. Deudores varios' ) \n\
                                     doc.set_cell_value ( 3, 56, 'float', '" + ( saldoCuenta ( 44 ) + saldoCuenta ( 553 ) ).toQString ( '.' ) + "' ) \n\
                                     doc.set_cell_value ( 4, 56, 'float', '" + ( saldoCuentaAnt ( 44 ) + saldoCuentaAnt ( 553 ) ).toQString ( '.' ) + "' ) \n\
                                     \
                                     doc.set_cell_value ( 2, 57, 'string', '       5. Personal' ) \n\
                                     doc.set_cell_value ( 3, 57, 'float', '" + ( saldoCuenta ( 460 ) + saldoCuenta ( 544 ) ).toQString ( '.' ) + "' ) \n\
                                     doc.set_cell_value ( 4, 57, 'float', '" + ( saldoCuentaAnt ( 460 ) + saldoCuentaAnt ( 544 ) ).toQString ( '.' ) + "' ) \n\
                                     \
                                     doc.set_cell_value ( 2, 58, 'string', '       6. Administraciones Publicas' ) \n\
                                     doc.set_cell_value ( 3, 58, 'float', '" + ( saldoCuenta ( 470 ) + saldoCuenta ( 471 ) + saldoCuenta ( 472 ) + saldoCuenta ( 473 ) + saldoCuenta ( 474 ) ).toQString ( '.' ) + "' ) \n\
                                     doc.set_cell_value ( 4, 58, 'float', '" + ( saldoCuentaAnt ( 470 ) + saldoCuentaAnt ( 471 ) + saldoCuentaAnt ( 472 ) + saldoCuentaAnt ( 473 ) + saldoCuentaAnt ( 474 ) ).toQString ( '.' ) + "' ) \n\
                                     \
                                     doc.set_cell_value ( 2, 59, 'string', '       7. Provisiones' ) \n\
                                     doc.set_cell_value ( 3, 59, 'float', '" + ( ( saldoCuenta ( 490 ) ) + ( saldoCuenta ( 493 ) ) + ( saldoCuenta ( 494 ) ) ).toQString ( '.' ) + "' ) \n\
                                     doc.set_cell_value ( 4, 59, 'float', '" + ( ( saldoCuentaAnt ( 490 ) ) + ( saldoCuentaAnt ( 493 ) ) + ( saldoCuentaAnt ( 494 ) ) ).toQString ( '.' ) + "' ) \n\
                                     \
                                     doc.set_cell_value ( 2, 60, 'string', '   IV.  Inversiones financieras temporales' ) \n\
                                     doc.set_cell_value ( 3, 60, 'formula', '=SUM(C61:C68)' ) \n\
                                     doc.set_cell_value ( 4, 60, 'formula', '=SUM(D61:D68)' ) \n\
                                     \
                                     doc.set_cell_value ( 2, 61, 'string', '       1. Participaciones en empresas del grupo' ) \n\
                                     doc.set_cell_value ( 3, 61, 'float', '" + ( saldoCuenta ( 530 ) + ( saldoCuenta ( 538 ) ) ).toQString ( '.' ) + "' ) \n\
                                     doc.set_cell_value ( 4, 61, 'float', '" + ( saldoCuentaAnt ( 530 ) + ( saldoCuentaAnt ( 538 ) ) ).toQString ( '.' ) + "' ) \n\
                                     \
                                     doc.set_cell_value ( 2, 62, 'string', '       2. Creditos a empresas del grupo' ) \n\
                                     doc.set_cell_value ( 3, 62, 'float', '" + ( saldoCuenta ( 532 ) + saldoCuenta ( 534 ) + saldoCuenta ( 536 ) ).toQString ( '.' ) + "' ) \n\
                                     doc.set_cell_value ( 4, 62, 'float', '" + ( saldoCuentaAnt ( 532 ) + saldoCuentaAnt ( 534 ) + saldoCuentaAnt ( 536 ) ).toQString ( '.' ) + "' ) \n\
                                     \
                                     doc.set_cell_value ( 2, 63, 'string', '       3. Participaciones en empresas asociadas' ) \n\
                                     doc.set_cell_value ( 3, 63, 'float', '" + ( saldoCuenta ( 531 ) + ( saldoCuenta ( 539 ) ) ).toQString ( '.' ) + "' ) \n\
                                     doc.set_cell_value ( 4, 63, 'float', '" + ( saldoCuentaAnt ( 531 ) + ( saldoCuentaAnt ( 539 ) ) ).toQString ( '.' ) + "' ) \n\
                                     \
                                     doc.set_cell_value ( 2, 64, 'string', '       4. Creditos a empresas asociadas' ) \n\
                                     doc.set_cell_value ( 3, 64, 'float', '" + ( saldoCuenta ( 533 ) + saldoCuenta ( 535 ) + saldoCuenta ( 537 ) ).toQString ( '.' ) + "' ) \n\
                                     doc.set_cell_value ( 4, 64, 'float', '" + ( saldoCuentaAnt ( 533 ) + saldoCuentaAnt ( 535 ) + saldoCuentaAnt ( 537 ) ).toQString ( '.' ) + "' ) \n\
                                     \
                                     doc.set_cell_value ( 2, 65, 'string', '       5. Cartera de valores a corto plazo' ) \n\
                                     doc.set_cell_value ( 3, 65, 'float', '" + ( saldoCuenta ( 540 ) + saldoCuenta ( 541 ) + saldoCuenta ( 546 ) + ( saldoCuenta ( 549 ) ) ).toQString ( '.' ) + "' ) \n\
                                     doc.set_cell_value ( 4, 65, 'float', '" + ( saldoCuentaAnt ( 540 ) + saldoCuentaAnt ( 541 ) + saldoCuentaAnt ( 546 ) + ( saldoCuentaAnt ( 549 ) ) ).toQString ( '.' ) + "' ) \n\
                                     \
                                     doc.set_cell_value ( 2, 66, 'string', '       6. Otros creditos' ) \n\
                                     doc.set_cell_value ( 3, 66, 'float', '" + ( saldoCuenta ( 542 ) + saldoCuenta ( 543 ) + saldoCuenta ( 545 ) + saldoCuenta ( 547 ) + saldoCuenta ( 548 ) ).toQString ( '.' ) + "' ) \n\
                                     doc.set_cell_value ( 4, 66, 'float', '" + ( saldoCuentaAnt ( 542 ) + saldoCuentaAnt ( 543 ) + saldoCuentaAnt ( 545 ) + saldoCuentaAnt ( 547 ) + saldoCuentaAnt ( 548 ) ).toQString ( '.' ) + "' ) \n\
                                     \
                                     doc.set_cell_value ( 2, 67, 'string', '       7. Depositos y fianzas constituidos a corto plazo' ) \n\
                                     doc.set_cell_value ( 3, 67, 'float', '" + ( saldoCuenta ( 565 ) + saldoCuenta ( 566 ) ).toQString ( '.' ) + "' ) \n\
                                     doc.set_cell_value ( 4, 67, 'float', '" + ( saldoCuentaAnt ( 565 ) + saldoCuentaAnt ( 566 ) ).toQString ( '.' ) + "' ) \n\
                                     \
                                     doc.set_cell_value ( 2, 68, 'string', '       8. Provisiones' ) \n\
                                     doc.set_cell_value ( 3, 68, 'float', '" + ( ( saldoCuenta ( 593 ) ) + ( saldoCuenta ( 594 ) ) + ( saldoCuenta ( 595 ) ) + ( saldoCuenta ( 596 ) ) + ( saldoCuenta ( 597 ) ) + ( saldoCuenta ( 598 ) ) ).toQString ( '.' ) + "' ) \n\
                                     doc.set_cell_value ( 4, 68, 'float', '" + ( ( saldoCuentaAnt ( 593 ) ) + ( saldoCuentaAnt ( 594 ) ) + ( saldoCuentaAnt ( 595 ) ) + ( saldoCuentaAnt ( 596 ) ) + ( saldoCuentaAnt ( 597 ) ) + ( saldoCuentaAnt ( 598 ) ) ).toQString ( '.' ) + "' ) \n\
                                     \
                                     doc.set_cell_value ( 2, 69, 'string', '   V.   Acciones propias a corto plazo' ) \n\
                                     doc.set_cell_value ( 3, 69, 'formula', '=0' ) \n\
                                     doc.set_cell_value ( 4, 69, 'formula', '=0' ) \n\
                                     \
                                     doc.set_cell_value ( 2, 70, 'string', '   VI.  Tesoreria' ) \n\
                                     doc.set_cell_value ( 3, 70, 'float', '" + saldoCuenta ( 57 ).toQString ( '.' ) + "' ) \n\
                                     doc.set_cell_value ( 4, 70, 'float', '" + saldoCuentaAnt ( 57 ).toQString ( '.' ) + "' ) \n\
                                     \
                                     doc.set_cell_value ( 2, 71, 'string', '   VII. Ajustes por periodificacion' ) \n\
                                     doc.set_cell_value ( 3, 71, 'float', '" + ( saldoCuenta ( 480 ) + saldoCuenta ( 580 ) ).toQString ( '.' ) + "' ) \n\
                                     doc.set_cell_value ( 4, 71, 'float', '" + ( saldoCuentaAnt ( 480 ) + saldoCuentaAnt ( 580 ) ).toQString ( '.' ) + "' ) \n\
                                     \
                                     doc.set_cell_property ( 'bold', True ) \n\
                                     doc.set_cell_value ( 2, 73, 'string', 'TOTAL GENERAL (A+B+C+D)' ) \n\
                                     doc.set_cell_value ( 3, 73, 'formula', '=C7+C9+C40+C42' ) \n\
                                     doc.set_cell_value ( 4, 73, 'formula', '=D7+D9+D40+D42' ) \n\
                                     doc.set_cell_property ( 'bold', False ) \n\
                                     \
                                     " );

                                     barra.setValue ( barra.value() + 1 );

                                     codigoPython.append ( "\
                                     \
                                     \n\
                                     doc.new_sheet ( \"Pasivo\")\n\n\
                                     doc.set_column_property(1, 'width', '0.5in')\n\
                                     doc.set_column_property(2, 'width', '5in')\n\
                                     doc.set_cell_property('bold', True)\n\
                                     doc.set_cell_value(2, 2, 'string', 'BALANCE DE SITUACIÓN')\n\
                                     doc.set_cell_value(2, 3, 'string', '" + QDateTime::currentDateTime().toString() + "')\n\
                                     doc.set_cell_value(4, 2, 'string', 'PASIVO')\n\
                                     doc.set_cell_value(2, 5, 'string', 'Periodo: de " + meses.at ( mesInicio ) + " a " + meses.at ( mesFin ) + "')\n\
                                     doc.set_cell_value(3, 5, 'string', '" + ejercicioActual + "')\n\
                                     doc.set_cell_value(4, 5, 'string', '" + ejercicioAnterior + "')\n\
                                     doc.set_cell_property('bold', False)\n\
                                     \
                                     \
                                     doc.set_cell_property('bold', True)\n\
                                     doc.set_cell_value(2, 7, 'string', 'A) Fondos propios')\n\
                                     doc.set_cell_value(3, 7, 'formula', '=C8+C9+C10+C11+C17+C21+C22')\n\
                                     doc.set_cell_value(4, 7, 'formula', '=D8+D9+D10+D11+D17+D21+D22')\n\
                                     doc.set_cell_property('bold', False)\n\
                                     \
                                     doc.set_cell_value(2, 8, 'string', '   I.   Capital suscrito')\n\
                                     doc.set_cell_value(3, 8, 'float', '" + ( -saldoCuenta ( 10 ) ).toQString ( '.' ) + "')\n\
                                     doc.set_cell_value(4, 8, 'float', '" + ( -saldoCuentaAnt ( 10 ) ).toQString ( '.' ) + "')\n\
                                     \
                                     doc.set_cell_value(2, 9, 'string', '   II.  Prima de emision')\n\
                                     doc.set_cell_value(3, 9, 'float', '" + ( -saldoCuenta ( 110 ) ).toQString ( '.' ) + "')\n\
                                     doc.set_cell_value(4, 9, 'float', '" + ( -saldoCuentaAnt ( 110 ) ).toQString ( '.' ) + "')\n\
                                     \
                                     doc.set_cell_value(2, 10, 'string', '   III. Reserva de revalorizacion')\n\
                                     doc.set_cell_value(3, 10, 'float', '" + ( -saldoCuenta ( 111 ) ).toQString ( '.' ) + "')\n\
                                     doc.set_cell_value(4, 10, 'float', '" + ( -saldoCuentaAnt ( 111 ) ).toQString ( '.' ) + "')\n\
                                     \
                                     doc.set_cell_value(2, 11, 'string', '   IV.  Reservas')\n\
                                     doc.set_cell_value(3, 11, 'formula', '=SUM(C12:C16)')\n\
                                     doc.set_cell_value(4, 11, 'formula', '=SUM(D12:D16)')\n\
                                     \
                                     doc.set_cell_value(2, 12, 'string', '       1. Reserva legal')\n\
                                     doc.set_cell_value(3, 12, 'float', '" + ( -saldoCuenta ( 112 ) ).toQString ( '.' ) + "')\n\
                                     doc.set_cell_value(4, 12, 'float', '" + ( -saldoCuentaAnt ( 112 ) ).toQString ( '.' ) + "')\n\
                                     \
                                     doc.set_cell_value(2, 13, 'string', '       2. Reserva para acciones propias')\n\
                                     doc.set_cell_value(3, 13, 'float', '" + ( -saldoCuenta ( 115 ) ).toQString ( '.' ) + "')\n\
                                     doc.set_cell_value(4, 13, 'float', '" + ( -saldoCuentaAnt ( 115 ) ).toQString ( '.' ) + "')\n\
                                     \
                                     doc.set_cell_value(2, 14, 'string', '       3. Reserva para acciones de la sociedad dominante')\n\
                                     doc.set_cell_value(3, 14, 'float', '" + ( -saldoCuenta ( 114 ) ).toQString ( '.' ) + "')\n\
                                     doc.set_cell_value(4, 14, 'float', '" + ( -saldoCuentaAnt ( 114 ) ).toQString ( '.' ) + "')\n\
                                     \
                                     doc.set_cell_value(2, 15, 'string', '       4. Reservas estatutarias')\n\
                                     doc.set_cell_value(3, 15, 'float', '" + ( -saldoCuenta ( 116 ) ).toQString ( '.' ) + "')\n\
                                     doc.set_cell_value(4, 15, 'float', '" + ( -saldoCuentaAnt ( 116 ) ).toQString ( '.' ) + "')\n\
                                     \
                                     doc.set_cell_value(2, 16, 'string', '       5. Otras reservas')\n\
                                     doc.set_cell_value(3, 16, 'float', '" + ( -saldoCuenta ( 113 ) + ( -saldoCuenta ( 117 ) ) + ( -saldoCuenta ( 118 ) ) ).toQString ( '.' ) + "')\n\
                                     doc.set_cell_value(4, 16, 'float', '" + ( -saldoCuentaAnt ( 113 ) + ( -saldoCuentaAnt ( 117 ) ) + ( -saldoCuentaAnt ( 118 ) ) ).toQString ( '.' ) + "')\n\
                                     \
                                     doc.set_cell_value(2, 17, 'string', '   V.   Resultados de ejercicios anteriores')\n\
                                     doc.set_cell_value(3, 17, 'formula', '=SUM(C18:C20)')\n\
                                     doc.set_cell_value(4, 17, 'formula', '=SUM(D18:D20)')\n\
                                     \
                                     doc.set_cell_value(2, 18, 'string', '       1. Remanente')\n\
                                     doc.set_cell_value(3, 18, 'float', '" + ( -saldoCuenta ( 120 ) ).toQString ( '.' ) + "')\n\
                                     doc.set_cell_value(4, 18, 'float', '" + ( -saldoCuentaAnt ( 120 ) ).toQString ( '.' ) + "')\n\
                                     \
                                     doc.set_cell_value(2, 19, 'string', '       2. Resultados negativos de ejercicios anteriores')\n\
                                     doc.set_cell_value(3, 19, 'float', '" + ( -saldoCuenta ( 121 ) ).toQString ( '.' ) + "')\n\
                                     doc.set_cell_value(4, 19, 'float', '" + ( -saldoCuentaAnt ( 121 ) ).toQString ( '.' ) + "')\n\
                                     \
                                     doc.set_cell_value(2, 20, 'string', '       3. Aportaciones de socios para compensacion de perdidas')\n\
                                     doc.set_cell_value(3, 20, 'float', '" + ( -saldoCuenta ( 122 ) ).toQString ( '.' ) + "')\n\
                                     doc.set_cell_value(4, 20, 'float', '" + ( -saldoCuentaAnt ( 122 ) ).toQString ( '.' ) + "')\n\
                                     \
                                     doc.set_cell_value(2, 21, 'string', '   VI.  Perdidas y ganancias (beneficio o perdida)')\n\
                                     doc.set_cell_value(3, 21, 'formula', '=if(Haber.C55>0;Haber.C55*-1;Debe.C59)')\n\
                                     doc.set_cell_value(4, 21, 'formula', '=if(Haber.D55>0;Haber.D55*-1;Debe.D59)')\n\
                                     \
                                     doc.set_cell_value(2, 22, 'string', '   VII. Dividendo a cuenta entregado en el ejercicio')\n\
                                     doc.set_cell_value(3, 22, 'float', '" + ( saldoCuenta ( 557 ) ).toQString ( '.' ) + "')\n\
                                     doc.set_cell_value(4, 22, 'float', '" + ( saldoCuentaAnt ( 557 ) ).toQString ( '.' ) + "')\n\
                                     " );

                                     barra.setValue ( barra.value() + 1 );

                                     codigoPython.append ( "\
                                     \
                                     doc.set_cell_property ( 'bold', True ) \n\
                                     doc.set_cell_value ( 2, 24, 'string', 'B) Ingresos a distribuir en varios ejercicios' ) \n\
                                     doc.set_cell_value ( 3, 24, 'formula', '=SUM(C25:C27)' ) \n\
                                     doc.set_cell_value ( 4, 24, 'formula', '=SUM(D25:D27)' ) \n\
                                     doc.set_cell_property ( 'bold', False ) \n\
                                     \
                                     doc.set_cell_value ( 2, 25, 'string', '       1. Subvenciones de capital' ) \n\
                                     doc.set_cell_value ( 3, 25, 'float', '" + ( -saldoCuenta ( 130 ) + ( -saldoCuenta ( 131 ) ) ).toQString ( '.' ) + "' ) \n\
                                     doc.set_cell_value ( 4, 25, 'float', '" + ( -saldoCuentaAnt ( 130 ) + ( -saldoCuentaAnt ( 131 ) ) ).toQString ( '.' ) + "' ) \n\
                                     \
                                     doc.set_cell_value ( 2, 26, 'string', '       2. Diferencias positivas de cambio' ) \n\
                                     doc.set_cell_value ( 3, 26, 'float', '" + ( -saldoCuenta ( 136 ) ).toQString ( '.' ) + "' ) \n\
                                     doc.set_cell_value ( 4, 26, 'float', '" + ( -saldoCuentaAnt ( 136 ) ).toQString ( '.' ) + "' ) \n\
                                     \
                                     doc.set_cell_value ( 2, 27, 'string', '       3. Otras ingresos a distribuir en varios ejercicios' ) \n\
                                     doc.set_cell_value ( 3, 27, 'float', '" + ( -saldoCuenta ( 135 ) ).toQString ( '.' ) + "' ) \n\
                                     doc.set_cell_value ( 4, 27, 'float', '" + ( -saldoCuentaAnt ( 135 ) ).toQString ( '.' ) + "' ) \n\
                                     \
                                     " );

                                     barra.setValue ( barra.value() + 1 );

                                     codigoPython.append ( "\
                                     \
                                     doc.set_cell_property ( 'bold', True ) \n\
                                     doc.set_cell_value ( 2, 29, 'string', 'C) Provisiones para riesgos y gastos' ) \n\
                                     doc.set_cell_value ( 3, 29, 'formula', '=SUM(C30:C33)' ) \n\
                                     doc.set_cell_value ( 4, 29, 'formula', '=SUM(D30:D33)' ) \n\
                                     doc.set_cell_property ( 'bold', False ) \n\
                                     \
                                     doc.set_cell_value ( 2, 30, 'string', '       1. Provisiones para pensiones y obligaciones similares' ) \n\
                                     doc.set_cell_value ( 3, 30, 'float', '" + ( -saldoCuenta ( 140 ) ).toQString ( '.' ) + "' ) \n\
                                     doc.set_cell_value ( 4, 30, 'float', '" + ( -saldoCuentaAnt ( 140 ) ).toQString ( '.' ) + "' ) \n\
                                     \
                                     doc.set_cell_value ( 2, 31, 'string', '       2. Provisiones para impuestos' ) \n\
                                     doc.set_cell_value ( 3, 31, 'float', '" + ( -saldoCuenta ( 141 ) ).toQString ( '.' ) + "' ) \n\
                                     doc.set_cell_value ( 4, 31, 'float', '" + ( -saldoCuentaAnt ( 141 ) ).toQString ( '.' ) + "' ) \n\
                                     \
                                     doc.set_cell_value ( 2, 32, 'string', '       3. Otras provisiones' ) \n\
                                     doc.set_cell_value ( 3, 32, 'float', '" + ( -saldoCuenta ( 142 ) + ( -saldoCuenta ( 143 ) ) ).toQString ( '.' ) + "' ) \n\
                                     doc.set_cell_value ( 4, 32, 'float', '" + ( -saldoCuentaAnt ( 142 ) + ( -saldoCuentaAnt ( 143 ) ) ).toQString ( '.' ) + "' ) \n\
                                     \
                                     doc.set_cell_value ( 2, 33, 'string', '       4. Fondo de reversion' ) \n\
                                     doc.set_cell_value ( 3, 33, 'float', '" + ( -saldoCuenta ( 144 ) ).toQString ( '.' ) + "' ) \n\
                                     doc.set_cell_value ( 4, 33, 'float', '" + ( -saldoCuentaAnt ( 144 ) ).toQString ( '.' ) + "' ) \n\
                                     " );

                                     barra.setValue ( barra.value() + 1 );

                                     codigoPython.append ( "\
                                     \
                                     doc.set_cell_property ( 'bold', True ) \n\
                                     doc.set_cell_value ( 2, 35, 'string', 'D) Acreedores a largo plazo' ) \n\
                                     doc.set_cell_value ( 3, 35, 'formula', '=C36+C40+C41+C44+C48' ) \n\
                                     doc.set_cell_value ( 4, 35, 'formula', '=D36+D40+D41+D44+D48' ) \n\
                                     doc.set_cell_property ( 'bold', False ) \n\
                                     \
                                     doc.set_cell_value ( 2, 36, 'string', '   I.   Emisiones de obligaciones y otros valores negociables' ) \n\
                                     doc.set_cell_value ( 3, 36, 'formula', '=SUM(C37:C39)' ) \n\
                                     doc.set_cell_value ( 4, 36, 'formula', '=SUM(D37:D39)' ) \n\
                                     \
                                     doc.set_cell_value ( 2, 37, 'string', '       1. Obligaciones no convertibles' ) \n\
                                     doc.set_cell_value ( 3, 37, 'float', '" + ( -saldoCuenta ( 150 ) ).toQString ( '.' ) + "' ) \n\
                                     doc.set_cell_value ( 4, 37, 'float', '" + ( -saldoCuentaAnt ( 150 ) ).toQString ( '.' ) + "' ) \n\
                                     \
                                     doc.set_cell_value ( 2, 38, 'string', '       2. Obligaciones convertibles' ) \n\
                                     doc.set_cell_value ( 3, 38, 'float', '" + ( -saldoCuenta ( 151 ) ).toQString ( '.' ) + "' ) \n\
                                     doc.set_cell_value ( 4, 38, 'float', '" + ( -saldoCuentaAnt ( 151 ) ).toQString ( '.' ) + "' ) \n\
                                     \
                                     doc.set_cell_value ( 2, 39, 'string', '       3. Otras deudas representadas en valores negociables' ) \n\
                                     doc.set_cell_value ( 3, 39, 'float', '" + ( -saldoCuenta ( 155 ) ).toQString ( '.' ) + "' ) \n\
                                     doc.set_cell_value ( 4, 39, 'float', '" + ( -saldoCuentaAnt ( 155 ) ).toQString ( '.' ) + "' ) \n\
                                     \
                                     doc.set_cell_value ( 2, 40, 'string', '   II.  Deudas con entidades de credito' ) \n\
                                     doc.set_cell_value ( 3, 40, 'float', '" + ( -saldoCuenta ( 170 ) ).toQString ( '.' ) + "' ) \n\
                                     doc.set_cell_value ( 4, 40, 'float', '" + ( -saldoCuentaAnt ( 170 ) ).toQString ( '.' ) + "' ) \n\
                                     \
                                     doc.set_cell_value ( 2, 41, 'string', '   III. Deudas con empresas del grupo y asociadas' ) \n\
                                     doc.set_cell_value ( 3, 41, 'formula', '=SUM(C42:C43)' ) \n\
                                     doc.set_cell_value ( 4, 41, 'formula', '=SUM(D42:D43)' ) \n\
                                     \
                                     doc.set_cell_value ( 2, 42, 'string', '       1. Deudas con empresas del grupo' ) \n\
                                     doc.set_cell_value ( 3, 42, 'float', '" + ( -saldoCuenta ( 160 ) + ( -saldoCuenta ( 162 ) ) + ( -saldoCuenta ( 164 ) ) ).toQString ( '.' ) + "' ) \n\
                                     doc.set_cell_value ( 4, 42, 'float', '" + ( -saldoCuentaAnt ( 160 ) + ( -saldoCuentaAnt ( 162 ) ) + ( -saldoCuentaAnt ( 164 ) ) ).toQString ( '.' ) + "' ) \n\
                                     \
                                     doc.set_cell_value ( 2, 43, 'string', '       2. Deudas con empresas asociadas' ) \n\
                                     doc.set_cell_value ( 3, 43, 'float', '" + ( -saldoCuenta ( 161 ) + ( -saldoCuenta ( 163 ) ) + ( -saldoCuenta ( 165 ) ) ).toQString ( '.' ) + "' ) \n\
                                     doc.set_cell_value ( 4, 43, 'float', '" + ( -saldoCuentaAnt ( 161 ) + ( -saldoCuentaAnt ( 163 ) ) + ( -saldoCuentaAnt ( 165 ) ) ).toQString ( '.' ) + "' ) \n\
                                     \
                                     doc.set_cell_value ( 2, 44, 'string', '   IV.  Otros acreedores' ) \n\
                                     doc.set_cell_value ( 3, 44, 'formula', '=SUM(C45:C47)' ) \n\
                                     doc.set_cell_value ( 4, 44, 'formula', '=SUM(D45:D47)' ) \n\
                                     \
                                     doc.set_cell_value ( 2, 45, 'string', '       1. Deudas representadas por efectos a pagar' ) \n\
                                     doc.set_cell_value ( 3, 45, 'float', '" + ( -saldoCuenta ( 174 ) ).toQString ( '.' ) + "' ) \n\
                                     doc.set_cell_value ( 4, 45, 'float', '" + ( -saldoCuentaAnt ( 174 ) ).toQString ( '.' ) + "' ) \n\
                                     \
                                     doc.set_cell_value ( 2, 46, 'string', '       2. Otras deudas' ) \n\
                                     doc.set_cell_value ( 3, 46, 'float', '" + ( -saldoCuenta ( 171 ) + ( -saldoCuenta ( 172 ) ) + ( -saldoCuenta ( 173 ) ) ).toQString ( '.' ) + "' ) \n\
                                     doc.set_cell_value ( 4, 46, 'float', '" + ( -saldoCuentaAnt ( 171 ) + ( -saldoCuentaAnt ( 172 ) ) + ( -saldoCuentaAnt ( 173 ) ) ).toQString ( '.' ) + "' ) \n\
                                     \
                                     doc.set_cell_value ( 2, 47, 'string', '       3. Fianzas y depositos recibidos a largo plazo' ) \n\
                                     doc.set_cell_value ( 3, 47, 'float', '" + ( -saldoCuenta ( 180 ) + ( -saldoCuenta ( 185 ) ) ).toQString ( '.' ) + "' ) \n\
                                     doc.set_cell_value ( 4, 47, 'float', '" + ( -saldoCuentaAnt ( 180 ) + ( -saldoCuentaAnt ( 185 ) ) ).toQString ( '.' ) + "' ) \n\
                                     \
                                     doc.set_cell_value ( 2, 48, 'string', '   V.   Desembolsos pendientes sobre acciones, no exigidos' ) \n\
                                     doc.set_cell_value ( 3, 48, 'formula', '=SUM(C49:C51)' ) \n\
                                     doc.set_cell_value ( 4, 48, 'formula', '=SUM(D49:D51)' ) \n\
                                     \
                                     doc.set_cell_value ( 2, 49, 'string', '       1. De empresas del grupo' ) \n\
                                     doc.set_cell_value ( 3, 49, 'float', '" + ( -saldoCuenta ( 248 ) ).toQString ( '.' ) + "' ) \n\
                                     doc.set_cell_value ( 4, 49, 'float', '" + ( -saldoCuentaAnt ( 248 ) ).toQString ( '.' ) + "' ) \n\
                                     \
                                     doc.set_cell_value ( 2, 50, 'string', '       2. De empresas asociadas' ) \n\
                                     doc.set_cell_value ( 3, 50, 'float', '" + ( -saldoCuenta ( 249 ) ).toQString ( '.' ) + "' ) \n\
                                     doc.set_cell_value ( 4, 50, 'float', '" + ( -saldoCuentaAnt ( 249 ) ).toQString ( '.' ) + "' ) \n\
                                     \
                                     doc.set_cell_value ( 2, 51, 'string', '       3. De otras empresas' ) \n\
                                     doc.set_cell_value ( 3, 51, 'float', '" + ( -saldoCuenta ( 259 ) ).toQString ( '.' ) + "' ) \n\
                                     doc.set_cell_value ( 4, 51, 'float', '" + ( -saldoCuentaAnt ( 259 ) ).toQString ( '.' ) + "' ) \n\
                                     " );

                                     barra.setValue ( barra.value() + 1 );

                                     codigoPython.append ( "\
                                     \
                                     doc.set_cell_property ( 'bold', True ) \n\
                                     doc.set_cell_value ( 2, 53, 'string', 'E) Acreedores a corto plazo' ) \n\
                                     doc.set_cell_value ( 3, 53, 'formula', '=C54+C59+C62+C65+C69+C75+C76' ) \n\
                                     doc.set_cell_value ( 4, 53, 'formula', '=D54+D59+D62+D65+D69+D75+D76' ) \n\
                                     doc.set_cell_property ( 'bold', False ) \n\
                                     \
                                     doc.set_cell_value ( 2, 54, 'string', '   I.   Emisiones de obligaciones y otros valores negociables' ) \n\
                                     doc.set_cell_value ( 3, 54, 'formula', '=SUM(C55:C58)' ) \n\
                                     doc.set_cell_value ( 4, 54, 'formula', '=SUM(D55:D58)' ) \n\
                                     \
                                     doc.set_cell_value ( 2, 55, 'string', '       1. Obligaciones no convertibles' ) \n\
                                     doc.set_cell_value ( 3, 55, 'float', '" + ( -saldoCuenta ( 500 ) ).toQString ( '.' ) + "' ) \n\
                                     doc.set_cell_value ( 4, 55, 'float', '" + ( -saldoCuentaAnt ( 500 ) ).toQString ( '.' ) + "' ) \n\
                                     \
                                     doc.set_cell_value ( 2, 56, 'string', '       2. Obligaciones convertibles' ) \n\
                                     doc.set_cell_value ( 3, 56, 'float', '" + ( -saldoCuenta ( 501 ) ).toQString ( '.' ) + "' ) \n\
                                     doc.set_cell_value ( 4, 56, 'float', '" + ( -saldoCuentaAnt ( 501 ) ).toQString ( '.' ) + "' ) \n\
                                     \
                                     doc.set_cell_value ( 2, 57, 'string', '       3. Otras deudas representadas en valores negociables' ) \n\
                                     doc.set_cell_value ( 3, 57, 'float', '" + ( -saldoCuenta ( 505 ) ).toQString ( '.' ) + "' ) \n\
                                     doc.set_cell_value ( 4, 57, 'float', '" + ( -saldoCuentaAnt ( 505 ) ).toQString ( '.' ) + "' ) \n\
                                     \
                                     doc.set_cell_value ( 2, 58, 'string', '       4. Intereses de obligaciones y otros valores' ) \n\
                                     doc.set_cell_value ( 3, 58, 'float', '" + ( -saldoCuenta ( 506 ) ).toQString ( '.' ) + "' ) \n\
                                     doc.set_cell_value ( 4, 58, 'float', '" + ( -saldoCuentaAnt ( 506 ) ).toQString ( '.' ) + "' ) \n\
                                     \
                                     doc.set_cell_value ( 2, 59, 'string', '   II.  Deudas con entidades de credito' ) \n\
                                     doc.set_cell_value ( 3, 59, 'formula', '=SUM(C60:C61)' ) \n\
                                     doc.set_cell_value ( 4, 59, 'formula', '=SUM(D60:D61)' ) \n\
                                     \
                                     doc.set_cell_value ( 2, 60, 'string', '       1. Prestamos y otras deudas' ) \n\
                                     doc.set_cell_value ( 3, 60, 'float', '" + ( -saldoCuenta ( 520 ) ).toQString ( '.' ) + "' ) \n\
                                     doc.set_cell_value ( 4, 60, 'float', '" + ( -saldoCuentaAnt ( 520 ) ).toQString ( '.' ) + "' ) \n\
                                     \
                                     doc.set_cell_value ( 2, 61, 'string', '       2. Deudas por intereses' ) \n\
                                     doc.set_cell_value ( 3, 61, 'float', '" + ( -saldoCuenta ( 526 ) ).toQString ( '.' ) + "' ) \n\
                                     doc.set_cell_value ( 4, 61, 'float', '" + ( -saldoCuentaAnt ( 526 ) ).toQString ( '.' ) + "' ) \n\
                                     \
                                     doc.set_cell_value ( 2, 62, 'string', '   III. Deudas con empresas del grupo y asociadas a corto plazo' ) \n\
                                     doc.set_cell_value ( 3, 62, 'formula', '=SUM(C63:C64)' ) \n\
                                     doc.set_cell_value ( 4, 62, 'formula', '=SUM(D63:D64)' ) \n\
                                     \
                                     doc.set_cell_value ( 2, 63, 'string', '       1. Deudas con empresas del grupo' ) \n\
                                     doc.set_cell_value ( 3, 63, 'float', '" + ( -saldoCuenta ( 402 ) + ( -saldoCuenta ( 510 ) ) + ( -saldoCuenta ( 512 ) ) + ( -saldoCuenta ( 514 ) ) + ( -saldoCuenta ( 516 ) ) + ( -saldoCuenta ( 551 ) ) ).toQString ( '.' ) + "' ) \n\
                                     doc.set_cell_value ( 4, 63, 'float', '" + ( -saldoCuentaAnt ( 402 ) + ( -saldoCuentaAnt ( 510 ) ) + ( -saldoCuentaAnt ( 512 ) ) + ( -saldoCuentaAnt ( 514 ) ) + ( -saldoCuentaAnt ( 516 ) ) + ( -saldoCuentaAnt ( 551 ) ) ).toQString ( '.' ) + "' ) \n\
                                     \
                                     doc.set_cell_value ( 2, 64, 'string', '       2. Deudas con empresas asociadas' ) \n\
                                     doc.set_cell_value ( 3, 64, 'float', '" + ( -saldoCuenta ( 403 ) + ( -saldoCuenta ( 511 ) ) + ( -saldoCuenta ( 513 ) ) + ( -saldoCuenta ( 515 ) ) + ( -saldoCuenta ( 517 ) ) + ( -saldoCuenta ( 552 ) ) ).toQString ( '.' ) + "' ) \n\
                                     doc.set_cell_value ( 4, 64, 'float', '" + ( -saldoCuentaAnt ( 403 ) + ( -saldoCuentaAnt ( 511 ) ) + ( -saldoCuentaAnt ( 513 ) ) + ( -saldoCuentaAnt ( 515 ) ) + ( -saldoCuentaAnt ( 517 ) ) + ( -saldoCuentaAnt ( 552 ) ) ).toQString ( '.' ) + "' ) \n\
                                     \
                                     doc.set_cell_value ( 2, 65, 'string', '   IV.  Acreedores comerciales' ) \n\
                                     doc.set_cell_value ( 3, 65, 'formula', '=SUM(C66:C68)' ) \n\
                                     doc.set_cell_value ( 4, 65, 'formula', '=SUM(D66:D68)' ) \n\
                                     \
                                     doc.set_cell_value ( 2, 66, 'string', '       1. Anticipos recibidos por pedidos' ) \n\
                                     doc.set_cell_value ( 3, 66, 'float', '" + ( -saldoCuenta ( 437 ) ).toQString ( '.' ) + "' ) \n\
                                     doc.set_cell_value ( 4, 66, 'float', '" + ( -saldoCuentaAnt ( 437 ) ).toQString ( '.' ) + "' ) \n\
                                     \
                                     doc.set_cell_value ( 2, 67, 'string', '       2. Deudas por compras o prestaciones de servicios' ) \n\
                                     doc.set_cell_value ( 3, 67, 'float', '" + ( -saldoCuenta ( 400 ) + ( saldoCuenta ( 406 ) ) + ( -saldoCuenta ( 410 ) ) + ( -saldoCuenta ( 419 ) ) ).toQString ( '.' ) + "' ) \n\
                                     doc.set_cell_value ( 4, 67, 'float', '" + ( -saldoCuentaAnt ( 400 ) + ( -saldoCuentaAnt ( 406 ) ) + ( -saldoCuentaAnt ( 410 ) ) + ( -saldoCuentaAnt ( 419 ) ) ).toQString ( '.' ) + "' ) \n\
                                     \
                                     doc.set_cell_value ( 2, 68, 'string', '       3. Deudas representadas por efectos a pagar' ) \n\
                                     doc.set_cell_value ( 3, 68, 'float', '" + ( -saldoCuenta ( 401 ) + ( -saldoCuenta ( 411 ) ) ).toQString ( '.' ) + "' ) \n\
                                     doc.set_cell_value ( 4, 68, 'float', '" + ( -saldoCuentaAnt ( 401 ) + ( -saldoCuentaAnt ( 411 ) ) ).toQString ( '.' ) + "' ) \n\
                                     \
                                     doc.set_cell_value ( 2, 69, 'string', '   V.   Otras deudas no comerciales' ) \n\
                                     doc.set_cell_value ( 3, 69, 'formula', '=SUM(C70:C74)' ) \n\
                                     doc.set_cell_value ( 4, 69, 'formula', '=SUM(D70:D74)' ) \n\
                                     \
                                     doc.set_cell_value ( 2, 70, 'string', '       1. Administraciones Publicas' ) \n\
                                     doc.set_cell_value ( 3, 70, 'float', '" + ( -saldoCuenta ( 475 ) + ( -saldoCuenta ( 476 ) ) + ( -saldoCuenta ( 477 ) ) + ( -saldoCuenta ( 479 ) ) ).toQString ( '.' ) + "' ) \n\
                                     doc.set_cell_value ( 4, 70, 'float', '" + ( -saldoCuentaAnt ( 475 ) + ( -saldoCuentaAnt ( 476 ) ) + ( -saldoCuentaAnt ( 477 ) ) + ( -saldoCuentaAnt ( 479 ) ) ).toQString ( '.' ) + "' ) \n\
                                     \
                                     doc.set_cell_value ( 2, 71, 'string', '       2. Deudas representadas por efectos a pagar' ) \n\
                                     doc.set_cell_value ( 3, 71, 'float', '" + ( -saldoCuenta ( 524 ) ).toQString ( '.' ) + "' ) \n\
                                     doc.set_cell_value ( 4, 71, 'float', '" + ( -saldoCuentaAnt ( 524 ) ).toQString ( '.' ) + "' ) \n\
                                     \
                                     doc.set_cell_value ( 2, 72, 'string', '       3. Otras deudas' ) \n\
                                     doc.set_cell_value ( 3, 72, 'float', '" + ( -saldoCuenta ( 509 ) + ( -saldoCuenta ( 521 ) ) + ( -saldoCuenta ( 523 ) ) + ( -saldoCuenta ( 525 ) ) + ( -saldoCuenta ( 527 ) ) + ( -saldoCuenta ( 555 ) ) + ( -saldoCuenta ( 556 ) ) ).toQString ( '.' ) + "' ) \n\
                                     doc.set_cell_value ( 4, 72, 'float', '" + ( -saldoCuentaAnt ( 509 ) + ( -saldoCuentaAnt ( 521 ) ) + ( -saldoCuentaAnt ( 523 ) ) + ( -saldoCuentaAnt ( 525 ) ) + ( -saldoCuentaAnt ( 527 ) ) + ( -saldoCuentaAnt ( 555 ) ) + ( -saldoCuentaAnt ( 556 ) ) ).toQString ( '.' ) + "' ) \n\
                                     \
                                     doc.set_cell_value ( 2, 73, 'string', '       4. Remuneraciones pendientes de pago' ) \n\
                                     doc.set_cell_value ( 3, 73, 'float', '" + ( -saldoCuenta ( 465 ) ).toQString ( '.' ) + "' ) \n\
                                     doc.set_cell_value ( 4, 73, 'float', '" + ( -saldoCuentaAnt ( 465 ) ).toQString ( '.' ) + "' ) \n\
                                     \
                                     doc.set_cell_value ( 2, 74, 'string', '       5. Fianzas y depositos recibidos a corto plazo' ) \n\
                                     doc.set_cell_value ( 3, 74, 'float', '" + ( -saldoCuenta ( 560 ) + ( -saldoCuenta ( 561 ) ) ).toQString ( '.' ) + "' ) \n\
                                     doc.set_cell_value ( 4, 74, 'float', '" + ( -saldoCuentaAnt ( 560 ) + ( -saldoCuentaAnt ( 561 ) ) ).toQString ( '.' ) + "' ) \n\
                                     \
                                     doc.set_cell_value ( 2, 75, 'string', '   VI.  Provisiones para operaciones de trafico' ) \n\
                                     doc.set_cell_value ( 3, 75, 'float', '" + ( -saldoCuenta ( 499 ) ).toQString ( '.' ) + "' ) \n\
                                     doc.set_cell_value ( 4, 75, 'float', '" + ( -saldoCuentaAnt ( 499 ) ).toQString ( '.' ) + "' ) \n\
                                     \
                                     doc.set_cell_value ( 2, 76, 'string', '   VII. Ajustes por periodificacion' ) \n\
                                     doc.set_cell_value ( 3, 76, 'float', '" + ( -saldoCuenta ( 485 ) + ( -saldoCuenta ( 585 ) ) ).toQString ( '.' ) + "' ) \n\
                                     doc.set_cell_value ( 4, 76, 'float', '" + ( -saldoCuentaAnt ( 485 ) + ( -saldoCuentaAnt ( 585 ) ) ).toQString ( '.' ) + "' ) \n\
                                     \
                                     doc.set_cell_property ( 'bold', True ) \n\
                                     doc.set_cell_value ( 2, 78, 'string', 'TOTAL GENERAL (A+B+C+D+E)' ) \n\
                                     doc.set_cell_value ( 3, 78, 'formula', '=C7+C24+C29+C35+C53' ) \n\
                                     doc.set_cell_value ( 4, 78, 'formula', '=D7+D24+D29+D35+D53' ) \n\
                                     doc.set_cell_property ( 'bold', False ) \n\
                                     \
                                     " );

                                     barra.setValue ( barra.value() + 1 );

                                     codigoPython.append ( "\
                                     \
                                     \n\
                                     doc.new_sheet ( \"Debe\")\n\n\
                                     doc.set_column_property(1, 'width', '0.5in')\n\
                                     doc.set_column_property(2, 'width', '5in')\n\
                                     doc.set_cell_property('bold', True)\n\
                                     doc.set_cell_value(2, 2, 'string', 'CUENTA DE PÉRDIDAS Y GANANCIAS')\n\
                                     doc.set_cell_value(2, 3, 'string', '" + QDateTime::currentDateTime().toString() + "')\n\
                                     doc.set_cell_value(4, 2, 'string', 'DEBE')\n\
                                     doc.set_cell_value(2, 5, 'string', 'Periodo: de " + meses.at ( mesInicio ) + " a " + meses.at ( mesFin ) + "')\n\
                                     doc.set_cell_value(3, 5, 'string', '" + ejercicioActual + "')\n\
                                     doc.set_cell_value(4, 5, 'string', '" + ejercicioAnterior + "')\n\
                                     doc.set_cell_property('bold', False)\n\
                                     \
                                     \
                                     doc.set_cell_property('bold', True)\n\
                                     doc.set_cell_value(2, 7, 'string', 'A) GASTOS')\n\
                                     doc.set_cell_value(3, 7, 'formula', '=C8+C9+C13+C16+C17+C21+C30+C35+C36+C44+C45+C46+C47+C48+C56+C57')\n\
                                     doc.set_cell_value(4, 7, 'formula', '=D8+D9+D13+D16+D17+D21+D30+D35+D36+D44+D45+D46+D47+D48+D56+D57')\n\
                                     doc.set_cell_property('bold', False)\n\
                                     \
                                     doc.set_cell_value(2, 8, 'string', '       1. Reduccion de existencias de productos terminados y en curso de fabricacion')\n\
                                     doc.set_cell_value(3, 8, 'float', '" + ( saldoCuenta ( 71 ) ).toQString ( '.' ) + "')\n\
                                     doc.set_cell_value(4, 8, 'float', '" + ( saldoCuentaAnt ( 71 ) ).toQString ( '.' ) + "')\n\
                                     \
                                     doc.set_cell_value(2, 9, 'string', '       2. Aprovisionamientos')\n\
                                     doc.set_cell_value(3, 9, 'formula', '=SUM(C10:C12)')\n\
                                     doc.set_cell_value(4, 9, 'formula', '=SUM(D10:D12)')\n\
                                     \
                                     doc.set_cell_value(2, 10, 'string', '            a) Consumo de mercaderias')\n\
                                     doc.set_cell_value(3, 10, 'float', '" + ( saldoCuenta ( 600 ) + ( saldoCuenta ( 6080 ) ) + ( saldoCuenta ( 6090 ) ) + ( saldoCuenta ( 610 ) ) ).toQString ( '.' ) + "')\n\
                                     doc.set_cell_value(4, 10, 'float', '" + ( saldoCuentaAnt ( 600 ) + ( saldoCuentaAnt ( 6080 ) ) + ( saldoCuentaAnt ( 6090 ) ) + ( saldoCuentaAnt ( 610 ) ) ).toQString ( '.' ) + "')\n\
                                     \
                                     doc.set_cell_value(2, 11, 'string', '            b) Consumo de materias primas y otras materias consumibles')\n\
                                     doc.set_cell_value(3, 11, 'float', '" + ( saldoCuenta ( 601 ) + ( saldoCuenta ( 602 ) ) + ( saldoCuenta ( 6081 ) ) + ( saldoCuenta ( 6082 ) ) + ( saldoCuenta ( 6091 ) ) + ( saldoCuenta ( 6092 ) ) + ( saldoCuenta ( 611 ) ) + ( saldoCuenta ( 612 ) ) ).toQString ( '.' ) + "')\n\
                                     doc.set_cell_value(4, 11, 'float', '" + ( saldoCuentaAnt ( 601 ) + ( saldoCuentaAnt ( 602 ) ) + ( saldoCuentaAnt ( 6081 ) ) + ( saldoCuentaAnt ( 6082 ) ) + ( saldoCuentaAnt ( 6091 ) ) + ( saldoCuentaAnt ( 6092 ) ) + ( saldoCuentaAnt ( 611 ) ) + ( saldoCuentaAnt ( 612 ) ) ).toQString ( '.' ) + "')\n\
                                     \
                                     doc.set_cell_value(2, 12, 'string', '            c) Otros gastos externos')\n\
                                     doc.set_cell_value(3, 12, 'float', '" + ( saldoCuenta ( 607 ) ).toQString ( '.' ) + "')\n\
                                     doc.set_cell_value(4, 12, 'float', '" + ( saldoCuentaAnt ( 607 ) ).toQString ( '.' ) + "')\n\
                                     \
                                     doc.set_cell_value(2, 13, 'string', '       3. Gastos de personal')\n\
                                     doc.set_cell_value(3, 13, 'formula', '=SUM(C14:C15)')\n\
                                     doc.set_cell_value(4, 13, 'formula', '=SUM(D14:D15)')\n\
                                     \
                                     doc.set_cell_value(2, 14, 'string', '            a) Sueldos, salarios y asimilados')\n\
                                     doc.set_cell_value(3, 14, 'float', '" + ( saldoCuenta ( 640 ) + ( saldoCuenta ( 641 ) ) ).toQString ( '.' ) + "')\n\
                                     doc.set_cell_value(4, 14, 'float', '" + ( saldoCuentaAnt ( 640 ) + ( saldoCuentaAnt ( 641 ) ) ).toQString ( '.' ) + "')\n\
                                     \
                                     doc.set_cell_value(2, 15, 'string', '            b) Cargas sociales')\n\
                                     doc.set_cell_value(3, 15, 'float', '" + ( saldoCuenta ( 642 ) + ( saldoCuenta ( 643 ) ) + ( saldoCuenta ( 649 ) ) ).toQString ( '.' ) + "')\n\
                                     doc.set_cell_value(4, 15, 'float', '" + ( saldoCuentaAnt ( 642 ) + ( saldoCuentaAnt ( 643 ) ) + ( saldoCuentaAnt ( 649 ) ) ).toQString ( '.' ) + "')\n\
                                     \
                                     doc.set_cell_value(2, 16, 'string', '       4. Dotaciones para amortizaciones de inmovilizado')\n\
                                     doc.set_cell_value(3, 16, 'float', '" + ( saldoCuenta ( 68 ) ).toQString ( '.' ) + "')\n\
                                     doc.set_cell_value(4, 16, 'float', '" + ( saldoCuentaAnt ( 68 ) ).toQString ( '.' ) + "')\n\
                                     \
                                     doc.set_cell_value(2, 17, 'string', '       5. Variacion de las provisiones de trafico')\n\
                                     doc.set_cell_value(3, 17, 'formula', '=SUM(C18:C20)')\n\
                                     doc.set_cell_value(4, 17, 'formula', '=SUM(D18:D20)')\n\
                                     \
                                     doc.set_cell_value(2, 18, 'string', '            a) Variaciones de las provisiones de existencias')\n\
                                     doc.set_cell_value(3, 18, 'float', '" + ( saldoCuenta ( 693 ) + ( -saldoCuenta ( 793 ) ) ).toQString ( '.' ) + "')\n\
                                     doc.set_cell_value(4, 18, 'float', '" + ( saldoCuentaAnt ( 693 ) + ( -saldoCuentaAnt ( 793 ) ) ).toQString ( '.' ) + "')\n\
                                     \
                                     doc.set_cell_value(2, 19, 'string', '            b) Variaciones de provisiones y perdidas de creditos incobrables')\n\
                                     doc.set_cell_value(3, 19, 'float', '" + ( saldoCuenta ( 650 ) + ( saldoCuenta ( 694 ) ) + ( saldoCuenta ( 794 ) ) ).toQString ( '.' ) + "')\n\
                                     doc.set_cell_value(4, 19, 'float', '" + ( saldoCuentaAnt ( 650 ) + ( saldoCuentaAnt ( 694 ) ) + ( saldoCuentaAnt ( 794 ) ) ).toQString ( '.' ) + "')\n\
                                     \
                                     doc.set_cell_value(2, 20, 'string', '            c) Variaciones de otras provisiones de trafico')\n\
                                     doc.set_cell_value(3, 20, 'float', '" + ( saldoCuenta ( 695 ) + ( -saldoCuenta ( 795 ) ) ).toQString ( '.' ) + "')\n\
                                     doc.set_cell_value(4, 20, 'float', '" + ( saldoCuentaAnt ( 695 ) + ( -saldoCuentaAnt ( 795 ) ) ).toQString ( '.' ) + "')\n\
                                     \
                                     doc.set_cell_value(2, 21, 'string', '       6. Otros gastos de explotacion')\n\
                                     doc.set_cell_value(3, 21, 'formula', '=SUM(C22:C25)')\n\
                                     doc.set_cell_value(4, 21, 'formula', '=SUM(D22:D25)')\n\
                                     \
                                     doc.set_cell_value(2, 22, 'string', '            a) Servicios exteriores')\n\
                                     doc.set_cell_value(3, 22, 'float', '" + ( saldoCuenta ( 62 ) ).toQString ( '.' ) + "')\n\
                                     doc.set_cell_value(4, 22, 'float', '" + ( saldoCuentaAnt ( 62 ) ).toQString ( '.' ) + "')\n\
                                     \
                                     doc.set_cell_value(2, 23, 'string', '            b) Tributos')\n\
                                     doc.set_cell_value(3, 23, 'float', '" + ( saldoCuenta ( 631 ) + ( saldoCuenta ( 634 ) ) + ( -saldoCuenta ( 636 ) ) + ( -saldoCuenta ( 639 ) ) ).toQString ( '.' ) + "')\n\
                                     doc.set_cell_value(4, 23, 'float', '" + ( saldoCuentaAnt ( 631 ) + ( saldoCuentaAnt ( 634 ) ) + ( -saldoCuentaAnt ( 636 ) ) + ( -saldoCuentaAnt ( 639 ) ) ).toQString ( '.' ) + "')\n\
                                     \
                                     doc.set_cell_value(2, 24, 'string', '            c) Otros gastos de gestion corriente')\n\
                                     doc.set_cell_value(3, 24, 'float', '" + ( saldoCuenta ( 651 ) + ( saldoCuenta ( 659 ) ) ).toQString ( '.' ) + "')\n\
                                     doc.set_cell_value(4, 24, 'float', '" + ( saldoCuentaAnt ( 651 ) + ( saldoCuentaAnt ( 659 ) ) ).toQString ( '.' ) + "')\n\
                                     \
                                     doc.set_cell_value(2, 25, 'string', '            d) Dotacion al fondo de reversion')\n\
                                     doc.set_cell_value(3, 25, 'float', '" + ( saldoCuenta ( 690 ) ).toQString ( '.' ) + "')\n\
                                     doc.set_cell_value(4, 25, 'float', '" + ( saldoCuentaAnt ( 690 ) ).toQString ( '.' ) + "')\n\
                                     \
                                     " );

                                     barra.setValue ( barra.value() + 1 );

                                     codigoPython.append ( "\
                                     \
                                     doc.set_cell_value(2, 27, 'string', '   I.   BENEFICIOS DE EXLOTACIÓN')\n\
                                     doc.set_cell_value(2, 28, 'string', '        (B1+B2+B3+B4-A1-A2-A3-A4-A5-A6)')\n\
                                     doc.set_cell_value(3, 27, 'formula', '=IF(Haber.C8+Haber.C12+Haber.C13+Haber.C14-C8-C9-C13-C16-C17-C21>0;Haber.C8+Haber.C12+Haber.C13+Haber.C14-C8-C9-C13-C16-C17-C21;0)')\n\
                                     doc.set_cell_value(4, 27, 'formula', '=IF(Haber.D8+Haber.D12+Haber.D13+Haber.D14-D8-D9-D13-D16-D17-D21>0;Haber.D8+Haber.D12+Haber.D13+Haber.D14-D8-D9-D13-D16-D17-D21;0)')\n\
                                     \
                                     doc.set_cell_value(2, 30, 'string', '       7. Gastos financieros y gastos asimilados')\n\
                                     doc.set_cell_value(3, 30, 'formula', '=SUM(C31:C34)')\n\
                                     doc.set_cell_value(4, 30, 'formula', '=SUM(D31:D34)')\n\
                                     \
                                     doc.set_cell_value(2, 31, 'string', '            a) Por deudas con empresas del grupo')\n\
                                     doc.set_cell_value(3, 31, 'float', '" + ( saldoCuenta ( 6610 ) + ( saldoCuenta ( 6615 ) ) + ( saldoCuenta ( 6620 ) ) + ( saldoCuenta ( 6630 ) ) + ( saldoCuenta ( 6640 ) ) + ( saldoCuenta ( 6650 ) ) ).toQString ( '.' ) + "')\n\
                                     doc.set_cell_value(4, 31, 'float', '" + ( saldoCuentaAnt ( 6610 ) + ( saldoCuentaAnt ( 6615 ) ) + ( saldoCuentaAnt ( 6620 ) ) + ( saldoCuentaAnt ( 6630 ) ) + ( saldoCuentaAnt ( 6640 ) ) + ( saldoCuentaAnt ( 6650 ) ) ).toQString ( '.' ) + "')\n\
                                     \
                                     doc.set_cell_value(2, 32, 'string', '            b) Por deudas con empresas asociadas')\n\
                                     doc.set_cell_value(3, 32, 'float', '" + ( saldoCuenta ( 6611 ) + ( saldoCuenta ( 6616 ) ) + ( saldoCuenta ( 6621 ) ) + ( saldoCuenta ( 6631 ) ) + ( saldoCuenta ( 6641 ) ) + ( saldoCuenta ( 6651 ) ) ).toQString ( '.' ) + "')\n\
                                     doc.set_cell_value(4, 32, 'float', '" + ( saldoCuentaAnt ( 6611 ) + ( saldoCuentaAnt ( 6616 ) ) + ( saldoCuentaAnt ( 6621 ) ) + ( saldoCuentaAnt ( 6631 ) ) + ( saldoCuentaAnt ( 6641 ) ) + ( saldoCuentaAnt ( 6651 ) ) ).toQString ( '.' ) + "')\n\
                                     \
                                     doc.set_cell_value(2, 33, 'string', '            c) Por deudas con terceros y gastos asimilados')\n\
                                     doc.set_cell_value(3, 33, 'float', '" + ( saldoCuenta ( 6613 ) + ( saldoCuenta ( 6618 ) ) + ( saldoCuenta ( 6622 ) ) ).toQString ( '.' ) + "')\n\
                                     doc.set_cell_value(4, 33, 'float', '" + ( saldoCuentaAnt ( 6613 ) + ( saldoCuentaAnt ( 6618 ) ) + ( saldoCuentaAnt ( 6622 ) ) ).toQString ( '.' ) + "')\n\
                                     \
                                     doc.set_cell_value(2, 34, 'string', '            d) Perdidas de inversiones financieras')\n\
                                     doc.set_cell_value(3, 34, 'float', '" + ( saldoCuenta ( 6623 ) + ( saldoCuenta ( 6632 ) ) + ( saldoCuenta ( 6633 ) ) + ( saldoCuenta ( 6643 ) ) + ( saldoCuenta ( 6653 ) ) + ( saldoCuenta ( 669 ) ) + ( saldoCuenta ( 666 ) ) + ( saldoCuenta ( 667 ) ) ).toQString ( '.' ) + "')\n\
                                     doc.set_cell_value(4, 34, 'float', '" + ( saldoCuentaAnt ( 6623 ) + ( saldoCuentaAnt ( 6632 ) ) + ( saldoCuentaAnt ( 6633 ) ) + ( saldoCuentaAnt ( 6643 ) ) + ( saldoCuentaAnt ( 6653 ) ) + ( saldoCuentaAnt ( 669 ) ) + ( saldoCuentaAnt ( 666 ) ) + ( saldoCuentaAnt ( 667 ) ) ).toQString ( '.' ) + "')\n\
                                     \
                                     doc.set_cell_value(2, 35, 'string', '       8. Variacion de las provisiones de inversiones financieras')\n\
                                     doc.set_cell_value(3, 35, 'float', '" + ( saldoCuenta ( 6963 ) + ( saldoCuenta ( 6965 ) ) + ( saldoCuenta ( 6966 ) ) + ( saldoCuenta ( 697 ) ) + ( saldoCuenta ( 698 ) ) + ( saldoCuenta ( 699 ) ) + ( -saldoCuenta ( 7963 ) ) + ( -saldoCuenta ( 7965 ) ) + ( -saldoCuenta ( 7966 ) ) + ( -saldoCuenta ( 797 ) ) + ( -saldoCuenta ( 798 ) ) + ( -saldoCuenta ( 799 ) ) ).toQString ( '.' ) + "')\n\
                                     doc.set_cell_value(4, 35, 'float', '" + ( saldoCuentaAnt ( 6963 ) + ( saldoCuentaAnt ( 6965 ) ) + ( saldoCuentaAnt ( 6966 ) ) + ( saldoCuentaAnt ( 697 ) ) + ( saldoCuentaAnt ( 698 ) ) + ( saldoCuentaAnt ( 699 ) ) + ( -saldoCuentaAnt ( 7963 ) ) + ( -saldoCuentaAnt ( 7965 ) ) + ( -saldoCuentaAnt ( 7966 ) ) + ( -saldoCuentaAnt ( 797 ) ) + ( -saldoCuentaAnt ( 798 ) ) + ( -saldoCuentaAnt ( 799 ) ) ).toQString ( '.' ) + "')\n\
                                     \
                                     doc.set_cell_value(2, 36, 'string', '       9. Diferencias negativas de cambio')\n\
                                     doc.set_cell_value(3, 36, 'float', '" + ( saldoCuenta ( 668 ) ).toQString ( '.' ) + "')\n\
                                     doc.set_cell_value(4, 36, 'float', '" + ( saldoCuentaAnt ( 668 ) ).toQString ( '.' ) + "')\n\
                                     \
                                     " );

                                     barra.setValue ( barra.value() + 1 );

                                     codigoPython.append ( "\
                                     \
                                     doc.set_cell_value(2, 38, 'string', '   II.  RESULTADOS FINANCIEROS POSITIVOS')\n\
                                     doc.set_cell_value(2, 39, 'string', '        (B5+B6+B7+B8-A7-A8-A9)')\n\
                                     doc.set_cell_value(3, 38, 'formula', '=if(Haber.C22+Haber.C26+Haber.C30+Haber.C35-C31-C35-C36>0;Haber.C22+Haber.C26+Haber.C30+Haber.C35-C31-C35-C36;0)')\n\
                                     doc.set_cell_value(4, 38, 'formula', '=if(Haber.D22+Haber.D26+Haber.D30+Haber.D35-D31-D35-D36>0;Haber.D22+Haber.D26+Haber.D30+Haber.D35-D31-D35-D36;0)')\n\
                                     \
                                     " );

                                     barra.setValue ( barra.value() + 1 );

                                     codigoPython.append ( "\
                                     \
                                     doc.set_cell_value(2, 41, 'string', '   III. BENEFICIOS DE LAS ACTIVIDADES ORDINARIAS')\n\
                                     doc.set_cell_value(2, 42, 'string', '        (AI+AII-BI-BII)')\n\
                                     doc.set_cell_value(3, 41, 'formula', '=if(C27+C38-Haber.C19-Haber.C37>0;C27+C38-Haber.C19-Haber.C37;0)')\n\
                                     doc.set_cell_value(4, 41, 'formula', '=if(D27+D38-Haber.D19-Haber.D37>0;D27+D38-Haber.D19-Haber.D37;0)')\n\
                                     \
                                     doc.set_cell_value(2, 44, 'string', '      10. Variacion de las provisiones de inmobilizado inmaterial, material y cartera de control')\n\
                                     doc.set_cell_value(3, 44, 'float', '" + ( saldoCuenta ( 691 ) + ( saldoCuenta ( 692 ) ) + ( saldoCuenta ( 6960 ) ) + ( saldoCuenta ( 6961 ) ) + ( -saldoCuenta ( 791 ) ) + ( -saldoCuenta ( 792 ) ) + ( -saldoCuenta ( 7960 ) ) + ( -saldoCuenta ( 7961 ) ) ).toQString ( '.' ) + "')\n\
                                     doc.set_cell_value(4, 44, 'float', '" + ( saldoCuentaAnt ( 691 ) + ( saldoCuentaAnt ( 692 ) ) + ( saldoCuentaAnt ( 6960 ) ) + ( saldoCuentaAnt ( 6961 ) ) + ( -saldoCuentaAnt ( 791 ) ) + ( -saldoCuentaAnt ( 792 ) ) + ( -saldoCuentaAnt ( 7960 ) ) + ( -saldoCuentaAnt ( 7961 ) ) ).toQString ( '.' ) + "')\n\
                                     \
                                     doc.set_cell_value(2, 45, 'string', '      11. Perdidas procedentes del inmovilizado')\n\
                                     doc.set_cell_value(3, 45, 'float', '" + ( saldoCuenta ( 670 ) + ( saldoCuenta ( 671 ) ) + ( saldoCuenta ( 672 ) ) + ( saldoCuenta ( 673 ) ) ).toQString ( '.' ) + "')\n\
                                     doc.set_cell_value(4, 45, 'float', '" + ( saldoCuentaAnt ( 670 ) + ( saldoCuentaAnt ( 671 ) ) + ( saldoCuentaAnt ( 672 ) ) + ( saldoCuentaAnt ( 673 ) ) ).toQString ( '.' ) + "')\n\
                                     \
                                     doc.set_cell_value(2, 46, 'string', '      12. Perdidas por operaciones con acciones y obligaciones propias')\n\
                                     doc.set_cell_value(3, 46, 'float', '" + ( saldoCuenta ( 674 ) ).toQString ( '.' ) + "')\n\
                                     doc.set_cell_value(4, 46, 'float', '" + ( saldoCuentaAnt ( 674 ) ).toQString ( '.' ) + "')\n\
                                     \
                                     doc.set_cell_value(2, 47, 'string', '      13. Gastos extraordinarios')\n\
                                     doc.set_cell_value(3, 47, 'float', '" + ( saldoCuenta ( 678 ) ).toQString ( '.' ) + "')\n\
                                     doc.set_cell_value(4, 47, 'float', '" + ( saldoCuentaAnt ( 678 ) ).toQString ( '.' ) + "')\n\
                                     \
                                     doc.set_cell_value(2, 48, 'string', '      14. Gastos y perdidas de otros ejercicios')\n\
                                     doc.set_cell_value(3, 48, 'float', '" + ( saldoCuenta ( 679 ) ).toQString ( '.' ) + "')\n\
                                     doc.set_cell_value(4, 48, 'float', '" + ( saldoCuentaAnt ( 679 ) ).toQString ( '.' ) + "')\n\
                                     \
                                     " );

                                     barra.setValue ( barra.value() + 1 );

                                     codigoPython.append ( "\
                                     \
                                     doc.set_cell_value(2, 50, 'string', '   IV.  RESULTADOS EXTRAORDINARIOS POSITIVOS')\n\
                                     doc.set_cell_value(2, 51, 'string', '        (B9+B10+B11+B12+B13-A10-A11-A12-A13-A14)')\n\
                                     doc.set_cell_value(3, 50, 'formula', '=if(Haber.C43+Haber.C44+Haber.C45+Haber.C46+Haber.C47-C44-C45-C46-C47-C48>0;Haber.C43+Haber.C44+Haber.C45+Haber.C46+Haber.C47-C44-C45-C46-C47-C48;0)')\n\
                                     doc.set_cell_value(4, 50, 'formula', '=if(Haber.D43+Haber.D44+Haber.D45+Haber.D46+Haber.D47-D44-D45-D46-D47-D48>0;Haber.D43+Haber.D44+Haber.D45+Haber.D46+Haber.D47-D44-D45-D46-D47-D48;0)')\n\
                                     \
                                     " );

                                     barra.setValue ( barra.value() + 1 );

                                     codigoPython.append ( "\
                                     \
                                     doc.set_cell_value(2, 53, 'string', '   V.   BENEFICIOS ANTES DE IMPUESTOS')\n\
                                     doc.set_cell_value(2, 54, 'string', '        (AIII+AIV-BIII-BIV)')\n\
                                     doc.set_cell_value(3, 53, 'formula', '=if(C41+C50-Haber.C40-Haber.C49>0;C41+C50-Haber.C40-Haber.C49;0)')\n\
                                     doc.set_cell_value(4, 53, 'formula', '=if(D41+D50-Haber.D40-Haber.D49>0;D41+D50-Haber.D40-Haber.D49;0)')\n\
                                     \
                                     doc.set_cell_value(2, 56, 'string', '      15. Impuesto sobre Sociedades')\n\
                                     doc.set_cell_value(3, 56, 'float', '" + ( saldoCuenta ( 630 ) + ( saldoCuenta ( 633 ) ) + ( saldoCuenta ( 638 ) ) ).toQString ( '.' ) + "')\n\
                                     doc.set_cell_value(4, 56, 'float', '" + ( saldoCuentaAnt ( 630 ) + ( saldoCuentaAnt ( 633 ) ) + ( saldoCuentaAnt ( 638 ) ) ).toQString ( '.' ) + "')\n\
                                     \
                                     doc.set_cell_value(2, 57, 'string', '      16. Otros impuestos')\n\
                                     doc.set_cell_value(3, 57, 'formula', '=0')\n\
                                     doc.set_cell_value(4, 57, 'formula', '=0')\n\
                                     \
                                     " );

                                     barra.setValue ( barra.value() + 1 );

                                     codigoPython.append ( "\
                                     \
                                     doc.set_cell_value(2, 59, 'string', '   VI.  RESULTADO DEL EJERCICIO (BENEFICIOS)')\n\
                                     doc.set_cell_value(2, 60, 'string', '        (AV-A15-A16)')\n\
                                     doc.set_cell_value(3, 59, 'formula', '=if(C53>0;C53-C56-C57;0)')\n\
                                     doc.set_cell_value(4, 59, 'formula', '=if(D53>0;D53-D56-D57;0)')\n\
                                     \
                                     \
                                     \n\
                                     doc.new_sheet(\"Haber\")\n\n\
                                     doc.set_column_property(1, 'width', '0.5in')\n\
                                     doc.set_column_property(2, 'width', '5in')\n\
                                     doc.set_cell_property('bold', True)\n\
                                     doc.set_cell_value(2, 2, 'string', 'CUENTA DE PÉRDIDAS Y GANANCIAS')\n\
                                     doc.set_cell_value(2, 3, 'string', '" + QDateTime::currentDateTime().toString() + "')\n\
                                     doc.set_cell_value(4, 2, 'string', 'HABER')\n\
                                     doc.set_cell_value(2, 5, 'string', 'Periodo: de " + meses.at ( mesInicio ) + " a " + meses.at ( mesFin ) + "')\n\
                                     doc.set_cell_value(3, 5, 'string', '" + ejercicioActual + "')\n\
                                     doc.set_cell_value(4, 5, 'string', '" + ejercicioAnterior + "')\n\
                                     doc.set_cell_property('bold', False)\n\
                                     \
                                     doc.set_cell_property('bold', False)\n\
                                     \
                                     doc.set_cell_property('bold', True)\n\
                                     doc.set_cell_value(2, 7, 'string', 'B) INGRESOS')\n\
                                     doc.set_cell_value(3, 7, 'formula', '=C8+C12+C13+C14+C22+C26+C30+C35+C43+C44+C45+C46+C47')\n\
                                     doc.set_cell_value(4, 7, 'formula', '=D8+D12+D13+D14+D22+D26+D30+D35+D43+D44+D45+D46+D47')\n\
                                     doc.set_cell_property('bold', False)\n\
                                     \
                                     doc.set_cell_value(2, 8, 'string', '       1. Importe neto de la cifra de negocio')\n\
                                     doc.set_cell_value(3, 8, 'formula', '=SUM(C9:C11)')\n\
                                     doc.set_cell_value(4, 8, 'formula', '=SUM(D9:D11)')\n\
                                     \
                                     doc.set_cell_value(2, 9, 'string', '            a) Ventas')\n\
                                     doc.set_cell_value(3, 9, 'float', '" + ( -saldoCuenta ( 700 ) + ( -saldoCuenta ( 701 ) ) + ( -saldoCuenta ( 702 ) ) + ( -saldoCuenta ( 703 ) ) + ( -saldoCuenta ( 704 ) ) ).toQString ( '.' ) + "')\n\
                                     doc.set_cell_value(4, 9, 'float', '" + ( -saldoCuentaAnt ( 700 ) + ( -saldoCuentaAnt ( 701 ) ) + ( -saldoCuentaAnt ( 702 ) ) + ( -saldoCuentaAnt ( 703 ) ) + ( -saldoCuentaAnt ( 704 ) ) ).toQString ( '.' ) + "')\n\
                                     \
                                     doc.set_cell_value(2, 10, 'string', '            b) Prestaciones de servicios')\n\
                                     doc.set_cell_value(3, 10, 'float', '" + ( -saldoCuenta ( 705 ) ).toQString ( '.' ) + "')\n\
                                     doc.set_cell_value(4, 10, 'float', '" + ( -saldoCuentaAnt ( 705 ) ).toQString ( '.' ) + "')\n\
                                     \
                                     doc.set_cell_value(2, 11, 'string', '            c) Devoluciones y \"rappels\" sobre ventas')\n\
                                     doc.set_cell_value(3, 11, 'float', '" + ( ( saldoCuenta ( 708 ) ) + ( saldoCuenta ( 709 ) ) ).toQString ( '.' ) + "')\n\
                                     doc.set_cell_value(4, 11, 'float', '" + ( ( saldoCuentaAnt ( 708 ) ) + ( saldoCuentaAnt ( 709 ) ) ).toQString ( '.' ) + "')\n\
                                     \
                                     doc.set_cell_value(2, 12, 'string', '       2. Aumento de las existencias de productos terminados y en curso de fabricacion')\n\
                                     doc.set_cell_value(3, 12, 'float', '" + ( -saldoCuenta ( 71 ) ).toQString ( '.' ) + "')\n\
                                     doc.set_cell_value(4, 12, 'float', '" + ( -saldoCuentaAnt ( 71 ) ).toQString ( '.' ) + "')\n\
                                     \
                                     doc.set_cell_value(2, 13, 'string', '       3. Trabajos efectuados por la empresa para el inmobilizado')\n\
                                     doc.set_cell_value(3, 13, 'float', '" + ( -saldoCuenta ( 74 ) ).toQString ( '.' ) + "')\n\
                                     doc.set_cell_value(4, 13, 'float', '" + ( -saldoCuentaAnt ( 74 ) ).toQString ( '.' ) + "')\n\
                                     \
                                     doc.set_cell_value(2, 14, 'string', '       4. Otros ingresos de explotacion')\n\
                                     doc.set_cell_value(3, 14, 'formula', '=SUM(C15:C17)')\n\
                                     doc.set_cell_value(4, 14, 'formula', '=SUM(D15:D17)')\n\
                                     \
                                     doc.set_cell_value(2, 15, 'string', '            a) Ingresos accesorios y otros de gestion corriente')\n\
                                     doc.set_cell_value(3, 15, 'float', '" + ( -saldoCuenta ( 75 ) ).toQString ( '.' ) + "')\n\
                                     doc.set_cell_value(4, 15, 'float', '" + ( -saldoCuentaAnt ( 75 ) ).toQString ( '.' ) + "')\n\
                                     \
                                     doc.set_cell_value(2, 16, 'string', '            b) Subvenciones')\n\
                                     doc.set_cell_value(3, 16, 'float', '" + ( -saldoCuenta ( 74 ) ).toQString ( '.' ) + "')\n\
                                     doc.set_cell_value(4, 16, 'float', '" + ( -saldoCuentaAnt ( 74 ) ).toQString ( '.' ) + "')\n\
                                     \
                                     doc.set_cell_value(2, 17, 'string', '            c) Exceso de provisiones de riesgos y gastos')\n\
                                     doc.set_cell_value(3, 17, 'float', '" + ( -saldoCuenta ( 790 ) ).toQString ( '.' ) + "')\n\
                                     doc.set_cell_value(4, 17, 'float', '" + ( -saldoCuentaAnt ( 790 ) ).toQString ( '.' ) + "')\n\
                                     \
                                     " );

                                     barra.setValue ( barra.value() + 1 );

                                     codigoPython.append ( "\
                                     \
                                     doc.set_cell_value(2, 19, 'string', '   I.   PÉRDIDAS DE EXPLOTACIÓN')\n\
                                     doc.set_cell_value(2, 20, 'string', '        (A1+A2+A3+A4+A5+A6-B1-B2-B3-B4)')\n\
                                     doc.set_cell_value(3, 19, 'formula', '=IF(Debe.C8+Debe.C9+Debe.C13+Debe.C16+Debe.C17+Debe.C21-C8-C12-C13-C14>0;Debe.C8+Debe.C9+Debe.C13+Debe.C16+Debe.C17+Debe.C21-C8-C12-C13-C14;0)')\n\
                                     doc.set_cell_value(4, 19, 'formula', '=IF(Debe.D8+Debe.D9+Debe.D13+Debe.D16+Debe.D17+Debe.D21-D8-D12-D13-D14>0;Debe.D8+Debe.D9+Debe.D13+Debe.D16+Debe.D17+Debe.D21-D8-D12-D13-D14;0)')\n\
                                     \
                                     doc.set_cell_value(2, 22, 'string', '       5. Ingresos de participaciones en capital')\n\
                                     doc.set_cell_value(3, 22, 'formula', '=SUM(C23:C25)')\n\
                                     doc.set_cell_value(4, 22, 'formula', '=SUM(D23:D25)')\n\
                                     \
                                     doc.set_cell_value(2, 23, 'string', '            a) En empresas del grupo')\n\
                                     doc.set_cell_value(3, 23, 'float', '" + ( -saldoCuenta ( 7600 ) ).toQString ( '.' ) + "')\n\
                                     doc.set_cell_value(4, 23, 'float', '" + ( -saldoCuentaAnt ( 7600 ) ).toQString ( '.' ) + "')\n\
                                     \
                                     doc.set_cell_value(2, 24, 'string', '            b) En empresas asociadas')\n\
                                     doc.set_cell_value(3, 24, 'float', '" + ( -saldoCuenta ( 7601 ) ).toQString ( '.' ) + "')\n\
                                     doc.set_cell_value(4, 24, 'float', '" + ( -saldoCuentaAnt ( 7601 ) ).toQString ( '.' ) + "')\n\
                                     \
                                     doc.set_cell_value(2, 25, 'string', '            c) En empresas fuera del grupo')\n\
                                     doc.set_cell_value(3, 25, 'float', '" + ( -saldoCuenta ( 7603 ) ).toQString ( '.' ) + "')\n\
                                     doc.set_cell_value(4, 25, 'float', '" + ( -saldoCuentaAnt ( 7603 ) ).toQString ( '.' ) + "')\n\
                                     \
                                     doc.set_cell_value(2, 26, 'string', '       6. Ingresos de otros valores mobiliarios y de creditos del activo inmovilizado')\n\
                                     doc.set_cell_value(3, 26, 'formula', '=SUM(C27:C29)')\n\
                                     doc.set_cell_value(4, 26, 'formula', '=SUM(D27:D29)')\n\
                                     \
                                     doc.set_cell_value(2, 27, 'string', '            a) De empresas del grupo')\n\
                                     doc.set_cell_value(3, 27, 'float', '" + ( -saldoCuenta ( 7610 ) + ( -saldoCuenta ( 7620 ) ) ).toQString ( '.' ) + "')\n\
                                     doc.set_cell_value(4, 27, 'float', '" + ( -saldoCuentaAnt ( 7610 ) + ( -saldoCuentaAnt ( 7620 ) ) ).toQString ( '.' ) + "')\n\
                                     \
                                     doc.set_cell_value(2, 28, 'string', '            b) De empresas asociadas')\n\
                                     doc.set_cell_value(3, 28, 'float', '" + ( -saldoCuenta ( 7611 ) + ( -saldoCuenta ( 7621 ) ) ).toQString ( '.' ) + "')\n\
                                     doc.set_cell_value(4, 28, 'float', '" + ( -saldoCuentaAnt ( 7611 ) + ( -saldoCuentaAnt ( 7621 ) ) ).toQString ( '.' ) + "')\n\
                                     \
                                     doc.set_cell_value(2, 29, 'string', '            c) De empresas fuera del grupo')\n\
                                     doc.set_cell_value(3, 29, 'float', '" + ( -saldoCuenta ( 7613 ) + ( -saldoCuenta ( 7623 ) ) ).toQString ( '.' ) + "')\n\
                                     doc.set_cell_value(4, 29, 'float', '" + ( -saldoCuentaAnt ( 7613 ) + ( -saldoCuentaAnt ( 7623 ) ) ).toQString ( '.' ) + "')\n\
                                     \
                                     doc.set_cell_value(2, 30, 'string', '       7. Otros intereses e ingresos asimilados')\n\
                                     doc.set_cell_value(3, 30, 'formula', '=SUM(C31:C34)')\n\
                                     doc.set_cell_value(4, 30, 'formula', '=SUM(D31:D34)')\n\
                                     \
                                     doc.set_cell_value(2, 31, 'string', '            a) De empresas del grupo')\n\
                                     doc.set_cell_value(3, 31, 'float', '" + ( -saldoCuenta ( 7630 ) + ( -saldoCuenta ( 7650 ) ) ).toQString ( '.' ) + "')\n\
                                     doc.set_cell_value(4, 31, 'float', '" + ( -saldoCuentaAnt ( 7630 ) + ( -saldoCuentaAnt ( 7650 ) ) ).toQString ( '.' ) + "')\n\
                                     \
                                     doc.set_cell_value(2, 32, 'string', '            b) De empresas asociadas')\n\
                                     doc.set_cell_value(3, 32, 'float', '" + ( -saldoCuenta ( 7631 ) + ( -saldoCuenta ( 7651 ) ) ).toQString ( '.' ) + "')\n\
                                     doc.set_cell_value(4, 32, 'float', '" + ( -saldoCuentaAnt ( 7631 ) + ( -saldoCuentaAnt ( 7651 ) ) ).toQString ( '.' ) + "')\n\
                                     \
                                     doc.set_cell_value(2, 33, 'string', '            c) Otros intereses')\n\
                                     doc.set_cell_value(3, 33, 'float', '" + ( -saldoCuenta ( 7633 ) + ( -saldoCuenta ( 7653 ) ) + ( -saldoCuenta ( 769 ) ) ).toQString ( '.' ) + "')\n\
                                     doc.set_cell_value(4, 33, 'float', '" + ( -saldoCuentaAnt ( 7633 ) + ( -saldoCuentaAnt ( 7653 ) ) + ( -saldoCuentaAnt ( 769 ) ) ).toQString ( '.' ) + "')\n\
                                     \
                                     doc.set_cell_value(2, 34, 'string', '            d) Beneficios en inversiones financieras temporales')\n\
                                     doc.set_cell_value(3, 34, 'float', '" + ( -saldoCuenta ( 766 ) ).toQString ( '.' ) + "')\n\
                                     doc.set_cell_value(4, 34, 'float', '" + ( -saldoCuentaAnt ( 766 ) ).toQString ( '.' ) + "')\n\
                                     \
                                     doc.set_cell_value(2, 35, 'string', '       8. Diferencias positivas de cambio')\n\
                                     doc.set_cell_value(3, 35, 'float', '" + ( -saldoCuenta ( 768 ) ).toQString ( '.' ) + "')\n\
                                     doc.set_cell_value(4, 35, 'float', '" + ( -saldoCuentaAnt ( 768 ) ).toQString ( '.' ) + "')\n\
                                     \
                                     " );

                                     barra.setValue ( barra.value() + 1 );

                                     codigoPython.append ( "\
                                     \
                                     doc.set_cell_value(2, 37, 'string', '   II.  RESULTADOS FINANCIEROS NEGATIVOS')\n\
                                     doc.set_cell_value(2, 38, 'string', '        (A7+A8+A9+A10-B5-B6-B7-B8)')\n\
                                     doc.set_cell_value(3, 37, 'formula', '=IF(Debe.C30+Debe.C35+Debe.C36+Debe.C44-C22-C26-C30-C35>0;Debe.C30+Debe.C35+Debe.C36+Debe.C44-C22-C26-C30-C35;0)')\n\
                                     doc.set_cell_value(4, 37, 'formula', '=IF(Debe.D30+Debe.D35+Debe.D36+Debe.D44-D22-D26-D30-D35>0;Debe.D30+Debe.D35+Debe.D36+Debe.D44-D22-D26-D30-D35;0)')\n\
                                     \
                                     " );

                                     barra.setValue ( barra.value() + 1 );

                                     codigoPython.append ( "\
                                     \
                                     doc.set_cell_value(2, 40, 'string', '   III. PÉRDIDAS DE LAS ACTIVIDADES ORDINARIAS')\n\
                                     doc.set_cell_value(2, 41, 'string', '        (BI+BII-AI-AII)')\n\
                                     doc.set_cell_value(3, 40, 'formula', '=IF(C19+C37-Debe.C27-Debe.C38>0;C19+C37-Debe.C27-Debe.C38;0)')\n\
                                     doc.set_cell_value(4, 40, 'formula', '=IF(D19+D37-Debe.D27-Debe.D38>0;D19+D37-Debe.D27-Debe.D38;0)')\n\
                                     \
                                     doc.set_cell_value(2, 43, 'string', '       9. Beneficios en enajenacion de inmovilizado inmaterial, material y cartera de control')\n\
                                     doc.set_cell_value(3, 43, 'float', '" + ( -saldoCuenta ( 770 ) + ( -saldoCuenta ( 771 ) ) + ( -saldoCuenta ( 772 ) ) + ( -saldoCuenta ( 773 ) ) ).toQString ( '.' ) + "')\n\
                                     doc.set_cell_value(4, 43, 'float', '" + ( -saldoCuentaAnt ( 770 ) + ( -saldoCuentaAnt ( 771 ) ) + ( -saldoCuentaAnt ( 772 ) ) + ( -saldoCuentaAnt ( 773 ) ) ).toQString ( '.' ) + "')\n\
                                     \
                                     doc.set_cell_value(2, 44, 'string', '      10. Beneficios por operaciones con acciones y obligaciones propias')\n\
                                     doc.set_cell_value(3, 44, 'float', '" + ( -saldoCuenta ( 774 ) ).toQString ( '.' ) + "')\n\
                                     doc.set_cell_value(4, 44, 'float', '" + ( -saldoCuentaAnt ( 774 ) ).toQString ( '.' ) + "')\n\
                                     \
                                     doc.set_cell_value(2, 45, 'string', '      11. Subvenciones de capital transferidas al resultado del ejercicio')\n\
                                     doc.set_cell_value(3, 45, 'float', '" + ( -saldoCuenta ( 775 ) ).toQString ( '.' ) + "')\n\
                                     doc.set_cell_value(4, 45, 'float', '" + ( -saldoCuentaAnt ( 775 ) ).toQString ( '.' ) + "')\n\
                                     \
                                     doc.set_cell_value(2, 46, 'string', '      12. Ingresos extraordinarios')\n\
                                     doc.set_cell_value(3, 46, 'float', '" + ( -saldoCuenta ( 778 ) ).toQString ( '.' ) + "')\n\
                                     doc.set_cell_value(4, 46, 'float', '" + ( -saldoCuentaAnt ( 778 ) ).toQString ( '.' ) + "')\n\
                                     \
                                     doc.set_cell_value(2, 47, 'string', '      13. Ingresos y beneficios de otros ejercicios')\n\
                                     doc.set_cell_value(3, 47, 'float', '" + ( -saldoCuenta ( 779 ) ).toQString ( '.' ) + "')\n\
                                     doc.set_cell_value(4, 47, 'float', '" + ( -saldoCuentaAnt ( 779 ) ).toQString ( '.' ) + "')\n\
                                     \
                                     " );

                                     barra.setValue ( barra.value() + 1 );

                                     codigoPython.append ( "\
                                     \
                                     doc.set_cell_value(2, 49, 'string', '   IV. RESULTADOS EXTRAORDINARIOS NEGATIVOS')\n\
                                     doc.set_cell_value(2, 50, 'string', '       (A11+A12+A13+A14+A15-B9-B10-B11-B12-B13)')\n\
                                     doc.set_cell_value(3, 49, 'formula', '=IF(IF(Debe.C56>0;Debe.C56;0)+Debe.C45+Debe.C46+Debe.C47+Debe.C48-C43-C44-C45-C46-C47>0;IF(Debe.C56>0;Debe.C56;0)+Debe.C45+Debe.C46+Debe.C47+Debe.C48-C43-C44-C45-C46-C47;0)')\n\
                                     doc.set_cell_value(4, 49, 'formula', '=IF(IF(Debe.D56>0;Debe.D56;0)+Debe.D45+Debe.D46+Debe.D47+Debe.D48-D43-D44-D45-D46-D47>0;IF(Debe.D56>0;Debe.D56;0)+Debe.D45+Debe.D46+Debe.D47+Debe.D48-D43-D44-D45-D46-D47;0)')\n\
                                     \
                                     " );

                                     barra.setValue ( barra.value() + 1 );

                                     codigoPython.append ( "\
                                     \
                                     doc.set_cell_value(2, 52, 'string', '   V.  PÉRDIDAS ANTES DE IMPUESTOS')\n\
                                     doc.set_cell_value(2, 53, 'string', '       (BIII+BIV-AIII-AIV)')\n\
                                     doc.set_cell_value(3, 52, 'formula', '=IF(C40+C49-Debe.C41-Debe.C50>0;C40+C49-Debe.C41-Debe.C50;0)')\n\
                                     doc.set_cell_value(4, 52, 'formula', '=IF(D40+D49-Debe.D41-Debe.D50>0;D40+D49-Debe.D41-Debe.D50;0)')\n\
                                     \
                                     " );

                                     barra.setValue ( barra.value() + 1 );

                                     codigoPython.append ( "\
                                     \
                                     doc.set_cell_value(2, 55, 'string', '   VI. RESULTADO DEL EJERCICIO (PÉRDIDAS)')\n\
                                     doc.set_cell_value(2, 56, 'string', '       (BV+A15+A16)')\n\
                                     doc.set_cell_value(3, 55, 'formula', '=IF(C52>0;C52+Debe.C56+Debe.C57;0)')\n\
                                     doc.set_cell_value(4, 55, 'formula', '=IF(D52>0;D52+Debe.D56+Debe.D57;0)')\n\
                                     \
                                     \
# Guardamos el documento\n\
doc.save(\"canualesods.ods\")\n" );

                                                           return codigoPython;
                                                       }

