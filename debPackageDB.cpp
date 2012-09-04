/**
 *  @file       debPackageDB.cpp
 *  @author     Michael A. Uman
 *  @date       August 15, 2012
 *  @brief      This file contains the definition of debPackage and
 *              debPackageDB.
 */

#include "debPackageDB.h"
#include "dbgutils.h"

debPackageVersionSpec::debPackageVersionSpec(STRING sMatchVersion)
:   m_eSpecType(SPEC_FLAG_BADSPEC)
{
    // ctor
    if (parseversion(&m_stVersionMatch, sMatchVersion.c_str(), NULL) == 0)
        m_eSpecType = SPEC_FLAG_MATCH;
}

/**
 *
 */

debPackageVersionSpec::debPackageVersionSpec(STRING sMatchVer,
                          STRING sMinVer,
                          STRING sMaxVer)
{
    int    flags = SPEC_FLAG_BADSPEC;

    // ctor
    if (parseversion(&m_stVersionMatch, sMatchVer.c_str(), NULL) == 0)
        flags |= SPEC_FLAG_MATCH;

    if (sMinVer.length() > 0) {
        if (parseversion(&m_stVersionMin, sMinVer.c_str(), NULL) == 0)
            flags |= SPEC_FLAG_GT_MIN;
    }

    if (sMaxVer.length() > 0L) {
        if (parseversion(&m_stVersionMax, sMaxVer.c_str(), NULL) == 0)
            flags |= SPEC_FLAG_LT_MAX;
    }

    m_eSpecType = (specTypeFlag)flags;
}

/**
 *
 */

debPackageVersionSpec::debPackageVersionSpec(const debPackageVersionSpec& copy)
{
    m_stVersionMatch = copy.m_stVersionMatch;
    m_stVersionMax   = copy.m_stVersionMax;
    m_stVersionMin   = copy.m_stVersionMin;
    m_eSpecType      = copy.m_eSpecType;
}

/**
 *
 */

debPackageVersionSpec::~debPackageVersionSpec()
{
    // dtor
}

/**
 *
 */

STRING debPackageVersionSpec::string() const
{
    STRING  sRes;

    if (valid()) {
        if (m_eSpecType == SPEC_FLAG_MATCH) {
            sRes = versiondescribe( &m_stVersionMatch, vdew_nonambig );
        } else {
            sRes = "N/A";
        }
    } else {
        sRes = "INVALID";
    }

    return sRes;
}

bool debPackageVersionSpec::valid() const {
    return (m_eSpecType != SPEC_FLAG_BADSPEC)?true:false;
}

/**
 *
 */

debPackage::debPackage(STRING sPackageName, STRING sPackageVersion)
:   m_sPackageName(sPackageName),
    m_cPackageVersion(sPackageVersion)
{
    // ctor
}

debPackage::debPackage(const debPackage& copy)
:   m_sPackageName(copy.m_sPackageName),
    m_cPackageVersion(copy.m_cPackageVersion)
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
    return m_cPackageVersion.string();
}

debPackage& debPackage::operator = (const debPackage& copy)
{
    m_sPackageName    = copy.m_sPackageName;
    m_cPackageVersion = copy.m_cPackageVersion;

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
