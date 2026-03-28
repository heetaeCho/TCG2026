// File: re2_pattern_test.cc

#include <gtest/gtest.h>
#include <string>
#include "re2/re2.h"

using re2::RE2;

// Fixture kept minimal since we treat RE2 as a black box.
class RE2PatternTest_2 : public ::testing::Test {};

// --- Normal operation ---

// Construct from const char* and read back via pattern()
TEST_F(RE2PatternTest_2, PatternReturnsInputCString_2) {
  const char* pat = "abc123";
  RE2 re(pat);
  EXPECT_EQ(re.pattern(), std::string("abc123"));
}

// Construct from std::string and read back via pattern()
TEST_F(RE2PatternTest_2, PatternReturnsInputStdString_2) {
  std::string pat = "a.*b(c|d)?";
  RE2 re(pat);
  EXPECT_EQ(re.pattern(), pat);
}

// Ensure calling pattern() multiple times is consistent (address & value)
TEST_F(RE2PatternTest_2, PatternReferenceIsStablePerInstance_2) {
  RE2 re("x+y*z");
  // Take the address of the returned reference (publicly observable).
  const std::string* first_addr = &re.pattern();
  const std::string* second_addr = &re.pattern();
  EXPECT_EQ(first_addr, second_addr);
  EXPECT_EQ(re.pattern(), "x+y*z");
}

// --- Boundary conditions ---

// Empty pattern should be reported as empty
TEST_F(RE2PatternTest_2, EmptyPattern_2) {
  RE2 re("");
  EXPECT_TRUE(re.pattern().empty());
}

// Long pattern (not huge to avoid test slowness, but large enough to be meaningful)
TEST_F(RE2PatternTest_2, LongPattern_2) {
  std::string long_pat(2048, 'a');  // 2K 'a'
  RE2 re(long_pat);
  EXPECT_EQ(re.pattern().size(), long_pat.size());
  EXPECT_EQ(re.pattern(), long_pat);
}

// Special characters and metacharacters should round-trip as given
TEST_F(RE2PatternTest_2, SpecialMetacharactersRoundTrip_2) {
  const std::string pat = R"((^|\b)[A-Z]+\d{2,}\s?.*$)";
  RE2 re(pat.c_str());
  EXPECT_EQ(re.pattern(), pat);
}

// --- Observable lifetime/independence behaviors ---

// Changing the source std::string after construction should not affect RE2::pattern()
TEST_F(RE2PatternTest_2, SourceStringMutationDoesNotAffectStoredPattern_2) {
  std::string src = "before";
  RE2 re(src);
  src = "after";  // mutate the original source
  EXPECT_EQ(re.pattern(), "before");
}

// Passing a writable C-string buffer, then mutating it, should not affect RE2::pattern()
TEST_F(RE2PatternTest_2, SourceBufferMutationDoesNotAffectStoredPattern_2) {
  char buf[] = "hello";
  RE2 re(buf);
  buf[0] = 'y';  // mutate original buffer
  EXPECT_EQ(re.pattern(), "hello");
}

// Two separate instances should expose their own (independent) pattern values
TEST_F(RE2PatternTest_2, MultipleInstancesHaveIndependentPatterns_2) {
  RE2 re1("foo");
  RE2 re2("bar");
  EXPECT_EQ(re1.pattern(), "foo");
  EXPECT_EQ(re2.pattern(), "bar");
  // Calling pattern() repeatedly remains consistent per instance
  EXPECT_EQ(&re1.pattern(), &re1.pattern());
  EXPECT_EQ(&re2.pattern(), &re2.pattern());
  // And obviously their reported values differ
  EXPECT_NE(re1.pattern(), re2.pattern());
}
