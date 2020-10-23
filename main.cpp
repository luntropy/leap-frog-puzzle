#include <iostream>

#include "State.h"

int main() {
    lily S[5] = { RIGHT, RIGHT, EMPTY, LEFT, LEFT };
    lily G[5] = { LEFT, LEFT, EMPTY, RIGHT, RIGHT };

    State* start = new State(S, nullptr);

    start->generate_state_space();
    start->print_result_path(G);

    return 0;
}
