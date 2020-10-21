#include "State.h"

void copy_lake(lily* lake, lily* copy) {
    for (int i = 0; i < 5; ++i) {
        copy[i] = lake[i];
    }
}

bool compare_lakes(lily* first_lake, lily* second_lake) {
    for (int i = 0; i < 5; ++i) {
        if (first_lake[i] != second_lake[i]) {
            return 0;
        }
    }

    return 1;
}

State::State(lily* lake, State* parent) {
    for (int i = 0; i < 5; ++i) {
        this->lake[i] = lake[i];
    }

    this->parent = parent;
}

void State::generate_states() {
    for (int i = 0; i < 5; ++i) {
        if (this->lake[i] == RIGHT) {
            State* new_state = nullptr;
            lily new_lake[5];
            copy_lake(this->lake, new_lake);

            bool generated_state = move_two_right(i, new_lake);

            if (generated_state) {
                new_state = new State(new_lake, this);
                this->children.push_back(new_state);
            }

            copy_lake(this->lake, new_lake);
            generated_state = move_one_right(i, new_lake);
            if (generated_state) {
                new_state = new State(new_lake, this);
                this->children.push_back(new_state);
            }
        }
        else if (this->lake[i] == LEFT) {
            State* new_state = nullptr;
            lily new_lake[5];
            copy_lake(this->lake, new_lake);

            bool generated_state = move_two_left(i, new_lake);

            if (generated_state) {
                new_state = new State(new_lake, this);
                this->children.push_back(new_state);
            }

            copy_lake(this->lake, new_lake);
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

        if (compare_lakes(current->lake, goal)) {
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
