#include <cstdint>
#include <wayland-server.h>
#include <unistd.h>
#include <stdlib.h>
#include "util.h"

// Spawns an executable
void spawn(void * data, uint32_t time, uint32_t value, uint32_t state)
{
    char * const * command = (char * const *)data;

    if (state != WL_KEYBOARD_KEY_STATE_PRESSED)
        return;

    if (fork() == 0)
    {
        execvp(command[0], command);
        exit(EXIT_FAILURE);
    }
}
