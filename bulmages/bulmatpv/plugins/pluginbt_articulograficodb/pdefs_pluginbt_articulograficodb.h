#ifndef PDEFS_PLUGINBT_ARTICULOGRAFICODB_H
#define PDEFS_PLUGINBT_ARTICULOGRAFICODB_H


#ifdef Q_OS_WIN32

#ifdef PLUGINBT_ARTICULOGRAFICODB
#define PLUGINBT_ARTICULOGRAFICODB_EXPORT __declspec(dllexport)
#else
#define PLUGINBT_ARTICULOGRAFICODB_EXPORT __declspec(dllimport)
#endif

#else

#define PLUGINBT_ARTICULOGRAFICODB_EXPORT

#endif


#endif

