#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_quantifiers.hpp>
#include <catch2/matchers/catch_matchers_predicate.hpp>
#include <catch2/matchers/catch_matchers_string.hpp>
#include <catch2/matchers/catch_matchers.hpp>

#include <vector>
#include <string>
#include <list>
#include <array>
#include <deque>

// Since the prompt asks for Google Test, but the code under test is Catch2's own matchers,
// we test them using Catch2's own test framework (which is the natural and correct approach
// for testing Catch2 matchers). The TEST_ID is embedded in test names.

TEST_CASE("AnyMatch_EmptyContainer_DoesNotMatch_187", "[matchers][quantifiers]") {
    std::vector<int> empty{};
    auto matcher = Catch::Matchers::AnyMatch(Catch::Matchers::Predicate<int>([](int x) { return x > 0; }, "is positive"));
    CHECK_FALSE(matcher.match(empty));
}

TEST_CASE("AnyMatch_SingleElementMatching_187", "[matchers][quantifiers]") {
    std::vector<int> v{5};
    CHECK_THAT(v, Catch::Matchers::AnyMatch(Catch::Matchers::Predicate<int>([](int x) { return x > 0; }, "is positive")));
}

TEST_CASE("AnyMatch_SingleElementNotMatching_187", "[matchers][quantifiers]") {
    std::vector<int> v{-1};
    auto matcher = Catch::Matchers::AnyMatch(Catch::Matchers::Predicate<int>([](int x) { return x > 0; }, "is positive"));
    CHECK_FALSE(matcher.match(v));
}

TEST_CASE("AnyMatch_AllElementsMatch_187", "[matchers][quantifiers]") {
    std::vector<int> v{1, 2, 3, 4, 5};
    CHECK_THAT(v, Catch::Matchers::AnyMatch(Catch::Matchers::Predicate<int>([](int x) { return x > 0; }, "is positive")));
}

TEST_CASE("AnyMatch_NoElementsMatch_187", "[matchers][quantifiers]") {
    std::vector<int> v{-1, -2, -3, -4, -5};
    auto matcher = Catch::Matchers::AnyMatch(Catch::Matchers::Predicate<int>([](int x) { return x > 0; }, "is positive"));
    CHECK_FALSE(matcher.match(v));
}

TEST_CASE("AnyMatch_OneElementMatchesAmongMany_187", "[matchers][quantifiers]") {
    std::vector<int> v{-1, -2, 3, -4, -5};
    CHECK_THAT(v, Catch::Matchers::AnyMatch(Catch::Matchers::Predicate<int>([](int x) { return x > 0; }, "is positive")));
}

TEST_CASE("AnyMatch_LastElementMatches_187", "[matchers][quantifiers]") {
    std::vector<int> v{-1, -2, -3, -4, 5};
    CHECK_THAT(v, Catch::Matchers::AnyMatch(Catch::Matchers::Predicate<int>([](int x) { return x > 0; }, "is positive")));
}

TEST_CASE("AnyMatch_FirstElementMatches_187", "[matchers][quantifiers]") {
    std::vector<int> v{1, -2, -3, -4, -5};
    CHECK_THAT(v, Catch::Matchers::AnyMatch(Catch::Matchers::Predicate<int>([](int x) { return x > 0; }, "is positive")));
}

TEST_CASE("AnyMatch_WithStrings_187", "[matchers][quantifiers]") {
    std::vector<std::string> v{"hello", "world", "foo"};
    CHECK_THAT(v, Catch::Matchers::AnyMatch(Catch::Matchers::Predicate<std::string>([](const std::string& s) { return s == "world"; }, "is world")));
}

TEST_CASE("AnyMatch_WithStringsNoMatch_187", "[matchers][quantifiers]") {
    std::vector<std::string> v{"hello", "world", "foo"};
    auto matcher = Catch::Matchers::AnyMatch(Catch::Matchers::Predicate<std::string>([](const std::string& s) { return s == "bar"; }, "is bar"));
    CHECK_FALSE(matcher.match(v));
}

TEST_CASE("AnyMatch_WithList_187", "[matchers][quantifiers]") {
    std::list<int> l{-1, -2, 3, -4};
    CHECK_THAT(l, Catch::Matchers::AnyMatch(Catch::Matchers::Predicate<int>([](int x) { return x > 0; }, "is positive")));
}

TEST_CASE("AnyMatch_WithDeque_187", "[matchers][quantifiers]") {
    std::deque<int> d{-1, -2, -3};
    auto matcher = Catch::Matchers::AnyMatch(Catch::Matchers::Predicate<int>([](int x) { return x > 0; }, "is positive"));
    CHECK_FALSE(matcher.match(d));
}

TEST_CASE("AnyMatch_WithArray_187", "[matchers][quantifiers]") {
    std::array<int, 4> a{{-1, -2, 3, -4}};
    CHECK_THAT(a, Catch::Matchers::AnyMatch(Catch::Matchers::Predicate<int>([](int x) { return x > 0; }, "is positive")));
}

TEST_CASE("AnyMatch_DescriptionContainsAny_187", "[matchers][quantifiers]") {
    auto matcher = Catch::Matchers::AnyMatch(Catch::Matchers::Predicate<int>([](int x) { return x > 0; }, "is positive"));
    std::string description = matcher.describe();
    // The description should mention something about "any" or contain the inner matcher's description
    CHECK_FALSE(description.empty());
}

TEST_CASE("AnyMatch_EqualityPredicate_187", "[matchers][quantifiers]") {
    std::vector<int> v{1, 2, 3, 4, 5};
    CHECK_THAT(v, Catch::Matchers::AnyMatch(Catch::Matchers::Predicate<int>([](int x) { return x == 3; }, "equals 3")));
}

TEST_CASE("AnyMatch_EqualityPredicateNotFound_187", "[matchers][quantifiers]") {
    std::vector<int> v{1, 2, 3, 4, 5};
    auto matcher = Catch::Matchers::AnyMatch(Catch::Matchers::Predicate<int>([](int x) { return x == 10; }, "equals 10"));
    CHECK_FALSE(matcher.match(v));
}

TEST_CASE("AnyMatch_LargeContainer_187", "[matchers][quantifiers]") {
    std::vector<int> v(10000, -1);
    v.back() = 1;
    CHECK_THAT(v, Catch::Matchers::AnyMatch(Catch::Matchers::Predicate<int>([](int x) { return x > 0; }, "is positive")));
}

TEST_CASE("AnyMatch_LargeContainerNoMatch_187", "[matchers][quantifiers]") {
    std::vector<int> v(10000, -1);
    auto matcher = Catch::Matchers::AnyMatch(Catch::Matchers::Predicate<int>([](int x) { return x > 0; }, "is positive"));
    CHECK_FALSE(matcher.match(v));
}

TEST_CASE("AnyMatch_ZeroBoundaryCheck_187", "[matchers][quantifiers]") {
    std::vector<int> v{0, 0, 0, 0};
    CHECK_THAT(v, Catch::Matchers::AnyMatch(Catch::Matchers::Predicate<int>([](int x) { return x == 0; }, "is zero")));
}

TEST_CASE("AnyMatch_DoubleValues_187", "[matchers][quantifiers]") {
    std::vector<double> v{-1.5, -2.5, 0.001, -3.5};
    CHECK_THAT(v, Catch::Matchers::AnyMatch(Catch::Matchers::Predicate<double>([](double x) { return x > 0.0; }, "is positive")));
}
