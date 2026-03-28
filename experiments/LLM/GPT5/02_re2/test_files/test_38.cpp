// File: re2_options_copy_test_38.cc

#include <gtest/gtest.h>
#include "re2/re2.h"  // Adjust include path if needed

using re2::RE2;

// Helper to make a clearly non-default configuration using only public setters.
static RE2::Options MakeConfiguredOptions() {
  RE2::Options o;
  o.set_max_mem(123456789LL);
  o.set_encoding(RE2::Options::EncodingLatin1);
  o.set_posix_syntax(true);
  o.set_longest_match(true);
  o.set_log_errors(false);
  o.set_literal(true);
  o.set_never_nl(true);
  o.set_dot_nl(true);
  o.set_never_capture(true);
  o.set_case_sensitive(false);
  o.set_perl_classes(true);
  o.set_word_boundary(true);
  o.set_one_line(true);
  return o;
}

// [Normal] Copy should make destination reflect source's observable state.
TEST(RE2_OptionsCopyTest_38, CopiesAllObservableFields_38) {
  RE2::Options src = MakeConfiguredOptions();
  RE2::Options dst;

  // Precondition: make sure they differ initially in at least one obvious way.
  EXPECT_NE(dst.case_sensitive(), src.case_sensitive());

  dst.Copy(src);

  EXPECT_EQ(dst.max_mem(),        src.max_mem());
  EXPECT_EQ(dst.encoding(),       src.encoding());
  EXPECT_EQ(dst.posix_syntax(),   src.posix_syntax());
  EXPECT_EQ(dst.longest_match(),  src.longest_match());
  EXPECT_EQ(dst.log_errors(),     src.log_errors());
  EXPECT_EQ(dst.literal(),        src.literal());
  EXPECT_EQ(dst.never_nl(),       src.never_nl());
  EXPECT_EQ(dst.dot_nl(),         src.dot_nl());
  EXPECT_EQ(dst.never_capture(),  src.never_capture());
  EXPECT_EQ(dst.case_sensitive(), src.case_sensitive());
  EXPECT_EQ(dst.perl_classes(),   src.perl_classes());
  EXPECT_EQ(dst.word_boundary(),  src.word_boundary());
  EXPECT_EQ(dst.one_line(),       src.one_line());

  // Also verify that any parse flags derived from the options match.
  EXPECT_EQ(dst.ParseFlags(), src.ParseFlags());
}

// [Independence] After Copy, subsequent changes to source should not affect dest.
TEST(RE2_OptionsCopyTest_38, CopyProducesIndependentObject_38) {
  RE2::Options src = MakeConfiguredOptions();
  RE2::Options dst;
  dst.Copy(src);

  // Mutate the source via public setters.
  src.set_case_sensitive(true);
  src.set_literal(false);
  src.set_never_capture(false);
  src.set_max_mem(987654321LL);
  src.set_encoding(RE2::Options::EncodingUTF8);
  src.set_posix_syntax(false);
  src.set_longest_match(false);
  src.set_log_errors(true);
  src.set_never_nl(false);
  src.set_dot_nl(false);
  src.set_perl_classes(false);
  src.set_word_boundary(false);
  src.set_one_line(false);

  // Destination should remain unchanged (observable via getters).
  EXPECT_NE(dst.case_sensitive(), src.case_sensitive());
  EXPECT_NE(dst.literal(),        src.literal());
  EXPECT_NE(dst.never_capture(),  src.never_capture());
  EXPECT_NE(dst.max_mem(),        src.max_mem());
  EXPECT_NE(dst.encoding(),       src.encoding());
  EXPECT_NE(dst.posix_syntax(),   src.posix_syntax());
  EXPECT_NE(dst.longest_match(),  src.longest_match());
  EXPECT_NE(dst.log_errors(),     src.log_errors());
  EXPECT_NE(dst.never_nl(),       src.never_nl());
  EXPECT_NE(dst.dot_nl(),         src.dot_nl());
  EXPECT_NE(dst.perl_classes(),   src.perl_classes());
  EXPECT_NE(dst.word_boundary(),  src.word_boundary());
  EXPECT_NE(dst.one_line(),       src.one_line());

  // And their derived parse flags should also differ as a result.
  EXPECT_NE(dst.ParseFlags(), src.ParseFlags());
}

// [Boundary] Copy should preserve boundary values (e.g., zero for max_mem).
TEST(RE2_OptionsCopyTest_38, PreservesBoundaryValuesForMaxMem_38) {
  RE2::Options src;
  src.set_max_mem(0);  // Boundary value
  src.set_case_sensitive(false); // Also flip an unrelated field

  RE2::Options dst;
  dst.Copy(src);

  EXPECT_EQ(dst.max_mem(), 0);
  EXPECT_EQ(dst.case_sensitive(), false);
  EXPECT_EQ(dst.ParseFlags(), src.ParseFlags());
}

// [Idempotence] Self-copy should be safe and leave state unchanged.
TEST(RE2_OptionsCopyTest_38, SelfCopyIsNoOp_38) {
  RE2::Options opt = MakeConfiguredOptions();

  // Snapshot observable state via getters before self-copy.
  const auto max_mem        = opt.max_mem();
  const auto encoding       = opt.encoding();
  const auto posix_syntax   = opt.posix_syntax();
  const auto longest_match  = opt.longest_match();
  const auto log_errors     = opt.log_errors();
  const auto literal        = opt.literal();
  const auto never_nl       = opt.never_nl();
  const auto dot_nl         = opt.dot_nl();
  const auto never_capture  = opt.never_capture();
  const auto case_sensitive = opt.case_sensitive();
  const auto perl_classes   = opt.perl_classes();
  const auto word_boundary  = opt.word_boundary();
  const auto one_line       = opt.one_line();
  const auto flags          = opt.ParseFlags();

  // Self-copy (observable behavior should be unchanged).
  opt.Copy(opt);

  EXPECT_EQ(opt.max_mem(),        max_mem);
  EXPECT_EQ(opt.encoding(),       encoding);
  EXPECT_EQ(opt.posix_syntax(),   posix_syntax);
  EXPECT_EQ(opt.longest_match(),  longest_match);
  EXPECT_EQ(opt.log_errors(),     log_errors);
  EXPECT_EQ(opt.literal(),        literal);
  EXPECT_EQ(opt.never_nl(),       never_nl);
  EXPECT_EQ(opt.dot_nl(),         dot_nl);
  EXPECT_EQ(opt.never_capture(),  never_capture);
  EXPECT_EQ(opt.case_sensitive(), case_sensitive);
  EXPECT_EQ(opt.perl_classes(),   perl_classes);
  EXPECT_EQ(opt.word_boundary(),  word_boundary);
  EXPECT_EQ(opt.one_line(),       one_line);
  EXPECT_EQ(opt.ParseFlags(),     flags);
}
