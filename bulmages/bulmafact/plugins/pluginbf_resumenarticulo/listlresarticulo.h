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

#ifndef LISTLRESARTICULO_H
#define LISTLRESARTICULO_H

#include "bltablewidget.h"
#include "bfsubform.h"
#include "blwidget.h"
#include "bfbulmafact.h"


class ListLResArticulo : public BfSubForm
{
    Q_OBJECT

public:
    QString mdb_idarticulo;
    ListLResArticulo ( QWidget *parent = 0 );
    ~ListLResArticulo() {};

public slots:
    virtual void load ( QString idarticulo );
};


class ListEntregas : public BfSubForm
{
    Q_OBJECT

public:
    QString mdb_idarticulo;
    ListEntregas ( QWidget *parent = 0 );
    ~ListEntregas() {};

public slots:
    virtual void load ( QString idarticulo );
};

class ListCompras : public BfSubForm
{
    Q_OBJECT

public:
    QString mdb_idarticulo;
    ListCompras ( QWidget *parent = 0 );
    ~ListCompras() {};

public slots:
    virtual void load ( QString idarticulo );
};

class ListRecogidas : public BfSubForm
{
    Q_OBJECT

public:
    QString mdb_idarticulo;
    ListRecogidas ( QWidget *parent = 0 );
    ~ListRecogidas() {};

public slots:
    virtual void load ( QString idarticulo );
};

#endif

