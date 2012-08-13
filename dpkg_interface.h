#ifndef __DPKG_INTERFACE__
#define __DPKG_INTERFACE__

#include <config.h>
#include <compat.h>
#include <dpkg/i18n.h>
#include <dpkg/dpkg.h>
#include <dpkg/dpkg-db.h>
#include <dpkg/pkg-array.h>
#include <dpkg/path.h>

class PackageArray {
public:
    PackageArray();
    virtual ~PackageArray();

    void   init();
    size_t size();


    class pkgiter {
    public:
        pkgiter();
        virtual ~pkgiter();

        pkginfo* operator *();

        pkgiter& operator = (const pkgiter& copy);
        bool operator !=(const pkgiter& comp);
        const pkgiter& operator++(int);
    protected:
        friend class PackageArray;

        pkgiter(PackageArray* pParent, size_t nIndex = 0);

    private:
        PackageArray*   m_pParent;
        size_t          m_nIndex;
    };

    pkgiter begin();
    pkgiter end();

protected:
    friend class pkgiter;

    struct pkg_array m_array;
private:
};

bool dpkg_system_open();
void dpkg_system_close();


#endif // __DPKG_INTERFACE__
