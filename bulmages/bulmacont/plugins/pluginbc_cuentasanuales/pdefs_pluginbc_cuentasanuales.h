#ifndef PDEFS_PLUGINBC_CUENTASANUALES_H
#define PDEFS_PLUGINBC_CUENTASANUALES_H


#ifdef WIN32

#ifdef PLUGINBC_CUENTASANUALES
#define PLUGINBC_CUENTASANUALES_EXPORT __declspec(dllexport)
#else
#define PLUGINBC_CUENTASANUALES_EXPORT __declspec(dllimport)
#endif

#else

#define PLUGINBC_CUENTASANUALES_EXPORT

#endif


#endif
