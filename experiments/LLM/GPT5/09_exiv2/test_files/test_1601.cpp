// TEST_ID 1601
// Unit tests for Exiv2::Internal::SonyMakerNote::printExposureStandardAdjustment
//
// Constraints honored:
// - Treat implementation as black box
// - Test only observable behavior via public interface
// - No access to private/internal state

#include <gtest/gtest.h>

#include <exiv2/exif.hpp>
#include <exiv2/value.hpp>

// The class lives in Exiv2::Internal and is implemented in sonymn_int.cpp.
// In the real codebase, this is typically declared in an internal header.
#include "sonymn_int.hpp"

#include <sstream>
#include <string>

namespace {

class SonyMakerNoteTest_1601 : public ::testing::Test {
 protected:
  static std::string StreamValue(const Exiv2::Value& v) {
    std::ostringstream oss;
    oss << v;
    return oss.str();
  }

  static std::unique_ptr<Exiv2::Value> MakeValue(Exiv2::TypeId type, const std::string& text) {
    auto v = Exiv2::Value::create(type);
    EXPECT_TRUE(static_cast<bool>(v));
    if (v) {
      // Value::read() is the public API to parse textual representation.
      v->read(text);
    }
    return v;
  }
};

TEST_F(SonyMakerNoteTest_1601, ParenthesizesWhenCountIsNotOne_1601) {
  Exiv2::Internal::SonyMakerNote mn;

  auto v = MakeValue(Exiv2::signedRational, "1/2 3/4");  // count != 1
  ASSERT_TRUE(v);

  std::ostringstream os;
  mn.printExposureStandardAdjustment(os, *v, nullptr);

  const std::string expected = "(" + StreamValue(*v) + ")";
  EXPECT_EQ(os.str(), expected);
}

TEST_F(SonyMakerNoteTest_1601, ParenthesizesWhenTypeIsNotSignedRational_1601) {
  Exiv2::Internal::SonyMakerNote mn;

  auto v = MakeValue(Exiv2::unsignedRational, "1/2");  // typeId != signedRational
  ASSERT_TRUE(v);
  ASSERT_EQ(v->count(), 1U); // ensure this case is "type mismatch" specifically

  std::ostringstream os;
  mn.printExposureStandardAdjustment(os, *v, nullptr);

  const std::string expected = "(" + StreamValue(*v) + ")";
  EXPECT_EQ(os.str(), expected);
}

TEST_F(SonyMakerNoteTest_1601, FormatsSignedRationalWithOneDecimal_1601) {
  Exiv2::Internal::SonyMakerNote mn;

  auto v = MakeValue(Exiv2::signedRational, "1/2");
  ASSERT_TRUE(v);
  ASSERT_EQ(v->count(), 1U);

  std::ostringstream os;
  mn.printExposureStandardAdjustment(os, *v, nullptr);

  EXPECT_EQ(os.str(), "0.5");
}

TEST_F(SonyMakerNoteTest_1601, RoundsToOneDecimal_1601) {
  Exiv2::Internal::SonyMakerNote mn;

  // 1/3 = 0.333..., should round to one decimal => "0.3"
  auto v = MakeValue(Exiv2::signedRational, "1/3");
  ASSERT_TRUE(v);
  ASSERT_EQ(v->count(), 1U);

  std::ostringstream os;
  mn.printExposureStandardAdjustment(os, *v, nullptr);

  EXPECT_EQ(os.str(), "0.3");
}

TEST_F(SonyMakerNoteTest_1601, HandlesNegativeSignedRational_1601) {
  Exiv2::Internal::SonyMakerNote mn;

  auto v = MakeValue(Exiv2::signedRational, "-1/2");
  ASSERT_TRUE(v);
  ASSERT_EQ(v->count(), 1U);

  std::ostringstream os;
  mn.printExposureStandardAdjustment(os, *v, nullptr);

  EXPECT_EQ(os.str(), "-0.5");
}

TEST_F(SonyMakerNoteTest_1601, BoundaryLargeNumeratorPrintsWithDecimal_1601) {
  Exiv2::Internal::SonyMakerNote mn;

  auto v = MakeValue(Exiv2::signedRational, "2147483647/1");
  ASSERT_TRUE(v);
  ASSERT_EQ(v->count(), 1U);

  std::ostringstream os;
  mn.printExposureStandardAdjustment(os, *v, nullptr);

  EXPECT_EQ(os.str(), "2147483647.0");
}

}  // namespace