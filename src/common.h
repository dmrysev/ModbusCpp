#ifndef COMMON_H
#define COMMON_H

#include <string>
#include <sstream>

string int_to_hex(int32_t value) {
    std::stringstream stream;
    stream << std::hex << value;
    string result(stream.str());

    return result;
}

#endif // COMMON_H
