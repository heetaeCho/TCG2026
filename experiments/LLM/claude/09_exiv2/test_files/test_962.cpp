#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <exiv2/value.hpp>
#include <exiv2/exif.hpp>
#include <sstream>

// We need access to the internal class
namespace Exiv2 {
namespace Internal {

class CanonMakerNote {
public:
  std::ostream& printSi0x0016(std::ostream& os, const Value& value, const ExifData*);
};

} // namespace Internal
} // namespace Exiv2

// Since we cannot directly include the internal header easily, we rely on the
// implementation being linked. We'll use the Exiv2 public API to create Value objects.

using namespace Exiv2;
using namespace Exiv2::Internal;

class CanonMakerNotePrintSi0x0016Test_962 : public ::testing::Test {
protected:
  CanonMakerNote maker_;
  std::ostringstream os_;
};

// Test: When value type is not unsignedShort, should output the raw value
TEST_F(CanonMakerNotePrintSi0x0016Test_962, NonUnsignedShortType_ReturnsRawValue_962) {
  // Create a SignedShort value instead of UnsignedShort
  ValueType<int16_t> val(signedShort);
  val.value_.push_back(100);

  maker_.printSi0x0016(os_, val, nullptr);

  std::string result = os_.str();
  // Should just output the value without " s" suffix formatting
  // Since type is not unsignedShort, it returns os << value
  EXPECT_EQ(result, "100");
}

// Test: When value count is 0, should output the raw value
TEST_F(CanonMakerNotePrintSi0x0016Test_962, EmptyValue_ReturnsRawValue_962) {
  ValueType<uint16_t> val(unsignedShort);
  // Don't add any values, count() == 0

  maker_.printSi0x0016(os_, val, nullptr);

  std::string result = os_.str();
  // Empty value output
  EXPECT_TRUE(result.find(" s") == std::string::npos);
}

// Test: Normal unsignedShort value with a typical exposure value
TEST_F(CanonMakerNotePrintSi0x0016Test_962, NormalUnsignedShortValue_OutputsExposureTime_962) {
  ValueType<uint16_t> val(unsignedShort);
  val.value_.push_back(0); // EV = 0

  maker_.printSi0x0016(os_, val, nullptr);

  std::string result = os_.str();
  // Should end with " s"
  EXPECT_TRUE(result.size() >= 2);
  EXPECT_EQ(result.substr(result.size() - 2), " s");
}

// Test: UnsignedShort value with a specific known value
TEST_F(CanonMakerNotePrintSi0x0016Test_962, UnsignedShortValue96_OutputsExposureTime_962) {
  ValueType<uint16_t> val(unsignedShort);
  val.value_.push_back(96); // Some EV value

  maker_.printSi0x0016(os_, val, nullptr);

  std::string result = os_.str();
  EXPECT_TRUE(result.find(" s") != std::string::npos);
}

// Test: UnsignedShort value with value 1
TEST_F(CanonMakerNotePrintSi0x0016Test_962, UnsignedShortValue1_OutputsExposureTime_962) {
  ValueType<uint16_t> val(unsignedShort);
  val.value_.push_back(1);

  maker_.printSi0x0016(os_, val, nullptr);

  std::string result = os_.str();
  EXPECT_TRUE(result.find(" s") != std::string::npos);
}

// Test: Passing nullptr for ExifData should work fine
TEST_F(CanonMakerNotePrintSi0x0016Test_962, NullExifData_WorksFine_962) {
  ValueType<uint16_t> val(unsignedShort);
  val.value_.push_back(160);

  EXPECT_NO_THROW(maker_.printSi0x0016(os_, val, nullptr));

  std::string result = os_.str();
  EXPECT_TRUE(result.find(" s") != std::string::npos);
}

// Test: String type value should output raw value (not unsignedShort)
TEST_F(CanonMakerNotePrintSi0x0016Test_962, StringTypeValue_ReturnsRawValue_962) {
  AsciiValue val;
  val.read("hello");

  maker_.printSi0x0016(os_, val, nullptr);

  std::string result = os_.str();
  // Since typeId() != unsignedShort, should just output the value
  EXPECT_EQ(result, "hello");
}

// Test: UnsignedLong type should output raw value
TEST_F(CanonMakerNotePrintSi0x0016Test_962, UnsignedLongType_ReturnsRawValue_962) {
  ValueType<uint32_t> val(unsignedLong);
  val.value_.push_back(42);

  maker_.printSi0x0016(os_, val, nullptr);

  std::string result = os_.str();
  EXPECT_EQ(result, "42");
}

// Test: Multiple values in unsignedShort - should use first value (toInt64 on index 0)
TEST_F(CanonMakerNotePrintSi0x0016Test_962, MultipleUnsignedShortValues_UsesFirstValue_962) {
  ValueType<uint16_t> val(unsignedShort);
  val.value_.push_back(32);
  val.value_.push_back(64);
  val.value_.push_back(128);

  maker_.printSi0x0016(os_, val, nullptr);

  std::string result = os_.str();
  // count() > 0 and typeId() == unsignedShort, so should format as exposure
  EXPECT_TRUE(result.find(" s") != std::string::npos);
}

// Test: Large unsignedShort value near max
TEST_F(CanonMakerNotePrintSi0x0016Test_962, LargeUnsignedShortValue_OutputsExposureTime_962) {
  ValueType<uint16_t> val(unsignedShort);
  val.value_.push_back(65535);

  maker_.printSi0x0016(os_, val, nullptr);

  std::string result = os_.str();
  EXPECT_TRUE(result.find(" s") != std::string::npos);
}

// Test: Return value is the same ostream reference
TEST_F(CanonMakerNotePrintSi0x0016Test_962, ReturnsSameOstream_962) {
  ValueType<uint16_t> val(unsignedShort);
  val.value_.push_back(32);

  std::ostream& ret = maker_.printSi0x0016(os_, val, nullptr);

  EXPECT_EQ(&ret, &os_);
}

// Test: Return value is the same ostream reference for non-unsignedShort
TEST_F(CanonMakerNotePrintSi0x0016Test_962, ReturnsSameOstreamForNonUShort_962) {
  ValueType<int16_t> val(signedShort);
  val.value_.push_back(42);

  std::ostream& ret = maker_.printSi0x0016(os_, val, nullptr);

  EXPECT_EQ(&ret, &os_);
}
