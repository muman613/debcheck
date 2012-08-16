/**
 *  @file   main.cpp
 *  @date   August 10, 2012
 *  @author Michael Uman
 *
 *  @brief  This application checks whether packages are installed, if not
 *          it will ask to install them.
 */

#include <config.h>
#include <compat.h>
#include <stdlib.h>
#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <popt.h>

#include "basicTypes.h"
#include "dpkg_interface.h"
#include "xml_interface.h"
#include "debPackageDB.h"

using namespace std;

char*       szControlFile = 0L;

struct poptOption poptions[] = {
    { "control", 'c', POPT_ARG_STRING, &szControlFile, 0, "Control file", "XML File" },
    POPT_AUTOHELP
    POPT_TABLEEND
};

/**
 *  Parse the commandline using the popt library.
 */

bool parse_args(int argc, const char* argv[])
{
    bool        bRes = false;
    poptContext poptCon;
    char        rc;

    poptCon = poptGetContext( "debcheck", argc, argv, poptions, 0 );

    while ((rc = poptGetNextOpt( poptCon )) > 0) {
        switch (rc) {
        default:
            break;
        }
    }

    bRes = (szControlFile != 0);
    poptFreeContext( poptCon );

    return bRes;
}

/**
 *
 */

int main(int argc, const char* argv[]) {
    debPackageDB    packageDB;

    if (!parse_args( argc, argv )) {
        return -10;
    }

//    printf("Control file = %s\n", szControlFile);

    if (!dpkg_system_open()) {
        fprintf(stderr, "ERROR: Unable to open dpkg library!\n");
        return -1;
    }

    if (xml_load_controlfile( szControlFile, packageDB )) {
        printf("-- control file loaded ok!\n");
        packageDB.Dump(stdout);

#ifdef _EXTRA_EXTRA_DEBUG
        dpkg_dump_installed();
#endif

        if (dpkg_is_package_installed("antiword", NULL)) {

            printf("Package is installed!\n");

            if (dpkg_is_package_installed("antiword", "0.37-6")) {
                printf("Package 0.37-6 is installed!\n");
            } else {
                STRING sVersion;
                dpkg_get_package_version("antiword", sVersion);
                printf("antiword version %s is installed!\n", sVersion.c_str());
            }
        }
    } else {
    }

    dpkg_system_close();

    return 0;
}
