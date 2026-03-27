// File: tests/range_equals_matcher_961_tests.cpp

#include <gtest/gtest.h>
#include <list>
#include <deque>
#include <vector>
#include <string>
#include <cctype>
#include <memory>

// Include the provided Catch2 amalgamated header (interface under test)
#include "Catch2/extras/catch_amalgamated.hpp"

namespace {

using Catch::Matchers::RangeEquals;

// Simple helper to call .match(...) on the matcher and assert expected result
template <typename Matcher, typename Range>
void ExpectMatch(const Matcher& m, const Range& r, bool expected) {
    EXPECT_EQ(m.match(r), expected);
}

// Case-insensitive string equality predicate
struct CaseInsensitiveEq {
    bool operator()(const std::string& a, const std::string& b) const {
        if (a.size() != b.size()) return false;
        for (size_t i = 0; i < a.size(); ++i) {
            unsigned char ca = static_cast<unsigned char>(a[i]);
            unsigned char cb = static_cast<unsigned char>(b[i]);
            if (std::tolower(ca) != std::tolower(cb)) return false;
        }
        return true;
    }
};

// Move-only predicate that counts the number of times it's invoked, via shared state.
// This verifies that a user-supplied predicate is actually used (external interaction).
struct MoveOnlyCountingEq {
    std::shared_ptr<int> counter;
    explicit MoveOnlyCountingEq(std::shared_ptr<int> c) : counter(std::move(c)) {}
    MoveOnlyCountingEq(const MoveOnlyCountingEq&) = delete;
    MoveOnlyCountingEq& operator=(const MoveOnlyCountingEq&) = delete;
    MoveOnlyCountingEq(MoveOnlyCountingEq&&) = default;
    MoveOnlyCountingEq& operator=(MoveOnlyCountingEq&&) = default;

    template <typename L, typename R>
    bool operator()(const L& l, const R& r) {
        ++(*counter);
        return l == r;
    }
};

class RangeEqualsMatcherTest_961 : public ::testing::Test {};

} // namespace

// ---------- Normal operation ----------

TEST_F(RangeEqualsMatcherTest_961, MatchesEqualSequences_IntVector_961) {
    const std::vector<int> actual{1, 2, 3, 4};
    auto m = RangeEquals<int>({1, 2, 3, 4}); // default std::equal_to
    ExpectMatch(m, actual, true);
}

TEST_F(RangeEqualsMatcherTest_961, WorksAcrossDifferentContainers_ListVsInit_961) {
    const std::list<int> actual{5, 6, 7};
    auto m = RangeEquals<int>({5, 6, 7});
    ExpectMatch(m, actual, true);
}

// ---------- Boundary conditions ----------

TEST_F(RangeEqualsMatcherTest_961, EmptyRangesMatch_961) {
    const std::vector<int> actual{};
    auto m = RangeEquals<int>({});
    ExpectMatch(m, actual, true);
}

TEST_F(RangeEqualsMatcherTest_961, MismatchDifferentSizes_961) {
    const std::deque<int> actual{1, 2, 3};
    auto m = RangeEquals<int>({1, 2, 3, 4});
    ExpectMatch(m, actual, false);
}

// ---------- Exceptional/negative observable cases ----------

TEST_F(RangeEqualsMatcherTest_961, FirstElementDiffers_Fails_961) {
    const std::vector<int> actual{9, 2, 3};
    auto m = RangeEquals<int>({1, 2, 3});
    ExpectMatch(m, actual, false);
}

TEST_F(RangeEqualsMatcherTest_961, MiddleElementDiffers_Fails_961) {
    const std::vector<int> actual{1, 99, 3};
    auto m = RangeEquals<int>({1, 2, 3});
    ExpectMatch(m, actual, false);
}

// ---------- Custom predicate (external interaction) ----------

TEST_F(RangeEqualsMatcherTest_961, CustomPredicate_CaseInsensitiveStrings_961) {
    const std::vector<std::string> actual{"Hello", "WORLD"};
    auto m = RangeEquals<std::string>({"hello", "world"}, CaseInsensitiveEq{});
    ExpectMatch(m, actual, true);
}

TEST_F(RangeEqualsMatcherTest_961, CustomPredicate_CaseInsensitive_FailsWhenDifferent_961) {
    const std::vector<std::string> actual{"Hello", "WORLD!"}; // punctuation difference
    auto m = RangeEquals<std::string>({"hello", "world"}, CaseInsensitiveEq{});
    ExpectMatch(m, actual, false);
}

// ---------- Move-only predicate is accepted and invoked ----------

TEST_F(RangeEqualsMatcherTest_961, MoveOnlyPredicate_IsUsedAndCountsInvocations_961) {
    auto callCount = std::make_shared<int>(0);
    MoveOnlyCountingEq pred{callCount};   // move-only predicate
    const std::vector<int> actual{10, 20, 30};

    // Pass move-only predicate via rvalue to exercise forwarding
    auto m = RangeEquals<int>({10, 20, 30}, std::move(pred));

    // Should match
    ExpectMatch(m, actual, true);

    // The predicate should have been called at least once (exact call count is an internal detail).
    EXPECT_GT(*callCount, 0);
}

// ---------- Heterogeneous containers (same element type), still match ----------

TEST_F(RangeEqualsMatcherTest_961, DequeMatchesInitList_961) {
    const std::deque<int> actual{42, 43};
    auto m = RangeEquals<int>({42, 43});
    ExpectMatch(m, actual, true);
}
