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

#ifdef Q_WS_WIN
# define MY_EXPORT __declspec(dllexport)
#else
# define MY_EXPORT
#endif

#include "blpostgresqlclient.h"
#include "bulmafact.h"
#include "blwidget.h"
#include "provedit.h"
#include "busquedareferencia.h"
#include "facturapview.h"
#include "albaranproveedorview.h"
#include "pedidoproveedorview.h"


extern "C" MY_EXPORT int SNewFacturaProveedorView (BfCompany *);
extern "C" MY_EXPORT int entryPoint ( Bulmafact * );
extern "C" MY_EXPORT int BfCompany_createMainWindows_Post(BfCompany *);
extern "C" MY_EXPORT int ProveedorView_ProveedorView_Post (ProveedorView *);
extern "C" MY_EXPORT int ProveedorView_cargarPost_Post (ProveedorView *);
extern "C" MY_EXPORT int BusquedaReferencia_on_mui_abrirtodo_clicked_Post (BusquedaReferencia *);
extern "C" MY_EXPORT int AlbaranProveedorView_AlbaranProveedorView ( AlbaranProveedorView * );
extern "C" MY_EXPORT int PedidoProveedorView_PedidoProveedorView ( PedidoProveedorView * );


// 
class mypluginfactp : public QObject, BlMainCompanyPointer
{
    Q_OBJECT

public:
    Bulmafact *m_bges;

public:
    mypluginfactp();
    ~mypluginfactp();
    void inicializa ( Bulmafact * );

public slots:
    void elslot();
    void elslot1();
};