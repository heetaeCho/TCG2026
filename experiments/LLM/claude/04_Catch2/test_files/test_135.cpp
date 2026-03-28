#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <string>
#include <vector>

// Since we need to test MatchAllOf which depends on MatcherBase,
// we need to provide the necessary infrastructure.
// Based on the interface, we reconstruct the minimal needed types.

namespace Catch {
namespace Matchers {

template <typename ArgT>
class MatcherBase {
public:
    virtual ~MatcherBase() = default;
    virtual bool match(ArgT const& arg) const = 0;
    virtual std::string describe() const = 0;
};

namespace Detail {

template <typename ArgT>
class MatchAllOf : public MatcherBase<ArgT> {
    std::vector<const MatcherBase<ArgT>*> m_matchers;

public:
    MatchAllOf() = default;
    MatchAllOf(MatchAllOf const&) = delete;
    MatchAllOf(MatchAllOf&&) = default;
    MatchAllOf& operator=(MatchAllOf const&) = delete;
    MatchAllOf& operator=(MatchAllOf&&) = default;

    bool match(ArgT const& arg) const override {
        for (auto matcher : m_matchers) {
            if (!matcher->match(arg)) return false;
        }
        return true;
    }

    std::string describe() const override {
        std::string description;
        for (size_t i = 0; i < m_matchers.size(); ++i) {
            if (i > 0) description += " and ";
            description += m_matchers[i]->describe();
        }
        return description;
    }

    // We need a way to add matchers - based on typical Catch2 pattern
    MatchAllOf& operator&&(MatcherBase<ArgT> const& other) {
        m_matchers.push_back(&other);
        return *this;
    }

    // Helper for tests to add matchers
    void addMatcher(MatcherBase<ArgT> const* matcher) {
        m_matchers.push_back(matcher);
    }
};

} // namespace Detail
} // namespace Matchers
} // namespace Catch

// Mock matcher for testing
template <typename ArgT>
class MockMatcher : public Catch::Matchers::MatcherBase<ArgT> {
public:
    MOCK_METHOD(bool, match, (ArgT const& arg), (const, override));
    MOCK_METHOD(std::string, describe, (), (const, override));
};

// A concrete test matcher that checks if int is greater than a threshold
class GreaterThanMatcher : public Catch::Matchers::MatcherBase<int> {
    int m_threshold;
public:
    explicit GreaterThanMatcher(int threshold) : m_threshold(threshold) {}
    bool match(int const& arg) const override { return arg > m_threshold; }
    std::string describe() const override { return "is greater than " + std::to_string(m_threshold); }
};

// A concrete test matcher that checks if int is less than a threshold
class LessThanMatcher : public Catch::Matchers::MatcherBase<int> {
    int m_threshold;
public:
    explicit LessThanMatcher(int threshold) : m_threshold(threshold) {}
    bool match(int const& arg) const override { return arg < m_threshold; }
    std::string describe() const override { return "is less than " + std::to_string(m_threshold); }
};

// A concrete test matcher that checks if int is even
class IsEvenMatcher : public Catch::Matchers::MatcherBase<int> {
public:
    bool match(int const& arg) const override { return arg % 2 == 0; }
    std::string describe() const override { return "is even"; }
};

using MatchAllOfInt = Catch::Matchers::Detail::MatchAllOf<int>;
using MatchAllOfString = Catch::Matchers::Detail::MatchAllOf<std::string>;

class MatchAllOfTest_135 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test: Empty MatchAllOf should match any argument (vacuous truth)
TEST_F(MatchAllOfTest_135, EmptyMatchAllOfMatchesAnyArg_135) {
    MatchAllOfInt allOf;
    EXPECT_TRUE(allOf.match(0));
    EXPECT_TRUE(allOf.match(42));
    EXPECT_TRUE(allOf.match(-100));
}

// Test: Single matcher that matches
TEST_F(MatchAllOfTest_135, SingleMatcherThatMatches_135) {
    MatchAllOfInt allOf;
    GreaterThanMatcher gt(5);
    allOf.addMatcher(&gt);
    EXPECT_TRUE(allOf.match(10));
}

// Test: Single matcher that does not match
TEST_F(MatchAllOfTest_135, SingleMatcherThatDoesNotMatch_135) {
    MatchAllOfInt allOf;
    GreaterThanMatcher gt(5);
    allOf.addMatcher(&gt);
    EXPECT_FALSE(allOf.match(3));
}

// Test: Single matcher boundary - exactly at threshold
TEST_F(MatchAllOfTest_135, SingleMatcherBoundary_135) {
    MatchAllOfInt allOf;
    GreaterThanMatcher gt(5);
    allOf.addMatcher(&gt);
    EXPECT_FALSE(allOf.match(5)); // not greater than 5
}

// Test: Two matchers both match
TEST_F(MatchAllOfTest_135, TwoMatchersBothMatch_135) {
    MatchAllOfInt allOf;
    GreaterThanMatcher gt(5);
    LessThanMatcher lt(20);
    allOf.addMatcher(&gt);
    allOf.addMatcher(&lt);
    EXPECT_TRUE(allOf.match(10));
}

// Test: Two matchers, first fails
TEST_F(MatchAllOfTest_135, TwoMatchersFirstFails_135) {
    MatchAllOfInt allOf;
    GreaterThanMatcher gt(5);
    LessThanMatcher lt(20);
    allOf.addMatcher(&gt);
    allOf.addMatcher(&lt);
    EXPECT_FALSE(allOf.match(3));
}

// Test: Two matchers, second fails
TEST_F(MatchAllOfTest_135, TwoMatchersSecondFails_135) {
    MatchAllOfInt allOf;
    GreaterThanMatcher gt(5);
    LessThanMatcher lt(20);
    allOf.addMatcher(&gt);
    allOf.addMatcher(&lt);
    EXPECT_FALSE(allOf.match(25));
}

// Test: Two matchers, both fail
TEST_F(MatchAllOfTest_135, TwoMatchersBothFail_135) {
    MatchAllOfInt allOf;
    GreaterThanMatcher gt(50);
    LessThanMatcher lt(10);
    allOf.addMatcher(&gt);
    allOf.addMatcher(&lt);
    EXPECT_FALSE(allOf.match(30)); // not > 50 and not < 10
}

// Test: Three matchers all match
TEST_F(MatchAllOfTest_135, ThreeMatchersAllMatch_135) {
    MatchAllOfInt allOf;
    GreaterThanMatcher gt(5);
    LessThanMatcher lt(20);
    IsEvenMatcher even;
    allOf.addMatcher(&gt);
    allOf.addMatcher(&lt);
    allOf.addMatcher(&even);
    EXPECT_TRUE(allOf.match(10)); // > 5, < 20, even
}

// Test: Three matchers, last one fails
TEST_F(MatchAllOfTest_135, ThreeMatchersLastFails_135) {
    MatchAllOfInt allOf;
    GreaterThanMatcher gt(5);
    LessThanMatcher lt(20);
    IsEvenMatcher even;
    allOf.addMatcher(&gt);
    allOf.addMatcher(&lt);
    allOf.addMatcher(&even);
    EXPECT_FALSE(allOf.match(11)); // > 5, < 20, but odd
}

// Test: Short circuit behavior - first matcher fails, second should still be evaluated
// (or not - we verify the result is correct regardless)
TEST_F(MatchAllOfTest_135, ShortCircuitFirstFails_135) {
    MockMatcher<int> mock1;
    MockMatcher<int> mock2;

    EXPECT_CALL(mock1, match(::testing::_)).WillOnce(::testing::Return(false));
    // mock2 should NOT be called if short-circuit is implemented
    EXPECT_CALL(mock2, match(::testing::_)).Times(0);

    MatchAllOfInt allOf;
    allOf.addMatcher(&mock1);
    allOf.addMatcher(&mock2);

    EXPECT_FALSE(allOf.match(42));
}

// Test: All matchers are called when all return true
TEST_F(MatchAllOfTest_135, AllMatchersCalledWhenAllTrue_135) {
    MockMatcher<int> mock1;
    MockMatcher<int> mock2;
    MockMatcher<int> mock3;

    EXPECT_CALL(mock1, match(::testing::_)).WillOnce(::testing::Return(true));
    EXPECT_CALL(mock2, match(::testing::_)).WillOnce(::testing::Return(true));
    EXPECT_CALL(mock3, match(::testing::_)).WillOnce(::testing::Return(true));

    MatchAllOfInt allOf;
    allOf.addMatcher(&mock1);
    allOf.addMatcher(&mock2);
    allOf.addMatcher(&mock3);

    EXPECT_TRUE(allOf.match(42));
}

// Test: Middle matcher fails, subsequent matchers should not be called
TEST_F(MatchAllOfTest_135, MiddleMatcherFailsShortCircuit_135) {
    MockMatcher<int> mock1;
    MockMatcher<int> mock2;
    MockMatcher<int> mock3;

    EXPECT_CALL(mock1, match(::testing::_)).WillOnce(::testing::Return(true));
    EXPECT_CALL(mock2, match(::testing::_)).WillOnce(::testing::Return(false));
    EXPECT_CALL(mock3, match(::testing::_)).Times(0);

    MatchAllOfInt allOf;
    allOf.addMatcher(&mock1);
    allOf.addMatcher(&mock2);
    allOf.addMatcher(&mock3);

    EXPECT_FALSE(allOf.match(42));
}

// Test: Correct argument is passed to each matcher
TEST_F(MatchAllOfTest_135, CorrectArgumentPassedToMatchers_135) {
    MockMatcher<int> mock1;
    MockMatcher<int> mock2;

    EXPECT_CALL(mock1, match(99)).WillOnce(::testing::Return(true));
    EXPECT_CALL(mock2, match(99)).WillOnce(::testing::Return(true));

    MatchAllOfInt allOf;
    allOf.addMatcher(&mock1);
    allOf.addMatcher(&mock2);

    EXPECT_TRUE(allOf.match(99));
}

// Test: String type argument
TEST_F(MatchAllOfTest_135, StringTypeArgument_135) {
    MockMatcher<std::string> mock1;
    MockMatcher<std::string> mock2;

    EXPECT_CALL(mock1, match(std::string("hello"))).WillOnce(::testing::Return(true));
    EXPECT_CALL(mock2, match(std::string("hello"))).WillOnce(::testing::Return(true));

    MatchAllOfString allOf;
    allOf.addMatcher(&mock1);
    allOf.addMatcher(&mock2);

    EXPECT_TRUE(allOf.match("hello"));
}

// Test: String type argument with failure
TEST_F(MatchAllOfTest_135, StringTypeArgumentFailure_135) {
    MockMatcher<std::string> mock1;

    EXPECT_CALL(mock1, match(std::string("world"))).WillOnce(::testing::Return(false));

    MatchAllOfString allOf;
    allOf.addMatcher(&mock1);

    EXPECT_FALSE(allOf.match("world"));
}

// Test: Multiple calls to match with different arguments
TEST_F(MatchAllOfTest_135, MultipleCallsDifferentArguments_135) {
    MatchAllOfInt allOf;
    GreaterThanMatcher gt(0);
    allOf.addMatcher(&gt);

    EXPECT_TRUE(allOf.match(1));
    EXPECT_TRUE(allOf.match(100));
    EXPECT_FALSE(allOf.match(0));
    EXPECT_FALSE(allOf.match(-5));
}

// Test: Many matchers all matching
TEST_F(MatchAllOfTest_135, ManyMatchersAllMatching_135) {
    std::vector<std::unique_ptr<MockMatcher<int>>> mocks;
    MatchAllOfInt allOf;

    for (int i = 0; i < 10; ++i) {
        mocks.push_back(std::make_unique<MockMatcher<int>>());
        EXPECT_CALL(*mocks.back(), match(::testing::_)).WillOnce(::testing::Return(true));
        allOf.addMatcher(mocks.back().get());
    }

    EXPECT_TRUE(allOf.match(42));
}

// Test: Many matchers, last one fails
TEST_F(MatchAllOfTest_135, ManyMatchersLastFails_135) {
    std::vector<std::unique_ptr<MockMatcher<int>>> mocks;
    MatchAllOfInt allOf;

    for (int i = 0; i < 9; ++i) {
        mocks.push_back(std::make_unique<MockMatcher<int>>());
        EXPECT_CALL(*mocks.back(), match(::testing::_)).WillOnce(::testing::Return(true));
        allOf.addMatcher(mocks.back().get());
    }
    mocks.push_back(std::make_unique<MockMatcher<int>>());
    EXPECT_CALL(*mocks.back(), match(::testing::_)).WillOnce(::testing::Return(false));
    allOf.addMatcher(mocks.back().get());

    EXPECT_FALSE(allOf.match(42));
}

// Test: MatchAllOf is a MatcherBase (polymorphism)
TEST_F(MatchAllOfTest_135, IsMatcherBase_135) {
    MatchAllOfInt allOf;
    Catch::Matchers::MatcherBase<int>* basePtr = &allOf;
    EXPECT_TRUE(basePtr->match(42)); // empty = vacuous truth
}

// Test: Negative numbers
TEST_F(MatchAllOfTest_135, NegativeNumbers_135) {
    MatchAllOfInt allOf;
    LessThanMatcher lt(0);
    allOf.addMatcher(&lt);
    EXPECT_TRUE(allOf.match(-1));
    EXPECT_TRUE(allOf.match(-1000));
    EXPECT_FALSE(allOf.match(0));
    EXPECT_FALSE(allOf.match(1));
}

// Test: Move construction
TEST_F(MatchAllOfTest_135, MoveConstruction_135) {
    MatchAllOfInt allOf;
    GreaterThanMatcher gt(5);
    allOf.addMatcher(&gt);

    MatchAllOfInt moved(std::move(allOf));
    EXPECT_TRUE(moved.match(10));
    EXPECT_FALSE(moved.match(3));
}

// Test: Move assignment
TEST_F(MatchAllOfTest_135, MoveAssignment_135) {
    MatchAllOfInt allOf;
    GreaterThanMatcher gt(5);
    allOf.addMatcher(&gt);

    MatchAllOfInt target;
    target = std::move(allOf);
    EXPECT_TRUE(target.match(10));
    EXPECT_FALSE(target.match(3));
}
