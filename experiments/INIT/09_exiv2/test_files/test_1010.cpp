// ***************************************************************** -*- C++ -*-
// Unit tests for Exiv2::Internal::MinoltaMakerNote
// File under test: ./TestProjects/exiv2/src/minoltamn_int.cpp
//
// Constraints respected:
// - Treat implementation as black box (test only observable behavior via interface)
// - No access to private state
// - Use gtest only (no external collaborators to mock here)
//
// TEST_ID: 1010
// *****************************************************************

#include <gtest/gtest.h>

#include <cmath>
#include <cstdint>
#include <iomanip>
#include <limits>
#include <ostream>
#include <sstream>
#include <string>

namespace Exiv2 {
// Minimal stand-ins to satisfy the interface used by the function under test.
// We do NOT re-implement Minolta logic; we only supply a Value with toInt64().
struct ExifData {
  // Opaque for these tests; only used as const ExifData* parameter.
};

class Value {
 public:
  virtual ~Value() = default;
  virtual int64_t toInt64() const = 0;
};
}  // namespace Exiv2

namespace Exiv2::Internal {

// Declaration must match the provided partial implementation signature.
class MinoltaMakerNote {
 public:
  std::ostream& printMinoltaExposureManualBias5D(std::ostream& os, const Exiv2::Value& value,
                                                const Exiv2::ExifData*);
};

}  // namespace Exiv2::Internal

// Test helper: a concrete Value that returns a known int64.
namespace {
class FakeValueInt64 final : public Exiv2::Value {
 public:
  explicit FakeValueInt64(int64_t v) : v_(v) {}
  int64_t toInt64() const override { return v_; }

 private:
  int64_t v_;
};

// Match the formatting style in a black-box way: compare the exact produced string.
// The function is expected to write a fixed two-decimal string representation.
static std::string CallAndGetString(int64_t raw) {
  Exiv2::Internal::MinoltaMakerNote mn;
  FakeValueInt64 v(raw);
  std::ostringstream oss;
  // ExifData* is not used for observable behavior in this interface; pass nullptr.
  mn.printMinoltaExposureManualBias5D(oss, v, nullptr);
  return oss.str();
}

// Helper to compute the reference string with standard iostream formatting.
// This does NOT infer internal logic beyond what is observable/explicit in code:
// two decimals, based on (raw - 128) / 24 as float.
static std::string ReferenceString(int64_t raw) {
  const float f = static_cast<float>(raw - 128) / 24.0f;
  std::ostringstream oss;
  oss.setf(std::ios::fixed);
  oss << std::setprecision(2) << f;
  return oss.str();
}
}  // namespace

// Test fixture
class MinoltaMakerNoteTest_1010 : public ::testing::Test {};

// ------------------------- Normal operation -------------------------

TEST_F(MinoltaMakerNoteTest_1010, WritesExpectedTwoDecimalString_ForZeroBiasAt128_1010) {
  // raw=128 should yield "0.00" if formatting is fixed to two decimals.
  EXPECT_EQ(CallAndGetString(128), ReferenceString(128));
}

TEST_F(MinoltaMakerNoteTest_1010, WritesExpectedString_ForCommonPositiveValue_1010) {
  // A typical value above 128.
  const int64_t raw = 152;
  EXPECT_EQ(CallAndGetString(raw), ReferenceString(raw));
}

TEST_F(MinoltaMakerNoteTest_1010, WritesExpectedString_ForCommonNegativeValue_1010) {
  // A typical value below 128.
  const int64_t raw = 104;
  EXPECT_EQ(CallAndGetString(raw), ReferenceString(raw));
}

// ------------------------- Boundary conditions -------------------------

TEST_F(MinoltaMakerNoteTest_1010, HandlesLowestPracticalSmallValue_ZeroRaw_1010) {
  // raw=0 -> negative output; verify formatting and computation path remain stable.
  EXPECT_EQ(CallAndGetString(0), ReferenceString(0));
}

TEST_F(MinoltaMakerNoteTest_1010, HandlesLargePositiveRawValue_1010) {
  // Use a large raw value that is still representable in float without INF.
  const int64_t raw = 1'000'000;
  const auto out = CallAndGetString(raw);
  const auto ref = ReferenceString(raw);
  EXPECT_EQ(out, ref);
}

TEST_F(MinoltaMakerNoteTest_1010, ProducesExactlyTwoDigitsAfterDecimalPoint_1010) {
  const std::string out = CallAndGetString(129);  // should be small positive ~0.04
  const auto dot = out.find('.');
  ASSERT_NE(dot, std::string::npos) << "Expected a decimal point in output: " << out;
  ASSERT_GE(out.size(), dot + 3) << "Expected at least two digits after decimal: " << out;
  EXPECT_TRUE(std::isdigit(static_cast<unsigned char>(out[dot + 1])));
  EXPECT_TRUE(std::isdigit(static_cast<unsigned char>(out[dot + 2])));

  // Ensure there isn't a third fractional digit (fixed precision 2).
  if (out.size() > dot + 3) {
    EXPECT_FALSE(std::isdigit(static_cast<unsigned char>(out[dot + 3])))
        << "Expected exactly two digits after decimal: " << out;
  }
}

// ------------------------- Exceptional / error cases (observable) -------------------------

TEST_F(MinoltaMakerNoteTest_1010, AcceptsNullExifDataPointer_1010) {
  // The interface allows ExifData*; passing nullptr should not crash and should still output.
  Exiv2::Internal::MinoltaMakerNote mn;
  FakeValueInt64 v(200);
  std::ostringstream oss;
  mn.printMinoltaExposureManualBias5D(oss, v, nullptr);
  EXPECT_EQ(oss.str(), ReferenceString(200));
}

TEST_F(MinoltaMakerNoteTest_1010, WorksWithNegativeRawInput_1010) {
  // Negative raw values are possible for int64; verify output is still produced.
  const int64_t raw = -1;
  EXPECT_EQ(CallAndGetString(raw), ReferenceString(raw));
}

// ------------------------- External interactions -------------------------

TEST_F(MinoltaMakerNoteTest_1010, ReturnsSameOstreamReference_1010) {
  Exiv2::Internal::MinoltaMakerNote mn;
  FakeValueInt64 v(128);
  std::ostringstream oss;

  std::ostream& ret = mn.printMinoltaExposureManualBias5D(oss, v, nullptr);
  EXPECT_EQ(&ret, &oss);
}

TEST_F(MinoltaMakerNoteTest_1010, AppendsToExistingStreamContent_1010) {
  Exiv2::Internal::MinoltaMakerNote mn;
  FakeValueInt64 v(152);
  std::ostringstream oss;
  oss << "prefix:";

  mn.printMinoltaExposureManualBias5D(oss, v, nullptr);

  EXPECT_EQ(oss.str(), std::string("prefix:") + ReferenceString(152));
}