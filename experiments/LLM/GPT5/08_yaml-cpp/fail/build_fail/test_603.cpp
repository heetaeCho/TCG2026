// File: yaml-cpp/node/convert_null_decode_test_603.cpp

#include <gtest/gtest.h>

#include <yaml-cpp/yaml.h>

namespace {

// This test targets the observable behavior of:
// YAML::decode(const Node& node, _Null&) -> bool
// as shown in the provided partial implementation snippet.
class ConvertNullDecodeTest_603 : public ::testing::Test {};

TEST_F(ConvertNullDecodeTest_603, DecodeReturnsTrueForNullNode_603) {
  YAML::Node n;  // default-constructed Node is expected to be Null in yaml-cpp usage.
  YAML::_Null out{};
  EXPECT_TRUE(YAML::decode(n, out));
}

TEST_F(ConvertNullDecodeTest_603, DecodeReturnsTrueForExplicitNullScalar_603) {
  YAML::Node n = YAML::Load("null");
  YAML::_Null out{};
  EXPECT_TRUE(YAML::decode(n, out));
}

TEST_F(ConvertNullDecodeTest_603, DecodeReturnsTrueForTildeNullScalar_603) {
  YAML::Node n = YAML::Load("~");
  YAML::_Null out{};
  EXPECT_TRUE(YAML::decode(n, out));
}

TEST_F(ConvertNullDecodeTest_603, DecodeReturnsFalseForNonNullScalar_603) {
  YAML::Node n = YAML::Load("hello");
  YAML::_Null out{};
  EXPECT_FALSE(YAML::decode(n, out));
}

TEST_F(ConvertNullDecodeTest_603, DecodeReturnsFalseForNonNullIntegerScalar_603) {
  YAML::Node n = YAML::Load("123");
  YAML::_Null out{};
  EXPECT_FALSE(YAML::decode(n, out));
}

TEST_F(ConvertNullDecodeTest_603, DecodeReturnsFalseForEmptyStringScalar_603) {
  YAML::Node n = YAML::Load("\"\"");
  YAML::_Null out{};
  EXPECT_FALSE(YAML::decode(n, out));
}

TEST_F(ConvertNullDecodeTest_603, DecodeReturnsFalseForSequenceNode_603) {
  YAML::Node n = YAML::Load("[1, 2, 3]");
  YAML::_Null out{};
  EXPECT_FALSE(YAML::decode(n, out));
}

TEST_F(ConvertNullDecodeTest_603, DecodeReturnsFalseForMapNode_603) {
  YAML::Node n = YAML::Load("{a: 1}");
  YAML::_Null out{};
  EXPECT_FALSE(YAML::decode(n, out));
}

TEST_F(ConvertNullDecodeTest_603, DecodeDoesNotThrowForVariousNodeKinds_603) {
  YAML::_Null out{};

  EXPECT_NO_THROW({
    YAML::Node n1;  // Null
    (void)YAML::decode(n1, out);
  });

  EXPECT_NO_THROW({
    YAML::Node n2 = YAML::Load("null");  // Null scalar
    (void)YAML::decode(n2, out);
  });

  EXPECT_NO_THROW({
    YAML::Node n3 = YAML::Load("abc");  // Scalar
    (void)YAML::decode(n3, out);
  });

  EXPECT_NO_THROW({
    YAML::Node n4 = YAML::Load("[a, b]");  // Sequence
    (void)YAML::decode(n4, out);
  });

  EXPECT_NO_THROW({
    YAML::Node n5 = YAML::Load("{k: v}");  // Map
    (void)YAML::decode(n5, out);
  });
}

}  // namespace