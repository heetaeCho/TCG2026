// =================================================================================================
// TEST_ID: 708
// File: test_panasonicmn_int_print0x0023_708.cpp
//
// Unit tests for:
//   Exiv2::Internal::PanasonicMakerNote::print0x0023(std::ostream&, const Value&, const ExifData*)
//
// Constraints honored:
// - Treat implementation as black box (no internal assumptions beyond observable output).
// - Test only via public interface (function call + stream output).
// - No private state access.
// - Include normal, boundary, and observable error/exceptional-ish cases.
// =================================================================================================

#include <gtest/gtest.h>

#include <cstdint>
#include <limits>
#include <ostream>
#include <sstream>
#include <string>

// Exiv2 headers (paths may differ in your tree; adjust if needed)
#include "exif.hpp"   // Exiv2::ExifData
#include "value.hpp"  // Exiv2::Value (and derived value types)
#include "panasonicmn_int.hpp"  // Exiv2::Internal::PanasonicMakerNote (adjust include if needed)

namespace {

// Helper: locate the " EV" suffix without hardcoding any localization-sensitive prefix text.
static bool EndsWith(const std::string& s, const std::string& suffix) {
  return s.size() >= suffix.size() && s.compare(s.size() - suffix.size(), suffix.size(), suffix) == 0;
}

}  // namespace

// -------- Test fixture --------
class PanasonicMakerNotePrint0x0023Test_708 : public ::testing::Test {
 protected:
  Exiv2::Internal::PanasonicMakerNote uut_;
  Exiv2::ExifData exif_;  // Passed as pointer (may be unused by implementation)
};

// Normal operation: basic formatting includes localized " EV" suffix; numeric portion is printed.
TEST_F(PanasonicMakerNotePrint0x0023Test_708, AppendsEvSuffix_708) {
  // Use a signed integer value; "3" should produce an integer "1" after division by 3,
  // but we don't rely on the exact math—only that some number appears and suffix is present.
  Exiv2::Value::UniquePtr v = Exiv2::Value::create(Exiv2::signedLong);
  ASSERT_TRUE(!!v);
  ASSERT_EQ(0, v->read("3"));

  std::ostringstream os;
  std::ostream& ret = uut_.print0x0023(os, *v, &exif_);

  EXPECT_EQ(&ret, &os);  // Should return the same stream by reference.
  const std::string out = os.str();

  EXPECT_FALSE(out.empty());
  EXPECT_TRUE(EndsWith(out, " EV")) << "Output was: [" << out << "]";
}

// Normal operation: nullptr ExifData is accepted (observable behavior: no crash and still prints).
TEST_F(PanasonicMakerNotePrint0x0023Test_708, AcceptsNullExifData_708) {
  Exiv2::Value::UniquePtr v = Exiv2::Value::create(Exiv2::signedLong);
  ASSERT_TRUE(!!v);
  ASSERT_EQ(0, v->read("0"));

  std::ostringstream os;
  uut_.print0x0023(os, *v, nullptr);

  const std::string out = os.str();
  EXPECT_TRUE(EndsWith(out, " EV")) << "Output was: [" << out << "]";
}

// Boundary: negative input should be representable and still end with " EV".
TEST_F(PanasonicMakerNotePrint0x0023Test_708, NegativeValuePrintsWithSuffix_708) {
  Exiv2::Value::UniquePtr v = Exiv2::Value::create(Exiv2::signedLong);
  ASSERT_TRUE(!!v);
  ASSERT_EQ(0, v->read("-3"));

  std::ostringstream os;
  uut_.print0x0023(os, *v, &exif_);

  const std::string out = os.str();
  EXPECT_TRUE(EndsWith(out, " EV")) << "Output was: [" << out << "]";
  // Don't assert exact number (black-box), but it should include a '-' for negative values.
  EXPECT_NE(out.find('-'), std::string::npos) << "Output was: [" << out << "]";
}

// Boundary: large magnitude value should not break formatting; still ends with " EV".
TEST_F(PanasonicMakerNotePrint0x0023Test_708, LargeMagnitudeValuePrintsWithSuffix_708) {
  // Use the largest int32-ish literal parsable by signedLong in typical Exiv2 builds.
  // We avoid asserting exact numeric result to keep tests black-box across platforms.
  Exiv2::Value::UniquePtr v = Exiv2::Value::create(Exiv2::signedLong);
  ASSERT_TRUE(!!v);
  ASSERT_EQ(0, v->read("2147483647"));

  std::ostringstream os;
  uut_.print0x0023(os, *v, &exif_);

  const std::string out = os.str();
  EXPECT_TRUE(EndsWith(out, " EV")) << "Output was: [" << out << "]";
  EXPECT_GT(out.size(), std::string(" EV").size());
}

// Exceptional-ish / robustness: When the output stream is in a bad state, function should not crash
// and should still return the same stream reference (observable via returned reference).
TEST_F(PanasonicMakerNotePrint0x0023Test_708, ReturnsSameStreamEvenIfStreamBad_708) {
  Exiv2::Value::UniquePtr v = Exiv2::Value::create(Exiv2::signedLong);
  ASSERT_TRUE(!!v);
  ASSERT_EQ(0, v->read("3"));

  std::ostringstream os;
  os.setstate(std::ios::badbit);

  std::ostream& ret = uut_.print0x0023(os, *v, &exif_);
  EXPECT_EQ(&ret, &os);
  // Do not assert on os.str() because stream may not accept output when badbit is set.
}

// Boundary: non-multiple-of-3 value—still should produce something with " EV" suffix.
TEST_F(PanasonicMakerNotePrint0x0023Test_708, NonMultipleOfThreeStillPrintsSuffix_708) {
  Exiv2::Value::UniquePtr v = Exiv2::Value::create(Exiv2::signedLong);
  ASSERT_TRUE(!!v);
  ASSERT_EQ(0, v->read("1"));

  std::ostringstream os;
  uut_.print0x0023(os, *v, &exif_);

  const std::string out = os.str();
  EXPECT_TRUE(EndsWith(out, " EV")) << "Output was: [" << out << "]";
}