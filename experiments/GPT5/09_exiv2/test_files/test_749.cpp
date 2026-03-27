// SPDX-License-Identifier: GPL-2.0-or-later
// File: test_exifdatum_ifdid_749.cpp

#include <gtest/gtest.h>

#include <exiv2/exif.hpp>
#include <exiv2/tags.hpp>

namespace {

using Exiv2::Exifdatum;
using Exiv2::ExifKey;
using Exiv2::IfdId;

TEST(ExifdatumIfdIdTest_749, ReturnsSameAsKeyIfdId_WithStringKeyCtor_749) {
  const ExifKey key("Exif.Image.Make");  // Key format is part of Exiv2 public API.
  const Exifdatum datum(key, nullptr);

  // Black-box observable behavior: Exifdatum::ifdId should match its key's ifdId.
  EXPECT_EQ(datum.ifdId(), key.ifdId());
}

TEST(ExifdatumIfdIdTest_749, ReturnsSameAsKeyIfdId_WithTagAndGroupCtor_749) {
  const uint16_t anyTag = 0x010F;               // Tag value itself isn't asserted; only used to build a key.
  const std::string groupName = "Exif.Image";   // Group string is part of Exiv2 key vocabulary.
  const ExifKey key(anyTag, groupName);
  const Exifdatum datum(key, nullptr);

  EXPECT_EQ(datum.ifdId(), key.ifdId());
}

TEST(ExifdatumIfdIdTest_749, CopyConstructedDatumPreservesIfdId_749) {
  const ExifKey key("Exif.Photo.DateTimeOriginal");
  const Exifdatum original(key, nullptr);

  const Exifdatum copied(original);

  // Observable: ifdId of the copy should be the same as the original.
  EXPECT_EQ(copied.ifdId(), original.ifdId());
  // And still consistent with the key used to construct the original.
  EXPECT_EQ(copied.ifdId(), key.ifdId());
}

TEST(ExifdatumIfdIdTest_749, CopyAssignedDatumPreservesIfdId_749) {
  const ExifKey keyA("Exif.Image.Make");
  const Exifdatum source(keyA, nullptr);

  const ExifKey keyB("Exif.Photo.DateTimeOriginal");
  Exifdatum target(keyB, nullptr);

  // Precondition sanity (not assuming anything about actual IfdId values).
  EXPECT_EQ(source.ifdId(), keyA.ifdId());
  EXPECT_EQ(target.ifdId(), keyB.ifdId());

  target = source;

  // Observable: after copy assignment, target should report the same ifdId as source.
  EXPECT_EQ(target.ifdId(), source.ifdId());
}

TEST(ExifdatumIfdIdTest_749, SelfAssignmentKeepsIfdIdStable_749) {
  const ExifKey key("Exif.Image.Make");
  Exifdatum datum(key, nullptr);

  const IfdId before = datum.ifdId();
  datum = datum;
  const IfdId after = datum.ifdId();

  EXPECT_EQ(after, before);
  EXPECT_EQ(after, key.ifdId());
}

}  // namespace