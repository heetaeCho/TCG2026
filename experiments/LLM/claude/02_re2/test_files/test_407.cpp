#include "gtest/gtest.h"
#include "re2/prog.h"
#include "absl/strings/string_view.h"

namespace re2 {

// Helper to check if a character is a word character (matching Prog::IsWordChar behavior)
// Word chars are [0-9A-Za-z_]
static bool IsWordCharHelper(uint8_t c) {
  return Prog::IsWordChar(c);
}

class ProgEmptyFlagsTest_407 : public ::testing::Test {
 protected:
};

// Test: pointer at beginning of text that starts with non-word, non-newline char
TEST_F(ProgEmptyFlagsTest_407, BeginOfText_407) {
  absl::string_view text("hello");
  const char* p = text.data();
  uint32_t flags = Prog::EmptyFlags(text, p);
  EXPECT_TRUE(flags & kEmptyBeginText);
  EXPECT_TRUE(flags & kEmptyBeginLine);
}

// Test: pointer at end of text
TEST_F(ProgEmptyFlagsTest_407, EndOfText_407) {
  absl::string_view text("hello");
  const char* p = text.data() + text.size();
  uint32_t flags = Prog::EmptyFlags(text, p);
  EXPECT_TRUE(flags & kEmptyEndText);
  EXPECT_TRUE(flags & kEmptyEndLine);
}

// Test: pointer at the beginning AND end of empty text
TEST_F(ProgEmptyFlagsTest_407, EmptyText_407) {
  absl::string_view text("");
  const char* p = text.data();
  uint32_t flags = Prog::EmptyFlags(text, p);
  EXPECT_TRUE(flags & kEmptyBeginText);
  EXPECT_TRUE(flags & kEmptyBeginLine);
  EXPECT_TRUE(flags & kEmptyEndText);
  EXPECT_TRUE(flags & kEmptyEndLine);
  // Empty text: no word chars on either side, so NonWordBoundary
  EXPECT_TRUE(flags & kEmptyNonWordBoundary);
  EXPECT_FALSE(flags & kEmptyWordBoundary);
}

// Test: pointer in the middle of text, after a newline
TEST_F(ProgEmptyFlagsTest_407, AfterNewline_407) {
  absl::string_view text("ab\ncd");
  const char* p = text.data() + 3; // points to 'c', p[-1] == '\n'
  uint32_t flags = Prog::EmptyFlags(text, p);
  EXPECT_TRUE(flags & kEmptyBeginLine);
  EXPECT_FALSE(flags & kEmptyBeginText);
}

// Test: pointer before a newline (should set kEmptyEndLine)
TEST_F(ProgEmptyFlagsTest_407, BeforeNewline_407) {
  absl::string_view text("ab\ncd");
  const char* p = text.data() + 2; // points to '\n'
  uint32_t flags = Prog::EmptyFlags(text, p);
  EXPECT_TRUE(flags & kEmptyEndLine);
  EXPECT_FALSE(flags & kEmptyEndText);
}

// Test: word boundary at beginning of text with word char
TEST_F(ProgEmptyFlagsTest_407, WordBoundaryAtBegin_407) {
  absl::string_view text("abc");
  const char* p = text.data();
  uint32_t flags = Prog::EmptyFlags(text, p);
  // p[0] = 'a' is a word char, p is at start of text
  EXPECT_TRUE(flags & kEmptyWordBoundary);
  EXPECT_FALSE(flags & kEmptyNonWordBoundary);
}

// Test: non-word boundary at beginning of text with non-word char
TEST_F(ProgEmptyFlagsTest_407, NonWordBoundaryAtBegin_407) {
  absl::string_view text(" abc");
  const char* p = text.data();
  uint32_t flags = Prog::EmptyFlags(text, p);
  // p[0] = ' ' is not a word char, p is at start of text
  EXPECT_FALSE(flags & kEmptyWordBoundary);
  EXPECT_TRUE(flags & kEmptyNonWordBoundary);
}

// Test: word boundary at end of text with word char
TEST_F(ProgEmptyFlagsTest_407, WordBoundaryAtEnd_407) {
  absl::string_view text("abc");
  const char* p = text.data() + text.size();
  uint32_t flags = Prog::EmptyFlags(text, p);
  // p[-1] = 'c' is a word char, p is at end of text
  EXPECT_TRUE(flags & kEmptyWordBoundary);
  EXPECT_FALSE(flags & kEmptyNonWordBoundary);
}

// Test: non-word boundary at end of text with non-word char
TEST_F(ProgEmptyFlagsTest_407, NonWordBoundaryAtEnd_407) {
  absl::string_view text("abc ");
  const char* p = text.data() + text.size();
  uint32_t flags = Prog::EmptyFlags(text, p);
  // p[-1] = ' ' is not a word char
  EXPECT_FALSE(flags & kEmptyWordBoundary);
  EXPECT_TRUE(flags & kEmptyNonWordBoundary);
}

// Test: word boundary in middle of text (word->non-word transition)
TEST_F(ProgEmptyFlagsTest_407, WordBoundaryMiddle_WordToNonWord_407) {
  absl::string_view text("a b");
  const char* p = text.data() + 1; // points to ' ', p[-1] = 'a'
  uint32_t flags = Prog::EmptyFlags(text, p);
  // p[-1]='a' is word, p[0]=' ' is non-word => word boundary
  EXPECT_TRUE(flags & kEmptyWordBoundary);
  EXPECT_FALSE(flags & kEmptyNonWordBoundary);
}

// Test: word boundary in middle of text (non-word->word transition)
TEST_F(ProgEmptyFlagsTest_407, WordBoundaryMiddle_NonWordToWord_407) {
  absl::string_view text(" a");
  const char* p = text.data() + 1; // points to 'a', p[-1] = ' '
  uint32_t flags = Prog::EmptyFlags(text, p);
  // p[-1]=' ' is non-word, p[0]='a' is word => word boundary
  EXPECT_TRUE(flags & kEmptyWordBoundary);
  EXPECT_FALSE(flags & kEmptyNonWordBoundary);
}

// Test: non-word boundary in middle (word->word)
TEST_F(ProgEmptyFlagsTest_407, NonWordBoundaryMiddle_WordToWord_407) {
  absl::string_view text("ab");
  const char* p = text.data() + 1; // points to 'b', p[-1] = 'a'
  uint32_t flags = Prog::EmptyFlags(text, p);
  // Both are word chars => non-word boundary
  EXPECT_FALSE(flags & kEmptyWordBoundary);
  EXPECT_TRUE(flags & kEmptyNonWordBoundary);
}

// Test: non-word boundary in middle (non-word->non-word)
TEST_F(ProgEmptyFlagsTest_407, NonWordBoundaryMiddle_NonWordToNonWord_407) {
  absl::string_view text("  ");
  const char* p = text.data() + 1; // points to ' ', p[-1] = ' '
  uint32_t flags = Prog::EmptyFlags(text, p);
  EXPECT_FALSE(flags & kEmptyWordBoundary);
  EXPECT_TRUE(flags & kEmptyNonWordBoundary);
}

// Test: middle of text, not near newlines, no special boundary
TEST_F(ProgEmptyFlagsTest_407, MiddleNoNewline_407) {
  absl::string_view text("abcde");
  const char* p = text.data() + 2; // points to 'c'
  uint32_t flags = Prog::EmptyFlags(text, p);
  EXPECT_FALSE(flags & kEmptyBeginText);
  EXPECT_FALSE(flags & kEmptyBeginLine);
  EXPECT_FALSE(flags & kEmptyEndText);
  EXPECT_FALSE(flags & kEmptyEndLine);
}

// Test: p after newline at end (newline is last char)
TEST_F(ProgEmptyFlagsTest_407, NewlineAtEnd_407) {
  absl::string_view text("abc\n");
  const char* p = text.data() + text.size(); // end of text
  uint32_t flags = Prog::EmptyFlags(text, p);
  EXPECT_TRUE(flags & kEmptyEndText);
  EXPECT_TRUE(flags & kEmptyEndLine);
  // p[-1] = '\n', not a word char
  EXPECT_FALSE(flags & kEmptyWordBoundary);
  EXPECT_TRUE(flags & kEmptyNonWordBoundary);
}

// Test: text with only a newline, pointer at start
TEST_F(ProgEmptyFlagsTest_407, SingleNewlineAtStart_407) {
  absl::string_view text("\n");
  const char* p = text.data();
  uint32_t flags = Prog::EmptyFlags(text, p);
  EXPECT_TRUE(flags & kEmptyBeginText);
  EXPECT_TRUE(flags & kEmptyBeginLine);
  EXPECT_TRUE(flags & kEmptyEndLine); // p[0] == '\n'
  EXPECT_FALSE(flags & kEmptyEndText);
}

// Test: text with only a newline, pointer at end
TEST_F(ProgEmptyFlagsTest_407, SingleNewlineAtEnd_407) {
  absl::string_view text("\n");
  const char* p = text.data() + text.size();
  uint32_t flags = Prog::EmptyFlags(text, p);
  EXPECT_TRUE(flags & kEmptyEndText);
  EXPECT_TRUE(flags & kEmptyEndLine);
  EXPECT_TRUE(flags & kEmptyBeginLine); // p[-1] == '\n'
  EXPECT_FALSE(flags & kEmptyBeginText);
}

// Test: digit is a word character
TEST_F(ProgEmptyFlagsTest_407, DigitIsWordChar_407) {
  absl::string_view text(" 5");
  const char* p = text.data() + 1; // points to '5', p[-1] = ' '
  uint32_t flags = Prog::EmptyFlags(text, p);
  EXPECT_TRUE(flags & kEmptyWordBoundary);
}

// Test: underscore is a word character
TEST_F(ProgEmptyFlagsTest_407, UnderscoreIsWordChar_407) {
  absl::string_view text(" _");
  const char* p = text.data() + 1; // points to '_', p[-1] = ' '
  uint32_t flags = Prog::EmptyFlags(text, p);
  EXPECT_TRUE(flags & kEmptyWordBoundary);
}

// Test: IsWordChar static method directly
TEST_F(ProgEmptyFlagsTest_407, IsWordChar_Letters_407) {
  EXPECT_TRUE(Prog::IsWordChar('a'));
  EXPECT_TRUE(Prog::IsWordChar('z'));
  EXPECT_TRUE(Prog::IsWordChar('A'));
  EXPECT_TRUE(Prog::IsWordChar('Z'));
  EXPECT_TRUE(Prog::IsWordChar('0'));
  EXPECT_TRUE(Prog::IsWordChar('9'));
  EXPECT_TRUE(Prog::IsWordChar('_'));
}

TEST_F(ProgEmptyFlagsTest_407, IsWordChar_NonWord_407) {
  EXPECT_FALSE(Prog::IsWordChar(' '));
  EXPECT_FALSE(Prog::IsWordChar('\n'));
  EXPECT_FALSE(Prog::IsWordChar('\t'));
  EXPECT_FALSE(Prog::IsWordChar('.'));
  EXPECT_FALSE(Prog::IsWordChar('-'));
  EXPECT_FALSE(Prog::IsWordChar('!'));
  EXPECT_FALSE(Prog::IsWordChar('@'));
}

// Test: single word character text
TEST_F(ProgEmptyFlagsTest_407, SingleWordChar_AtStart_407) {
  absl::string_view text("a");
  const char* p = text.data();
  uint32_t flags = Prog::EmptyFlags(text, p);
  EXPECT_TRUE(flags & kEmptyBeginText);
  EXPECT_TRUE(flags & kEmptyBeginLine);
  EXPECT_TRUE(flags & kEmptyWordBoundary);
}

TEST_F(ProgEmptyFlagsTest_407, SingleWordChar_AtEnd_407) {
  absl::string_view text("a");
  const char* p = text.data() + 1;
  uint32_t flags = Prog::EmptyFlags(text, p);
  EXPECT_TRUE(flags & kEmptyEndText);
  EXPECT_TRUE(flags & kEmptyEndLine);
  EXPECT_TRUE(flags & kEmptyWordBoundary);
}

// Test: single non-word character text
TEST_F(ProgEmptyFlagsTest_407, SingleNonWordChar_AtStart_407) {
  absl::string_view text("!");
  const char* p = text.data();
  uint32_t flags = Prog::EmptyFlags(text, p);
  EXPECT_TRUE(flags & kEmptyBeginText);
  EXPECT_TRUE(flags & kEmptyNonWordBoundary);
  EXPECT_FALSE(flags & kEmptyWordBoundary);
}

// Test: multiple newlines
TEST_F(ProgEmptyFlagsTest_407, BetweenNewlines_407) {
  absl::string_view text("\n\n");
  const char* p = text.data() + 1; // between two newlines
  uint32_t flags = Prog::EmptyFlags(text, p);
  // p[-1] == '\n' => kEmptyBeginLine
  EXPECT_TRUE(flags & kEmptyBeginLine);
  // p[0] == '\n' => kEmptyEndLine
  EXPECT_TRUE(flags & kEmptyEndLine);
  EXPECT_FALSE(flags & kEmptyBeginText);
  EXPECT_FALSE(flags & kEmptyEndText);
}

// Test: word boundary between letter and newline
TEST_F(ProgEmptyFlagsTest_407, WordCharBeforeNewline_407) {
  absl::string_view text("a\n");
  const char* p = text.data() + 1; // points to '\n', p[-1] = 'a'
  uint32_t flags = Prog::EmptyFlags(text, p);
  // 'a' is word, '\n' is not => word boundary
  EXPECT_TRUE(flags & kEmptyWordBoundary);
  EXPECT_TRUE(flags & kEmptyEndLine);
}

}  // namespace re2
