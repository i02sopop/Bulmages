#ifndef PDEFS_PLUGINBT_TECLADONUMERICO_H
#define PDEFS_PLUGINBT_TECLADONUMERICO_H


#ifdef WIN32

#ifdef PLUGINBT_TECLADONUMERICO
#define PLUGINBT_TECLADONUMERICO_EXPORT __declspec(dllexport)
#else
#define PLUGINBT_TECLADONUMERICO_EXPORT __declspec(dllimport)
#endif

#else

#define PLUGINBT_TECLADONUMERICO_EXPORT

#endif


#endif
