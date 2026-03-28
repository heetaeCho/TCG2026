// =================================================================================================
//  TEST_ID: 715
//  File: panasonicmn_int_test.cpp
//  Unit tests for: Exiv2::Internal::PanasonicMakerNote::printAccelerometer
// =================================================================================================

#include <gtest/gtest.h>

#include <cstdint>
#include <limits>
#include <sstream>
#include <string>

// Include Exiv2 public headers for Value / ExifData.
// Adjust include paths as needed for your build.
#include <exiv2/exiv2.hpp>

// Include the internal header that declares PanasonicMakerNote.
// If your project structure differs, adjust accordingly.
#include "panasonicmn_int.hpp"

namespace {

using Exiv2::ExifData;
using Exiv2::Value;
using Exiv2::ValueType;
using Exiv2::Internal::PanasonicMakerNote;

class PanasonicMakerNoteTest_715 : public ::testing::Test {
 protected:
  PanasonicMakerNote sut_;
  ExifData exif_;  // passed as pointer; should not be dereferenced by this function.
};

static Value::UniquePtr MakeSignedLongValue(int32_t v) {
  // SignedLong is a common numeric Value type in Exiv2.
  // This only constructs a Value; the class under test is a black box.
  Value::UniquePtr val = Value::create(ValueType::signedLong);
  val->read(std::to_string(v));
  return val;
}

TEST_F(PanasonicMakerNoteTest_715, PrintsZero_715) {
  auto v = MakeSignedLongValue(0);
  std::ostringstream os;

  std::ostream& ret = sut_.printAccelerometer(os, *v, &exif_);

  EXPECT_EQ(&ret, &os);
  EXPECT_EQ(os.str(), "0");
}

TEST_F(PanasonicMakerNoteTest_715, PrintsPositiveWithinInt16Range_715) {
  auto v = MakeSignedLongValue(12345);
  std::ostringstream os;

  sut_.printAccelerometer(os, *v, nullptr);

  EXPECT_EQ(os.str(), "12345");
}

TEST_F(PanasonicMakerNoteTest_715, PrintsNegativeWithinInt16Range_715) {
  auto v = MakeSignedLongValue(-12345);
  std::ostringstream os;

  sut_.printAccelerometer(os, *v, &exif_);

  EXPECT_EQ(os.str(), "-12345");
}

TEST_F(PanasonicMakerNoteTest_715, TruncatesToInt16_MaxBoundary_715) {
  const int32_t in = std::numeric_limits<int16_t>::max();  // 32767
  auto v = MakeSignedLongValue(in);
  std::ostringstream os;

  sut_.printAccelerometer(os, *v, nullptr);

  EXPECT_EQ(os.str(), "32767");
}

TEST_F(PanasonicMakerNoteTest_715, TruncatesToInt16_MinBoundary_715) {
  const int32_t in = std::numeric_limits<int16_t>::min();  // -32768
  auto v = MakeSignedLongValue(in);
  std::ostringstream os;

  sut_.printAccelerometer(os, *v, &exif_);

  EXPECT_EQ(os.str(), "-32768");
}

TEST_F(PanasonicMakerNoteTest_715, WrapsOnOverflow_PositiveBeyondInt16_715) {
  // Behavior is observable: the implementation casts to int16_t then prints it.
  // 32768 becomes -32768 in int16_t.
  auto v = MakeSignedLongValue(std::numeric_limits<int16_t>::max() + 1);  // 32768
  std::ostringstream os;

  sut_.printAccelerometer(os, *v, nullptr);

  EXPECT_EQ(os.str(), "-32768");
}

TEST_F(PanasonicMakerNoteTest_715, WrapsOnOverflow_NegativeBeyondInt16_715) {
  // -32769 becomes 32767 in int16_t.
  auto v = MakeSignedLongValue(std::numeric_limits<int16_t>::min() - 1);  // -32769
  std::ostringstream os;

  sut_.printAccelerometer(os, *v, &exif_);

  EXPECT_EQ(os.str(), "32767");
}

TEST_F(PanasonicMakerNoteTest_715, AppendsToExistingStreamContent_715) {
  auto v = MakeSignedLongValue(42);
  std::ostringstream os;
  os << "prefix:";

  sut_.printAccelerometer(os, *v, nullptr);

  EXPECT_EQ(os.str(), "prefix:42");
}

TEST_F(PanasonicMakerNoteTest_715, DoesNotThrowWithNullExifData_715) {
  auto v = MakeSignedLongValue(-7);
  std::ostringstream os;

  EXPECT_NO_THROW({
    sut_.printAccelerometer(os, *v, nullptr);
  });
  EXPECT_EQ(os.str(), "-7");
}

}  // namespace