// File: catch_convert_pointer_test_86.cpp

#include <gtest/gtest.h>
#include <string>

// Include the header under test
#include "Catch2/src/catch2/catch_tostring.hpp"

namespace {

using ::Catch::convert;
using ::Catch::Detail::rawMemoryToString;

// Simple fixture (kept minimal for clarity/consistency)
class CatchConvertPointerTest_86 : public ::testing::Test {};

TEST_F(CatchConvertPointerTest_86, NullIntPointer_ReturnsLiteralNullptr_86) {
    int* p = nullptr;
    EXPECT_EQ(convert(p), std::string("nullptr"));
}

TEST_F(CatchConvertPointerTest_86, NonNullIntPointer_UsesRawMemoryToString_86) {
    int value = 42;
    int* p = &value;

    const std::string expected = rawMemoryToString(p);
    const std::string actual   = convert(p);

    EXPECT_EQ(actual, expected);
    EXPECT_NE(actual, std::string("nullptr"));
}

TEST_F(CatchConvertPointerTest_86, NonNullVoidPointer_UsesRawMemoryToString_86) {
    int value = 7;
    void* p = &value;

    const std::string expected = rawMemoryToString(p);
    const std::string actual   = convert(static_cast<void*>(p));

    EXPECT_EQ(actual, expected);
    EXPECT_NE(actual, std::string("nullptr"));
}

TEST_F(CatchConvertPointerTest_86, NonNullConstPointer_UsesRawMemoryToString_86) {
    const int value = 13;
    const int* p = &value;

    const std::string expected = rawMemoryToString(p);
    const std::string actual   = convert(p);

    EXPECT_EQ(actual, expected);
    EXPECT_NE(actual, std::string("nullptr"));
}

TEST_F(CatchConvertPointerTest_86, DifferentAddresses_ProduceDifferentStrings_86) {
    int a = 1;
    int b = 2;

    const std::string sa = convert(&a);
    const std::string sb = convert(&b);

    // Observable behavior: different non-null pointers stringify differently.
    EXPECT_NE(sa, sb);
    EXPECT_NE(sa, std::string("nullptr"));
    EXPECT_NE(sb, std::string("nullptr"));
}

} // namespace
