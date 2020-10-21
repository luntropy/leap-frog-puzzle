#include "State.h"

void State::copy_objects_lake(lily* lake) {
    for (int i = 0; i < 5; ++i) {
        lake[i] = this->lake[i];
    }
}

void State::copy_lake_to_object(const lily* lake) {
    for (int i = 0; i < 5; ++i) {
        this->lake[i] = lake[i];
    }
}

bool State::compare_lakes(lily* lake) {
    for (int i = 0; i < 5; ++i) {
        if (this->lake[i] != lake[i]) {
            return 0;
        }
    }

    return 1;
}

void State::empty_lake() {
    for (int i = 0; i < 5; ++i) {
        this->lake[i] = EMPTY;
    }
}

void State::clear_state() {
    std::vector<State*>::iterator it;
    for (it = this->children.begin(); it != this->children.end(); ++it) {
        delete *it;
    }
}

void State::copy_state(const State& state) {
    this->copy_lake_to_object((&state)->lake);
    this->parent = (&state)->parent;
    // this->copy_children(state->children);
    this->children = (&state)->children;
}

State::State() {
    this->empty_lake();
    this->parent = nullptr;
}

State::State(lily* lake, State* parent) : State() {
    this->copy_lake_to_object(lake);
    this->parent = parent;
}

State::State(const State& state) : State() {
    this->copy_state(state);
}

State& State::operator=(const State& state) {
    if (this != &state) {
        this->clear_state();
        this->copy_state(state);
    }

    return *this;
}

State::~State() {
    this->clear_state();
}

void State::generate_states() {
    for (int i = 0; i < 5; ++i) {
        if (this->lake[i] == RIGHT) {
            State* new_state = nullptr;
            lily new_lake[5];
            this->copy_objects_lake(new_lake);

            bool generated_state = move_two_right(i, new_lake);

            if (generated_state) {
                new_state = new State(new_lake, this);
                this->children.push_back(new_state);
            }

            this->copy_objects_lake(new_lake);
            generated_state = move_one_right(i, new_lake);
            if (generated_state) {
                new_state = new State(new_lake, this);
                this->children.push_back(new_state);
            }
        }
        else if (this->lake[i] == LEFT) {
            State* new_state = nullptr;
            lily new_lake[5];
            this->copy_objects_lake(new_lake);

            bool generated_state = move_two_left(i, new_lake);

            if (generated_state) {
                new_state = new State(new_lake, this);
                this->children.push_back(new_state);
            }

            this->copy_objects_lake(new_lake);
            generated_state = move_one_left(i, new_lake);
            if (generated_state) {
                new_state = new State(new_lake, this);
                this->children.push_back(new_state);
            }
        }
    }
}

void State::generate_state_space() {
    std::stack<State*> to_visit;
    to_visit.push(this);

    while (!to_visit.empty()) {
        State* current = to_visit.top();
        to_visit.pop();

        current->generate_states();

        std::vector<State*>::iterator it;
        for (it = current->children.begin(); it != current->children.end(); ++it) {
            to_visit.push(*it);
        }
    }
}

bool State::validate_movement(int index, int target_index, lily* lake) {
    if (lake[target_index] != EMPTY || lake[index] == EMPTY || target_index < 0 || target_index > 4) {
        return 0;
    }
    else if (lake[index] == RIGHT) {
        if (index > target_index) {
            return 0;
        }
        else {
            return 1;
        }
    }
    else if (lake[index] == LEFT) {
        if (index < target_index) {
            return 0;
        }
        else {
            return 1;
        }
    }

    return 0;
}

bool State::move_two_left(int index, lily* lake) {
    int target_index = index - 2;

    if (validate_movement(index, target_index, lake)) {
        lake[target_index] = lake[index];
        lake[index] = EMPTY;

        return 1;
    }

    return 0;
}

bool State::move_one_left(int index, lily* lake) {
    int target_index = index - 1;

    if (validate_movement(index, target_index, lake)) {
        lake[target_index] = lake[index];
        lake[index] = EMPTY;

        return 1;
    }

    return 0;
}

bool State::move_two_right(int index, lily* lake) {
    int target_index = index + 2;

    if (validate_movement(index, target_index, lake)) {
        lake[target_index] = lake[index];
        lake[index] = EMPTY;

        return 1;
    }

    return 0;
}

bool State::move_one_right(int index, lily* lake) {
    int target_index = index + 1;

    if (validate_movement(index, target_index, lake)) {
        lake[target_index] = lake[index];
        lake[index] = EMPTY;

        return 1;
    }

    return 0;
}

void State::print_lake() {
        for (int i = 0; i < 5; ++i) {
            std::cout << this->lake[i] << ' ';
        }
        std::cout << std::endl;
}

void State::print_children() {
    std::vector<State*>::iterator it;

    for (it = this->children.begin(); it != this->children.end(); ++it) {
        (*it)->print_lake();
    }
}

void State::print_state_space() {
    std::stack<State*> to_visit;
    to_visit.push(this);

    while (!to_visit.empty()) {
        State* current = to_visit.top();
        to_visit.pop();

        current->print_lake();

        std::vector<State*>::iterator it;
        for (it = current->children.begin(); it != current->children.end(); ++it) {
            to_visit.push(*it);
        }
    }
}

State* State::find_result(lily* goal) {
    std::vector<State*> visited;
    std::stack<State*> to_visit;

    to_visit.push(this);

    while (!to_visit.empty()) {
        State* current = to_visit.top();
        to_visit.pop();

        if (current->compare_lakes(goal)) {
            return current;
        }

        if (!current->children.empty()) {
            std::vector<State*>::iterator it;

            for (it = current->children.begin(); it != current->children.end(); ++it) {
                to_visit.push(*it);
            }
        }
    }

    return nullptr;
}

void State::print_result_path(lily* goal) {
    State* result = this->find_result(goal);

    if (result) {
        std::stack<State*> path;
        path.push(result);

        while (result->parent) {
            path.push(result->parent);
            result = result->parent;
        }

        while (!path.empty()) {
            State* current = path.top();
            path.pop();

            current->print_lake();
        }
    }
}
