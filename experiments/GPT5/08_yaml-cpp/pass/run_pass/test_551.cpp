// TEST_ID: 551
#include <gtest/gtest.h>

#include <string>
#include <limits>

#include <yaml-cpp/yaml.h>

namespace {

class AsIfTest_551 : public ::testing::Test {};

TEST_F(AsIfTest_551, UndefinedNodeReturnsFallbackForInt_551) {
  YAML::Node n;  // default constructed (often "undefined" until assigned)
  EXPECT_EQ(n.as<int>(42), 42);
}

TEST_F(AsIfTest_551, UndefinedNodeReturnsFallbackForString_551) {
  YAML::Node n;
  const std::string fallback = "fallback";
  EXPECT_EQ(n.as<std::string>(fallback), fallback);
}

TEST_F(AsIfTest_551, ScalarNodeDecodesToIntWhenConvertible_551) {
  YAML::Node n("123");
  EXPECT_EQ(n.as<int>(7), 123);
}

TEST_F(AsIfTest_551, ScalarNodeReturnsFallbackWhenDecodeFails_551) {
  YAML::Node n("not_an_int");
  EXPECT_EQ(n.as<int>(7), 7);
}

TEST_F(AsIfTest_551, AssignedIntNodeReturnsValueNotFallback_551) {
  YAML::Node n;
  n = 5;
  EXPECT_EQ(n.as<int>(0), 5);
}

TEST_F(AsIfTest_551, AssignedStringNodeReturnsValueNotFallback_551) {
  YAML::Node n;
  n = std::string("hello");
  EXPECT_EQ(n.as<std::string>(std::string("fallback")), "hello");
}

TEST_F(AsIfTest_551, FallbackIsNotModified_551) {
  YAML::Node n;  // undefined => should use fallback
  int fallback = 99;
  const int result = n.as<int>(fallback);
  EXPECT_EQ(result, 99);
  EXPECT_EQ(fallback, 99);  // ensure not mutated by the call
}

TEST_F(AsIfTest_551, LargeFallbackValueIsReturnedWhenUndefined_551) {
  YAML::Node n;
  const int fallback = std::numeric_limits<int>::max();
  EXPECT_EQ(n.as<int>(fallback), fallback);
}

TEST_F(AsIfTest_551, ConvertibleScalarToDoubleReturnsDecodedValue_551) {
  YAML::Node n("3.5");
  EXPECT_DOUBLE_EQ(n.as<double>(1.0), 3.5);
}

TEST_F(AsIfTest_551, NonConvertibleScalarToDoubleReturnsFallback_551) {
  YAML::Node n("nanana");
  EXPECT_DOUBLE_EQ(n.as<double>(1.25), 1.25);
}

TEST_F(AsIfTest_551, AsWithoutFallbackOnUndefinedThrows_551) {
  YAML::Node n;  // undefined
  EXPECT_ANY_THROW((void)n.as<int>());
}

TEST_F(AsIfTest_551, AsWithoutFallbackOnBadConversionThrows_551) {
  YAML::Node n("abc");  // not convertible to int in typical YAML conversions
  EXPECT_ANY_THROW((void)n.as<int>());
}

}  // namespace