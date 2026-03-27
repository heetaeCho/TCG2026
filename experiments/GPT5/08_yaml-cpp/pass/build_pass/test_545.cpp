// TEST_ID: 545
#include <gtest/gtest.h>

#include <string>
#include <vector>

#include <yaml-cpp/binary.h>

namespace {

class DecodeBase64Test_545 : public ::testing::Test {
protected:
  static std::vector<unsigned char> ToUChars(const std::string& s) {
    return std::vector<unsigned char>(s.begin(), s.end());
  }

  static std::string ToString(const std::vector<unsigned char>& v) {
    return std::string(v.begin(), v.end());
  }
};

TEST_F(DecodeBase64Test_545, EmptyInputReturnsEmptyVector_545) {
  const auto out = YAML::DecodeBase64("");
  EXPECT_TRUE(out.empty());
}

TEST_F(DecodeBase64Test_545, DecodesKnownVectorsWithoutPadding_545) {
  // "Man" -> "TWFu"
  const auto out = YAML::DecodeBase64("TWFu");
  EXPECT_EQ(out, ToUChars("Man"));
}

TEST_F(DecodeBase64Test_545, DecodesKnownVectorsWithOnePaddingChar_545) {
  // "Ma" -> "TWE="
  const auto out = YAML::DecodeBase64("TWE=");
  EXPECT_EQ(out, ToUChars("Ma"));
}

TEST_F(DecodeBase64Test_545, DecodesKnownVectorsWithTwoPaddingChars_545) {
  // "M" -> "TQ=="
  const auto out = YAML::DecodeBase64("TQ==");
  EXPECT_EQ(out, ToUChars("M"));
}

TEST_F(DecodeBase64Test_545, IgnoresWhitespaceInInput_545) {
  // Insert whitespace/newlines into a valid base64 stream.
  const std::string with_ws = " \nT W\tF\r u  ";
  const auto out = YAML::DecodeBase64(with_ws);
  EXPECT_EQ(out, ToUChars("Man"));
}

TEST_F(DecodeBase64Test_545, InvalidCharacterReturnsEmptyVector_545) {
  // '$' is not valid in base64.
  const auto out = YAML::DecodeBase64("TWFu$");
  EXPECT_TRUE(out.empty());
}

TEST_F(DecodeBase64Test_545, InvalidCharacterAfterValidQuartetReturnsEmptyVector_545) {
  // Even if a prefix is valid, an invalid character should make the call fail
  // (observable behavior: returns empty vector).
  const auto out = YAML::DecodeBase64("TWFuTQ==$");
  EXPECT_TRUE(out.empty());
}

TEST_F(DecodeBase64Test_545, OnlyWhitespaceReturnsEmptyVector_545) {
  const auto out = YAML::DecodeBase64(" \t\r\n ");
  EXPECT_TRUE(out.empty());
}

TEST_F(DecodeBase64Test_545, IncompleteQuartetProducesNoOutput_545) {
  // Boundary/error-like case: input length not sufficient to form a quartet.
  // Observable expectation for this implementation: no bytes are produced.
  EXPECT_TRUE(YAML::DecodeBase64("TQ").empty());
  EXPECT_TRUE(YAML::DecodeBase64("TQ=").empty());
  EXPECT_TRUE(YAML::DecodeBase64("TWE").empty());
}

TEST_F(DecodeBase64Test_545, DecodesRepeatedBlocksConsistently_545) {
  const int kRepeats = 64;
  std::string in;
  std::string expected;
  in.reserve(4 * kRepeats);
  expected.reserve(3 * kRepeats);

  for (int i = 0; i < kRepeats; ++i) {
    in += "TWFu";       // "Man"
    expected += "Man";
  }

  const auto out = YAML::DecodeBase64(in);
  EXPECT_EQ(ToString(out), expected);
}

}  // namespace