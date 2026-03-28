// File: string_maker_unsigned_int_convert_test_272.cpp
#include <gtest/gtest.h>
#include <string>
#include <limits>

// Include the Catch2 StringMaker declaration.
// Adjust include path if your project layout differs.
#include "catch2/catch_tostring.hpp"

namespace {

using Catch::StringMaker;

// Fixture kept minimal for naming consistency & future extension
class StringMakerUIntTest_272 : public ::testing::Test {};

TEST_F(StringMakerUIntTest_272, ConvertsZeroToString_272) {
    unsigned int v = 0u;
    EXPECT_EQ(StringMaker<unsigned int>::convert(v), std::to_string(v));
}

TEST_F(StringMakerUIntTest_272, ConvertsOneToString_272) {
    unsigned int v = 1u;
    EXPECT_EQ(StringMaker<unsigned int>::convert(v), std::to_string(v));
}

TEST_F(StringMakerUIntTest_272, ConvertsTypicalValues_272) {
    const unsigned int values[] = { 2u, 7u, 42u, 123u, 1024u, 65535u, 100000u, 999999u };
    for (unsigned int v : values) {
        EXPECT_EQ(StringMaker<unsigned int>::convert(v), std::to_string(v)) << "Mismatch for v=" << v;
    }
}

TEST_F(StringMakerUIntTest_272, ConvertsPowersOfTwo_272) {
    // Covers changing digit lengths and high-bit transitions
    const unsigned int values[] = {
        1u, 2u, 4u, 8u, 16u, 32u, 64u, 128u, 256u, 512u,
        1024u, 2048u, 4096u, 8192u, 16384u, 32768u, 65536u,
        1u << 20, 1u << 24, 1u << 30 // the last is safe if UINT is >= 31 bits
    };
    for (unsigned int v : values) {
        // Guard against shifting beyond the width of unsigned int
        if (v == 0u) continue;
        EXPECT_EQ(StringMaker<unsigned int>::convert(v), std::to_string(v)) << "Mismatch for v=" << v;
    }
}

TEST_F(StringMakerUIntTest_272, ConvertsMaxUnsignedInt_272) {
    unsigned int v = std::numeric_limits<unsigned int>::max();
    EXPECT_EQ(StringMaker<unsigned int>::convert(v), std::to_string(v));
}

TEST_F(StringMakerUIntTest_272, NoSignCharactersForLargeValues_272) {
    // Ensure formatting is unsigned-like (no negative sign) for high-bit values.
    unsigned int v = std::numeric_limits<unsigned int>::max();
    std::string s = StringMaker<unsigned int>::convert(v);
    ASSERT_FALSE(s.empty());
    EXPECT_NE(s[0], '-') << "Result should not be a negative representation";
    EXPECT_EQ(s, std::to_string(v));
}

TEST_F(StringMakerUIntTest_272, DeterministicRepeatedCalls_272) {
    unsigned int v = 1234567890u; // representative large-ish value within unsigned int range
    std::string a = StringMaker<unsigned int>::convert(v);
    std::string b = StringMaker<unsigned int>::convert(v);
    EXPECT_EQ(a, b);
    EXPECT_EQ(a, std::to_string(v));
}

} // namespace
