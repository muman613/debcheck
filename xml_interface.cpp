/**
 *  @file       xml_interface.cpp
 *  @author     Michael A. Uman
 *  @date       August 15, 2012
 *  @brief      This file contains the xml interface for debcheck.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "xml_interface.h"
#include "debPackageDB.h"
#include "dbgutils.h"

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

            D(ebug("found root node!\n"));

            if (xml_find_all_tags(pRoot, XML_TAG_PACKAGE, packageNodeVec)) {

                D(ebug("found %ld packages!\n", packageNodeVec.size()));

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

                    /* Add the package to the database */
                    packDB.Add( packageName, packageVersion );
                }
            }
        }

        /* free the document */
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


    D(ebug("find_all_tags(%p, %s, ...)\n", pNode, tag.c_str()));

    while (pThisNode != 0) {
        if ((pThisNode->type == XML_ELEMENT_NODE) &&
            (std::string((const char*)pThisNode->name) == tag))
        {
            tagVec.push_back(pThisNode);
        }
        pThisNode = pThisNode->next;
    }

    return (tagVec.size() > 0); // Return true if tags were found.
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
            xmlFree( pContent );

            return true;
        }

        pThis = pThis->next;
    }
    return false;
}
