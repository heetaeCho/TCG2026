// File: test_stringmaker_uchar_convert_277.cpp
#include <gtest/gtest.h>
#include <string>

// Adjust include to your project layout as needed:
#include "catch2/catch_tostring.hpp"

using Catch::StringMaker;

namespace {

// Normal operation: printable ASCII
TEST(StringMakerUnsignedCharTest_277, PrintableAsciiMatchesChar_277) {
    const unsigned char v = static_cast<unsigned char>('A');

    const std::string as_unsigned = StringMaker<unsigned char>::convert(v);
    const std::string as_char     = StringMaker<char>::convert(static_cast<char>(v));

    EXPECT_EQ(as_unsigned, as_char);
}

// Boundary: NUL (0)
TEST(StringMakerUnsignedCharTest_277, NullByteMatchesChar_277) {
    const unsigned char v = 0u;

    EXPECT_NO_THROW({
        const std::string as_unsigned = StringMaker<unsigned char>::convert(v);
        const std::string as_char     = StringMaker<char>::convert(static_cast<char>(v));
        EXPECT_EQ(as_unsigned, as_char);
    });
}

// Boundary & extended values: 0, 1, 127, 128, 255
TEST(StringMakerUnsignedCharTest_277, BoundaryAndExtendedValuesMatchChar_277) {
    const unsigned char values[] = { 0u, 1u, 127u, 128u, 255u };

    for (unsigned char v : values) {
        SCOPED_TRACE(::testing::Message() << "value=" << static_cast<unsigned int>(v));
        const std::string as_unsigned = StringMaker<unsigned char>::convert(v);
        const std::string as_char     = StringMaker<char>::convert(static_cast<char>(v));
        EXPECT_EQ(as_unsigned, as_char);
    }
}

// Stability: repeated calls yield identical results
TEST(StringMakerUnsignedCharTest_277, RepeatedCallsConsistent_277) {
    const unsigned char v = 200u; // extended range

    const std::string first  = StringMaker<unsigned char>::convert(v);
    const std::string second = StringMaker<unsigned char>::convert(v);

    EXPECT_EQ(first, second);
}

} // namespace
