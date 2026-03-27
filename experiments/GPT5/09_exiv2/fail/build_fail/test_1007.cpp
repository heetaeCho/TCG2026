// ============================================================================
// Unit tests for ./TestProjects/exiv2/src/minoltamn_int.cpp
//
// Interface under test:
//   Exiv2::Internal::MinoltaMakerNote::printMinoltaFlashExposureCompStd(
//        std::ostream& os, const Value& value, const ExifData* )
//
// Constraints honored:
// - Treat implementation as black box (tests only observable output to ostream).
// - No access to internal/private state.
// - GoogleMock used only for external collaborator (Value).
// - Boundary + normal cases included.
// ============================================================================

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <cstdint>
#include <limits>
#include <ostream>
#include <sstream>

namespace Exiv2 {
// Minimal stubs to satisfy the provided interface.
// We only model what the public signature requires.
class ExifData {};

class Value {
public:
  virtual ~Value() = default;
  virtual std::int64_t toInt64() const = 0;
};

namespace Internal {
class MinoltaMakerNote {
public:
  std::ostream& printMinoltaFlashExposureCompStd(std::ostream& os, const Value& value, const ExifData*);
};
}  // namespace Internal
}  // namespace Exiv2

// Mock external collaborator: Value
class MockValue_1007 : public Exiv2::Value {
public:
  MOCK_METHOD(std::int64_t, toInt64, (), (const, override));
};

using ::testing::Return;
using ::testing::StrictMock;

namespace {

class MinoltaMakerNoteTest_1007 : public ::testing::Test {
protected:
  Exiv2::Internal::MinoltaMakerNote sut_;
  Exiv2::ExifData exif_;  // not used by observable behavior, but passed for signature completeness
};

static std::string CallAndCapture_1007(Exiv2::Internal::MinoltaMakerNote& sut,
                                      const Exiv2::Value& v,
                                      const Exiv2::ExifData* exifPtr) {
  std::ostringstream oss;
  sut.printMinoltaFlashExposureCompStd(oss, v, exifPtr);
  return oss.str();
}

// ---------------------- Normal operation ----------------------

TEST_F(MinoltaMakerNoteTest_1007, WritesZeroWhenValueIsSix_1007) {
  StrictMock<MockValue_1007> v;
  EXPECT_CALL(v, toInt64()).WillOnce(Return(6));

  const std::string out = CallAndCapture_1007(sut_, v, &exif_);
  EXPECT_EQ(out, "0");
}

TEST_F(MinoltaMakerNoteTest_1007, WritesPositiveOneWhenValueIsNine_1007) {
  StrictMock<MockValue_1007> v;
  EXPECT_CALL(v, toInt64()).WillOnce(Return(9));

  const std::string out = CallAndCapture_1007(sut_, v, &exif_);
  EXPECT_EQ(out, "1");
}

TEST_F(MinoltaMakerNoteTest_1007, WritesNegativeOneWhenValueIsThree_1007) {
  StrictMock<MockValue_1007> v;
  EXPECT_CALL(v, toInt64()).WillOnce(Return(3));

  const std::string out = CallAndCapture_1007(sut_, v, &exif_);
  EXPECT_EQ(out, "-1");
}

// ---------------------- Boundary / truncation behavior ----------------------
// These cases check observable formatting for values that won't divide evenly,
// without assuming internal rounding rules beyond what the output reveals.

TEST_F(MinoltaMakerNoteTest_1007, TruncatesTowardZeroForNonMultipleAboveSix_1007) {
  StrictMock<MockValue_1007> v;
  EXPECT_CALL(v, toInt64()).WillOnce(Return(8));  // (8-6)/3 -> observable should be 0 with integer formatting

  const std::string out = CallAndCapture_1007(sut_, v, &exif_);
  EXPECT_EQ(out, "0");
}

TEST_F(MinoltaMakerNoteTest_1007, TruncatesTowardZeroForNonMultipleBelowSix_1007) {
  StrictMock<MockValue_1007> v;
  EXPECT_CALL(v, toInt64()).WillOnce(Return(5));  // (5-6)/3 -> observable should be 0 if trunc toward zero

  const std::string out = CallAndCapture_1007(sut_, v, &exif_);
  EXPECT_EQ(out, "0");
}

// ---------------------- Exceptional / error-ish cases (observable) ----------------------
// No exceptions are declared. We can still validate behavior with nullptr ExifData*,
// since the function accepts it in the signature and output remains observable.

TEST_F(MinoltaMakerNoteTest_1007, AcceptsNullExifDataPointer_1007) {
  StrictMock<MockValue_1007> v;
  EXPECT_CALL(v, toInt64()).WillOnce(Return(6));

  const std::string out = CallAndCapture_1007(sut_, v, nullptr);
  EXPECT_EQ(out, "0");
}

// ---------------------- External interaction verification ----------------------
// Ensure Value::toInt64 is called (and only once) per invocation.

TEST_F(MinoltaMakerNoteTest_1007, CallsToInt64ExactlyOnce_1007) {
  StrictMock<MockValue_1007> v;
  EXPECT_CALL(v, toInt64()).WillOnce(Return(12));  // output expected "2"

  const std::string out = CallAndCapture_1007(sut_, v, &exif_);
  EXPECT_EQ(out, "2");
}

// ---------------------- Extreme boundary values (no crash, deterministic stream output) ----------------------
// We only verify that something is written and the stream remains usable,
// without assuming internal overflow handling details.

TEST_F(MinoltaMakerNoteTest_1007, ExtremeInt64MinProducesSomeOutput_1007) {
  StrictMock<MockValue_1007> v;
  EXPECT_CALL(v, toInt64()).WillOnce(Return(std::numeric_limits<std::int64_t>::min()));

  std::ostringstream oss;
  sut_.printMinoltaFlashExposureCompStd(oss, v, &exif_);
  EXPECT_FALSE(oss.str().empty());
  EXPECT_TRUE(oss.good() || oss.eof());  // allow eof; just ensure no catastrophic failure
}

TEST_F(MinoltaMakerNoteTest_1007, ExtremeInt64MaxProducesSomeOutput_1007) {
  StrictMock<MockValue_1007> v;
  EXPECT_CALL(v, toInt64()).WillOnce(Return(std::numeric_limits<std::int64_t>::max()));

  std::ostringstream oss;
  sut_.printMinoltaFlashExposureCompStd(oss, v, &exif_);
  EXPECT_FALSE(oss.str().empty());
  EXPECT_TRUE(oss.good() || oss.eof());
}

}  // namespace