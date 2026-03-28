// File: pcre_options_ctor_test_591.cc
#include <gtest/gtest.h>
#include "re2/util/pcre.h"

namespace re2 {

class PCREOptionsCtorTest_591 : public ::testing::Test {
protected:
  // Helper to create default options
  static PCRE_Options DefaultOpts() {
    PCRE_Options opts;
    return opts;  // Uses default option(), match_limit(), stack_limit(), report_errors()
  }
};

// [Normal] Construction with typical pattern and default options keeps the pattern.
TEST_F(PCREOptionsCtorTest_591, ConstructsWithCStringAndOptions_SetsPattern_591) {
  const char* pat = "ab(c|d)+\\w*";
  PCRE_Options opts = DefaultOpts();

  PCRE re(pat, opts);

  // Observable: pattern() should echo what was passed in.
  EXPECT_EQ(re.pattern(), std::string(pat));
}

// [Boundary] Empty pattern is accepted and exposed via pattern().
TEST_F(PCREOptionsCtorTest_591, ConstructsWithEmptyPattern_SetsEmptyPattern_591) {
  const char* pat = "";
  PCRE_Options opts = DefaultOpts();

  PCRE re(pat, opts);

  EXPECT_EQ(re.pattern(), std::string());
}

// [Boundary] Very long pattern is accepted and preserved.
TEST_F(PCREOptionsCtorTest_591, ConstructsWithLongPattern_SetsPattern_591) {
  // Create a long but reasonable pattern string
  std::string long_pat(4096, 'a');         // 4KB of 'a'
  long_pat += "(b|c)*\\d{2,5}\\w?";         // add some meta to avoid being purely literal
  PCRE_Options opts = DefaultOpts();

  PCRE re(long_pat.c_str(), opts);

  EXPECT_EQ(re.pattern(), long_pat);
}

// [Normal] Options can be set to various values; construction must succeed (no throw).
// We don't assert internal effects—only that construction is valid and pattern is preserved.
TEST_F(PCREOptionsCtorTest_591, ConstructsWithVariousOptionValues_DoesNotThrow_591) {
  const char* pat = "^start.*end$";
  PCRE_Options opts;

  // Flip switches and limits to exercise the constructor path that reads from PCRE_Options.
  // We don't assert internal behavior; just verify construction and observable pattern.
  // (Values are arbitrary but valid integers for limits.)
  opts.set_match_limit(12345);
  opts.set_stack_limit(6789);
  opts.set_report_errors(false);
  // If other option enums are available in your codebase, you can set them here:
  // opts.set_option(PCRE::None);  // Safe fallback if no other enums are exposed.

  // Construction should be well-defined and not crash/throw.
  PCRE re(pat, opts);

  EXPECT_EQ(re.pattern(), std::string(pat));
}

// [Error-ish input] Even with a likely-invalid pattern, construction must be well-defined.
// We only assert that construction succeeds and pattern() reflects the input.
// (We do NOT infer how errors are reported internally.)
TEST_F(PCREOptionsCtorTest_591, ConstructsWithPossiblyInvalidPattern_PreservesPattern_591) {
  const char* bad_pat = "(";  // Often invalid in many regex engines
  PCRE_Options opts = DefaultOpts();
  opts.set_report_errors(true);   // Flip to true
  {
    PCRE re(bad_pat, opts);
    EXPECT_EQ(re.pattern(), std::string(bad_pat));
  }
  // Also try with report_errors=false (observable behavior we check remains the same here)
  opts.set_report_errors(false);
  {
    PCRE re(bad_pat, opts);
    EXPECT_EQ(re.pattern(), std::string(bad_pat));
  }
}

}  // namespace re2
