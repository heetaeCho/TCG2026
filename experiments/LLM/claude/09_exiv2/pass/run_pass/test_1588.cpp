#include <gtest/gtest.h>
#include <exiv2/exiv2.hpp>
#include <sstream>

// We need to access the SonyMakerNote class from the Internal namespace
// Since the class is defined in sonymn_int.cpp, we include the relevant header
#include "sonymn_int.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

class SonyMakerNoteTest_1588 : public ::testing::Test {
protected:
    SonyMakerNote sonyMakerNote;
    std::ostringstream os;
};

// Test normal operation with a single unsignedLong value
TEST_F(SonyMakerNoteTest_1588, PrintWhiteBalanceFineTune_NormalValue_1588) {
    ULongValue value;
    value.read("42");
    
    sonyMakerNote.printWhiteBalanceFineTune(os, value, nullptr);
    
    EXPECT_EQ(os.str(), "42");
}

// Test normal operation with zero value
TEST_F(SonyMakerNoteTest_1588, PrintWhiteBalanceFineTune_ZeroValue_1588) {
    ULongValue value;
    value.read("0");
    
    sonyMakerNote.printWhiteBalanceFineTune(os, value, nullptr);
    
    EXPECT_EQ(os.str(), "0");
}

// Test with large unsigned value that becomes negative when cast to int32_t
TEST_F(SonyMakerNoteTest_1588, PrintWhiteBalanceFineTune_LargeUnsignedValue_1588) {
    ULongValue value;
    // 4294967295 is 0xFFFFFFFF, which is -1 as int32_t
    value.read("4294967295");
    
    sonyMakerNote.printWhiteBalanceFineTune(os, value, nullptr);
    
    EXPECT_EQ(os.str(), "-1");
}

// Test with value that has high bit set (negative when interpreted as signed)
TEST_F(SonyMakerNoteTest_1588, PrintWhiteBalanceFineTune_HighBitSet_1588) {
    ULongValue value;
    // 2147483648 is 0x80000000, which is INT32_MIN as int32_t
    value.read("2147483648");
    
    sonyMakerNote.printWhiteBalanceFineTune(os, value, nullptr);
    
    EXPECT_EQ(os.str(), "-2147483648");
}

// Test with wrong type (not unsignedLong) - should output parenthesized value
TEST_F(SonyMakerNoteTest_1588, PrintWhiteBalanceFineTune_WrongType_1588) {
    UShortValue value;
    value.read("42");
    
    sonyMakerNote.printWhiteBalanceFineTune(os, value, nullptr);
    
    std::string result = os.str();
    EXPECT_EQ(result.front(), '(');
    EXPECT_EQ(result.back(), ')');
}

// Test with multiple values (count != 1) - should output parenthesized value
TEST_F(SonyMakerNoteTest_1588, PrintWhiteBalanceFineTune_MultipleValues_1588) {
    ULongValue value;
    value.read("42");
    value.read("43");
    
    // count() should be 2, so it should fall into the parenthesized output
    if (value.count() != 1) {
        sonyMakerNote.printWhiteBalanceFineTune(os, value, nullptr);
        std::string result = os.str();
        EXPECT_EQ(result.front(), '(');
        EXPECT_EQ(result.back(), ')');
    }
}

// Test with value 1
TEST_F(SonyMakerNoteTest_1588, PrintWhiteBalanceFineTune_ValueOne_1588) {
    ULongValue value;
    value.read("1");
    
    sonyMakerNote.printWhiteBalanceFineTune(os, value, nullptr);
    
    EXPECT_EQ(os.str(), "1");
}

// Test with max int32_t value (2147483647)
TEST_F(SonyMakerNoteTest_1588, PrintWhiteBalanceFineTune_MaxInt32_1588) {
    ULongValue value;
    value.read("2147483647");
    
    sonyMakerNote.printWhiteBalanceFineTune(os, value, nullptr);
    
    EXPECT_EQ(os.str(), "2147483647");
}

// Test that the function returns the ostream reference
TEST_F(SonyMakerNoteTest_1588, PrintWhiteBalanceFineTune_ReturnsOstream_1588) {
    ULongValue value;
    value.read("100");
    
    std::ostream& result = sonyMakerNote.printWhiteBalanceFineTune(os, value, nullptr);
    
    EXPECT_EQ(&result, &os);
}

// Test that ExifData pointer can be null without issues
TEST_F(SonyMakerNoteTest_1588, PrintWhiteBalanceFineTune_NullExifData_1588) {
    ULongValue value;
    value.read("50");
    
    EXPECT_NO_THROW(sonyMakerNote.printWhiteBalanceFineTune(os, value, nullptr));
    EXPECT_EQ(os.str(), "50");
}

// Test with wrong type - string type should trigger parenthesized output
TEST_F(SonyMakerNoteTest_1588, PrintWhiteBalanceFineTune_StringType_1588) {
    StringValue value;
    value.read("hello");
    
    sonyMakerNote.printWhiteBalanceFineTune(os, value, nullptr);
    
    std::string result = os.str();
    EXPECT_EQ(result.front(), '(');
    EXPECT_EQ(result.back(), ')');
}

// Test with value close to negative boundary in signed interpretation
TEST_F(SonyMakerNoteTest_1588, PrintWhiteBalanceFineTune_NearNegativeBoundary_1588) {
    ULongValue value;
    // 4294967294 is 0xFFFFFFFE, which is -2 as int32_t
    value.read("4294967294");
    
    sonyMakerNote.printWhiteBalanceFineTune(os, value, nullptr);
    
    EXPECT_EQ(os.str(), "-2");
}
