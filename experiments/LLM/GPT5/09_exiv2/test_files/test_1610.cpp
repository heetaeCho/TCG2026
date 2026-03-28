// File: test_sonymn_int_printafmode_1610.cpp
#include <gtest/gtest.h>

#include <exiv2/exif.hpp>
#include <exiv2/types.hpp>
#include <exiv2/value.hpp>

// Include the interface under test
#include "sonymn_int.hpp"

#include <memory>
#include <ostream>
#include <sstream>
#include <string>

namespace {

using Exiv2::ExifData;
using Exiv2::Internal::SonyMakerNote;
using Exiv2::TypeId;

class SonyMakerNotePrintAFModeTest_1610 : public ::testing::Test {
 protected:
  static std::unique_ptr<Exiv2::Value> MakeValue(TypeId type, const std::string& text) {
    auto v = Exiv2::Value::create(type);
    // Treat parsing as black-box: use public read() only.
    (void)v->read(text);
    return v;
  }

  static std::string Parenthesized(const Exiv2::Value& v) {
    std::ostringstream oss;
    oss << "(" << v << ")";
    return oss.str();
  }

  static void ExpectSameStream(std::ostream& returned, std::ostream& original) {
    EXPECT_EQ(&returned, &original);
  }
};

TEST_F(SonyMakerNotePrintAFModeTest_1610, NullMetadata_PrintsParenthesizedValue_1610) {
  SonyMakerNote mn;

  auto v = MakeValue(Exiv2::unsignedShort, "0");
  ASSERT_NE(v, nullptr);

  std::ostringstream os;
  std::ostream& ret = mn.printAFMode(os, *v, /*metadata=*/nullptr);

  ExpectSameStream(ret, os);
  EXPECT_EQ(os.str(), Parenthesized(*v));
}

TEST_F(SonyMakerNotePrintAFModeTest_1610, NonSingleCount_PrintsParenthesizedValue_1610) {
  SonyMakerNote mn;

  // Attempt to create a Value with count != 1 via public parsing API.
  // If parsing yields count==1 anyway, we force a clearly multi-token form.
  auto v = MakeValue(Exiv2::unsignedShort, "0 1");
  ASSERT_NE(v, nullptr);
  ASSERT_NE(v->count(), 0u);

  ExifData exif;  // Empty metadata is fine for this guard-branch test.

  std::ostringstream os;
  std::ostream& ret = mn.printAFMode(os, *v, &exif);

  ExpectSameStream(ret, os);

  if (v->count() != 1) {
    EXPECT_EQ(os.str(), Parenthesized(*v));
  } else {
    // If the library parser normalizes to a single item, the guard doesn't apply.
    // In that case, at minimum the result should NOT be the parenthesized form
    // triggered by (count != 1).
    EXPECT_NE(os.str(), Parenthesized(*v));
  }
}

TEST_F(SonyMakerNotePrintAFModeTest_1610, WrongType_PrintsParenthesizedValue_1610) {
  SonyMakerNote mn;

  auto v = MakeValue(Exiv2::unsignedLong, "0");
  ASSERT_NE(v, nullptr);

  ExifData exif;

  std::ostringstream os;
  std::ostream& ret = mn.printAFMode(os, *v, &exif);

  ExpectSameStream(ret, os);
  EXPECT_EQ(os.str(), Parenthesized(*v));
}

TEST_F(SonyMakerNotePrintAFModeTest_1610, NoMetaVersion_MapsValue0ToDefault_1610) {
  SonyMakerNote mn;

  auto v = MakeValue(Exiv2::unsignedShort, "0");
  ASSERT_NE(v, nullptr);
  ASSERT_EQ(v->count(), 1u);

  ExifData exif;  // Empty metadata: getMetaVersion(...) is expected to fail.

  std::ostringstream os;
  std::ostream& ret = mn.printAFMode(os, *v, &exif);

  ExpectSameStream(ret, os);

  // Observable output expected to come from sonyAFModeSet1 mapping for value 0: "Default".
  // (Do not assume additional formatting; assert substring.)
  EXPECT_NE(os.str(), Parenthesized(*v));
  EXPECT_NE(os.str().find("Default"), std::string::npos);
}

TEST_F(SonyMakerNotePrintAFModeTest_1610, NoMetaVersion_MapsFlexibleSpot_1610) {
  SonyMakerNote mn;

  auto v = MakeValue(Exiv2::unsignedShort, "4");
  ASSERT_NE(v, nullptr);
  ASSERT_EQ(v->count(), 1u);

  ExifData exif;

  std::ostringstream os;
  std::ostream& ret = mn.printAFMode(os, *v, &exif);

  ExpectSameStream(ret, os);

  // sonyAFModeSet1 value 4: "Flexible Spot"
  EXPECT_NE(os.str(), Parenthesized(*v));
  EXPECT_NE(os.str().find("Flexible"), std::string::npos);
}

TEST_F(SonyMakerNotePrintAFModeTest_1610, NoMetaVersion_MapsMaxUShortToNA_1610) {
  SonyMakerNote mn;

  auto v = MakeValue(Exiv2::unsignedShort, "65535");
  ASSERT_NE(v, nullptr);
  ASSERT_EQ(v->count(), 1u);

  ExifData exif;

  std::ostringstream os;
  std::ostream& ret = mn.printAFMode(os, *v, &exif);

  ExpectSameStream(ret, os);

  // sonyAFModeSet1 value 65535: "n/a"
  EXPECT_NE(os.str(), Parenthesized(*v));
  EXPECT_NE(os.str().find("n/a"), std::string::npos);
}

}  // namespace