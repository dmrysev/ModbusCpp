#include "test.h"
#include <iostream>
#include <chrono>
#include <vector>
#include <typeinfo>
#include <string>
#include "common.h"

using namespace std;

Test::Test():
//    modbus{make_unique<DriveModbusTCP>("172.17.4.204", 502)}
    modbus{make_unique<DriveModbusRTU>("\\\\.\\COM23", 1, 9600)}
{
    //        int16_t value = test.modbus->read_int16(30, 12);
    //        cout << value << endl;

//        test.read_fault();
//        test.restart_drive();

    //        test.modbus->write_int32(229, 1, 1);

        modbus->write_int32(92, 1, 2);
//        read_parameter(30, 12);

    //        uint32_t address = DriveModbus::get_address(1, 11);
    //        test.read_n_times(100, address);
    //        test.read_n_times(100, 30, 12);
//    read_register(54);
    //        test.read_n_times(100, 56);
    //    test.continious_read();
}

void Test::read_parameter(uint16_t group, uint16_t parameter) {
    int32_t value = modbus->read_int32(group, parameter);
    cout << "Value of parameter " << group << '.' << parameter
         << " = " << value << '\n';
}

void Test::read_register(uint32_t address) {
    int32_t value = modbus->read_int32(address);
    cout << "Value of register " << address << " = " << value << '\n';
}

void Test::continious_read() {
    while(true) {
        int32_t result = modbus->read_int32(1, 1);
        cout << result << '\n';
    }
}

void Test::read_n_times(uint32_t count, uint16_t group, uint16_t parameter) {
    uint32_t address = DriveModbus::get_address_32bit(group, parameter);
    read_n_times(count, address);
}

void Test::read_n_times(uint32_t count, uint32_t register_address) {
    chrono::steady_clock::time_point begin = chrono::steady_clock::now();
    vector<int32_t> values;
    for (uint32_t i = 0; i < count; i++) {
        int32_t value = modbus->read_int32(register_address);
        values.push_back(value);
    }
    chrono::steady_clock::time_point end = chrono::steady_clock::now();
    calculate_durations(begin, end, count);
}

void Test::read_fault() {
    int32_t int_value = modbus->read_int32(4, 1);
    string hex_value = int_to_hex(int_value);
    cout << hex_value << '\n';
}

void Test::restart_drive() {
    modbus->write_int32(96, 8, 1);
}

void Test::calculate_durations(chrono::steady_clock::time_point begin,
                         chrono::steady_clock::time_point end,
                         uint32_t count)
{
    auto total_duration = chrono::duration_cast<chrono::microseconds>(end - begin).count();
    auto total_duration_ms = float(total_duration) / 1000;
    cout << "Total duration = " << total_duration_ms << " milliseconds\n";

    auto duration_per_one_read = total_duration / count;
    auto duration_per_one_read_ms = float(duration_per_one_read) / 1000;
    cout << "Duration per one read = " << duration_per_one_read_ms << " milliseconds\n";
}
