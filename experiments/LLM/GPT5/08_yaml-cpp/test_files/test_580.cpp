// TEST_ID: 580
#include <gtest/gtest.h>

#include <sstream>
#include <string>

#include <yaml-cpp/yaml.h>

namespace {

class LoadTest_580 : public ::testing::Test {};

TEST_F(LoadTest_580, EmptyStreamReturnsUndefinedNode_580) {
  std::stringstream ss("");
  YAML::Node n = YAML::Load(ss);

  // YAML::Load returns Node() when it cannot handle a document.
  EXPECT_FALSE(n.IsDefined());
}

TEST_F(LoadTest_580, WhitespaceAndCommentsOnlyReturnsUndefinedNode_580) {
  std::stringstream ss("   \n# just a comment\n\n  # another\n");
  YAML::Node n = YAML::Load(ss);

  EXPECT_FALSE(n.IsDefined());
}

TEST_F(LoadTest_580, ScalarLoadsAsString_580) {
  std::stringstream ss("hello");
  YAML::Node n = YAML::Load(ss);

  ASSERT_TRUE(n.IsDefined());
  EXPECT_TRUE(n.IsScalar());
  EXPECT_EQ(n.as<std::string>(), "hello");
}

TEST_F(LoadTest_580, SequenceLoadsWithExpectedElements_580) {
  std::stringstream ss("- a\n- b\n- c\n");
  YAML::Node n = YAML::Load(ss);

  ASSERT_TRUE(n.IsDefined());
  ASSERT_TRUE(n.IsSequence());
  ASSERT_EQ(n.size(), 3u);
  EXPECT_EQ(n[0].as<std::string>(), "a");
  EXPECT_EQ(n[1].as<std::string>(), "b");
  EXPECT_EQ(n[2].as<std::string>(), "c");
}

TEST_F(LoadTest_580, MapLoadsWithExpectedKeyValue_580) {
  std::stringstream ss("k: v\n");
  YAML::Node n = YAML::Load(ss);

  ASSERT_TRUE(n.IsDefined());
  ASSERT_TRUE(n.IsMap());
  ASSERT_TRUE(n["k"].IsDefined());
  EXPECT_EQ(n["k"].as<std::string>(), "v");
}

TEST_F(LoadTest_580, MultipleDocumentsLoadsFirstDocumentOnly_580) {
  std::stringstream ss("---\na\n---\nb\n");
  YAML::Node n = YAML::Load(ss);

  ASSERT_TRUE(n.IsDefined());
  ASSERT_TRUE(n.IsScalar());
  EXPECT_EQ(n.as<std::string>(), "a");  // Should be the first document's root.
}

TEST_F(LoadTest_580, InvalidYamlThrowsException_580) {
  // Missing closing bracket for flow sequence.
  std::stringstream ss("a: [1, 2\n");

  EXPECT_THROW({ (void)YAML::Load(ss); }, YAML::Exception);
}

}  // namespace