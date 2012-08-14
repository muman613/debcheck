/**
 *  @file   main.cpp
 *  @date   August 10, 2012
 *  @author Michael Uman
 *
 *  @brief  This application checks whether packages are installed, if not
 *          it will ask to install them.
 */

#include <config.h>
#include <compat.h>
#include <stdlib.h>
#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>

#include "dpkg_interface.h"

using namespace std;


/**
 *
 */

int main(int argc, const char* argv[]) {

    if (!dpkg_system_open()) {
        fprintf(stderr, "ERROR: Unable to open dpkg library!\n");
        return -1;
    }

    dpkg_dump_installed();

    dpkg_system_close();

    return 0;
}
