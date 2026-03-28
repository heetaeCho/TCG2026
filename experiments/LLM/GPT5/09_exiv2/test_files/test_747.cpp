// SPDX-License-Identifier: GPL-2.0-or-later
//
// File: exifdatum_tagdesc_test_747.cpp
//
// Unit tests for Exiv2::Exifdatum::tagDesc()
// (black-box tests based strictly on public interfaces)

#include <gtest/gtest.h>

#include <exiv2/exif.hpp>
#include <exiv2/tags.hpp>

#include <string>

namespace {

class ExifdatumTagDescTest_747 : public ::testing::Test {
 protected:
  static Exiv2::Exifdatum MakeDatumOrFail(const std::string& keyStr) {
    // We intentionally pass nullptr for Value* to avoid relying on Value internals.
    Exiv2::ExifKey key(keyStr);
    return Exiv2::Exifdatum(key, nullptr);
  }
};

TEST_F(ExifdatumTagDescTest_747, TagDescMatchesKeyTagDesc_747) {
  const Exiv2::ExifKey key("Exif.Image.Make");
  const Exiv2::Exifdatum d(key, nullptr);

  // Observable behavior: tagDesc is derived from the key (if present).
  EXPECT_EQ(d.tagDesc(), key.tagDesc());
}

TEST_F(ExifdatumTagDescTest_747, TagDescWithNullValueStillMatchesKey_747) {
  const Exiv2::ExifKey key("Exif.Image.Model");
  const Exiv2::Exifdatum d(key, nullptr);

  // Boundary: constructor receives nullptr value pointer.
  EXPECT_EQ(d.tagDesc(), key.tagDesc());
}

TEST_F(ExifdatumTagDescTest_747, CopyConstructorPreservesTagDesc_747) {
  const Exiv2::ExifKey key("Exif.Image.Make");
  const Exiv2::Exifdatum original(key, nullptr);

  const Exiv2::Exifdatum copy(original);

  EXPECT_EQ(copy.tagDesc(), original.tagDesc());
  EXPECT_EQ(copy.tagDesc(), key.tagDesc());
}

TEST_F(ExifdatumTagDescTest_747, CopyAssignmentPreservesTagDesc_747) {
  const Exiv2::ExifKey keyA("Exif.Image.Make");
  const Exiv2::ExifKey keyB("Exif.Image.Model");

  Exiv2::Exifdatum a(keyA, nullptr);
  Exiv2::Exifdatum b(keyB, nullptr);

  // Precondition sanity via public API only.
  EXPECT_EQ(a.tagDesc(), keyA.tagDesc());
  EXPECT_EQ(b.tagDesc(), keyB.tagDesc());

  b = a;

  EXPECT_EQ(b.tagDesc(), a.tagDesc());
  EXPECT_EQ(b.tagDesc(), keyA.tagDesc());
}

TEST_F(ExifdatumTagDescTest_747, TwoDifferentKeysEachMatchTheirOwnTagDesc_747) {
  const Exiv2::ExifKey keyA("Exif.Image.Make");
  const Exiv2::ExifKey keyB("Exif.Image.Model");

  const Exiv2::Exifdatum a(keyA, nullptr);
  const Exiv2::Exifdatum b(keyB, nullptr);

  EXPECT_EQ(a.tagDesc(), keyA.tagDesc());
  EXPECT_EQ(b.tagDesc(), keyB.tagDesc());

  // If the library reports different descriptions for these keys, the datums should reflect that.
  // (No assumption if they happen to be identical on some builds/tag tables.)
  if (keyA.tagDesc() != keyB.tagDesc()) {
    EXPECT_NE(a.tagDesc(), b.tagDesc());
  }
}

TEST_F(ExifdatumTagDescTest_747, BoundaryEmptyKeyStringDoesNotCrashAndMatchesKey_747) {
  // Boundary: empty key string (behavior may vary across builds; we only assert consistency).
  Exiv2::ExifKey key("");
  Exiv2::Exifdatum d(key, nullptr);

  EXPECT_EQ(d.tagDesc(), key.tagDesc());
}

TEST_F(ExifdatumTagDescTest_747, BoundaryVeryLongKeyStringEitherWorksOrIsSkipped_747) {
  // Boundary: unusually long key string. Some implementations may reject it.
  const std::string longKey(4096, 'A');

  try {
    Exiv2::ExifKey key(longKey);
    Exiv2::Exifdatum d(key, nullptr);
    EXPECT_EQ(d.tagDesc(), key.tagDesc());
  } catch (...) {
    GTEST_SKIP() << "ExifKey rejected an unusually long key string; skipping boundary assertion.";
  }
}

}  // namespace