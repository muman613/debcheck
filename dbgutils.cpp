/**
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

#include "dbgutils.h"

#ifdef  _DEBUG

FILE*       fDbgOut = stderr;

void ebug(const char* szFmt, ...) {
    va_list ap;

    va_start(ap, szFmt);
    vfprintf(fDbgOut, szFmt, ap);
    va_end(ap);

    return;
}

#endif
