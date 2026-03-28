#include <gtest/gtest.h>
#include <sstream>
#include <exiv2/exiv2.hpp>

// We need access to the internal function and tag details
namespace Exiv2 {
namespace Internal {
std::ostream& print0xa300(std::ostream& os, const Value& value, const ExifData* metadata);
}
}

class Print0xa300Test_1409 : public ::testing::Test {
protected:
    std::ostringstream os;
};

// Test with value 1 - should print "Film scanner"
TEST_F(Print0xa300Test_1409, ValueOne_PrintsFilmScanner_1409) {
    auto value = Exiv2::Value::create(Exiv2::unsignedShort);
    value->read("1");
    Exiv2::Internal::print0xa300(os, *value, nullptr);
    EXPECT_NE(std::string::npos, os.str().find("Film scanner"));
}

// Test with value 2 - should print "Reflexion print scanner"
TEST_F(Print0xa300Test_1409, ValueTwo_PrintsReflexionPrintScanner_1409) {
    auto value = Exiv2::Value::create(Exiv2::unsignedShort);
    value->read("2");
    Exiv2::Internal::print0xa300(os, *value, nullptr);
    EXPECT_NE(std::string::npos, os.str().find("Reflexion print scanner"));
}

// Test with value 3 - should print "Digital still camera"
TEST_F(Print0xa300Test_1409, ValueThree_PrintsDigitalStillCamera_1409) {
    auto value = Exiv2::Value::create(Exiv2::unsignedShort);
    value->read("3");
    Exiv2::Internal::print0xa300(os, *value, nullptr);
    EXPECT_NE(std::string::npos, os.str().find("Digital still camera"));
}

// Test with unknown value (0) - should produce some output (likely unknown/number)
TEST_F(Print0xa300Test_1409, ValueZero_PrintsUnknownOrValue_1409) {
    auto value = Exiv2::Value::create(Exiv2::unsignedShort);
    value->read("0");
    Exiv2::Internal::print0xa300(os, *value, nullptr);
    std::string result = os.str();
    // Should produce some output, not be empty
    EXPECT_FALSE(result.empty());
    // Should NOT match any known tag
    EXPECT_EQ(std::string::npos, result.find("Film scanner"));
    EXPECT_EQ(std::string::npos, result.find("Reflexion print scanner"));
    EXPECT_EQ(std::string::npos, result.find("Digital still camera"));
}

// Test with out of range value (4) - should produce some output (likely unknown/number)
TEST_F(Print0xa300Test_1409, ValueFour_PrintsUnknownOrValue_1409) {
    auto value = Exiv2::Value::create(Exiv2::unsignedShort);
    value->read("4");
    Exiv2::Internal::print0xa300(os, *value, nullptr);
    std::string result = os.str();
    EXPECT_FALSE(result.empty());
    EXPECT_EQ(std::string::npos, result.find("Film scanner"));
    EXPECT_EQ(std::string::npos, result.find("Reflexion print scanner"));
    EXPECT_EQ(std::string::npos, result.find("Digital still camera"));
}

// Test with large out of range value
TEST_F(Print0xa300Test_1409, LargeValue_PrintsUnknownOrValue_1409) {
    auto value = Exiv2::Value::create(Exiv2::unsignedShort);
    value->read("999");
    Exiv2::Internal::print0xa300(os, *value, nullptr);
    std::string result = os.str();
    EXPECT_FALSE(result.empty());
}

// Test with nullptr metadata - should still work for valid values
TEST_F(Print0xa300Test_1409, NullMetadata_StillWorks_1409) {
    auto value = Exiv2::Value::create(Exiv2::unsignedShort);
    value->read("3");
    Exiv2::Internal::print0xa300(os, *value, nullptr);
    EXPECT_NE(std::string::npos, os.str().find("Digital still camera"));
}

// Test with ExifData metadata - should still work for valid values
TEST_F(Print0xa300Test_1409, WithExifDataMetadata_StillWorks_1409) {
    Exiv2::ExifData exifData;
    auto value = Exiv2::Value::create(Exiv2::unsignedShort);
    value->read("1");
    Exiv2::Internal::print0xa300(os, *value, &exifData);
    EXPECT_NE(std::string::npos, os.str().find("Film scanner"));
}

// Test that the function returns a reference to the same stream
TEST_F(Print0xa300Test_1409, ReturnsReferenceToSameStream_1409) {
    auto value = Exiv2::Value::create(Exiv2::unsignedShort);
    value->read("3");
    std::ostream& result = Exiv2::Internal::print0xa300(os, *value, nullptr);
    EXPECT_EQ(&os, &result);
}

// Test with negative value
TEST_F(Print0xa300Test_1409, NegativeValue_ProducesSomeOutput_1409) {
    auto value = Exiv2::Value::create(Exiv2::signedShort);
    value->read("-1");
    Exiv2::Internal::print0xa300(os, *value, nullptr);
    std::string result = os.str();
    EXPECT_FALSE(result.empty());
}

// Test with unsigned long type value
TEST_F(Print0xa300Test_1409, UnsignedLongType_ValueThree_1409) {
    auto value = Exiv2::Value::create(Exiv2::unsignedLong);
    value->read("3");
    Exiv2::Internal::print0xa300(os, *value, nullptr);
    EXPECT_NE(std::string::npos, os.str().find("Digital still camera"));
}
