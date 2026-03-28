// TEST_ID is 36
//
// Unit tests for gbase64Encode in ./TestProjects/poppler/goo/gbase64.cc
//
// Constraints followed:
// - Treat implementation as black box (no re-implementation of internal logic like b64encodeTriplet).
// - Test only via observable behavior (returned std::string).
// - Cover normal, boundary, and error-ish/edge cases observable through interface.

#include <gtest/gtest.h>

#include <array>
#include <cstddef>
#include <cstdint>
#include <string>
#include <vector>

// Forward declaration (function is implemented in the codebase).
std::string gbase64Encode(const void *input, size_t len);

namespace {

bool IsBase64CharOrPad(char c) {
  return (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9') || c == '+' ||
         c == '/' || c == '=';
}

}  // namespace

class GBase64EncodeTest_36 : public ::testing::Test {};

// Normal operation: known vectors (RFC 4648 examples are widely used).
TEST_F(GBase64EncodeTest_36, EncodesKnownAsciiVectors_36) {
  const char *s1 = "f";
  const char *s2 = "fo";
  const char *s3 = "foo";
  const char *s4 = "foob";
  const char *s5 = "fooba";
  const char *s6 = "foobar";

  EXPECT_EQ(gbase64Encode(s1, 1), "Zg==");
  EXPECT_EQ(gbase64Encode(s2, 2), "Zm8=");
  EXPECT_EQ(gbase64Encode(s3, 3), "Zm9v");
  EXPECT_EQ(gbase64Encode(s4, 4), "Zm9vYg==");
  EXPECT_EQ(gbase64Encode(s5, 5), "Zm9vYmE=");
  EXPECT_EQ(gbase64Encode(s6, 6), "Zm9vYmFy");
}

// Boundary: empty input should produce empty output.
TEST_F(GBase64EncodeTest_36, EmptyLengthReturnsEmptyString_36) {
  const std::array<unsigned char, 1> dummy{{0xAB}};  // pointer is valid even if len==0
  EXPECT_EQ(gbase64Encode(dummy.data(), 0), "");
}

// Boundary: output length should be 4 * ceil(len/3).
TEST_F(GBase64EncodeTest_36, OutputLengthMatchesBase64ExpansionRule_36) {
  std::vector<unsigned char> data(10);
  for (size_t i = 0; i < data.size(); ++i) data[i] = static_cast<unsigned char>(i);

  for (size_t len = 0; len <= data.size(); ++len) {
    const std::string out = gbase64Encode(data.data(), len);
    const size_t expected = ((len + 2) / 3) * 4;
    EXPECT_EQ(out.size(), expected) << "len=" << len;
  }
}

// Boundary: padding behavior visible via '=' placement for len%3.
TEST_F(GBase64EncodeTest_36, AddsCorrectPaddingForRemainders_36) {
  const unsigned char bytes1[] = {0x01};
  const unsigned char bytes2[] = {0x01, 0x02};
  const unsigned char bytes3[] = {0x01, 0x02, 0x03};
  const unsigned char bytes4[] = {0x01, 0x02, 0x03, 0x04};
  const unsigned char bytes5[] = {0x01, 0x02, 0x03, 0x04, 0x05};

  const std::string o1 = gbase64Encode(bytes1, 1);
  ASSERT_EQ(o1.size(), 4u);
  EXPECT_EQ(o1[2], '=');
  EXPECT_EQ(o1[3], '=');

  const std::string o2 = gbase64Encode(bytes2, 2);
  ASSERT_EQ(o2.size(), 4u);
  EXPECT_NE(o2[2], '=');  // remainder 2 -> only last char padded
  EXPECT_EQ(o2[3], '=');

  const std::string o3 = gbase64Encode(bytes3, 3);
  ASSERT_EQ(o3.size(), 4u);
  EXPECT_NE(o3[2], '=');
  EXPECT_NE(o3[3], '=');

  const std::string o4 = gbase64Encode(bytes4, 4);
  ASSERT_EQ(o4.size(), 8u);
  EXPECT_EQ(o4[6], '=');
  EXPECT_EQ(o4[7], '=');

  const std::string o5 = gbase64Encode(bytes5, 5);
  ASSERT_EQ(o5.size(), 8u);
  EXPECT_NE(o5[6], '=');
  EXPECT_EQ(o5[7], '=');
}

// Normal: determinism (same input => same output), and not dependent on pointer identity.
TEST_F(GBase64EncodeTest_36, DeterministicForSameBytes_36) {
  std::vector<unsigned char> a = {0x00, 0x10, 0x20, 0x30, 0xFF};
  std::vector<unsigned char> b = a;  // different storage

  const std::string oa1 = gbase64Encode(a.data(), a.size());
  const std::string oa2 = gbase64Encode(a.data(), a.size());
  const std::string ob = gbase64Encode(b.data(), b.size());

  EXPECT_EQ(oa1, oa2);
  EXPECT_EQ(oa1, ob);
}

// Normal: binary data should encode to valid base64 alphabet + '=' only.
TEST_F(GBase64EncodeTest_36, OutputContainsOnlyBase64AlphabetAndPadding_36) {
  std::vector<unsigned char> data(256);
  for (size_t i = 0; i < data.size(); ++i) data[i] = static_cast<unsigned char>(i);

  const std::string out = gbase64Encode(data.data(), data.size());
  ASSERT_FALSE(out.empty());

  for (char c : out) {
    EXPECT_TRUE(IsBase64CharOrPad(c)) << "Unexpected char: " << static_cast<int>(static_cast<unsigned char>(c));
  }
}

// Edge / error-ish: if len==0, nullptr input should still be safe/produce empty string (observable behavior).
TEST_F(GBase64EncodeTest_36, NullptrWithZeroLengthReturnsEmptyString_36) {
  EXPECT_EQ(gbase64Encode(nullptr, 0), "");
}