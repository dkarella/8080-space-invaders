#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

enum argtype { argtype_none, argtype_d8, argtype_d16, argtype_addr };

typedef struct Opcode {
        char const* instruction;
        uint8_t arg;
} Opcode;

Opcode opcodes[256] = {
    [0x00] = {.instruction = "NOP"},
    [0x01] = {.instruction = "LXI B", .arg = argtype_d16},
    [0x02] = {.instruction = "STAX B"},
    [0x03] = {.instruction = "INX B"},
    [0x04] = {.instruction = "INR B"},
    [0x05] = {.instruction = "DCR B"},
    [0x06] = {.instruction = "MVI B", .arg = argtype_d8},
    [0x07] = {.instruction = "RLC"},
    [0x08] = {.instruction = "NOP"},
    [0x09] = {.instruction = "DAD B"},
    [0x0a] = {.instruction = "LDAX B"},
    [0x0b] = {.instruction = "DCX B"},
    [0x0c] = {.instruction = "INR C"},
    [0x0d] = {.instruction = "DCR C"},
    [0x0e] = {.instruction = "MVI C", .arg = argtype_d8},
    [0x0f] = {.instruction = "RRC"},
    [0x10] = {.instruction = "-"},
    [0x11] = {.instruction = "LXI D", .arg = argtype_d16},
    [0x12] = {.instruction = "STAX D"},
    [0x13] = {.instruction = "INX D"},
    [0x14] = {.instruction = "INR D"},
    [0x15] = {.instruction = "DCR D"},
    [0x16] = {.instruction = "MVI D", .arg = argtype_d8},
    [0x17] = {.instruction = "RAL"},
    [0x18] = {.instruction = "-"},
    [0x19] = {.instruction = "DAD D"},
    [0x1a] = {.instruction = "LDAX D"},
    [0x1b] = {.instruction = "DCX D"},
    [0x1c] = {.instruction = "INR E"},
    [0x1d] = {.instruction = "DCR E"},
    [0x1e] = {.instruction = "MVI E", .arg = argtype_d8},
    [0x1f] = {.instruction = "RAR"},
    [0x20] = {.instruction = "RIM"},
    [0x21] = {.instruction = "LXI H", .arg = argtype_d16},
    [0x22] = {.instruction = "SHLD", .arg = argtype_addr},
    [0x23] = {.instruction = "INX H"},
    [0x24] = {.instruction = "INR H"},
    [0x25] = {.instruction = "DCR H"},
    [0x26] = {.instruction = "MVI H", .arg = argtype_d8},
    [0x27] = {.instruction = "DAA"},
    [0x28] = {.instruction = "-"},
    [0x29] = {.instruction = "DAD H"},
    [0x2a] = {.instruction = "LHLD", .arg = argtype_addr},
    [0x2b] = {.instruction = "DCX H"},
    [0x2c] = {.instruction = "INR L"},
    [0x2d] = {.instruction = "DCR L"},
    [0x2e] = {.instruction = "MVI L", .arg = argtype_d8},
    [0x2f] = {.instruction = "CMA"},
    [0x30] = {.instruction = "SIM"},
    [0x31] = {.instruction = "LXI SP", .arg = argtype_d16},
    [0x32] = {.instruction = "STA", .arg = argtype_addr},
    [0x33] = {.instruction = "INX SP"},
    [0x34] = {.instruction = "INR M"},
    [0x35] = {.instruction = "DCR M"},
    [0x36] = {.instruction = "MVI M", .arg = argtype_d8},
    [0x37] = {.instruction = "STC"},
    [0x38] = {.instruction = "-"},
    [0x39] = {.instruction = "DAD SP"},
    [0x3a] = {.instruction = "LDA", .arg = argtype_addr},
    [0x3b] = {.instruction = "DCX SP"},
    [0x3c] = {.instruction = "INR A"},
    [0x3d] = {.instruction = "DCR A"},
    [0x3e] = {.instruction = "MVI A", .arg = argtype_d8},
    [0x3f] = {.instruction = "CMC"},
    [0x40] = {.instruction = "MOV B B"},
    [0x41] = {.instruction = "MOV B C"},
    [0x42] = {.instruction = "MOV B D"},
    [0x43] = {.instruction = "MOV B E"},
    [0x44] = {.instruction = "MOV B H"},
    [0x45] = {.instruction = "MOV B L"},
    [0x46] = {.instruction = "MOV B M"},
    [0x47] = {.instruction = "MOV B A"},
    [0x48] = {.instruction = "MOV C B"},
    [0x49] = {.instruction = "MOV C C"},
    [0x4a] = {.instruction = "MOV C D"},
    [0x4b] = {.instruction = "MOV C E"},
    [0x4c] = {.instruction = "MOV C H"},
    [0x4d] = {.instruction = "MOV C L"},
    [0x4e] = {.instruction = "MOV C M"},
    [0x4f] = {.instruction = "MOV C A"},
    [0x50] = {.instruction = "MOV D B"},
    [0x51] = {.instruction = "MOV D C"},
    [0x52] = {.instruction = "MOV D D"},
    [0x53] = {.instruction = "MOV D E"},
    [0x54] = {.instruction = "MOV D H"},
    [0x55] = {.instruction = "MOV D L"},
    [0x56] = {.instruction = "MOV D M"},
    [0x57] = {.instruction = "MOV D A"},
    [0x58] = {.instruction = "MOV E B"},
    [0x59] = {.instruction = "MOV E C"},
    [0x5a] = {.instruction = "MOV E D"},
    [0x5b] = {.instruction = "MOV E E"},
    [0x5c] = {.instruction = "MOV E H"},
    [0x5d] = {.instruction = "MOV E L"},
    [0x5e] = {.instruction = "MOV E M"},
    [0x5f] = {.instruction = "MOV E A"},
    [0x60] = {.instruction = "MOV H B"},
    [0x61] = {.instruction = "MOV H C"},
    [0x62] = {.instruction = "MOV H D"},
    [0x63] = {.instruction = "MOV H E"},
    [0x64] = {.instruction = "MOV H H"},
    [0x65] = {.instruction = "MOV H L"},
    [0x66] = {.instruction = "MOV H M"},
    [0x67] = {.instruction = "MOV H A"},
    [0x68] = {.instruction = "MOV L B"},
    [0x69] = {.instruction = "MOV L C"},
    [0x6a] = {.instruction = "MOV L D"},
    [0x6b] = {.instruction = "MOV L E"},
    [0x6c] = {.instruction = "MOV L H"},
    [0x6d] = {.instruction = "MOV L L"},
    [0x6e] = {.instruction = "MOV L M"},
    [0x6f] = {.instruction = "MOV L A"},
    [0x70] = {.instruction = "MOV M B"},
    [0x71] = {.instruction = "MOV M C"},
    [0x72] = {.instruction = "MOV M D"},
    [0x73] = {.instruction = "MOV M E"},
    [0x74] = {.instruction = "MOV M H"},
    [0x75] = {.instruction = "MOV M L"},
    [0x76] = {.instruction = "HLT"},
    [0x77] = {.instruction = "MOV M A"},
    [0x78] = {.instruction = "MOV A B"},
    [0x79] = {.instruction = "MOV A C"},
    [0x7a] = {.instruction = "MOV A D"},
    [0x7b] = {.instruction = "MOV A E"},
    [0x7c] = {.instruction = "MOV A H"},
    [0x7d] = {.instruction = "MOV A L"},
    [0x7e] = {.instruction = "MOV A M"},
    [0x7f] = {.instruction = "MOV A A"},
    [0x80] = {.instruction = "ADD B"},
    [0x81] = {.instruction = "ADD C"},
    [0x82] = {.instruction = "ADD D"},
    [0x83] = {.instruction = "ADD E"},
    [0x84] = {.instruction = "ADD H"},
    [0x85] = {.instruction = "ADD L"},
    [0x86] = {.instruction = "ADD M"},
    [0x87] = {.instruction = "ADD A"},
    [0x88] = {.instruction = "ADC B"},
    [0x89] = {.instruction = "ADC C"},
    [0x8a] = {.instruction = "ADC D"},
    [0x8b] = {.instruction = "ADC E"},
    [0x8c] = {.instruction = "ADC H"},
    [0x8d] = {.instruction = "ADC L"},
    [0x8e] = {.instruction = "ADC M"},
    [0x8f] = {.instruction = "ADC A"},
    [0x90] = {.instruction = "SUB B"},
    [0x91] = {.instruction = "SUB C"},
    [0x92] = {.instruction = "SUB D"},
    [0x93] = {.instruction = "SUB E"},
    [0x94] = {.instruction = "SUB H"},
    [0x95] = {.instruction = "SUB L"},
    [0x96] = {.instruction = "SUB M"},
    [0x97] = {.instruction = "SUB A"},
    [0x98] = {.instruction = "SBB B"},
    [0x99] = {.instruction = "SBB C"},
    [0x9a] = {.instruction = "SBB D"},
    [0x9b] = {.instruction = "SBB E"},
    [0x9c] = {.instruction = "SBB H"},
    [0x9d] = {.instruction = "SBB L"},
    [0x9e] = {.instruction = "SBB M"},
    [0x9f] = {.instruction = "SBB A"},
    [0xa0] = {.instruction = "ANA B"},
    [0xa1] = {.instruction = "ANA C"},
    [0xa2] = {.instruction = "ANA D"},
    [0xa3] = {.instruction = "ANA E"},
    [0xa4] = {.instruction = "ANA H"},
    [0xa5] = {.instruction = "ANA L"},
    [0xa6] = {.instruction = "ANA M"},
    [0xa7] = {.instruction = "ANA A"},
    [0xa8] = {.instruction = "XRA B"},
    [0xa9] = {.instruction = "XRA C"},
    [0xaa] = {.instruction = "XRA D"},
    [0xab] = {.instruction = "XRA E"},
    [0xac] = {.instruction = "XRA H"},
    [0xad] = {.instruction = "XRA L"},
    [0xae] = {.instruction = "XRA M"},
    [0xaf] = {.instruction = "XRA A"},
    [0xb0] = {.instruction = "ORA B"},
    [0xb1] = {.instruction = "ORA C"},
    [0xb2] = {.instruction = "ORA D"},
    [0xb3] = {.instruction = "ORA E"},
    [0xb4] = {.instruction = "ORA H"},
    [0xb5] = {.instruction = "ORA L"},
    [0xb6] = {.instruction = "ORA M"},
    [0xb7] = {.instruction = "ORA A"},
    [0xb8] = {.instruction = "CMP B"},
    [0xb9] = {.instruction = "CMP C"},
    [0xba] = {.instruction = "CMP D"},
    [0xbb] = {.instruction = "CMP E"},
    [0xbc] = {.instruction = "CMP H"},
    [0xbd] = {.instruction = "CMP L"},
    [0xbe] = {.instruction = "CMP M"},
    [0xbf] = {.instruction = "CMP A"},
    [0xc0] = {.instruction = "RNZ"},
    [0xc1] = {.instruction = "POP B"},
    [0xc2] = {.instruction = "JNZ", .arg = argtype_addr},
    [0xc3] = {.instruction = "JMP", .arg = argtype_addr},
    [0xc4] = {.instruction = "CNZ", .arg = argtype_addr},
    [0xc5] = {.instruction = "PUSH B"},
    [0xc6] = {.instruction = "ADI", .arg = argtype_d8},
    [0xc7] = {.instruction = "RST 0"},
    [0xc8] = {.instruction = "RZ"},
    [0xc9] = {.instruction = "RET"},
    [0xca] = {.instruction = "JZ", .arg = argtype_addr},
    [0xcb] = {.instruction = "-"},
    [0xcc] = {.instruction = "CZ", .arg = argtype_addr},
    [0xcd] = {.instruction = "CALL", .arg = argtype_addr},
    [0xce] = {.instruction = "ACI", .arg = argtype_d8},
    [0xcf] = {.instruction = "RST 1"},
    [0xd0] = {.instruction = "RNC"},
    [0xd1] = {.instruction = "POP D"},
    [0xd2] = {.instruction = "JNC", .arg = argtype_addr},
    [0xd3] = {.instruction = "OUT", .arg = argtype_d8},
    [0xd4] = {.instruction = "CNC", .arg = argtype_addr},
    [0xd5] = {.instruction = "PUSH D"},
    [0xd6] = {.instruction = "SUI", .arg = argtype_d8},
    [0xd7] = {.instruction = "RST 2"},
    [0xd8] = {.instruction = "RC"},
    [0xd9] = {.instruction = "-"},
    [0xda] = {.instruction = "JC", .arg = argtype_addr},
    [0xdb] = {.instruction = "IN", .arg = argtype_d8},
    [0xdc] = {.instruction = "CC", .arg = argtype_addr},
    [0xdd] = {.instruction = "-"},
    [0xde] = {.instruction = "SBI", .arg = argtype_d8},
    [0xdf] = {.instruction = "RST 3"},
    [0xe0] = {.instruction = "RPO"},
    [0xe1] = {.instruction = "POP H"},
    [0xe2] = {.instruction = "JPO", .arg = argtype_addr},
    [0xe3] = {.instruction = "XTHL"},
    [0xe4] = {.instruction = "CPO", .arg = argtype_addr},
    [0xe5] = {.instruction = "PUSH H"},
    [0xe6] = {.instruction = "ANI", .arg = argtype_d8},
    [0xe7] = {.instruction = "RST 4"},
    [0xe8] = {.instruction = "RPE"},
    [0xe9] = {.instruction = "PCHL"},
    [0xea] = {.instruction = "JPE", .arg = argtype_addr},
    [0xeb] = {.instruction = "XCHG"},
    [0xec] = {.instruction = "CPE", .arg = argtype_addr},
    [0xed] = {.instruction = "-"},
    [0xee] = {.instruction = "XRI", .arg = argtype_d8},
    [0xef] = {.instruction = "RST 5"},
    [0xf0] = {.instruction = "RP"},
    [0xf1] = {.instruction = "POP PSW"},
    [0xf2] = {.instruction = "JP", .arg = argtype_addr},
    [0xf3] = {.instruction = "DI"},
    [0xf4] = {.instruction = "CP", .arg = argtype_addr},
    [0xf5] = {.instruction = "PUSH PSW"},
    [0xf6] = {.instruction = "ORI", .arg = argtype_d8},
    [0xf7] = {.instruction = "RST 6"},
    [0xf8] = {.instruction = "RM"},
    [0xf9] = {.instruction = "SPHL"},
    [0xfa] = {.instruction = "JM", .arg = argtype_addr},
    [0xfb] = {.instruction = "EI"},
    [0xfc] = {.instruction = "CM", .arg = argtype_addr},
    [0xfd] = {.instruction = "-"},
    [0xfe] = {.instruction = "CPI", .arg = argtype_d8},
    [0xff] = {.instruction = "RST 7"},
};

size_t dissassemble(FILE* restrict in, FILE* restrict out) {
        uint16_t pc = 0;
        for (int op = fgetc(in); op != EOF; op = fgetc(in)) {
                Opcode opcode = opcodes[op];
                if (!opcode.instruction) {
                        fprintf(stderr, "Unknown opcode: %02x\n", op);
                        return 0;
                }
                if (opcode.arg == argtype_none) {
                        fprintf(out, "%04x %02x\t\t%s", pc, op,
                                opcode.instruction);
                }
                if (opcode.arg == argtype_d8) {
                        int a = fgetc(in);
                        if (a == EOF) {
                                fprintf(stderr, "Unexpected EOF\n");
                                return 0;
                        }
                        fprintf(out, "%04x %02x %02x\t%s #$%02x", pc, op, a,
                                opcode.instruction, a);
                        pc++;
                }
                if (opcode.arg == argtype_d16) {
                        int a = fgetc(in);
                        int b = fgetc(in);
                        if (b == EOF) {
                                fprintf(stderr, "Unexpected EOF\n");
                                return 0;
                        }
                        fprintf(out, "%04x %02x %02x %02x\t%s #$%02x%02x", pc,
                                op, a, b, opcode.instruction, b, a);
                        pc += 2;
                }
                if (opcode.arg == argtype_addr) {
                        int a = fgetc(in);
                        int b = fgetc(in);
                        if (b == EOF) {
                                fprintf(stderr, "Unexpected EOF\n");
                                return 0;
                        }
                        fprintf(out, "%04x %02x %02x %02x\t%s $%02x%02x", pc,
                                op, a, b, opcode.instruction, b, a);
                        pc += 2;
                }
                fprintf(out, "\n");

                pc++;
        }

        return 1;
}

int main(void) {
        FILE* in = freopen(0, "rb", stdin);
        if (!in) {
                fprintf(stderr, "Failed to open stdin in binary mode\n");
                return EXIT_FAILURE;
        }

        if (!dissassemble(in, stdout)) {
                return EXIT_FAILURE;
        }

        return EXIT_SUCCESS;
}