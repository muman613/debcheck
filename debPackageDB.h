#ifndef __DEBPACKAGEDB_H__
#define __DEBPACKAGEDB_H__

#include <stdio.h>
#include "basicTypes.h"
#include "dpkg_interface.h"

/**
 *  This class represents either an absolute version specification or a range
 *  of versions which can be used in comparisons.
 */

class debPackageVersionSpec {
public:
    enum specTypeFlag {
        SPEC_FLAG_BADSPEC = 0,
        SPEC_FLAG_MATCH   = (1L << 0),
        SPEC_FLAG_GT_MIN  = (1L << 1),
        SPEC_FLAG_LT_MAX  = (1L << 2),
    };

    debPackageVersionSpec(STRING sMatchVer);
    debPackageVersionSpec(STRING sMatchVer,
                          STRING sMinVer,
                          STRING sMaxVer);
    debPackageVersionSpec(const debPackageVersionSpec& copy);
    virtual ~debPackageVersionSpec();

    bool                valid() const;
    STRING              string() const;

protected:

    versionrevision     m_stVersionMatch;   ///< Version to match.
    versionrevision     m_stVersionMin;     ///< Minimun acceptable version.
    versionrevision     m_stVersionMax;     ///< Maximum acceptable version.
    specTypeFlag        m_eSpecType;        ///< Type of vesion specification.
};

/**
 *
 */

class debPackage {
public:
    debPackage(STRING sPackageName, STRING sPackageVersion);
    debPackage(const debPackage& copy);
    virtual ~debPackage();

    debPackage& operator = (const debPackage& copy);

    STRING                  PackageName() const;
    STRING                  PackageVersion() const;

protected:
    STRING                  m_sPackageName;
    debPackageVersionSpec   m_cPackageVersion;
    int                     m_nFlags;
};

typedef std::vector<debPackage>             DEB_PACKAGE_VECTOR;
typedef std::vector<debPackage>::iterator   DEB_PACKAGE_VECTOR_ITER;

/**
 *
 */

class debPackageDB
{
    public:
        debPackageDB();
        virtual ~debPackageDB();

        size_t  size();
        void    clear();

        void    Add(STRING sPackageName, STRING sPackageVersion);

        void    Dump(FILE* fOut=stdout);

        DEB_PACKAGE_VECTOR_ITER begin();
        DEB_PACKAGE_VECTOR_ITER end();

    protected:

        DEB_PACKAGE_VECTOR  m_packageVec;
    private:
};




#endif // __DEBPACKAGEDB_H__
