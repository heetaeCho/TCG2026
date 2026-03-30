// =================================================================================================
// TestProjects/exiv2/src/panasonicmn_int_test.cpp
// Unit tests for: Exiv2::Internal::PanasonicMakerNote::printRollAngle
//
// Constraints:
// - Black-box tests based only on the provided public interface.
// - No private/internal state access.
// - Cover normal, boundary, and error/exceptional cases (when observable).
// =================================================================================================

#include <gtest/gtest.h>

#include <cstdint>
#include <limits>
#include <memory>
#include <sstream>
#include <string>

#include "panasonicmn_int.hpp"  // Expected to declare Exiv2::Internal::PanasonicMakerNote

// Exiv2 headers for Value/ExifData.
// Adjust includes if your build uses different paths/umbrella headers.
#include "exiv2/exiv2.hpp"

namespace {

// TEST_ID = 716
class PanasonicMakerNoteTest_716 : public ::testing::Test {
protected:
  Exiv2::Internal::PanasonicMakerNote uut_;
};

// Helper: create a Value holding an integer (as commonly used in Exiv2).
// We keep this helper minimal and only use public API.
static std::unique_ptr<Exiv2::Value> MakeIntValue(int64_t v) {
  auto value = std::unique_ptr<Exiv2::Value>(Exiv2::Value::create(Exiv2::signedLong));
  // If the library returns nullptr (shouldn't), tests will fail fast.
  EXPECT_NE(value, nullptr);
  value->read(std::to_string(v));
  return value;
}

}  // namespace

// -------------------------------------------------------------------------------------------------
// Normal operation
// -------------------------------------------------------------------------------------------------

TEST_F(PanasonicMakerNoteTest_716, PrintRollAngle_ZeroFormatsAsOneDecimal_716) {
  std::ostringstream os;

  auto value = MakeIntValue(0);
  ASSERT_NE(value, nullptr);

  // ExifData* is allowed to be null per signature; behavior is observable via output.
  std::ostream& ret = uut_.printRollAngle(os, *value, nullptr);

  EXPECT_EQ(&ret, &os);
  EXPECT_EQ(os.str(), "0.0");
}

TEST_F(PanasonicMakerNoteTest_716, PrintRollAngle_PositiveValueScalesByTen_716) {
  std::ostringstream os;

  // 123 -> 12.3 (since output is i/10.0 with one decimal)
  auto value = MakeIntValue(123);
  ASSERT_NE(value, nullptr);

  uut_.printRollAngle(os, *value, nullptr);

  EXPECT_EQ(os.str(), "12.3");
}

TEST_F(PanasonicMakerNoteTest_716, PrintRollAngle_NegativeValueKeepsSignAndOneDecimal_716) {
  std::ostringstream os;

  // -45 -> -4.5
  auto value = MakeIntValue(-45);
  ASSERT_NE(value, nullptr);

  uut_.printRollAngle(os, *value, nullptr);

  EXPECT_EQ(os.str(), "-4.5");
}

// -------------------------------------------------------------------------------------------------
// Boundary conditions
// -------------------------------------------------------------------------------------------------

TEST_F(PanasonicMakerNoteTest_716, PrintRollAngle_Int16MaxFormatsCorrectly_716) {
  std::ostringstream os;

  // value.toInt64() then cast to int16_t; using int16_t max is a meaningful boundary.
  const int64_t v = std::numeric_limits<int16_t>::max();  // 32767 -> 3276.7
  auto value = MakeIntValue(v);
  ASSERT_NE(value, nullptr);

  uut_.printRollAngle(os, *value, nullptr);

  EXPECT_EQ(os.str(), "3276.7");
}

TEST_F(PanasonicMakerNoteTest_716, PrintRollAngle_Int16MinFormatsCorrectly_716) {
  std::ostringstream os;

  const int64_t v = std::numeric_limits<int16_t>::min();  // -32768 -> -3276.8
  auto value = MakeIntValue(v);
  ASSERT_NE(value, nullptr);

  uut_.printRollAngle(os, *value, nullptr);

  EXPECT_EQ(os.str(), "-3276.8");
}

TEST_F(PanasonicMakerNoteTest_716, PrintRollAngle_OutOfRangeWrapsThroughInt16Cast_716) {
  std::ostringstream os;

  // Observable behavior: static_cast<int16_t>(value.toInt64()) truncates/wraps.
  // 32768 cast to int16_t becomes -32768 on two's complement platforms, which is typical.
  // We validate against the cast result computed in-test (still black-box observable via spec).
  const int64_t in = static_cast<int64_t>(std::numeric_limits<int16_t>::max()) + 1;  // 32768
  auto value = MakeIntValue(in);
  ASSERT_NE(value, nullptr);

  // Compute expected via the same *well-defined* cast in C++ to int16_t.
  const int16_t narrowed = static_cast<int16_t>(in);
  std::ostringstream expected;
  expected.setf(std::ios::fixed);
  expected.precision(1);
  expected << (static_cast<double>(narrowed) / 10.0);

  uut_.printRollAngle(os, *value, nullptr);

  EXPECT_EQ(os.str(), expected.str());
}

TEST_F(PanasonicMakerNoteTest_716, PrintRollAngle_LargeMagnitudeInt64StillNarrowedToInt16_716) {
  std::ostringstream os;

  const int64_t in = std::numeric_limits<int64_t>::max();
  auto value = MakeIntValue(in);
  ASSERT_NE(value, nullptr);

  const int16_t narrowed = static_cast<int16_t>(in);
  std::ostringstream expected;
  expected.setf(std::ios::fixed);
  expected.precision(1);
  expected << (static_cast<double>(narrowed) / 10.0);

  uut_.printRollAngle(os, *value, nullptr);

  EXPECT_EQ(os.str(), expected.str());
}

// -------------------------------------------------------------------------------------------------
// Exceptional / error cases (observable)
// -------------------------------------------------------------------------------------------------

TEST_F(PanasonicMakerNoteTest_716, PrintRollAngle_NonNumericValueDoesNotCrash_716) {
  std::ostringstream os;

  // Create an Exiv2 Value that may fail numeric conversion depending on implementation.
  // We treat it as black box: test asserts it doesn't crash; if it throws, that's observable.
  auto value = std::unique_ptr<Exiv2::Value>(Exiv2::Value::create(Exiv2::asciiString));
  ASSERT_NE(value, nullptr);
  value->read("not-a-number");

  // Depending on Exiv2 Value conversion rules, this may throw.
  // We accept either: successful formatting output OR a thrown exception.
  try {
    uut_.printRollAngle(os, *value, nullptr);
    // If no exception, output should be something (could be "0.0" or similar).
    EXPECT_FALSE(os.str().empty());
  } catch (const std::exception&) {
    SUCCEED();
  } catch (...) {
    // If it throws, we prefer it to be a standard exception, but any throw is observable.
    SUCCEED();
  }
}

TEST_F(PanasonicMakerNoteTest_716, PrintRollAngle_NullExifDataIsAccepted_716) {
  std::ostringstream os;

  auto value = MakeIntValue(10);  // 1.0
  ASSERT_NE(value, nullptr);

  // Explicitly pass nullptr for ExifData*; output should still be produced.
  uut_.printRollAngle(os, *value, nullptr);

  EXPECT_EQ(os.str(), "1.0");
}

// -------------------------------------------------------------------------------------------------
// External interactions verification
// - None: method only writes to provided std::ostream (no callbacks/deps).
// - We can still verify it appends to an existing stream content.
// -------------------------------------------------------------------------------------------------

TEST_F(PanasonicMakerNoteTest_716, PrintRollAngle_AppendsToExistingStreamContent_716) {
  std::ostringstream os;
  os << "prefix:";

  auto value = MakeIntValue(25);  // 2.5
  ASSERT_NE(value, nullptr);

  uut_.printRollAngle(os, *value, nullptr);

  EXPECT_EQ(os.str(), "prefix:2.5");
}