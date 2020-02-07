#ifndef DRIVEMODBUSTCP_H
#define DRIVEMODBUSTCP_H

#include "drivemodbus.h"


class DriveModbusTCP: public DriveModbus
{
public:
    DriveModbusTCP(string ip_address, uint16_t port);

private:
    void connect();
};

#endif // DRIVEMODBUSTCP_H
