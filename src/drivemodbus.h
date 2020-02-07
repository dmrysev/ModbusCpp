#ifndef DRIVEMODBUSRADER_H
#define DRIVEMODBUSRADER_H

#include <string>
#include "modbus/modbus.h"

using namespace std;

class DriveModbus
{
public:
    DriveModbus();
    ~DriveModbus();
    int32_t read_int32(uint16_t group, uint16_t parameter);
    int32_t read_int32(uint32_t address);
    int16_t read_int16(uint16_t group, uint16_t parameter);
    int16_t read_int16(uint32_t address);
    void write_int32(uint32_t address, int32_t value);
    void write_int32(uint16_t group, uint16_t parameter, int32_t value);
    static uint32_t get_address_16bit(uint16_t group, uint16_t parameter);
    static uint32_t get_address_32bit(uint16_t group, uint16_t parameter);

protected:
    modbus_t *mb;
    void read_registers(uint32_t address, uint16_t size, uint16_t *response);
};

#endif // DRIVEMODBUSRADER_H
