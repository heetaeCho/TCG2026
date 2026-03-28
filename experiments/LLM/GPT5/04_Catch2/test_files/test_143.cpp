// File: match_not_of_test.cpp
#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "catch2/matchers/catch_matchers.hpp"  // Uses the provided interface

using ::testing::Return;
using ::testing::StrictMock;

namespace Catch {
namespace Matchers {

// Create a mock for the external collaborator (MatcherBase<T>).
template <typename T>
class MockMatcherBase : public MatcherBase<T> {
public:
    MOCK_METHOD(bool, match, (T const&), (const, override));
    MOCK_METHOD(std::string, describe, (), (const, override));
};

} // namespace Matchers
} // namespace Catch

using Catch::Matchers::MockMatcherBase;
using Catch::Matchers::Detail::MatchNotOf;

// -------------------- Tests --------------------

class MatchNotOfTest_143 : public ::testing::Test {};

// Verifies: When the underlying matcher returns true, MatchNotOf::match returns false.
TEST_F(MatchNotOfTest_143, NegatesTrueToFalse_143) {
    StrictMock<MockMatcherBase<int>> underlying;
    const MatchNotOf<int> notMatcher{underlying};

    EXPECT_CALL(underlying, match(42)).WillOnce(Return(true));

    EXPECT_FALSE(notMatcher.match(42));
}

// Verifies: When the underlying matcher returns false, MatchNotOf::match returns true.
TEST_F(MatchNotOfTest_143, NegatesFalseToTrue_143) {
    StrictMock<MockMatcherBase<int>> underlying;
    const MatchNotOf<int> notMatcher{underlying};

    EXPECT_CALL(underlying, match(-7)).WillOnce(Return(false));

    EXPECT_TRUE(notMatcher.match(-7));
}

// Verifies: The argument is forwarded exactly once and unmodified to the underlying matcher.
TEST_F(MatchNotOfTest_143, ForwardsArgumentExactlyOnce_143) {
    StrictMock<MockMatcherBase<std::string>> underlying;
    const MatchNotOf<std::string> notMatcher{underlying};

    const std::string input = "catch2";
    EXPECT_CALL(underlying, match(input)).WillOnce(Return(false));

    // Underlying returns false -> negation yields true.
    EXPECT_TRUE(notMatcher.match(input));
}

// Verifies: match is callable on a const MatchNotOf instance (interface const-correctness).
TEST_F(MatchNotOfTest_143, MatchCallableOnConstInstance_143) {
    StrictMock<MockMatcherBase<int>> underlying;
    const MatchNotOf<int> notMatcher{underlying};

    EXPECT_CALL(underlying, match(0)).WillOnce(Return(true));

    // If match is correctly marked const, this compiles and runs: true -> negated to false.
    const bool result = notMatcher.match(0);
    EXPECT_FALSE(result);
}

