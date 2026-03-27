// TEST_ID: 622
#include <gtest/gtest.h>

#include <algorithm>
#include <cstddef>
#include <vector>

#include "yaml-cpp/binary.h"
#include "yaml-cpp/node/convert.h"
#include "yaml-cpp/node/node.h"

namespace {

class ConvertBinaryDecodeTest_622 : public ::testing::Test {
 protected:
  static void ExpectBinaryEquals_622(const YAML::Binary& bin,
                                    const std::vector<unsigned char>& expected) {
    ASSERT_EQ(bin.size(), expected.size());
    const unsigned char* data = bin.data();
    if (expected.empty()) {
      // data() may be nullptr for empty; nothing else to check.
      return;
    }
    ASSERT_NE(data, nullptr);
    for (std::size_t i = 0; i < expected.size(); ++i) {
      EXPECT_EQ(data[i], expected[i]) << "byte index " << i;
    }
  }

  static YAML::Binary MakeBinary_622(const std::vector<unsigned char>& bytes) {
    // Use the public ctor (const unsigned char*, size) to seed content.
    return YAML::Binary(bytes.empty() ? nullptr : bytes.data(), bytes.size());
  }
};

TEST_F(ConvertBinaryDecodeTest_622, ReturnsFalseForNonScalarNodeAndDoesNotModifyRhs_622) {
  YAML::Node nonScalar(YAML::NodeType::Sequence);
  nonScalar.push_back(1);

  const std::vector<unsigned char> originalBytes{0x10, 0x20, 0x30};
  YAML::Binary rhs = MakeBinary_622(originalBytes);

  const bool ok = YAML::decode(nonScalar, rhs);

  EXPECT_FALSE(ok);
  ExpectBinaryEquals_622(rhs, originalBytes);
}

TEST_F(ConvertBinaryDecodeTest_622, ReturnsTrueAndDecodesValidBase64ScalarIntoRhs_622) {
  // "AQID" is standard base64 for bytes {0x01, 0x02, 0x03}.
  YAML::Node scalar("AQID");

  YAML::Binary rhs;  // start empty / default
  const bool ok = YAML::decode(scalar, rhs);

  EXPECT_TRUE(ok);
  ExpectBinaryEquals_622(rhs, std::vector<unsigned char>({0x01, 0x02, 0x03}));
}

TEST_F(ConvertBinaryDecodeTest_622, OnSuccessReplacesExistingRhsContents_622) {
  YAML::Node scalar("AA==");  // base64 for single byte {0x00}

  const std::vector<unsigned char> originalBytes{0xDE, 0xAD, 0xBE, 0xEF};
  YAML::Binary rhs = MakeBinary_622(originalBytes);

  const bool ok = YAML::decode(scalar, rhs);

  EXPECT_TRUE(ok);
  ExpectBinaryEquals_622(rhs, std::vector<unsigned char>({0x00}));
}

TEST_F(ConvertBinaryDecodeTest_622, EmptyScalarSucceedsAndClearsRhsToEmpty_622) {
  YAML::Node emptyScalar("");  // boundary: empty scalar

  const std::vector<unsigned char> originalBytes{0x01, 0x02};
  YAML::Binary rhs = MakeBinary_622(originalBytes);

  const bool ok = YAML::decode(emptyScalar, rhs);

  EXPECT_TRUE(ok);
  ExpectBinaryEquals_622(rhs, std::vector<unsigned char>({}));
}

TEST_F(ConvertBinaryDecodeTest_622, InvalidNonEmptyBase64ReturnsFalseAndDoesNotModifyRhs_622) {
  // Choose a clearly invalid base64 string; if decoding yields empty for non-empty input,
  // decode() should return false and leave rhs unchanged.
  YAML::Node invalidScalar("!!!not_base64!!!");

  const std::vector<unsigned char> originalBytes{0xAB, 0xCD, 0xEF};
  YAML::Binary rhs = MakeBinary_622(originalBytes);

  const bool ok = YAML::decode(invalidScalar, rhs);

  EXPECT_FALSE(ok);
  ExpectBinaryEquals_622(rhs, originalBytes);
}

}  // namespace