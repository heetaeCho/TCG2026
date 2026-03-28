#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <exiv2/value.hpp>
#include <exiv2/exif.hpp>
#include <sstream>

// We need to include the internal header or replicate the class declaration
// Since we're given the implementation, we'll work with it directly
namespace Exiv2 {
namespace Internal {
class CanonMakerNote {
 public:
  std::ostream& printSi0x0013(std::ostream& os, const Value& value, const ExifData*) {
    if (value.typeId() != unsignedShort || value.count() == 0)
      return os << value;
    if (auto l = value.toInt64(); l == 0xffff)  {
      return os << "Infinite";
    }
    return os << value.toInt64() / 100.0 << " m";
  }
};
}  // namespace Internal
}  // namespace Exiv2

using namespace Exiv2;
using namespace Exiv2::Internal;

class CanonMakerNoteTest_960 : public ::testing::Test {
 protected:
  CanonMakerNote maker_;
  std::ostringstream os_;
};

// Test: When value type is unsignedShort and value is 0xffff, should print "Infinite"
TEST_F(CanonMakerNoteTest_960, PrintSi0x0013_Infinite_960) {
  ValueType<uint16_t> value;
  value.value_.push_back(0xffff);
  
  maker_.printSi0x0013(os_, value, nullptr);
  
  EXPECT_EQ(os_.str(), "Infinite");
}

// Test: When value type is unsignedShort and value is a normal distance, should print distance in meters
TEST_F(CanonMakerNoteTest_960, PrintSi0x0013_NormalDistance_960) {
  ValueType<uint16_t> value;
  value.value_.push_back(500);  // 500/100.0 = 5.0 m
  
  maker_.printSi0x0013(os_, value, nullptr);
  
  EXPECT_EQ(os_.str(), "5 m");
}

// Test: When value type is unsignedShort and value is 0, should print "0 m"
TEST_F(CanonMakerNoteTest_960, PrintSi0x0013_ZeroDistance_960) {
  ValueType<uint16_t> value;
  value.value_.push_back(0);
  
  maker_.printSi0x0013(os_, value, nullptr);
  
  EXPECT_EQ(os_.str(), "0 m");
}

// Test: When value type is unsignedShort and value is 1, should print "0.01 m"
TEST_F(CanonMakerNoteTest_960, PrintSi0x0013_SmallDistance_960) {
  ValueType<uint16_t> value;
  value.value_.push_back(1);
  
  maker_.printSi0x0013(os_, value, nullptr);
  
  EXPECT_EQ(os_.str(), "0.01 m");
}

// Test: When value type is unsignedShort and value is 100, should print "1 m"
TEST_F(CanonMakerNoteTest_960, PrintSi0x0013_OneMetreDistance_960) {
  ValueType<uint16_t> value;
  value.value_.push_back(100);
  
  maker_.printSi0x0013(os_, value, nullptr);
  
  EXPECT_EQ(os_.str(), "1 m");
}

// Test: When value type is unsignedShort and value is 250, should print "2.5 m"
TEST_F(CanonMakerNoteTest_960, PrintSi0x0013_FractionalDistance_960) {
  ValueType<uint16_t> value;
  value.value_.push_back(250);
  
  maker_.printSi0x0013(os_, value, nullptr);
  
  EXPECT_EQ(os_.str(), "2.5 m");
}

// Test: When value type is NOT unsignedShort (e.g., unsignedLong), should print raw value
TEST_F(CanonMakerNoteTest_960, PrintSi0x0013_WrongType_960) {
  ValueType<uint32_t> value;
  value.value_.push_back(500);
  
  maker_.printSi0x0013(os_, value, nullptr);
  
  // Should print the raw value via os << value, not as distance
  EXPECT_FALSE(os_.str().empty());
  // Should NOT contain " m" since it's the wrong type
  EXPECT_EQ(os_.str().find(" m"), std::string::npos);
}

// Test: When value type is unsignedShort but count is 0 (empty), should print raw value
TEST_F(CanonMakerNoteTest_960, PrintSi0x0013_EmptyValue_960) {
  ValueType<uint16_t> value;
  // Don't push any values, count() should be 0
  
  maker_.printSi0x0013(os_, value, nullptr);
  
  // With empty value, it falls through to os << value
  // The output should not contain " m"
  EXPECT_EQ(os_.str().find(" m"), std::string::npos);
}

// Test: When value is a signed short type, should print raw value (wrong type)
TEST_F(CanonMakerNoteTest_960, PrintSi0x0013_SignedShortType_960) {
  ValueType<int16_t> value;
  value.value_.push_back(500);
  
  maker_.printSi0x0013(os_, value, nullptr);
  
  // signedShort != unsignedShort, so should print raw value
  EXPECT_FALSE(os_.str().empty());
}

// Test: When value is 0xfffe (one less than infinite), should print distance
TEST_F(CanonMakerNoteTest_960, PrintSi0x0013_JustBelowInfinite_960) {
  ValueType<uint16_t> value;
  value.value_.push_back(0xfffe);  // 65534 / 100.0 = 655.34 m
  
  maker_.printSi0x0013(os_, value, nullptr);
  
  std::string result = os_.str();
  EXPECT_NE(result, "Infinite");
  EXPECT_NE(result.find(" m"), std::string::npos);
}

// Test: When ExifData pointer is nullptr (should work fine)
TEST_F(CanonMakerNoteTest_960, PrintSi0x0013_NullExifData_960) {
  ValueType<uint16_t> value;
  value.value_.push_back(1000);  // 10 m
  
  maker_.printSi0x0013(os_, value, nullptr);
  
  EXPECT_EQ(os_.str(), "10 m");
}

// Test: Large value just below 0xffff
TEST_F(CanonMakerNoteTest_960, PrintSi0x0013_LargeValue_960) {
  ValueType<uint16_t> value;
  value.value_.push_back(60000);  // 600 m
  
  maker_.printSi0x0013(os_, value, nullptr);
  
  EXPECT_EQ(os_.str(), "600 m");
}

// Test: When value type is string, should print raw value
TEST_F(CanonMakerNoteTest_960, PrintSi0x0013_StringType_960) {
  AsciiValue value;
  value.read("test");
  
  maker_.printSi0x0013(os_, value, nullptr);
  
  std::string result = os_.str();
  // Should not contain " m" since it's wrong type
  EXPECT_EQ(result.find(" m"), std::string::npos);
}
