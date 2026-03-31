#include <gtest/gtest.h>
#include <sstream>
#include <exiv2/exiv2.hpp>

// We need access to the internal function and tag details
namespace Exiv2 {
namespace Internal {
std::ostream& print0xa406(std::ostream& os, const Value& value, const ExifData* metadata);
}
}

class Print0xa406Test_1416 : public ::testing::Test {
protected:
    std::ostringstream os;
};

// Test Standard scene capture type (value 0)
TEST_F(Print0xa406Test_1416, StandardSceneCaptureType_1416) {
    auto value = Exiv2::Value::create(Exiv2::unsignedShort);
    value->read("0");
    Exiv2::Internal::print0xa406(os, *value, nullptr);
    EXPECT_EQ(os.str(), "Standard");
}

// Test Landscape scene capture type (value 1)
TEST_F(Print0xa406Test_1416, LandscapeSceneCaptureType_1416) {
    auto value = Exiv2::Value::create(Exiv2::unsignedShort);
    value->read("1");
    Exiv2::Internal::print0xa406(os, *value, nullptr);
    EXPECT_EQ(os.str(), "Landscape");
}

// Test Portrait scene capture type (value 2)
TEST_F(Print0xa406Test_1416, PortraitSceneCaptureType_1416) {
    auto value = Exiv2::Value::create(Exiv2::unsignedShort);
    value->read("2");
    Exiv2::Internal::print0xa406(os, *value, nullptr);
    EXPECT_EQ(os.str(), "Portrait");
}

// Test Night scene capture type (value 3)
TEST_F(Print0xa406Test_1416, NightSceneSceneCaptureType_1416) {
    auto value = Exiv2::Value::create(Exiv2::unsignedShort);
    value->read("3");
    Exiv2::Internal::print0xa406(os, *value, nullptr);
    EXPECT_EQ(os.str(), "Night scene");
}

// Test unknown/out-of-range value (value 4)
TEST_F(Print0xa406Test_1416, UnknownValueAboveRange_1416) {
    auto value = Exiv2::Value::create(Exiv2::unsignedShort);
    value->read("4");
    Exiv2::Internal::print0xa406(os, *value, nullptr);
    std::string result = os.str();
    // Should output something (likely "(4)") since 4 is not in the known tags
    EXPECT_FALSE(result.empty());
    EXPECT_NE(result, "Standard");
    EXPECT_NE(result, "Landscape");
    EXPECT_NE(result, "Portrait");
    EXPECT_NE(result, "Night scene");
}

// Test with a large unknown value
TEST_F(Print0xa406Test_1416, LargeUnknownValue_1416) {
    auto value = Exiv2::Value::create(Exiv2::unsignedShort);
    value->read("65535");
    Exiv2::Internal::print0xa406(os, *value, nullptr);
    std::string result = os.str();
    EXPECT_FALSE(result.empty());
    EXPECT_NE(result, "Standard");
    EXPECT_NE(result, "Landscape");
    EXPECT_NE(result, "Portrait");
    EXPECT_NE(result, "Night scene");
}

// Test with ExifData pointer provided (non-null)
TEST_F(Print0xa406Test_1416, WithExifDataPointer_1416) {
    Exiv2::ExifData exifData;
    auto value = Exiv2::Value::create(Exiv2::unsignedShort);
    value->read("0");
    Exiv2::Internal::print0xa406(os, *value, &exifData);
    EXPECT_EQ(os.str(), "Standard");
}

// Test with ExifData pointer and landscape value
TEST_F(Print0xa406Test_1416, WithExifDataPointerLandscape_1416) {
    Exiv2::ExifData exifData;
    auto value = Exiv2::Value::create(Exiv2::unsignedShort);
    value->read("1");
    Exiv2::Internal::print0xa406(os, *value, &exifData);
    EXPECT_EQ(os.str(), "Landscape");
}

// Test that the function returns a reference to the same ostream
TEST_F(Print0xa406Test_1416, ReturnsOstreamReference_1416) {
    auto value = Exiv2::Value::create(Exiv2::unsignedShort);
    value->read("2");
    std::ostream& returned = Exiv2::Internal::print0xa406(os, *value, nullptr);
    EXPECT_EQ(&returned, &os);
}

// Test with unsignedLong type value
TEST_F(Print0xa406Test_1416, UnsignedLongValueType_1416) {
    auto value = Exiv2::Value::create(Exiv2::unsignedLong);
    value->read("0");
    Exiv2::Internal::print0xa406(os, *value, nullptr);
    EXPECT_EQ(os.str(), "Standard");
}

// Test sequential writes to the same stream
TEST_F(Print0xa406Test_1416, SequentialWrites_1416) {
    auto value0 = Exiv2::Value::create(Exiv2::unsignedShort);
    value0->read("0");
    Exiv2::Internal::print0xa406(os, *value0, nullptr);
    
    auto value1 = Exiv2::Value::create(Exiv2::unsignedShort);
    value1->read("1");
    Exiv2::Internal::print0xa406(os, *value1, nullptr);
    
    EXPECT_EQ(os.str(), "StandardLandscape");
}

// Test boundary: value just at the last valid index (3)
TEST_F(Print0xa406Test_1416, BoundaryLastValidValue_1416) {
    auto value = Exiv2::Value::create(Exiv2::unsignedShort);
    value->read("3");
    Exiv2::Internal::print0xa406(os, *value, nullptr);
    EXPECT_EQ(os.str(), "Night scene");
}

// Test negative-like value (signed interpretation)
TEST_F(Print0xa406Test_1416, SignedNegativeValue_1416) {
    auto value = Exiv2::Value::create(Exiv2::signedShort);
    value->read("-1");
    Exiv2::Internal::print0xa406(os, *value, nullptr);
    std::string result = os.str();
    EXPECT_FALSE(result.empty());
    // -1 should not match any known tag
    EXPECT_NE(result, "Standard");
    EXPECT_NE(result, "Landscape");
    EXPECT_NE(result, "Portrait");
    EXPECT_NE(result, "Night scene");
}
