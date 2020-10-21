#include <iostream>

#include <vector>
#include <stack>

#ifndef STATE_H
#define STATE_H

enum lily {EMPTY, LEFT, RIGHT};

class State {
private:
    lily lake[5];
    State* parent;
    std::vector<State*> children;

public:
    State(lily*, State*);

    void generate_states();
    void generate_state_space();
    bool validate_movement(int, int, lily*);
    bool move_two_left(int, lily*);
    bool move_one_left(int, lily*);
    bool move_two_right(int, lily*);
    bool move_one_right(int, lily*);

    void print_lake();
    void print_children();
    void print_state_space();

    State* find_result(lily*);
    void print_result_path(lily*);
};

#endif
