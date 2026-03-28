#include <gtest/gtest.h>
#include <memory>
#include <string>
#include <vector>

#include "re2/re2.h"
#include "re2/filtered_re2.h"
#include "re2/set.h"

using namespace re2;

// Tests for RE2::Options which is a key dependency of Filter::Compile
class RE2OptionsTest_64 : public ::testing::Test {
 protected:
  RE2::Options options_;
};

TEST_F(RE2OptionsTest_64, DefaultOptions_64) {
  EXPECT_TRUE(options_.case_sensitive());
  EXPECT_FALSE(options_.literal());
  EXPECT_FALSE(options_.posix_syntax());
  EXPECT_FALSE(options_.longest_match());
  EXPECT_TRUE(options_.log_errors());
  EXPECT_FALSE(options_.never_nl());
  EXPECT_FALSE(options_.dot_nl());
  EXPECT_FALSE(options_.never_capture());
  EXPECT_FALSE(options_.perl_classes());
  EXPECT_FALSE(options_.word_boundary());
  EXPECT_FALSE(options_.one_line());
}

TEST_F(RE2OptionsTest_64, SetLiteral_64) {
  options_.set_literal(true);
  EXPECT_TRUE(options_.literal());
  options_.set_literal(false);
  EXPECT_FALSE(options_.literal());
}

TEST_F(RE2OptionsTest_64, SetCaseSensitive_64) {
  options_.set_case_sensitive(false);
  EXPECT_FALSE(options_.case_sensitive());
  options_.set_case_sensitive(true);
  EXPECT_TRUE(options_.case_sensitive());
}

TEST_F(RE2OptionsTest_64, CopyOptions_64) {
  RE2::Options src;
  src.set_literal(true);
  src.set_case_sensitive(false);
  src.set_dot_nl(true);

  RE2::Options dst;
  dst.Copy(src);

  EXPECT_TRUE(dst.literal());
  EXPECT_FALSE(dst.case_sensitive());
  EXPECT_TRUE(dst.dot_nl());
}

TEST_F(RE2OptionsTest_64, SetMaxMem_64) {
  int64_t mem = 1024 * 1024;
  options_.set_max_mem(mem);
  EXPECT_EQ(options_.max_mem(), mem);
}

// Tests for RE2::Set which is used internally by Filter::Compile
class RE2SetTest_64 : public ::testing::Test {};

TEST_F(RE2SetTest_64, CompileEmptySet_64) {
  RE2::Options options;
  options.set_literal(true);
  options.set_case_sensitive(false);
  RE2::Set set(options, RE2::UNANCHORED);
  EXPECT_TRUE(set.Compile());
}

TEST_F(RE2SetTest_64, AddAndCompile_64) {
  RE2::Options options;
  options.set_literal(true);
  options.set_case_sensitive(false);
  RE2::Set set(options, RE2::UNANCHORED);

  std::string error;
  int idx = set.Add("hello", &error);
  EXPECT_EQ(idx, 0);

  idx = set.Add("world", &error);
  EXPECT_EQ(idx, 1);

  EXPECT_TRUE(set.Compile());
}

TEST_F(RE2SetTest_64, AddMultipleAndMatch_64) {
  RE2::Options options;
  options.set_literal(true);
  options.set_case_sensitive(false);
  RE2::Set set(options, RE2::UNANCHORED);

  std::string error;
  EXPECT_EQ(set.Add("foo", &error), 0);
  EXPECT_EQ(set.Add("bar", &error), 1);
  EXPECT_TRUE(set.Compile());

  std::vector<int> matches;
  EXPECT_TRUE(set.Match("this is foo text", &matches));
  EXPECT_FALSE(matches.empty());
}

TEST_F(RE2SetTest_64, CaseInsensitiveMatch_64) {
  RE2::Options options;
  options.set_literal(true);
  options.set_case_sensitive(false);
  RE2::Set set(options, RE2::UNANCHORED);

  std::string error;
  EXPECT_EQ(set.Add("hello", &error), 0);
  EXPECT_TRUE(set.Compile());

  std::vector<int> matches;
  EXPECT_TRUE(set.Match("HELLO", &matches));
  EXPECT_EQ(matches.size(), 1);
  EXPECT_EQ(matches[0], 0);
}

TEST_F(RE2SetTest_64, NoMatch_64) {
  RE2::Options options;
  options.set_literal(true);
  options.set_case_sensitive(false);
  RE2::Set set(options, RE2::UNANCHORED);

  std::string error;
  EXPECT_EQ(set.Add("xyz", &error), 0);
  EXPECT_TRUE(set.Compile());

  std::vector<int> matches;
  EXPECT_FALSE(set.Match("abc", &matches));
  EXPECT_TRUE(matches.empty());
}

// Tests for FilteredRE2 which is the underlying filter mechanism
class FilteredRE2Test_64 : public ::testing::Test {
 protected:
  re2::FilteredRE2 filter_;
};

TEST_F(FilteredRE2Test_64, AddSimplePattern_64) {
  int id;
  RE2::Options options;
  RE2::ErrorCode err = filter_.Add("hello", options, &id);
  EXPECT_EQ(err, RE2::NoError);
  EXPECT_EQ(id, 0);
}

TEST_F(FilteredRE2Test_64, AddMultiplePatterns_64) {
  int id;
  RE2::Options options;

  RE2::ErrorCode err = filter_.Add("hello", options, &id);
  EXPECT_EQ(err, RE2::NoError);
  EXPECT_EQ(id, 0);

  err = filter_.Add("world", options, &id);
  EXPECT_EQ(err, RE2::NoError);
  EXPECT_EQ(id, 1);
}

TEST_F(FilteredRE2Test_64, CompileAndGetAtoms_64) {
  int id;
  RE2::Options options;
  filter_.Add("hello.*world", options, &id);

  std::vector<std::string> atoms;
  filter_.Compile(&atoms);
  // After compile, atoms should be populated (or empty for trivial patterns)
  // We can't assert specific contents without knowing internals
}

TEST_F(FilteredRE2Test_64, GetRE2AfterAdd_64) {
  int id;
  RE2::Options options;
  filter_.Add("test_pattern", options, &id);

  const RE2& re2 = filter_.GetRE2(id);
  EXPECT_EQ(re2.pattern(), "test_pattern");
}

TEST_F(FilteredRE2Test_64, EmptyFilterCompile_64) {
  std::vector<std::string> atoms;
  filter_.Compile(&atoms);
  EXPECT_TRUE(atoms.empty());
}

TEST_F(FilteredRE2Test_64, MatchAfterCompile_64) {
  int id;
  RE2::Options options;
  filter_.Add("hello", options, &id);
  EXPECT_EQ(id, 0);

  std::vector<std::string> atoms;
  filter_.Compile(&atoms);

  // Build a set from atoms for matching
  RE2::Options set_options;
  set_options.set_literal(true);
  set_options.set_case_sensitive(false);
  RE2::Set set(set_options, RE2::UNANCHORED);
  for (int i = 0; i < static_cast<int>(atoms.size()); ++i) {
    EXPECT_EQ(set.Add(atoms[i], nullptr), i);
  }
  EXPECT_TRUE(set.Compile());

  std::vector<int> atom_matches;
  if (!atoms.empty()) {
    set.Match("hello world", &atom_matches);
  }

  std::vector<int> regex_matches;
  filter_.AllMatches("hello world", atom_matches, &regex_matches);
  EXPECT_FALSE(regex_matches.empty());
  EXPECT_EQ(regex_matches[0], 0);
}

TEST_F(FilteredRE2Test_64, NoMatchReturnsEmpty_64) {
  int id;
  RE2::Options options;
  filter_.Add("xyz123", options, &id);

  std::vector<std::string> atoms;
  filter_.Compile(&atoms);

  std::vector<int> regex_matches;
  std::vector<int> empty_atom_matches;
  filter_.AllMatches("abcdef", empty_atom_matches, &regex_matches);
  EXPECT_TRUE(regex_matches.empty());
}

TEST_F(FilteredRE2Test_64, MultiplePatternMatch_64) {
  int id1, id2;
  RE2::Options options;
  filter_.Add("hello", options, &id1);
  filter_.Add("world", options, &id2);
  EXPECT_EQ(id1, 0);
  EXPECT_EQ(id2, 1);

  std::vector<std::string> atoms;
  filter_.Compile(&atoms);

  RE2::Options set_options;
  set_options.set_literal(true);
  set_options.set_case_sensitive(false);
  RE2::Set set(set_options, RE2::UNANCHORED);
  for (int i = 0; i < static_cast<int>(atoms.size()); ++i) {
    EXPECT_EQ(set.Add(atoms[i], nullptr), i);
  }
  EXPECT_TRUE(set.Compile());

  std::vector<int> atom_matches;
  if (!atoms.empty()) {
    set.Match("hello world", &atom_matches);
  }

  std::vector<int> regex_matches;
  filter_.AllMatches("hello world", atom_matches, &regex_matches);
  // Both patterns should match
  EXPECT_GE(regex_matches.size(), 2u);
}

// Test the RE2::Options configuration used in Filter::Compile
class FilterCompileOptionsTest_64 : public ::testing::Test {};

TEST_F(FilterCompileOptionsTest_64, LiteralCaseInsensitiveSetCompiles_64) {
  RE2::Options options;
  options.set_literal(true);
  options.set_case_sensitive(false);

  RE2::Set set(options, RE2::UNANCHORED);
  std::string error;
  EXPECT_EQ(set.Add("test", &error), 0);
  EXPECT_TRUE(set.Compile());

  std::vector<int> matches;
  EXPECT_TRUE(set.Match("TEST", &matches));
  EXPECT_EQ(matches.size(), 1);
}

TEST_F(FilterCompileOptionsTest_64, AddWithNullError_64) {
  RE2::Options options;
  options.set_literal(true);
  options.set_case_sensitive(false);

  RE2::Set set(options, RE2::UNANCHORED);
  // This mirrors what Filter::Compile does - passing NULL for error
  int idx = set.Add("atom", /*error=*/NULL);
  EXPECT_EQ(idx, 0);
  EXPECT_TRUE(set.Compile());
}

TEST_F(FilterCompileOptionsTest_64, SequentialAddReturnsSequentialIndices_64) {
  RE2::Options options;
  options.set_literal(true);
  options.set_case_sensitive(false);

  RE2::Set set(options, RE2::UNANCHORED);
  for (int i = 0; i < 10; ++i) {
    std::string atom = "atom" + std::to_string(i);
    int idx = set.Add(atom, nullptr);
    EXPECT_EQ(idx, i);
  }
  EXPECT_TRUE(set.Compile());
}

// Test that CannedOptions work correctly
TEST(RE2CannedOptionsTest_64, QuietOption_64) {
  RE2::Options options(RE2::Quiet);
  EXPECT_FALSE(options.log_errors());
}

TEST(RE2CannedOptionsTest_64, POSIXOption_64) {
  RE2::Options options(RE2::POSIX);
  EXPECT_TRUE(options.posix_syntax());
  EXPECT_TRUE(options.longest_match());
}

TEST(RE2CannedOptionsTest_64, Latin1Option_64) {
  RE2::Options options(RE2::Latin1);
  EXPECT_EQ(options.encoding(), RE2::Options::EncodingLatin1);
}
