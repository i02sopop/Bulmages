#ifndef PDEFS_PLUGINBT_ARTICULOGRAFICO_H
#define PDEFS_PLUGINBT_ARTICULOGRAFICO_H


#ifdef Q_OS_WIN32

#ifdef PLUGINBT_ARTICULOGRAFICO
#define PLUGINBT_ARTICULOGRAFICO_EXPORT __declspec(dllexport)
#else
#define PLUGINBT_ARTICULOGRAFICO_EXPORT __declspec(dllimport)
#endif

#else

#define PLUGINBT_ARTICULOGRAFICO_EXPORT

#endif


#endif

