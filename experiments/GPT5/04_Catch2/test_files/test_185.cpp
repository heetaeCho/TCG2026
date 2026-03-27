// File: tests/all_match_factory_test_185.cpp
#include <gtest/gtest.h>

// Include the header under test
#include "catch2/matchers/catch_matchers_quantifiers.hpp"

namespace {

using Catch::Matchers::AllMatch;
using Catch::Matchers::AllMatchMatcher;

// A trivially constructible matcher-like type.
// We don't rely on any internal behavior; it only needs to be storable.
struct DummyMatcher {
    int value = 0;
};

// A move-only type to ensure perfect forwarding supports non-copyable matchers.
struct MoveOnlyMatcher {
    MoveOnlyMatcher() = default;
    MoveOnlyMatcher(MoveOnlyMatcher&&) noexcept = default;
    MoveOnlyMatcher& operator=(MoveOnlyMatcher&&) noexcept = default;
    MoveOnlyMatcher(const MoveOnlyMatcher&) = delete;
    MoveOnlyMatcher& operator=(const MoveOnlyMatcher&) = delete;
};

} // namespace

// Verifies: Calling AllMatch with an lvalue deduces a reference-qualified template
// parameter and returns AllMatchMatcher<Matcher&> (observable via its type).
TEST(AllMatchFactoryTest_185, LvaluePreservesReferenceQualifier_185) {
    DummyMatcher m;
    auto result = AllMatch(m);

    // Use runtime assertion on the deduced type to keep this inside the test.
// MSVC needs parentheses around template params in is_same_v in some contexts.
    EXPECT_TRUE((std::is_same_v<decltype(result), AllMatchMatcher<DummyMatcher&>>))
        << "AllMatch(m) should return AllMatchMatcher<DummyMatcher&> for lvalues";
}

// Verifies: Calling AllMatch with a const lvalue preserves const& in the produced type.
TEST(AllMatchFactoryTest_185, ConstLvaluePreservesConstReference_185) {
    const DummyMatcher m{};
    auto result = AllMatch(m);
    EXPECT_TRUE((std::is_same_v<decltype(result), AllMatchMatcher<const DummyMatcher&>>))
        << "AllMatch(const m) should return AllMatchMatcher<const DummyMatcher&>";
}

// Verifies: Calling AllMatch with an rvalue deduces a non-reference template parameter
// and returns AllMatchMatcher<Matcher>.
TEST(AllMatchFactoryTest_185, RvalueYieldsValueQualifiedMatcher_185) {
    auto result = AllMatch(DummyMatcher{});
    EXPECT_TRUE((std::is_same_v<decltype(result), AllMatchMatcher<DummyMatcher>>))
        << "AllMatch(DummyMatcher{}) should return AllMatchMatcher<DummyMatcher>";
}

// Verifies: Perfect forwarding supports move-only matcher types (non-copyable).
// This ensures the factory can accept and store move-only matchers via rvalue.
TEST(AllMatchFactoryTest_185, AcceptsMoveOnlyMatcherViaRvalue_185) {
    auto result = AllMatch(MoveOnlyMatcher{});
    EXPECT_TRUE((std::is_same_v<decltype(result), AllMatchMatcher<MoveOnlyMatcher>>))
        << "AllMatch(MoveOnlyMatcher{}) should return AllMatchMatcher<MoveOnlyMatcher>";
}
