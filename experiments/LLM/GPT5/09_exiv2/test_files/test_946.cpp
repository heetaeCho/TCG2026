// SPDX-License-Identifier: GPL-2.0-or-later
// TEST_ID 946
//
// Unit tests for Exiv2::Internal::CanonMakerNote::printCs0x0002
//
// Constraints adhered to:
// - Black-box testing via public interface only
// - No private/internal state access
// - No re-implementation of internal logic beyond observable I/O formatting expectations
// - Boundary + error/exceptional cases covered (type mismatch, count==0)
// - External interactions: ostream output verification

#include <gtest/gtest.h>

#include <exiv2/exiv2.hpp>

#include <cmath>
#include <iomanip>
#include <limits>
#include <sstream>
#include <string>
#include <vector>

namespace Exiv2 {
namespace Internal {

// Forward declaration is enough for calling the method if canonmn_int.cpp is linked in.
// If the build exposes the full definition via headers, this still compiles.
// If not, keep this declaration in sync with the signature shown in the prompt.
class CanonMakerNote {
public:
  std::ostream& printCs0x0002(std::ostream& os, const Value& value, const ExifData*);
};

}  // namespace Internal
}  // namespace Exiv2

namespace {

class CanonMakerNotePrintCs0x0002Test_946 : public ::testing::Test {
protected:
  Exiv2::Internal::CanonMakerNote uut_;
  Exiv2::ExifData exif_;  // not used by implementation per interface; provided to satisfy signature

  static std::string ToString(std::ostream& (*printer)(std::ostream&, const Exiv2::Value&, const Exiv2::ExifData*),
                              Exiv2::Internal::CanonMakerNote& obj, const Exiv2::Value& v,
                              const Exiv2::ExifData* ed) {
    std::ostringstream oss;
    // Call through pointer is not required; keep helper unused by default.
    (void)printer;
    obj.printCs0x0002(oss, v, ed);
    return oss.str();
  }

  static std::string Print(Exiv2::Internal::CanonMakerNote& obj, const Exiv2::Value& v,
                           const Exiv2::ExifData* ed) {
    std::ostringstream oss;
    obj.printCs0x0002(oss, v, ed);
    return oss.str();
  }

  static double ParseLeadingDouble(const std::string& s, bool* ok) {
    if (ok) *ok = false;
    std::istringstream iss(s);
    double d = 0.0;
    iss >> d;
    if (!iss.fail()) {
      if (ok) *ok = true;
      return d;
    }
    return 0.0;
  }
};

TEST_F(CanonMakerNotePrintCs0x0002Test_946, NonUnsignedShortType_IsStreamedAsValue_946) {
  // Exceptional/error-ish case: type mismatch should fall back to streaming "value" itself.
  // Use an ASCII value (definitely not unsignedShort).
  Exiv2::AsciiValue ascii;
  ascii.read("hello");

  std::ostringstream expected;
  expected << ascii;

  const std::string out = Print(uut_, ascii, &exif_);
  EXPECT_EQ(out, expected.str());
}

TEST_F(CanonMakerNotePrintCs0x0002Test_946, CountZero_IsStreamedAsValue_946) {
  // Boundary case: unsigned short type but count==0 should fall back to streaming "value" itself.
  Exiv2::UShortValue us;
  // Intentionally do not add any elements => count() == 0
  ASSERT_EQ(us.count(), 0U);

  std::ostringstream expected;
  expected << us;

  const std::string out = Print(uut_, us, &exif_);
  EXPECT_EQ(out, expected.str());
}

TEST_F(CanonMakerNotePrintCs0x0002Test_946, UnsignedShortZero_PrintsOff_946) {
  // Normal operation: l == 0 prints "Off"
  Exiv2::UShortValue us;
  us.value_.push_back(static_cast<uint16_t>(0));
  ASSERT_EQ(us.count(), 1U);

  const std::string out = Print(uut_, us, &exif_);
  EXPECT_EQ(out, "Off");
}

TEST_F(CanonMakerNotePrintCs0x0002Test_946, UnsignedShortNonZero_PrintsSecondsWithSuffix_946) {
  // Normal operation: non-zero prints "<number> s"
  Exiv2::UShortValue us;
  us.value_.push_back(static_cast<uint16_t>(10));  // should become 1.0 s based on observable formatting

  const std::string out = Print(uut_, us, &exif_);
  // Should end with " s"
  ASSERT_GE(out.size(), 2U);
  EXPECT_EQ(out.substr(out.size() - 2), " s");

  bool ok = false;
  const double val = ParseLeadingDouble(out, &ok);
  EXPECT_TRUE(ok);
  EXPECT_NEAR(val, 1.0, 1e-12);
}

TEST_F(CanonMakerNotePrintCs0x0002Test_946, UnsignedShortBoundaryOne_PrintsSmallestNonZero_946) {
  // Boundary condition: smallest non-zero (1) => 0.1 s
  Exiv2::UShortValue us;
  us.value_.push_back(static_cast<uint16_t>(1));

  const std::string out = Print(uut_, us, &exif_);
  EXPECT_EQ(out.substr(out.size() - 2), " s");

  bool ok = false;
  const double val = ParseLeadingDouble(out, &ok);
  EXPECT_TRUE(ok);
  EXPECT_NEAR(val, 0.1, 1e-12);
}

TEST_F(CanonMakerNotePrintCs0x0002Test_946, UnsignedShortBoundaryMax_PrintsLargeSeconds_946) {
  // Boundary condition: largest uint16_t
  Exiv2::UShortValue us;
  us.value_.push_back(std::numeric_limits<uint16_t>::max());  // 65535 => 6553.5 s

  const std::string out = Print(uut_, us, &exif_);
  EXPECT_EQ(out.substr(out.size() - 2), " s");

  bool ok = false;
  const double val = ParseLeadingDouble(out, &ok);
  EXPECT_TRUE(ok);
  EXPECT_NEAR(val, 6553.5, 1e-9);
}

TEST_F(CanonMakerNotePrintCs0x0002Test_946, NullExifDataPointer_IsAccepted_946) {
  // Boundary: ExifData* can be null (signature allows it). Observable behavior is just output.
  Exiv2::UShortValue us;
  us.value_.push_back(static_cast<uint16_t>(20));  // 2.0 s

  const std::string out = Print(uut_, us, nullptr);
  EXPECT_EQ(out.substr(out.size() - 2), " s");

  bool ok = false;
  const double val = ParseLeadingDouble(out, &ok);
  EXPECT_TRUE(ok);
  EXPECT_NEAR(val, 2.0, 1e-12);
}

TEST_F(CanonMakerNotePrintCs0x0002Test_946, ReturnsSameOstreamReference_946) {
  // Verifies external interaction with ostream: returned reference should be the same stream passed in.
  Exiv2::UShortValue us;
  us.value_.push_back(static_cast<uint16_t>(0));

  std::ostringstream oss;
  std::ostream& ret = uut_.printCs0x0002(oss, us, &exif_);
  EXPECT_EQ(&ret, &oss);
  EXPECT_EQ(oss.str(), "Off");
}

}  // namespace