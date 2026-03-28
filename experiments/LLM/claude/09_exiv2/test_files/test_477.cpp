#include <gtest/gtest.h>
#include <sstream>
#include <cmath>
#include <exiv2/exiv2.hpp>

// We need access to the Internal namespace
// Since the function is part of Nikon3MakerNote, we need to access it
// We'll test through the public interface as described

using namespace Exiv2;

class Nikon3MakerNotePrintFocusDistanceTest_477 : public ::testing::Test {
protected:
    std::ostringstream os;
    
    // Helper to call printFocusDistance via the tag's print function
    // Since we're treating this as black box, we'll test through Exiv2's
    // tag printing mechanism or directly if accessible
    
    // We'll create values and check the output format
    std::string callPrintFocusDistance(const Value& value) {
        os.str("");
        os.clear();
        // Use the Exiv2 internal printing mechanism
        // The printFocusDistance is registered as a print function for Nikon tags
        // We can access it through ExifTags printing
        
        // Since the class is in Internal namespace, let's try to invoke it
        // through the tag system
        Exiv2::Internal::Nikon3MakerNote note;
        note.printFocusDistance(os, value, nullptr);
        return os.str();
    }
};

// Test: Value with count != 1 should return raw value in parentheses
TEST_F(Nikon3MakerNotePrintFocusDistanceTest_477, WrongCount_ReturnsRawValue_477) {
    Exiv2::DataBuf buf(2);
    buf.data()[0] = 10;
    buf.data()[1] = 20;
    Exiv2::DataValue value(Exiv2::unsignedByte);
    value.read(buf.data(), 2, Exiv2::littleEndian);
    
    std::string result = callPrintFocusDistance(value);
    // Should be in parentheses format since count != 1
    EXPECT_EQ(result.front(), '(');
    EXPECT_EQ(result.back(), ')');
}

// Test: Value with wrong type should return raw value in parentheses
TEST_F(Nikon3MakerNotePrintFocusDistanceTest_477, WrongType_ReturnsRawValue_477) {
    Exiv2::ValueType<uint16_t> value;
    value.value_.push_back(42);
    
    std::string result = callPrintFocusDistance(value);
    EXPECT_EQ(result.front(), '(');
    EXPECT_EQ(result.back(), ')');
}

// Test: Value of 0 should return "n/a"
TEST_F(Nikon3MakerNotePrintFocusDistanceTest_477, ZeroValue_ReturnsNA_477) {
    Exiv2::DataValue value(Exiv2::unsignedByte);
    uint8_t data = 0;
    value.read(&data, 1, Exiv2::littleEndian);
    
    std::string result = callPrintFocusDistance(value);
    // Should contain "n/a"
    EXPECT_NE(result.find("n/a"), std::string::npos);
}

// Test: Non-zero value should return formatted distance
TEST_F(Nikon3MakerNotePrintFocusDistanceTest_477, NonZeroValue_ReturnsFormattedDistance_477) {
    Exiv2::DataValue value(Exiv2::unsignedByte);
    uint8_t data = 80; // 10^(80/40 - 2) = 10^0 = 1.00
    value.read(&data, 1, Exiv2::littleEndian);
    
    std::string result = callPrintFocusDistance(value);
    // Expected: "1.00 m"
    EXPECT_NE(result.find("1.00 m"), std::string::npos);
}

// Test: Value of 40 should give 0.10 m (10^(40/40 - 2) = 10^(-1) = 0.10)
TEST_F(Nikon3MakerNotePrintFocusDistanceTest_477, Value40_Returns0Point10m_477) {
    Exiv2::DataValue value(Exiv2::unsignedByte);
    uint8_t data = 40;
    value.read(&data, 1, Exiv2::littleEndian);
    
    std::string result = callPrintFocusDistance(value);
    // 10^(40/40 - 2) = 10^(-1) = 0.10
    EXPECT_NE(result.find("0.10 m"), std::string::npos);
}

// Test: Value of 120 should give 10.00 m (10^(120/40 - 2) = 10^1 = 10.00)
TEST_F(Nikon3MakerNotePrintFocusDistanceTest_477, Value120_Returns10m_477) {
    Exiv2::DataValue value(Exiv2::unsignedByte);
    uint8_t data = 120;
    value.read(&data, 1, Exiv2::littleEndian);
    
    std::string result = callPrintFocusDistance(value);
    // 10^(120/40 - 2) = 10^1 = 10.00
    EXPECT_NE(result.find("10.00 m"), std::string::npos);
}

// Test: Value of 1 should give a small distance
TEST_F(Nikon3MakerNotePrintFocusDistanceTest_477, Value1_ReturnsSmallDistance_477) {
    Exiv2::DataValue value(Exiv2::unsignedByte);
    uint8_t data = 1;
    value.read(&data, 1, Exiv2::littleEndian);
    
    std::string result = callPrintFocusDistance(value);
    // 10^(1/40 - 2) = 10^(-1.975) ≈ 0.01
    double expected = std::pow(10.0, (1.0 / 40.0) - 2.0);
    // Should contain " m"
    EXPECT_NE(result.find(" m"), std::string::npos);
    // Should NOT be "n/a"
    EXPECT_EQ(result.find("n/a"), std::string::npos);
}

// Test: Value of 255 (max unsigned byte) should give large distance
TEST_F(Nikon3MakerNotePrintFocusDistanceTest_477, Value255_ReturnsLargeDistance_477) {
    Exiv2::DataValue value(Exiv2::unsignedByte);
    uint8_t data = 255;
    value.read(&data, 1, Exiv2::littleEndian);
    
    std::string result = callPrintFocusDistance(value);
    // 10^(255/40 - 2) = 10^(4.375) ≈ 23713.74
    EXPECT_NE(result.find(" m"), std::string::npos);
}

// Test: Value of 160 should give 100.00 m (10^(160/40 - 2) = 10^2 = 100.00)
TEST_F(Nikon3MakerNotePrintFocusDistanceTest_477, Value160_Returns100m_477) {
    Exiv2::DataValue value(Exiv2::unsignedByte);
    uint8_t data = 160;
    value.read(&data, 1, Exiv2::littleEndian);
    
    std::string result = callPrintFocusDistance(value);
    // 10^(160/40 - 2) = 10^2 = 100.00
    EXPECT_NE(result.find("100.00 m"), std::string::npos);
}

// Test: Signed short type with count 1 should return parenthesized value (wrong type)
TEST_F(Nikon3MakerNotePrintFocusDistanceTest_477, SignedShortType_ReturnsParenthesized_477) {
    Exiv2::ValueType<int16_t> value;
    value.value_.push_back(80);
    
    std::string result = callPrintFocusDistance(value);
    // Type is signedShort, not unsignedByte
    EXPECT_EQ(result.front(), '(');
    EXPECT_EQ(result.back(), ')');
}

// Test: Empty value (count 0) should return parenthesized
TEST_F(Nikon3MakerNotePrintFocusDistanceTest_477, EmptyValue_ReturnsParenthesized_477) {
    Exiv2::DataValue value(Exiv2::unsignedByte);
    // Don't read any data - count should be 0
    
    std::string result = callPrintFocusDistance(value);
    EXPECT_EQ(result.front(), '(');
    EXPECT_EQ(result.back(), ')');
}

// Test: Verify the result ends with " m" for valid non-zero values
TEST_F(Nikon3MakerNotePrintFocusDistanceTest_477, ValidValue_EndsWithMeters_477) {
    Exiv2::DataValue value(Exiv2::unsignedByte);
    uint8_t data = 100;
    value.read(&data, 1, Exiv2::littleEndian);
    
    std::string result = callPrintFocusDistance(value);
    // Should end with " m"
    ASSERT_GE(result.size(), 2u);
    EXPECT_EQ(result.substr(result.size() - 2), " m");
}

// Test: Verify format has exactly 2 decimal places
TEST_F(Nikon3MakerNotePrintFocusDistanceTest_477, ValidValue_HasTwoDecimalPlaces_477) {
    Exiv2::DataValue value(Exiv2::unsignedByte);
    uint8_t data = 80; // Should give 1.00 m
    value.read(&data, 1, Exiv2::littleEndian);
    
    std::string result = callPrintFocusDistance(value);
    // Find the decimal point
    auto dot_pos = result.find('.');
    ASSERT_NE(dot_pos, std::string::npos);
    // After the dot, there should be exactly 2 digits before " m"
    std::string after_dot = result.substr(dot_pos + 1);
    // Should start with two digits
    EXPECT_TRUE(std::isdigit(after_dot[0]));
    EXPECT_TRUE(std::isdigit(after_dot[1]));
    EXPECT_EQ(after_dot[2], ' ');
}
