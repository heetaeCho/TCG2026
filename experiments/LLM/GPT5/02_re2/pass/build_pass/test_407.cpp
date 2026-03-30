// File: prog_emptyflags_test_407.cc

#include "gtest/gtest.h"
#include "re2/prog.h"
#include "absl/strings/string_view.h"
#include <string>

using re2::Prog;
using re2::kEmptyBeginLine;
using re2::kEmptyEndLine;
using re2::kEmptyBeginText;
using re2::kEmptyEndText;
using re2::kEmptyWordBoundary;
using re2::kEmptyNonWordBoundary;

namespace {

bool IsWord(uint8_t c) { return Prog::IsWordChar(c); }

}  // namespace

// Start of non-empty text
TEST(Prog_EmptyFlagsTest_407, StartOfText_SetsBeginFlagsAndBoundary_407) {
  const std::string text = "x";
  const char* p = text.data();  // start
  uint32_t f = Prog::EmptyFlags(absl::string_view(text), p);

  EXPECT_TRUE(f & kEmptyBeginText);
  EXPECT_TRUE(f & kEmptyBeginLine);
  EXPECT_FALSE(f & kEmptyEndText);
  EXPECT_FALSE(f & kEmptyEndLine);

  if (IsWord(static_cast<uint8_t>(text[0]))) {
    EXPECT_TRUE(f & kEmptyWordBoundary);
    EXPECT_FALSE(f & kEmptyNonWordBoundary);
  } else {
    EXPECT_FALSE(f & kEmptyWordBoundary);
    EXPECT_TRUE(f & kEmptyNonWordBoundary);
  }
}

// End of non-empty text
TEST(Prog_EmptyFlagsTest_407, EndOfText_SetsEndFlagsAndBoundary_407) {
  const std::string text = "yz";
  const char* p = text.data() + text.size();  // end
  uint32_t f = Prog::EmptyFlags(absl::string_view(text), p);

  EXPECT_FALSE(f & kEmptyBeginText);
  EXPECT_FALSE(f & kEmptyBeginLine);
  EXPECT_TRUE(f & kEmptyEndText);
  EXPECT_TRUE(f & kEmptyEndLine);  // end-of-text counts as end-of-line

  const char prev = text[text.size() - 1];
  if (IsWord(static_cast<uint8_t>(prev))) {
    EXPECT_TRUE(f & kEmptyWordBoundary);
    EXPECT_FALSE(f & kEmptyNonWordBoundary);
  } else {
    EXPECT_FALSE(f & kEmptyWordBoundary);
    EXPECT_TRUE(f & kEmptyNonWordBoundary);
  }
}

// Position immediately before a '\n' (…|'\n'…): sets EndLine
TEST(Prog_EmptyFlagsTest_407, BeforeNewline_SetsEndLine_407) {
  const std::string text = "a\nb";
  const char* p = text.data() + 1;  // points at '\n'
  uint32_t f = Prog::EmptyFlags(absl::string_view(text), p);

  EXPECT_FALSE(f & kEmptyBeginText);
  EXPECT_FALSE(f & kEmptyBeginLine);
  EXPECT_FALSE(f & kEmptyEndText);
  EXPECT_TRUE(f & kEmptyEndLine);

  const uint8_t prev = static_cast<uint8_t>(text[0]);      // 'a'
  const uint8_t next = static_cast<uint8_t>(text[1]);      // '\n'
  const bool expect_boundary = (IsWord(prev) != IsWord(next));
  EXPECT_EQ(expect_boundary, static_cast<bool>(f & kEmptyWordBoundary));
  EXPECT_NE(static_cast<bool>(f & kEmptyWordBoundary),
            static_cast<bool>(f & kEmptyNonWordBoundary));  // mutually exclusive
}

// Position immediately after a '\n' ('\n'|…): sets BeginLine
TEST(Prog_EmptyFlagsTest_407, AfterNewline_SetsBeginLine_407) {
  const std::string text = "a\nb";
  const char* p = text.data() + 2;  // after '\n', before 'b'
  uint32_t f = Prog::EmptyFlags(absl::string_view(text), p);

  EXPECT_FALSE(f & kEmptyBeginText);
  EXPECT_TRUE(f & kEmptyBeginLine);
  EXPECT_FALSE(f & kEmptyEndText);
  EXPECT_FALSE(f & kEmptyEndLine);

  const uint8_t prev = static_cast<uint8_t>(text[1]);  // '\n'
  const uint8_t next = static_cast<uint8_t>(text[2]);  // 'b'
  const bool expect_boundary = (IsWord(prev) != IsWord(next));
  EXPECT_EQ(expect_boundary, static_cast<bool>(f & kEmptyWordBoundary));
  EXPECT_NE(static_cast<bool>(f & kEmptyWordBoundary),
            static_cast<bool>(f & kEmptyNonWordBoundary));
}

// Empty text: start == end, all text/line boundaries set; non-word boundary set
TEST(Prog_EmptyFlagsTest_407, EmptyText_AllTextLineFlags_NonWordBoundary_407) {
  const std::string text;  // ""
  const char* p = text.data();  // also end
  uint32_t f = Prog::EmptyFlags(absl::string_view(text), p);

  EXPECT_TRUE(f & kEmptyBeginText);
  EXPECT_TRUE(f & kEmptyBeginLine);
  EXPECT_TRUE(f & kEmptyEndText);
  EXPECT_TRUE(f & kEmptyEndLine);

  EXPECT_FALSE(f & kEmptyWordBoundary);   // special-cased
  EXPECT_TRUE(f & kEmptyNonWordBoundary);
}

// Middle of text where adjacent chars have same "wordness" -> NonWordBoundary
TEST(Prog_EmptyFlagsTest_407, MiddleSameWordness_SetsNonWordBoundary_407) {
  const std::string text = "ab";
  const char* p = text.data() + 1;  // between 'a' and 'b'
  uint32_t f = Prog::EmptyFlags(absl::string_view(text), p);

  EXPECT_FALSE(f & kEmptyBeginText);
  EXPECT_FALSE(f & kEmptyBeginLine);
  EXPECT_FALSE(f & kEmptyEndText);
  EXPECT_FALSE(f & kEmptyEndLine);

  const bool same_wordness =
      IsWord(static_cast<uint8_t>(text[0])) == IsWord(static_cast<uint8_t>(text[1]));
  if (same_wordness) {
    EXPECT_FALSE(f & kEmptyWordBoundary);
    EXPECT_TRUE(f & kEmptyNonWordBoundary);
  } else {
    EXPECT_TRUE(f & kEmptyWordBoundary);
    EXPECT_FALSE(f & kEmptyNonWordBoundary);
  }
}

// Sanity: At any position, WordBoundary and NonWordBoundary are exclusive.
TEST(Prog_EmptyFlagsTest_407, BoundaryFlags_AreMutuallyExclusive_407) {
  const std::string text = "x y\nz";
  for (size_t i = 0; i <= text.size(); ++i) {
    const char* p = text.data() + i;
    uint32_t f = Prog::EmptyFlags(absl::string_view(text), p);
    const bool wb = static_cast<bool>(f & kEmptyWordBoundary);
    const bool nwb = static_cast<bool>(f & kEmptyNonWordBoundary);
    EXPECT_NE(wb, nwb) << "i=" << i << " flags=" << f;
  }
}
