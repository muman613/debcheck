#include "debPackageDB.h"


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
}

debPackageDB::~debPackageDB()
{
    //dtor
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

    fprintf(stdout, "Adding package %s version %s\n",
            sPackageName.c_str(),
            sPackageVersion.c_str());
    m_packageVec.push_back( newPackage );
}

void debPackageDB::Dump(FILE* fOut) {
    for (size_t i = 0 ; i < size() ; i++) {
        fprintf(fOut, "%-40s : %s", m_packageVec[i].PackageName().c_str(),
               m_packageVec[i].PackageVersion().c_str());
    }
}

DEB_PACKAGE_VECTOR_ITER debPackageDB::begin() {
    return m_packageVec.begin();
}

DEB_PACKAGE_VECTOR_ITER debPackageDB::end() {
    return m_packageVec.end();
}
