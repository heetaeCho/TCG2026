#include <gtest/gtest.h>
#include <sstream>
#include <exiv2/exiv2.hpp>

// We need access to the internal function
namespace Exiv2 {
namespace Internal {
std::ostream& printGPSDirRef(std::ostream& os, const Value& value, const ExifData* metadata);
}
}

class PrintGPSDirRefTest_1420 : public ::testing::Test {
protected:
    std::ostringstream os;
};

// Test with value 'T' which should print "True direction"
TEST_F(PrintGPSDirRefTest_1420, TrueDirection_1420) {
    Exiv2::AsciiValue value;
    value.read("T");
    Exiv2::Internal::printGPSDirRef(os, value, nullptr);
    EXPECT_EQ(os.str(), "True direction");
}

// Test with value 'M' which should print "Magnetic direction"
TEST_F(PrintGPSDirRefTest_1420, MagneticDirection_1420) {
    Exiv2::AsciiValue value;
    value.read("M");
    Exiv2::Internal::printGPSDirRef(os, value, nullptr);
    EXPECT_EQ(os.str(), "Magnetic direction");
}

// Test with an unknown/invalid value - should print something (likely the raw value or "(n)")
TEST_F(PrintGPSDirRefTest_1420, UnknownValue_1420) {
    Exiv2::AsciiValue value;
    value.read("X");
    Exiv2::Internal::printGPSDirRef(os, value, nullptr);
    std::string result = os.str();
    // Unknown value should not match known tags
    EXPECT_NE(result, "True direction");
    EXPECT_NE(result, "Magnetic direction");
    EXPECT_FALSE(result.empty());
}

// Test with ExifData pointer being non-null (should still work)
TEST_F(PrintGPSDirRefTest_1420, WithExifDataPointer_1420) {
    Exiv2::AsciiValue value;
    value.read("T");
    Exiv2::ExifData exifData;
    Exiv2::Internal::printGPSDirRef(os, value, &exifData);
    EXPECT_EQ(os.str(), "True direction");
}

// Test with ExifData pointer being null and value 'M'
TEST_F(PrintGPSDirRefTest_1420, MagneticDirectionNullMetadata_1420) {
    Exiv2::AsciiValue value;
    value.read("M");
    Exiv2::Internal::printGPSDirRef(os, value, nullptr);
    EXPECT_EQ(os.str(), "Magnetic direction");
}

// Test that the function returns a reference to the same ostream
TEST_F(PrintGPSDirRefTest_1420, ReturnsOstreamReference_1420) {
    Exiv2::AsciiValue value;
    value.read("T");
    std::ostream& result = Exiv2::Internal::printGPSDirRef(os, value, nullptr);
    EXPECT_EQ(&result, &os);
}

// Test with empty string value
TEST_F(PrintGPSDirRefTest_1420, EmptyValue_1420) {
    Exiv2::AsciiValue value;
    value.read("");
    Exiv2::Internal::printGPSDirRef(os, value, nullptr);
    std::string result = os.str();
    // Should produce some output (likely unknown/fallback)
    EXPECT_NE(result, "True direction");
    EXPECT_NE(result, "Magnetic direction");
}

// Test with a lowercase 't' - should not match 'T'
TEST_F(PrintGPSDirRefTest_1420, LowercaseT_1420) {
    Exiv2::AsciiValue value;
    value.read("t");
    Exiv2::Internal::printGPSDirRef(os, value, nullptr);
    std::string result = os.str();
    // Lowercase should not match the uppercase tag
    EXPECT_NE(result, "True direction");
}

// Test with a lowercase 'm' - should not match 'M'
TEST_F(PrintGPSDirRefTest_1420, LowercaseM_1420) {
    Exiv2::AsciiValue value;
    value.read("m");
    Exiv2::Internal::printGPSDirRef(os, value, nullptr);
    std::string result = os.str();
    EXPECT_NE(result, "Magnetic direction");
}

// Test consecutive calls to ensure stream accumulates
TEST_F(PrintGPSDirRefTest_1420, ConsecutiveCalls_1420) {
    Exiv2::AsciiValue value1;
    value1.read("T");
    Exiv2::Internal::printGPSDirRef(os, value1, nullptr);
    std::string first = os.str();
    EXPECT_EQ(first, "True direction");

    Exiv2::AsciiValue value2;
    value2.read("M");
    Exiv2::Internal::printGPSDirRef(os, value2, nullptr);
    std::string combined = os.str();
    EXPECT_EQ(combined, "True directionMagnetic direction");
}
