#include <gtest/gtest.h>
#include <sstream>
#include <exiv2/exiv2.hpp>
#include "nikonmn_int.hpp"

// We need access to the Internal namespace
using namespace Exiv2;
using namespace Exiv2::Internal;

class Nikon3MakerNoteTest_467 : public ::testing::Test {
protected:
    std::ostringstream os;
    
    // Helper to create a DataValue with specific bytes
    std::unique_ptr<DataValue> makeValue(const std::vector<uint8_t>& bytes) {
        auto val = std::make_unique<DataValue>(invalidTypeId);
        // Use DataValue with undefined type for byte array
        auto dv = std::make_unique<DataValue>(undefined);
        dv->read(bytes.data(), bytes.size(), invalidByteOrder);
        return dv;
    }
};

// Test when value size is not 4 - should print value in parentheses
TEST_F(Nikon3MakerNoteTest_467, SizeNot4PrintsParenthesized_467) {
    // Create a value with size != 4
    DataValue val(undefined);
    uint8_t data[] = {0x01, 0x02, 0x03};
    val.read(data, 3, invalidByteOrder);
    
    Nikon3MakerNote::print0x0088(os, val, nullptr);
    std::string result = os.str();
    EXPECT_TRUE(result.front() == '(');
    EXPECT_TRUE(result.back() == ')');
}

// Test when value size is 5 (also != 4)
TEST_F(Nikon3MakerNoteTest_467, Size5PrintsParenthesized_467) {
    DataValue val(undefined);
    uint8_t data[] = {0x01, 0x02, 0x03, 0x04, 0x05};
    val.read(data, 5, invalidByteOrder);
    
    Nikon3MakerNote::print0x0088(os, val, nullptr);
    std::string result = os.str();
    EXPECT_TRUE(result.front() == '(');
    EXPECT_TRUE(result.back() == ')');
}

// Test when all four bytes are zero - should print "n/a"
TEST_F(Nikon3MakerNoteTest_467, AllZerosPrintsNA_467) {
    DataValue val(undefined);
    uint8_t data[] = {0x00, 0x00, 0x00, 0x00};
    val.read(data, 4, invalidByteOrder);
    
    Nikon3MakerNote::print0x0088(os, val, nullptr);
    std::string result = os.str();
    EXPECT_NE(result.find("n/a"), std::string::npos);
}

// Test focus metering = 0x00 (Single area), focus point = 0, focus used = 1 (bit 0 = center)
TEST_F(Nikon3MakerNoteTest_467, SingleAreaFocusMetering_467) {
    DataValue val(undefined);
    // focusmetering=0, focuspoint=0, focusused=(0<<8)+1 = 1
    uint8_t data[] = {0x00, 0x00, 0x00, 0x01};
    val.read(data, 4, invalidByteOrder);
    
    Nikon3MakerNote::print0x0088(os, val, nullptr);
    std::string result = os.str();
    EXPECT_NE(result.find("Single area"), std::string::npos);
    EXPECT_NE(result.find("used"), std::string::npos);
}

// Test focus metering = 0x01 (Dynamic area)
TEST_F(Nikon3MakerNoteTest_467, DynamicAreaFocusMetering_467) {
    DataValue val(undefined);
    // focusmetering=1, focuspoint=0, focusused=1
    uint8_t data[] = {0x01, 0x00, 0x00, 0x01};
    val.read(data, 4, invalidByteOrder);
    
    Nikon3MakerNote::print0x0088(os, val, nullptr);
    std::string result = os.str();
    EXPECT_NE(result.find("Dynamic area"), std::string::npos);
    EXPECT_NE(result.find("used"), std::string::npos);
}

// Test focus metering = 0x02 (Closest subject) - no user selected point
TEST_F(Nikon3MakerNoteTest_467, ClosestSubjectFocusMetering_467) {
    DataValue val(undefined);
    // focusmetering=2, focuspoint=0, focusused=1
    uint8_t data[] = {0x02, 0x00, 0x00, 0x01};
    val.read(data, 4, invalidByteOrder);
    
    Nikon3MakerNote::print0x0088(os, val, nullptr);
    std::string result = os.str();
    EXPECT_NE(result.find("Closest subject"), std::string::npos);
    // For closest subject, no focus point should be printed
}

// Test focus metering = 0x03 (Group dynamic-AF)
TEST_F(Nikon3MakerNoteTest_467, GroupDynamicAFFocusMetering_467) {
    DataValue val(undefined);
    // focusmetering=3, focuspoint=0, focusused=1
    uint8_t data[] = {0x03, 0x00, 0x00, 0x01};
    val.read(data, 4, invalidByteOrder);
    
    Nikon3MakerNote::print0x0088(os, val, nullptr);
    std::string result = os.str();
    EXPECT_NE(result.find("Group dynamic-AF"), std::string::npos);
}

// Test focus metering = 0x04 (Single area wide)
TEST_F(Nikon3MakerNoteTest_467, SingleAreaWideFocusMetering_467) {
    DataValue val(undefined);
    uint8_t data[] = {0x04, 0x00, 0x00, 0x01};
    val.read(data, 4, invalidByteOrder);
    
    Nikon3MakerNote::print0x0088(os, val, nullptr);
    std::string result = os.str();
    EXPECT_NE(result.find("Single area (wide)"), std::string::npos);
}

// Test focus metering = 0x05 (Dynamic area wide)
TEST_F(Nikon3MakerNoteTest_467, DynamicAreaWideFocusMetering_467) {
    DataValue val(undefined);
    uint8_t data[] = {0x05, 0x00, 0x00, 0x01};
    val.read(data, 4, invalidByteOrder);
    
    Nikon3MakerNote::print0x0088(os, val, nullptr);
    std::string result = os.str();
    EXPECT_NE(result.find("Dynamic area (wide)"), std::string::npos);
}

// Test unknown focus metering value - should print in parentheses
TEST_F(Nikon3MakerNoteTest_467, UnknownFocusMeteringValue_467) {
    DataValue val(undefined);
    uint8_t data[] = {0x0A, 0x00, 0x00, 0x01};
    val.read(data, 4, invalidByteOrder);
    
    Nikon3MakerNote::print0x0088(os, val, nullptr);
    std::string result = os.str();
    EXPECT_NE(result.find("(10)"), std::string::npos);
}

// Test focusused = 0 should print "none" then "used"
TEST_F(Nikon3MakerNoteTest_467, FocusUsedZeroPrintsNone_467) {
    DataValue val(undefined);
    // focusmetering=0, focuspoint=1, focusused=0
    // Note: all zero would hit the early return, so we need focuspoint != 0
    uint8_t data[] = {0x00, 0x01, 0x00, 0x00};
    val.read(data, 4, invalidByteOrder);
    
    Nikon3MakerNote::print0x0088(os, val, nullptr);
    std::string result = os.str();
    EXPECT_NE(result.find("none"), std::string::npos);
    EXPECT_NE(result.find("used"), std::string::npos);
}

// Test when focusused matches exactly 1 << focuspoint (no extra points listed)
TEST_F(Nikon3MakerNoteTest_467, FocusUsedMatchesFocusPoint_467) {
    DataValue val(undefined);
    // focusmetering=0, focuspoint=2, focusused=(0<<8)+4 = 4 = 1<<2
    uint8_t data[] = {0x00, 0x02, 0x00, 0x04};
    val.read(data, 4, invalidByteOrder);
    
    Nikon3MakerNote::print0x0088(os, val, nullptr);
    std::string result = os.str();
    EXPECT_NE(result.find("Single area"), std::string::npos);
    EXPECT_NE(result.find("used"), std::string::npos);
}

// Test when focusused has multiple bits set (different from 1<<focuspoint)
TEST_F(Nikon3MakerNoteTest_467, FocusUsedMultiplePoints_467) {
    DataValue val(undefined);
    // focusmetering=0, focuspoint=0, focusused=(0<<8)+3 = 3 (bits 0 and 1)
    uint8_t data[] = {0x00, 0x00, 0x00, 0x03};
    val.read(data, 4, invalidByteOrder);
    
    Nikon3MakerNote::print0x0088(os, val, nullptr);
    std::string result = os.str();
    EXPECT_NE(result.find("used"), std::string::npos);
}

// Test with empty value (size = 0)
TEST_F(Nikon3MakerNoteTest_467, EmptyValuePrintsParenthesized_467) {
    DataValue val(undefined);
    // Don't read any data - size should be 0
    
    Nikon3MakerNote::print0x0088(os, val, nullptr);
    std::string result = os.str();
    EXPECT_TRUE(result.front() == '(');
    EXPECT_TRUE(result.back() == ')');
}

// Test with single byte value
TEST_F(Nikon3MakerNoteTest_467, SingleByteValuePrintsParenthesized_467) {
    DataValue val(undefined);
    uint8_t data[] = {0x01};
    val.read(data, 1, invalidByteOrder);
    
    Nikon3MakerNote::print0x0088(os, val, nullptr);
    std::string result = os.str();
    EXPECT_TRUE(result.front() == '(');
    EXPECT_TRUE(result.back() == ')');
}

// Test focuspoint out of range of nikonFocuspoints array
TEST_F(Nikon3MakerNoteTest_467, FocusPointOutOfRange_467) {
    DataValue val(undefined);
    // focusmetering=0, focuspoint=0xFF (likely out of range), focusused=1
    uint8_t data[] = {0x00, 0xFF, 0x00, 0x01};
    val.read(data, 4, invalidByteOrder);
    
    Nikon3MakerNote::print0x0088(os, val, nullptr);
    std::string result = os.str();
    // Out of range focus point should be printed in parentheses
    EXPECT_NE(result.find("(255)"), std::string::npos);
}

// Test closest subject with focusused having multiple bits
TEST_F(Nikon3MakerNoteTest_467, ClosestSubjectMultipleFocusUsed_467) {
    DataValue val(undefined);
    // focusmetering=2, focuspoint=0, focusused=3 (bits 0 and 1, not equal to 1<<0=1)
    uint8_t data[] = {0x02, 0x00, 0x00, 0x03};
    val.read(data, 4, invalidByteOrder);
    
    Nikon3MakerNote::print0x0088(os, val, nullptr);
    std::string result = os.str();
    EXPECT_NE(result.find("Closest subject"), std::string::npos);
    EXPECT_NE(result.find("used"), std::string::npos);
}

// Test that the function returns the ostream reference
TEST_F(Nikon3MakerNoteTest_467, ReturnsOstreamReference_467) {
    DataValue val(undefined);
    uint8_t data[] = {0x00, 0x00, 0x00, 0x00};
    val.read(data, 4, invalidByteOrder);
    
    std::ostream& result = Nikon3MakerNote::print0x0088(os, val, nullptr);
    EXPECT_EQ(&result, &os);
}

// Test focusused with high byte set (byte 2 contributes to focusused)
TEST_F(Nikon3MakerNoteTest_467, FocusUsedHighByte_467) {
    DataValue val(undefined);
    // focusmetering=0, focuspoint=0, focusused = (1<<8)+0 = 256
    // 256 != 1<<0 = 1, so multiple focus points should be listed
    uint8_t data[] = {0x00, 0x00, 0x01, 0x00};
    val.read(data, 4, invalidByteOrder);
    
    Nikon3MakerNote::print0x0088(os, val, nullptr);
    std::string result = os.str();
    EXPECT_NE(result.find("used"), std::string::npos);
}

// Test with 2 bytes (size != 4)
TEST_F(Nikon3MakerNoteTest_467, TwoBytesValuePrintsParenthesized_467) {
    DataValue val(undefined);
    uint8_t data[] = {0x01, 0x02};
    val.read(data, 2, invalidByteOrder);
    
    Nikon3MakerNote::print0x0088(os, val, nullptr);
    std::string result = os.str();
    EXPECT_TRUE(result.front() == '(');
    EXPECT_TRUE(result.back() == ')');
}
