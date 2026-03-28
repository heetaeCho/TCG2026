// File: test_canonmn_int_printSi0x0009_956.cpp
#include <gtest/gtest.h>

#include <sstream>
#include <string>

// Exiv2 public headers (for Value/ExifData/type IDs)
#include <exiv2/exiv2.hpp>

// Include the implementation TU that contains CanonMakerNote (internal).
// This matches the provided file path in the prompt.
#include "canonmn_int.cpp"

namespace {

// Helper: stream a Value to string via operator<< (used for expected fallback output).
static std::string ValueToString(const Exiv2::Value& v) {
  std::ostringstream os;
  os << v;
  return os.str();
}

}  // namespace

namespace Exiv2::Internal {

class CanonMakerNoteTest_956 : public ::testing::Test {
 protected:
  CanonMakerNote sut_;
};

// Normal operation: unsignedShort + count>0 prints numeric (toInt64) with no extra text.
TEST_F(CanonMakerNoteTest_956, UnsignedShortCountOne_PrintsNumeric_956) {
  Exiv2::Value::UniquePtr v = Exiv2::Value::create(Exiv2::unsignedShort);
  ASSERT_NE(v.get(), nullptr);
  ASSERT_EQ(0, v->read("42"));

  std::ostringstream os;
  sut_.printSi0x0009(os, *v, nullptr);

  EXPECT_EQ("42", os.str());
}

// Boundary: unsignedShort + count==0 falls back to streaming the Value itself.
TEST_F(CanonMakerNoteTest_956, UnsignedShortCountZero_FallsBackToValueStream_956) {
  // Create an unsignedShort Value but do not read anything => count() should be 0.
  Exiv2::Value::UniquePtr v = Exiv2::Value::create(Exiv2::unsignedShort);
  ASSERT_NE(v.get(), nullptr);

  const std::string expected = ValueToString(*v);

  std::ostringstream os;
  sut_.printSi0x0009(os, *v, nullptr);

  EXPECT_EQ(expected, os.str());
}

// Error/exceptional (observable): wrong typeId should fall back to streaming the Value itself.
TEST_F(CanonMakerNoteTest_956, WrongTypeId_FallsBackToValueStream_956) {
  Exiv2::Value::UniquePtr v = Exiv2::Value::create(Exiv2::signedShort);  // not unsignedShort
  ASSERT_NE(v.get(), nullptr);
  ASSERT_EQ(0, v->read("7"));

  const std::string expected = ValueToString(*v);

  std::ostringstream os;
  sut_.printSi0x0009(os, *v, nullptr);

  EXPECT_EQ(expected, os.str());
}

// Boundary: unsignedShort with multiple elements still prints a number (black-box: uses toInt64()).
// We verify it produces non-empty output and is parseable as an integer.
TEST_F(CanonMakerNoteTest_956, UnsignedShortMultipleValues_ProducesIntegerText_956) {
  Exiv2::Value::UniquePtr v = Exiv2::Value::create(Exiv2::unsignedShort);
  ASSERT_NE(v.get(), nullptr);
  ASSERT_EQ(0, v->read("1 2 3"));

  std::ostringstream os;
  sut_.printSi0x0009(os, *v, nullptr);

  const std::string out = os.str();
  ASSERT_FALSE(out.empty());

  // Must be parseable as an integer (do not assume which element is chosen).
  std::istringstream is(out);
  long long parsed = 0;
  is >> parsed;
  EXPECT_TRUE(is && is.eof()) << "Output was not a plain integer: '" << out << "'";
}

// Boundary: large-ish value remains printed as digits (no truncation assumptions; just verify integer text).
TEST_F(CanonMakerNoteTest_956, UnsignedShortLargeValue_ProducesIntegerText_956) {
  Exiv2::Value::UniquePtr v = Exiv2::Value::create(Exiv2::unsignedShort);
  ASSERT_NE(v.get(), nullptr);

  // Use max of uint16_t
  ASSERT_EQ(0, v->read("65535"));

  std::ostringstream os;
  sut_.printSi0x0009(os, *v, nullptr);

  EXPECT_EQ("65535", os.str());
}

// External interaction: ExifData pointer is accepted (may be null or non-null) and should not affect output.
// We only validate equality of outputs for null vs non-null on same Value.
TEST_F(CanonMakerNoteTest_956, ExifDataPointerDoesNotChangeOutput_956) {
  Exiv2::Value::UniquePtr v = Exiv2::Value::create(Exiv2::unsignedShort);
  ASSERT_NE(v.get(), nullptr);
  ASSERT_EQ(0, v->read("123"));

  std::ostringstream os_null;
  sut_.printSi0x0009(os_null, *v, nullptr);

  Exiv2::ExifData exif;
  std::ostringstream os_nonnull;
  sut_.printSi0x0009(os_nonnull, *v, &exif);

  EXPECT_EQ(os_null.str(), os_nonnull.str());
  EXPECT_EQ("123", os_null.str());
}

}  // namespace Exiv2::Internal