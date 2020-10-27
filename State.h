#include <iostream>

#include <vector>
#include <stack>
#include <algorithm>

#ifndef STATE_H
#define STATE_H

const int N = 5;

enum lily {EMPTY, LEFT, RIGHT};

class State {
private:
    lily lake[N];
    State* parent;
    std::vector<State*> children;

    void copy_objects_lake(lily*);
    void copy_lake_to_object(const lily*);
    bool compare_lakes(lily*);
    void empty_lake();
    void clear_state();
    void copy_state(const State&);

    bool move_two_left(int, lily*);
    bool move_one_left(int, lily*);
    bool move_two_right(int, lily*);
    bool move_one_right(int, lily*);

    bool validate_movement(int, int, lily*);
    void generate_states();
    State* find_result(lily*);

public:
    State();
    State(lily*, State*);
    State(const State&);
    State& operator=(const State&);
    ~State();

    void generate_state_space();
    void print_result_path(lily*);

    void print_lake();
    void print_children();
    void print_state_space();
};

#endif
