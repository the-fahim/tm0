#ifndef TURING_HPP
#define TURING_HPP

#include<string>
#include<deque>
#include<map>

enum class Direction{
    LEFT, RIGHT
};

struct Transition {
    std::string next_state;
    char write_symbol;
    Direction move_direction;
};

class TuringMachine {
private:
    std::deque<char> tape;
    long long head_position; // Index relative to the deque
    std::string current_state;
    std::string halt_state;
    
    // Key: pair(state, symbol), Value: Transition
    std::map<std::pair<std::string, char>, Transition> transitions;
    
    void normalize_tape();

public:
    TuringMachine(
        const std::string& initial_state, 
        const std::string& halt_state);
    
    void add_transition(const std::string& state, char symbol, 
                        const std::string& next_state, char write_symbol, Direction dir);
    
    void load_tape(const std::string& input);
    bool step();
    void run();
    void print_state() const;
};

#endif