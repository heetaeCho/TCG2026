#include "gtest/gtest.h"
#include "re2/re2.h"
#include "re2/regexp.h"
#include "re2/prog.h"

namespace re2 {

// Test that RE2 compilation works for basic patterns (exercises Compiler including PreVisit)
TEST(CompilerPreVisitTest_319, BasicPatternCompiles_319) {
  RE2 re("hello");
  ASSERT_TRUE(re.ok());
}

TEST(CompilerPreVisitTest_319, EmptyPatternCompiles_319) {
  RE2 re("");
  ASSERT_TRUE(re.ok());
}

TEST(CompilerPreVisitTest_319, SimpleAlternationCompiles_319) {
  RE2 re("a|b");
  ASSERT_TRUE(re.ok());
}

TEST(CompilerPreVisitTest_319, RepetitionCompiles_319) {
  RE2 re("a*b+c?");
  ASSERT_TRUE(re.ok());
}

TEST(CompilerPreVisitTest_319, CharacterClassCompiles_319) {
  RE2 re("[a-z0-9]");
  ASSERT_TRUE(re.ok());
}

TEST(CompilerPreVisitTest_319, NestedGroupsCompile_319) {
  RE2 re("((a)(b(c)))");
  ASSERT_TRUE(re.ok());
}

TEST(CompilerPreVisitTest_319, ComplexPatternCompiles_319) {
  RE2 re("^[a-zA-Z_][a-zA-Z0-9_]*$");
  ASSERT_TRUE(re.ok());
}

TEST(CompilerPreVisitTest_319, DotStarCompiles_319) {
  RE2 re(".*");
  ASSERT_TRUE(re.ok());
}

TEST(CompilerPreVisitTest_319, AnchoredPatternCompiles_319) {
  RE2 re("^abc$");
  ASSERT_TRUE(re.ok());
}

TEST(CompilerPreVisitTest_319, QuantifierWithBoundsCompiles_319) {
  RE2 re("a{2,5}");
  ASSERT_TRUE(re.ok());
}

TEST(CompilerPreVisitTest_319, LargeRepetitionBoundary_319) {
  // This tests behavior when compilation may stress the compiler
  RE2::Options opts;
  opts.set_max_mem(1 << 20);  // 1MB
  RE2 re("a{1000}", opts);
  ASSERT_TRUE(re.ok());
}

TEST(CompilerPreVisitTest_319, VeryLargePatternMayFail_319) {
  // When the compiler runs out of resources, failed_ becomes true
  // and PreVisit should stop traversal
  RE2::Options opts;
  opts.set_max_mem(1 << 10);  // Very small memory limit
  std::string pattern;
  for (int i = 0; i < 100; i++) {
    pattern += "(a*b*c*|d*e*f*)";
  }
  RE2 re(pattern, opts);
  // Pattern may or may not compile depending on limits - just verify no crash
  // If it fails, the compiler's failed_ state would have triggered PreVisit's stop
  SUCCEED();
}

TEST(CompilerPreVisitTest_319, NonCapturingGroupCompiles_319) {
  RE2 re("(?:abc)+");
  ASSERT_TRUE(re.ok());
}

TEST(CompilerPreVisitTest_319, CompiledPatternMatchesCorrectly_319) {
  RE2 re("(\\d+)-(\\w+)");
  ASSERT_TRUE(re.ok());
  ASSERT_TRUE(RE2::FullMatch("123-abc", re));
}

TEST(CompilerPreVisitTest_319, EscapeSequencesCompile_319) {
  RE2 re("\\d+\\.\\d+");
  ASSERT_TRUE(re.ok());
  ASSERT_TRUE(RE2::FullMatch("3.14", re));
}

TEST(CompilerPreVisitTest_319, UnicodePatternCompiles_319) {
  RE2 re("\\pL+");
  ASSERT_TRUE(re.ok());
}

}  // namespace re2
