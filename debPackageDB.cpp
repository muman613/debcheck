/**
 *  @file       debPackageDB.cpp
 *  @author     Michael A. Uman
 *  @date       August 15, 2012
 *  @brief      This file contains the definition of debPackage and
 *              debPackageDB.
 */

#include "debPackageDB.h"
#include "dbgutils.h"

debPackage::debPackage(STRING sPackageName, STRING sPackageVersion)
:   m_sPackageName(sPackageName),
    m_sPackageVersion(sPackageVersion)
{
    // ctor
}

debPackage::debPackage(const debPackage& copy)
:   m_sPackageName(copy.m_sPackageName),
    m_sPackageVersion(copy.m_sPackageVersion)
{
    // copy ctor
}

debPackage::~debPackage()
{
    // dtor
}

STRING debPackage::PackageName() const {
    return m_sPackageName;
}

STRING debPackage::PackageVersion() const {
    return m_sPackageVersion;
}

debPackage& debPackage::operator = (const debPackage& copy)
{
    m_sPackageName    = copy.m_sPackageName;
    m_sPackageVersion = copy.m_sPackageVersion;

    return *this;
}

/**
 *
 */

debPackageDB::debPackageDB()
{
    //ctor
    D(ebug("debPackageDB::debPackageDB()\n"));
}

debPackageDB::~debPackageDB()
{
    //dtor
    D(ebug("debPackageDB::~debPackageDB()\n"));
}

size_t debPackageDB::size() {
    return m_packageVec.size();
}

void debPackageDB::clear() {
    m_packageVec.clear();
}

void debPackageDB::Add(STRING sPackageName, STRING sPackageVersion)
{
    debPackage      newPackage(sPackageName, sPackageVersion);

    D(ebug("Adding package %s version %s\n",
            sPackageName.c_str(),
            sPackageVersion.c_str()));

    m_packageVec.push_back( newPackage );
}

/**
 *  Send list of all packages in database to output.
 */

void debPackageDB::Dump(FILE* fOut) {
    D(ebug("debPackageDB::Dump\n"));

    for (size_t i = 0 ; i < size() ; i++) {
        fprintf(fOut, "%-40s : %s\n", m_packageVec[i].PackageName().c_str(),
               m_packageVec[i].PackageVersion().c_str());
    }
}

/**
 *  Return iterator pointing to first element in vector.
 */

DEB_PACKAGE_VECTOR_ITER debPackageDB::begin() {
    return m_packageVec.begin();
}

/**
 *  Return iterator pointing to last element in vector.
 */

DEB_PACKAGE_VECTOR_ITER debPackageDB::end() {
    return m_packageVec.end();
}
