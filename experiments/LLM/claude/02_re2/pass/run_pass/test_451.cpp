#include "re2/re2.h"
#include "re2/prog.h"
#include "gtest/gtest.h"

#include <string>
#include <vector>

namespace re2 {

// Test DFA behavior through RE2's public interface, which exercises
// the DFA and its internal StateSaver class during matching operations.

class DFAStateSaverTest_451 : public ::testing::Test {
 protected:
  void SetUp() override {}
  void TearDown() override {}
};

// Test basic matching which exercises DFA creation and state saving
TEST_F(DFAStateSaverTest_451, BasicMatch_451) {
  RE2 re("hello");
  ASSERT_TRUE(re.ok());
  EXPECT_TRUE(RE2::FullMatch("hello", re));
  EXPECT_FALSE(RE2::FullMatch("world", re));
}

// Test partial matching
TEST_F(DFAStateSaverTest_451, PartialMatch_451) {
  RE2 re("ell");
  ASSERT_TRUE(re.ok());
  EXPECT_TRUE(RE2::PartialMatch("hello", re));
  EXPECT_FALSE(RE2::PartialMatch("world", re));
}

// Test with special states - empty pattern
TEST_F(DFAStateSaverTest_451, EmptyPattern_451) {
  RE2 re("");
  ASSERT_TRUE(re.ok());
  EXPECT_TRUE(RE2::FullMatch("", re));
  EXPECT_TRUE(RE2::PartialMatch("anything", re));
}

// Test with complex pattern that exercises DFA state management
TEST_F(DFAStateSaverTest_451, ComplexPattern_451) {
  RE2 re("(a|b)*c+d?e");
  ASSERT_TRUE(re.ok());
  EXPECT_TRUE(RE2::FullMatch("abababccce", re));
  EXPECT_TRUE(RE2::FullMatch("ce", re));
  EXPECT_TRUE(RE2::FullMatch("cde", re));
  EXPECT_FALSE(RE2::FullMatch("xyz", re));
}

// Test with alternation which may trigger state saving/restoring
TEST_F(DFAStateSaverTest_451, Alternation_451) {
  RE2 re("(abc|def|ghi)");
  ASSERT_TRUE(re.ok());
  EXPECT_TRUE(RE2::FullMatch("abc", re));
  EXPECT_TRUE(RE2::FullMatch("def", re));
  EXPECT_TRUE(RE2::FullMatch("ghi", re));
  EXPECT_FALSE(RE2::FullMatch("xyz", re));
}

// Test with repetition patterns
TEST_F(DFAStateSaverTest_451, Repetition_451) {
  RE2 re("a{3,5}");
  ASSERT_TRUE(re.ok());
  EXPECT_TRUE(RE2::FullMatch("aaa", re));
  EXPECT_TRUE(RE2::FullMatch("aaaa", re));
  EXPECT_TRUE(RE2::FullMatch("aaaaa", re));
  EXPECT_FALSE(RE2::FullMatch("aa", re));
  EXPECT_FALSE(RE2::FullMatch("aaaaaa", re));
}

// Test matching on longer strings that exercise DFA cache
TEST_F(DFAStateSaverTest_451, LongString_451) {
  RE2 re("[a-z]+@[a-z]+\\.[a-z]+");
  ASSERT_TRUE(re.ok());
  EXPECT_TRUE(RE2::FullMatch("user@example.com", re));
  EXPECT_FALSE(RE2::FullMatch("user@.com", re));
}

// Test with character classes
TEST_F(DFAStateSaverTest_451, CharacterClasses_451) {
  RE2 re("[[:digit:]]+");
  ASSERT_TRUE(re.ok());
  EXPECT_TRUE(RE2::FullMatch("12345", re));
  EXPECT_FALSE(RE2::FullMatch("abc", re));
  EXPECT_FALSE(RE2::FullMatch("", re));
}

// Test DeadState-like behavior: pattern that can never match
TEST_F(DFAStateSaverTest_451, NoMatch_451) {
  RE2 re("a{100}");
  ASSERT_TRUE(re.ok());
  EXPECT_FALSE(RE2::FullMatch("aaa", re));
  std::string long_a(100, 'a');
  EXPECT_TRUE(RE2::FullMatch(long_a, re));
}

// Test FullMatch state behavior
TEST_F(DFAStateSaverTest_451, FullMatchState_451) {
  RE2 re(".*");
  ASSERT_TRUE(re.ok());
  EXPECT_TRUE(RE2::FullMatch("", re));
  EXPECT_TRUE(RE2::FullMatch("anything at all", re));
}

// Test boundary: single character
TEST_F(DFAStateSaverTest_451, SingleChar_451) {
  RE2 re("x");
  ASSERT_TRUE(re.ok());
  EXPECT_TRUE(RE2::FullMatch("x", re));
  EXPECT_FALSE(RE2::FullMatch("y", re));
  EXPECT_FALSE(RE2::FullMatch("xx", re));
}

// Test with nested groups that exercise DFA state transitions
TEST_F(DFAStateSaverTest_451, NestedGroups_451) {
  RE2 re("((a+)(b+))+");
  ASSERT_TRUE(re.ok());
  EXPECT_TRUE(RE2::FullMatch("ab", re));
  EXPECT_TRUE(RE2::FullMatch("aabb", re));
  EXPECT_TRUE(RE2::FullMatch("ababab", re));
  EXPECT_FALSE(RE2::FullMatch("ba", re));
}

// Test with anchored patterns
TEST_F(DFAStateSaverTest_451, AnchoredPattern_451) {
  RE2 re("^abc$");
  ASSERT_TRUE(re.ok());
  EXPECT_TRUE(RE2::FullMatch("abc", re));
  EXPECT_FALSE(RE2::FullMatch("xabc", re));
  EXPECT_FALSE(RE2::FullMatch("abcx", re));
}

}  // namespace re2
