#ifndef __XML_INTERFACE_H__
#define __XML_INTERFACE_H__

#include <string>
#include <vector>
#include <libxml/tree.h>

#include "basicTypes.h"

class debPackageDB;

typedef std::vector<xmlNodePtr>             NODE_VECTOR;
typedef std::vector<xmlNodePtr>::iterator   NODE_VECTOR_ITER;

/**
 *
 */

bool xml_load_controlfile(const char* szControlName, debPackageDB& packDB);

bool xml_find_all_tags(xmlNodePtr pNode,
                       STRING tag,
                       NODE_VECTOR& tagVec);

bool xml_get_child_contents(xmlNodePtr pParent,
                            STRING sNodeName,
                            STRING& sNodeContent);


#define     XML_TAG_DEBCHECK        "debcheck"
#define     XML_TAG_PACKAGE         "package"
#define     XML_TAG_PACK_NAME       "name"
#define     XML_TAG_PACK_VERSION    "version"

#endif // __XML_INTERFACE_H__
