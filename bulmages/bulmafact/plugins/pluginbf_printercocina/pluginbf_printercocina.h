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

#ifndef PLUGINBF_PRINTERCOCINA_H
#define PLUGINBF_PRINTERCOCINA_H

#include <QtCore/QObject>
#include "bfbulmafact.h"
#include "blform.h"
#include "bfsubform.h"
#include "articuloview.h"
#include "articulolist.h"
#include "pdefs_pluginbf_printercocina.h"


extern "C" PLUGINBF_PRINTERCOCINA_EXPORT int entryPoint ( BfBulmaFact * );
extern "C" PLUGINBF_PRINTERCOCINA_EXPORT int ArticuloView_ArticuloView_Post ( ArticuloView * );

#endif

