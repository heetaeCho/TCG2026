// File: ./TestProjects/yaml-cpp/test/loadall_test_584.cpp

#include <gtest/gtest.h>

#include <yaml-cpp/yaml.h>
#include <yaml-cpp/exceptions.h>

#include <sstream>
#include <string>
#include <vector>

namespace {

class LoadAllTest_584 : public ::testing::Test {};

TEST_F(LoadAllTest_584, EmptyInputReturnsEmpty_584) {
  std::istringstream in("");
  const std::vector<YAML::Node> docs = YAML::LoadAll(in);
  EXPECT_TRUE(docs.empty());
}

TEST_F(LoadAllTest_584, SingleMapDocumentParses_584) {
  std::istringstream in("a: 1\n");
  const std::vector<YAML::Node> docs = YAML::LoadAll(in);

  ASSERT_EQ(docs.size(), 1u);
  EXPECT_TRUE(docs[0].IsDefined());
  EXPECT_TRUE(docs[0].IsMap());
  EXPECT_EQ(docs[0]["a"].as<int>(), 1);
}

TEST_F(LoadAllTest_584, MultipleDocumentsParsesAll_584) {
  std::istringstream in(
      "a: 1\n"
      "---\n"
      "b: 2\n"
      "---\n"
      "- 3\n"
      "- 4\n");

  const std::vector<YAML::Node> docs = YAML::LoadAll(in);

  ASSERT_EQ(docs.size(), 3u);

  EXPECT_TRUE(docs[0].IsMap());
  EXPECT_EQ(docs[0]["a"].as<int>(), 1);

  EXPECT_TRUE(docs[1].IsMap());
  EXPECT_EQ(docs[1]["b"].as<int>(), 2);

  EXPECT_TRUE(docs[2].IsSequence());
  ASSERT_EQ(docs[2].size(), 2u);
  EXPECT_EQ(docs[2][0].as<int>(), 3);
  EXPECT_EQ(docs[2][1].as<int>(), 4);
}

TEST_F(LoadAllTest_584, LeadingDocumentSeparatorStillParsesOneDoc_584) {
  std::istringstream in(
      "---\n"
      "a: 1\n");

  const std::vector<YAML::Node> docs = YAML::LoadAll(in);

  ASSERT_EQ(docs.size(), 1u);
  EXPECT_TRUE(docs[0].IsMap());
  EXPECT_EQ(docs[0]["a"].as<int>(), 1);
}

TEST_F(LoadAllTest_584, StopsWhenNextDocumentRootIsNull_584) {
  // LoadAll stops when builder.Root().IsNull() becomes true.
  std::istringstream in(
      "a: 1\n"
      "---\n"
      "~\n"
      "---\n"
      "b: 2\n");

  const std::vector<YAML::Node> docs = YAML::LoadAll(in);

  ASSERT_EQ(docs.size(), 1u);
  EXPECT_TRUE(docs[0].IsMap());
  EXPECT_EQ(docs[0]["a"].as<int>(), 1);
}

TEST_F(LoadAllTest_584, InvalidYamlThrows_584) {
  // Malformed flow sequence (missing closing bracket).
  std::istringstream in("a: [1, 2\n");
  EXPECT_THROW((void)YAML::LoadAll(in), YAML::Exception);
}

TEST_F(LoadAllTest_584, ManySmallDocumentsParsesAll_584) {
  std::ostringstream yaml;
  constexpr int kDocs = 50;
  for (int i = 0; i < kDocs; ++i) {
    yaml << "n: " << i << "\n";
    if (i != kDocs - 1) yaml << "---\n";
  }

  std::istringstream in(yaml.str());
  const std::vector<YAML::Node> docs = YAML::LoadAll(in);

  ASSERT_EQ(docs.size(), static_cast<std::size_t>(kDocs));
  for (int i = 0; i < kDocs; ++i) {
    ASSERT_TRUE(docs[static_cast<std::size_t>(i)].IsMap());
    EXPECT_EQ(docs[static_cast<std::size_t>(i)]["n"].as<int>(), i);
  }
}

}  // namespace