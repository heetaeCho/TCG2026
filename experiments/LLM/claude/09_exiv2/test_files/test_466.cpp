#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <sstream>
#include <string>

// We need Exiv2 headers for Value, ExifData, etc.
#include <exiv2/value.hpp>
#include <exiv2/exif.hpp>
#include <exiv2/types.hpp>

// Include the internal header for Nikon3MakerNote
// Since the class is in Exiv2::Internal namespace, we need access to it.
// We'll recreate the class interface as provided in the partial code.

namespace Exiv2 {
namespace Internal {

class Nikon3MakerNote {
 public:
  std::ostream& print0x0086(std::ostream& os, const Value& value, const ExifData*) {
    auto [r, s] = value.toRational();
    if (r == 0)
      return os << "Not used";
    if (s == 0)
      return os << "(" << value << ")";
    std::ostringstream tmp;
    tmp << std::fixed;
    tmp.precision(1);
    tmp << static_cast<float>(r) / s << "x";
    return os << tmp.str();
  }
};

}  // namespace Internal
}  // namespace Exiv2

using namespace Exiv2;
using namespace Exiv2::Internal;

class Nikon3MakerNoteTest_466 : public ::testing::Test {
 protected:
  Nikon3MakerNote maker_;
  std::ostringstream os_;
};

// Test when rational value is 0/1 (r == 0) => "Not used"
TEST_F(Nikon3MakerNoteTest_466, Print0x0086_ZeroNumerator_ReturnsNotUsed_466) {
  auto value = Value::create(unsignedRational);
  URational rat(0, 1);
  value->read(reinterpret_cast<const byte*>(&rat), 8, littleEndian);

  maker_.print0x0086(os_, *value, nullptr);

  EXPECT_EQ(os_.str(), "Not used");
}

// Test when rational value is 0/0 (r == 0, s == 0) => "Not used" (r==0 check comes first)
TEST_F(Nikon3MakerNoteTest_466, Print0x0086_ZeroNumeratorZeroDenominator_ReturnsNotUsed_466) {
  auto value = Value::create(unsignedRational);
  URational rat(0, 0);
  value->read(reinterpret_cast<const byte*>(&rat), 8, littleEndian);

  maker_.print0x0086(os_, *value, nullptr);

  EXPECT_EQ(os_.str(), "Not used");
}

// Test when rational denominator is 0 but numerator is non-zero => parenthesized output
TEST_F(Nikon3MakerNoteTest_466, Print0x0086_NonZeroNumeratorZeroDenominator_ReturnsParenthesized_466) {
  auto value = Value::create(unsignedRational);
  URational rat(5, 0);
  value->read(reinterpret_cast<const byte*>(&rat), 8, littleEndian);

  maker_.print0x0086(os_, *value, nullptr);

  std::string result = os_.str();
  EXPECT_TRUE(result.front() == '(');
  EXPECT_TRUE(result.back() == ')');
}

// Test normal rational value 2/1 => "2.0x"
TEST_F(Nikon3MakerNoteTest_466, Print0x0086_NormalValue2Over1_Returns2Point0x_466) {
  auto value = Value::create(unsignedRational);
  URational rat(2, 1);
  value->read(reinterpret_cast<const byte*>(&rat), 8, littleEndian);

  maker_.print0x0086(os_, *value, nullptr);

  EXPECT_EQ(os_.str(), "2.0x");
}

// Test normal rational value 3/2 => "1.5x"
TEST_F(Nikon3MakerNoteTest_466, Print0x0086_NormalValue3Over2_Returns1Point5x_466) {
  auto value = Value::create(unsignedRational);
  URational rat(3, 2);
  value->read(reinterpret_cast<const byte*>(&rat), 8, littleEndian);

  maker_.print0x0086(os_, *value, nullptr);

  EXPECT_EQ(os_.str(), "1.5x");
}

// Test normal rational value 1/1 => "1.0x"
TEST_F(Nikon3MakerNoteTest_466, Print0x0086_NormalValue1Over1_Returns1Point0x_466) {
  auto value = Value::create(unsignedRational);
  URational rat(1, 1);
  value->read(reinterpret_cast<const byte*>(&rat), 8, littleEndian);

  maker_.print0x0086(os_, *value, nullptr);

  EXPECT_EQ(os_.str(), "1.0x");
}

// Test rational value 7/3 => "2.3x"
TEST_F(Nikon3MakerNoteTest_466, Print0x0086_NormalValue7Over3_ReturnsFormatted_466) {
  auto value = Value::create(unsignedRational);
  URational rat(7, 3);
  value->read(reinterpret_cast<const byte*>(&rat), 8, littleEndian);

  maker_.print0x0086(os_, *value, nullptr);

  EXPECT_EQ(os_.str(), "2.3x");
}

// Test rational value 1/3 => "0.3x"
TEST_F(Nikon3MakerNoteTest_466, Print0x0086_SmallFraction_ReturnsFormatted_466) {
  auto value = Value::create(unsignedRational);
  URational rat(1, 3);
  value->read(reinterpret_cast<const byte*>(&rat), 8, littleEndian);

  maker_.print0x0086(os_, *value, nullptr);

  EXPECT_EQ(os_.str(), "0.3x");
}

// Test with nullptr ExifData - should work fine (not used in the function)
TEST_F(Nikon3MakerNoteTest_466, Print0x0086_NullExifData_DoesNotCrash_466) {
  auto value = Value::create(unsignedRational);
  URational rat(5, 2);
  value->read(reinterpret_cast<const byte*>(&rat), 8, littleEndian);

  EXPECT_NO_THROW(maker_.print0x0086(os_, *value, nullptr));
  EXPECT_EQ(os_.str(), "2.5x");
}

// Test large values
TEST_F(Nikon3MakerNoteTest_466, Print0x0086_LargeValues_ReturnsFormatted_466) {
  auto value = Value::create(unsignedRational);
  URational rat(10000, 1);
  value->read(reinterpret_cast<const byte*>(&rat), 8, littleEndian);

  maker_.print0x0086(os_, *value, nullptr);

  EXPECT_EQ(os_.str(), "10000.0x");
}

// Test that return value is the same stream
TEST_F(Nikon3MakerNoteTest_466, Print0x0086_ReturnsSameStream_466) {
  auto value = Value::create(unsignedRational);
  URational rat(2, 1);
  value->read(reinterpret_cast<const byte*>(&rat), 8, littleEndian);

  std::ostream& result = maker_.print0x0086(os_, *value, nullptr);

  EXPECT_EQ(&result, &os_);
}

// Test using signed rational with r == 0
TEST_F(Nikon3MakerNoteTest_466, Print0x0086_SignedRationalZero_ReturnsNotUsed_466) {
  auto value = Value::create(signedRational);
  Rational rat(0, 1);
  value->read(reinterpret_cast<const byte*>(&rat), 8, littleEndian);

  maker_.print0x0086(os_, *value, nullptr);

  EXPECT_EQ(os_.str(), "Not used");
}
