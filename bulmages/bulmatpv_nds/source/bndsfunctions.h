/***************************************************************************
 *                                                                         *
 *   BulmaTPV remote client for Nintendo DS console.                       *
 *   -----------------------------------------------                       *
 *                                                                         *
 *   Copyright (C) 2010 by Fco. Javier M. C.                               *
 *   comercial@todo-redes.com                                              *
 *   http://www.todo-redes.com                                             *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation, either version 3 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program.  If not, see <http://www.gnu.org/licenses/>. *
 *                                                                         *
 ***************************************************************************/

#ifndef BNDSFUNCTIONS_H
#define BNDSFUNCTIONS_H

#include <nds.h>
#include <stdio.h>
#include <string>
#include <list>

#include "bndsreadfilecontent.h"

using namespace std;


unsigned long ipToLong(string ip);

int callback_processConfigFile(int event, const char* txt, int len, void* tuser);
int callback_processCategoryArticles(int event, const char* txt, int len, void* tuser);

void callback_keyboardOnKeyPressed(int key);

u8 getPixel8bpp ( int x, int y, u16* buffer );
void drawPixel8bpp ( int x, int y, u16 paletteIndex, u16* buffer );
void drawPixel1bpp ( int x, int y, bool color, u8* buffer, u16 offset );
void drawRectangle8bpp ( int x1, int y1, int x2, int y2, u16 paletteIndex, u16* buffer);
void drawLine(int x1, int y1, int x2, int y2, int widthX, int heightY, u16 paletteIndex, u16* buffer);
string float2string3x2 (float number);
void debugStop();
void write8(u8* address, u8 value);
void write16(u16* address, u16 value);
void write32(u32* address, u32 value);
string strHex2IntWep128(string cadena);
string readWholeFileContent(string fileName);

#endif

