#include "gtest/gtest.h"
#include "manifest_parser.h"
#include "state.h"
#include <string>
#include <map>

// A simple FileReader implementation for testing
struct MockFileReader : public ManifestParser::FileReader {
  bool ReadFile(const std::string& path, std::string* content, std::string* err) override {
    auto it = files_.find(path);
    if (it != files_.end()) {
      *content = it->second;
      return true;
    }
    *err = "file not found: " + path;
    return false;
  }
  std::map<std::string, std::string> files_;
};

class ManifestParserTest_11 : public ::testing::Test {
 protected:
  void SetUp() override {
    state_.Reset();
  }

  State state_;
  MockFileReader file_reader_;
};

TEST_F(ManifestParserTest_11, EmptyInput_11) {
  ManifestParser parser(&state_, &file_reader_, ManifestParserOptions());
  std::string err;
  EXPECT_TRUE(parser.ParseTest("", &err));
  EXPECT_EQ("", err);
}

TEST_F(ManifestParserTest_11, SimpleRule_11) {
  ManifestParser parser(&state_, &file_reader_, ManifestParserOptions());
  std::string err;
  EXPECT_TRUE(parser.ParseTest(
      "rule cat\n"
      "  command = cat $in > $out\n",
      &err));
  EXPECT_EQ("", err);
}

TEST_F(ManifestParserTest_11, SimpleEdge_11) {
  ManifestParser parser(&state_, &file_reader_, ManifestParserOptions());
  std::string err;
  EXPECT_TRUE(parser.ParseTest(
      "rule cat\n"
      "  command = cat $in > $out\n"
      "build out: cat in\n",
      &err));
  EXPECT_EQ("", err);
}

TEST_F(ManifestParserTest_11, InvalidSyntax_11) {
  ManifestParser parser(&state_, &file_reader_, ManifestParserOptions());
  std::string err;
  EXPECT_FALSE(parser.ParseTest("foobar", &err));
  EXPECT_NE("", err);
}

TEST_F(ManifestParserTest_11, BadIndentation_11) {
  ManifestParser parser(&state_, &file_reader_, ManifestParserOptions());
  std::string err;
  EXPECT_FALSE(parser.ParseTest("  command = foo\n", &err));
  EXPECT_NE("", err);
}

TEST_F(ManifestParserTest_11, RuleWithoutCommand_11) {
  ManifestParser parser(&state_, &file_reader_, ManifestParserOptions());
  std::string err;
  EXPECT_FALSE(parser.ParseTest(
      "rule cat\n"
      "build out: cat in\n",
      &err));
  EXPECT_NE("", err);
}

TEST_F(ManifestParserTest_11, PoolDeclaration_11) {
  ManifestParser parser(&state_, &file_reader_, ManifestParserOptions());
  std::string err;
  EXPECT_TRUE(parser.ParseTest(
      "pool link_pool\n"
      "  depth = 4\n",
      &err));
  EXPECT_EQ("", err);
}

TEST_F(ManifestParserTest_11, PoolWithoutDepth_11) {
  ManifestParser parser(&state_, &file_reader_, ManifestParserOptions());
  std::string err;
  EXPECT_FALSE(parser.ParseTest(
      "pool link_pool\n",
      &err));
  EXPECT_NE("", err);
}

TEST_F(ManifestParserTest_11, DefaultTarget_11) {
  ManifestParser parser(&state_, &file_reader_, ManifestParserOptions());
  std::string err;
  EXPECT_TRUE(parser.ParseTest(
      "rule cat\n"
      "  command = cat $in > $out\n"
      "build out: cat in\n"
      "default out\n",
      &err));
  EXPECT_EQ("", err);
}

TEST_F(ManifestParserTest_11, DefaultNonexistentTarget_11) {
  ManifestParser parser(&state_, &file_reader_, ManifestParserOptions());
  std::string err;
  EXPECT_FALSE(parser.ParseTest(
      "default nonexistent\n",
      &err));
  EXPECT_NE("", err);
}

TEST_F(ManifestParserTest_11, VariableBinding_11) {
  ManifestParser parser(&state_, &file_reader_, ManifestParserOptions());
  std::string err;
  EXPECT_TRUE(parser.ParseTest(
      "foo = bar\n",
      &err));
  EXPECT_EQ("", err);
}

TEST_F(ManifestParserTest_11, MultipleRules_11) {
  ManifestParser parser(&state_, &file_reader_, ManifestParserOptions());
  std::string err;
  EXPECT_TRUE(parser.ParseTest(
      "rule cat\n"
      "  command = cat $in > $out\n"
      "rule dog\n"
      "  command = dog $in > $out\n",
      &err));
  EXPECT_EQ("", err);
}

TEST_F(ManifestParserTest_11, DuplicateRule_11) {
  ManifestParser parser(&state_, &file_reader_, ManifestParserOptions());
  std::string err;
  EXPECT_FALSE(parser.ParseTest(
      "rule cat\n"
      "  command = cat $in > $out\n"
      "rule cat\n"
      "  command = cat $in > $out\n",
      &err));
  EXPECT_NE("", err);
}

TEST_F(ManifestParserTest_11, CommentsAreIgnored_11) {
  ManifestParser parser(&state_, &file_reader_, ManifestParserOptions());
  std::string err;
  EXPECT_TRUE(parser.ParseTest(
      "# this is a comment\n"
      "rule cat\n"
      "  command = cat $in > $out\n",
      &err));
  EXPECT_EQ("", err);
}

TEST_F(ManifestParserTest_11, BlankLines_11) {
  ManifestParser parser(&state_, &file_reader_, ManifestParserOptions());
  std::string err;
  EXPECT_TRUE(parser.ParseTest(
      "\n"
      "\n"
      "rule cat\n"
      "  command = cat $in > $out\n"
      "\n",
      &err));
  EXPECT_EQ("", err);
}

TEST_F(ManifestParserTest_11, BuildWithMultipleInputsAndOutputs_11) {
  ManifestParser parser(&state_, &file_reader_, ManifestParserOptions());
  std::string err;
  EXPECT_TRUE(parser.ParseTest(
      "rule cat\n"
      "  command = cat $in > $out\n"
      "build out1 out2: cat in1 in2\n",
      &err));
  EXPECT_EQ("", err);
}

TEST_F(ManifestParserTest_11, BuildWithImplicitDeps_11) {
  ManifestParser parser(&state_, &file_reader_, ManifestParserOptions());
  std::string err;
  EXPECT_TRUE(parser.ParseTest(
      "rule cat\n"
      "  command = cat $in > $out\n"
      "build out: cat in | implicit_dep\n",
      &err));
  EXPECT_EQ("", err);
}

TEST_F(ManifestParserTest_11, BuildWithOrderOnlyDeps_11) {
  ManifestParser parser(&state_, &file_reader_, ManifestParserOptions());
  std::string err;
  EXPECT_TRUE(parser.ParseTest(
      "rule cat\n"
      "  command = cat $in > $out\n"
      "build out: cat in || order_dep\n",
      &err));
  EXPECT_EQ("", err);
}

TEST_F(ManifestParserTest_11, BuildUsingUndefinedRule_11) {
  ManifestParser parser(&state_, &file_reader_, ManifestParserOptions());
  std::string err;
  EXPECT_FALSE(parser.ParseTest(
      "build out: undefined_rule in\n",
      &err));
  EXPECT_NE("", err);
}

TEST_F(ManifestParserTest_11, EdgeBindings_11) {
  ManifestParser parser(&state_, &file_reader_, ManifestParserOptions());
  std::string err;
  EXPECT_TRUE(parser.ParseTest(
      "rule cat\n"
      "  command = cat $in > $out $var\n"
      "build out: cat in\n"
      "  var = value\n",
      &err));
  EXPECT_EQ("", err);
}

TEST_F(ManifestParserTest_11, PoolUsedByEdge_11) {
  ManifestParser parser(&state_, &file_reader_, ManifestParserOptions());
  std::string err;
  EXPECT_TRUE(parser.ParseTest(
      "pool link_pool\n"
      "  depth = 4\n"
      "rule link\n"
      "  command = link $in > $out\n"
      "  pool = link_pool\n"
      "build out: link in\n",
      &err));
  EXPECT_EQ("", err);
}

TEST_F(ManifestParserTest_11, SubninjaMissingFile_11) {
  ManifestParser parser(&state_, &file_reader_, ManifestParserOptions());
  std::string err;
  EXPECT_FALSE(parser.ParseTest(
      "subninja nonexistent.ninja\n",
      &err));
  EXPECT_NE("", err);
}

TEST_F(ManifestParserTest_11, IncludeMissingFile_11) {
  ManifestParser parser(&state_, &file_reader_, ManifestParserOptions());
  std::string err;
  EXPECT_FALSE(parser.ParseTest(
      "include nonexistent.ninja\n",
      &err));
  EXPECT_NE("", err);
}

TEST_F(ManifestParserTest_11, IncludeExistingFile_11) {
  file_reader_.files_["sub.ninja"] = "rule cat\n  command = cat $in > $out\n";
  ManifestParser parser(&state_, &file_reader_, ManifestParserOptions());
  std::string err;
  EXPECT_TRUE(parser.ParseTest(
      "include sub.ninja\n",
      &err));
  EXPECT_EQ("", err);
}

TEST_F(ManifestParserTest_11, SubninjaExistingFile_11) {
  file_reader_.files_["sub.ninja"] = "rule cat\n  command = cat $in > $out\n";
  ManifestParser parser(&state_, &file_reader_, ManifestParserOptions());
  std::string err;
  EXPECT_TRUE(parser.ParseTest(
      "subninja sub.ninja\n",
      &err));
  EXPECT_EQ("", err);
}

TEST_F(ManifestParserTest_11, PoolNegativeDepth_11) {
  ManifestParser parser(&state_, &file_reader_, ManifestParserOptions());
  std::string err;
  EXPECT_FALSE(parser.ParseTest(
      "pool link_pool\n"
      "  depth = -1\n",
      &err));
  EXPECT_NE("", err);
}

TEST_F(ManifestParserTest_11, BuildWithValidations_11) {
  ManifestParser parser(&state_, &file_reader_, ManifestParserOptions());
  std::string err;
  EXPECT_TRUE(parser.ParseTest(
      "rule cat\n"
      "  command = cat $in > $out\n"
      "build out: cat in |@ validation\n",
      &err));
  EXPECT_EQ("", err);
}

TEST_F(ManifestParserTest_11, RuleWithDescription_11) {
  ManifestParser parser(&state_, &file_reader_, ManifestParserOptions());
  std::string err;
  EXPECT_TRUE(parser.ParseTest(
      "rule cat\n"
      "  command = cat $in > $out\n"
      "  description = concatenating files\n",
      &err));
  EXPECT_EQ("", err);
}

TEST_F(ManifestParserTest_11, RuleWithDepfile_11) {
  ManifestParser parser(&state_, &file_reader_, ManifestParserOptions());
  std::string err;
  EXPECT_TRUE(parser.ParseTest(
      "rule cc\n"
      "  command = cc $in -o $out\n"
      "  depfile = $out.d\n",
      &err));
  EXPECT_EQ("", err);
}

TEST_F(ManifestParserTest_11, RuleWithDeps_11) {
  ManifestParser parser(&state_, &file_reader_, ManifestParserOptions());
  std::string err;
  EXPECT_TRUE(parser.ParseTest(
      "rule cc\n"
      "  command = cc $in -o $out\n"
      "  deps = gcc\n"
      "  depfile = $out.d\n",
      &err));
  EXPECT_EQ("", err);
}

TEST_F(ManifestParserTest_11, RuleWithResponseFile_11) {
  ManifestParser parser(&state_, &file_reader_, ManifestParserOptions());
  std::string err;
  EXPECT_TRUE(parser.ParseTest(
      "rule link\n"
      "  command = link @$out.rsp\n"
      "  rspfile = $out.rsp\n"
      "  rspfile_content = $in\n",
      &err));
  EXPECT_EQ("", err);
}

TEST_F(ManifestParserTest_11, NullCharInInput_11) {
  ManifestParser parser(&state_, &file_reader_, ManifestParserOptions());
  std::string err;
  std::string input("build\0out", 9);
  EXPECT_FALSE(parser.ParseTest(input, &err));
  EXPECT_NE("", err);
}

TEST_F(ManifestParserTest_11, TrailingWhitespace_11) {
  ManifestParser parser(&state_, &file_reader_, ManifestParserOptions());
  std::string err;
  EXPECT_TRUE(parser.ParseTest(
      "rule cat\n"
      "  command = cat $in > $out\n"
      "\n",
      &err));
  EXPECT_EQ("", err);
}

TEST_F(ManifestParserTest_11, DuplicateEdgeWithOption_11) {
  ManifestParserOptions options;
  options.dupe_edge_action_ = kDupeEdgeActionError;
  ManifestParser parser(&state_, &file_reader_, options);
  std::string err;
  EXPECT_FALSE(parser.ParseTest(
      "rule cat\n"
      "  command = cat $in > $out\n"
      "build out: cat in\n"
      "build out: cat in2\n",
      &err));
  EXPECT_NE("", err);
}

TEST_F(ManifestParserTest_11, DuplicateEdgeWarning_11) {
  ManifestParserOptions options;
  options.dupe_edge_action_ = kDupeEdgeActionWarn;
  ManifestParser parser(&state_, &file_reader_, options);
  std::string err;
  EXPECT_TRUE(parser.ParseTest(
      "rule cat\n"
      "  command = cat $in > $out\n"
      "build out: cat in\n"
      "build out: cat in2\n",
      &err));
}

TEST_F(ManifestParserTest_11, PhonyRule_11) {
  ManifestParser parser(&state_, &file_reader_, ManifestParserOptions());
  std::string err;
  EXPECT_TRUE(parser.ParseTest(
      "build out: phony in\n",
      &err));
  EXPECT_EQ("", err);
}

TEST_F(ManifestParserTest_11, PhonyNoInputs_11) {
  ManifestParser parser(&state_, &file_reader_, ManifestParserOptions());
  std::string err;
  EXPECT_TRUE(parser.ParseTest(
      "build out: phony\n",
      &err));
  EXPECT_EQ("", err);
}

TEST_F(ManifestParserTest_11, VariableExpansionInBuild_11) {
  ManifestParser parser(&state_, &file_reader_, ManifestParserOptions());
  std::string err;
  EXPECT_TRUE(parser.ParseTest(
      "var = out\n"
      "rule cat\n"
      "  command = cat $in > $out\n"
      "build $var: cat in\n",
      &err));
  EXPECT_EQ("", err);
}

TEST_F(ManifestParserTest_11, ConsecutiveNewlines_11) {
  ManifestParser parser(&state_, &file_reader_, ManifestParserOptions());
  std::string err;
  EXPECT_TRUE(parser.ParseTest(
      "\n\n\n",
      &err));
  EXPECT_EQ("", err);
}

TEST_F(ManifestParserTest_11, LineContinuation_11) {
  ManifestParser parser(&state_, &file_reader_, ManifestParserOptions());
  std::string err;
  EXPECT_TRUE(parser.ParseTest(
      "rule cat\n"
      "  command = cat $\n"
      "    $in > $out\n",
      &err));
  EXPECT_EQ("", err);
}
