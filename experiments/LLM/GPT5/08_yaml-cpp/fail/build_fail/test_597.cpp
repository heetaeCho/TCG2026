// File: test/node_convert_encode_const_char_test.cpp
// TEST_ID: 597
//
// Unit tests for yaml-cpp/node/convert.h
// Interface under test:
//   namespace YAML { static Node encode(const char* rhs) { return Node(rhs); } }
//
// Notes:
// - Treat implementation as a black box: only validate observable behavior through YAML::Node.
// - These tests assume yaml-cpp is available and YAML::Node supports IsNull()/IsScalar()/as<std::string>().

#include <gtest/gtest.h>

#include <string>
#include <yaml-cpp/yaml.h>

// Some yaml-cpp builds provide YAML::encode in node/convert.h only;
// include it explicitly to ensure the function is visible.
#include <yaml-cpp/node/convert.h>

namespace {

class EncodeConstCharTest_597 : public ::testing::Test {};

TEST_F(EncodeConstCharTest_597, EncodeNullptrProducesNullNode_597) {
  const char* p = nullptr;

  YAML::Node n = YAML::encode(p);

  EXPECT_TRUE(n.IsNull());
  EXPECT_FALSE(n.IsScalar());
}

TEST_F(EncodeConstCharTest_597, EncodeEmptyStringProducesScalarEmpty_597) {
  const char* p = "";

  YAML::Node n = YAML::encode(p);

  EXPECT_TRUE(n.IsScalar());
  EXPECT_EQ(n.as<std::string>(), "");
}

TEST_F(EncodeConstCharTest_597, EncodeAsciiStringProducesScalarWithSameValue_597) {
  const char* p = "hello world";

  YAML::Node n = YAML::encode(p);

  EXPECT_TRUE(n.IsScalar());
  EXPECT_EQ(n.as<std::string>(), "hello world");
}

TEST_F(EncodeConstCharTest_597, EncodeStringWithSpacesAndPunctuationRoundTrips_597) {
  const char* p = "a b\tc\n!@#$%^&*()_+-=[]{};':,./<>?";

  YAML::Node n = YAML::encode(p);

  EXPECT_TRUE(n.IsScalar());
  EXPECT_EQ(n.as<std::string>(), std::string(p));
}

TEST_F(EncodeConstCharTest_597, EncodeNonAsciiUtf8StringRoundTrips_597) {
  // UTF-8 literal (Korean).
  const char* p = u8"안녕하세요";

  YAML::Node n = YAML::encode(p);

  EXPECT_TRUE(n.IsScalar());
  EXPECT_EQ(n.as<std::string>(), std::string(p));
}

TEST_F(EncodeConstCharTest_597, EncodeMultipleCallsIndependentValues_597) {
  YAML::Node n1 = YAML::encode("first");
  YAML::Node n2 = YAML::encode("second");

  ASSERT_TRUE(n1.IsScalar());
  ASSERT_TRUE(n2.IsScalar());
  EXPECT_EQ(n1.as<std::string>(), "first");
  EXPECT_EQ(n2.as<std::string>(), "second");
}

TEST_F(EncodeConstCharTest_597, EncodeThenAssignDoesNotChangeOriginal_597) {
  YAML::Node n = YAML::encode("original");
  ASSERT_TRUE(n.IsScalar());
  EXPECT_EQ(n.as<std::string>(), "original");

  // Mutate the node through public API; ensure it changes to the new value (observable behavior),
  // and that original expectation above was stable.
  n = YAML::Node("new");
  EXPECT_TRUE(n.IsScalar());
  EXPECT_EQ(n.as<std::string>(), "new");
}

}  // namespace