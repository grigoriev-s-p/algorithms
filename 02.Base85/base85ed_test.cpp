#include <gtest/gtest.h>

#include <vector>
#include <cstdint>
#include <string>

#include "base85ed.h"

const std::vector<std::pair<const char *, const char *>> short_cases =
{
    { "",      ""     },
    { "F#",    "1"    },
    { "F){",   "12"   },
    { "F)}j",  "123"  },
    { "F)}kW", "1234" }
};

static std::vector<uint8_t> cstr2v(const char *s)
{
    return std::vector<uint8_t>(s, s + std::string(s).size());
}

TEST(Base85ShortsEncode, TrivialShortEncodes)
{
    for (const auto &p : short_cases)
    {
        EXPECT_EQ(base85::encode(cstr2v(p.second)), cstr2v(p.first));
    }
}

TEST(Base85ShortsDecode, TrivialShortDecodes)
{
    for (const auto &p : short_cases)
    {
        EXPECT_EQ(base85::decode(cstr2v(p.first)), cstr2v(p.second));
    }
}

TEST(Base85Encode, HelloEncode)
{
    EXPECT_EQ(base85::encode(cstr2v("hello")), cstr2v("Xk~0{Zv"));
}

TEST(Base85Decode, HelloDecode)
{
    EXPECT_EQ(base85::decode(cstr2v("Xk~0{Zv")), cstr2v("hello"));
}

TEST(Base85RoundTrip, DifferentBytes)
{
    std::vector<uint8_t> data = {0, 1, 2, 3, 4, 5, 254, 255};
    EXPECT_EQ(base85::decode(base85::encode(data)), data);
}

