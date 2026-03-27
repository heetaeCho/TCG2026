// File: ./TestProjects/ninja/tests/dyndep_parser_test_110.cc

#include "dyndep_parser.h"

#include <string>

#include "dyndep.h"
#include "graph.h"
#include "state.h"
#include "test.h"      // For ::AssertParse and VirtualFileSystem
#include "gtest/gtest.h"

using std::string;

class DyndepParserTest_110 : public testing::Test {
protected:
  void SetUp() override {
    // Prepare a minimal build graph that DyndepParser can refer to.
    // We create a simple rule "touch" and a build edge that produces "out".
    ::AssertParse(&state_,
                  "rule touch\n"
                  " command = touch $out\n"
                  "build out otherout: touch\n");
  }

  // Helper for cases where parsing is expected to succeed with no error.
  void AssertParseOk_110(const char* input) {
    DyndepParser parser(&state_, &fs_, &dyndep_file_);
    string err;
    EXPECT_TRUE(parser.ParseTest(input, &err));
    EXPECT_EQ("", err);
  }

  State state_;
  VirtualFileSystem fs_;
  DyndepFile dyndep_file_;
};

//------------------------------------------------------------------------------
// Version header / top-level syntax
//------------------------------------------------------------------------------

TEST_F(DyndepParserTest_110, EmptyInputReturnsError_110) {
  const char kInput[] = "";
  DyndepParser parser(&state_, &fs_, &dyndep_file_);
  string err;

  EXPECT_FALSE(parser.ParseTest(kInput, &err));
  EXPECT_EQ("input:1: expected 'ninja_dyndep_version = ...'\n", err);
}

TEST_F(DyndepParserTest_110, ValidVersionLineParses_110) {
  AssertParseOk_110("ninja_dyndep_version = 1\n");
}

TEST_F(DyndepParserTest_110, CommentAndBlankBeforeVersion_110) {
  AssertParseOk_110(
      "# comment before version\n"
      "ninja_dyndep_version = 1\n");
}

TEST_F(DyndepParserTest_110, UnsupportedVersionZero_110) {
  const char kInput[] = "ninja_dyndep_version = 0\n";
  DyndepParser parser(&state_, &fs_, &dyndep_file_);
  string err;

  EXPECT_FALSE(parser.ParseTest(kInput, &err));
  EXPECT_EQ(
      "input:1: unsupported 'ninja_dyndep_version = 0'\n"
      "ninja_dyndep_version = 0\n"
      " ^ near here",
      err);
}

TEST_F(DyndepParserTest_110, UnsupportedVersionOneDotOne_110) {
  const char kInput[] = "ninja_dyndep_version = 1.1\n";
  DyndepParser parser(&state_, &fs_, &dyndep_file_);
  string err;

  EXPECT_FALSE(parser.ParseTest(kInput, &err));
  EXPECT_EQ(
      "input:1: unsupported 'ninja_dyndep_version = 1.1'\n"
      "ninja_dyndep_version = 1.1\n"
      " ^ near here",
      err);
}

TEST_F(DyndepParserTest_110, DuplicateVersionStatements_110) {
  const char kInput[] =
      "ninja_dyndep_version = 1\n"
      "ninja_dyndep_version = 1\n";
  DyndepParser parser(&state_, &fs_, &dyndep_file_);
  string err;

  EXPECT_FALSE(parser.ParseTest(kInput, &err));
  EXPECT_EQ("input:2: unexpected identifier\n", err);
}

TEST_F(DyndepParserTest_110, MissingVersionButOtherVariable_110) {
  const char kInput[] = "not_ninja_dyndep_version = 1\n";
  DyndepParser parser(&state_, &fs_, &dyndep_file_);
  string err;

  EXPECT_FALSE(parser.ParseTest(kInput, &err));
  EXPECT_EQ(
      "input:1: expected 'ninja_dyndep_version = ...'\n"
      "not_ninja_dyndep_version = 1\n"
      " ^ near here",
      err);
}

TEST_F(DyndepParserTest_110, MissingVersionBeforeBuild_110) {
  const char kInput[] = "build out: dyndep\n";
  DyndepParser parser(&state_, &fs_, &dyndep_file_);
  string err;

  EXPECT_FALSE(parser.ParseTest(kInput, &err));
  EXPECT_EQ("input:1: expected 'ninja_dyndep_version = ...'\n", err);
}

TEST_F(DyndepParserTest_110, UnexpectedEqualAndIndent_110) {
  {
    const char kInput[] = "= 1\n";
    DyndepParser parser(&state_, &fs_, &dyndep_file_);
    string err;

    EXPECT_FALSE(parser.ParseTest(kInput, &err));
    EXPECT_EQ("input:1: unexpected '='\n", err);
  }
  {
    const char kInput[] = " = 1\n";
    DyndepParser parser(&state_, &fs_, &dyndep_file_);
    string err;

    EXPECT_FALSE(parser.ParseTest(kInput, &err));
    EXPECT_EQ("input:1: unexpected indent\n", err);
  }
}

//------------------------------------------------------------------------------
// Build statement errors
//------------------------------------------------------------------------------

TEST_F(DyndepParserTest_110, DuplicateOutBuildStatements_110) {
  const char kInput[] =
      "ninja_dyndep_version = 1\n"
      "build out: dyndep\n"
      "build out: dyndep\n";
  DyndepParser parser(&state_, &fs_, &dyndep_file_);
  string err;

  EXPECT_FALSE(parser.ParseTest(kInput, &err));
  EXPECT_EQ(
      "input:3: multiple statements for 'out'\n"
      "build out: dyndep\n"
      " ^ near here",
      err);
}

TEST_F(DyndepParserTest_110, UnknownOutputHasNoBuildStatement_110) {
  const char kInput[] =
      "ninja_dyndep_version = 1\n"
      "build missing: dyndep\n";
  DyndepParser parser(&state_, &fs_, &dyndep_file_);
  string err;

  EXPECT_FALSE(parser.ParseTest(kInput, &err));
  EXPECT_EQ(
      "input:2: no build statement exists for 'missing'\n"
      "build missing: dyndep\n"
      " ^ near here",
      err);
}

TEST_F(DyndepParserTest_110, BuildWithoutRuleOrBadRule_110) {
  {
    const char kInput[] =
        "ninja_dyndep_version = 1\n"
        "build out:";
    DyndepParser parser(&state_, &fs_, &dyndep_file_);
    string err;

    EXPECT_FALSE(parser.ParseTest(kInput, &err));
    EXPECT_EQ(
        "input:2: expected build command name 'dyndep'\n"
        "build out:\n"
        " ^ near here",
        err);
  }
  {
    const char kInput[] =
        "ninja_dyndep_version = 1\n"
        "build out: touch";
    DyndepParser parser(&state_, &fs_, &dyndep_file_);
    string err;

    EXPECT_FALSE(parser.ParseTest(kInput, &err));
    EXPECT_EQ(
        "input:2: expected build command name 'dyndep'\n"
        "build out: touch\n"
        " ^ near here",
        err);
  }
}

TEST_F(DyndepParserTest_110, ExplicitInputsOrOutputsNotSupported_110) {
  {
    const char kInput[] =
        "ninja_dyndep_version = 1\n"
        "build out exp: dyndep\n";
    DyndepParser parser(&state_, &fs_, &dyndep_file_);
    string err;

    EXPECT_FALSE(parser.ParseTest(kInput, &err));
    EXPECT_EQ(
        "input:2: explicit outputs not supported\n"
        "build out exp: dyndep\n"
        " ^ near here",
        err);
  }
  {
    const char kInput[] =
        "ninja_dyndep_version = 1\n"
        "build out: dyndep exp\n";
    DyndepParser parser(&state_, &fs_, &dyndep_file_);
    string err;

    EXPECT_FALSE(parser.ParseTest(kInput, &err));
    EXPECT_EQ(
        "input:2: explicit inputs not supported\n"
        "build out: dyndep exp\n"
        " ^ near here",
        err);
  }
}

TEST_F(DyndepParserTest_110, OrderOnlyInputsNotSupported_110) {
  const char kInput[] =
      "ninja_dyndep_version = 1\n"
      "build out: dyndep ||\n";
  DyndepParser parser(&state_, &fs_, &dyndep_file_);
  string err;

  EXPECT_FALSE(parser.ParseTest(kInput, &err));
  EXPECT_EQ(
      "input:2: order-only inputs not supported\n"
      "build out: dyndep ||\n"
      " ^ near here",
      err);
}

//------------------------------------------------------------------------------
// Successful parsing: dyndep file contents (implicit in/out, restat, etc.)
//------------------------------------------------------------------------------

TEST_F(DyndepParserTest_110, NoImplicitDepsOrRestat_110) {
  AssertParseOk_110(
      "ninja_dyndep_version = 1\n"
      "build out: dyndep\n");

  ASSERT_EQ(1u, dyndep_file_.size());
  DyndepFile::iterator it = dyndep_file_.find(state_.edges_[0]);
  ASSERT_NE(it, dyndep_file_.end());

  EXPECT_FALSE(it->second.restat_);
  EXPECT_EQ(0u, it->second.implicit_outputs_.size());
  EXPECT_EQ(0u, it->second.implicit_inputs_.size());
}

TEST_F(DyndepParserTest_110, ImplicitInputsAndOutputsParsed_110) {
  AssertParseOk_110(
      "ninja_dyndep_version = 1\n"
      "build out | impout1 impout2: dyndep | impin1 impin2\n");

  ASSERT_EQ(1u, dyndep_file_.size());
  DyndepFile::iterator it = dyndep_file_.find(state_.edges_[0]);
  ASSERT_NE(it, dyndep_file_.end());

  // restat flag
  EXPECT_FALSE(it->second.restat_);

  // implicit outputs
  ASSERT_EQ(2u, it->second.implicit_outputs_.size());
  EXPECT_EQ("impout1", it->second.implicit_outputs_[0]->path());
  EXPECT_EQ("impout2", it->second.implicit_outputs_[1]->path());

  // implicit inputs
  ASSERT_EQ(2u, it->second.implicit_inputs_.size());
  EXPECT_EQ("impin1", it->second.implicit_inputs_[0]->path());
  EXPECT_EQ("impin2", it->second.implicit_inputs_[1]->path());
}

TEST_F(DyndepParserTest_110, RestatBindingIsReflected_110) {
  AssertParseOk_110(
      "ninja_dyndep_version = 1\n"
      "build out: dyndep\n"
      " restat = 1\n");

  ASSERT_EQ(1u, dyndep_file_.size());
  DyndepFile::iterator it = dyndep_file_.find(state_.edges_[0]);
  ASSERT_NE(it, dyndep_file_.end());

  EXPECT_TRUE(it->second.restat_);
  EXPECT_EQ(0u, it->second.implicit_outputs_.size());
  EXPECT_EQ(0u, it->second.implicit_inputs_.size());
}

//------------------------------------------------------------------------------
// Multiple edges in the same dyndep file
//------------------------------------------------------------------------------

TEST_F(DyndepParserTest_110, MultipleEdgesWithDifferentSettings_110) {
  // Add another edge ("out2") to the state beforehand.
  ::AssertParse(&state_, "build out2: touch\n");
  ASSERT_EQ(2u, state_.edges_.size());

  // Now the dyndep file provides dyndep info for both outputs.
  AssertParseOk_110(
      "ninja_dyndep_version = 1\n"
      "build out: dyndep\n"
      "build out2: dyndep\n"
      " restat = 1\n");

  ASSERT_EQ(2u, dyndep_file_.size());

  // First edge: no restat.
  {
    DyndepFile::iterator it = dyndep_file_.find(state_.edges_[0]);
    ASSERT_NE(it, dyndep_file_.end());
    EXPECT_FALSE(it->second.restat_);
    EXPECT_EQ(0u, it->second.implicit_outputs_.size());
    EXPECT_EQ(0u, it->second.implicit_inputs_.size());
  }

  // Second edge: restat = 1 from binding.
  {
    DyndepFile::iterator it = dyndep_file_.find(state_.edges_[1]);
    ASSERT_NE(it, dyndep_file_.end());
    EXPECT_TRUE(it->second.restat_);
    EXPECT_EQ(0u, it->second.implicit_outputs_.size());
    EXPECT_EQ(0u, it->second.implicit_inputs_.size());
  }
}
