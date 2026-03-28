#include <gtest/gtest.h>

#include <yaml-cpp/yaml.h>

#include <sstream>
#include <string>

namespace {

class LoadFromCStringTest_579 : public ::testing::Test {};

// Verifies that the const char* overload behaves equivalently to loading from a stream
// with the same textual content.
TEST_F(LoadFromCStringTest_579, ValidYamlMatchesStreamLoad_579) {
  const char* input = "a: 1\nb: 2\nc:\n  - x\n  - y\n";

  YAML::Node from_cstr = YAML::Load(input);

  std::stringstream ss;
  ss << input;
  YAML::Node from_stream = YAML::Load(ss);

  EXPECT_TRUE(from_cstr == from_stream);
}

// Boundary: empty input should be handled (yaml-cpp typically yields a Null node).
TEST_F(LoadFromCStringTest_579, EmptyStringYieldsNullNode_579) {
  YAML::Node node = YAML::Load("");
  EXPECT_TRUE(node.IsNull());
}

// Normal operation: scalar parsing.
TEST_F(LoadFromCStringTest_579, ScalarParsesAndCanBeRead_579) {
  YAML::Node node = YAML::Load("hello");
  ASSERT_TRUE(node.IsScalar());
  EXPECT_EQ(node.as<std::string>(), "hello");
}

// Normal operation: sequence parsing.
TEST_F(LoadFromCStringTest_579, SequenceParsesWithExpectedElements_579) {
  YAML::Node node = YAML::Load("- a\n- b\n- c\n");
  ASSERT_TRUE(node.IsSequence());
  ASSERT_EQ(node.size(), 3u);
  EXPECT_EQ(node[0].as<std::string>(), "a");
  EXPECT_EQ(node[1].as<std::string>(), "b");
  EXPECT_EQ(node[2].as<std::string>(), "c");
}

// Normal operation: map parsing.
TEST_F(LoadFromCStringTest_579, MapParsesWithExpectedKeys_579) {
  YAML::Node node = YAML::Load("key1: value1\nkey2: 42\n");
  ASSERT_TRUE(node.IsMap());
  EXPECT_EQ(node["key1"].as<std::string>(), "value1");
  EXPECT_EQ(node["key2"].as<int>(), 42);
}

// Error case: invalid YAML should throw an exception observable via the interface.
TEST_F(LoadFromCStringTest_579, InvalidYamlThrowsParserException_579) {
  const char* bad = "a: [1, 2\n";  // missing closing ']'
  EXPECT_THROW((void)YAML::Load(bad), YAML::ParserException);
}

// Boundary-ish: reasonably large input should still parse.
TEST_F(LoadFromCStringTest_579, LargerInputParses_579) {
  std::string input;
  input.reserve(4096);
  for (int i = 0; i < 200; ++i) {
    input += "k";
    input += std::to_string(i);
    input += ": ";
    input += std::to_string(i);
    input += "\n";
  }

  YAML::Node node = YAML::Load(input.c_str());
  ASSERT_TRUE(node.IsMap());
  EXPECT_EQ(node["k0"].as<int>(), 0);
  EXPECT_EQ(node["k199"].as<int>(), 199);
}

// Verifies that embedded NUL in a std::string is treated as C-string termination
// (i.e., only the prefix is visible to YAML::Load(const char*)).
TEST_F(LoadFromCStringTest_579, EmbeddedNullCharUsesCStringPrefixOnly_579) {
  std::string with_nul = std::string("a: 1\n") + '\0' + "b: 2\n";
  const char* cstr = with_nul.c_str();

  YAML::Node from_cstr = YAML::Load(cstr);

  // Compare with loading from a stream built from the visible prefix up to NUL.
  std::stringstream ss;
  ss << std::string(cstr);  // stops at NUL
  YAML::Node from_stream = YAML::Load(ss);

  EXPECT_TRUE(from_cstr == from_stream);
}

}  // namespace