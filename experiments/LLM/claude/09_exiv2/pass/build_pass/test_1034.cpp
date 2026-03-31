#include <gtest/gtest.h>
#include <sstream>
#include <exiv2/exiv2.hpp>

// Forward declare the function we're testing
namespace Exiv2 {
namespace Internal {
std::ostream& printMinoltaSonyRotation(std::ostream& os, const Value& value, const ExifData* metadata);
}
}

using namespace Exiv2;
using namespace Exiv2::Internal;

class PrintMinoltaSonyRotationTest_1034 : public ::testing::Test {
protected:
    std::ostringstream os;
};

// Test normal case: value 0 should print "Horizontal (normal)"
TEST_F(PrintMinoltaSonyRotationTest_1034, Value0_HorizontalNormal_1034) {
    auto value = Value::create(unsignedShort);
    value->read("0");
    printMinoltaSonyRotation(os, *value, nullptr);
    EXPECT_EQ(os.str(), "Horizontal (normal)");
}

// Test normal case: value 1 should print "Rotate 90 CW"
TEST_F(PrintMinoltaSonyRotationTest_1034, Value1_Rotate90CW_1034) {
    auto value = Value::create(unsignedShort);
    value->read("1");
    printMinoltaSonyRotation(os, *value, nullptr);
    EXPECT_EQ(os.str(), "Rotate 90 CW");
}

// Test normal case: value 2 should print "Rotate 270 CW"
TEST_F(PrintMinoltaSonyRotationTest_1034, Value2_Rotate270CW_1034) {
    auto value = Value::create(unsignedShort);
    value->read("2");
    printMinoltaSonyRotation(os, *value, nullptr);
    EXPECT_EQ(os.str(), "Rotate 270 CW");
}

// Test boundary/error case: value 3 (out of range) should print the numeric value
TEST_F(PrintMinoltaSonyRotationTest_1034, Value3_OutOfRange_1034) {
    auto value = Value::create(unsignedShort);
    value->read("3");
    printMinoltaSonyRotation(os, *value, nullptr);
    // Out-of-range values typically print as "(n)"
    std::string result = os.str();
    EXPECT_FALSE(result.empty());
    // Should not match any known tag description
    EXPECT_NE(result, "Horizontal (normal)");
    EXPECT_NE(result, "Rotate 90 CW");
    EXPECT_NE(result, "Rotate 270 CW");
}

// Test boundary/error case: large value out of range
TEST_F(PrintMinoltaSonyRotationTest_1034, LargeValue_OutOfRange_1034) {
    auto value = Value::create(unsignedShort);
    value->read("999");
    printMinoltaSonyRotation(os, *value, nullptr);
    std::string result = os.str();
    EXPECT_FALSE(result.empty());
    EXPECT_NE(result, "Horizontal (normal)");
    EXPECT_NE(result, "Rotate 90 CW");
    EXPECT_NE(result, "Rotate 270 CW");
}

// Test with ExifData pointer (non-null but empty)
TEST_F(PrintMinoltaSonyRotationTest_1034, WithEmptyExifData_1034) {
    ExifData exifData;
    auto value = Value::create(unsignedShort);
    value->read("0");
    printMinoltaSonyRotation(os, *value, &exifData);
    EXPECT_EQ(os.str(), "Horizontal (normal)");
}

// Test with nullptr metadata
TEST_F(PrintMinoltaSonyRotationTest_1034, NullMetadata_1034) {
    auto value = Value::create(unsignedShort);
    value->read("1");
    printMinoltaSonyRotation(os, *value, nullptr);
    EXPECT_EQ(os.str(), "Rotate 90 CW");
}

// Test return value is the same stream
TEST_F(PrintMinoltaSonyRotationTest_1034, ReturnsOstream_1034) {
    auto value = Value::create(unsignedShort);
    value->read("0");
    std::ostream& result = printMinoltaSonyRotation(os, *value, nullptr);
    EXPECT_EQ(&result, &os);
}

// Test with signed long value type
TEST_F(PrintMinoltaSonyRotationTest_1034, SignedLongValue_1034) {
    auto value = Value::create(signedLong);
    value->read("2");
    printMinoltaSonyRotation(os, *value, nullptr);
    EXPECT_EQ(os.str(), "Rotate 270 CW");
}

// Test chaining output after the function call
TEST_F(PrintMinoltaSonyRotationTest_1034, ChainingOutput_1034) {
    auto value = Value::create(unsignedShort);
    value->read("0");
    printMinoltaSonyRotation(os, *value, nullptr) << " extra";
    EXPECT_EQ(os.str(), "Horizontal (normal) extra");
}
