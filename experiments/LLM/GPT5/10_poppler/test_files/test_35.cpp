// File: gbase64_test_35.cpp
// Target: ./TestProjects/poppler/goo/gbase64.h
//
// TEST_ID: 35
//
// Notes:
// - We treat gbase64Encode(const std::vector<unsigned char>&) as a black box.
// - We only test observable behavior from the public inline wrapper:
//     * empty input returns empty std::string
//     * non-empty input returns *some* (possibly empty, but practically should be non-empty) std::string
// - We do NOT assume details of Base64 output formatting, padding, line breaks, etc.

#include <gtest/gtest.h>

#include <string>
#include <vector>

// Include the header under test.
#include "goo/gbase64.h"

namespace {

class GBase64EncodeVectorTest_35 : public ::testing::Test {
 protected:
  static std::vector<unsigned char> MakeVec(std::initializer_list<unsigned int> bytes) {
    std::vector<unsigned char> v;
    v.reserve(bytes.size());
    for (auto b : bytes) v.push_back(static_cast<unsigned char>(b & 0xFFu));
    return v;
  }
};

TEST_F(GBase64EncodeVectorTest_35, EmptyVectorReturnsEmptyString_35) {
  const std::vector<unsigned char> input;
  const std::string out = gbase64Encode(input);
  EXPECT_TRUE(out.empty());
}

TEST_F(GBase64EncodeVectorTest_35, EmptyVectorConstRefReturnsEmptyString_35) {
  const std::vector<unsigned char> input = {};
  const std::string out = gbase64Encode(input);
  EXPECT_EQ(out, std::string());
}

TEST_F(GBase64EncodeVectorTest_35, NonEmptyVectorDoesNotCrashAndReturnsString_35) {
  const auto input = MakeVec({0x00});
  const std::string out = gbase64Encode(input);

  // Black-box, minimal observable expectations:
  // - Must return a valid std::string object (already true if we got here).
  // - For non-empty input, it's reasonable to expect some output (base64 encoding),
  //   but we avoid asserting exact content.
  EXPECT_FALSE(out.empty());
}

TEST_F(GBase64EncodeVectorTest_35, MultipleBytesDoesNotCrashAndReturnsNonEmpty_35) {
  const auto input = MakeVec({0x00, 0x01, 0x02, 0x7F, 0x80, 0xFE, 0xFF});
  const std::string out = gbase64Encode(input);
  EXPECT_FALSE(out.empty());
}

TEST_F(GBase64EncodeVectorTest_35, DeterministicForSameInput_35) {
  const auto input = MakeVec({0x10, 0x20, 0x30, 0x40, 0x50});
  const std::string out1 = gbase64Encode(input);
  const std::string out2 = gbase64Encode(input);

  // Encoding should be deterministic for identical input.
  EXPECT_EQ(out1, out2);
}

TEST_F(GBase64EncodeVectorTest_35, DifferentInputsProduceDifferentOutputsInSimpleCase_35) {
  // We avoid relying on full base64 rules, but in typical encoders,
  // different 1-byte inputs should yield different outputs.
  const auto inputA = MakeVec({0x00});
  const auto inputB = MakeVec({0x01});

  const std::string outA = gbase64Encode(inputA);
  const std::string outB = gbase64Encode(inputB);

  EXPECT_FALSE(outA.empty());
  EXPECT_FALSE(outB.empty());
  EXPECT_NE(outA, outB);
}

TEST_F(GBase64EncodeVectorTest_35, HandlesEmbeddedNullBytes_35) {
  const auto input = MakeVec({0x41, 0x00, 0x42, 0x00, 0x43});  // 'A',0,'B',0,'C'
  const std::string out = gbase64Encode(input);

  // Observable: should encode binary data, not treat 0x00 as terminator.
  EXPECT_FALSE(out.empty());
}

TEST_F(GBase64EncodeVectorTest_35, LargeInputBoundaryDoesNotCrash_35) {
  // Boundary-ish test: ensure it can handle a reasonably large vector.
  // Keep size moderate to avoid slowing down CI.
  std::vector<unsigned char> input(64 * 1024);
  for (size_t i = 0; i < input.size(); ++i) input[i] = static_cast<unsigned char>(i & 0xFFu);

  const std::string out = gbase64Encode(input);
  EXPECT_FALSE(out.empty());

  // Determinism check for same buffer.
  const std::string out2 = gbase64Encode(input);
  EXPECT_EQ(out, out2);
}

}  // namespace