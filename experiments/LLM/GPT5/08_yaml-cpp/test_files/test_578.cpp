// File: ./TestProjects/yaml-cpp/test/load_string_tests_578.cpp

#include <gtest/gtest.h>
#include <yaml-cpp/yaml.h>

#include <sstream>
#include <string>

namespace {

class LoadStringTest_578 : public ::testing::Test {};

TEST_F(LoadStringTest_578, ParsesScalarInt_578) {
  const std::string input = "123";
  YAML::Node n = YAML::Load(input);

  ASSERT_TRUE(n.IsScalar());
  EXPECT_EQ(n.as<int>(), 123);
}

TEST_F(LoadStringTest_578, ParsesMap_578) {
  const std::string input = "a: 1\nb: two\n";
  YAML::Node n = YAML::Load(input);

  ASSERT_TRUE(n.IsMap());
  ASSERT_TRUE(n["a"]);
  ASSERT_TRUE(n["b"]);
  EXPECT_EQ(n["a"].as<int>(), 1);
  EXPECT_EQ(n["b"].as<std::string>(), "two");
}

TEST_F(LoadStringTest_578, ParsesSequence_578) {
  const std::string input = "- 1\n- 2\n- 3\n";
  YAML::Node n = YAML::Load(input);

  ASSERT_TRUE(n.IsSequence());
  ASSERT_EQ(n.size(), 3u);
  EXPECT_EQ(n[0].as<int>(), 1);
  EXPECT_EQ(n[1].as<int>(), 2);
  EXPECT_EQ(n[2].as<int>(), 3);
}

TEST_F(LoadStringTest_578, EmptyStringYieldsNull_578) {
  const std::string input = "";
  YAML::Node n = YAML::Load(input);

  EXPECT_TRUE(n.IsNull());
}

TEST_F(LoadStringTest_578, WhitespaceOnlyYieldsNull_578) {
  const std::string input = " \n\t\r\n";
  YAML::Node n = YAML::Load(input);

  EXPECT_TRUE(n.IsNull());
}

TEST_F(LoadStringTest_578, EquivalentToLoadFromStream_578) {
  const std::string input = "root:\n  k: v\n  n: 42\n";

  YAML::Node from_string = YAML::Load(input);

  std::stringstream ss(input);
  YAML::Node from_stream = YAML::Load(ss);

  // Compare observable serialized form rather than relying on internal representation.
  EXPECT_EQ(YAML::Dump(from_string), YAML::Dump(from_stream));
}

TEST_F(LoadStringTest_578, InvalidYamlThrows_578) {
  const std::string input = "a: [1, 2\n";  // missing closing ']'

  EXPECT_THROW(
      {
        (void)YAML::Load(input);
      },
      YAML::ParserException);
}

}  // namespace