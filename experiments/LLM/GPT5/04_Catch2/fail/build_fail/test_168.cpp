// File: tests/match_not_of_generic_bang_operator_test.cpp

#include <gtest/gtest.h>
#include <type_traits>
#include <string>

// Include the header under test
#include "catch2/matchers/catch_matchers_templated.hpp"

namespace {

using namespace Catch::Matchers::Detail;

// A minimal external matcher type used as a collaborator in tests.
// It exposes only the public interface the wrapper relies on:
//   - template<typename Arg> bool match(Arg&&) const
//   - std::string describe() const
//
// Behavior (purely for test observability):
//   - matches even integers
//   - describe() returns a fixed string
struct EvenMatcher {
    template <typename Arg>
    bool match(Arg&&) const {
        // For non-integers, return false so behavior is well-defined in tests.
        return false;
    }
    bool match(int v) const { return (v % 2) == 0; }

    std::string describe() const { return "is even"; }
};

// Another simple matcher to ensure generality and avoid overfitting.
struct LengthAtLeastMatcher {
    explicit LengthAtLeastMatcher(std::size_t n) : n_(n) {}

    template <typename Arg>
    bool match(const Arg& a) const {
        using std::size;
        using std::string;
        // Only attempt size-based matching for containers/strings where size() exists
        // If not available, return false.
        // This is purely external to the class under test and stays within the interface.
        return hasSize(a) && getSize(a) >= n_;
    }

    std::string describe() const {
        return "length at least " + std::to_string(n_);
    }

private:
    std::size_t n_;

    template <typename T>
    static auto getSize(const T& t) -> decltype(t.size()) { return t.size(); }

    template <typename T>
    static auto hasSize(const T& t) -> decltype((void)t.size(), true) { return true; }

    static bool hasSize(...) { return false; }
};

} // namespace

// ---------- Tests ----------

// Verifies the *type* of the returned value from operator! is `MatcherT const&`.
TEST(MatchNotOfGeneric_NotOperator_168, ReturnsConstReferenceType_168) {
    EvenMatcher base{};
    MatchNotOfGeneric<EvenMatcher> wrapper(base);

    // The operator! should return a const reference to a MatcherT
    auto& returned = !wrapper;
    static_assert(std::is_same<decltype(returned), EvenMatcher const&>::value,
                  "operator! must return MatcherT const&");

    // A basic runtime assertion so the test isn't compile-time only.
    EXPECT_TRUE(std::is_reference<decltype(returned)>::value);
}

// Ensures the returned matcher reference behaves the same as the original collaborator
// (observable via match() and describe()).
TEST(MatchNotOfGeneric_NotOperator_168, ReturnedMatcherBehavesLikeOriginal_168) {
    EvenMatcher original{};
    MatchNotOfGeneric<EvenMatcher> wrapper(original);

    const EvenMatcher& returned = !wrapper;

    // Behavior checks (observable via the collaborator's public interface)
    EXPECT_TRUE(returned.match(2));
    EXPECT_FALSE(returned.match(3));
    EXPECT_EQ(returned.describe(), original.describe());
}

// Confirm it works when constructed from an rvalue (temporary) collaborator.
TEST(MatchNotOfGeneric_NotOperator_168, WorksWithRvalueCollaborator_168) {
    MatchNotOfGeneric<EvenMatcher> wrapper(EvenMatcher{});
    const EvenMatcher& returned = !wrapper;

    EXPECT_TRUE(returned.match(0));
    EXPECT_TRUE(returned.match(100));
    EXPECT_FALSE(returned.match(101));
    EXPECT_EQ(returned.describe(), std::string("is even"));
}

// Cross-check with a different collaborator type to avoid coupling to a single matcher shape.
TEST(MatchNotOfGeneric_NotOperator_168, WorksWithDifferentMatcherType_168) {
    LengthAtLeastMatcher len3(3);

    MatchNotOfGeneric<LengthAtLeastMatcher> wrapper(len3);
    const LengthAtLeastMatcher& returned = !wrapper;

    // Use observable behavior only
    EXPECT_TRUE(returned.match(std::string("abcd"))); // size 4 >= 3
    EXPECT_TRUE(returned.match(std::string("xyz")));  // size 3 >= 3
    EXPECT_FALSE(returned.match(std::string("hi")));  // size 2 < 3

    EXPECT_EQ(returned.describe(), len3.describe());
}

// Boundary-ish values for collaborator behavior are still valid through the returned reference.
TEST(MatchNotOfGeneric_NotOperator_168, BoundaryValuesAreObservedThroughReturnedMatcher_168) {
    EvenMatcher base{};
    MatchNotOfGeneric<EvenMatcher> wrapper(base);
    const EvenMatcher& returned = !wrapper;

    // Check a few edge-ish integers
    EXPECT_TRUE(returned.match(0));      // even
    EXPECT_FALSE(returned.match(-1));    // odd
    EXPECT_TRUE(returned.match(-2));     // even
    EXPECT_FALSE(returned.match(1));     // odd
}
