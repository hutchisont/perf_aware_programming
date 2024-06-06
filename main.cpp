#include <assert.h>
#include <bitset>
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>

namespace {
    constexpr unsigned char OpcodeMask = 0b1111'1100;
    constexpr unsigned char DMask = 0b0000'0010;
    constexpr unsigned char WMask = 0b0000'0001;
    constexpr unsigned char ModMask = 0b1100'0000;
    constexpr unsigned char RegMask = 0b0011'1000;
    constexpr unsigned char RMMask = 0b0000'0111;
}

enum class opcode {
    mov,
};

std::string opcodeToString(const opcode& code) {
    switch (code) {
    case opcode::mov:
        return "mov";
        break;
    }

    std::cerr
        << "we got an unknown opcode, need to update the switch to handle it"
        << std::endl;
    assert(false);
}

std::map<unsigned char, opcode> opcodes = {
    {0b1000'1000, opcode::mov},
};

std::map<unsigned char, std::string> Mod11Registers16 = {
    {0b000, "ax"}, {0b001, "cx"}, {0b010, "dx"}, {0b011, "bx"},
    {0b100, "sp"}, {0b101, "bp"}, {0b110, "si"}, {0b111, "di"},
};

std::map<unsigned char, std::string> Mod11Registers8 = {
    {0b000, "al"}, {0b001, "cl"}, {0b010, "dl"}, {0b011, "bl"},
    {0b100, "ah"}, {0b101, "ch"}, {0b110, "dh"}, {0b111, "bh"},
};

std::string toRegister(const unsigned char mod, const unsigned char width,
                       const unsigned char enc) {
    switch (mod) {
    case 0b00:
    case 0b01:
    case 0b10:
        std::cerr << "not yet implemented mod: " << std::bitset<2>(mod)
                  << std::endl;
        exit(1);
        break;
    case 0b11:
        switch (width) {
        case 0b0:
            return Mod11Registers8[enc];
        case 0b1:
            return Mod11Registers16[enc];
        }
    }

    std::cerr << "could not determine register\n";
    std::cerr << "mod: " << std::bitset<2>(mod) << "\n";
    std::cerr << "width: " << std::bitset<3>(width) << "\n";
    std::cerr << "enc: " << std::bitset<3>(enc) << std::endl;
    assert(false);
}

void printVectorBinary(const std::vector<unsigned char>& vec) {
    for (const auto& ele : vec) {
        std::cout << std::bitset<8>(ele) << std::endl;
    }
}

void printVectorString(const std::vector<std::string>& vec) {
    for (const auto& ele : vec) {
        std::cout << ele << std::endl;
    }
}

std::vector<std::string> convertToASM(const std::vector<unsigned char>& data) {
    std::vector<std::string> asmCommands;
    for (size_t i = 0; i < data.size(); ++i) {
        const auto b1 = data[i];
        const auto opcode = b1 & OpcodeMask;
        const auto dir = (b1 & DMask) >> 1;
        (void)dir;
        const auto width = b1 & WMask;
        const auto op = opcodes[opcode];
        std::string loc1 = "";
        std::string loc2 = "";
        switch (op) {
        case opcode::mov:
            const auto b2 = data[++i];
            const auto mod = (b2 & ModMask) >> 6;
            const auto reg = (b2 & RegMask) >> 3;
            const auto rm = b2 & RMMask;
            loc1 = toRegister(mod, width, reg);
            loc2 = toRegister(mod, width, rm);
            break;
        }
        const auto opcodeString = opcodeToString(op);
        asmCommands.push_back(opcodeString + " " + loc2 + ", " + loc1);
    }

    return asmCommands;
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "a filepath to the asm file to decode must be provided"
                  << std::endl;
        exit(1);
    }
    std::ifstream input(argv[1], std::ios::binary);
    std::vector<unsigned char> asmData(std::istreambuf_iterator<char>(input),
                                       {});
    std::vector<std::string> asmCommands = convertToASM(asmData);
    printVectorString(asmCommands);

    return 0;
}
