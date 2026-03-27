// TEST_ID: 34
// Unit tests for ./TestProjects/poppler/goo/gbase64.h
//
// Target API:
//   inline std::string gbase64Encode(const std::vector<char> &input)
//
// Notes:
// - Treat implementation as a black box.
// - We only assert observable behavior guaranteed by the inline wrapper itself:
//   * empty input => returns empty std::string()
//   * non-empty input => must not return empty (base64 of >=1 byte is non-empty)
//   * determinism: same input => same output
//   * supports embedded '\0' bytes (vector<char> carries raw bytes)
//
// If the project also exposes a byte-pointer overload `gbase64Encode(const char*, size_t)`,
// these tests don't depend on its internal logic; they only validate the wrapper behavior.

#include <gtest/gtest.h>

#include <string>
#include <vector>

#include "goo/gbase64.h"

namespace {

class GBase64EncodeVectorTest_34 : public ::testing::Test {};

TEST_F(GBase64EncodeVectorTest_34, EmptyVectorReturnsEmptyString_34) {
  const std::vector<char> input;
  const std::string out = gbase64Encode(input);
  EXPECT_TRUE(out.empty());
  EXPECT_EQ(out, std::string());
}

TEST_F(GBase64EncodeVectorTest_34, SingleByteInputProducesNonEmptyString_34) {
  const std::vector<char> input = {'A'};
  const std::string out = gbase64Encode(input);

  EXPECT_FALSE(out.empty());
}

TEST_F(GBase64EncodeVectorTest_34, TwoBytesInputProducesNonEmptyString_34) {
  const std::vector<char> input = {'A', 'B'};
  const std::string out = gbase64Encode(input);

  EXPECT_FALSE(out.empty());
}

TEST_F(GBase64EncodeVectorTest_34, DeterministicForSameInput_34) {
  const std::vector<char> input = {'h', 'e', 'l', 'l', 'o'};
  const std::string out1 = gbase64Encode(input);
  const std::string out2 = gbase64Encode(input);

  EXPECT_EQ(out1, out2);
  EXPECT_FALSE(out1.empty());
}

TEST_F(GBase64EncodeVectorTest_34, DifferentInputsLikelyProduceDifferentOutputs_34) {
  // Base64 encoding is injective over byte sequences; different inputs should yield different outputs.
  // This is a property of base64 in general; we do not assume the internal implementation details.
  const std::vector<char> input1 = {'a'};
  const std::vector<char> input2 = {'b'};

  const std::string out1 = gbase64Encode(input1);
  const std::string out2 = gbase64Encode(input2);

  EXPECT_NE(out1, out2);
  EXPECT_FALSE(out1.empty());
  EXPECT_FALSE(out2.empty());
}

TEST_F(GBase64EncodeVectorTest_34, HandlesEmbeddedNullBytes_34) {
  // Ensure wrapper accepts raw bytes including '\0' and produces some output.
  const std::vector<char> input = {'A', '\0', 'B', '\0', 'C'};
  const std::string out = gbase64Encode(input);

  EXPECT_FALSE(out.empty());

  // Determinism with embedded NULs.
  const std::string out2 = gbase64Encode(input);
  EXPECT_EQ(out, out2);
}

TEST_F(GBase64EncodeVectorTest_34, LargeInputProducesNonEmptyString_34) {
  // Boundary-ish: larger buffer still works.
  std::vector<char> input;
  input.resize(4096);
  for (size_t i = 0; i < input.size(); ++i) {
    input[i] = static_cast<char>(i % 256);
  }

  const std::string out = gbase64Encode(input);
  EXPECT_FALSE(out.empty());

  // Deterministic as well.
  EXPECT_EQ(out, gbase64Encode(input));
}

}  // namespace