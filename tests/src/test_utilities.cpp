#include "test_utilities.hpp"
#include <iomanip>
#include <iostream>
#include <algorithm>

void test_equal(const std::vector<uint8_t>& buffer1, const std::vector<uint8_t>& buffer2)
{
    if (buffer1.size() != buffer2.size())
    {
        size_t len = std::min(buffer1.size(),buffer2.size());
        std::cout << "buffer1 size " << buffer1.size() << " != buffer2 size " << buffer2.size() << "\n"; 
        for (size_t k = 0; k <= len; ++k)
        {
            std::cout << std::hex << std::setprecision(2) << std::setw(2) 
                      << std::noshowbase << std::setfill('0') << static_cast<int>(buffer1[k]);
        }
        for (size_t k = 0; k <= len; ++k)
        {
            std::cout << std::hex << std::setprecision(2) << std::setw(2) 
                      << std::noshowbase << std::setfill('0') << static_cast<int>(buffer2[k]);
        }
    }
    REQUIRE(buffer1.size() == buffer2.size());

    for (size_t i = 0; i < buffer1.size(); ++i)
    {
        if (buffer1[i] != buffer2[i])
        {
            std::cout << "Different at position " << i << "\n"; 
            for (size_t k = 0; k <= i; ++k)
            {
                std::cout << std::hex << std::setprecision(2) << std::setw(2) 
                          << std::noshowbase << std::setfill('0') << static_cast<int>(buffer1[k]);
            }
            for (size_t k = 0; k <= i; ++k)
            {
                std::cout << std::hex << std::setprecision(2) << std::setw(2) 
                          << std::noshowbase << std::setfill('0') << static_cast<int>(buffer2[k]);
            }
        }
        REQUIRE(buffer2[i] == buffer1[i]);
    }
}

