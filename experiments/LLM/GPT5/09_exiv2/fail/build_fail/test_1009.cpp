// ***************************************************************** -*- C++ -*-
// Unit tests for Exiv2::Internal::MinoltaMakerNote::printMinoltaBrightnessStd
// *****************************************************************
//
// Constraints respected:
// - Treat implementation as black box (test only observable stream output).
// - Do not access private/internal state.
// - No internal logic re-implementation beyond verifying observable behavior.
//
// File under test: ./TestProjects/exiv2/src/minoltamn_int.cpp

#include <gtest/gtest.h>

#include <cstdint>
#include <ostream>
#include <sstream>
#include <string>

#include <exiv2/exif.hpp>

namespace {

// A Value implementation that lets us control toInt64() deterministically.
// This is an "external collaborator" for the method under test (passed in as const Value&),
// so providing a small test double is acceptable; we are not simulating MinoltaMakerNote internals.
class FakeValue final : public Exiv2::Value {
 public:
  explicit FakeValue(int64_t v) : v_(v) {}
  ~FakeValue() override = default;

  // ---- Value interface ----
  int read(const std::string&) override { return 0; }
  int read(const Exiv2::byte*, size_t, Exiv2::ByteOrder) override { return 0; }
  int setDataArea(const Exiv2::byte*, size_t) override { return 0; }

  long count() const override { return 1; }
  long size() const override { return 0; }
  Exiv2::TypeId typeId() const override { return Exiv2::invalidTypeId; }

  Exiv2::Value::AutoPtr clone() const override { return Exiv2::Value::AutoPtr(new FakeValue(v_)); }

  std::ostream& write(std::ostream& os) const override { os << v_; return os; }

  int64_t toInt64(long) const override { return v_; }
  int64_t toInt64() const override { return v_; }

 private:
  int64_t v_;
};

class MinoltaMakerNoteTest_1009 : public ::testing::Test {
 protected:
  Exiv2::Internal::MinoltaMakerNote sut_;
};

static std::string CallToString(Exiv2::Internal::MinoltaMakerNote& sut, int64_t input,
                                const Exiv2::ExifData* exif = nullptr) {
  FakeValue v(input);
  std::ostringstream os;
  sut.printMinoltaBrightnessStd(os, v, exif);
  return os.str();
}

}  // namespace

// Normal operation: typical positive value produces some integral output and returns same stream.
TEST_F(MinoltaMakerNoteTest_1009, PrintsExpectedForTypicalValue_1009) {
  FakeValue v(80);  // chosen to be divisible by 8 for a stable expected integer format
  std::ostringstream os;

  std::ostream& ret = sut_.printMinoltaBrightnessStd(os, v, nullptr);

  EXPECT_EQ(&ret, &os) << "Function should return the same stream it wrote to.";
  EXPECT_EQ(os.str(), "4") << "Expected stable formatted output for a typical value.";
}

// Boundary: zero value.
TEST_F(MinoltaMakerNoteTest_1009, PrintsExpectedForZero_1009) {
  EXPECT_EQ(CallToString(sut_, 0), "-6");
}

// Boundary: divisible-by-8 negative value.
TEST_F(MinoltaMakerNoteTest_1009, PrintsExpectedForNegativeDivisibleBy8_1009) {
  EXPECT_EQ(CallToString(sut_, -8), "-7");
}

// Boundary: non-divisible positive value; verifies integer formatting (no decimals) is produced.
TEST_F(MinoltaMakerNoteTest_1009, PrintsIntegralTextForNonDivisiblePositive_1009) {
  const std::string out = CallToString(sut_, 9);
  // Observable behavior: output is textual representation of an integer.
  // We don't assume rounding policy beyond "it prints something parseable as an integer".
  ASSERT_FALSE(out.empty());
  // Accept leading '-' only; rest digits.
  size_t i = (out[0] == '-') ? 1u : 0u;
  ASSERT_LT(i, out.size());
  for (; i < out.size(); ++i) {
    EXPECT_TRUE(out[i] >= '0' && out[i] <= '9') << "Non-integer character found: " << out;
  }
}

// Boundary: non-divisible negative value; still outputs an integer string.
TEST_F(MinoltaMakerNoteTest_1009, PrintsIntegralTextForNonDivisibleNegative_1009) {
  const std::string out = CallToString(sut_, -9);
  ASSERT_FALSE(out.empty());
  size_t i = (out[0] == '-') ? 1u : 0u;
  ASSERT_LT(i, out.size());
  for (; i < out.size(); ++i) {
    EXPECT_TRUE(out[i] >= '0' && out[i] <= '9') << "Non-integer character found: " << out;
  }
}

// External interaction: ExifData* is accepted; behavior should be consistent for same Value
// regardless of whether ExifData pointer is null or not (observable via output).
TEST_F(MinoltaMakerNoteTest_1009, OutputDoesNotDependOnExifPointerPresence_1009) {
  Exiv2::ExifData exif;
  const std::string outNull = CallToString(sut_, 80, nullptr);
  const std::string outNonNull = CallToString(sut_, 80, &exif);
  EXPECT_EQ(outNull, outNonNull);
}

// Exceptional/error case (observable): using very large magnitude values should not crash;
// output should still be some integer string.
TEST_F(MinoltaMakerNoteTest_1009, LargeMagnitudeInputProducesSomeOutput_1009) {
  const int64_t big = (std::numeric_limits<int64_t>::max)();
  const std::string out = CallToString(sut_, big);
  EXPECT_FALSE(out.empty());
  // Should look like an integer.
  size_t i = (out[0] == '-') ? 1u : 0u;
  ASSERT_LT(i, out.size());
  for (; i < out.size(); ++i) {
    EXPECT_TRUE(out[i] >= '0' && out[i] <= '9');
  }
}