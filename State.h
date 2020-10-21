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

private:
    void copy_objects_lake(lily*);
    void copy_lake_to_object(const lily*);
    bool compare_lakes(lily*);
    void empty_lake();
    void clear_state();
    void copy_state(const State&);

public:
    State();
    State(lily*, State*);
    State(const State&);
    State& operator=(const State&);
    ~State();

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
