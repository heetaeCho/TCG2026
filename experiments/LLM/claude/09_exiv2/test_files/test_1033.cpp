#include <gtest/gtest.h>
#include <sstream>
#include <exiv2/exiv2.hpp>

// Forward declaration of the function under test
namespace Exiv2 {
namespace Internal {
std::ostream& printMinoltaSonyQualityCs(std::ostream& os, const Value& value, const ExifData* metadata);
}
}

class PrintMinoltaSonyQualityCsTest_1033 : public ::testing::Test {
protected:
    std::ostringstream os;
};

// Test RAW quality (value 0)
TEST_F(PrintMinoltaSonyQualityCsTest_1033, QualityRAW_1033) {
    Exiv2::Value::UniquePtr value = Exiv2::Value::create(Exiv2::unsignedShort);
    value->read("0");
    Exiv2::Internal::printMinoltaSonyQualityCs(os, *value, nullptr);
    EXPECT_EQ(os.str(), "RAW");
}

// Test CRAW quality (value 2)
TEST_F(PrintMinoltaSonyQualityCsTest_1033, QualityCRAW_1033) {
    Exiv2::Value::UniquePtr value = Exiv2::Value::create(Exiv2::unsignedShort);
    value->read("2");
    Exiv2::Internal::printMinoltaSonyQualityCs(os, *value, nullptr);
    EXPECT_EQ(os.str(), "CRAW");
}

// Test Extra Fine quality (value 16)
TEST_F(PrintMinoltaSonyQualityCsTest_1033, QualityExtraFine_1033) {
    Exiv2::Value::UniquePtr value = Exiv2::Value::create(Exiv2::unsignedShort);
    value->read("16");
    Exiv2::Internal::printMinoltaSonyQualityCs(os, *value, nullptr);
    EXPECT_EQ(os.str(), "Extra Fine");
}

// Test Fine quality (value 32)
TEST_F(PrintMinoltaSonyQualityCsTest_1033, QualityFine_1033) {
    Exiv2::Value::UniquePtr value = Exiv2::Value::create(Exiv2::unsignedShort);
    value->read("32");
    Exiv2::Internal::printMinoltaSonyQualityCs(os, *value, nullptr);
    EXPECT_EQ(os.str(), "Fine");
}

// Test RAW+JPEG quality (value 34)
TEST_F(PrintMinoltaSonyQualityCsTest_1033, QualityRAWPlusJPEG_1033) {
    Exiv2::Value::UniquePtr value = Exiv2::Value::create(Exiv2::unsignedShort);
    value->read("34");
    Exiv2::Internal::printMinoltaSonyQualityCs(os, *value, nullptr);
    EXPECT_EQ(os.str(), "RAW+JPEG");
}

// Test CRAW+JPEG quality (value 35)
TEST_F(PrintMinoltaSonyQualityCsTest_1033, QualityCRAWPlusJPEG_1033) {
    Exiv2::Value::UniquePtr value = Exiv2::Value::create(Exiv2::unsignedShort);
    value->read("35");
    Exiv2::Internal::printMinoltaSonyQualityCs(os, *value, nullptr);
    EXPECT_EQ(os.str(), "CRAW+JPEG");
}

// Test Standard quality (value 48)
TEST_F(PrintMinoltaSonyQualityCsTest_1033, QualityStandard_1033) {
    Exiv2::Value::UniquePtr value = Exiv2::Value::create(Exiv2::unsignedShort);
    value->read("48");
    Exiv2::Internal::printMinoltaSonyQualityCs(os, *value, nullptr);
    EXPECT_EQ(os.str(), "Standard");
}

// Test unknown/unmapped value (value 1 is not in the table)
TEST_F(PrintMinoltaSonyQualityCsTest_1033, QualityUnknownValue1_1033) {
    Exiv2::Value::UniquePtr value = Exiv2::Value::create(Exiv2::unsignedShort);
    value->read("1");
    Exiv2::Internal::printMinoltaSonyQualityCs(os, *value, nullptr);
    // Unknown values typically print as "(1)"
    EXPECT_EQ(os.str(), "(1)");
}

// Test another unknown value (value 99)
TEST_F(PrintMinoltaSonyQualityCsTest_1033, QualityUnknownValue99_1033) {
    Exiv2::Value::UniquePtr value = Exiv2::Value::create(Exiv2::unsignedShort);
    value->read("99");
    Exiv2::Internal::printMinoltaSonyQualityCs(os, *value, nullptr);
    EXPECT_EQ(os.str(), "(99)");
}

// Test with a negative unknown value
TEST_F(PrintMinoltaSonyQualityCsTest_1033, QualityUnknownNegativeValue_1033) {
    Exiv2::Value::UniquePtr value = Exiv2::Value::create(Exiv2::signedShort);
    value->read("-1");
    Exiv2::Internal::printMinoltaSonyQualityCs(os, *value, nullptr);
    // Should print as unknown
    std::string result = os.str();
    EXPECT_FALSE(result.empty());
}

// Test with large unknown value (value 255)
TEST_F(PrintMinoltaSonyQualityCsTest_1033, QualityUnknownLargeValue_1033) {
    Exiv2::Value::UniquePtr value = Exiv2::Value::create(Exiv2::unsignedShort);
    value->read("255");
    Exiv2::Internal::printMinoltaSonyQualityCs(os, *value, nullptr);
    EXPECT_EQ(os.str(), "(255)");
}

// Test with ExifData pointer (non-null but empty)
TEST_F(PrintMinoltaSonyQualityCsTest_1033, QualityWithExifData_1033) {
    Exiv2::ExifData exifData;
    Exiv2::Value::UniquePtr value = Exiv2::Value::create(Exiv2::unsignedShort);
    value->read("32");
    Exiv2::Internal::printMinoltaSonyQualityCs(os, *value, &exifData);
    EXPECT_EQ(os.str(), "Fine");
}

// Test that the function returns the same ostream reference
TEST_F(PrintMinoltaSonyQualityCsTest_1033, ReturnsOstreamReference_1033) {
    Exiv2::Value::UniquePtr value = Exiv2::Value::create(Exiv2::unsignedShort);
    value->read("0");
    std::ostream& result = Exiv2::Internal::printMinoltaSonyQualityCs(os, *value, nullptr);
    EXPECT_EQ(&result, &os);
}

// Test boundary: value just below a known tag (value 15, just before 16)
TEST_F(PrintMinoltaSonyQualityCsTest_1033, QualityBoundaryBelow16_1033) {
    Exiv2::Value::UniquePtr value = Exiv2::Value::create(Exiv2::unsignedShort);
    value->read("15");
    Exiv2::Internal::printMinoltaSonyQualityCs(os, *value, nullptr);
    EXPECT_EQ(os.str(), "(15)");
}

// Test boundary: value just above a known tag (value 33, between 32 and 34)
TEST_F(PrintMinoltaSonyQualityCsTest_1033, QualityBoundaryBetween32And34_1033) {
    Exiv2::Value::UniquePtr value = Exiv2::Value::create(Exiv2::unsignedShort);
    value->read("33");
    Exiv2::Internal::printMinoltaSonyQualityCs(os, *value, nullptr);
    EXPECT_EQ(os.str(), "(33)");
}

// Test boundary: value just above last known tag (value 49)
TEST_F(PrintMinoltaSonyQualityCsTest_1033, QualityBoundaryAbove48_1033) {
    Exiv2::Value::UniquePtr value = Exiv2::Value::create(Exiv2::unsignedShort);
    value->read("49");
    Exiv2::Internal::printMinoltaSonyQualityCs(os, *value, nullptr);
    EXPECT_EQ(os.str(), "(49)");
}

// Test with unsignedLong type value
TEST_F(PrintMinoltaSonyQualityCsTest_1033, QualityWithUnsignedLongType_1033) {
    Exiv2::Value::UniquePtr value = Exiv2::Value::create(Exiv2::unsignedLong);
    value->read("48");
    Exiv2::Internal::printMinoltaSonyQualityCs(os, *value, nullptr);
    EXPECT_EQ(os.str(), "Standard");
}
