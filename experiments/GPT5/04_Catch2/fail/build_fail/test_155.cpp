// File: describe_multi_matcher_155_tests.cpp

#include <gtest/gtest.h>
#include <array>
#include <string>
#include <vector>
#include <utility>
#include <type_traits>
#include <cstddef>
#include <utility>
#include <initializer_list>

// ---- Minimal external stubs (safe test doubles) ----
// We only need a pass-through StringRef type to satisfy the signature.
// We do NOT depend on or assert anything about its internals.
namespace Catch {
class StringRef {
public:
  StringRef(const char* /*unused*/) {}
};
} // namespace Catch

// Forward declare the namespace path we will test + include the header under test.
#include "Catch2/src/catch2/matchers/catch_matchers_templated.hpp"

// ---- Test-only spy for the *other* overload dependency ----
// We mock the collaborator that the template forwards to:
//   describe_multi_matcher(StringRef, const std::string*, const std::string*)
// This lets us observe the strings produced by toString() without
// re-implementing the class-under-test logic.
namespace {
struct SpyStorage {
  std::vector<std::string> last_descriptions;
  int call_count = 0;

  void reset() {
    last_descriptions.clear();
    call_count = 0;
  }
};
SpyStorage g_spy;
} // namespace

namespace Catch { namespace Matchers { namespace Detail {

// This is our test double for the dependent overload.
// It simply records the range of strings it receives and returns a sentinel.
static std::string describe_multi_matcher(
    Catch::StringRef /*combine_ignored_for_blackbox*/,
    std::string const* begin,
    std::string const* end) {
  ++g_spy.call_count;
  g_spy.last_descriptions.assign(begin, end);
  return std::string{"__TEST_SENTINEL__"};
}

}}} // namespace Catch::Matchers::Detail

// ---- Lightweight matcher stand-ins with observable toString() side-effects ----
namespace test_helpers {
struct MatcherA {
  static int toString_calls;
  std::string name;
  explicit MatcherA(std::string n) : name(std::move(n)) {}
  std::string toString() const {
    ++toString_calls;
    return name;
  }
};
int MatcherA::toString_calls = 0;

struct MatcherB {
  static int toString_calls;
  std::string name;
  explicit MatcherB(std::string n) : name(std::move(n)) {}
  std::string toString() const {
    ++toString_calls;
    return name;
  }
};
int MatcherB::toString_calls = 0;

struct MatcherC {
  static int toString_calls;
  std::string name;
  explicit MatcherC(std::string n) : name(std::move(n)) {}
  std::string toString() const {
    ++toString_calls;
    return name;
  }
};
int MatcherC::toString_calls = 0;

inline void ResetCounters() {
  MatcherA::toString_calls = 0;
  MatcherB::toString_calls = 0;
  MatcherC::toString_calls = 0;
  g_spy.reset();
}
} // namespace test_helpers

using Catch::Matchers::Detail::describe_multi_matcher;

// ------------------------- Tests -------------------------

// Normal operation with two matchers: verifies that toString() results are forwarded
// to the dependent overload in the correct order, exactly once each.
TEST(DescribeMultiMatcher_155, ForwardsTwoMatcherDescriptionsInOrder_155) {
  using namespace test_helpers;
  ResetCounters();

  MatcherA a{"alpha"};
  MatcherB b{"beta"};

  std::array<void const*, 2> ptrs{{ static_cast<void const*>(&a),
                                    static_cast<void const*>(&b) }};

  // Call the template under test (black box)
  std::string out = Catch::Matchers::Detail::describe_multi_matcher<MatcherA, MatcherB>(
      Catch::StringRef("&&"), ptrs, std::index_sequence<0,1>{});

  // Returned value is produced by our spy; we only assert it is exactly that sentinel.
  EXPECT_EQ(out, "__TEST_SENTINEL__");

  // Observable behavior: dependent overload received the two strings in order.
  ASSERT_EQ(g_spy.call_count, 1);
  ASSERT_EQ(g_spy.last_descriptions.size(), 2u);
  EXPECT_EQ(g_spy.last_descriptions[0], "alpha");
  EXPECT_EQ(g_spy.last_descriptions[1], "beta");

  // Each matcher had its toString() called exactly once.
  EXPECT_EQ(MatcherA::toString_calls, 1);
  EXPECT_EQ(MatcherB::toString_calls, 1);
  EXPECT_EQ(MatcherC::toString_calls, 0);
}

// Boundary: single matcher. Ensures single element path works and is forwarded correctly.
TEST(DescribeMultiMatcher_155, ForwardsSingleMatcherDescription_155) {
  using namespace test_helpers;
  ResetCounters();

  MatcherC c{"solo"};
  std::array<void const*, 1> ptrs{{ static_cast<void const*>(&c) }};

  std::string out = Catch::Matchers::Detail::describe_multi_matcher<MatcherC>(
      Catch::StringRef("||"), ptrs, std::index_sequence<0>{});

  EXPECT_EQ(out, "__TEST_SENTINEL__");
  ASSERT_EQ(g_spy.call_count, 1);
  ASSERT_EQ(g_spy.last_descriptions.size(), 1u);
  EXPECT_EQ(g_spy.last_descriptions[0], "solo");
  EXPECT_EQ(MatcherC::toString_calls, 1);
  EXPECT_EQ(MatcherA::toString_calls, 0);
  EXPECT_EQ(MatcherB::toString_calls, 0);
}

// Boundary: zero matchers. Ensures the function can be instantiated with an empty pack
// and forwards an empty range to the dependent overload.
TEST(DescribeMultiMatcher_155, HandlesZeroMatchers_EmptyForward_155) {
  using namespace test_helpers;
  ResetCounters();

  std::array<void const*, 0> ptrs{};

  // Empty template parameter pack and empty index sequence
  std::string out =
      Catch::Matchers::Detail::describe_multi_matcher<>(
          Catch::StringRef("irrelevant"), ptrs, std::index_sequence<>{});

  EXPECT_EQ(out, "__TEST_SENTINEL__");
  ASSERT_EQ(g_spy.call_count, 1);
  ASSERT_TRUE(g_spy.last_descriptions.empty());

  // No toString() should have been called.
  EXPECT_EQ(MatcherA::toString_calls, 0);
  EXPECT_EQ(MatcherB::toString_calls, 0);
  EXPECT_EQ(MatcherC::toString_calls, 0);
}

// Mixed types and three matchers: verifies order and that each specific type is used
// to obtain its own description (no cross-casting / swapped order).
TEST(DescribeMultiMatcher_155, ForwardsThreeMixedMatchersPreservingOrder_155) {
  using namespace test_helpers;
  ResetCounters();

  MatcherB b{"bee"};
  MatcherA a{"aye"};
  MatcherC c{"see"};

  // IMPORTANT: Pointers must match the template parameter order by index
  std::array<void const*, 3> ptrs{{ static_cast<void const*>(&b),
                                    static_cast<void const*>(&a),
                                    static_cast<void const*>(&c) }};

  std::string out =
      Catch::Matchers::Detail::describe_multi_matcher<MatcherB, MatcherA, MatcherC>(
          Catch::StringRef("combine"), ptrs, std::index_sequence<0,1,2>{});

  EXPECT_EQ(out, "__TEST_SENTINEL__");
  ASSERT_EQ(g_spy.call_count, 1);
  ASSERT_EQ(g_spy.last_descriptions.size(), 3u);
  EXPECT_EQ(g_spy.last_descriptions[0], "bee");
  EXPECT_EQ(g_spy.last_descriptions[1], "aye");
  EXPECT_EQ(g_spy.last_descriptions[2], "see");

  EXPECT_EQ(MatcherA::toString_calls, 1);
  EXPECT_EQ(MatcherB::toString_calls, 1);
  EXPECT_EQ(MatcherC::toString_calls, 1);
}
