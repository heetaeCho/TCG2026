// File: ./TestProjects/yaml-cpp/test/parse_loadall_cstr_test_583.cpp

#include <gtest/gtest.h>

#include <sstream>
#include <string>
#include <vector>

#include <yaml-cpp/yaml.h>

// These tests target:
//   namespace YAML { std::vector<Node> LoadAll(const char* input) { std::stringstream stream(input); return LoadAll(stream); } }
//
// Treating implementation as a black box, we validate observable behavior via the public API.
// In particular, we compare results of YAML::LoadAll(const char*) to YAML::LoadAll(std::istream&)
// for the same content, and check boundary / error behaviors through exceptions.

namespace {

class LoadAllConstCharTest_583 : public ::testing::Test {
 protected:
  static void ExpectSameDocuments(const std::vector<YAML::Node>& a,
                                  const std::vector<YAML::Node>& b) {
    ASSERT_EQ(a.size(), b.size());
    for (std::size_t i = 0; i < a.size(); ++i) {
      EXPECT_TRUE(a[i] == b[i]) << "Document index: " << i;
    }
  }
};

}  // namespace

TEST_F(LoadAllConstCharTest_583, SingleDocument_MatchesIstreamOverload_583) {
  const char* yaml = "a: 1\nb: [2, 3]\n";
  std::stringstream ss;
  ss << yaml;

  const std::vector<YAML::Node> from_cstr = YAML::LoadAll(yaml);
  const std::vector<YAML::Node> from_stream = YAML::LoadAll(ss);

  ExpectSameDocuments(from_cstr, from_stream);
  ASSERT_EQ(from_cstr.size(), 1u);
  EXPECT_TRUE(from_cstr[0].IsMap());
  EXPECT_EQ(from_cstr[0]["a"].as<int>(), 1);
  EXPECT_EQ(from_cstr[0]["b"][0].as<int>(), 2);
  EXPECT_EQ(from_cstr[0]["b"][1].as<int>(), 3);
}

TEST_F(LoadAllConstCharTest_583, MultipleDocuments_MatchesIstreamOverload_583) {
  const char* yaml =
      "---\n"
      "a: 1\n"
      "---\n"
      "- x\n"
      "- y\n"
      "---\n"
      "k: v\n";

  std::stringstream ss;
  ss << yaml;

  const std::vector<YAML::Node> from_cstr = YAML::LoadAll(yaml);
  const std::vector<YAML::Node> from_stream = YAML::LoadAll(ss);

  ExpectSameDocuments(from_cstr, from_stream);

  ASSERT_EQ(from_cstr.size(), 3u);
  EXPECT_TRUE(from_cstr[0].IsMap());
  EXPECT_EQ(from_cstr[0]["a"].as<int>(), 1);

  EXPECT_TRUE(from_cstr[1].IsSequence());
  ASSERT_EQ(from_cstr[1].size(), 2u);
  EXPECT_EQ(from_cstr[1][0].as<std::string>(), "x");
  EXPECT_EQ(from_cstr[1][1].as<std::string>(), "y");

  EXPECT_TRUE(from_cstr[2].IsMap());
  EXPECT_EQ(from_cstr[2]["k"].as<std::string>(), "v");
}

TEST_F(LoadAllConstCharTest_583, EmptyString_MatchesIstreamOverload_583) {
  const char* yaml = "";
  std::stringstream ss;
  ss << yaml;

  const std::vector<YAML::Node> from_cstr = YAML::LoadAll(yaml);
  const std::vector<YAML::Node> from_stream = YAML::LoadAll(ss);

  ExpectSameDocuments(from_cstr, from_stream);
}

TEST_F(LoadAllConstCharTest_583, WhitespaceOnly_MatchesIstreamOverload_583) {
  const char* yaml = "   \n\t\n  ";
  std::stringstream ss;
  ss << yaml;

  const std::vector<YAML::Node> from_cstr = YAML::LoadAll(yaml);
  const std::vector<YAML::Node> from_stream = YAML::LoadAll(ss);

  ExpectSameDocuments(from_cstr, from_stream);
}

TEST_F(LoadAllConstCharTest_583, ValidScalarDocument_MatchesIstreamOverload_583) {
  const char* yaml = "hello\n";
  std::stringstream ss;
  ss << yaml;

  const std::vector<YAML::Node> from_cstr = YAML::LoadAll(yaml);
  const std::vector<YAML::Node> from_stream = YAML::LoadAll(ss);

  ExpectSameDocuments(from_cstr, from_stream);
  ASSERT_EQ(from_cstr.size(), 1u);
  EXPECT_TRUE(from_cstr[0].IsScalar());
  EXPECT_EQ(from_cstr[0].as<std::string>(), "hello");
}

TEST_F(LoadAllConstCharTest_583, InvalidYaml_ThrowsSameExceptionTypeAsIstreamOverload_583) {
  // Intentionally malformed YAML (unbalanced sequence bracket).
  const char* yaml = "a: [1, 2\n";

  std::stringstream ss;
  ss << yaml;

  // We don't assume a specific concrete exception type beyond the library's base.
  // But we do verify that the wrapper and the istream overload both report errors.
  EXPECT_THROW((void)YAML::LoadAll(yaml), YAML::Exception);
  EXPECT_THROW((void)YAML::LoadAll(ss), YAML::Exception);
}

TEST_F(LoadAllConstCharTest_583, MultipleDocuments_WithOneInvalid_Throws_583) {
  const char* yaml =
      "---\n"
      "ok: 1\n"
      "---\n"
      "bad: [1, 2\n"  // invalid
      "---\n"
      "also_ok: 3\n";

  EXPECT_THROW((void)YAML::LoadAll(yaml), YAML::Exception);
}

// NOTE: Passing nullptr to YAML::LoadAll(const char*) would attempt to construct a std::stringstream
// from a null C-string, which is undefined behavior in C++.
// We intentionally do not add a test that calls YAML::LoadAll(nullptr).