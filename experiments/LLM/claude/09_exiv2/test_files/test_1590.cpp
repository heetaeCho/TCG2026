#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <sstream>
#include <exiv2/value.hpp>
#include <exiv2/exif.hpp>

// Include the header that declares the SonyMakerNote class
// Since we only have the implementation, we'll need to declare it
namespace Exiv2 {
namespace Internal {
class SonyMakerNote {
public:
    std::ostream& printMultiBurstSize(std::ostream& os, const Value& value, const ExifData*);
};
}  // namespace Internal
}  // namespace Exiv2

using namespace Exiv2;
using namespace Exiv2::Internal;

class SonyMakerNoteTest_1590 : public ::testing::Test {
protected:
    SonyMakerNote maker_;
    std::ostringstream oss_;
};

// Test normal operation: single unsignedShort value
TEST_F(SonyMakerNoteTest_1590, PrintMultiBurstSize_NormalSingleUnsignedShort_1590) {
    UShortValue value;
    value.read(reinterpret_cast<const byte*>("\x00\x01"), 2, littleEndian);
    
    maker_.printMultiBurstSize(oss_, value, nullptr);
    
    // Should print the uint32 representation of the value
    EXPECT_EQ(oss_.str(), std::to_string(value.toUint32(0)));
}

// Test with zero value
TEST_F(SonyMakerNoteTest_1590, PrintMultiBurstSize_ZeroValue_1590) {
    UShortValue value;
    uint16_t zero = 0;
    value.read(reinterpret_cast<const byte*>(&zero), 2, littleEndian);
    
    maker_.printMultiBurstSize(oss_, value, nullptr);
    
    EXPECT_EQ(oss_.str(), "0");
}

// Test with maximum unsigned short value
TEST_F(SonyMakerNoteTest_1590, PrintMultiBurstSize_MaxUnsignedShort_1590) {
    UShortValue value;
    uint16_t maxVal = 0xFFFF;
    value.read(reinterpret_cast<const byte*>(&maxVal), 2, littleEndian);
    
    maker_.printMultiBurstSize(oss_, value, nullptr);
    
    EXPECT_EQ(oss_.str(), std::to_string(65535));
}

// Test boundary: wrong type (not unsignedShort) - should output parenthesized format
TEST_F(SonyMakerNoteTest_1590, PrintMultiBurstSize_WrongType_UnsignedLong_1590) {
    ULongValue value;
    uint32_t val = 42;
    value.read(reinterpret_cast<const byte*>(&val), 4, littleEndian);
    
    maker_.printMultiBurstSize(oss_, value, nullptr);
    
    std::string result = oss_.str();
    // Should be wrapped in parentheses since it's not unsignedShort
    EXPECT_TRUE(result.front() == '(');
    EXPECT_TRUE(result.back() == ')');
}

// Test boundary: count != 1 (multiple unsignedShort values)
TEST_F(SonyMakerNoteTest_1590, PrintMultiBurstSize_MultipleValues_1590) {
    UShortValue value;
    uint16_t data[2] = {100, 200};
    value.read(reinterpret_cast<const byte*>(data), 4, littleEndian);
    
    ASSERT_EQ(value.count(), 2u);
    
    maker_.printMultiBurstSize(oss_, value, nullptr);
    
    std::string result = oss_.str();
    // count != 1, so should be parenthesized
    EXPECT_TRUE(result.front() == '(');
    EXPECT_TRUE(result.back() == ')');
}

// Test with nullptr ExifData - normal case should still work
TEST_F(SonyMakerNoteTest_1590, PrintMultiBurstSize_NullExifData_1590) {
    UShortValue value;
    uint16_t val = 1024;
    value.read(reinterpret_cast<const byte*>(&val), 2, littleEndian);
    
    maker_.printMultiBurstSize(oss_, value, nullptr);
    
    EXPECT_EQ(oss_.str(), "1024");
}

// Test with a signed short type (wrong type)
TEST_F(SonyMakerNoteTest_1590, PrintMultiBurstSize_SignedShortType_1590) {
    ShortValue value;
    int16_t val = 42;
    value.read(reinterpret_cast<const byte*>(&val), 2, littleEndian);
    
    maker_.printMultiBurstSize(oss_, value, nullptr);
    
    std::string result = oss_.str();
    // signedShort != unsignedShort, so should be parenthesized
    EXPECT_TRUE(result.front() == '(');
    EXPECT_TRUE(result.back() == ')');
}

// Test with ASCII string value (wrong type and potentially wrong count)
TEST_F(SonyMakerNoteTest_1590, PrintMultiBurstSize_AsciiValue_1590) {
    AsciiValue value;
    value.read("test");
    
    maker_.printMultiBurstSize(oss_, value, nullptr);
    
    std::string result = oss_.str();
    // Wrong type, should be parenthesized
    EXPECT_TRUE(result.front() == '(');
    EXPECT_TRUE(result.back() == ')');
}

// Test that the return value is the same ostream reference
TEST_F(SonyMakerNoteTest_1590, PrintMultiBurstSize_ReturnsOstreamReference_1590) {
    UShortValue value;
    uint16_t val = 5;
    value.read(reinterpret_cast<const byte*>(&val), 2, littleEndian);
    
    std::ostream& result = maker_.printMultiBurstSize(oss_, value, nullptr);
    
    EXPECT_EQ(&result, &oss_);
}

// Test that the return value is the same ostream reference in error case
TEST_F(SonyMakerNoteTest_1590, PrintMultiBurstSize_ReturnsOstreamReferenceOnError_1590) {
    ULongValue value;
    uint32_t val = 42;
    value.read(reinterpret_cast<const byte*>(&val), 4, littleEndian);
    
    std::ostream& result = maker_.printMultiBurstSize(oss_, value, nullptr);
    
    EXPECT_EQ(&result, &oss_);
}

// Test with a specific known value
TEST_F(SonyMakerNoteTest_1590, PrintMultiBurstSize_SpecificValue256_1590) {
    UShortValue value;
    uint16_t val = 256;
    value.read(reinterpret_cast<const byte*>(&val), 2, littleEndian);
    
    maker_.printMultiBurstSize(oss_, value, nullptr);
    
    EXPECT_EQ(oss_.str(), "256");
}

// Test with value of 1
TEST_F(SonyMakerNoteTest_1590, PrintMultiBurstSize_ValueOne_1590) {
    UShortValue value;
    uint16_t val = 1;
    value.read(reinterpret_cast<const byte*>(&val), 2, littleEndian);
    
    maker_.printMultiBurstSize(oss_, value, nullptr);
    
    EXPECT_EQ(oss_.str(), "1");
}
