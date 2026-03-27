// File: test/node/convert_bool_test_606.cpp

#include <gtest/gtest.h>
#include <yaml-cpp/yaml.h>

// The code under test (from yaml-cpp/node/convert.h):
// namespace YAML { static Node encode(bool rhs) { return rhs ? Node("true") : Node("false"); } }

namespace {

TEST(ConvertBoolEncodeTest_606, EncodeTrueReturnsScalarTrue_606) {
  YAML::Node n = YAML::encode(true);

  // Observable behavior: should be a scalar and stringify to "true".
  ASSERT_TRUE(n.IsScalar());
  EXPECT_EQ(n.as<std::string>(), "true");
}

TEST(ConvertBoolEncodeTest_606, EncodeFalseReturnsScalarFalse_606) {
  YAML::Node n = YAML::encode(false);

  ASSERT_TRUE(n.IsScalar());
  EXPECT_EQ(n.as<std::string>(), "false");
}

TEST(ConvertBoolEncodeTest_606, EncodeTrueAndFalseReturnDifferentValues_606) {
  YAML::Node t = YAML::encode(true);
  YAML::Node f = YAML::encode(false);

  ASSERT_TRUE(t.IsScalar());
  ASSERT_TRUE(f.IsScalar());

  // Ensure they are observably different via the public interface.
  EXPECT_NE(t.as<std::string>(), f.as<std::string>());
  EXPECT_EQ(t.as<std::string>(), "true");
  EXPECT_EQ(f.as<std::string>(), "false");
}

TEST(ConvertBoolEncodeTest_606, EncodedNodeCanBeRoundTrippedViaAsString_606) {
  // Boundary-ish check: repeated calls and conversions remain stable/consistent.
  const YAML::Node n1 = YAML::encode(true);
  const YAML::Node n2 = YAML::encode(true);

  ASSERT_TRUE(n1.IsScalar());
  ASSERT_TRUE(n2.IsScalar());
  EXPECT_EQ(n1.as<std::string>(), "true");
  EXPECT_EQ(n2.as<std::string>(), "true");
}

TEST(ConvertBoolEncodeTest_606, EncodedNodeDoesNotThrowOnStringConversion_606) {
  // Exceptional/error cases (observable): conversion to string should not throw.
  EXPECT_NO_THROW({
    YAML::Node n = YAML::encode(false);
    (void)n.as<std::string>();
  });
}

}  // namespace