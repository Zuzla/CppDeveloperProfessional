#include "print_ip.h"

using namespace print_ip;

int main(int argc, char **argv)
{
    Print_ip(int8_t{-1});                            // 255
    Print_ip(int16_t{0});                            // 0.0
    Print_ip(int32_t{2130706433});                   // 127.0.0.1
    Print_ip(int64_t{8875824491850138409});          // 123.45.67.89.101.112.131.41
    Print_ip(std::string{"Hello, World!"});          // Hello, World!
    Print_ip(std::vector<int>{100, 200, 300, 400});  // 100.200.300.400
    Print_ip(std::list<short>{400, 300, 200, 100});  // 400.300.200.100
    Print_ip(std::make_tuple(123, 456, 789, 0)); // 123.456.789.0
}
