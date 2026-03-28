// SPDX-License-Identifier: GPL-2.0-or-later

#include <gtest/gtest.h>

#include <cstring>
#include <vector>

#include "exiv2/exif.hpp"
#include "exiv2/exifkey.hpp"
#include "exiv2/types.hpp"
#include "exiv2/value.hpp"

namespace {

// Helper to build a valid ExifKey without depending on internal state.
// Common, stable Exif key string used across Exiv2.
Exiv2::ExifKey MakeTestKey() {
  return Exiv2::ExifKey("Exif.Image.Make");
}

}  // namespace

class ExifdatumTest_752 : public ::testing::Test {};

TEST_F(ExifdatumTest_752, CopyReturnsZeroWhenValueIsNull_752) {
  Exiv2::ExifKey key = MakeTestKey();

  // Construct with null Value pointer (observable behavior: copy() should return 0).
  Exiv2::Exifdatum datum(key, nullptr);

  std::vector<Exiv2::byte> buf(32, static_cast<Exiv2::byte>(0xAA));

  EXPECT_EQ(datum.copy(buf.data(), Exiv2::littleEndian), 0u);
  EXPECT_EQ(datum.copy(buf.data(), Exiv2::bigEndian), 0u);

  // Boundary: nullptr buffer should be fine when there is no value to copy.
  EXPECT_EQ(datum.copy(nullptr, Exiv2::littleEndian), 0u);
}

TEST_F(ExifdatumTest_752, CopyWritesSomeBytesWhenValueIsPresent_752) {
  Exiv2::ExifKey key = MakeTestKey();

  // Use a real Value instance from the public factory; Exifdatum is expected to take/clone it.
  auto v = Exiv2::Value::create(Exiv2::asciiString);
  ASSERT_NE(v, nullptr);

  Exiv2::Exifdatum datum(key, v.get());
  datum = std::string("Canon");  // use public assignment operator

  std::vector<Exiv2::byte> buf(128, static_cast<Exiv2::byte>(0xAA));
  const size_t n = datum.copy(buf.data(), Exiv2::littleEndian);

  EXPECT_GT(n, 0u);
  ASSERT_LE(n, buf.size());

  // Ensure the call had an observable effect in the written region (not all still 0xAA).
  bool any_changed = false;
  for (size_t i = 0; i < n; ++i) {
    if (buf[i] != static_cast<Exiv2::byte>(0xAA)) {
      any_changed = true;
      break;
    }
  }
  EXPECT_TRUE(any_changed);
}

TEST_F(ExifdatumTest_752, CopyIsRepeatableForSameInputs_752) {
  Exiv2::ExifKey key = MakeTestKey();
  auto v = Exiv2::Value::create(Exiv2::asciiString);
  ASSERT_NE(v, nullptr);

  Exiv2::Exifdatum datum(key, v.get());
  datum = std::string("Nikon");

  std::vector<Exiv2::byte> b1(128, static_cast<Exiv2::byte>(0x11));
  std::vector<Exiv2::byte> b2(128, static_cast<Exiv2::byte>(0x22));

  const size_t n1 = datum.copy(b1.data(), Exiv2::bigEndian);
  const size_t n2 = datum.copy(b2.data(), Exiv2::bigEndian);

  EXPECT_EQ(n1, n2);
  ASSERT_LE(n1, b1.size());
  ASSERT_LE(n2, b2.size());

  EXPECT_EQ(std::memcmp(b1.data(), b2.data(), n1), 0);
}

TEST_F(ExifdatumTest_752, CopyMatchesUnderlyingValueCopyWhenValuePresent_752) {
  Exiv2::ExifKey key = MakeTestKey();
  auto v = Exiv2::Value::create(Exiv2::asciiString);
  ASSERT_NE(v, nullptr);

  Exiv2::Exifdatum datum(key, v.get());
  datum = std::string("SONY");

  std::vector<Exiv2::byte> b_datum(128, static_cast<Exiv2::byte>(0xAA));
  std::vector<Exiv2::byte> b_value(128, static_cast<Exiv2::byte>(0xBB));

  const size_t n_datum = datum.copy(b_datum.data(), Exiv2::littleEndian);
  const size_t n_value = datum.value().copy(b_value.data(), Exiv2::littleEndian);

  EXPECT_EQ(n_datum, n_value);
  ASSERT_LE(n_datum, b_datum.size());
  ASSERT_LE(n_value, b_value.size());

  EXPECT_EQ(std::memcmp(b_datum.data(), b_value.data(), n_datum), 0);
}