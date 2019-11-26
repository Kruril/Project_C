#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "headers/run.h"

int main()
{
    bool running = true;

    while (running)
    {
        running = run();
    }

    printf("Fin du Programme\n");
    return 0;
}