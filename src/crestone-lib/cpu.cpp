#include "cpu.hpp"

#define GET_REGISTER( x ) emulator_state->registers[x]

Cpu::Cpu(EmulatorState* emulator_state) : emulator_state(emulator_state) {}

Cpu::~Cpu() {}

u16 Cpu::nnn() { return current_opcode & 0x0FFF; }
u8 Cpu::n() { return current_opcode & 0x000F; }
u8 Cpu::x() { return (current_opcode & 0x0F00) >> 8; }
u8 Cpu::y() {return (current_opcode & 0x00F0) >> 4; }
u8 Cpu::kk() {return current_opcode & 0x00FF; }

void Cpu::execute() {
    if (emulator_state->clear_display) {
        emulator_state->clear_display = false;
    }

    current_opcode = emulator_state->memory[emulator_state->program_counter] << 8 + emulator_state->memory[emulator_state->program_counter + 1];
    emulator_state->program_counter += 2;
    // Function pointers did not want to work :(
    switch (current_opcode > 12) {
        case 0x0:
            switch (kk()) {
                case 0xE0:
                    OP_00E0();
                    return;
                case 0xEE:
                    OP_00EE();
                    return;
                default:
                    return;
            }
        case 0x1:
            OP_1NNN();
            return;
        case 0x2:
            OP_2NNN();
            return;
        case 0x3:
            OP_3XKK();
            return;
        case 0x4:
            OP_4XKK();
            return;
        case 0x5: 
            OP_5XY0();
            return;
        case 0x6:
            OP_6XKK();
            return;
        case 0x7:
            OP_7XKK();
            return;
        case 0x8:
            switch (n()) {
                case 0x0:
                    OP_8XY0();
                    return;
                case 0x1:
                    OP_8XY1();
                    return;
                case 0x2:
                    OP_8XY2();
                    return;
                case 0x3:
                    OP_8XY3();
                    return;
                case 0x4:
                    OP_8XY4();
                    return;
                case 0x5:
                    OP_8XY5();
                    return;
                case 0x6:
                    OP_8XY6();
                    return;
                case 0x7:
                    OP_8XY7();
                    return;
                default:
                    return;
            }
        case 0x9:
            OP_9XY0();
            return;
        case 0xA:
            OP_ANNN();
            return;
        case 0xB:
            OP_BNNN();
            return;
        case 0xC:
            OP_CXKK();
            return;
        case 0xD:
            OP_DXYN();
            return;
        case 0xE:
            switch (kk()) {
                case 0x9E:
                    OP_EX9E();
                    return;
                case 0xA1:
                    OP_EXA1();
                    return;
                default:
                    return;
            }
        case 0xF:
            switch (kk()) {
                case 0x07:
                    OP_FX07();
                    return;
                case 0x0A:
                    OP_FX0A();
                    return;
                case 0x15:
                    OP_FX15();
                    return;
                case 0x18:
                    OP_FX18();
                    return;
                case 0x1E:
                    OP_FX1E();
                    return;
                case 0x29:
                    OP_FX29();
                    return;
                case 0x33:
                    OP_FX33();
                    return;
                case 0x55:
                    OP_FX55();
                    return;
                case 0x65:
                    OP_FX65();
                    return;
                default:
                    return;
            }
        default:
            return;
    }

}

void Cpu::OP_00E0() {
    emulator_state->clear_display = true;
}

void Cpu::OP_00EE() {
    emulator_state->program_counter = emulator_state->stack[emulator_state->stack_pointer];
    emulator_state->stack_pointer -= 1;
}

void Cpu::OP_1NNN() {
    emulator_state->program_counter = nnn();
}

void Cpu::OP_2NNN() {
    emulator_state->stack_pointer += 1;
    emulator_state->stack[emulator_state->stack_pointer] = emulator_state->program_counter;
    emulator_state->program_counter = nnn();
}

void Cpu::OP_3XKK() {
    if (GET_REGISTER(x()) == kk()) {
        emulator_state->program_counter += 2;
    }
}

void Cpu::OP_4XKK() {
    if (GET_REGISTER(x()) != kk()) {
        emulator_state->program_counter += 2;
    }
}

void Cpu::OP_5XY0() {
    if (GET_REGISTER(x()) == GET_REGISTER(y())) {
        emulator_state->program_counter += 2;
    }
}

void Cpu::OP_6XKK() {
    GET_REGISTER(x()) = kk();
}

void Cpu::OP_7XKK() {
    GET_REGISTER(x()) += kk();
}

void Cpu::OP_8XY0() {
    GET_REGISTER(x()) = GET_REGISTER(y());
}

void Cpu::OP_8XY1() {
    GET_REGISTER(x()) = GET_REGISTER(x()) | GET_REGISTER(y());
}

void Cpu::OP_8XY2() {
    GET_REGISTER(x()) = GET_REGISTER(x()) & GET_REGISTER(y());
}

void Cpu::OP_8XY3() {
    GET_REGISTER(x()) = GET_REGISTER(x()) ^ GET_REGISTER(y());
}

void Cpu::OP_8XY4() {
    
}

void Cpu::OP_8XY5() {

}

void Cpu::OP_8XY6() {

}

void Cpu::OP_8XY7() {

}

void Cpu::OP_8XYE() {

}

void Cpu::OP_9XY0() {

}

void Cpu::OP_ANNN() {

}

void Cpu::OP_BNNN() {

}

void Cpu::OP_CXKK() {

}

void Cpu::OP_DXYN() {

}

void Cpu::OP_EX9E() {

}

void Cpu::OP_EXA1() {

}

void Cpu::OP_FX07() {

}

void Cpu::OP_FX0A() {

}

void Cpu::OP_FX15() {

}

void Cpu::OP_FX18() {

}

void Cpu::OP_FX1E() {

}

void Cpu::OP_FX29() {

}

void Cpu::OP_FX33() {

}

void Cpu::OP_FX55() {

}

void Cpu::OP_FX65() {

}
