#include <cstdint>
#include <array>

class Memory
{
public:
    void Init();
    uint8_t& operator[](uint32_t pos);
private:
    std::array<uint8_t, 1024 * 64> data;
};