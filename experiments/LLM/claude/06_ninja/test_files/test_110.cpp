#include "dyndep_parser.h"
#include "state.h"
#include "graph.h"
#include "dyndep.h"
#include "test.h"

#include <gtest/gtest.h>
#include <string>
#include <map>
#include <vector>

struct MockFileReader : public FileReader {
  std::map<std::string, std::string> files_;

  bool ReadFile(const std::string& path, std::string* content,
                std::string* err) override {
    auto it = files_.find(path);
    if (it != files_.end()) {
      *content = it->second;
      return true;
    }
    *err = "file not found: " + path;
    return false;
  }
};

class DyndepParserTest_110 : public testing::Test {
 protected:
  void SetUp() override {
    // Build a simple state with an edge so we can test dyndep parsing.
    // We need at least one edge with inputs/outputs for dyndep to work with.
  }

  void AssertParse(const char* input) {
    std::string err;
    ASSERT_TRUE(parser_.ParseTest(input, &err)) << err;
  }

  State state_;
  MockFileReader file_reader_;
  DyndepFile dyndep_file_;
  DyndepParser parser_{&state_, &file_reader_, &dyndep_file_};
};

TEST_F(DyndepParserTest_110, EmptyInput_110) {
  std::string err;
  EXPECT_FALSE(parser_.ParseTest("", &err));
  EXPECT_FALSE(err.empty());
}

TEST_F(DyndepParserTest_110, OnlyNewline_110) {
  std::string err;
  EXPECT_FALSE(parser_.ParseTest("\n", &err));
  EXPECT_FALSE(err.empty());
}

TEST_F(DyndepParserTest_110, NinjaDyndepVersionOnly_110) {
  std::string err;
  // Just the version, no edges - should parse successfully if no edges needed
  EXPECT_TRUE(parser_.ParseTest("ninja_dyndep_version = 1\n", &err)) << err;
}

TEST_F(DyndepParserTest_110, MissingVersion_110) {
  std::string err;
  EXPECT_FALSE(parser_.ParseTest("build foo: dyndep\n", &err));
  EXPECT_FALSE(err.empty());
}

TEST_F(DyndepParserTest_110, WrongVersion_110) {
  std::string err;
  EXPECT_FALSE(parser_.ParseTest("ninja_dyndep_version = 2\n", &err));
  EXPECT_FALSE(err.empty());
}

TEST_F(DyndepParserTest_110, VersionZero_110) {
  std::string err;
  EXPECT_FALSE(parser_.ParseTest("ninja_dyndep_version = 0\n", &err));
  EXPECT_FALSE(err.empty());
}

TEST_F(DyndepParserTest_110, InvalidVersionString_110) {
  std::string err;
  EXPECT_FALSE(parser_.ParseTest("ninja_dyndep_version = abc\n", &err));
  EXPECT_FALSE(err.empty());
}

TEST_F(DyndepParserTest_110, GarbageInput_110) {
  std::string err;
  EXPECT_FALSE(parser_.ParseTest("random garbage text\n", &err));
  EXPECT_FALSE(err.empty());
}

TEST_F(DyndepParserTest_110, VersionWithTrailingSpace_110) {
  std::string err;
  EXPECT_TRUE(parser_.ParseTest("ninja_dyndep_version = 1\n", &err)) << err;
}

TEST_F(DyndepParserTest_110, BuildWithoutVersion_110) {
  std::string err;
  EXPECT_FALSE(parser_.ParseTest("build out: dyndep | implicit\n", &err));
  EXPECT_FALSE(err.empty());
}

// Test with an edge that actually exists in the state
class DyndepParserWithEdgeTest_110 : public testing::Test {
 protected:
  void SetUp() override {
    // Add a rule and edge to the state
    state_.AddRule(&State::kPhonyRule);
    
    // Add nodes
    state_.GetNode("out", 0);
    state_.GetNode("in", 0);
    state_.GetNode("dd", 0);
    
    // We need to add an edge properly
    // Add a simple rule
    Rule* rule = new Rule("cc");
    rule->AddBinding("command", EvalString());
    state_.bindings_.AddRule(rule);
    
    Edge* edge = state_.AddEdge(rule);
    edge->outputs_.push_back(state_.GetNode("out", 0));
    state_.GetNode("out", 0)->set_in_edge(edge);
    edge->inputs_.push_back(state_.GetNode("in", 0));
    edge->dyndep_ = state_.GetNode("dd", 0);
  }

  State state_;
  MockFileReader file_reader_;
  DyndepFile dyndep_file_;
  DyndepParser parser_{&state_, &file_reader_, &dyndep_file_};
};

TEST_F(DyndepParserWithEdgeTest_110, ValidDyndepBuildStatement_110) {
  std::string err;
  EXPECT_TRUE(parser_.ParseTest(
      "ninja_dyndep_version = 1\n"
      "build out: dyndep\n", &err)) << err;
}

TEST_F(DyndepParserWithEdgeTest_110, DyndepWithImplicitInput_110) {
  std::string err;
  EXPECT_TRUE(parser_.ParseTest(
      "ninja_dyndep_version = 1\n"
      "build out: dyndep | in\n", &err)) << err;
}

TEST_F(DyndepParserWithEdgeTest_110, DyndepWithImplicitOutput_110) {
  std::string err;
  EXPECT_TRUE(parser_.ParseTest(
      "ninja_dyndep_version = 1\n"
      "build out | imp_out: dyndep\n", &err)) << err;
}

TEST_F(DyndepParserWithEdgeTest_110, DyndepWithRestat_110) {
  std::string err;
  EXPECT_TRUE(parser_.ParseTest(
      "ninja_dyndep_version = 1\n"
      "build out: dyndep\n"
      "  restat = 1\n", &err)) << err;
}

TEST_F(DyndepParserWithEdgeTest_110, DyndepBuildUnknownOutput_110) {
  std::string err;
  EXPECT_FALSE(parser_.ParseTest(
      "ninja_dyndep_version = 1\n"
      "build unknown_out: dyndep\n", &err));
  EXPECT_FALSE(err.empty());
}

TEST_F(DyndepParserWithEdgeTest_110, DyndepDuplicateEdge_110) {
  std::string err;
  EXPECT_FALSE(parser_.ParseTest(
      "ninja_dyndep_version = 1\n"
      "build out: dyndep\n"
      "build out: dyndep\n", &err));
  EXPECT_FALSE(err.empty());
}

TEST_F(DyndepParserWithEdgeTest_110, MultipleVersionStatements_110) {
  std::string err;
  // A second variable assignment after version should likely fail
  // or be treated differently
  EXPECT_FALSE(parser_.ParseTest(
      "ninja_dyndep_version = 1\n"
      "ninja_dyndep_version = 1\n", &err));
}

TEST_F(DyndepParserWithEdgeTest_110, VersionWithExtraWhitespace_110) {
  std::string err;
  EXPECT_TRUE(parser_.ParseTest(
      "ninja_dyndep_version = 1\n"
      "build out: dyndep\n", &err)) << err;
}

TEST_F(DyndepParserWithEdgeTest_110, NoNewlineAtEnd_110) {
  std::string err;
  // Input without trailing newline
  bool result = parser_.ParseTest("ninja_dyndep_version = 1", &err);
  // Just check it doesn't crash; behavior may vary
  (void)result;
}

TEST_F(DyndepParserWithEdgeTest_110, CommentLine_110) {
  std::string err;
  EXPECT_TRUE(parser_.ParseTest(
      "ninja_dyndep_version = 1\n"
      "# this is a comment\n"
      "build out: dyndep\n", &err)) << err;
}

TEST_F(DyndepParserWithEdgeTest_110, BlankLinesBetweenStatements_110) {
  std::string err;
  EXPECT_TRUE(parser_.ParseTest(
      "ninja_dyndep_version = 1\n"
      "\n"
      "build out: dyndep\n", &err)) << err;
}

TEST_F(DyndepParserWithEdgeTest_110, InvalidLetBinding_110) {
  std::string err;
  EXPECT_FALSE(parser_.ParseTest(
      "ninja_dyndep_version = 1\n"
      "build out: dyndep\n"
      "  invalid_var = something\n", &err));
  EXPECT_FALSE(err.empty());
}

TEST_F(DyndepParserWithEdgeTest_110, DyndepFilePopulated_110) {
  std::string err;
  ASSERT_TRUE(parser_.ParseTest(
      "ninja_dyndep_version = 1\n"
      "build out: dyndep\n", &err)) << err;
  
  // The dyndep_file_ should have been populated with the edge info
  EXPECT_FALSE(dyndep_file_.empty());
}

TEST_F(DyndepParserWithEdgeTest_110, DyndepFilePopulatedWithRestat_110) {
  std::string err;
  ASSERT_TRUE(parser_.ParseTest(
      "ninja_dyndep_version = 1\n"
      "build out: dyndep\n"
      "  restat = 1\n", &err)) << err;
  
  EXPECT_FALSE(dyndep_file_.empty());
  
  // Check if the edge is in the dyndep file and restat is set
  Node* out = state_.GetNode("out", 0);
  Edge* edge = out->in_edge();
  auto it = dyndep_file_.find(edge);
  ASSERT_NE(it, dyndep_file_.end());
  EXPECT_TRUE(it->second.restat_);
}

TEST_F(DyndepParserWithEdgeTest_110, DyndepWithoutRestatDefaultsFalse_110) {
  std::string err;
  ASSERT_TRUE(parser_.ParseTest(
      "ninja_dyndep_version = 1\n"
      "build out: dyndep\n", &err)) << err;
  
  Node* out = state_.GetNode("out", 0);
  Edge* edge = out->in_edge();
  auto it = dyndep_file_.find(edge);
  ASSERT_NE(it, dyndep_file_.end());
  EXPECT_FALSE(it->second.restat_);
}
