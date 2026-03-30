// matcher_untyped_base_to_string_tests_246.cpp
#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <string>

// Minimal includes/adaptations to match the provided interface
// (We place the tested class in the same namespaces as in the prompt.)
namespace Catch { namespace Matchers {

class MatcherUntypedBase {
protected:
    // As used by toString() in the .cpp, describe() must be callable from a const context.
    virtual std::string describe() const { return std::string(); }
    mutable std::string m_cachedToString;

public:
    MatcherUntypedBase() = default;
    MatcherUntypedBase(const MatcherUntypedBase&) = default;
    MatcherUntypedBase(MatcherUntypedBase&&) = default;
    virtual ~MatcherUntypedBase() = default;

    std::string toString() const {
        if (m_cachedToString.empty()) {
            m_cachedToString = describe();
        }
        return m_cachedToString;
    }

    MatcherUntypedBase& operator=(const MatcherUntypedBase&) = delete;
    MatcherUntypedBase& operator=(MatcherUntypedBase&&) = delete;
};

}} // namespace Catch::Matchers

using ::testing::Return;
using ::testing::Exactly;

namespace Catch { namespace Matchers {

// A Google Mock–based derived class to observe calls to the protected virtual `describe()`.
class MockMatcher : public MatcherUntypedBase {
public:
    using MatcherUntypedBase::toString; // expose toString() for tests
protected:
    MOCK_METHOD(std::string, describe, (), (const, override));
};

}} // namespace Catch::Matchers

using Catch::Matchers::MockMatcher;

// ---------- Tests ----------

class MatcherUntypedBaseTest_246 : public ::testing::Test {};

// Normal operation: first call computes via describe(); value returned.
TEST_F(MatcherUntypedBaseTest_246, FirstCallInvokesDescribeAndReturnsResult_246) {
    MockMatcher mock;
    EXPECT_CALL(mock, describe())
        .Times(Exactly(1))
        .WillOnce(Return("desc"));

    const std::string s = mock.toString();
    EXPECT_EQ(s, "desc");
}

// Caching behavior: subsequent calls do NOT call describe() again once cached.
TEST_F(MatcherUntypedBaseTest_246, SubsequentCallsUseCacheDoNotReinvokeDescribe_246) {
    MockMatcher mock;
    EXPECT_CALL(mock, describe())
        .Times(Exactly(1))
        .WillOnce(Return("cached-value"));

    // First call fills the cache
    EXPECT_EQ(mock.toString(), "cached-value");
    // These should be served from the cache, without new describe() calls
    EXPECT_EQ(mock.toString(), "cached-value");
    EXPECT_EQ(mock.toString(), "cached-value");
}

// Boundary-like behavior: if describe() returns an empty string,
// toString() will consider the cache "empty" and call describe() every time.
TEST_F(MatcherUntypedBaseTest_246, EmptyDescribeLeadsToRecomputeOnEveryCall_246) {
    MockMatcher mock;
    EXPECT_CALL(mock, describe())
        .Times(Exactly(2))
        .WillRepeatedly(Return("")); // always returns empty

    EXPECT_EQ(mock.toString(), "");
    EXPECT_EQ(mock.toString(), ""); // triggers describe() again due to empty cache
}

// Sanity: toString() mirrors describe()’s value (string equality).
TEST_F(MatcherUntypedBaseTest_246, ToStringEqualsDescribeValue_246) {
    MockMatcher mock;
    EXPECT_CALL(mock, describe())
        .Times(Exactly(1))
        .WillOnce(Return("the description"));

    EXPECT_EQ(mock.toString(), "the description");
}
