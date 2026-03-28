// SPDX-License-Identifier: GPL-2.0-or-later
// Unit tests for Exiv2::XmpKey
//
// File under test (as provided): ./TestProjects/exiv2/src/properties.cpp
// Public interface: exiv2/properties.hpp (and Key base in exiv2/metadatum.hpp)

#include <gtest/gtest.h>

#include <exiv2/properties.hpp>
#include <exiv2/metadatum.hpp>

#include <cstdint>
#include <memory>
#include <string>

namespace {

class XmpKeyTest_2178 : public ::testing::Test {};

TEST_F(XmpKeyTest_2178, ConstructFromSingleString_AllAccessorsCallable_2178) {
  // Black-box: just verify construction works and accessors are callable.
  Exiv2::XmpKey key("Xmp.dc.title");

  EXPECT_NO_THROW({
    (void)key.key();
    (void)key.familyName();
    (void)key.groupName();
    (void)key.tagName();
    (void)key.tagLabel();
    (void)key.tagDesc();
    (void)key.tag();
    (void)key.ns();
  });

  // familyName() returns const char*, ensure it's a valid pointer.
  EXPECT_NE(nullptr, key.familyName());
}

TEST_F(XmpKeyTest_2178, ConstructFromPrefixAndProperty_AllAccessorsCallable_2178) {
  Exiv2::XmpKey key("Xmp.dc", "title");

  EXPECT_NO_THROW({
    (void)key.key();
    (void)key.familyName();
    (void)key.groupName();
    (void)key.tagName();
    (void)key.tagLabel();
    (void)key.tagDesc();
    (void)key.tag();
    (void)key.ns();
  });

  EXPECT_NE(nullptr, key.familyName());
}

TEST_F(XmpKeyTest_2178, CopyConstructor_PreservesObservableState_2178) {
  Exiv2::XmpKey original("Xmp.dc.title");
  const std::string originalKey = original.key();
  const std::string originalNs = original.ns();
  const std::string originalGroup = original.groupName();
  const std::string originalTagName = original.tagName();
  const uint16_t originalTag = original.tag();

  Exiv2::XmpKey copy(original);

  EXPECT_EQ(copy.key(), originalKey);
  EXPECT_EQ(copy.ns(), originalNs);
  EXPECT_EQ(copy.groupName(), originalGroup);
  EXPECT_EQ(copy.tagName(), originalTagName);
  EXPECT_EQ(copy.tag(), originalTag);
  EXPECT_STREQ(copy.familyName(), original.familyName());
}

TEST_F(XmpKeyTest_2178, CopyAssignment_PreservesObservableState_2178) {
  Exiv2::XmpKey source("Xmp.dc.title");
  Exiv2::XmpKey target("Xmp.xmp.CreatorTool");  // different initial value

  const std::string sourceKey = source.key();
  const std::string sourceNs = source.ns();
  const std::string sourceGroup = source.groupName();
  const std::string sourceTagName = source.tagName();
  const uint16_t sourceTag = source.tag();

  target = source;

  EXPECT_EQ(target.key(), sourceKey);
  EXPECT_EQ(target.ns(), sourceNs);
  EXPECT_EQ(target.groupName(), sourceGroup);
  EXPECT_EQ(target.tagName(), sourceTagName);
  EXPECT_EQ(target.tag(), sourceTag);
  EXPECT_STREQ(target.familyName(), source.familyName());
}

TEST_F(XmpKeyTest_2178, SelfAssignment_DoesNotChangeObservableState_2178) {
  Exiv2::XmpKey key("Xmp.dc.title");

  const std::string beforeKey = key.key();
  const std::string beforeNs = key.ns();
  const std::string beforeGroup = key.groupName();
  const std::string beforeTagName = key.tagName();
  const std::string beforeTagLabel = key.tagLabel();
  const std::string beforeTagDesc = key.tagDesc();
  const uint16_t beforeTag = key.tag();
  const char* beforeFamily = key.familyName();

  key = key;

  EXPECT_EQ(key.key(), beforeKey);
  EXPECT_EQ(key.ns(), beforeNs);
  EXPECT_EQ(key.groupName(), beforeGroup);
  EXPECT_EQ(key.tagName(), beforeTagName);
  EXPECT_EQ(key.tagLabel(), beforeTagLabel);
  EXPECT_EQ(key.tagDesc(), beforeTagDesc);
  EXPECT_EQ(key.tag(), beforeTag);
  EXPECT_STREQ(key.familyName(), beforeFamily);
}

TEST_F(XmpKeyTest_2178, Clone_ReturnsIndependentObjectWithSameObservableState_2178) {
  Exiv2::XmpKey original("Xmp.dc.title");

  const std::string originalKey = original.key();
  const std::string originalNs = original.ns();
  const std::string originalGroup = original.groupName();
  const std::string originalTagName = original.tagName();
  const std::string originalTagLabel = original.tagLabel();
  const std::string originalTagDesc = original.tagDesc();
  const uint16_t originalTag = original.tag();

  Exiv2::Key::UniquePtr clonedBase;
  ASSERT_NO_THROW({ clonedBase = original.clone(); });
  ASSERT_NE(clonedBase.get(), nullptr);

  // Clone is returned as Key; verify observable behavior through virtual interface.
  EXPECT_EQ(clonedBase->key(), originalKey);
  EXPECT_STREQ(clonedBase->familyName(), original.familyName());
  EXPECT_EQ(clonedBase->groupName(), originalGroup);
  EXPECT_EQ(clonedBase->tagName(), originalTagName);
  EXPECT_EQ(clonedBase->tagLabel(), originalTagLabel);
  EXPECT_EQ(clonedBase->tagDesc(), originalTagDesc);
  EXPECT_EQ(clonedBase->tag(), originalTag);

  // Independence check: reassign original; cloned should remain unchanged.
  original = Exiv2::XmpKey("Xmp.xmp.CreatorTool");
  EXPECT_EQ(clonedBase->key(), originalKey);
}

TEST_F(XmpKeyTest_2178, Boundary_EmptyStrings_DoNotCrashAndAccessorsCallable_2178) {
  // Boundary cases: empty key string, and empty prefix/property.
  EXPECT_NO_THROW({
    Exiv2::XmpKey emptyKeyString("");
    (void)emptyKeyString.key();
    (void)emptyKeyString.familyName();
    (void)emptyKeyString.groupName();
    (void)emptyKeyString.tagName();
    (void)emptyKeyString.tagLabel();
    (void)emptyKeyString.tagDesc();
    (void)emptyKeyString.tag();
    (void)emptyKeyString.ns();
  });

  EXPECT_NO_THROW({
    Exiv2::XmpKey emptyParts("", "");
    (void)emptyParts.key();
    (void)emptyParts.familyName();
    (void)emptyParts.groupName();
    (void)emptyParts.tagName();
    (void)emptyParts.tagLabel();
    (void)emptyParts.tagDesc();
    (void)emptyParts.tag();
    (void)emptyParts.ns();
  });
}

TEST_F(XmpKeyTest_2178, Boundary_UnusualButValidCharacters_AccessorsCallable_2178) {
  // Black-box: don't assume parsing rules; just ensure no crash for atypical input.
  Exiv2::XmpKey key("Xmp.dc", "title-with-dash_and_underscore.1");

  EXPECT_NO_THROW({
    (void)key.key();
    (void)key.familyName();
    (void)key.groupName();
    (void)key.tagName();
    (void)key.tagLabel();
    (void)key.tagDesc();
    (void)key.tag();
    (void)key.ns();
  });
}

}  // namespace