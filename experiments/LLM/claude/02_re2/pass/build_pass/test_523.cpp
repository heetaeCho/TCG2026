#include "gtest/gtest.h"
#include "absl/strings/string_view.h"

// We need access to the internal function and types.
// Since LookupPerlGroup is in the re2 namespace but not publicly exported,
// we need to declare the relevant types and the function.

namespace re2 {

// Forward declarations based on known structures in re2
struct URange {
  int lo;
  int hi;
};

struct UGroup {
  const char* name;
  int sign;
  const URange* range;
  int num_ranges;
};

// Declare the function we're testing
static const UGroup* LookupPerlGroup(absl::string_view name);

// We need to access the actual implementation, so we include the source
// or rely on linkage. Since the function is static, we need to include
// the source file or use a workaround.

}  // namespace re2

// Since LookupPerlGroup is a static function in parse.cc, we cannot directly
// call it from a separate translation unit. We need to include the source
// or use a test-friendly wrapper. For the purpose of these tests, we'll
// include the relevant parts to get access.

// Alternative approach: We test through the public regex parsing interface
// which exercises LookupPerlGroup internally. Perl character classes like
// \d, \s, \w and their negations \D, \S, \W are handled by LookupPerlGroup.

#include "re2/re2.h"
#include "re2/regexp.h"

namespace re2 {

class LookupPerlGroupTest_523 : public ::testing::Test {
 protected:
  // Helper: checks if a pattern containing a Perl class compiles successfully
  bool PatternCompiles(const std::string& pattern) {
    RE2 re(pattern);
    return re.ok();
  }

  // Helper: checks if a string matches a pattern
  bool Matches(const std::string& pattern, const std::string& text) {
    return RE2::FullMatch(text, pattern);
  }
};

// Test that \d matches digits
TEST_F(LookupPerlGroupTest_523, DigitClassMatchesDigits_523) {
  EXPECT_TRUE(Matches("\\d", "0"));
  EXPECT_TRUE(Matches("\\d", "5"));
  EXPECT_TRUE(Matches("\\d", "9"));
}

// Test that \d does not match non-digits
TEST_F(LookupPerlGroupTest_523, DigitClassDoesNotMatchNonDigits_523) {
  EXPECT_FALSE(Matches("\\d", "a"));
  EXPECT_FALSE(Matches("\\d", " "));
  EXPECT_FALSE(Matches("\\d", "!"));
}

// Test that \D matches non-digits
TEST_F(LookupPerlGroupTest_523, NonDigitClassMatchesNonDigits_523) {
  EXPECT_TRUE(Matches("\\D", "a"));
  EXPECT_TRUE(Matches("\\D", " "));
  EXPECT_TRUE(Matches("\\D", "!"));
}

// Test that \D does not match digits
TEST_F(LookupPerlGroupTest_523, NonDigitClassDoesNotMatchDigits_523) {
  EXPECT_FALSE(Matches("\\D", "0"));
  EXPECT_FALSE(Matches("\\D", "5"));
  EXPECT_FALSE(Matches("\\D", "9"));
}

// Test that \s matches whitespace
TEST_F(LookupPerlGroupTest_523, SpaceClassMatchesWhitespace_523) {
  EXPECT_TRUE(Matches("\\s", " "));
  EXPECT_TRUE(Matches("\\s", "\t"));
  EXPECT_TRUE(Matches("\\s", "\n"));
  EXPECT_TRUE(Matches("\\s", "\r"));
  EXPECT_TRUE(Matches("\\s", "\f"));
}

// Test that \s does not match non-whitespace
TEST_F(LookupPerlGroupTest_523, SpaceClassDoesNotMatchNonWhitespace_523) {
  EXPECT_FALSE(Matches("\\s", "a"));
  EXPECT_FALSE(Matches("\\s", "0"));
  EXPECT_FALSE(Matches("\\s", "!"));
}

// Test that \S matches non-whitespace
TEST_F(LookupPerlGroupTest_523, NonSpaceClassMatchesNonWhitespace_523) {
  EXPECT_TRUE(Matches("\\S", "a"));
  EXPECT_TRUE(Matches("\\S", "0"));
  EXPECT_TRUE(Matches("\\S", "!"));
}

// Test that \S does not match whitespace
TEST_F(LookupPerlGroupTest_523, NonSpaceClassDoesNotMatchWhitespace_523) {
  EXPECT_FALSE(Matches("\\S", " "));
  EXPECT_FALSE(Matches("\\S", "\t"));
  EXPECT_FALSE(Matches("\\S", "\n"));
}

// Test that \w matches word characters
TEST_F(LookupPerlGroupTest_523, WordClassMatchesWordChars_523) {
  EXPECT_TRUE(Matches("\\w", "a"));
  EXPECT_TRUE(Matches("\\w", "Z"));
  EXPECT_TRUE(Matches("\\w", "0"));
  EXPECT_TRUE(Matches("\\w", "_"));
}

// Test that \w does not match non-word characters
TEST_F(LookupPerlGroupTest_523, WordClassDoesNotMatchNonWordChars_523) {
  EXPECT_FALSE(Matches("\\w", " "));
  EXPECT_FALSE(Matches("\\w", "!"));
  EXPECT_FALSE(Matches("\\w", "@"));
}

// Test that \W matches non-word characters
TEST_F(LookupPerlGroupTest_523, NonWordClassMatchesNonWordChars_523) {
  EXPECT_TRUE(Matches("\\W", " "));
  EXPECT_TRUE(Matches("\\W", "!"));
  EXPECT_TRUE(Matches("\\W", "@"));
}

// Test that \W does not match word characters
TEST_F(LookupPerlGroupTest_523, NonWordClassDoesNotMatchWordChars_523) {
  EXPECT_FALSE(Matches("\\W", "a"));
  EXPECT_FALSE(Matches("\\W", "Z"));
  EXPECT_FALSE(Matches("\\W", "0"));
  EXPECT_FALSE(Matches("\\W", "_"));
}

// Test Perl classes used within larger patterns
TEST_F(LookupPerlGroupTest_523, PerlClassInLargerPattern_523) {
  EXPECT_TRUE(Matches("\\d+", "12345"));
  EXPECT_TRUE(Matches("\\w+", "hello_world123"));
  EXPECT_TRUE(Matches("\\s+", "   \t\n"));
  EXPECT_FALSE(Matches("\\d+", "abc"));
  EXPECT_FALSE(Matches("\\w+", "   "));
}

// Test Perl classes combined with other elements
TEST_F(LookupPerlGroupTest_523, PerlClassCombinedWithOtherElements_523) {
  EXPECT_TRUE(Matches("a\\d+b", "a123b"));
  EXPECT_FALSE(Matches("a\\d+b", "ab"));
  EXPECT_TRUE(Matches("\\w+@\\w+\\.\\w+", "user@host.com"));
}

// Test boundary: empty string should not match single Perl class
TEST_F(LookupPerlGroupTest_523, EmptyStringDoesNotMatchSingleClass_523) {
  EXPECT_FALSE(Matches("\\d", ""));
  EXPECT_FALSE(Matches("\\s", ""));
  EXPECT_FALSE(Matches("\\w", ""));
  EXPECT_FALSE(Matches("\\D", ""));
  EXPECT_FALSE(Matches("\\S", ""));
  EXPECT_FALSE(Matches("\\W", ""));
}

// Test Perl classes inside character classes
TEST_F(LookupPerlGroupTest_523, PerlClassInsideCharacterClass_523) {
  EXPECT_TRUE(Matches("[\\d]+", "123"));
  EXPECT_TRUE(Matches("[\\da-f]+", "1a2b3c"));
  EXPECT_FALSE(Matches("[\\d]+", "abc"));
}

// Test multiple Perl classes in one pattern
TEST_F(LookupPerlGroupTest_523, MultiplePerlClassesInPattern_523) {
  EXPECT_TRUE(Matches("\\d\\s\\w", "1 a"));
  EXPECT_FALSE(Matches("\\d\\s\\w", "aaa"));
}

// Test that patterns with Perl classes compile successfully
TEST_F(LookupPerlGroupTest_523, PerlClassPatternsCompile_523) {
  EXPECT_TRUE(PatternCompiles("\\d"));
  EXPECT_TRUE(PatternCompiles("\\D"));
  EXPECT_TRUE(PatternCompiles("\\s"));
  EXPECT_TRUE(PatternCompiles("\\S"));
  EXPECT_TRUE(PatternCompiles("\\w"));
  EXPECT_TRUE(PatternCompiles("\\W"));
}

// Test digit boundary values
TEST_F(LookupPerlGroupTest_523, DigitBoundaryValues_523) {
  // '/' is just before '0' in ASCII
  EXPECT_FALSE(Matches("\\d", "/"));
  // '0' is the first digit
  EXPECT_TRUE(Matches("\\d", "0"));
  // '9' is the last digit
  EXPECT_TRUE(Matches("\\d", "9"));
  // ':' is just after '9' in ASCII
  EXPECT_FALSE(Matches("\\d", ":"));
}

// Test word character boundaries
TEST_F(LookupPerlGroupTest_523, WordCharBoundaryValues_523) {
  EXPECT_TRUE(Matches("\\w", "a"));
  EXPECT_TRUE(Matches("\\w", "z"));
  EXPECT_TRUE(Matches("\\w", "A"));
  EXPECT_TRUE(Matches("\\w", "Z"));
  EXPECT_TRUE(Matches("\\w", "0"));
  EXPECT_TRUE(Matches("\\w", "9"));
  EXPECT_TRUE(Matches("\\w", "_"));
  // Characters adjacent to word char ranges
  EXPECT_FALSE(Matches("\\w", "`"));  // just before 'a'
  EXPECT_FALSE(Matches("\\w", "{"));  // just after 'z'
  EXPECT_FALSE(Matches("\\w", "@"));  // just before 'A'
  EXPECT_FALSE(Matches("\\w", "["));  // just after 'Z'
}

}  // namespace re2
