// SPDX-License-Identifier: GPL-2.0-or-later
// File: test_sonymn_int_getmodel_1584.cpp
//
// Unit tests for Exiv2::Internal::getModel (from sonymn_int.cpp)
//
// NOTE:
// - We treat the implementation as a black box.
// - We only validate observable behavior: return value + output string + public ExifData/Exifdatum APIs.
// - getModel() is defined with internal linkage (static) in sonymn_int.cpp, so we include that TU here.
//   This is a common pattern for testing internal-linkage helpers when no public entry point exists.

#include <gtest/gtest.h>

#include <string>

#include "exiv2/exif.hpp"
#include "exiv2/types.hpp"

// Include the implementation file to access the internal-linkage function.
#include "TestProjects/exiv2/src/sonymn_int.cpp"

namespace {

bool ContainsSpace(const std::string& s) {
  return s.find(' ') != std::string::npos;
}

class GetModelTest_1584 : public ::testing::Test {};

TEST_F(GetModelTest_1584, ImageModelAsciiPresent_ReturnsTrueAndCopiesValue_1584) {
  Exiv2::ExifData md;
  md["Exif.Image.Model"] = std::string("ILCE-7M3");

  std::string out("preexisting");
  const bool ok = Exiv2::Internal::getModel(&md, out);

  EXPECT_TRUE(ok);
  EXPECT_EQ(out, "ILCE-7M3");
}

TEST_F(GetModelTest_1584, ImageModelAsciiMayContainSpaces_IsNotFiltered_1584) {
  Exiv2::ExifData md;
  md["Exif.Image.Model"] = std::string("Sony Camera Model With Spaces");

  std::string out;
  const bool ok = Exiv2::Internal::getModel(&md, out);

  EXPECT_TRUE(ok);
  EXPECT_EQ(out, "Sony Camera Model With Spaces");
}

TEST_F(GetModelTest_1584, ImageModelWrongType_FallsBackToSony1_1584) {
  Exiv2::ExifData md;

  // Wrong type for Exif.Image.Model (expects asciiString).
  md["Exif.Image.Model"] = static_cast<uint16_t>(123);

  // Provide Sony1 model id (expects unsignedShort).
  md["Exif.Sony1.SonyModelID"] = static_cast<uint16_t>(1);

  auto pos = md.findKey(Exiv2::ExifKey("Exif.Sony1.SonyModelID"));
  ASSERT_NE(pos, md.end());
  ASSERT_NE(pos->size(), 0u);
  ASSERT_EQ(pos->typeId(), Exiv2::unsignedShort);

  const std::string printed = pos->print(&md);

  std::string out("preexisting");
  const bool ok = Exiv2::Internal::getModel(&md, out);

  // Observable contract: when ok == true, out should equal the printed representation,
  // and that printed representation should not contain spaces. When ok == false, out is "".
  if (!ContainsSpace(printed)) {
    EXPECT_TRUE(ok);
    EXPECT_EQ(out, printed);
  } else {
    EXPECT_FALSE(ok);
    EXPECT_TRUE(out.empty());
  }
}

TEST_F(GetModelTest_1584, Sony1PresentUnsignedShort_ResultConsistentWithPrintedFormatting_1584) {
  Exiv2::ExifData md;
  md["Exif.Sony1.SonyModelID"] = static_cast<uint16_t>(65535);

  auto pos = md.findKey(Exiv2::ExifKey("Exif.Sony1.SonyModelID"));
  ASSERT_NE(pos, md.end());
  const std::string printed = pos->print(&md);

  std::string out("preexisting");
  const bool ok = Exiv2::Internal::getModel(&md, out);

  if (!ContainsSpace(printed)) {
    EXPECT_TRUE(ok);
    EXPECT_EQ(out, printed);
    EXPECT_FALSE(ContainsSpace(out));
  } else {
    EXPECT_FALSE(ok);
    EXPECT_TRUE(out.empty());
  }
}

TEST_F(GetModelTest_1584, Sony2UsedWhenSony1Missing_ResultConsistentWithPrintedFormatting_1584) {
  Exiv2::ExifData md;

  // Sony1 missing, Sony2 present.
  md["Exif.Sony2.SonyModelID"] = static_cast<uint16_t>(42);

  auto pos = md.findKey(Exiv2::ExifKey("Exif.Sony2.SonyModelID"));
  ASSERT_NE(pos, md.end());
  const std::string printed = pos->print(&md);

  std::string out("preexisting");
  const bool ok = Exiv2::Internal::getModel(&md, out);

  if (!ContainsSpace(printed)) {
    EXPECT_TRUE(ok);
    EXPECT_EQ(out, printed);
    EXPECT_FALSE(ContainsSpace(out));
  } else {
    EXPECT_FALSE(ok);
    EXPECT_TRUE(out.empty());
  }
}

TEST_F(GetModelTest_1584, Sony1PreferredOverSony2_WhenBothPresent_1584) {
  Exiv2::ExifData md;

  md["Exif.Sony1.SonyModelID"] = static_cast<uint16_t>(1);
  md["Exif.Sony2.SonyModelID"] = static_cast<uint16_t>(2);

  auto pos1 = md.findKey(Exiv2::ExifKey("Exif.Sony1.SonyModelID"));
  auto pos2 = md.findKey(Exiv2::ExifKey("Exif.Sony2.SonyModelID"));
  ASSERT_NE(pos1, md.end());
  ASSERT_NE(pos2, md.end());

  const std::string printed1 = pos1->print(&md);
  const std::string printed2 = pos2->print(&md);

  std::string out;
  const bool ok = Exiv2::Internal::getModel(&md, out);

  // Preference is observable only when Sony1 yields a successful result.
  // If Sony1's printed value contains spaces, getModel is expected to return false and clear out,
  // and (per implementation) it should not proceed to Sony2.
  if (!ContainsSpace(printed1)) {
    EXPECT_TRUE(ok);
    EXPECT_EQ(out, printed1);
    // If Sony2 also has a printable value, we still expect Sony1's to win.
    (void)printed2;
  } else {
    EXPECT_FALSE(ok);
    EXPECT_TRUE(out.empty());
  }
}

TEST_F(GetModelTest_1584, NoRelevantKeys_ReturnsFalseAndClearsVal_1584) {
  Exiv2::ExifData md;

  std::string out("preexisting");
  const bool ok = Exiv2::Internal::getModel(&md, out);

  EXPECT_FALSE(ok);
  EXPECT_TRUE(out.empty());
}

}  // namespace