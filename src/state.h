#ifndef STATE_H
#define STATE_H

enum state_t{
    HELLOWORLD,     // Estado 1
    TEMPERATURE,    // Estado 2
    ACCELETOMETER,  // Estado 3
    MAGNETOMETER,   // Estado 4
    BLUETOOTH       // Estado 5
};

struct state {
    union {
        struct internal_states{
            enum state_t previous;
            enum state_t current;
            enum state_t next;
        };
        enum state_t s[3];
    };

    void (*run)(void);
};

#endif //STATE_H
