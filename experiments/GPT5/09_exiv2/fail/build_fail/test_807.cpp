// TEST_ID: 807
// File: string_value_base_test_807.cpp

#include <gtest/gtest.h>

#include <cstdint>
#include <cstring>
#include <sstream>
#include <string>
#include <vector>

#include "exiv2/value.hpp"

namespace {

class StringValueBaseTest_807 : public ::testing::Test {
 protected:
  // Helper to build a StringValueBase with a "string-like" TypeId.
  // We avoid assuming too much: if multiple string TypeIds exist in the codebase,
  // asciiString is the most common in Exiv2. If your tree uses a different one,
  // adjust here (e.g., string, comment, xmpText, etc.).
  static Exiv2::TypeId StringTypeId() { return Exiv2::asciiString; }
};

TEST_F(StringValueBaseTest_807, ConstructWithNonEmptyString_SizeMatchesLength_807) {
  const std::string s = "abc";
  Exiv2::StringValueBase v(StringTypeId(), s);

  EXPECT_EQ(v.size(), s.size());
}

TEST_F(StringValueBaseTest_807, ConstructWithEmptyString_SizeIsZero_807) {
  const std::string s;
  Exiv2::StringValueBase v(StringTypeId(), s);

  EXPECT_EQ(v.size(), 0u);
}

TEST_F(StringValueBaseTest_807, ConstructWithEmbeddedNulls_SizeCountsNullBytes_807) {
  const char raw[] = {'a', '\0', 'b'};
  const std::string s(raw, sizeof(raw));  // size == 3
  Exiv2::StringValueBase v(StringTypeId(), s);

  EXPECT_EQ(v.size(), s.size());
  EXPECT_EQ(v.size(), 3u);
}

TEST_F(StringValueBaseTest_807, ReadFromStdString_UpdatesSizeToNewBufferLength_807) {
  Exiv2::StringValueBase v(StringTypeId(), "initial");

  const std::string next = "hi";
  (void)v.read(next);

  EXPECT_EQ(v.size(), next.size());
}

TEST_F(StringValueBaseTest_807, ReadFromByteBuffer_UpdatesSizeToLen_807) {
  Exiv2::StringValueBase v(StringTypeId(), "initial");

  const unsigned char raw[] = {'x', 'y', 'z', '\0', 'w'};
  const size_t len = sizeof(raw);
  (void)v.read(reinterpret_cast<const Exiv2::byte*>(raw), len, Exiv2::littleEndian);

  EXPECT_EQ(v.size(), len);
}

TEST_F(StringValueBaseTest_807, Copy_ReturnsSizeAndCopiesThatManyBytes_807) {
  const unsigned char raw[] = {'A', 'B', 'C', '\0', 'D'};
  const size_t len = sizeof(raw);

  Exiv2::StringValueBase v(StringTypeId(), "");
  (void)v.read(reinterpret_cast<const Exiv2::byte*>(raw), len, Exiv2::littleEndian);

  std::vector<Exiv2::byte> out(v.size());
  const size_t copied = v.copy(out.data(), Exiv2::littleEndian);

  EXPECT_EQ(copied, v.size());
  ASSERT_EQ(out.size(), len);
  EXPECT_EQ(0, std::memcmp(out.data(), raw, len));
}

TEST_F(StringValueBaseTest_807, LargeString_SizeMatchesLength_807) {
  const size_t kLarge = 1'000'000;
  const std::string s(kLarge, 'x');

  Exiv2::StringValueBase v(StringTypeId(), s);

  EXPECT_EQ(v.size(), kLarge);
}

}  // namespace