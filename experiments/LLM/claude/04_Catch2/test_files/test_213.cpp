#include <gtest/gtest.h>
#include <string>
#include <functional>

// Since we're testing against the Catch2 PredicateMatcher, we need to recreate
// enough of the infrastructure to test it. Based on the known dependencies,
// we'll include the actual header or recreate the minimal interface.

// Minimal recreation of Catch2 infrastructure needed for testing
namespace Catch {
    namespace Detail {
        inline std::string finalizeDescription(std::string const& desc) {
            if (desc.empty()) {
                return "matches undescribed predicate";
            }
            return desc;
        }
    }

    // Forward declaration macro equivalent
    #ifndef CATCH_FORWARD
    #define CATCH_FORWARD(x) std::forward<decltype(x)>(x)
    #endif

    namespace Matchers {
        template <typename T>
        class MatcherBase {
        public:
            virtual ~MatcherBase() = default;
            virtual bool match(T const& item) const = 0;
            virtual std::string describe() const = 0;
        };

        template <typename T, typename Predicate>
        class PredicateMatcher : public MatcherBase<T> {
        private:
            Predicate m_predicate;
            std::string m_description;
        public:
            PredicateMatcher(Predicate&& elem, std::string const& descr)
                : m_predicate(CATCH_FORWARD(elem)),
                  m_description(Detail::finalizeDescription(descr)) {}

            bool match(T const& item) const override {
                return m_predicate(item);
            }

            std::string describe() const override {
                return m_description;
            }
        };
    }
}

// Helper to create PredicateMatcher easily
template <typename T, typename Predicate>
Catch::Matchers::PredicateMatcher<T, Predicate> makePredMatcher(Predicate&& pred, std::string const& desc = "") {
    return Catch::Matchers::PredicateMatcher<T, Predicate>(std::forward<Predicate>(pred), desc);
}

// ============================================================
// Test Fixture
// ============================================================
class PredicateMatcherTest_213 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// ============================================================
// Normal operation tests
// ============================================================

TEST_F(PredicateMatcherTest_213, MatchReturnsTrueWhenPredicateReturnsTrue_213) {
    auto matcher = makePredMatcher<int>([](int const& x) { return x > 0; }, "is positive");
    EXPECT_TRUE(matcher.match(5));
}

TEST_F(PredicateMatcherTest_213, MatchReturnsFalseWhenPredicateReturnsFalse_213) {
    auto matcher = makePredMatcher<int>([](int const& x) { return x > 0; }, "is positive");
    EXPECT_FALSE(matcher.match(-3));
}

TEST_F(PredicateMatcherTest_213, MatchWorksWithStringType_213) {
    auto matcher = makePredMatcher<std::string>(
        [](std::string const& s) { return s.size() > 3; },
        "has length > 3"
    );
    EXPECT_TRUE(matcher.match("hello"));
    EXPECT_FALSE(matcher.match("hi"));
}

TEST_F(PredicateMatcherTest_213, DescribeReturnsProvidedDescription_213) {
    auto matcher = makePredMatcher<int>([](int const&) { return true; }, "always true");
    EXPECT_EQ(matcher.describe(), "always true");
}

TEST_F(PredicateMatcherTest_213, MatchWithEqualityPredicate_213) {
    auto matcher = makePredMatcher<int>([](int const& x) { return x == 42; }, "equals 42");
    EXPECT_TRUE(matcher.match(42));
    EXPECT_FALSE(matcher.match(43));
}

TEST_F(PredicateMatcherTest_213, MatchWithDoublePredicate_213) {
    auto matcher = makePredMatcher<double>(
        [](double const& x) { return x >= 0.0 && x <= 1.0; },
        "is in [0, 1]"
    );
    EXPECT_TRUE(matcher.match(0.5));
    EXPECT_FALSE(matcher.match(1.5));
    EXPECT_TRUE(matcher.match(0.0));
    EXPECT_TRUE(matcher.match(1.0));
}

// ============================================================
// Boundary condition tests
// ============================================================

TEST_F(PredicateMatcherTest_213, MatchWithAlwaysTruePredicate_213) {
    auto matcher = makePredMatcher<int>([](int const&) { return true; }, "always true");
    EXPECT_TRUE(matcher.match(0));
    EXPECT_TRUE(matcher.match(-1));
    EXPECT_TRUE(matcher.match(INT_MAX));
    EXPECT_TRUE(matcher.match(INT_MIN));
}

TEST_F(PredicateMatcherTest_213, MatchWithAlwaysFalsePredicate_213) {
    auto matcher = makePredMatcher<int>([](int const&) { return false; }, "always false");
    EXPECT_FALSE(matcher.match(0));
    EXPECT_FALSE(matcher.match(1));
    EXPECT_FALSE(matcher.match(-1));
}

TEST_F(PredicateMatcherTest_213, DescribeWithEmptyDescription_213) {
    auto matcher = makePredMatcher<int>([](int const&) { return true; }, "");
    // When description is empty, finalizeDescription should provide a default
    std::string desc = matcher.describe();
    EXPECT_FALSE(desc.empty());
    EXPECT_EQ(desc, "matches undescribed predicate");
}

TEST_F(PredicateMatcherTest_213, MatchWithEmptyString_213) {
    auto matcher = makePredMatcher<std::string>(
        [](std::string const& s) { return s.empty(); },
        "is empty"
    );
    EXPECT_TRUE(matcher.match(""));
    EXPECT_FALSE(matcher.match("a"));
}

TEST_F(PredicateMatcherTest_213, MatchAtIntegerBoundaries_213) {
    auto matcher = makePredMatcher<int>(
        [](int const& x) { return x >= 0; },
        "is non-negative"
    );
    EXPECT_TRUE(matcher.match(0));
    EXPECT_TRUE(matcher.match(INT_MAX));
    EXPECT_FALSE(matcher.match(-1));
    EXPECT_FALSE(matcher.match(INT_MIN));
}

// ============================================================
// Tests with complex types
// ============================================================

TEST_F(PredicateMatcherTest_213, MatchWithVectorType_213) {
    auto matcher = makePredMatcher<std::vector<int>>(
        [](std::vector<int> const& v) { return v.size() == 3; },
        "has 3 elements"
    );
    EXPECT_TRUE(matcher.match({1, 2, 3}));
    EXPECT_FALSE(matcher.match({1, 2}));
    EXPECT_FALSE(matcher.match({}));
}

TEST_F(PredicateMatcherTest_213, MatchWithCustomStruct_213) {
    struct Point {
        int x, y;
    };
    auto matcher = makePredMatcher<Point>(
        [](Point const& p) { return p.x == 0 && p.y == 0; },
        "is origin"
    );
    EXPECT_TRUE(matcher.match(Point{0, 0}));
    EXPECT_FALSE(matcher.match(Point{1, 0}));
    EXPECT_FALSE(matcher.match(Point{0, 1}));
}

// ============================================================
// Tests verifying predicate is actually called with correct argument
// ============================================================

TEST_F(PredicateMatcherTest_213, PredicateReceivesCorrectArgument_213) {
    int capturedValue = 0;
    auto matcher = makePredMatcher<int>(
        [&capturedValue](int const& x) {
            capturedValue = x;
            return true;
        },
        "captures value"
    );
    matcher.match(42);
    EXPECT_EQ(capturedValue, 42);

    matcher.match(99);
    EXPECT_EQ(capturedValue, 99);
}

TEST_F(PredicateMatcherTest_213, PredicateCalledOnEachMatch_213) {
    int callCount = 0;
    auto matcher = makePredMatcher<int>(
        [&callCount](int const&) {
            callCount++;
            return true;
        },
        "counts calls"
    );
    matcher.match(1);
    matcher.match(2);
    matcher.match(3);
    EXPECT_EQ(callCount, 3);
}

// ============================================================
// Test with stateful predicate (via std::function)
// ============================================================

TEST_F(PredicateMatcherTest_213, MatchWithStdFunction_213) {
    std::function<bool(int const&)> pred = [](int const& x) { return x % 2 == 0; };
    auto matcher = makePredMatcher<int>(std::move(pred), "is even");
    EXPECT_TRUE(matcher.match(0));
    EXPECT_TRUE(matcher.match(2));
    EXPECT_TRUE(matcher.match(-4));
    EXPECT_FALSE(matcher.match(1));
    EXPECT_FALSE(matcher.match(3));
}

// ============================================================
// Test describe with special characters
// ============================================================

TEST_F(PredicateMatcherTest_213, DescribeWithSpecialCharacters_213) {
    auto matcher = makePredMatcher<int>(
        [](int const&) { return true; },
        "value is > 0 && < 100"
    );
    EXPECT_EQ(matcher.describe(), "value is > 0 && < 100");
}

TEST_F(PredicateMatcherTest_213, DescribeWithLongDescription_213) {
    std::string longDesc(1000, 'x');
    auto matcher = makePredMatcher<int>([](int const&) { return true; }, longDesc);
    EXPECT_EQ(matcher.describe(), longDesc);
}

// ============================================================
// Polymorphic behavior test (through base pointer)
// ============================================================

TEST_F(PredicateMatcherTest_213, MatchThroughBasePointer_213) {
    auto matcher = makePredMatcher<int>([](int const& x) { return x > 10; }, "greater than 10");
    Catch::Matchers::MatcherBase<int>* basePtr = &matcher;

    EXPECT_TRUE(basePtr->match(11));
    EXPECT_FALSE(basePtr->match(10));
    EXPECT_EQ(basePtr->describe(), "greater than 10");
}

// ============================================================
// Bool type test
// ============================================================

TEST_F(PredicateMatcherTest_213, MatchWithBoolType_213) {
    auto matcher = makePredMatcher<bool>(
        [](bool const& b) { return b; },
        "is true"
    );
    EXPECT_TRUE(matcher.match(true));
    EXPECT_FALSE(matcher.match(false));
}
