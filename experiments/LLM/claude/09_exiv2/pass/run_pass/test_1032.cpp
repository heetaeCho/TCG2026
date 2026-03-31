#include <gtest/gtest.h>
#include <exiv2/exiv2.hpp>
#include <sstream>

// Forward declaration of the function under test
namespace Exiv2 {
namespace Internal {
std::ostream& printMinoltaSonyPrioritySetupShutterRelease(std::ostream& os, const Value& value, const ExifData* metadata);
}
}

using namespace Exiv2;
using namespace Exiv2::Internal;

class PrintMinoltaSonyPrioritySetupShutterReleaseTest_1032 : public ::testing::Test {
protected:
    std::ostringstream oss;
};

// Test normal case: value 0 should print "AF"
TEST_F(PrintMinoltaSonyPrioritySetupShutterReleaseTest_1032, Value0PrintsAF_1032) {
    auto value = Value::create(unsignedShort);
    value->read("0");
    printMinoltaSonyPrioritySetupShutterRelease(oss, *value, nullptr);
    EXPECT_NE(oss.str().find("AF"), std::string::npos);
}

// Test normal case: value 1 should print "Release"
TEST_F(PrintMinoltaSonyPrioritySetupShutterReleaseTest_1032, Value1PrintsRelease_1032) {
    auto value = Value::create(unsignedShort);
    value->read("1");
    printMinoltaSonyPrioritySetupShutterRelease(oss, *value, nullptr);
    EXPECT_NE(oss.str().find("Release"), std::string::npos);
}

// Test boundary/error case: value 2 (out of range) should print something (likely the numeric value)
TEST_F(PrintMinoltaSonyPrioritySetupShutterReleaseTest_1032, Value2OutOfRange_1032) {
    auto value = Value::create(unsignedShort);
    value->read("2");
    printMinoltaSonyPrioritySetupShutterRelease(oss, *value, nullptr);
    std::string result = oss.str();
    // Should not be empty; unknown values typically print the number
    EXPECT_FALSE(result.empty());
}

// Test boundary/error case: negative value (out of range)
TEST_F(PrintMinoltaSonyPrioritySetupShutterReleaseTest_1032, NegativeValueOutOfRange_1032) {
    auto value = Value::create(signedShort);
    value->read("-1");
    printMinoltaSonyPrioritySetupShutterRelease(oss, *value, nullptr);
    std::string result = oss.str();
    EXPECT_FALSE(result.empty());
}

// Test that the function returns the same ostream reference
TEST_F(PrintMinoltaSonyPrioritySetupShutterReleaseTest_1032, ReturnsSameOstream_1032) {
    auto value = Value::create(unsignedShort);
    value->read("0");
    std::ostream& returned = printMinoltaSonyPrioritySetupShutterRelease(oss, *value, nullptr);
    EXPECT_EQ(&returned, &oss);
}

// Test with ExifData pointer being non-null (should still work)
TEST_F(PrintMinoltaSonyPrioritySetupShutterReleaseTest_1032, WithNonNullExifData_1032) {
    ExifData exifData;
    auto value = Value::create(unsignedShort);
    value->read("0");
    printMinoltaSonyPrioritySetupShutterRelease(oss, *value, &exifData);
    EXPECT_NE(oss.str().find("AF"), std::string::npos);
}

// Test with ExifData pointer being non-null and value 1
TEST_F(PrintMinoltaSonyPrioritySetupShutterReleaseTest_1032, WithNonNullExifDataValue1_1032) {
    ExifData exifData;
    auto value = Value::create(unsignedShort);
    value->read("1");
    printMinoltaSonyPrioritySetupShutterRelease(oss, *value, &exifData);
    EXPECT_NE(oss.str().find("Release"), std::string::npos);
}

// Test with a large out-of-range value
TEST_F(PrintMinoltaSonyPrioritySetupShutterReleaseTest_1032, LargeValueOutOfRange_1032) {
    auto value = Value::create(unsignedShort);
    value->read("65535");
    printMinoltaSonyPrioritySetupShutterRelease(oss, *value, nullptr);
    std::string result = oss.str();
    EXPECT_FALSE(result.empty());
    // Should not contain known tag descriptions for out of range
    EXPECT_EQ(result.find("AF"), std::string::npos);
    EXPECT_EQ(result.find("Release"), std::string::npos);
}

// Test with unsigned long type value
TEST_F(PrintMinoltaSonyPrioritySetupShutterReleaseTest_1032, UnsignedLongValue0_1032) {
    auto value = Value::create(unsignedLong);
    value->read("0");
    printMinoltaSonyPrioritySetupShutterRelease(oss, *value, nullptr);
    std::string result = oss.str();
    EXPECT_FALSE(result.empty());
}

// Test that value 0 does NOT print "Release"
TEST_F(PrintMinoltaSonyPrioritySetupShutterReleaseTest_1032, Value0DoesNotPrintRelease_1032) {
    auto value = Value::create(unsignedShort);
    value->read("0");
    printMinoltaSonyPrioritySetupShutterRelease(oss, *value, nullptr);
    EXPECT_EQ(oss.str().find("Release"), std::string::npos);
}

// Test that value 1 does NOT print "AF" as a standalone match
TEST_F(PrintMinoltaSonyPrioritySetupShutterReleaseTest_1032, Value1DoesNotPrintAFOnly_1032) {
    auto value = Value::create(unsignedShort);
    value->read("1");
    printMinoltaSonyPrioritySetupShutterRelease(oss, *value, nullptr);
    std::string result = oss.str();
    // "Release" should be present, not just "AF"
    EXPECT_NE(result.find("Release"), std::string::npos);
}
