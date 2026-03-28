// File: yaml-cpp/node/convert_charptr_encode_test_599.cpp

#include <gtest/gtest.h>
#include <yaml-cpp/yaml.h>

namespace {

class EncodeCharPtrTest_599 : public ::testing::Test {};

TEST_F(EncodeCharPtrTest_599, EncodeSimpleCStringReturnsScalarNode_599) {
  const char* input = "hello";
  YAML::Node node = YAML::encode(input);

  ASSERT_TRUE(node.IsScalar());
  EXPECT_EQ(node.as<std::string>(), "hello");
}

TEST_F(EncodeCharPtrTest_599, EncodeEmptyCStringReturnsEmptyScalar_599) {
  const char* input = "";
  YAML::Node node = YAML::encode(input);

  ASSERT_TRUE(node.IsScalar());
  EXPECT_EQ(node.as<std::string>(), "");
}

TEST_F(EncodeCharPtrTest_599, EncodeCStringWithSpacesPreservesContent_599) {
  const char* input = "  a b  c  ";
  YAML::Node node = YAML::encode(input);

  ASSERT_TRUE(node.IsScalar());
  EXPECT_EQ(node.as<std::string>(), "  a b  c  ");
}

TEST_F(EncodeCharPtrTest_599, EncodeUtf8CStringRoundTripsAsString_599) {
  // UTF-8 literal (Korean + emoji) to ensure non-ASCII survives the API.
  const char* input = u8"안녕하세요 🌟";
  YAML::Node node = YAML::encode(input);

  ASSERT_TRUE(node.IsScalar());
  EXPECT_EQ(node.as<std::string>(), std::string(u8"안녕하세요 🌟"));
}

TEST_F(EncodeCharPtrTest_599, EncodeLongCStringHandlesLargeInput_599) {
  const std::string long_str(10000, 'x');
  YAML::Node node = YAML::encode(long_str.c_str());

  ASSERT_TRUE(node.IsScalar());
  EXPECT_EQ(node.as<std::string>(), long_str);
}

TEST_F(EncodeCharPtrTest_599, EncodeCStringWithEmbeddedNullStopsAtFirstNull_599) {
  // C-string semantics: content ends at the first '\0'.
  const char input[] = {'a', '\0', 'b', '\0'};
  YAML::Node node = YAML::encode(input);

  ASSERT_TRUE(node.IsScalar());
  EXPECT_EQ(node.as<std::string>(), "a");
}

#if GTEST_HAS_DEATH_TEST
TEST_F(EncodeCharPtrTest_599, EncodeNullptrIsAnErrorCase_599) {
  // Passing nullptr to a const char* API is invalid input; behavior may be
  // a crash (UB) depending on the underlying implementation.
  EXPECT_DEATH_IF_SUPPORTED(
      {
        (void)YAML::encode(static_cast<const char*>(nullptr));
      },
      "");
}
#endif

}  // namespace