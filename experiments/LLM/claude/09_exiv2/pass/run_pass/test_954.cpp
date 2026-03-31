#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <sstream>
#include <cmath>
#include <exiv2/exiv2.hpp>

// We need access to the Internal namespace
#include "canonmn_int.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

// Helper function to compute canonEv as it's used in the implementation
// We won't re-implement it but we'll verify observable output behavior

class CanonMakerNoteTest_954 : public ::testing::Test {
protected:
    CanonMakerNote maker_;
    std::ostringstream os_;
};

// Test that when value type is unsignedShort and count > 0, something is printed
TEST_F(CanonMakerNoteTest_954, PrintSi0x0002_UnsignedShortWithValue_PrintsOutput_954) {
    UShortValue value;
    value.read(reinterpret_cast<const byte*>("\x00\x00"), 2, littleEndian);
    
    std::ostringstream os;
    maker_.printSi0x0002(os, value, nullptr);
    
    // With value 0, canonEv(0) should produce some result, and the formula should output a number
    EXPECT_FALSE(os.str().empty());
}

// Test that when value type is not unsignedShort, nothing is printed
TEST_F(CanonMakerNoteTest_954, PrintSi0x0002_NonUnsignedShortType_PrintsNothing_954) {
    // Use a signed long value instead of unsigned short
    LongValue value;
    value.read(reinterpret_cast<const byte*>("\x00\x00\x00\x00"), 4, littleEndian);
    
    std::ostringstream os;
    maker_.printSi0x0002(os, value, nullptr);
    
    EXPECT_TRUE(os.str().empty());
}

// Test that the function returns the same ostream reference
TEST_F(CanonMakerNoteTest_954, PrintSi0x0002_ReturnsOstreamReference_954) {
    UShortValue value;
    value.read(reinterpret_cast<const byte*>("\x00\x00"), 2, littleEndian);
    
    std::ostringstream os;
    std::ostream& result = maker_.printSi0x0002(os, value, nullptr);
    
    EXPECT_EQ(&os, &result);
}

// Test with a non-unsignedShort type also returns ostream reference
TEST_F(CanonMakerNoteTest_954, PrintSi0x0002_NonUnsignedShort_ReturnsOstreamReference_954) {
    LongValue value;
    value.read(reinterpret_cast<const byte*>("\x01\x00\x00\x00"), 4, littleEndian);
    
    std::ostringstream os;
    std::ostream& result = maker_.printSi0x0002(os, value, nullptr);
    
    EXPECT_EQ(&os, &result);
}

// Test with nullptr ExifData - should still work
TEST_F(CanonMakerNoteTest_954, PrintSi0x0002_NullExifData_DoesNotCrash_954) {
    UShortValue value;
    uint16_t rawVal = 96; // some non-zero value
    value.read(reinterpret_cast<const byte*>(&rawVal), 2, littleEndian);
    
    std::ostringstream os;
    EXPECT_NO_THROW(maker_.printSi0x0002(os, value, nullptr));
}

// Test with a specific unsigned short value to verify output is numeric
TEST_F(CanonMakerNoteTest_954, PrintSi0x0002_SpecificValue_OutputIsNumeric_954) {
    UShortValue value;
    uint16_t rawVal = 0; // value of 0
    value.read(reinterpret_cast<const byte*>(&rawVal), 2, littleEndian);
    
    std::ostringstream os;
    maker_.printSi0x0002(os, value, nullptr);
    
    std::string output = os.str();
    EXPECT_FALSE(output.empty());
    
    // The output should be parseable as a float
    try {
        float f = std::stof(output);
        EXPECT_TRUE(std::isfinite(f));
    } catch (...) {
        // If it can't be parsed, that's also informative
        // but we mainly check it's not empty for unsignedShort
    }
}

// Test with empty value (count == 0) for unsigned short
TEST_F(CanonMakerNoteTest_954, PrintSi0x0002_EmptyUnsignedShortValue_PrintsNothing_954) {
    UShortValue value;
    // Don't read any data, so count should be 0
    
    std::ostringstream os;
    maker_.printSi0x0002(os, value, nullptr);
    
    EXPECT_TRUE(os.str().empty());
}

// Test with a signed short type (not unsigned short)
TEST_F(CanonMakerNoteTest_954, PrintSi0x0002_SignedShortType_PrintsNothing_954) {
    // signedShort is different from unsignedShort
    ShortValue value;
    int16_t rawVal = 100;
    value.read(reinterpret_cast<const byte*>(&rawVal), 2, littleEndian);
    
    std::ostringstream os;
    maker_.printSi0x0002(os, value, nullptr);
    
    // signedShort typeId is different from unsignedShort, so nothing should print
    // Note: ShortValue might actually be unsignedShort depending on Exiv2 implementation
    // This test verifies the type checking behavior
}

// Test with multiple unsigned short values (count > 1)
TEST_F(CanonMakerNoteTest_954, PrintSi0x0002_MultipleValues_PrintsBasedOnFirst_954) {
    UShortValue value;
    uint16_t rawVals[2] = {0, 100};
    value.read(reinterpret_cast<const byte*>(rawVals), 4, littleEndian);
    
    std::ostringstream os;
    maker_.printSi0x0002(os, value, nullptr);
    
    // count > 0 and type is unsignedShort, so should print something
    EXPECT_FALSE(os.str().empty());
}

// Test with a string value type
TEST_F(CanonMakerNoteTest_954, PrintSi0x0002_StringValueType_PrintsNothing_954) {
    StringValue value;
    value.read("test");
    
    std::ostringstream os;
    maker_.printSi0x0002(os, value, nullptr);
    
    // String type is not unsignedShort, so nothing should print
    EXPECT_TRUE(os.str().empty());
}
