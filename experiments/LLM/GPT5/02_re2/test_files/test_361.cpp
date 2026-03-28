// File: regexp_named_captures_test_361.cc

#include <gtest/gtest.h>
#include <map>
#include <string>
#include "re2/regexp.h"

using re2::Regexp;

namespace {

// Helper: parse a pattern into a Regexp*. We pass 0 flags and nullptr status.
static Regexp* ParseOrNull(const std::string& pattern) {
  // ParseFlags appears as a nested type in the provided header.
  return Regexp::Parse(pattern, static_cast<Regexp::ParseFlags>(0), nullptr);
}

// Fixture to ensure consistent cleanup via Decref().
class RegexpNamedCapturesTest_361 : public ::testing::Test {
protected:
  static void DecrefIfNonNull(Regexp* re) {
    if (re) re->Decref();
  }
};

}  // namespace

// Normal operation: pattern without named groups.
// Observable behavior: returns nullptr OR an empty map.
TEST_F(RegexpNamedCapturesTest_361, NoNamedGroups_ReturnsNullOrEmpty_361) {
  Regexp* re = ParseOrNull("abc");
  ASSERT_NE(re, nullptr) << "Parse failed for a simple literal pattern.";
  std::map<std::string, int>* m = re->NamedCaptures();

  if (m == nullptr) {
    SUCCEED() << "No named groups -> nullptr is acceptable.";
  } else {
    EXPECT_TRUE(m->empty()) << "No named groups -> map should be empty if non-null.";
    delete m;
  }

  DecrefIfNonNull(re);
}

// Normal operation: single named group.
// Observable behavior: returns a non-null map containing the given name
// mapped to a positive (>=1) capture index.
TEST_F(RegexpNamedCapturesTest_361, SingleNamedGroup_ContainsNameWithPositiveIndex_361) {
  // RE2 accepts (?P<name>...) syntax for named captures.
  Regexp* re = ParseOrNull("(?P<foo>a)");
  ASSERT_NE(re, nullptr) << "Parse failed for a pattern with a named capture.";

  std::map<std::string, int>* m = re->NamedCaptures();
  ASSERT_NE(m, nullptr) << "Expected a non-null map for a pattern with a named capture.";

  auto it = m->find("foo");
  ASSERT_NE(it, m->end()) << "Expected to find key 'foo' in named captures.";
  EXPECT_GE(it->second, 1) << "Capture index should be positive (>= 1).";

  delete m;
  DecrefIfNonNull(re);
}

// Normal operation: multiple named groups.
// Observable behavior: returns a non-null map containing both names.
// Their capture indices should exist and need not be equal.
TEST_F(RegexpNamedCapturesTest_361, MultipleNamedGroups_ContainsAllNames_361) {
  Regexp* re = ParseOrNull("(?P<x>a)(?P<y>b)");
  ASSERT_NE(re, nullptr) << "Parse failed for a pattern with multiple named captures.";

  std::map<std::string, int>* m = re->NamedCaptures();
  ASSERT_NE(m, nullptr) << "Expected a non-null map for multiple named captures.";

  auto ix = m->find("x");
  auto iy = m->find("y");
  ASSERT_NE(ix, m->end()) << "Missing name 'x'.";
  ASSERT_NE(iy, m->end()) << "Missing name 'y'.";
  EXPECT_GE(ix->second, 1);
  EXPECT_GE(iy->second, 1);
  // Indices need not be specific, but commonly they differ.
  // We don't require inequality here to avoid assuming internal numbering.

  delete m;
  DecrefIfNonNull(re);
}

// Consistency / idempotence: repeated calls should be safe and yield
// consistent observable results (same keys and associated indices).
TEST_F(RegexpNamedCapturesTest_361, RepeatedCalls_ReturnConsistentMappings_361) {
  Regexp* re = ParseOrNull("(?P<a>one)(?P<b>two)");
  ASSERT_NE(re, nullptr) << "Parse failed for a pattern with two named captures.";

  std::unique_ptr<std::map<std::string, int>> first(re->NamedCaptures());
  std::unique_ptr<std::map<std::string, int>> second(re->NamedCaptures());

  ASSERT_NE(first, nullptr);
  ASSERT_NE(second, nullptr);

  EXPECT_EQ(first->size(), second->size()) << "Named capture map sizes should match across calls.";

  for (const auto& kv : *first) {
    auto it = second->find(kv.first);
    ASSERT_NE(it, second->end()) << "Missing key '" << kv.first << "' on second call.";
    EXPECT_EQ(kv.second, it->second) << "Capture index for '" << kv.first << "' should match across calls.";
  }

  DecrefIfNonNull(re);
}

