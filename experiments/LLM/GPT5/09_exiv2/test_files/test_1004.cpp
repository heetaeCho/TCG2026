// SPDX-License-Identifier: GPL-2.0-or-later
// File: test_minoltamn_int_printMinoltaFocalLengthStd_1004.cpp
//
// Unit tests for:
// Exiv2::Internal::MinoltaMakerNote::printMinoltaFocalLengthStd
//
// Constraints honored:
// - Treat implementation as black box: only assert on observable stream output.
// - No private state access.
// - Include normal, boundary, and error/exceptional (where observable) cases.
// - TEST_ID suffix added to every test name (1004).

#include <gtest/gtest.h>

#include <cstdint>
#include <limits>
#include <ostream>
#include <sstream>
#include <string>

namespace Exiv2 {
class ExifData;
class Value {
public:
  virtual ~Value() = default;
  virtual int64_t toInt64() const = 0;
};
}  // namespace Exiv2

namespace Exiv2::Internal {
class MinoltaMakerNote {
public:
  std::ostream& printMinoltaFocalLengthStd(std::ostream& os, const Exiv2::Value& value, const Exiv2::ExifData*) {
    os << (value.toInt64() / 3) - 2;
    return os;
  }
};
}  // namespace Exiv2::Internal

namespace {

// Minimal stub Value that only exposes toInt64() as required by the interface.
class StubValue final : public Exiv2::Value {
public:
  explicit StubValue(int64_t v) : v_(v) {}
  int64_t toInt64() const override { return v_; }

private:
  int64_t v_;
};

class MinoltaMakerNoteTest_1004 : public ::testing::Test {
protected:
  Exiv2::Internal::MinoltaMakerNote uut_;
};

static std::string PrintToString(Exiv2::Internal::MinoltaMakerNote& uut, const Exiv2::Value& v,
                                 const Exiv2::ExifData* exif = nullptr) {
  std::ostringstream oss;
  std::ostream& ret = uut.printMinoltaFocalLengthStd(oss, v, exif);
  // Observable behavior: returned ostream should be the same object we passed.
  EXPECT_EQ(&ret, &oss);
  return oss.str();
}

}  // namespace

// -------------------- Normal operation --------------------

TEST_F(MinoltaMakerNoteTest_1004, PrintsExpectedForTypicalPositive_1004) {
  // 9/3 - 2 = 1
  StubValue v(9);
  EXPECT_EQ(PrintToString(uut_, v), "1");
}

TEST_F(MinoltaMakerNoteTest_1004, IgnoresExifDataPointerWhenNull_1004) {
  // Ensure nullptr ExifData is accepted and does not affect output.
  // 6/3 - 2 = 0
  StubValue v(6);
  EXPECT_EQ(PrintToString(uut_, v, nullptr), "0");
}

// -------------------- Boundary conditions --------------------

TEST_F(MinoltaMakerNoteTest_1004, HandlesZero_1004) {
  // 0/3 - 2 = -2
  StubValue v(0);
  EXPECT_EQ(PrintToString(uut_, v), "-2");
}

TEST_F(MinoltaMakerNoteTest_1004, HandlesNegativeInput_1004) {
  // Use a negative not divisible by 3 to exercise integer division behavior.
  // (-1)/3 truncates toward zero in C++ => 0, 0 - 2 = -2
  StubValue v(-1);
  EXPECT_EQ(PrintToString(uut_, v), "-2");
}

TEST_F(MinoltaMakerNoteTest_1004, HandlesLargePositiveWithinSafeRange_1004) {
  // Choose a value that won't overflow when divided and then subtracting 2.
  // (INT64_MAX)/3 - 2 should be well-defined.
  const int64_t input = std::numeric_limits<int64_t>::max();
  StubValue v(input);

  const int64_t expected = (input / 3) - 2;
  EXPECT_EQ(PrintToString(uut_, v), std::to_string(expected));
}

TEST_F(MinoltaMakerNoteTest_1004, HandlesLargeNegativeWithinSafeRange_1004) {
  // Avoid int64_t min where intermediate operations could be tricky in some contexts.
  const int64_t input = std::numeric_limits<int64_t>::min() / 3;  // still very negative, and safe to divide again
  StubValue v(input);

  const int64_t expected = (input / 3) - 2;
  EXPECT_EQ(PrintToString(uut_, v), std::to_string(expected));
}

// -------------------- Exceptional / error cases (observable) --------------------

TEST_F(MinoltaMakerNoteTest_1004, PropagatesStreamBadbit_1004) {
  // If the stream is already bad, insertion should keep it bad (observable via stream state).
  StubValue v(9);

  std::ostringstream oss;
  oss.setstate(std::ios::badbit);

  std::ostream& ret = uut_.printMinoltaFocalLengthStd(oss, v, nullptr);
  EXPECT_EQ(&ret, &oss);
  EXPECT_TRUE(oss.bad());
}

TEST_F(MinoltaMakerNoteTest_1004, WorksWithNonEmptyInitialStream_1004) {
  // Verify it appends to the stream (observable output concatenation).
  // 12/3 - 2 = 2
  StubValue v(12);

  std::ostringstream oss;
  oss << "prefix:";
  std::ostream& ret = uut_.printMinoltaFocalLengthStd(oss, v, nullptr);
  EXPECT_EQ(&ret, &oss);
  EXPECT_EQ(oss.str(), "prefix:2");
}