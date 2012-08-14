#ifndef __DEBPACKAGEDB_H__
#define __DEBPACKAGEDB_H__

#include <stdio.h>
#include "basicTypes.h"

/**
 *
 */

class debPackage {
public:
    debPackage(STRING sPackageName, STRING sPackageVersion);
    debPackage(const debPackage& copy);
    virtual ~debPackage();

    debPackage& operator = (const debPackage& copy);

    STRING      PackageName() const;
    STRING      PackageVersion() const;

protected:
    STRING      m_sPackageName;
    STRING      m_sPackageVersion;
    int         m_nFlags;
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
