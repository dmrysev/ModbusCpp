#pragma once

#include <memory>
#include <chrono>
#include "drivemodbustcp.h"
#include "drivemodbusrtu.h"

class Test
{
public:
    Test();
    void read_parameter(uint16_t group, uint16_t parameter);
    void read_register(uint32_t address);
    void continious_read();
    void read_n_times(uint32_t count, uint16_t group, uint16_t parameter);
    void read_n_times(uint32_t count, uint32_t register_address);
    void read_fault();
    void restart_drive();

private:
    std::unique_ptr<DriveModbus> modbus;
    void calculate_durations(chrono::steady_clock::time_point begin,
                             chrono::steady_clock::time_point end,
                             uint32_t count);
};
