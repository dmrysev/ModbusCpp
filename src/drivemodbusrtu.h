#ifndef DRIVEMODBUSRTU_H
#define DRIVEMODBUSRTU_H

#include "drivemodbus.h"

class DriveModbusRTU: public DriveModbus
{
public:
    uint16_t node_id;

    DriveModbusRTU(string port, uint16_t node_id, uint32_t baud = 9600, char parity = 'N',
                   uint8_t data_bit = 8, uint8_t stop_bit = 1);
private:
    void connect(uint16_t node_id);
};

#endif // DRIVEMODBUSRTU_H
