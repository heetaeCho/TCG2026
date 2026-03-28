// File: yaml-cpp/node/convert_test.cpp
#include <gtest/gtest.h>

#include <string>

#include "yaml-cpp/node/convert.h"
#include "yaml-cpp/node/node.h"

namespace {

TEST(EncodeStringTest_595, ReturnsScalarNodeWithSameContent_595) {
  const std::string input = "hello world";

  YAML::Node n;
  EXPECT_NO_THROW({
    n = YAML::encode(input);
  });

  EXPECT_TRUE(n.IsScalar());
  EXPECT_EQ(n.Scalar(), input);
  EXPECT_EQ(n.as<std::string>(), input);
}

TEST(EncodeStringTest_595, EmptyStringProducesEmptyScalar_595) {
  const std::string input;

  YAML::Node n;
  EXPECT_NO_THROW({
    n = YAML::encode(input);
  });

  EXPECT_TRUE(n.IsScalar());
  EXPECT_EQ(n.Scalar(), "");
  EXPECT_EQ(n.as<std::string>(), "");
}

TEST(EncodeStringTest_595, PreservesWhitespaceAndPunctuation_595) {
  const std::string input = "  \tline1\nline2\r\n!@#$%^&*()_+-=[]{};':\",.<>/?\\  ";

  YAML::Node n;
  EXPECT_NO_THROW({
    n = YAML::encode(input);
  });

  EXPECT_TRUE(n.IsScalar());
  EXPECT_EQ(n.Scalar(), input);
  EXPECT_EQ(n.as<std::string>(), input);
}

TEST(EncodeStringTest_595, SupportsUnicodeInUtf8Strings_595) {
  const std::string input = u8"안녕하세요 YAML 👋";

  YAML::Node n;
  EXPECT_NO_THROW({
    n = YAML::encode(input);
  });

  EXPECT_TRUE(n.IsScalar());
  EXPECT_EQ(n.Scalar(), input);
  EXPECT_EQ(n.as<std::string>(), input);
}

TEST(EncodeStringTest_595, HandlesLargeString_595) {
  const std::string input(1 << 20, 'a');  // 1 MiB

  YAML::Node n;
  EXPECT_NO_THROW({
    n = YAML::encode(input);
  });

  ASSERT_TRUE(n.IsScalar());
  const std::string out = n.as<std::string>();
  EXPECT_EQ(out.size(), input.size());
  EXPECT_EQ(out, input);
}

}  // namespace