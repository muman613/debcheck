#ifndef __DBGUTILS_H__
#define __DBGUTILS_H__

#include <assert.h>

/**
 *  Another version of dbgutils.h
 *
 *  Looks like 'D(ebug("format %s", sValue));'
 *
 */

#ifdef  _DEBUG

#define D(x) (x)

void ebug(const char* szFmt, ...);

#else   // _DEBUG

#define D(x) /* (x) */

#endif  // _DEBUG

#endif // __DBGUTILS_H__

