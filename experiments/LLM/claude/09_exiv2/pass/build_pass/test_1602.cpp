#include <gtest/gtest.h>
#include <sstream>
#include <exiv2/value.hpp>
#include <exiv2/exif.hpp>

// We need access to the internal function, so we replicate the class declaration
// as provided in the partial code
namespace Exiv2 {
namespace Internal {

class SonyMakerNote {
 public:
  std::ostream& printPixelShiftInfo(std::ostream& os, const Value& value, const ExifData*);
};

}  // namespace Internal
}  // namespace Exiv2

// Helper to create an undefined-type Value with specific bytes
static std::unique_ptr<Exiv2::Value> makeUndefinedValue(const std::vector<uint8_t>& bytes) {
  auto val = Exiv2::Value::create(Exiv2::undefined);
  val->read(bytes.data(), bytes.size(), Exiv2::littleEndian);
  return val;
}

class SonyMakerNoteTest_1602 : public ::testing::Test {
 protected:
  Exiv2::Internal::SonyMakerNote maker_;
  std::ostringstream os_;
};

// Test: When value count is not 6, should print fallback format
TEST_F(SonyMakerNoteTest_1602, WrongCount_PrintsFallback_1602) {
  // Create undefined value with 5 bytes (count != 6)
  std::vector<uint8_t> data = {0, 0, 0, 0, 0};
  auto val = makeUndefinedValue(data);
  
  maker_.printPixelShiftInfo(os_, *val, nullptr);
  std::string result = os_.str();
  
  // Should start with "(" and end with ")"
  EXPECT_EQ(result.front(), '(');
  EXPECT_EQ(result.back(), ')');
}

// Test: When value count is 7 (more than 6), should print fallback format
TEST_F(SonyMakerNoteTest_1602, TooManyBytes_PrintsFallback_1602) {
  std::vector<uint8_t> data = {0, 0, 0, 0, 0, 0, 0};
  auto val = makeUndefinedValue(data);
  
  maker_.printPixelShiftInfo(os_, *val, nullptr);
  std::string result = os_.str();
  
  EXPECT_EQ(result.front(), '(');
  EXPECT_EQ(result.back(), ')');
}

// Test: When type is not undefined but count is 6, should print fallback
TEST_F(SonyMakerNoteTest_1602, WrongType_PrintsFallback_1602) {
  // Create a short-type value with 6 entries
  auto val = Exiv2::Value::create(Exiv2::unsignedShort);
  // Read 6 unsigned shorts (12 bytes)
  uint8_t data[12] = {0};
  val->read(data, 12, Exiv2::littleEndian);
  
  maker_.printPixelShiftInfo(os_, *val, nullptr);
  std::string result = os_.str();
  
  // If count is 6 but type is wrong, should print fallback
  EXPECT_EQ(result.front(), '(');
  EXPECT_EQ(result.back(), ')');
}

// Test: All zeros should print "n/a"
TEST_F(SonyMakerNoteTest_1602, AllZeros_PrintsNA_1602) {
  std::vector<uint8_t> data = {0, 0, 0, 0, 0, 0};
  auto val = makeUndefinedValue(data);
  
  maker_.printPixelShiftInfo(os_, *val, nullptr);
  std::string result = os_.str();
  
  // Should contain "n/a"
  EXPECT_NE(result.find("n/a"), std::string::npos);
}

// Test: Non-zero values should produce formatted group output
TEST_F(SonyMakerNoteTest_1602, NonZeroValues_PrintsGroupInfo_1602) {
  // bytes: {1, 2, 3, 4, 2, 4}
  // groupID = (4 << 24) + (3 << 16) + (2 << 8) + 1 = 0x04030201
  std::vector<uint8_t> data = {1, 2, 3, 4, 2, 4};
  auto val = makeUndefinedValue(data);
  
  maker_.printPixelShiftInfo(os_, *val, nullptr);
  std::string result = os_.str();
  
  // Should contain "Group" and "Shot"
  EXPECT_NE(result.find("Group"), std::string::npos);
  EXPECT_NE(result.find("Shot"), std::string::npos);
  // Shot should be "2/4"
  EXPECT_NE(result.find("2/4"), std::string::npos);
}

// Test: Verify specific groupID bit extraction
TEST_F(SonyMakerNoteTest_1602, SpecificGroupID_CorrectExtraction_1602) {
  // groupID = (byte3 << 24) + (byte2 << 16) + (byte1 << 8) + byte0
  // Let's use bytes that give a known groupID
  // bytes: {0x00, 0x00, 0x00, 0x00, 1, 1} but all zeros -> "n/a"
  // Use: {0x01, 0x00, 0x00, 0x00, 1, 1}
  // groupID = 0x00000001
  // (groupID >> 17) & 0x1f = 0
  // (groupID >> 12) & 0x1f = 0
  // (groupID >> 6) & 0x3f = 0
  // groupID & 0x3f = 1
  // (groupID >> 22) = 0
  // Result: "Group 00000001, Shot 1/1 (0x0)"
  std::vector<uint8_t> data = {0x01, 0x00, 0x00, 0x00, 1, 1};
  auto val = makeUndefinedValue(data);
  
  maker_.printPixelShiftInfo(os_, *val, nullptr);
  std::string result = os_.str();
  
  EXPECT_NE(result.find("Group"), std::string::npos);
  EXPECT_NE(result.find("Shot 1/1"), std::string::npos);
  EXPECT_NE(result.find("0x0"), std::string::npos);
}

// Test: Verify with larger byte values
TEST_F(SonyMakerNoteTest_1602, LargerByteValues_CorrectFormat_1602) {
  // bytes: {0xFF, 0xFF, 0xFF, 0xFF, 3, 4}
  // groupID = 0xFFFFFFFF
  // (groupID >> 17) & 0x1f = (0x7FFF) & 0x1f = 31
  // (groupID >> 12) & 0x1f = (0xFFFFF) & 0x1f = 31
  // (groupID >> 6) & 0x3f = (0x3FFFFFF) & 0x3f = 63
  // groupID & 0x3f = 63
  // (groupID >> 22) = 0x3FF = 1023
  std::vector<uint8_t> data = {0xFF, 0xFF, 0xFF, 0xFF, 3, 4};
  auto val = makeUndefinedValue(data);
  
  maker_.printPixelShiftInfo(os_, *val, nullptr);
  std::string result = os_.str();
  
  EXPECT_NE(result.find("Group"), std::string::npos);
  EXPECT_NE(result.find("Shot 3/4"), std::string::npos);
  EXPECT_NE(result.find("0x3ff"), std::string::npos);
}

// Test: Empty value (count 0) should print fallback
TEST_F(SonyMakerNoteTest_1602, EmptyValue_PrintsFallback_1602) {
  auto val = Exiv2::Value::create(Exiv2::undefined);
  // Don't read any data -> count should be 0
  
  maker_.printPixelShiftInfo(os_, *val, nullptr);
  std::string result = os_.str();
  
  EXPECT_EQ(result.front(), '(');
  EXPECT_EQ(result.back(), ')');
}

// Test: ExifData pointer is nullptr - should still work normally
TEST_F(SonyMakerNoteTest_1602, NullExifData_Works_1602) {
  std::vector<uint8_t> data = {0, 0, 0, 0, 0, 0};
  auto val = makeUndefinedValue(data);
  
  // Should not crash with nullptr ExifData
  maker_.printPixelShiftInfo(os_, *val, nullptr);
  std::string result = os_.str();
  
  EXPECT_NE(result.find("n/a"), std::string::npos);
}

// Test: Shot numbers at boundary (0/0)
TEST_F(SonyMakerNoteTest_1602, ShotZeroZero_1602) {
  // All non-zero in first 4 bytes but shot 0/0
  std::vector<uint8_t> data = {0x01, 0x00, 0x00, 0x00, 0, 0};
  auto val = makeUndefinedValue(data);
  
  maker_.printPixelShiftInfo(os_, *val, nullptr);
  std::string result = os_.str();
  
  EXPECT_NE(result.find("Shot 0/0"), std::string::npos);
}

// Test: Maximum shot values (255/255)
TEST_F(SonyMakerNoteTest_1602, MaxShotValues_1602) {
  std::vector<uint8_t> data = {0x01, 0x00, 0x00, 0x00, 0xFF, 0xFF};
  auto val = makeUndefinedValue(data);
  
  maker_.printPixelShiftInfo(os_, *val, nullptr);
  std::string result = os_.str();
  
  EXPECT_NE(result.find("Shot 255/255"), std::string::npos);
}

// Test: Single byte value (count 1)
TEST_F(SonyMakerNoteTest_1602, SingleByte_PrintsFallback_1602) {
  std::vector<uint8_t> data = {42};
  auto val = makeUndefinedValue(data);
  
  maker_.printPixelShiftInfo(os_, *val, nullptr);
  std::string result = os_.str();
  
  EXPECT_EQ(result.front(), '(');
  EXPECT_EQ(result.back(), ')');
}

// Test: Verify output stream is returned correctly (chaining)
TEST_F(SonyMakerNoteTest_1602, ReturnsOutputStream_1602) {
  std::vector<uint8_t> data = {0, 0, 0, 0, 0, 0};
  auto val = makeUndefinedValue(data);
  
  std::ostream& returned = maker_.printPixelShiftInfo(os_, *val, nullptr);
  
  // The returned reference should be the same stream
  EXPECT_EQ(&returned, &os_);
}

// Test: Verify Group formatting with specific bit patterns
TEST_F(SonyMakerNoteTest_1602, GroupBitPattern_1602) {
  // groupID where each field has a distinct value
  // Let's set groupID = (10 << 17) | (5 << 12) | (30 << 6) | 15
  // = 0x00145BCF... let me compute:
  // 10 << 17 = 1310720 = 0x140000
  // 5 << 12 = 20480 = 0x5000
  // 30 << 6 = 1920 = 0x780
  // 15 = 0xF
  // groupID = 0x14578F
  // In bytes (little-endian): byte0=0x8F, byte1=0x57, byte2=0x14, byte3=0x00
  // (groupID >> 22) = 0
  std::vector<uint8_t> data = {0x8F, 0x57, 0x14, 0x00, 2, 3};
  auto val = makeUndefinedValue(data);
  
  maker_.printPixelShiftInfo(os_, *val, nullptr);
  std::string result = os_.str();
  
  // Group fields: 10, 05, 30, 15
  EXPECT_NE(result.find("Group"), std::string::npos);
  EXPECT_NE(result.find("Shot 2/3"), std::string::npos);
}
