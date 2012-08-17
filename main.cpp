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
#include "dbgutils.h"

using namespace std;

char*       szControlFile   = 0L;
bool        gVerbose        = false;

/** Popt options array. */

struct poptOption poptions[] = {
    { "control", 'c', POPT_ARG_STRING, &szControlFile, 0,   "Control file", "XML File" },
    { NULL,      'v', POPT_ARG_NONE,   NULL,           'v', "Enable verbose messages", },

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
        case 'v':
            gVerbose = true;
            break;

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
    int             nRes = 0;
    int             cntInstOK = 0,
                    cntInstWrongVer = 0,
                    cntNotInst = 0;

    if (!parse_args( argc, argv )) {
        return -10;
    }

//    printf("Control file = %s\n", szControlFile);

    if (!dpkg_system_open()) {
        fprintf(stderr, "ERROR: Unable to open dpkg library!\n");
        return -1;
    }

    /* Load the control file, if failed print error and exit. */
    if (xml_load_controlfile( szControlFile, packageDB )) {
        printf("-- control file loaded ok!\n");

        if (gVerbose)
            packageDB.Dump(stdout);

#ifdef _EXTRA_EXTRA_DEBUG
        dpkg_dump_installed();
#endif

        DEB_PACKAGE_VECTOR_ITER pIter;
        for (pIter = packageDB.begin() ; pIter != packageDB.end() ; pIter++) {
            STRING          sPackName, sPackVers;
            debPackage      pkg = *pIter;

            sPackName = pkg.PackageName();
            sPackVers = pkg.PackageVersion();

            D(ebug("-- processing package [%s - %s]\n",
                   sPackName.c_str(),
                   sPackVers.c_str()));

            if (dpkg_is_package_installed(sPackName.c_str(),
                                          sPackVers.c_str()))
            {
                printf("Package %s version %s installed!\n",
                       sPackName.c_str(), sPackVers.c_str());
                cntInstOK++;
            }
            else
            {
                STRING sActualVers;

                if (dpkg_get_package_version( sPackName.c_str(), sActualVers ))
                {
                    printf("WARNING: Package %s installed BUT version %s NOT version %s!\n",
                           sPackName.c_str(), sActualVers.c_str(), sPackVers.c_str());
                    cntInstWrongVer++;
                } else {
                    printf("ERROR: Package %s IS NOT installed!\n",
                           sPackName.c_str());
                    cntNotInst++;
                }
            }
        }

        if (gVerbose) {
            printf("STAT : %d Installed / %d Wrong Version / %d Not Installed\n",
                   cntInstOK, cntInstWrongVer, cntNotInst);
        }


    } else {
        fprintf(stderr, "ERROR: Unable to parse control file!\n");
        nRes = -10;
    }

    dpkg_system_close();

    return nRes;
}

#if 0
        if (dpkg_is_package_installed("antiword")) {

            printf("Package is installed!\n");

            if (dpkg_is_package_installed("antiword", "0.37-6")) {
                printf("Package 0.37-6 is installed!\n");
            } else {
                STRING sVersion;
                dpkg_get_package_version("antiword", sVersion);
                printf("antiword version %s is installed!\n", sVersion.c_str());
            }
        }
#endif
