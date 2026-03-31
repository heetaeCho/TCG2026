#include <gtest/gtest.h>
#include <sstream>
#include <exiv2/exiv2.hpp>

// Forward declaration of the function under test
namespace Exiv2 {
namespace Internal {
std::ostream& printMinoltaSonyLocalAFAreaPoint(std::ostream& os, const Value& value, const ExifData* metadata);
}
}

using namespace Exiv2;
using namespace Exiv2::Internal;

class PrintMinoltaSonyLocalAFAreaPointTest_1030 : public ::testing::Test {
protected:
    std::ostringstream os;
};

// Test: Value 1 should print "Center"
TEST_F(PrintMinoltaSonyLocalAFAreaPointTest_1030, Value1PrintsCenter_1030) {
    auto value = Value::create(unsignedShort);
    value->read("1");
    printMinoltaSonyLocalAFAreaPoint(os, *value, nullptr);
    EXPECT_NE(os.str().find("Center"), std::string::npos);
}

// Test: Value 2 should print "Top"
TEST_F(PrintMinoltaSonyLocalAFAreaPointTest_1030, Value2PrintsTop_1030) {
    auto value = Value::create(unsignedShort);
    value->read("2");
    printMinoltaSonyLocalAFAreaPoint(os, *value, nullptr);
    EXPECT_NE(os.str().find("Top"), std::string::npos);
}

// Test: Value 3 should print "Top-Right"
TEST_F(PrintMinoltaSonyLocalAFAreaPointTest_1030, Value3PrintsTopRight_1030) {
    auto value = Value::create(unsignedShort);
    value->read("3");
    printMinoltaSonyLocalAFAreaPoint(os, *value, nullptr);
    EXPECT_NE(os.str().find("Top-Right"), std::string::npos);
}

// Test: Value 4 should print "Right"
TEST_F(PrintMinoltaSonyLocalAFAreaPointTest_1030, Value4PrintsRight_1030) {
    auto value = Value::create(unsignedShort);
    value->read("4");
    printMinoltaSonyLocalAFAreaPoint(os, *value, nullptr);
    EXPECT_NE(os.str().find("Right"), std::string::npos);
}

// Test: Value 5 should print "Bottom-Right"
TEST_F(PrintMinoltaSonyLocalAFAreaPointTest_1030, Value5PrintsBottomRight_1030) {
    auto value = Value::create(unsignedShort);
    value->read("5");
    printMinoltaSonyLocalAFAreaPoint(os, *value, nullptr);
    EXPECT_NE(os.str().find("Bottom-Right"), std::string::npos);
}

// Test: Value 6 should print "Bottom"
TEST_F(PrintMinoltaSonyLocalAFAreaPointTest_1030, Value6PrintsBottom_1030) {
    auto value = Value::create(unsignedShort);
    value->read("6");
    printMinoltaSonyLocalAFAreaPoint(os, *value, nullptr);
    EXPECT_NE(os.str().find("Bottom"), std::string::npos);
}

// Test: Value 7 should print "Bottom-Left"
TEST_F(PrintMinoltaSonyLocalAFAreaPointTest_1030, Value7PrintsBottomLeft_1030) {
    auto value = Value::create(unsignedShort);
    value->read("7");
    printMinoltaSonyLocalAFAreaPoint(os, *value, nullptr);
    EXPECT_NE(os.str().find("Bottom-Left"), std::string::npos);
}

// Test: Value 8 should print "Left"
TEST_F(PrintMinoltaSonyLocalAFAreaPointTest_1030, Value8PrintsLeft_1030) {
    auto value = Value::create(unsignedShort);
    value->read("8");
    printMinoltaSonyLocalAFAreaPoint(os, *value, nullptr);
    EXPECT_NE(os.str().find("Left"), std::string::npos);
}

// Test: Value 9 should print "Top-Left"
TEST_F(PrintMinoltaSonyLocalAFAreaPointTest_1030, Value9PrintsTopLeft_1030) {
    auto value = Value::create(unsignedShort);
    value->read("9");
    printMinoltaSonyLocalAFAreaPoint(os, *value, nullptr);
    EXPECT_NE(os.str().find("Top-Left"), std::string::npos);
}

// Test: Value 10 should print "Far-Right"
TEST_F(PrintMinoltaSonyLocalAFAreaPointTest_1030, Value10PrintsFarRight_1030) {
    auto value = Value::create(unsignedShort);
    value->read("10");
    printMinoltaSonyLocalAFAreaPoint(os, *value, nullptr);
    EXPECT_NE(os.str().find("Far-Right"), std::string::npos);
}

// Test: Value 11 should print "Far-Left"
TEST_F(PrintMinoltaSonyLocalAFAreaPointTest_1030, Value11PrintsFarLeft_1030) {
    auto value = Value::create(unsignedShort);
    value->read("11");
    printMinoltaSonyLocalAFAreaPoint(os, *value, nullptr);
    EXPECT_NE(os.str().find("Far-Left"), std::string::npos);
}

// Test: Unknown value (0) - boundary below valid range
TEST_F(PrintMinoltaSonyLocalAFAreaPointTest_1030, Value0PrintsUnknown_1030) {
    auto value = Value::create(unsignedShort);
    value->read("0");
    printMinoltaSonyLocalAFAreaPoint(os, *value, nullptr);
    std::string result = os.str();
    // Should not contain any of the known tag names - should print the numeric value or "(0)"
    EXPECT_EQ(result.find("Center"), std::string::npos);
    EXPECT_EQ(result.find("Top-Right"), std::string::npos);
    EXPECT_FALSE(result.empty());
}

// Test: Unknown value (12) - boundary above valid range
TEST_F(PrintMinoltaSonyLocalAFAreaPointTest_1030, Value12PrintsUnknown_1030) {
    auto value = Value::create(unsignedShort);
    value->read("12");
    printMinoltaSonyLocalAFAreaPoint(os, *value, nullptr);
    std::string result = os.str();
    EXPECT_EQ(result.find("Far-Left"), std::string::npos);
    EXPECT_EQ(result.find("Far-Right"), std::string::npos);
    EXPECT_FALSE(result.empty());
}

// Test: Large unknown value
TEST_F(PrintMinoltaSonyLocalAFAreaPointTest_1030, LargeValuePrintsUnknown_1030) {
    auto value = Value::create(unsignedShort);
    value->read("999");
    printMinoltaSonyLocalAFAreaPoint(os, *value, nullptr);
    std::string result = os.str();
    EXPECT_FALSE(result.empty());
}

// Test: Function returns the same ostream reference
TEST_F(PrintMinoltaSonyLocalAFAreaPointTest_1030, ReturnsSameOstream_1030) {
    auto value = Value::create(unsignedShort);
    value->read("1");
    std::ostream& returned = printMinoltaSonyLocalAFAreaPoint(os, *value, nullptr);
    EXPECT_EQ(&returned, &os);
}

// Test: With non-null ExifData pointer (should still work)
TEST_F(PrintMinoltaSonyLocalAFAreaPointTest_1030, WorksWithNonNullMetadata_1030) {
    ExifData exifData;
    auto value = Value::create(unsignedShort);
    value->read("1");
    printMinoltaSonyLocalAFAreaPoint(os, *value, &exifData);
    EXPECT_NE(os.str().find("Center"), std::string::npos);
}

// Test: Using signedLong type value
TEST_F(PrintMinoltaSonyLocalAFAreaPointTest_1030, WorksWithSignedLongValue_1030) {
    auto value = Value::create(signedLong);
    value->read("6");
    printMinoltaSonyLocalAFAreaPoint(os, *value, nullptr);
    EXPECT_NE(os.str().find("Bottom"), std::string::npos);
}

// Test: Negative value should be unknown
TEST_F(PrintMinoltaSonyLocalAFAreaPointTest_1030, NegativeValuePrintsUnknown_1030) {
    auto value = Value::create(signedShort);
    value->read("-1");
    printMinoltaSonyLocalAFAreaPoint(os, *value, nullptr);
    std::string result = os.str();
    EXPECT_FALSE(result.empty());
    // Should not match any known label
    EXPECT_EQ(result.find("Center"), std::string::npos);
}
