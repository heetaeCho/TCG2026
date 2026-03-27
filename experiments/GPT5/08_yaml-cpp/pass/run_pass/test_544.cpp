// File: ./TestProjects/yaml-cpp/test/binary_encode_base64_test_544.cpp

#include <gtest/gtest.h>

#include <cstddef>
#include <string>
#include <vector>

#include <yaml-cpp/binary.h>  // Expected to declare YAML::EncodeBase64

namespace {

std::string EncodeVec(const std::vector<unsigned char>& v) {
  const unsigned char* ptr = v.empty() ? nullptr : v.data();
  return YAML::EncodeBase64(ptr, v.size());
}

bool IsBase64CharOrPad(char c) {
  // RFC 4648 base64 alphabet + pad '='
  if (c >= 'A' && c <= 'Z') return true;
  if (c >= 'a' && c <= 'z') return true;
  if (c >= '0' && c <= '9') return true;
  if (c == '+' || c == '/' || c == '=') return true;
  return false;
}

}  // namespace

class EncodeBase64Test_544 : public ::testing::Test {};

// -------------------- Normal operation (known vectors) --------------------

TEST_F(EncodeBase64Test_544, EncodesEmptyInputToEmptyString_544) {
  // Avoid passing a non-null pointer for size 0; nullptr should be acceptable.
  EXPECT_NO_THROW({
    std::string out = YAML::EncodeBase64(nullptr, 0);
    EXPECT_EQ(out, "");
  });
}

TEST_F(EncodeBase64Test_544, EncodesSingleByteAscii_f_544) {
  const std::vector<unsigned char> data = {'f'};
  EXPECT_EQ(EncodeVec(data), "Zg==");
}

TEST_F(EncodeBase64Test_544, EncodesTwoBytesAscii_fo_544) {
  const std::vector<unsigned char> data = {'f', 'o'};
  EXPECT_EQ(EncodeVec(data), "Zm8=");
}

TEST_F(EncodeBase64Test_544, EncodesThreeBytesAscii_foo_544) {
  const std::vector<unsigned char> data = {'f', 'o', 'o'};
  EXPECT_EQ(EncodeVec(data), "Zm9v");
}

TEST_F(EncodeBase64Test_544, EncodesFourBytesAscii_foob_544) {
  const std::vector<unsigned char> data = {'f', 'o', 'o', 'b'};
  EXPECT_EQ(EncodeVec(data), "Zm9vYg==");
}

TEST_F(EncodeBase64Test_544, EncodesFiveBytesAscii_fooba_544) {
  const std::vector<unsigned char> data = {'f', 'o', 'o', 'b', 'a'};
  EXPECT_EQ(EncodeVec(data), "Zm9vYmE=");
}

TEST_F(EncodeBase64Test_544, EncodesSixBytesAscii_foobar_544) {
  const std::vector<unsigned char> data = {'f', 'o', 'o', 'b', 'a', 'r'};
  EXPECT_EQ(EncodeVec(data), "Zm9vYmFy");
}

// -------------------- Boundary conditions (remainder sizes) --------------------

TEST_F(EncodeBase64Test_544, EncodesRemainder1_WithPadding_544) {
  const std::vector<unsigned char> data = {0x00};
  EXPECT_EQ(EncodeVec(data), "AA==");
}

TEST_F(EncodeBase64Test_544, EncodesRemainder2_WithPadding_544) {
  const std::vector<unsigned char> data = {0x00, 0x00};
  EXPECT_EQ(EncodeVec(data), "AAA=");
}

TEST_F(EncodeBase64Test_544, EncodesExactlyThreeBytes_NoPadding_544) {
  const std::vector<unsigned char> data = {0x00, 0x00, 0x00};
  EXPECT_EQ(EncodeVec(data), "AAAA");
}

TEST_F(EncodeBase64Test_544, EncodesMixedBinaryIncludingFF_544) {
  const std::vector<unsigned char> data1 = {0xff};
  const std::vector<unsigned char> data2 = {0xff, 0xee};
  const std::vector<unsigned char> data3 = {0xff, 0xee, 0xdd};

  EXPECT_EQ(EncodeVec(data1), "/w==");
  EXPECT_EQ(EncodeVec(data2), "/+4=");
  EXPECT_EQ(EncodeVec(data3), "/+7d");
}

// -------------------- Observable properties --------------------

TEST_F(EncodeBase64Test_544, OutputLengthIsMultipleOfFourForNonEmptyInput_544) {
  const std::vector<std::vector<unsigned char>> cases = {
      {0x01},
      {0x01, 0x02},
      {0x01, 0x02, 0x03},
      {0x01, 0x02, 0x03, 0x04},
      {0x00, 0xff, 0x10, 0x20, 0x30},
  };

  for (const auto& v : cases) {
    const std::string out = EncodeVec(v);
    ASSERT_FALSE(out.empty());
    EXPECT_EQ(out.size() % 4, 0u) << "Unexpected size for input length " << v.size();
  }
}

TEST_F(EncodeBase64Test_544, OutputUsesOnlyBase64AlphabetOrPad_544) {
  const std::vector<unsigned char> data = {
      0x00, 0x01, 0x02, 0x10, 0x20, 0x7f, 0x80, 0xfe, 0xff};
  const std::string out = EncodeVec(data);

  ASSERT_FALSE(out.empty());
  for (char c : out) {
    EXPECT_TRUE(IsBase64CharOrPad(c)) << "Unexpected character: " << c;
  }
}