#include <gtest/gtest.h>
#include <sstream>
#include <exiv2/exiv2.hpp>

// Forward declaration of the function under test
namespace Exiv2 {
namespace Internal {
std::ostream& printNormalSoftHard(std::ostream& os, const Value& value, const ExifData* metadata);
}
}

using namespace Exiv2;
using namespace Exiv2::Internal;

class PrintNormalSoftHardTest_1421 : public ::testing::Test {
protected:
    std::ostringstream os;
};

// Test normal case: value 0 should print "Normal"
TEST_F(PrintNormalSoftHardTest_1421, ValueZeroPrintsNormal_1421) {
    auto value = Value::create(unsignedShort);
    value->read("0");
    printNormalSoftHard(os, *value, nullptr);
    EXPECT_NE(os.str().find("Normal"), std::string::npos);
}

// Test normal case: value 1 should print "Soft"
TEST_F(PrintNormalSoftHardTest_1421, ValueOnePrintsSoft_1421) {
    auto value = Value::create(unsignedShort);
    value->read("1");
    printNormalSoftHard(os, *value, nullptr);
    EXPECT_NE(os.str().find("Soft"), std::string::npos);
}

// Test normal case: value 2 should print "Hard"
TEST_F(PrintNormalSoftHardTest_1421, ValueTwoPrintsHard_1421) {
    auto value = Value::create(unsignedShort);
    value->read("2");
    printNormalSoftHard(os, *value, nullptr);
    EXPECT_NE(os.str().find("Hard"), std::string::npos);
}

// Test boundary/error case: value 3 (out of range) should not print Normal, Soft, or Hard
TEST_F(PrintNormalSoftHardTest_1421, ValueThreeOutOfRange_1421) {
    auto value = Value::create(unsignedShort);
    value->read("3");
    printNormalSoftHard(os, *value, nullptr);
    std::string result = os.str();
    // Out of range values typically print the numeric value or "(n)"
    EXPECT_EQ(result.find("Normal"), std::string::npos);
    EXPECT_EQ(result.find("Soft"), std::string::npos);
    EXPECT_EQ(result.find("Hard"), std::string::npos);
}

// Test boundary/error case: negative value (if using signed type)
TEST_F(PrintNormalSoftHardTest_1421, NegativeValueOutOfRange_1421) {
    auto value = Value::create(signedShort);
    value->read("-1");
    printNormalSoftHard(os, *value, nullptr);
    std::string result = os.str();
    EXPECT_EQ(result.find("Normal"), std::string::npos);
    EXPECT_EQ(result.find("Soft"), std::string::npos);
    EXPECT_EQ(result.find("Hard"), std::string::npos);
}

// Test that the function returns a reference to the same ostream
TEST_F(PrintNormalSoftHardTest_1421, ReturnsSameOstream_1421) {
    auto value = Value::create(unsignedShort);
    value->read("0");
    std::ostream& returned = printNormalSoftHard(os, *value, nullptr);
    EXPECT_EQ(&returned, &os);
}

// Test with a large out-of-range value
TEST_F(PrintNormalSoftHardTest_1421, LargeValueOutOfRange_1421) {
    auto value = Value::create(unsignedShort);
    value->read("65535");
    printNormalSoftHard(os, *value, nullptr);
    std::string result = os.str();
    EXPECT_EQ(result.find("Normal"), std::string::npos);
    EXPECT_EQ(result.find("Soft"), std::string::npos);
    EXPECT_EQ(result.find("Hard"), std::string::npos);
}

// Test with ExifData pointer provided (non-null but empty)
TEST_F(PrintNormalSoftHardTest_1421, WithEmptyExifData_1421) {
    ExifData exifData;
    auto value = Value::create(unsignedShort);
    value->read("1");
    printNormalSoftHard(os, *value, &exifData);
    EXPECT_NE(os.str().find("Soft"), std::string::npos);
}

// Test with unsignedLong type value
TEST_F(PrintNormalSoftHardTest_1421, UnsignedLongValue_1421) {
    auto value = Value::create(unsignedLong);
    value->read("2");
    printNormalSoftHard(os, *value, nullptr);
    EXPECT_NE(os.str().find("Hard"), std::string::npos);
}

// Test that output stream is not empty after call
TEST_F(PrintNormalSoftHardTest_1421, OutputNotEmpty_1421) {
    auto value = Value::create(unsignedShort);
    value->read("0");
    printNormalSoftHard(os, *value, nullptr);
    EXPECT_FALSE(os.str().empty());
}

// Test exact match for "Normal" output with value 0
TEST_F(PrintNormalSoftHardTest_1421, ExactNormalOutput_1421) {
    auto value = Value::create(unsignedShort);
    value->read("0");
    printNormalSoftHard(os, *value, nullptr);
    EXPECT_EQ(os.str(), "Normal");
}

// Test exact match for "Soft" output with value 1
TEST_F(PrintNormalSoftHardTest_1421, ExactSoftOutput_1421) {
    auto value = Value::create(unsignedShort);
    value->read("1");
    printNormalSoftHard(os, *value, nullptr);
    EXPECT_EQ(os.str(), "Soft");
}

// Test exact match for "Hard" output with value 2
TEST_F(PrintNormalSoftHardTest_1421, ExactHardOutput_1421) {
    auto value = Value::create(unsignedShort);
    value->read("2");
    printNormalSoftHard(os, *value, nullptr);
    EXPECT_EQ(os.str(), "Hard");
}
