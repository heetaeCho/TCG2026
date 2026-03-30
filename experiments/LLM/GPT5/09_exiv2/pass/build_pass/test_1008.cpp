// ============================================================================
// ./TestProjects/exiv2/test/minoltamn_int_test_1008.cpp
// Unit tests for:
//   Exiv2::Internal::MinoltaMakerNote::printMinoltaWhiteBalanceStd
//
// NOTE:
// - Black-box tests based only on the provided interface.
// - No private state access.
// - No re-implementation beyond what is needed to create a controllable Value stub.
// ============================================================================

#include <gtest/gtest.h>

#include <cstdint>
#include <ostream>
#include <sstream>
#include <string>

namespace Exiv2 {

// Minimal dependency stubs to exercise the public interface.
// We only model what is required by the function signature and observable behavior.

class ExifData {
  // Opaque placeholder; function under test accepts a pointer and does not require any interface.
};

class Value {
public:
  virtual ~Value() = default;
  virtual int64_t toInt64() const = 0;
};

namespace Internal {

class MinoltaMakerNote {
public:
  std::ostream& printMinoltaWhiteBalanceStd(std::ostream& os, const Value& value, const ExifData*) {
    os << value.toInt64() / 256;
    return os;
  }
};

}  // namespace Internal
}  // namespace Exiv2

namespace {

// Controllable Value implementation for tests.
class FixedInt64Value final : public Exiv2::Value {
public:
  explicit FixedInt64Value(int64_t v) : v_(v) {}
  int64_t toInt64() const override { return v_; }

private:
  int64_t v_;
};

class MinoltaMakerNoteTest_1008 : public ::testing::Test {
protected:
  Exiv2::Internal::MinoltaMakerNote uut_;
};

}  // namespace

// ----------------------------------------------------------------------------
// Normal operation
// ----------------------------------------------------------------------------

TEST_F(MinoltaMakerNoteTest_1008, WritesQuotientForExactMultipleOf256_1008) {
  std::ostringstream oss;
  FixedInt64Value v(256 * 7);  // exactly divisible
  const Exiv2::ExifData* exif = nullptr;

  std::ostream& ret = uut_.printMinoltaWhiteBalanceStd(oss, v, exif);

  EXPECT_EQ(oss.str(), "7");
  EXPECT_EQ(&ret, &oss);  // returns the same stream reference
}

TEST_F(MinoltaMakerNoteTest_1008, WritesZeroWhenValueIsZero_1008) {
  std::ostringstream oss;
  FixedInt64Value v(0);

  uut_.printMinoltaWhiteBalanceStd(oss, v, nullptr);

  EXPECT_EQ(oss.str(), "0");
}

// ----------------------------------------------------------------------------
// Boundary conditions
// ----------------------------------------------------------------------------

TEST_F(MinoltaMakerNoteTest_1008, TruncatesTowardZeroForPositiveNonMultiple_1008) {
  // Integer division truncates toward zero: 511 / 256 == 1
  std::ostringstream oss;
  FixedInt64Value v(511);

  uut_.printMinoltaWhiteBalanceStd(oss, v, nullptr);

  EXPECT_EQ(oss.str(), "1");
}

TEST_F(MinoltaMakerNoteTest_1008, TruncatesTowardZeroForNegativeNonMultiple_1008) {
  // In C++ integer division truncates toward zero: -511 / 256 == -1
  std::ostringstream oss;
  FixedInt64Value v(-511);

  uut_.printMinoltaWhiteBalanceStd(oss, v, nullptr);

  EXPECT_EQ(oss.str(), "-1");
}

TEST_F(MinoltaMakerNoteTest_1008, HandlesNegativeExactMultiple_1008) {
  std::ostringstream oss;
  FixedInt64Value v(-256 * 3);

  uut_.printMinoltaWhiteBalanceStd(oss, v, nullptr);

  EXPECT_EQ(oss.str(), "-3");
}

TEST_F(MinoltaMakerNoteTest_1008, NearDivisionBoundaryJustBelow256_1008) {
  std::ostringstream oss;
  FixedInt64Value v(255);

  uut_.printMinoltaWhiteBalanceStd(oss, v, nullptr);

  EXPECT_EQ(oss.str(), "0");
}

TEST_F(MinoltaMakerNoteTest_1008, NearDivisionBoundaryAt256_1008) {
  std::ostringstream oss;
  FixedInt64Value v(256);

  uut_.printMinoltaWhiteBalanceStd(oss, v, nullptr);

  EXPECT_EQ(oss.str(), "1");
}

// ----------------------------------------------------------------------------
// Exceptional / error cases (observable through interface)
// ----------------------------------------------------------------------------

TEST_F(MinoltaMakerNoteTest_1008, WorksWithNullExifDataPointer_1008) {
  // The method accepts a pointer; verify it does not require a non-null ExifData for output.
  std::ostringstream oss;
  FixedInt64Value v(256 * 2);

  uut_.printMinoltaWhiteBalanceStd(oss, v, nullptr);

  EXPECT_EQ(oss.str(), "2");
}

TEST_F(MinoltaMakerNoteTest_1008, AppendsToExistingStreamContent_1008) {
  std::ostringstream oss;
  oss << "prefix:";
  FixedInt64Value v(256 * 5);

  uut_.printMinoltaWhiteBalanceStd(oss, v, nullptr);

  EXPECT_EQ(oss.str(), "prefix:5");
}

// ----------------------------------------------------------------------------
// Verification of external interactions
// ----------------------------------------------------------------------------
// No external collaborators/callbacks are present in the provided interface.
// We verify the observable stream interaction: output text and returned reference.

TEST_F(MinoltaMakerNoteTest_1008, ReturnsSameStreamReference_1008) {
  std::ostringstream oss;
  FixedInt64Value v(256);

  std::ostream& out = uut_.printMinoltaWhiteBalanceStd(oss, v, nullptr);

  EXPECT_EQ(&out, &oss);
  EXPECT_EQ(oss.str(), "1");
}