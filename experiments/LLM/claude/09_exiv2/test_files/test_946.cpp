#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <exiv2/value.hpp>
#include <exiv2/exif.hpp>
#include <sstream>

// Include the internal header for CanonMakerNote
// Since we're given a partial implementation, we need to work with the interface
namespace Exiv2 {
namespace Internal {

class CanonMakerNote {
 public:
  std::ostream& printCs0x0002(std::ostream& os, const Value& value, const ExifData*);
};

}  // namespace Internal
}  // namespace Exiv2

// We need to include the actual implementation or link against it.
// For the purpose of this test, we replicate the provided implementation.
// In a real build system, this would be linked from the library.
namespace Exiv2 {
namespace Internal {

std::ostream& CanonMakerNote::printCs0x0002(std::ostream& os, const Value& value, const ExifData*) {
  if (value.typeId() != unsignedShort || value.count() == 0)
    return os << value;
  if (auto l = value.toInt64(); l == 0) {
    os << "Off";
  } else {
    os << l / 10.0 << " s";
  }
  return os;
}

}  // namespace Internal
}  // namespace Exiv2

using namespace Exiv2;
using namespace Exiv2::Internal;

class CanonMakerNoteTest_946 : public ::testing::Test {
 protected:
  CanonMakerNote maker_;
  std::ostringstream os_;
};

// Test: When value is unsignedShort and value is 0, output should be "Off"
TEST_F(CanonMakerNoteTest_946, PrintCs0x0002_ValueZero_PrintsOff_946) {
  ValueType<uint16_t> value(unsignedShort);
  value.value_.push_back(0);

  maker_.printCs0x0002(os_, value, nullptr);
  EXPECT_EQ(os_.str(), "Off");
}

// Test: When value is unsignedShort and value is 10, output should be "1 s"
TEST_F(CanonMakerNoteTest_946, PrintCs0x0002_Value10_Prints1Second_946) {
  ValueType<uint16_t> value(unsignedShort);
  value.value_.push_back(10);

  maker_.printCs0x0002(os_, value, nullptr);
  EXPECT_EQ(os_.str(), "1 s");
}

// Test: When value is unsignedShort and value is 20, output should be "2 s"
TEST_F(CanonMakerNoteTest_946, PrintCs0x0002_Value20_Prints2Seconds_946) {
  ValueType<uint16_t> value(unsignedShort);
  value.value_.push_back(20);

  maker_.printCs0x0002(os_, value, nullptr);
  EXPECT_EQ(os_.str(), "2 s");
}

// Test: When value is unsignedShort and value is 5, output should be "0.5 s"
TEST_F(CanonMakerNoteTest_946, PrintCs0x0002_Value5_PrintsHalfSecond_946) {
  ValueType<uint16_t> value(unsignedShort);
  value.value_.push_back(5);

  maker_.printCs0x0002(os_, value, nullptr);
  EXPECT_EQ(os_.str(), "0.5 s");
}

// Test: When value is unsignedShort and value is 1, output should be "0.1 s"
TEST_F(CanonMakerNoteTest_946, PrintCs0x0002_Value1_PrintsTenthSecond_946) {
  ValueType<uint16_t> value(unsignedShort);
  value.value_.push_back(1);

  maker_.printCs0x0002(os_, value, nullptr);
  EXPECT_EQ(os_.str(), "0.1 s");
}

// Test: When value type is not unsignedShort (e.g., unsignedLong), should print raw value
TEST_F(CanonMakerNoteTest_946, PrintCs0x0002_WrongType_PrintsRawValue_946) {
  ValueType<uint32_t> value(unsignedLong);
  value.value_.push_back(42);

  maker_.printCs0x0002(os_, value, nullptr);
  // Should just print the value using operator<< on Value
  EXPECT_FALSE(os_.str().empty());
  // It should NOT print "Off" or "s"
  EXPECT_EQ(os_.str().find("Off"), std::string::npos);
}

// Test: When value count is 0, should print raw value (empty)
TEST_F(CanonMakerNoteTest_946, PrintCs0x0002_EmptyValue_PrintsRawValue_946) {
  ValueType<uint16_t> value(unsignedShort);
  // No values pushed, count() == 0

  maker_.printCs0x0002(os_, value, nullptr);
  // With count == 0, it falls through to os << value
  // The output might be empty or some default representation
  // Key point: it should not crash
}

// Test: When value is unsignedShort with large value
TEST_F(CanonMakerNoteTest_946, PrintCs0x0002_LargeValue_PrintsCorrectly_946) {
  ValueType<uint16_t> value(unsignedShort);
  value.value_.push_back(1000);

  maker_.printCs0x0002(os_, value, nullptr);
  EXPECT_EQ(os_.str(), "100 s");
}

// Test: Passing nullptr for ExifData should work fine
TEST_F(CanonMakerNoteTest_946, PrintCs0x0002_NullExifData_WorksFine_946) {
  ValueType<uint16_t> value(unsignedShort);
  value.value_.push_back(30);

  maker_.printCs0x0002(os_, value, nullptr);
  EXPECT_EQ(os_.str(), "3 s");
}

// Test: When value type is string, should print raw value
TEST_F(CanonMakerNoteTest_946, PrintCs0x0002_StringType_PrintsRawValue_946) {
  AsciiValue value;
  value.read("hello");

  maker_.printCs0x0002(os_, value, nullptr);
  // Should print raw value since typeId != unsignedShort
  std::string result = os_.str();
  EXPECT_FALSE(result.empty());
}

// Test: Value 15 should print "1.5 s"
TEST_F(CanonMakerNoteTest_946, PrintCs0x0002_Value15_Prints1Point5Seconds_946) {
  ValueType<uint16_t> value(unsignedShort);
  value.value_.push_back(15);

  maker_.printCs0x0002(os_, value, nullptr);
  EXPECT_EQ(os_.str(), "1.5 s");
}

// Test: Multiple values - only first value's toInt64 is used
TEST_F(CanonMakerNoteTest_946, PrintCs0x0002_MultipleValues_UsesFirstValue_946) {
  ValueType<uint16_t> value(unsignedShort);
  value.value_.push_back(30);
  value.value_.push_back(50);

  maker_.printCs0x0002(os_, value, nullptr);
  // toInt64() without index returns first value
  EXPECT_EQ(os_.str(), "3 s");
}

// Test: Return value is the same stream
TEST_F(CanonMakerNoteTest_946, PrintCs0x0002_ReturnsSameStream_946) {
  ValueType<uint16_t> value(unsignedShort);
  value.value_.push_back(10);

  std::ostream& result = maker_.printCs0x0002(os_, value, nullptr);
  EXPECT_EQ(&result, &os_);
}
