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
#include <dpkg/myopt.h>

using namespace std;

const char* admindir   = "/var/lib/dpkg";
const char  thisname[] = "debcheck";

/**
 *
 */

int main() {
    jmp_buf ejbuf;
    struct pkg_array array;
    struct pkginfo *pkg;

    standard_startup(&ejbuf);

    modstatdb_init(admindir,msdbrw_readonly);

    pkg_array_init_from_db(&array);
    pkg_array_sort(&array, pkg_sorter_by_name);

    for (int i = 0; i < array.n_pkgs; i++) {
        pkg = array.pkgs[i];
        if (pkg->status == pkginfo::stat_notinstalled) continue;
        printf("%-40s %s-%s\n", pkg->name,
                                pkg->configversion.version,
                                pkg->configversion.revision);
//      list1package(pkg, &head, &array);
    }

    pkg_array_free(&array);
    modstatdb_shutdown();
    standard_shutdown();

    return 0;
}
