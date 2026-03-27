// File: regexp_quest_test_340.cc
#include <gtest/gtest.h>
#include <memory>
#include "re2/regexp.h"

using namespace re2;

class RegexpQuestTest_340 : public ::testing::Test {
protected:
  struct RegexpDeleter {
    void operator()(Regexp* r) const {
      if (r) r->Decref();
    }
  };
  using RegexpPtr = std::unique_ptr<Regexp, RegexpDeleter>;

  static RegexpPtr MakeLiteral(Regexp::ParseFlags flags, Rune r = static_cast<Rune>('x')) {
    return RegexpPtr(Regexp::NewLiteral(r, flags));
  }
};

// Normal operation: creates a '?' node wrapping the given sub, preserving flags.
TEST_F(RegexpQuestTest_340, CreatesQuestNodeAndKeepsSubAndFlags_340) {
  auto flags = static_cast<Regexp::ParseFlags>(0);
  auto sub = MakeLiteral(flags);
  ASSERT_NE(sub, nullptr);

  Regexp* raw = Regexp::Quest(sub.get(), flags);
  RegexpQuestTest_340::RegexpPtr node(raw);
  ASSERT_NE(node, nullptr);

  EXPECT_EQ(node->op(), kRegexpQuest);
  EXPECT_EQ(node->parse_flags(), flags);

  // Verify the returned node references the provided sub-expression.
  ASSERT_GE(node->nsub(), 1);
  ASSERT_NE(node->sub(), nullptr);
  EXPECT_EQ(node->sub()[0], sub.get());
}

// Boundary: null sub-expression. Behavior should be observable (nullptr result).
TEST_F(RegexpQuestTest_340, NullSubReturnsNull_340) {
  auto flags = static_cast<Regexp::ParseFlags>(0);
  Regexp* node = Regexp::Quest(nullptr, flags);
  EXPECT_EQ(node, nullptr);
}

// Flags passthrough: non-zero flags are preserved on the created node.
TEST_F(RegexpQuestTest_340, PreservesNonZeroParseFlags_340) {
  auto flags = static_cast<Regexp::ParseFlags>(0x1234);  // arbitrary non-zero value
  auto sub = MakeLiteral(flags, static_cast<Rune>('a'));
  ASSERT_NE(sub, nullptr);

  Regexp* raw = Regexp::Quest(sub.get(), flags);
  RegexpQuestTest_340::RegexpPtr node(raw);
  ASSERT_NE(node, nullptr);

  EXPECT_EQ(node->op(), kRegexpQuest);
  EXPECT_EQ(node->parse_flags(), flags);
}

// Structural check: resulting node exposes exactly one sub (when observable via the interface).
TEST_F(RegexpQuestTest_340, HasSingleSubWhenCreatedFromSingleSub_340) {
  auto flags = static_cast<Regexp::ParseFlags>(0);
  auto sub = MakeLiteral(flags, static_cast<Rune>('b'));
  ASSERT_NE(sub, nullptr);

  Regexp* raw = Regexp::Quest(sub.get(), flags);
  RegexpQuestTest_340::RegexpPtr node(raw);
  ASSERT_NE(node, nullptr);

  // The interface exposes nsub() and sub(); verify it reports a single child and that child is `sub`.
  EXPECT_EQ(node->nsub(), 1);
  ASSERT_NE(node->sub(), nullptr);
  EXPECT_EQ(node->sub()[0], sub.get());
}
