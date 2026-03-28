// =================================================================================================
// TEST_ID: 712
// File: ./TestProjects/exiv2/src/panasonicmn_int.cpp (unit tests)
// =================================================================================================

#include <gtest/gtest.h>

#include <cstdint>
#include <ostream>
#include <sstream>
#include <string>

// Exiv2 headers (adjust include paths if your build uses different public headers)
#include "exif.hpp"
#include "value.hpp"

namespace {

// A tiny helper that matches the observable contract used by PanasonicMakerNote::print0x003c:
// - Uses Value::toInt64() for branching
// - Streams either translated string via N_ macro (compile-time marker) or the Value itself
//
// NOTE: We are NOT re-implementing any hidden logic beyond what is explicitly shown in the provided snippet.
static std::string PrintPanasonic0x003cViaClass(Exiv2::Internal::PanasonicMakerNote& mn,
                                                const Exiv2::Value& v) {
  std::ostringstream oss;
  mn.print0x003c(oss, v, /*ExifData*/ nullptr);
  return oss.str();
}

// Builds a signed long Value (widely supported by Exiv2 Value factory).
static Exiv2::Value::UniquePtr MakeSLongValue(int32_t x) {
  // Value::create takes a TypeId; signedLong is commonly used for integral tests.
  Exiv2::Value::UniquePtr val = Exiv2::Value::create(Exiv2::signedLong);
  val->read(std::to_string(x));
  return val;
}

}  // namespace

class PanasonicMakerNotePrint0x003cTest_712 : public ::testing::Test {
 protected:
  Exiv2::Internal::PanasonicMakerNote mn_;
};

TEST_F(PanasonicMakerNotePrint0x003cTest_712, PrintsIntelligentIsoFor65534_712) {
  // 65534 fits in int32_t.
  auto v = MakeSLongValue(65534);
  ASSERT_NE(v.get(), nullptr);

  const std::string out = PrintPanasonic0x003cViaClass(mn_, *v);

  // The code prints N_("Intelligent ISO") for 65534. In practice N_ often expands to the literal.
  EXPECT_EQ(out, "Intelligent ISO");
}

TEST_F(PanasonicMakerNotePrint0x003cTest_712, PrintsNaFor65535_712) {
  // 65535 fits in int32_t.
  auto v = MakeSLongValue(65535);
  ASSERT_NE(v.get(), nullptr);

  const std::string out = PrintPanasonic0x003cViaClass(mn_, *v);

  // The code prints N_("n/a") for 65535.
  EXPECT_EQ(out, "n/a");
}

TEST_F(PanasonicMakerNotePrint0x003cTest_712, StreamsValueForOtherNumbers_712) {
  auto v = MakeSLongValue(123);
  ASSERT_NE(v.get(), nullptr);

  const std::string out = PrintPanasonic0x003cViaClass(mn_, *v);

  // For default: os << value; so output should match streaming the value itself.
  std::ostringstream expected;
  expected << *v;
  EXPECT_EQ(out, expected.str());
}

TEST_F(PanasonicMakerNotePrint0x003cTest_712, StreamsNegativeValueForOtherNumbers_712) {
  auto v = MakeSLongValue(-1);
  ASSERT_NE(v.get(), nullptr);

  const std::string out = PrintPanasonic0x003cViaClass(mn_, *v);

  std::ostringstream expected;
  expected << *v;
  EXPECT_EQ(out, expected.str());
}

TEST_F(PanasonicMakerNotePrint0x003cTest_712, BoundaryAroundSpecialCases_712) {
  // Boundary checks around 65534/65535:
  // 65533 -> default
  // 65534 -> Intelligent ISO
  // 65535 -> n/a
  auto v_65533 = MakeSLongValue(65533);
  auto v_65534 = MakeSLongValue(65534);
  auto v_65535 = MakeSLongValue(65535);
  ASSERT_NE(v_65533.get(), nullptr);
  ASSERT_NE(v_65534.get(), nullptr);
  ASSERT_NE(v_65535.get(), nullptr);

  {
    const std::string out = PrintPanasonic0x003cViaClass(mn_, *v_65533);
    std::ostringstream expected;
    expected << *v_65533;
    EXPECT_EQ(out, expected.str());
  }
  EXPECT_EQ(PrintPanasonic0x003cViaClass(mn_, *v_65534), "Intelligent ISO");
  EXPECT_EQ(PrintPanasonic0x003cViaClass(mn_, *v_65535), "n/a");
}

TEST_F(PanasonicMakerNotePrint0x003cTest_712, ReturnsSameStreamReference_712) {
  auto v = MakeSLongValue(65534);
  ASSERT_NE(v.get(), nullptr);

  std::ostringstream oss;
  std::ostream& ret = mn_.print0x003c(oss, *v, /*ExifData*/ nullptr);

  // Observable behavior: function returns std::ostream&; should be the same stream object.
  EXPECT_EQ(&ret, &oss);
  EXPECT_EQ(oss.str(), "Intelligent ISO");
}

TEST_F(PanasonicMakerNotePrint0x003cTest_712, DoesNotThrowForValidValue_712) {
  // Exceptional case (observable): ensure no exception is thrown for typical values.
  auto v = MakeSLongValue(0);
  ASSERT_NE(v.get(), nullptr);

  std::ostringstream oss;
  EXPECT_NO_THROW({ mn_.print0x003c(oss, *v, /*ExifData*/ nullptr); });
}