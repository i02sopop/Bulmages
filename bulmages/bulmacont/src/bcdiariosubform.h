/***************************************************************************
 *   Copyright (C) 2003 by Tomeu Borras Riera                              *
 *   tborras@conetxia.com                                                  *
 *   http://www.iglues.org Asociación Iglues -- Contabilidad Linux         *
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

#ifndef BCDIARIOSUBFORM_H
#define BCDIARIOSUBFORM_H

#include "bccompany.h"
#include "bcsubform.h"
#include "blwidget.h"
#include "bldefs.h"

///
/** SubFormulario de la pantalla de Diario.*/


class BC_EXPORT BcDiarioSubForm : public BcSubForm
{
    Q_OBJECT

public:
    BcDiarioSubForm ( QWidget *parent = 0, const char *name = 0 );
    virtual ~BcDiarioSubForm();

public slots:
    virtual void s_pintaMenu ( QMenu *menu );
    virtual void s_trataMenu ( QAction *action );
};

#endif
