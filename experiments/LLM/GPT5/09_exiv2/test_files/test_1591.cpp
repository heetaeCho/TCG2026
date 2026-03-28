// =================================================================================================
// TestProjects/exiv2/tests/sonymn_int_printautohdrstd_test_1591.cpp
// =================================================================================================

#include <gtest/gtest.h>

#include <exiv2/exif.hpp>
#include <exiv2/types.hpp>
#include <exiv2/value.hpp>

#include "sonymn_int.hpp"

#include <sstream>
#include <string>

namespace {

using Exiv2::ExifData;
using Exiv2::Internal::SonyMakerNote;
using Exiv2::TypeId;
using Exiv2::Value;

static Value::UniquePtr makeValue(TypeId type, const std::string& textual) {
  auto v = Value::create(type);
  EXPECT_NE(v.get(), nullptr);
  if (!v) return v;
  // Black-box: rely only on the public interface. If parsing fails, ok() should reflect it.
  (void)v->read(textual);
  return v;
}

class SonyMakerNotePrintAutoHDRStdTest_1591 : public ::testing::Test {
protected:
  SonyMakerNote mn_;
  ExifData exif_;
};

}  // namespace

// Normal operation: known mapping for both parts (0 -> Off, 0 -> Uncorrected image)
TEST_F(SonyMakerNotePrintAutoHDRStdTest_1591, PrintsKnownMappings_ZeroValue_1591) {
  auto v = makeValue(Exiv2::unsignedLong, "0");
  ASSERT_NE(v.get(), nullptr);

  std::ostringstream os;
  std::ostream& ret = mn_.printAutoHDRStd(os, *v, /*metadata*/ nullptr);

  EXPECT_EQ(&ret, &os);
  const std::string out = os.str();

  // Observable behavior: should print two parts separated by ", ".
  EXPECT_NE(out.find(", "), std::string::npos);

  // From provided tag tables:
  EXPECT_NE(out.find("Off"), std::string::npos);
  EXPECT_NE(out.find("Uncorrected image"), std::string::npos);
}

// Normal operation: lower byte=1 (Auto), high word=1 (HDR image (good))
TEST_F(SonyMakerNotePrintAutoHDRStdTest_1591, PrintsKnownMappings_AutoAndGoodHDR_1591) {
  // v0 = 1 + (1 << 16) = 65537
  auto v = makeValue(Exiv2::unsignedLong, "65537");
  ASSERT_NE(v.get(), nullptr);

  std::ostringstream os;
  std::ostream& ret = mn_.printAutoHDRStd(os, *v, &exif_);

  EXPECT_EQ(&ret, &os);
  const std::string out = os.str();

  EXPECT_NE(out.find(", "), std::string::npos);
  EXPECT_NE(out.find("Auto"), std::string::npos);
  EXPECT_NE(out.find("HDR image (good)"), std::string::npos);
}

// Boundary/alternate mapping: max listed EV in part1 (26 -> "6.0 EV") and part2=3 ("HDR (fail 2)")
TEST_F(SonyMakerNotePrintAutoHDRStdTest_1591, PrintsKnownMappings_MaxEVAndFail2_1591) {
  // v0 = 26 + (3 << 16) = 26 + 196608 = 196634
  auto v = makeValue(Exiv2::unsignedLong, "196634");
  ASSERT_NE(v.get(), nullptr);

  std::ostringstream os;
  mn_.printAutoHDRStd(os, *v, &exif_);
  const std::string out = os.str();

  EXPECT_NE(out.find(", "), std::string::npos);
  EXPECT_NE(out.find("6.0 EV"), std::string::npos);
  EXPECT_NE(out.find("HDR (fail 2)"), std::string::npos);
}

// Error/exceptional (observable) case: wrong type => outputs "(<value>)"
TEST_F(SonyMakerNotePrintAutoHDRStdTest_1591, WrongType_PrintsParenthesizedValue_1591) {
  auto v = makeValue(Exiv2::unsignedShort, "0");
  ASSERT_NE(v.get(), nullptr);

  std::ostringstream os;
  mn_.printAutoHDRStd(os, *v, &exif_);
  const std::string out = os.str();

  ASSERT_FALSE(out.empty());
  EXPECT_EQ(out.front(), '(');
  EXPECT_EQ(out.back(), ')');
}

// Error/exceptional (observable) case: count != 1 => outputs "(<value>)"
TEST_F(SonyMakerNotePrintAutoHDRStdTest_1591, CountNotOne_PrintsParenthesizedValue_1591) {
  // Black-box: for Exiv2 numeric values, a whitespace-separated list commonly yields count > 1.
  auto v = makeValue(Exiv2::unsignedLong, "0 1");
  ASSERT_NE(v.get(), nullptr);

  // If parsing didn't yield multiple values in this build, force the test to still validate behavior
  // when count != 1 by accepting either outcome but requiring "parenthesized" output iff count != 1.
  std::ostringstream os;
  mn_.printAutoHDRStd(os, *v, &exif_);
  const std::string out = os.str();

  ASSERT_FALSE(out.empty());
  if (v->count() != 1) {
    EXPECT_EQ(out.front(), '(');
    EXPECT_EQ(out.back(), ')');
  } else {
    // If the Value implementation treats "0 1" as a single value, we at least ensure it's not empty
    // and has the expected separator for the normal-path formatting.
    EXPECT_NE(out.find(", "), std::string::npos);
  }
}

// Boundary case: very large value should not crash and should still produce a two-part output
TEST_F(SonyMakerNotePrintAutoHDRStdTest_1591, LargeValue_DoesNotThrow_ProducesOutput_1591) {
  auto v = makeValue(Exiv2::unsignedLong, "4294967295");  // 0xFFFFFFFF
  ASSERT_NE(v.get(), nullptr);

  std::ostringstream os;
  EXPECT_NO_THROW({ mn_.printAutoHDRStd(os, *v, /*metadata*/ nullptr); });

  const std::string out = os.str();
  EXPECT_FALSE(out.empty());

  // For normal path (type/count ok), formatting includes ", ".
  // If the Value is not count==1 for any reason, it would be parenthesized.
  if (v->count() == 1 && v->typeId() == Exiv2::unsignedLong) {
    EXPECT_NE(out.find(", "), std::string::npos);
  } else {
    EXPECT_EQ(out.front(), '(');
    EXPECT_EQ(out.back(), ')');
  }
}