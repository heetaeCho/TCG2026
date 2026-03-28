#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_predicate.hpp>
#include <catch2/matchers/catch_matchers.hpp>
#include <string>
#include <functional>

// Using Catch2's own test framework to test its matchers

TEST_CASE("PredicateMatcher_BasicTrueMatch_215", "[matchers][predicate]") {
    auto matcher = Catch::Matchers::Predicate<int>([](int x) { return x > 0; }, "is positive");
    CHECK_THAT(1, matcher);
    CHECK_THAT(42, matcher);
    CHECK_THAT(100, matcher);
}

TEST_CASE("PredicateMatcher_BasicFalseMatch_215", "[matchers][predicate]") {
    auto matcher = Catch::Matchers::Predicate<int>([](int x) { return x > 0; }, "is positive");
    CHECK_THAT(-1, !matcher);
    CHECK_THAT(0, !matcher);
    CHECK_THAT(-100, !matcher);
}

TEST_CASE("PredicateMatcher_WithStringType_215", "[matchers][predicate]") {
    auto matcher = Catch::Matchers::Predicate<std::string>(
        [](const std::string& s) { return s.empty(); }, "is empty string");
    CHECK_THAT(std::string(""), matcher);
    CHECK_THAT(std::string("hello"), !matcher);
}

TEST_CASE("PredicateMatcher_EmptyDescription_215", "[matchers][predicate]") {
    auto matcher = Catch::Matchers::Predicate<int>([](int x) { return x == 0; });
    CHECK_THAT(0, matcher);
    CHECK_THAT(1, !matcher);
}

TEST_CASE("PredicateMatcher_WithCustomDescription_215", "[matchers][predicate]") {
    std::string desc = "is even number";
    auto matcher = Catch::Matchers::Predicate<int>([](int x) { return x % 2 == 0; }, desc);
    CHECK_THAT(2, matcher);
    CHECK_THAT(4, matcher);
    CHECK_THAT(3, !matcher);
}

TEST_CASE("PredicateMatcher_BoundaryZero_215", "[matchers][predicate]") {
    auto matcher = Catch::Matchers::Predicate<int>([](int x) { return x >= 0; }, "is non-negative");
    CHECK_THAT(0, matcher);
    CHECK_THAT(-1, !matcher);
    CHECK_THAT(1, matcher);
}

TEST_CASE("PredicateMatcher_WithDoubleType_215", "[matchers][predicate]") {
    auto matcher = Catch::Matchers::Predicate<double>(
        [](double x) { return x > 0.0 && x < 1.0; }, "is between 0 and 1 exclusive");
    CHECK_THAT(0.5, matcher);
    CHECK_THAT(0.0, !matcher);
    CHECK_THAT(1.0, !matcher);
    CHECK_THAT(-0.1, !matcher);
}

TEST_CASE("PredicateMatcher_WithFunctionObject_215", "[matchers][predicate]") {
    struct IsPositive {
        bool operator()(int x) const { return x > 0; }
    };
    auto matcher = Catch::Matchers::Predicate<int>(IsPositive{}, "is positive via functor");
    CHECK_THAT(5, matcher);
    CHECK_THAT(-5, !matcher);
}

TEST_CASE("PredicateMatcher_AlwaysTrue_215", "[matchers][predicate]") {
    auto matcher = Catch::Matchers::Predicate<int>([](int) { return true; }, "always true");
    CHECK_THAT(0, matcher);
    CHECK_THAT(-999, matcher);
    CHECK_THAT(999, matcher);
}

TEST_CASE("PredicateMatcher_AlwaysFalse_215", "[matchers][predicate]") {
    auto matcher = Catch::Matchers::Predicate<int>([](int) { return false; }, "always false");
    CHECK_THAT(0, !matcher);
    CHECK_THAT(42, !matcher);
}

TEST_CASE("PredicateMatcher_WithConstReference_215", "[matchers][predicate]") {
    auto matcher = Catch::Matchers::Predicate<std::string>(
        [](const std::string& s) { return s.size() > 3; }, "has length > 3");
    CHECK_THAT(std::string("abcd"), matcher);
    CHECK_THAT(std::string("abc"), !matcher);
    CHECK_THAT(std::string(""), !matcher);
}

TEST_CASE("PredicateMatcher_WithStdFunction_215", "[matchers][predicate]") {
    std::function<bool(int)> fn = [](int x) { return x % 3 == 0; };
    auto matcher = Catch::Matchers::Predicate<int>(std::move(fn), "divisible by 3");
    CHECK_THAT(9, matcher);
    CHECK_THAT(10, !matcher);
    CHECK_THAT(0, matcher);
}

TEST_CASE("PredicateMatcher_WithBoolType_215", "[matchers][predicate]") {
    auto matcher = Catch::Matchers::Predicate<bool>([](bool b) { return b; }, "is true");
    CHECK_THAT(true, matcher);
    CHECK_THAT(false, !matcher);
}

TEST_CASE("PredicateMatcher_CapturingLambda_215", "[matchers][predicate]") {
    int threshold = 10;
    auto matcher = Catch::Matchers::Predicate<int>(
        [threshold](int x) { return x > threshold; }, "greater than threshold");
    CHECK_THAT(11, matcher);
    CHECK_THAT(10, !matcher);
    CHECK_THAT(9, !matcher);
}
