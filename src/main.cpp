#include "window.h"

int main()
{
    const Window window(800, 600, "GL Viewer");

    /* Loop until the user closes the window */
    while (window.IsOpen())
    {
        window.Update();
    }

    return 0;
}
