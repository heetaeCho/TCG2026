#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <sstream>
#include <exiv2/value.hpp>
#include <exiv2/exif.hpp>

// We need to include or replicate the minimal interface for testing
// Based on the provided code, we need the SonyMakerNote class
namespace Exiv2 {
namespace Internal {
class SonyMakerNote {
public:
    std::ostream& printFocalPlaneAFPointsUsed(std::ostream& os, const Value& value, const ExifData*);
};
}  // namespace Internal
}  // namespace Exiv2

// Since we need the actual implementation, let's include it or link against it.
// The test file relies on the implementation from sonymn_int.cpp being linked.

class SonyMakerNoteTest_1599 : public ::testing::Test {
protected:
    Exiv2::Internal::SonyMakerNote maker_;
    std::ostringstream os_;
};

// Test: When value type is unsignedByte and first element is 0, output should contain "None"
TEST_F(SonyMakerNoteTest_1599, FocalPlaneAFPointsUsed_UnsignedByte_Zero_PrintsNone_1599) {
    Exiv2::DataBuf buf(1);
    buf.data()[0] = 0;
    Exiv2::DataValue value(Exiv2::unsignedByte);
    value.read(buf.c_data(), buf.size(), Exiv2::littleEndian);

    maker_.printFocalPlaneAFPointsUsed(os_, value, nullptr);

    std::string result = os_.str();
    // Should print the translated "None" string
    EXPECT_TRUE(result.find("None") != std::string::npos) 
        << "Expected 'None' in output, got: " << result;
}

// Test: When value type is unsignedByte and first element is non-zero, output should be parenthesized value
TEST_F(SonyMakerNoteTest_1599, FocalPlaneAFPointsUsed_UnsignedByte_NonZero_PrintsParenthesizedValue_1599) {
    Exiv2::DataBuf buf(1);
    buf.data()[0] = 5;
    Exiv2::DataValue value(Exiv2::unsignedByte);
    value.read(buf.c_data(), buf.size(), Exiv2::littleEndian);

    maker_.printFocalPlaneAFPointsUsed(os_, value, nullptr);

    std::string result = os_.str();
    EXPECT_EQ(result.front(), '(');
    EXPECT_EQ(result.back(), ')');
    EXPECT_TRUE(result.find("5") != std::string::npos)
        << "Expected '5' in output, got: " << result;
}

// Test: When value type is not unsignedByte, output should be parenthesized value
TEST_F(SonyMakerNoteTest_1599, FocalPlaneAFPointsUsed_NonUnsignedByte_PrintsParenthesizedValue_1599) {
    Exiv2::UShortValue value;
    value.read("42");

    maker_.printFocalPlaneAFPointsUsed(os_, value, nullptr);

    std::string result = os_.str();
    EXPECT_EQ(result.front(), '(');
    EXPECT_EQ(result.back(), ')');
    EXPECT_TRUE(result.find("42") != std::string::npos)
        << "Expected '42' in output, got: " << result;
}

// Test: When value type is unsignedByte with value 255 (boundary), should print parenthesized
TEST_F(SonyMakerNoteTest_1599, FocalPlaneAFPointsUsed_UnsignedByte_Max_PrintsParenthesizedValue_1599) {
    Exiv2::DataBuf buf(1);
    buf.data()[0] = 255;
    Exiv2::DataValue value(Exiv2::unsignedByte);
    value.read(buf.c_data(), buf.size(), Exiv2::littleEndian);

    maker_.printFocalPlaneAFPointsUsed(os_, value, nullptr);

    std::string result = os_.str();
    EXPECT_EQ(result.front(), '(');
    EXPECT_EQ(result.back(), ')');
    EXPECT_TRUE(result.find("255") != std::string::npos)
        << "Expected '255' in output, got: " << result;
}

// Test: When value type is unsignedByte with value 1 (boundary non-zero), should print parenthesized
TEST_F(SonyMakerNoteTest_1599, FocalPlaneAFPointsUsed_UnsignedByte_One_PrintsParenthesizedValue_1599) {
    Exiv2::DataBuf buf(1);
    buf.data()[0] = 1;
    Exiv2::DataValue value(Exiv2::unsignedByte);
    value.read(buf.c_data(), buf.size(), Exiv2::littleEndian);

    maker_.printFocalPlaneAFPointsUsed(os_, value, nullptr);

    std::string result = os_.str();
    EXPECT_EQ(result.front(), '(');
    EXPECT_EQ(result.back(), ')');
}

// Test: When ExifData pointer is nullptr, function should still work correctly
TEST_F(SonyMakerNoteTest_1599, FocalPlaneAFPointsUsed_NullExifData_WorksCorrectly_1599) {
    Exiv2::DataBuf buf(1);
    buf.data()[0] = 0;
    Exiv2::DataValue value(Exiv2::unsignedByte);
    value.read(buf.c_data(), buf.size(), Exiv2::littleEndian);

    // Should not crash with nullptr ExifData
    EXPECT_NO_THROW(maker_.printFocalPlaneAFPointsUsed(os_, value, nullptr));
}

// Test: Return value is reference to the same stream
TEST_F(SonyMakerNoteTest_1599, FocalPlaneAFPointsUsed_ReturnsSameStream_1599) {
    Exiv2::DataBuf buf(1);
    buf.data()[0] = 0;
    Exiv2::DataValue value(Exiv2::unsignedByte);
    value.read(buf.c_data(), buf.size(), Exiv2::littleEndian);

    std::ostream& result = maker_.printFocalPlaneAFPointsUsed(os_, value, nullptr);
    EXPECT_EQ(&result, &os_);
}

// Test: Non-unsignedByte type (signedShort) should produce parenthesized output
TEST_F(SonyMakerNoteTest_1599, FocalPlaneAFPointsUsed_SignedShortType_PrintsParenthesizedValue_1599) {
    Exiv2::ShortValue value;
    value.read("0");

    maker_.printFocalPlaneAFPointsUsed(os_, value, nullptr);

    std::string result = os_.str();
    // Since type is not unsignedByte, should go to first branch: "(" << value << ")"
    EXPECT_EQ(result.front(), '(');
    EXPECT_EQ(result.back(), ')');
}

// Test: Multiple bytes as unsignedByte with first being zero should print None
TEST_F(SonyMakerNoteTest_1599, FocalPlaneAFPointsUsed_MultipleBytes_FirstZero_PrintsNone_1599) {
    Exiv2::DataBuf buf(3);
    buf.data()[0] = 0;
    buf.data()[1] = 10;
    buf.data()[2] = 20;
    Exiv2::DataValue value(Exiv2::unsignedByte);
    value.read(buf.c_data(), buf.size(), Exiv2::littleEndian);

    maker_.printFocalPlaneAFPointsUsed(os_, value, nullptr);

    std::string result = os_.str();
    EXPECT_TRUE(result.find("None") != std::string::npos)
        << "Expected 'None' in output, got: " << result;
}

// Test: Multiple bytes as unsignedByte with first being non-zero should print parenthesized
TEST_F(SonyMakerNoteTest_1599, FocalPlaneAFPointsUsed_MultipleBytes_FirstNonZero_PrintsParenthesized_1599) {
    Exiv2::DataBuf buf(3);
    buf.data()[0] = 1;
    buf.data()[1] = 10;
    buf.data()[2] = 20;
    Exiv2::DataValue value(Exiv2::unsignedByte);
    value.read(buf.c_data(), buf.size(), Exiv2::littleEndian);

    maker_.printFocalPlaneAFPointsUsed(os_, value, nullptr);

    std::string result = os_.str();
    EXPECT_EQ(result.front(), '(');
    EXPECT_EQ(result.back(), ')');
}

// Test: Using unsignedLong type (not unsignedByte) should produce parenthesized output
TEST_F(SonyMakerNoteTest_1599, FocalPlaneAFPointsUsed_UnsignedLongType_PrintsParenthesizedValue_1599) {
    Exiv2::ULongValue value;
    value.read("100");

    maker_.printFocalPlaneAFPointsUsed(os_, value, nullptr);

    std::string result = os_.str();
    EXPECT_EQ(result.front(), '(');
    EXPECT_EQ(result.back(), ')');
    EXPECT_TRUE(result.find("100") != std::string::npos);
}
