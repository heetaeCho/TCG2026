// SPDX-License-Identifier: GPL-2.0-or-later
// File: test_exifdatum_taglabel_746.cpp
//
// Unit tests for Exiv2::Exifdatum::tagLabel()
// Interface under test (black-box): std::string Exifdatum::tagLabel() const;
//
// TEST_ID: 746

#include <gtest/gtest.h>

#include <exiv2/exif.hpp>
#include <exiv2/tags.hpp>

namespace {

class ExifdatumTagLabelTest_746 : public ::testing::Test {};

TEST_F(ExifdatumTagLabelTest_746, TagLabelMatchesUnderlyingKey_746) {
  const Exiv2::ExifKey key("Exif.Image.Make");
  const Exiv2::Exifdatum datum(key, nullptr);

  // Black-box check: Exifdatum::tagLabel() should reflect the key's tagLabel().
  EXPECT_EQ(datum.tagLabel(), key.tagLabel());
}

TEST_F(ExifdatumTagLabelTest_746, TagLabelStableAcrossCopyConstruction_746) {
  const Exiv2::ExifKey key("Exif.Image.Model");
  const Exiv2::Exifdatum original(key, nullptr);

  const Exiv2::Exifdatum copied(original);

  EXPECT_EQ(copied.tagLabel(), original.tagLabel());
  EXPECT_EQ(copied.tagLabel(), key.tagLabel());
}

TEST_F(ExifdatumTagLabelTest_746, TagLabelStableAcrossCopyAssignment_746) {
  const Exiv2::ExifKey keyA("Exif.Image.Make");
  const Exiv2::ExifKey keyB("Exif.Image.Model");

  const Exiv2::Exifdatum a(keyA, nullptr);
  Exiv2::Exifdatum b(keyB, nullptr);

  // Sanity: likely different keys; regardless, assignment should make b match a.
  b = a;

  EXPECT_EQ(b.tagLabel(), a.tagLabel());
  EXPECT_EQ(b.tagLabel(), keyA.tagLabel());
}

TEST_F(ExifdatumTagLabelTest_746, TagLabelUnaffectedByValueStringAssignment_746) {
  const Exiv2::ExifKey key("Exif.Image.Make");
  Exiv2::Exifdatum datum(key, nullptr);

  const std::string before = datum.tagLabel();

  // Changing the value via public operator= should not change the key-derived label.
  datum = std::string("SomeValue");

  EXPECT_EQ(datum.tagLabel(), before);
  EXPECT_EQ(datum.tagLabel(), key.tagLabel());
}

TEST_F(ExifdatumTagLabelTest_746, TagLabelWorksForDifferentKeys_746) {
  const Exiv2::ExifKey key1("Exif.Image.Make");
  const Exiv2::ExifKey key2("Exif.Image.Model");

  const Exiv2::Exifdatum d1(key1, nullptr);
  const Exiv2::Exifdatum d2(key2, nullptr);

  // Boundary-style check across different inputs: each datum should match its own key.
  EXPECT_EQ(d1.tagLabel(), key1.tagLabel());
  EXPECT_EQ(d2.tagLabel(), key2.tagLabel());
}

}  // namespace