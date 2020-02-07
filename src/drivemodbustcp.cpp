#include <iostream>
#include "drivemodbustcp.h"
#include "modbus/modbus.h"

DriveModbusTCP::DriveModbusTCP(string ip_address, uint16_t port) {
    mb = modbus_new_tcp(ip_address.c_str(), port);
    connect();
}

void DriveModbusTCP::connect() {
    if (mb == NULL) {
        string msg = "Connection failed. ";
        msg += modbus_strerror(errno);
        throw runtime_error(msg);
    }

    if (modbus_connect(mb) == -1) {
        string msg = "Connection failed. ";
        msg += modbus_strerror(errno);
        throw runtime_error(msg);
    }
}
