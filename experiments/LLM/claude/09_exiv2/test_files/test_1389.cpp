#include <gtest/gtest.h>
#include <sstream>
#include <exiv2/exiv2.hpp>

// Forward declaration of the function under test
namespace Exiv2 {
namespace Internal {
std::ostream& print0x000c(std::ostream& os, const Value& value, const ExifData* metadata);
}
}

class Print0x000cTest_1389 : public ::testing::Test {
protected:
    std::ostringstream os;
};

// Test with 'K' value - should print "km/h"
TEST_F(Print0x000cTest_1389, ValueK_PrintsKmh_1389) {
    auto value = Exiv2::Value::create(Exiv2::asciiString);
    value->read("K");
    Exiv2::Internal::print0x000c(os, *value, nullptr);
    EXPECT_NE(os.str().find("km/h"), std::string::npos);
}

// Test with 'M' value - should print "mph"
TEST_F(Print0x000cTest_1389, ValueM_PrintsMph_1389) {
    auto value = Exiv2::Value::create(Exiv2::asciiString);
    value->read("M");
    Exiv2::Internal::print0x000c(os, *value, nullptr);
    EXPECT_NE(os.str().find("mph"), std::string::npos);
}

// Test with 'N' value - should print "knots"
TEST_F(Print0x000cTest_1389, ValueN_PrintsKnots_1389) {
    auto value = Exiv2::Value::create(Exiv2::asciiString);
    value->read("N");
    Exiv2::Internal::print0x000c(os, *value, nullptr);
    EXPECT_NE(os.str().find("knots"), std::string::npos);
}

// Test with unknown value - should print something (likely the raw value or "(x)")
TEST_F(Print0x000cTest_1389, UnknownValue_PrintsSomething_1389) {
    auto value = Exiv2::Value::create(Exiv2::asciiString);
    value->read("X");
    Exiv2::Internal::print0x000c(os, *value, nullptr);
    std::string result = os.str();
    // The output should not be empty for an unknown value
    EXPECT_FALSE(result.empty());
    // It should NOT match any of the known descriptions
    EXPECT_EQ(result.find("km/h"), std::string::npos);
    EXPECT_EQ(result.find("mph"), std::string::npos);
    EXPECT_EQ(result.find("knots"), std::string::npos);
}

// Test with nullptr metadata - should still work
TEST_F(Print0x000cTest_1389, NullMetadata_DoesNotCrash_1389) {
    auto value = Exiv2::Value::create(Exiv2::asciiString);
    value->read("K");
    EXPECT_NO_THROW(Exiv2::Internal::print0x000c(os, *value, nullptr));
}

// Test with ExifData object
TEST_F(Print0x000cTest_1389, WithExifData_PrintsCorrectly_1389) {
    Exiv2::ExifData exifData;
    auto value = Exiv2::Value::create(Exiv2::asciiString);
    value->read("M");
    Exiv2::Internal::print0x000c(os, *value, &exifData);
    EXPECT_NE(os.str().find("mph"), std::string::npos);
}

// Test that the function returns the ostream reference
TEST_F(Print0x000cTest_1389, ReturnsOstreamReference_1389) {
    auto value = Exiv2::Value::create(Exiv2::asciiString);
    value->read("N");
    std::ostream& result = Exiv2::Internal::print0x000c(os, *value, nullptr);
    EXPECT_EQ(&result, &os);
}

// Test with empty string value
TEST_F(Print0x000cTest_1389, EmptyValue_PrintsSomething_1389) {
    auto value = Exiv2::Value::create(Exiv2::asciiString);
    value->read("");
    EXPECT_NO_THROW(Exiv2::Internal::print0x000c(os, *value, nullptr));
}

// Test with integer value type representing 'K' (75 in ASCII)
TEST_F(Print0x000cTest_1389, IntegerValueK_1389) {
    auto value = Exiv2::Value::create(Exiv2::unsignedShort);
    value->read("75"); // 'K' = 75 in ASCII
    Exiv2::Internal::print0x000c(os, *value, nullptr);
    std::string result = os.str();
    EXPECT_FALSE(result.empty());
}

// Test with integer value type representing 'M' (77 in ASCII)
TEST_F(Print0x000cTest_1389, IntegerValueM_1389) {
    auto value = Exiv2::Value::create(Exiv2::unsignedShort);
    value->read("77"); // 'M' = 77 in ASCII
    Exiv2::Internal::print0x000c(os, *value, nullptr);
    std::string result = os.str();
    EXPECT_FALSE(result.empty());
}

// Test with integer value type representing 'N' (78 in ASCII)
TEST_F(Print0x000cTest_1389, IntegerValueN_1389) {
    auto value = Exiv2::Value::create(Exiv2::unsignedShort);
    value->read("78"); // 'N' = 78 in ASCII
    Exiv2::Internal::print0x000c(os, *value, nullptr);
    std::string result = os.str();
    EXPECT_FALSE(result.empty());
}

// Test with an unrecognized integer value
TEST_F(Print0x000cTest_1389, IntegerValueUnknown_1389) {
    auto value = Exiv2::Value::create(Exiv2::unsignedShort);
    value->read("999");
    Exiv2::Internal::print0x000c(os, *value, nullptr);
    std::string result = os.str();
    EXPECT_FALSE(result.empty());
}
