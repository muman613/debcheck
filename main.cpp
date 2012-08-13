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

#include <dpkg/i18n.h>
#include <dpkg/dpkg.h>
#include <dpkg/dpkg-db.h>
#include <dpkg/pkg-array.h>
#include <dpkg/path.h>
//#include <dpkg/myopt.h>
#include "dpkg_interface.h"

using namespace std;

//const char* admindir   = "/var/lib/dpkg";
//const char  thisname[] = "debcheck";

/**
 *
 */

int main() {
    //struct pkg_array array;
    //struct pkginfo *pkg;

    if (!dpkg_system_open()) {
        fprintf(stderr, "ERROR: Unable to open dpkg library!\n");
        return -1;
    }

#if 1
    PackageArray    pkgArray;
    PackageArray::pkgiter pIter;
    struct pkginfo *pkg;

    for (pIter = pkgArray.begin() ; pIter != pkgArray.end() ; pIter++) {
        pkg = *pIter;
        if (pkg->status == pkginfo::stat_notinstalled) continue;
        printf("%-40s %s-%s\n", pkg->set->name,
                                pkg->configversion.version,
                                pkg->configversion.revision);
    }

#else
    pkg_array_init_from_db(&array);
    pkg_array_sort(&array, pkg_sorter_by_name);

    for (int i = 0; i < array.n_pkgs; i++) {
        pkg = array.pkgs[i];
        if (pkg->status == pkginfo::stat_notinstalled) continue;
        printf("%-40s %s-%s\n", pkg->set->name,
                                pkg->configversion.version,
                                pkg->configversion.revision);
//      list1package(pkg, &head, &array);
    }
#endif

    dpkg_system_close();

    return 0;
}
