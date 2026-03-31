#include <gtest/gtest.h>
#include <exiv2/value.hpp>
#include <exiv2/exif.hpp>
#include <sstream>

// Declaration of the function under test
namespace Exiv2 {
namespace Internal {
std::ostream& print0x0000(std::ostream& os, const Value& value, const ExifData*);
}
}

using namespace Exiv2;
using namespace Exiv2::Internal;

class Print0x0000Test_1383 : public ::testing::Test {
protected:
    std::ostringstream os;
};

// Test normal operation: 4 unsignedByte values formatted as version string
TEST_F(Print0x0000Test_1383, NormalFourUnsignedBytes_1383) {
    auto value = Value::create(unsignedByte);
    value->read("48 50 51 48");
    std::string result;
    print0x0000(os, *value, nullptr);
    result = os.str();
    EXPECT_EQ(result, "48.50.51.48");
}

// Test with version-like values 0.1.0.0
TEST_F(Print0x0000Test_1383, VersionZeroOneZeroZero_1383) {
    auto value = Value::create(unsignedByte);
    value->read("0 1 0 0");
    print0x0000(os, *value, nullptr);
    EXPECT_EQ(os.str(), "0.1.0.0");
}

// Test with all zeros
TEST_F(Print0x0000Test_1383, AllZeros_1383) {
    auto value = Value::create(unsignedByte);
    value->read("0 0 0 0");
    print0x0000(os, *value, nullptr);
    EXPECT_EQ(os.str(), "0.0.0.0");
}

// Test with max byte values (255)
TEST_F(Print0x0000Test_1383, MaxByteValues_1383) {
    auto value = Value::create(unsignedByte);
    value->read("255 255 255 255");
    print0x0000(os, *value, nullptr);
    EXPECT_EQ(os.str(), "255.255.255.255");
}

// Test boundary: wrong size (3 bytes instead of 4) - should fall back to default output
TEST_F(Print0x0000Test_1383, ThreeBytes_FallbackOutput_1383) {
    auto value = Value::create(unsignedByte);
    value->read("1 2 3");
    
    std::ostringstream expectedOs;
    expectedOs << *value;
    
    print0x0000(os, *value, nullptr);
    EXPECT_EQ(os.str(), expectedOs.str());
}

// Test boundary: wrong size (5 bytes instead of 4) - should fall back to default output
TEST_F(Print0x0000Test_1383, FiveBytes_FallbackOutput_1383) {
    auto value = Value::create(unsignedByte);
    value->read("1 2 3 4 5");
    
    std::ostringstream expectedOs;
    expectedOs << *value;
    
    print0x0000(os, *value, nullptr);
    EXPECT_EQ(os.str(), expectedOs.str());
}

// Test boundary: wrong type (unsignedShort instead of unsignedByte) - should fall back
TEST_F(Print0x0000Test_1383, WrongTypeUnsignedShort_FallbackOutput_1383) {
    auto value = Value::create(unsignedShort);
    value->read("1 2 3 4");
    
    std::ostringstream expectedOs;
    expectedOs << *value;
    
    print0x0000(os, *value, nullptr);
    EXPECT_EQ(os.str(), expectedOs.str());
}

// Test boundary: wrong type (unsignedLong) - should fall back
TEST_F(Print0x0000Test_1383, WrongTypeUnsignedLong_FallbackOutput_1383) {
    auto value = Value::create(unsignedLong);
    value->read("1");
    
    std::ostringstream expectedOs;
    expectedOs << *value;
    
    print0x0000(os, *value, nullptr);
    EXPECT_EQ(os.str(), expectedOs.str());
}

// Test with empty value - should fall back
TEST_F(Print0x0000Test_1383, EmptyValue_FallbackOutput_1383) {
    auto value = Value::create(unsignedByte);
    
    std::ostringstream expectedOs;
    expectedOs << *value;
    
    print0x0000(os, *value, nullptr);
    EXPECT_EQ(os.str(), expectedOs.str());
}

// Test with single byte - should fall back
TEST_F(Print0x0000Test_1383, SingleByte_FallbackOutput_1383) {
    auto value = Value::create(unsignedByte);
    value->read("42");
    
    std::ostringstream expectedOs;
    expectedOs << *value;
    
    print0x0000(os, *value, nullptr);
    EXPECT_EQ(os.str(), expectedOs.str());
}

// Test with signedByte type (wrong type) with 4 elements - should fall back
TEST_F(Print0x0000Test_1383, WrongTypeSignedByte_FallbackOutput_1383) {
    auto value = Value::create(signedByte);
    value->read("1 2 3 4");
    
    std::ostringstream expectedOs;
    expectedOs << *value;
    
    print0x0000(os, *value, nullptr);
    EXPECT_EQ(os.str(), expectedOs.str());
}

// Test with ASCII type - should fall back
TEST_F(Print0x0000Test_1383, WrongTypeAscii_FallbackOutput_1383) {
    auto value = Value::create(asciiString);
    value->read("test");
    
    std::ostringstream expectedOs;
    expectedOs << *value;
    
    print0x0000(os, *value, nullptr);
    EXPECT_EQ(os.str(), expectedOs.str());
}

// Test with mixed values
TEST_F(Print0x0000Test_1383, MixedValues_1383) {
    auto value = Value::create(unsignedByte);
    value->read("2 3 1 0");
    print0x0000(os, *value, nullptr);
    EXPECT_EQ(os.str(), "2.3.1.0");
}

// Test that nullptr ExifData is accepted (normal operation)
TEST_F(Print0x0000Test_1383, NullExifDataAccepted_1383) {
    auto value = Value::create(unsignedByte);
    value->read("1 0 0 0");
    print0x0000(os, *value, nullptr);
    EXPECT_EQ(os.str(), "1.0.0.0");
}

// Test return value is the same stream reference
TEST_F(Print0x0000Test_1383, ReturnsSameStream_1383) {
    auto value = Value::create(unsignedByte);
    value->read("1 2 3 4");
    std::ostream& result = print0x0000(os, *value, nullptr);
    EXPECT_EQ(&result, &os);
}

// Test return value is the same stream reference for fallback path
TEST_F(Print0x0000Test_1383, ReturnsSameStreamFallback_1383) {
    auto value = Value::create(unsignedByte);
    value->read("1 2 3");
    std::ostream& result = print0x0000(os, *value, nullptr);
    EXPECT_EQ(&result, &os);
}

// Test with exactly 2 bytes - should fall back
TEST_F(Print0x0000Test_1383, TwoBytes_FallbackOutput_1383) {
    auto value = Value::create(unsignedByte);
    value->read("1 2");
    
    std::ostringstream expectedOs;
    expectedOs << *value;
    
    print0x0000(os, *value, nullptr);
    EXPECT_EQ(os.str(), expectedOs.str());
}
