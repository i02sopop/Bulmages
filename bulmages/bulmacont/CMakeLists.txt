# Copyright (C) 2008 by Leopold Palomo-Avellaneda                       #
# leo@alaxarxa.net                                                      #
# Modified (C) 2013 by Daniel Ripoll                                                     #
# http://www.iglues.org                                                 #
#                                                                       #
# This program is free software; you can redistribute it and/or modify  #
# it under the terms of the GNU General Public License as published by  #
# the Free Software Foundation; either version 2 of the License, or     #
# (at your option) any later version.                                   #
#                                                                       #
# This program is distributed in the hope that it will be useful,       #
# but WITHOUT ANY WARRANTY; without even the implied warranty of        #
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         #
# GNU General Public License for more details.                          #
#                                                                       #
# You should have received a copy of the GNU General Public License     #
# along with this program; if not, write to the                         #
# Free Software Foundation, Inc.,                                       #
# 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             #
#                                                                       #
#########################################################################


PROJECT(bulmacont)

cmake_policy(SET CMP0020 OLD)

FILE(READ css/bulmacont_es_ES.css VAR_CSS_es_ES)
FILE(APPEND ${CMAKE_BINARY_DIR}/css/bulmacont_es_ES.css "${VAR_CSS_es_ES}" )

FILE(READ css/bulmacont_ca_ES.css VAR_CSS_ca_ES)
FILE(APPEND ${CMAKE_BINARY_DIR}/css/bulmacont_ca_ES.css "${VAR_CSS_ca_ES}" )

FILE(READ css/bulmacont_fr_FR.css VAR_CSS_fr_FR)
FILE(APPEND ${CMAKE_BINARY_DIR}/css/bulmacont_fr_FR.css "${VAR_CSS_fr_FR}" )

FILE(READ css/bulmacont_en_EN.css VAR_CSS_en_EN)
FILE(APPEND ${CMAKE_BINARY_DIR}/css/bulmacont_en_EN.css "${VAR_CSS_en_EN}" )

add_subdirectory(src)

add_subdirectory(plugins)


SET(QT_USE_QTUITOOLS TRUE)
SET(QT_USE_QTXML TRUE) # uitools depends on xml
SET(QT_USE_QTWEBKIT TRUE)

# if you want to add some private code
# simple put your add_directory in a
# CMakeLists.txt.private


if(EXISTS "${CMAKE_SOURCE_DIR}/bulmacont/CMakeLists.txt.private")
   message(STATUS "Private code inserted in bulmacont")
   include("${CMAKE_SOURCE_DIR}/bulmacont/CMakeLists.txt.private")
endif(EXISTS "${CMAKE_SOURCE_DIR}/bulmacont/CMakeLists.txt.private")


