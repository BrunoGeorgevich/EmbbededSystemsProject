#include "configure.h"

int main() {
    init_sensors();
    configure_buttons();
    init_state_machine();

    while (PROGRAM_RUNS_CORRECTLY) {
        current_state->run();
    }

    return NO_ERRORS;
}
