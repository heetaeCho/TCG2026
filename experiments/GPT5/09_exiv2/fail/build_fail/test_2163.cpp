// SPDX-License-Identifier: GPL-2.0-or-later
// File: test_exifdatum_ctor_2163.cpp
//
// Unit tests for Exiv2::Exifdatum constructor behavior (black-box).
// The TEST_ID is 2163.

#include <gtest/gtest.h>

#include <limits>
#include <memory>
#include <string>

#include "exiv2/exif.hpp"
#include "exiv2/tags.hpp"
#include "exiv2/value.hpp"

namespace {

class ExifdatumTest_2163 : public ::testing::Test {};

TEST_F(ExifdatumTest_2163, ConstructWithNullValue_KeyIsAccessible_2163) {
  Exiv2::ExifKey key("Exif.Image.ImageDescription");

  EXPECT_NO_THROW({
    Exiv2::Exifdatum datum(key, nullptr);

    // Observable: key-related accessors should be callable.
    (void)datum.key();
    (void)datum.familyName();
    (void)datum.groupName();
    (void)datum.tagName();
    (void)datum.tagLabel();
    (void)datum.tagDesc();
    (void)datum.tag();
    (void)datum.ifdId();
    (void)datum.ifdName();
    (void)datum.idx();
    (void)datum.typeId();
    (void)datum.typeName();
    (void)datum.typeSize();
    (void)datum.count();
    (void)datum.size();
    (void)datum.toString();
  });
}

TEST_F(ExifdatumTest_2163, ConstructorClonesKey_IdxDoesNotTrackSourceKeyChanges_2163) {
  Exiv2::ExifKey key("Exif.Image.ImageDescription");

  const int initialIdx = std::numeric_limits<int>::min();
  const int changedIdx = std::numeric_limits<int>::max();

  // Set a known idx before construction.
  key.setIdx(initialIdx);
  Exiv2::Exifdatum datum(key, nullptr);

  // Mutate the source key after construction.
  key.setIdx(changedIdx);

  // Observable expectation: datum should keep the original key state it cloned.
  EXPECT_EQ(datum.idx(), initialIdx);

  // And its key string should remain stable.
  const std::string datumKey = datum.key();
  EXPECT_FALSE(datumKey.empty());
}

TEST_F(ExifdatumTest_2163, ConstructorClonesValue_ToStringRemainsStableAfterOriginalMutates_2163) {
  Exiv2::ExifKey key("Exif.Image.ImageDescription");

  // Use the key's default type to avoid hard-coding a TypeId.
  auto originalValue = Exiv2::Value::create(key.defaultTypeId());
  ASSERT_TRUE(static_cast<bool>(originalValue));

  // Try to seed the value with some content via the public interface.
  // (We intentionally do not assume how parsing works; we only rely on toString being observable.)
  (void)originalValue->read(std::string("hello"));

  const std::string before = originalValue->toString();

  // Construct Exifdatum with the value pointer; it should clone the value.
  Exiv2::Exifdatum datum(key, originalValue.get());

  // Mutate the original value after construction.
  (void)originalValue->read(std::string("world"));
  const std::string after = originalValue->toString();

  // The original may or may not change depending on parsing rules, but if it does change,
  // the datum's string representation should remain the "before" snapshot if cloning occurred.
  // We can at least require datum.toString() equals the snapshot taken at construction time.
  EXPECT_EQ(datum.toString(), before);

  // Extra observable sanity: if the original did change, datum should differ from it.
  if (after != before) {
    EXPECT_NE(datum.toString(), after);
  }
}

TEST_F(ExifdatumTest_2163, ConstructWithNullValue_DataAreaApisAreCallable_2163) {
  Exiv2::ExifKey key("Exif.Image.ImageDescription");
  Exiv2::Exifdatum datum(key, nullptr);

  // Boundary-ish: data area size should be queryable even without an explicit value.
  EXPECT_NO_THROW({
    (void)datum.sizeDataArea();
    (void)datum.dataArea();
  });

  // Also ensure copy/write APIs are callable with benign inputs.
  EXPECT_NO_THROW({
    // copy() requires a buffer; passing nullptr may or may not be allowed by implementation,
    // so allocate a small buffer.
    Exiv2::byte buf[32] = {};
    (void)datum.copy(buf, Exiv2::littleEndian);

    std::ostringstream os;
    (void)datum.write(os, nullptr);
  });
}

}  // namespace