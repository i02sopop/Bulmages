###########################################
# Plugin for bulmafact                    #
###########################################
#pluginbf_clientealbaran

set (plugin pluginbf_clientealbaran)
set (docs README.es)

file(GLOB plugin_SRC *.c *.cpp *.cxx)
file(GLOB plugin_MOCS *.hpp *.h)
file(GLOB plugin_UIS *.ui)

set(QT_USE_QTASSISTANT true)
set(QT_USE_QTXML true)


configure_file( ${CMAKE_CURRENT_SOURCE_DIR}/css/${plugin}.css.in ${plugin}.css @ONLY)


INCLUDE( ${QT_USE_FILE} )

include_directories(
    ${QT_INCLUDE_DIR}
	${PGSQL_INCLUDE_DIR}
	${QT_QTXML_INCLUDE_DIR}
	${QT_QTASSISTANT_INCLUDE_DIR}
	${CMAKE_CURRENT_BINARY_DIR}
	${CMAKE_CURRENT_SOURCE_DIR}
	${CMAKE_BINARY_DIR}/bulmalib/src/
	${CMAKE_SOURCE_DIR}/bulmalib/src/
	${CMAKE_BINARY_DIR}/bulmafact/src/
	${CMAKE_SOURCE_DIR}/bulmafact/src/
	${CMAKE_BINARY_DIR}/bulmafact/plugins/pluginbf_cliente/
	${CMAKE_SOURCE_DIR}/bulmafact/plugins/pluginbf_cliente/
	${CMAKE_BINARY_DIR}/bulmafact/plugins/pluginbf_clientepresupuesto/
	${CMAKE_SOURCE_DIR}/bulmafact/plugins/pluginbf_clientepresupuesto/
	${CMAKE_BINARY_DIR}/bulmafact/plugins/pluginbf_clientepedido/
	${CMAKE_SOURCE_DIR}/bulmafact/plugins/pluginbf_clientepedido/
	${CMAKE_BINARY_DIR}/bulmafact/plugins/pluginbf_clientealbaran/
	${CMAKE_SOURCE_DIR}/bulmafact/plugins/pluginbf_clientealbaran/
	${CMAKE_BINARY_DIR}/bulmafact/plugins/pluginbf_clientefactura/
	${CMAKE_SOURCE_DIR}/bulmafact/plugins/pluginbf_clientefactura/)

# generate rules for building source files from the resources
#QT4_WRAP_CPP(plugin_MOC_SRCS ${plugin_MOCS})

# generate rules for building source files that moc generates
QT4_WRAP_UI(plugin_UIS_H ${plugin_UIS} OPTIONS -tr N_)
QT4_WRAP_CPP(plugin_MOC_SRCS ${plugin_MOCS})
#QT4_ADD_RESOURCES(plugin_RCC_SRCS ${plugin_RCCS})


# delete previous list of files to process (i18n)
#FILE(REMOVE ${CMAKE_BINARY_DIR}/bulmafact/plugins/${plugin}/${plugin}_pot_list)

#FOREACH(loop ${plugin_UIS_H} ${plugin_SRC})
#    FILE(APPEND ${CMAKE_BINARY_DIR}/bulmafact/plugins/${plugin}/${plugin}_pot_list ${loop} "\n")
#ENDFOREACH(loop)


#ADD_DEFINITIONS(${QT_DEFINITIONS})
ADD_DEFINITIONS(-DQT_SHARED)

# i18n
ADD_DEFINITIONS("-D'_(String)=BlI18n(\"${plugin}\", String)'" )
ADD_DEFINITIONS("-D'N_(String, Int)=BlI18n(\"${plugin}\", String)'" )

if(USE_GETTEXT)
   set(plugin_i18n ${plugin_SRC} ${plugin_MOC_SRCS} ${plugin_UIS_H}
                        ${plugin_SRCS} ${plugin_MOCS})
   GETTEXT_CREATE_TEMPLATE(${plugin} ${CMAKE_CURRENT_BINARY_DIR}
                                ${CMAKE_CURRENT_SOURCE_DIR} plugin_i18n)
   GETTEXT_CREATE_TRANSLATIONS(${CMAKE_CURRENT_BINARY_DIR}/${plugin}.pot
                                ALL LANGUAGES es_ES.UTF-8 ca_ES.UTF-8)
endif(USE_GETTEXT)


# build sources, moc'd sources, and rcc'd sources

if(APPLE)
  set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -undefined dynamic_lookup")
endif(APPLE)

add_library(${plugin} SHARED ${plugin_SRC} ${plugin_MOC_SRCS}
	${plugin_UIS_H} ${plugin_SRCS} ${plugin_MOCS})


set_target_properties( ${plugin} PROPERTIES 
  SOVERSION "${BULMAGES_VERSION_MAJOR}.${BULMAGES_VERSION_MINOR}"
  VERSION "${BULMAGES_VERSION}")

target_link_libraries(${plugin} libbulmafact bulmalib ${QT_LIBRARIES} ${PGSQL_LIBRARIES})


# i18n
#GETTEXT_CREATE_TEMPLATE(${plugin} ${CMAKE_BINARY_DIR}/bulmafact/plugins/${plugin} ${CMAKE_SOURCE_DIR}/bulmafact/plugins/${plugin} ${CMAKE_BINARY_DIR}/bulmafact/plugins/${plugin}/${plugin}_pot_list)
#GETTEXT_CREATE_TRANSLATIONS (${CMAKE_BINARY_DIR}/bulmafact/plugins/${plugin}/${plugin}.pot ALL LANGUAGES es_ES.UTF-8 ca_ES.UTF-8)

# i18n commands executed after build.
#ADD_CUSTOM_COMMAND(TARGET ${plugin} POST_BUILD COMMAND make ${plugin}.pot WORKING_DIRECTORY ${CMAKE_BINARY_DIR})
#ADD_CUSTOM_COMMAND(TARGET ${plugin} POST_BUILD COMMAND make ${plugin}_pos WORKING_DIRECTORY ${CMAKE_BINARY_DIR})


install_targets(/lib/bulmafact/plugins ${plugin})

foreach(dfile ${docs})
   install (FILES ${dfile} DESTINATION share/bulmages/bulmafact-plugins/ RENAME ${dfile}.${plugin})
endforeach(dfile in ${docs})

add_dependencies(${plugin} bulmafact bulmalib pluginbf_clientepresupuesto pluginbf_clientepedido)

FILE(READ ${CMAKE_BINARY_DIR}/${plugin}.css VAR_CSS)
FILE(APPEND ${CMAKE_BINARY_DIR}/css/bulmafact.css "${VAR_CSS}" )

install(DIRECTORY images DESTINATION share/bulmages PATTERN ".svn" EXCLUDE)