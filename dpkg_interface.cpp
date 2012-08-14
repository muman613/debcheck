/**
 *  @file   dpkg_interface.cpp
 *  @author Michael Uman
 *  @date   August 13, 2012
 */

#include <stdio.h>
#include <stdlib.h>
#include "dpkg_interface.h"
#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>

PackageArray::PackageArray()
{
    //init();
}

PackageArray::~PackageArray()
{

}

void PackageArray::init() {
    pkg_array_init_from_db(&m_array);
    pkg_array_sort(&m_array, pkg_sorter_by_name);
}

size_t PackageArray::size() {
    return m_array.n_pkgs;
}

/**
 *  Iterator class.
 */

PackageArray::pkgiter::pkgiter(PackageArray* pParent, size_t index)
:   m_pParent(pParent),
    m_nIndex(index)
{
}

PackageArray::pkgiter::pkgiter() {}

PackageArray::pkgiter::~pkgiter() {}

pkginfo* PackageArray::pkgiter::operator *() {
    return (pkginfo*)m_pParent->m_array.pkgs[m_nIndex];
}

const PackageArray::pkgiter& PackageArray::pkgiter::operator++(int) {
    m_nIndex++;
    return *this;
}

bool PackageArray::pkgiter::operator !=(const PackageArray::pkgiter& comp) {
    //printf("index %d comp.index %d\n", m_nIndex, comp.m_nIndex);
    return (m_nIndex != comp.m_nIndex);
}

PackageArray::pkgiter& PackageArray::pkgiter::operator =(const PackageArray::pkgiter& copy)
{
    m_pParent = copy.m_pParent;
    m_nIndex = copy.m_nIndex;

    return *this;
}

PackageArray::pkgiter PackageArray::begin()
{
    //printf("begin()\n");
    PackageArray::pkgiter thisIter(this);

    return thisIter;
}

PackageArray::pkgiter PackageArray::end()
{
    //printf("end()\n");
    PackageArray::pkgiter thisIter(this, m_array.n_pkgs);

    return thisIter;
}

PackageArray            pkgArray;

/**
 *
 */

bool dpkg_system_open() {
    fprintf(stderr, "dpkg_system_open()\n");

    standard_startup();
    modstatdb_init();
    modstatdb_open(msdbrw_readonly);
    //printf("Using directory : %s\n", dpkg_db_get_dir());

    pkgArray.init();

    return true;
}

/**
 *
 */

void dpkg_system_close() {
    modstatdb_shutdown();
    standard_shutdown();

    return;
}

/**
 *  Dump all installed package names to FILE...
 */

void dpkg_dump_installed(FILE* fOut) {
    PackageArray::pkgiter   pIter;
    struct pkginfo*         pkg;
    const char*             sVersion;

    for (pIter = pkgArray.begin() ; pIter != pkgArray.end() ; pIter++) {
        pkg = *pIter;

        if (pkg->status == pkginfo::stat_notinstalled)
            continue;

        sVersion = versiondescribe( &pkg->configversion, vdew_nonambig);

        printf("%-40s : %s\n", pkg->set->name, sVersion);
    }

    return;
}

/**
 *  Determine if a package is installed.
 */

bool dpkg_is_package_installed(const char* szPackageName,
                          const char* szPackageRevision)
{
    PackageArray::pkgiter   pIter;
    struct pkginfo*         pkg;
    const char*             sVersion;

    for (pIter = pkgArray.begin() ; pIter != pkgArray.end() ; pIter++) {
        pkg = *pIter;

        if (strcmp(szPackageName, pkg->set->name) == 0) {
            if (szPackageRevision != 0L) {
                sVersion = versiondescribe( &pkg->configversion, vdew_nonambig);

                if (strcmp(szPackageRevision, sVersion) == 0) {
                    return true;
                } else {
                    return false;
                }
            } else {
                return true;
            }
        }
    }

    return false;
}
