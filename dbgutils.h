#ifndef __DBGUTILS_H__
#define __DBGUTILS_H__

/**
 *  Another version of dbgutils.h
 */

#ifdef  _DEBUG

#define D(x) (x)

void ebug(const char* szFmt, ...);

#else   // _DEBUG

#define D(x) /* (x) */

#endif  // _DEBUG

#endif // __DBGUTILS_H__

