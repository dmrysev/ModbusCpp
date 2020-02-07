#include "drivemodbusrtu.h"
#include <iostream>

using namespace std;

DriveModbusRTU::DriveModbusRTU(string port, uint16_t node_id, uint32_t baud, char parity,
                               uint8_t data_bit, uint8_t stop_bit)
{
    mb = modbus_new_rtu(port.c_str(), (int16_t) baud, parity, (int8_t) data_bit, (int8_t) stop_bit);
    connect(node_id);
}

void DriveModbusRTU::connect(uint16_t node_id) {
    if (mb == NULL) {
        string msg = "Connection failed. ";
        msg += modbus_strerror(errno);
        throw runtime_error(msg);
    }

    modbus_set_slave(mb, node_id);

    if (modbus_connect(mb) == -1) {
        string msg = "Connection failed. ";
        msg += modbus_strerror(errno);
        throw runtime_error(msg);
    }
}
