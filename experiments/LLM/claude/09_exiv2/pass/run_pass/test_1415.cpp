#include <gtest/gtest.h>
#include <sstream>
#include <exiv2/value.hpp>
#include <exiv2/exif.hpp>

// Declaration of the function under test
namespace Exiv2 {
namespace Internal {
std::ostream& print0xa405(std::ostream& os, const Value& value, const ExifData*);
}
}

using namespace Exiv2;
using namespace Exiv2::Internal;

class Print0xa405Test_1415 : public ::testing::Test {
protected:
    std::ostringstream os;
};

// Test normal positive integer value
TEST_F(Print0xa405Test_1415, PositiveIntegerValue_1415) {
    auto value = Value::create(unsignedShort);
    value->read("50");
    print0xa405(os, *value, nullptr);
    EXPECT_EQ(os.str(), "50.0 mm");
}

// Test zero value outputs "Unknown"
TEST_F(Print0xa405Test_1415, ZeroValueOutputsUnknown_1415) {
    auto value = Value::create(unsignedShort);
    value->read("0");
    print0xa405(os, *value, nullptr);
    EXPECT_EQ(os.str(), "Unknown");
}

// Test value of 1
TEST_F(Print0xa405Test_1415, ValueOfOne_1415) {
    auto value = Value::create(unsignedShort);
    value->read("1");
    print0xa405(os, *value, nullptr);
    EXPECT_EQ(os.str(), "1.0 mm");
}

// Test large value
TEST_F(Print0xa405Test_1415, LargeValue_1415) {
    auto value = Value::create(unsignedShort);
    value->read("65535");
    print0xa405(os, *value, nullptr);
    EXPECT_EQ(os.str(), "65535.0 mm");
}

// Test with signed long value type
TEST_F(Print0xa405Test_1415, SignedLongPositiveValue_1415) {
    auto value = Value::create(signedLong);
    value->read("200");
    print0xa405(os, *value, nullptr);
    EXPECT_EQ(os.str(), "200.0 mm");
}

// Test with signed long negative value (non-zero, should output with mm)
TEST_F(Print0xa405Test_1415, SignedLongNegativeValue_1415) {
    auto value = Value::create(signedLong);
    value->read("-50");
    print0xa405(os, *value, nullptr);
    EXPECT_EQ(os.str(), "-50.0 mm");
}

// Test with nullptr ExifData (should work fine)
TEST_F(Print0xa405Test_1415, NullExifDataPointer_1415) {
    auto value = Value::create(unsignedShort);
    value->read("100");
    print0xa405(os, *value, nullptr);
    EXPECT_EQ(os.str(), "100.0 mm");
}

// Test with ExifData pointer (non-null, should still work)
TEST_F(Print0xa405Test_1415, NonNullExifDataPointer_1415) {
    ExifData exifData;
    auto value = Value::create(unsignedShort);
    value->read("85");
    print0xa405(os, *value, &exifData);
    EXPECT_EQ(os.str(), "85.0 mm");
}

// Test that the function returns reference to the same ostream
TEST_F(Print0xa405Test_1415, ReturnsOstreamReference_1415) {
    auto value = Value::create(unsignedShort);
    value->read("50");
    std::ostream& result = print0xa405(os, *value, nullptr);
    EXPECT_EQ(&result, &os);
}

// Test that the function returns ostream reference for zero value too
TEST_F(Print0xa405Test_1415, ReturnsOstreamReferenceForZero_1415) {
    auto value = Value::create(unsignedShort);
    value->read("0");
    std::ostream& result = print0xa405(os, *value, nullptr);
    EXPECT_EQ(&result, &os);
}

// Test with unsigned long type
TEST_F(Print0xa405Test_1415, UnsignedLongValue_1415) {
    auto value = Value::create(unsignedLong);
    value->read("300");
    print0xa405(os, *value, nullptr);
    EXPECT_EQ(os.str(), "300.0 mm");
}

// Test typical focal length equivalent value (e.g., 35mm equivalent)
TEST_F(Print0xa405Test_1415, TypicalFocalLength35mm_1415) {
    auto value = Value::create(unsignedShort);
    value->read("35");
    print0xa405(os, *value, nullptr);
    EXPECT_EQ(os.str(), "35.0 mm");
}

// Test value of 2
TEST_F(Print0xa405Test_1415, SmallNonZeroValue_1415) {
    auto value = Value::create(unsignedShort);
    value->read("2");
    print0xa405(os, *value, nullptr);
    EXPECT_EQ(os.str(), "2.0 mm");
}
