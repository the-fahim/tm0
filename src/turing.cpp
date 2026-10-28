#include "turing.h"
#include <iostream>

TuringMachine::TuringMachine(const std::string& initial_state, const std::string& halt_state)
    : head_position(0), current_state(initial_state), halt_state(halt_state) {
    tape.push_back('_'); // Initialize with a blank symbol
}

void TuringMachine::add_transition(const std::string& state, char symbol, 
                                  const std::string& next_state, char write_symbol, Direction dir) {
    transitions[{state, symbol}] = {next_state, write_symbol, dir};
}

void TuringMachine::load_tape(const std::string& input) {
    tape.clear();
    for (char c : input) {
        tape.push_back(c);
    }
    if (tape.empty()) {
        tape.push_back('_');
    }
    head_position = 0;
}

void TuringMachine::normalize_tape() {
    // Ensure the head never goes out of bounds by padding the deque
    while (head_position < 0) {
        tape.push_front('_');
        head_position = 0;
    }
    while (head_position >= static_cast<long long>(tape.size())) {
        tape.push_back('_');
    }
}

bool TuringMachine::step() {
    if (current_state == halt_state) {
        return false;
    }

    normalize_tape();
    char current_symbol = tape[head_position];

    auto it = transitions.find({current_state, current_symbol});
    if (it == transitions.end()) {
        // No transition found, halt execution
        return false;
    }

    const Transition& t = it->second;
    tape[head_position] = t.write_symbol;
    current_state = t.next_state;

    if (t.move_direction == Direction::LEFT) {
        head_position--;
    } else {
        head_position++;
    }

    return true;
}

void TuringMachine::run() {
    int steps = 0;
    print_state();
    while (current_state != halt_state && step()) {
        print_state();
        steps++;
        if (steps > 1000) { // Safety break against infinite loops
            std::cout << "Max steps reached. Halting.\n";
            break;
        }
    }
}

void TuringMachine::print_state() const {
    std::cout << "State: " << current_state << " \t| Tape: ";
    for (size_t i = 0; i < tape.size(); ++i) {
        if (static_cast<long long>(i) == head_position) {
            std::cout << "[" << tape[i] << "]";
        } else {
            std::cout << " " << tape[i] << " ";
        }
    }
    std::cout << "\n";
}