#ifndef __DPKG_INTERFACE__
#define __DPKG_INTERFACE__

#include <config.h>
#include <compat.h>
#include <dpkg/i18n.h>
#include <dpkg/dpkg.h>
#include <dpkg/dpkg-db.h>
#include <dpkg/pkg-array.h>
#include <dpkg/path.h>

/**
 *  This class encapsulates the dpkg array.
 */

class PackageArray {
public:
    PackageArray();
    virtual ~PackageArray();

    void   init();
    size_t size();

    /** Iterator class */
    class pkgiter {
    public:
        pkgiter();
        virtual ~pkgiter();

        pkginfo* operator *();

        pkgiter&       operator = (const pkgiter& copy);
        bool           operator !=(const pkgiter& comp);
        const pkgiter& operator++(int);

    protected:
        friend class PackageArray;

        pkgiter(PackageArray* pParent, size_t nIndex = 0);

    private:
        PackageArray*   m_pParent;
        size_t          m_nIndex;
    };

    pkgiter begin();    ///< Return iterator for first element
    pkgiter end();      ///< Return iterator for last element

protected:
    friend class pkgiter;

    struct pkg_array m_array;
private:
};

bool dpkg_system_open();
void dpkg_system_close();

void dpkg_dump_installed(FILE* fOut = stdout);

bool dpkg_is_package_installed(const char* szPackageName, const char* szPackageRevision);
bool dpkg_get_package_version(const char* szPackageName, char* sVersion, size_t len);

#endif // __DPKG_INTERFACE__
