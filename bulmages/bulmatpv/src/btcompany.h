/***************************************************************************
 *   Copyright (C) 2004 by Tomeu Borras Riera                              *
 *   tborras@conetxia.com                                                  *
 *   http://www.iglues.org                                                 *
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

#ifndef BTCOMPANY_H
#define BTCOMPANY_H

#include <QObject>
#include <QAssistantClient>
#include <QLibraryInfo>

#include "blpostgresqlclient.h"
#include "listventanas.h"
#include "blworkspace.h"
#include "blmaincompany.h"
#include "blsplashscreen.h"
#include "ticket.h"
#include "input.h"


class BulmaTPV;

/// Clase company (empresa).
/** Clase principal del programa donde se almacenan y gestionan
    todos los datos de la empresa con la que se est&aacute; trabajando.
    Deriva de postgresiface ya que tiene el tratamiento de la base de datos. */
class BtCompany : public BlMainCompany, public Input
{
private:
    /// Puntero al mainWindow
    BulmaTPV *m_bulmaTPV;
    QList<Ticket *> m_listaTickets;
    Ticket *m_ticketActual;

public:
    BtCompany ( BulmaTPV *bges );
    virtual ~BtCompany();
    void createMainWindows ( BlSplashScreen * );
    void guardaConf();
    void cargaConf();
    Ticket *newTicket();
    void cobrar();
    void z();
    void x();
    Ticket *ticketActual();
    QList<Ticket *> *listaTickets();
    void setTicketActual ( Ticket *tick );

};

#endif
