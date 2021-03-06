/***************************************************************************
 *   Copyright (C) 2011 by Fco. Javier M. C.                               *
 *   fcojavmc@todo-redes.com                                               *
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

#include <QtPlugin>

#include "widgetbf_buscarreferencia.h"


WidgetBf_BuscarReferencia::WidgetBf_BuscarReferencia(QObject *parent)
    : QObject(parent)
{
    initialized = false;
}


void WidgetBf_BuscarReferencia::initialize(QDesignerFormEditorInterface *formEditor)
{
    if (initialized)
        return;

    initialized = true;
}


bool WidgetBf_BuscarReferencia::isInitialized() const
{
    return initialized;
}


QWidget *WidgetBf_BuscarReferencia::createWidget(QWidget *parent)
{
    return new BfBuscarReferencia(parent);
}


QString WidgetBf_BuscarReferencia::name() const
{
    return "BfBuscarReferencia";
}


QString WidgetBf_BuscarReferencia::group() const
{
    return "Iglues/BulmaFact";
}


QIcon WidgetBf_BuscarReferencia::icon() const
{
    return QIcon();
}


QString WidgetBf_BuscarReferencia::toolTip() const
{
    return "";
}


QString WidgetBf_BuscarReferencia::whatsThis() const
{
    return "";
}


bool WidgetBf_BuscarReferencia::isContainer() const
{
    return false;
}


QString WidgetBf_BuscarReferencia::domXml() const
{

    QString xml =  "<ui language=\"c++\">\n"
           " <widget class=\"BfBuscarReferencia\" name=\"mui_buscarReferencia\">\n"
           "  <property name=\"geometry\">\n"
           "   <rect>\n"
           "    <x>0</x>\n"
           "    <y>0</y>\n"
           "    <width>140</width>\n"
           "    <height>30</height>\n"
           "   </rect>\n"
           "  </property>\n"
           "  <property name=\"toolTip\" >\n"
           "   <string>BfBuscarReferencia</string>\n"
           "  </property>\n"
           "  <property name=\"whatsThis\" >\n"
           "   <string>BfBuscarReferencia</string>\n"
           "  </property>\n"
           " </widget>\n"
           "</ui>\n";



    return xml;
}


QString WidgetBf_BuscarReferencia::includeFile() const
{
    return "bfbuscarreferencia.h";
}


Q_EXPORT_PLUGIN2(widgetbf_buscarreferencia, WidgetBf_BuscarReferencia)

