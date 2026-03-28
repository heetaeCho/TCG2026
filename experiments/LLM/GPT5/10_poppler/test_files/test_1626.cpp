// Decrypt_md5_test_1626.cc
#include <gtest/gtest.h>

#include <array>
#include <cctype>
#include <cstdint>
#include <cstring>
#include <string>
#include <vector>

#if __has_include("Decrypt.h")
#include "Decrypt.h"
#elif __has_include("poppler/Decrypt.h")
#include "poppler/Decrypt.h"
#else
// Fallback declaration (keeps the test buildable even if the header path differs).
void md5(const unsigned char *msg, int msgLen, unsigned char *digest);
#endif

namespace {

std::array<unsigned char, 16> HexToDigest(const char *hex32) {
  std::array<unsigned char, 16> out{};
  auto hexVal = [](char c) -> int {
    c = static_cast<char>(std::tolower(static_cast<unsigned char>(c)));
    if (c >= '0' && c <= '9') return c - '0';
    if (c >= 'a' && c <= 'f') return 10 + (c - 'a');
    return -1;
  };

  // Expect exactly 32 hex chars.
  ASSERT_NE(hex32, nullptr);
  ASSERT_EQ(std::strlen(hex32), 32u);

  for (int i = 0; i < 16; ++i) {
    int hi = hexVal(hex32[i * 2]);
    int lo = hexVal(hex32[i * 2 + 1]);
    ASSERT_GE(hi, 0);
    ASSERT_GE(lo, 0);
    out[i] = static_cast<unsigned char>((hi << 4) | lo);
  }
  return out;
}

void ExpectDigestEq(const unsigned char *actual,
                    const std::array<unsigned char, 16> &expected) {
  ASSERT_NE(actual, nullptr);
  for (int i = 0; i < 16; ++i) {
    EXPECT_EQ(actual[i], expected[i]) << "digest byte mismatch at index " << i;
  }
}

class Md5Test_1626 : public ::testing::Test {};

} // namespace

TEST_F(Md5Test_1626, ComputesEmptyStringDigest_1626) {
  std::array<unsigned char, 16> digest{};
  md5(reinterpret_cast<const unsigned char *>(""), 0, digest.data());

  const auto expected = HexToDigest("d41d8cd98f00b204e9800998ecf8427e");
  ExpectDigestEq(digest.data(), expected);
}

TEST_F(Md5Test_1626, ComputesKnownVectorAbc_1626) {
  std::array<unsigned char, 16> digest{};
  const char *msg = "abc";
  md5(reinterpret_cast<const unsigned char *>(msg),
      static_cast<int>(std::strlen(msg)), digest.data());

  const auto expected = HexToDigest("900150983cd24fb0d6963f7d28e17f72");
  ExpectDigestEq(digest.data(), expected);
}

TEST_F(Md5Test_1626, ComputesKnownVectorQuickBrownFox_1626) {
  std::array<unsigned char, 16> digest{};
  const char *msg = "The quick brown fox jumps over the lazy dog";
  md5(reinterpret_cast<const unsigned char *>(msg),
      static_cast<int>(std::strlen(msg)), digest.data());

  const auto expected = HexToDigest("9e107d9d372bb6826bd81d3542a419d6");
  ExpectDigestEq(digest.data(), expected);
}

TEST_F(Md5Test_1626, ComputesBinaryDataIncludingNullBytes_1626) {
  std::array<unsigned char, 16> digest{};
  const unsigned char bytes[] = {0x00, 0x01, 0x02, 0x03};
  md5(bytes, 4, digest.data());

  const auto expected = HexToDigest("37b59afd592725f9305e484a5d7f5168");
  ExpectDigestEq(digest.data(), expected);
}

TEST_F(Md5Test_1626, NegativeLengthDoesNotModifyDigest_1626) {
  std::array<unsigned char, 16> digest{};
  digest.fill(0xAA);

  const unsigned char dummy[] = {0x10, 0x20, 0x30};
  md5(dummy, -1, digest.data());

  // Observable behavior: early return; digest remains unchanged.
  for (int i = 0; i < 16; ++i) {
    EXPECT_EQ(digest[i], 0xAA) << "digest modified at index " << i;
  }
}

TEST_F(Md5Test_1626, LargeInputOneMillionAs_1626) {
  std::vector<unsigned char> msg(1'000'000, static_cast<unsigned char>('a'));

  std::array<unsigned char, 16> digest{};
  md5(msg.data(), static_cast<int>(msg.size()), digest.data());

  const auto expected = HexToDigest("7707d6ae4e027c70eea2a935c2296f21");
  ExpectDigestEq(digest.data(), expected);
}