#include "turing.h"

int main() {
    // Example: Binary incrementer machine
    // States: q0 (scan right to find the end), q1 (carry/add), halt
    TuringMachine tm("q0", "halt");

    // Scan right until finding a blank symbol '_'
    tm.add_transition("q0", '0', "q0", '0', Direction::RIGHT);
    tm.add_transition("q0", '1', "q0", '1', Direction::RIGHT);
    tm.add_transition("q0", '_', "q1", '_', Direction::LEFT);

    // Carry logic: flip 1 to 0 and move left, flip 0 to 1 and halt, blank to 1 and halt
    tm.add_transition("q1", '1', "q1", '0', Direction::LEFT);
    tm.add_transition("q1", '0', "halt", '1', Direction::RIGHT);
    tm.add_transition("q1", '_', "halt", '1', Direction::RIGHT);

    // Load binary number 1011 (11 in decimal) onto the tape
    tm.load_tape("1011");

    tm.run();

    return 0;
}