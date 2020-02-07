#include <iostream>
#include "drivemodbus.h"


using namespace std;

DriveModbus::DriveModbus() {
}

int32_t DriveModbus::read_int32(uint16_t group, uint16_t parameter) {
    uint32_t address = get_address_32bit(group, parameter);
    auto result = read_int32(address);

    return result;
}

int32_t DriveModbus::read_int32(uint32_t address) {
    constexpr uint8_t size = 2;
    uint16_t response[size];
    read_registers(address, size, response);
    int32_t result = (response[0] << 16) + response[1];

    return result;
}

int16_t DriveModbus::read_int16(uint16_t group, uint16_t parameter) {
    uint32_t address = get_address_16bit(group, parameter);
    int16_t result = read_int16(address);

    return result;
}

int16_t DriveModbus::read_int16(uint32_t address) {
    const uint8_t size = 1;
    uint16_t response[size];
    read_registers(address, size, response);
    int16_t result = int16_t(response[0]);

    return result;
}

void DriveModbus::write_int32(uint32_t address, int32_t value) {
    int mask = (1 << 16) - 1;
    uint16_t value1 = uint16_t(value >> 16);
    uint16_t value2 = uint16_t(value & mask);
    uint16_t values[] = {value1, value2};
    int ret = modbus_write_registers(mb, int(address), 2, values);

    if (ret == -1) {
        string msg = "Writing register failed. ";
        msg += modbus_strerror(errno);
        throw runtime_error(msg);
    }
}

void DriveModbus::write_int32(uint16_t group, uint16_t parameter, int32_t value) {
    uint32_t address = get_address_32bit(group, parameter);
    write_int32(address, value);
}

uint32_t DriveModbus::get_address_16bit(uint16_t group, uint16_t parameter) {
    uint32_t address = uint32_t(100 * group + parameter);

    return address;
}

uint32_t DriveModbus::get_address_32bit(uint16_t group, uint16_t parameter) {
    uint32_t address = uint32_t((20000 + 200 * group + 2 * parameter) - 1);

    return address;
}

void DriveModbus::read_registers(uint32_t address, uint16_t size, uint16_t* response){
    int rc = modbus_read_registers(mb, (int) address, (int) size, response);
    if (rc == -1) {
        string msg = "Reading registers failed. ";
        msg += modbus_strerror(errno);
        throw runtime_error(msg);
    }
}

DriveModbus::~DriveModbus() {
    modbus_close(mb);
    modbus_free(mb);
}
