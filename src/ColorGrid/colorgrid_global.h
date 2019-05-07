#pragma once

#include <QtCore/qglobal.h>

#ifndef BUILD_STATIC
# if defined(COLORGRID_LIB)
#  define COLORGRID_EXPORT Q_DECL_EXPORT
# else
#  define COLORGRID_EXPORT Q_DECL_IMPORT
# endif
#else
# define COLORGRID_EXPORT
#endif
