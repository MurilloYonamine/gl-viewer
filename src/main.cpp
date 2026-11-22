// Created by murillo.gyonamine on 08/08/2026.

#include <iostream>
#include <exception>
#include "app/viewer.h"

int main()
{
    try
    {
        Viewer viewer;
        viewer.Update();
    }
    catch (const std::exception& e)
    {
        std::cerr << "[ERROR] " << e.what() << '\n';
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
