#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <sstream>
#include <string>
#include <vector>
#include <cstdint>

// Include necessary Exiv2 headers
#include <exiv2/value.hpp>
#include <exiv2/exif.hpp>

// Include the header that contains PentaxMakerNote or declare it based on the provided code
namespace Exiv2 {
namespace Internal {

// Forward declaration based on the provided implementation
class PentaxMakerNote {
public:
    std::ostream& printTime(std::ostream& os, const Value& value, const ExifData*);
};

}  // namespace Internal
}  // namespace Exiv2

class PentaxMakerNoteTest_192 : public ::testing::Test {
protected:
    Exiv2::Internal::PentaxMakerNote maker_;
    std::ostringstream oss_;
};

// Test normal time formatting with typical values
TEST_F(PentaxMakerNoteTest_192, PrintTime_NormalTime_192) {
    Exiv2::Value::UniquePtr value = Exiv2::Value::create(Exiv2::unsignedShort);
    value->read("10 30 45");
    
    maker_.printTime(oss_, *value, nullptr);
    
    EXPECT_EQ("10:30:45", oss_.str());
}

// Test time with zero values (midnight)
TEST_F(PentaxMakerNoteTest_192, PrintTime_Midnight_192) {
    Exiv2::Value::UniquePtr value = Exiv2::Value::create(Exiv2::unsignedShort);
    value->read("0 0 0");
    
    maker_.printTime(oss_, *value, nullptr);
    
    EXPECT_EQ("00:00:00", oss_.str());
}

// Test time with single digit values that should be zero-padded
TEST_F(PentaxMakerNoteTest_192, PrintTime_SingleDigitValues_192) {
    Exiv2::Value::UniquePtr value = Exiv2::Value::create(Exiv2::unsignedShort);
    value->read("1 2 3");
    
    maker_.printTime(oss_, *value, nullptr);
    
    EXPECT_EQ("01:02:03", oss_.str());
}

// Test time at end of day (23:59:59)
TEST_F(PentaxMakerNoteTest_192, PrintTime_EndOfDay_192) {
    Exiv2::Value::UniquePtr value = Exiv2::Value::create(Exiv2::unsignedShort);
    value->read("23 59 59");
    
    maker_.printTime(oss_, *value, nullptr);
    
    EXPECT_EQ("23:59:59", oss_.str());
}

// Test with noon time
TEST_F(PentaxMakerNoteTest_192, PrintTime_Noon_192) {
    Exiv2::Value::UniquePtr value = Exiv2::Value::create(Exiv2::unsignedShort);
    value->read("12 0 0");
    
    maker_.printTime(oss_, *value, nullptr);
    
    EXPECT_EQ("12:00:00", oss_.str());
}

// Test with nullptr ExifData parameter (should still work)
TEST_F(PentaxMakerNoteTest_192, PrintTime_NullExifData_192) {
    Exiv2::Value::UniquePtr value = Exiv2::Value::create(Exiv2::unsignedShort);
    value->read("15 45 30");
    
    maker_.printTime(oss_, *value, nullptr);
    
    EXPECT_EQ("15:45:30", oss_.str());
}

// Test that the function returns the same ostream reference
TEST_F(PentaxMakerNoteTest_192, PrintTime_ReturnsOstream_192) {
    Exiv2::Value::UniquePtr value = Exiv2::Value::create(Exiv2::unsignedShort);
    value->read("10 20 30");
    
    std::ostream& result = maker_.printTime(oss_, *value, nullptr);
    
    EXPECT_EQ(&oss_, &result);
}

// Test with values that have mixed padding needs
TEST_F(PentaxMakerNoteTest_192, PrintTime_MixedPadding_192) {
    Exiv2::Value::UniquePtr value = Exiv2::Value::create(Exiv2::unsignedShort);
    value->read("9 15 5");
    
    maker_.printTime(oss_, *value, nullptr);
    
    EXPECT_EQ("09:15:05", oss_.str());
}

// Test chaining output - writing to ostream that already has content
TEST_F(PentaxMakerNoteTest_192, PrintTime_AppendToExistingContent_192) {
    oss_ << "Time: ";
    Exiv2::Value::UniquePtr value = Exiv2::Value::create(Exiv2::unsignedShort);
    value->read("8 30 0");
    
    maker_.printTime(oss_, *value, nullptr);
    
    EXPECT_EQ("Time: 08:30:00", oss_.str());
}

// Test with byte type values
TEST_F(PentaxMakerNoteTest_192, PrintTime_ByteValues_192) {
    Exiv2::Value::UniquePtr value = Exiv2::Value::create(Exiv2::unsignedByte);
    value->read("14 25 36");
    
    maker_.printTime(oss_, *value, nullptr);
    
    EXPECT_EQ("14:25:36", oss_.str());
}
