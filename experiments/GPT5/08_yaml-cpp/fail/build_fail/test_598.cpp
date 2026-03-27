// File: yaml-cpp/node/convert_test.cpp
#include <gtest/gtest.h>

#include <string>

// Prefer the main yaml-cpp header so Node APIs (Scalar/as/Type checks) are available.
#include <yaml-cpp/yaml.h>

namespace {

class EncodeCharPtrTest_598 : public ::testing::Test {};

TEST_F(EncodeCharPtrTest_598, EncodesSimpleCStringToScalar_598) {
  const char* input = "hello";
  YAML::Node n;

  ASSERT_NO_THROW(n = YAML::encode(input));
  EXPECT_TRUE(n.IsScalar());
  EXPECT_EQ(n.Scalar(), "hello");
  EXPECT_EQ(n.as<std::string>(), std::string("hello"));
}

TEST_F(EncodeCharPtrTest_598, EncodesEmptyCString_598) {
  const char* input = "";
  YAML::Node n;

  ASSERT_NO_THROW(n = YAML::encode(input));
  EXPECT_TRUE(n.IsScalar());
  EXPECT_EQ(n.Scalar(), "");
  EXPECT_EQ(n.as<std::string>(), std::string(""));
}

TEST_F(EncodeCharPtrTest_598, EncodesCStringWithSpacesAndPunctuation_598) {
  const char* input = " a b\tc !@#$%^&*()[]{};:,./? ";
  YAML::Node n;

  ASSERT_NO_THROW(n = YAML::encode(input));
  EXPECT_TRUE(n.IsScalar());
  EXPECT_EQ(n.as<std::string>(), std::string(input));
}

TEST_F(EncodeCharPtrTest_598, EncodesMultilineCString_598) {
  const char* input = "line1\nline2\nline3";
  YAML::Node n;

  ASSERT_NO_THROW(n = YAML::encode(input));
  EXPECT_TRUE(n.IsScalar());
  EXPECT_EQ(n.as<std::string>(), std::string(input));
}

TEST_F(EncodeCharPtrTest_598, EncodesLongCString_598) {
  const std::string long_str(4096, 'x');  // boundary-ish size without being extreme
  YAML::Node n;

  ASSERT_NO_THROW(n = YAML::encode(long_str.c_str()));
  EXPECT_TRUE(n.IsScalar());
  EXPECT_EQ(n.as<std::string>(), long_str);
}

TEST_F(EncodeCharPtrTest_598, NullptrInputEitherThrowsOrProducesObservableNode_598) {
  // Behavior for nullptr is not specified by the provided interface.
  // This test is written to be robust: it passes if encode(nullptr) either
  // throws (error case) OR returns a Node that is safely inspectable.
  try {
    YAML::Node n = YAML::encode(static_cast<const char*>(nullptr));

    // If it doesn't throw, it should still be safe to query basic properties.
    // Accept common observable outcomes without assuming internal logic.
    const bool ok =
        n.IsNull() ||
        (n.IsScalar() && (n.Scalar().empty() || n.as<std::string>().empty()));

    EXPECT_TRUE(ok);
  } catch (...) {
    SUCCEED();
  }
}

}  // namespace