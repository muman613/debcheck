#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "xml_interface.h"
#include "debPackageDB.h"

/**
 *
 */

bool xml_load_controlfile(const char* szControlName, debPackageDB& packDB){
    bool            bRes = false;
    xmlDocPtr       pDoc = NULL;

    pDoc = xmlParseFile( szControlName );

    if (pDoc != 0L) {
        xmlNodePtr  pRoot = xmlDocGetRootElement( pDoc );

        if ( xmlStrcmp(pRoot->name, BAD_CAST XML_TAG_DEBCHECK) == 0 ) {
            NODE_VECTOR packageNodeVec;

            printf("found root node!\n");

            if (xml_find_all_tags(pRoot, XML_TAG_PACKAGE, packageNodeVec)) {
                printf("found %ld packages!\n", packageNodeVec.size());

                for (NODE_VECTOR_ITER nIt = packageNodeVec.begin();
                                      nIt != packageNodeVec.end();
                                      nIt++)
                {
                    xmlNodePtr pPackNode = *nIt;
                    STRING     packageName, packageVersion;

                    if (!xml_get_child_contents(pPackNode,
                                               XML_TAG_PACK_NAME,
                                               packageName))
                    {
                        fprintf(stderr, "ERROR: Package name must be specified!\n");
                        return false;
                    }

                    if (!xml_get_child_contents(pPackNode,
                                               XML_TAG_PACK_VERSION,
                                               packageVersion))
                    {
                        packageVersion = "*";
                    }

                    packDB.Add( packageName, packageVersion );
                }
            }
        }
//      packDB.clear();

        xmlFreeDoc( pDoc );
        bRes = true;
    }

    return bRes;
}

/**
 *  Used to find all nodes which match a tag pattern.
 */

bool    xml_find_all_tags(xmlNodePtr pNode,
                          STRING tag,
                          NODE_VECTOR& tagVec)
{
    xmlNodePtr  pThisNode = pNode->children;

#ifdef  DEBUG
    fprintf(stderr, "find_all_tags(%p, %s, ...)\n", pNode, tag.c_str());
#endif

    while (pThisNode != 0) {
        if ((pThisNode->type == XML_ELEMENT_NODE) &&
            (std::string((const char*)pThisNode->name) == tag))
        {
            tagVec.push_back(pThisNode);
        }
        pThisNode = pThisNode->next;
    }

    return (tagVec.size() > 0);
}

/**
 *
 */

bool xml_get_child_contents(xmlNodePtr pParent,
                            STRING sNodeName,
                            STRING& sNodeContent)
{
    xmlNodePtr  pThis = pParent->children;

    while (pThis != 0L) {
        if ((pThis->type == XML_ELEMENT_NODE) &&
            (xmlStrcmp(pThis->name, BAD_CAST sNodeName.c_str()) == 0))
        {
            char*    pContent = (char *)xmlNodeGetContent( pThis );
            sNodeContent = pContent;
            return true;
        }

        pThis = pThis->next;
    }
    return false;
}
