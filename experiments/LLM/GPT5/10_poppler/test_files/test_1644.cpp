// Decrypt_sha512_test_1644.cc
#include <gtest/gtest.h>

#include <array>
#include <cstdint>
#include <cstring>
#include <iomanip>
#include <sstream>
#include <string>
#include <vector>

// The function under test is `static` in Decrypt.cc, so we include the implementation
// into this test translation unit to access it without modifying production code.
#include "Decrypt.cc"

namespace {

using Digest64 = std::array<unsigned char, 64>;

static std::string ToHex(const Digest64 &d) {
  std::ostringstream oss;
  oss << std::hex << std::setfill('0');
  for (unsigned char b : d) {
    oss << std::setw(2) << static_cast<unsigned int>(b);
  }
  return oss.str();
}

static Digest64 ComputeSha512(const unsigned char *msg, int msgLen) {
  Digest64 out{};
  sha512(const_cast<unsigned char *>(msg), msgLen, out.data());
  return out;
}

static Digest64 ComputeSha512(const std::string &s) {
  return ComputeSha512(reinterpret_cast<const unsigned char *>(s.data()),
                       static_cast<int>(s.size()));
}

class Sha512Test_1644 : public ::testing::Test {};

TEST_F(Sha512Test_1644, DeterministicSameInput_1644) {
  const std::string msg = "abc";
  const Digest64 d1 = ComputeSha512(msg);
  const Digest64 d2 = ComputeSha512(msg);
  EXPECT_EQ(d1, d2);
}

TEST_F(Sha512Test_1644, EmptyStringKnownVector_1644) {
  // SHA-512("") (NIST/FIPS test vector)
  const std::string expected =
      "cf83e1357eefb8bdf1542850d66d8007d620e4050b5715dc83f4a921d36ce9ce"
      "47d0d13c5d85f2b0ff8318d2877eec2f63b931bd47417a81a538327af927da3e";
  const Digest64 d = ComputeSha512(std::string());
  EXPECT_EQ(ToHex(d), expected);
}

TEST_F(Sha512Test_1644, NullMessagePointerWithZeroLengthDoesNotCrashAndMatchesEmpty_1644) {
  // For msgLen==0, the function should not need to dereference msg.
  const std::string expected =
      "cf83e1357eefb8bdf1542850d66d8007d620e4050b5715dc83f4a921d36ce9ce"
      "47d0d13c5d85f2b0ff8318d2877eec2f63b931bd47417a81a538327af927da3e";
  const Digest64 d = ComputeSha512(nullptr, 0);
  EXPECT_EQ(ToHex(d), expected);
}

TEST_F(Sha512Test_1644, AbcKnownVector_1644) {
  // SHA-512("abc")
  const std::string expected =
      "ddaf35a193617abacc417349ae20413112e6fa4e89a97ea20a9eeee64b55d39a"
      "2192992a274fc1a836ba3c23a3feebbd454d4423643ce80e2a9ac94fa54ca49f";
  const Digest64 d = ComputeSha512("abc");
  EXPECT_EQ(ToHex(d), expected);
}

TEST_F(Sha512Test_1644, QuickBrownFoxKnownVector_1644) {
  // SHA-512("The quick brown fox jumps over the lazy dog")
  const std::string msg = "The quick brown fox jumps over the lazy dog";
  const std::string expected =
      "07e547d9586f6a73f73fbac0435ed76951218fb7d0c8d788a309d785436bbb64"
      "2e93a252a954f23912547d1e8a3b5ed6e1bfd7097821233fa0538f3db854fee6";
  const Digest64 d = ComputeSha512(msg);
  EXPECT_EQ(ToHex(d), expected);
}

TEST_F(Sha512Test_1644, QuickBrownFoxWithPeriodKnownVector_1644) {
  // SHA-512("The quick brown fox jumps over the lazy dog.")
  const std::string msg = "The quick brown fox jumps over the lazy dog.";
  const std::string expected =
      "91ea1245f20d46ae9a037a989f54f1f790f0a47607eeb8a14d12890cea77a1bb"
      "c6c7ed9cf205e67b7f2b8fd4c7dfd3a7a8617e45f3c463d481c7e586c39ac1ed";
  const Digest64 d = ComputeSha512(msg);
  EXPECT_EQ(ToHex(d), expected);
}

TEST_F(Sha512Test_1644, LongNistKnownVector_1644) {
  // SHA-512("abcdbc...nopq") (multi-block style known test vector)
  const std::string msg =
      "abcdbcdecdefdefgefghfghighijhijkijkljklmklmnlmnomnopnopq";
  const std::string expected =
      "204a8fc6dda82f0a0ced7beb8e08a41657c16ef468b228a8279be331a703c335"
      "96fd15c13b1b07f9aa1d3bea57789ca031ad85c7a71dd70354ec631238ca3445";
  const Digest64 d = ComputeSha512(msg);
  EXPECT_EQ(ToHex(d), expected);
}

TEST_F(Sha512Test_1644, OneMillionAsKnownVector_1644) {
  // SHA-512("a" repeated 1,000,000 times)
  const std::string expected =
      "e718483d0ce769644e2e42c7bc15b4638e1f98b13b2044285632a803afa973eb"
      "de0ff244877ea60a4cb0432ce577c31beb009c5c2c49aa2e4eadb217ad8cc09b";

  std::string msg;
  msg.assign(1'000'000, 'a');
  const Digest64 d = ComputeSha512(msg);
  EXPECT_EQ(ToHex(d), expected);
}

TEST_F(Sha512Test_1644, HashBufferIsOverwritten_1644) {
  std::array<unsigned char, 64> out;
  out.fill(0xAA);

  const std::string msg = "abc";
  sha512(reinterpret_cast<unsigned char *>(const_cast<char *>(msg.data())),
         static_cast<int>(msg.size()), out.data());

  // Matches known vector for "abc"
  const std::string expected =
      "ddaf35a193617abacc417349ae20413112e6fa4e89a97ea20a9eeee64b55d39a"
      "2192992a274fc1a836ba3c23a3feebbd454d4423643ce80e2a9ac94fa54ca49f";
  EXPECT_EQ(ToHex(out), expected);

  // And it should not remain entirely as the prefilled pattern.
  bool any_changed = false;
  for (unsigned char b : out) {
    if (b != 0xAA) {
      any_changed = true;
      break;
    }
  }
  EXPECT_TRUE(any_changed);
}

#if GTEST_HAS_DEATH_TEST
TEST_F(Sha512Test_1644, DeathOnNullHashPointerWithNonZeroLength_1644) {
  const std::string msg = "abc";
  ASSERT_DEATH(
      sha512(reinterpret_cast<unsigned char *>(const_cast<char *>(msg.data())),
             static_cast<int>(msg.size()), nullptr),
      "");
}

TEST_F(Sha512Test_1644, DeathOnNullMessagePointerWithNonZeroLength_1644) {
  std::array<unsigned char, 64> out{};
  ASSERT_DEATH(sha512(nullptr, 1, out.data()), "");
}
#endif

}  // namespace