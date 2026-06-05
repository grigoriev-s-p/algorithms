#include <vector>
#include <cstdint>
#include <stdexcept>

#include "base85ed.h"

std::vector<uint8_t> base85::encode(std::vector<uint8_t> const &bytes)
{
    std::vector<uint8_t> result;
    const char *alphabet =
        "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz!#$%&()*+-;<=>?@^_`{|}~";

    for (size_t i = 0; i < bytes.size(); i += 4)
    {
        uint32_t value = 0;
        int count = 0;

        for (int j = 0; j < 4; ++j)
        {
            value = value * 256;

            if (i + j < bytes.size())
            {
                value += bytes[i + j];
                ++count;
            }
        }

        uint8_t block[5];

        for (int j = 4; j >= 0; --j)
        {
            block[j] = alphabet[value % 85];
            value /= 85;
        }
        if (count == 4)
        {
            for (int j = 0; j < 5; ++j)
            {
                result.push_back(block[j]);
            }
        }
        else
        {
            for (int j = 0; j < count + 1; ++j)
            {
                result.push_back(block[j]);
            }
        }
    }

    return result;
}

std::vector<uint8_t> base85::decode(std::vector<uint8_t> const &b85str)
{
    std::vector<uint8_t> result;
    const char *alphabet =
        "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz!#$%&()*+-;<=>?@^_`{|}~";

    for (size_t i = 0; i < b85str.size(); i += 5)
    {
        int count;

        if (i + 5 <= b85str.size())
        {
            count = 5;
        }
        else
        {
            count = b85str.size() - i;
        }

        uint32_t value = 0;

        for (int j = 0; j < count; ++j)
        {
            int digit = -1;

            for (int k = 0; k < 85; ++k)
            {
                if (b85str[i + j] == alphabet[k])
                {
                    digit = k;
                    break;
                }
            }

            if (digit == -1)
            {
                throw std::runtime_error("Invalid Base85 character");
            }

            value = value * 85 + digit;
        }

        for (int j = count; j < 5; ++j)
        {
            value = value * 85 + 84;
        }

        uint8_t block[4];

        for (int j = 3; j >= 0; --j)
        {
            block[j] = value % 256;
            value /= 256;
        }

        if (count == 5)
        {
            for (int j = 0; j < 4; ++j)
            {
                result.push_back(block[j]);
            }
        }
        else
        {
            for (int j = 0; j < count - 1; ++j)
            {
                result.push_back(block[j]);
            }
        }
    }

    return result;
}