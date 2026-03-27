// File: size_matches_matcher_tests_233.cpp

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <vector>
#include <string>
#include <memory>
#include <cstddef>

// Header under test (path from your prompt)
#include "catch2/matchers/catch_matchers_container_properties.hpp"

using ::testing::Return;
using ::testing::StrictMock;

namespace Catch { namespace Matchers {

// A mock for the inner "size" matcher that SizeMatchesMatcher delegates to.
// We adapt it via a lightweight adapter so we can pass a copyable object into
// SizeMatchesMatcher (its ctor takes the matcher by value/move).
struct MockSizePredicate {
    MOCK_METHOD(bool, match, (std::size_t), (const));
    MOCK_METHOD(std::string, describe, (), (const));
};

struct MockAdapter {
    std::shared_ptr<MockSizePredicate> mock;

    // Interface expected by SizeMatchesMatcher<Matcher>
    bool match(std::size_t sz) const { return mock->match(sz); }
    std::string describe() const { return mock->describe(); }
};

}} // namespace Catch::Matchers

// Alias for brevity
using Catch::Matchers::MockSizePredicate;
using Catch::Matchers::MockAdapter;
using Catch::Matchers::SizeMatchesMatcher;

TEST(SizeMatchesMatcherTest_233, ForwardsSizeOfVector_233) {
    auto mock = std::make_shared<StrictMock<MockSizePredicate>>();
    MockAdapter adapter{mock};

    // Expect the inner matcher to be called with the vector's size (3)
    EXPECT_CALL(*mock, match(3)).WillOnce(Return(true));

    SizeMatchesMatcher<MockAdapter> uut(adapter);

    std::vector<int> v{1, 2, 3};
    EXPECT_TRUE(uut.match(v));
}

TEST(SizeMatchesMatcherTest_233, ReturnsInnerMatcherResultFalse_233) {
    auto mock = std::make_shared<StrictMock<MockSizePredicate>>();
    MockAdapter adapter{mock};

    // Empty vector -> size 0
    EXPECT_CALL(*mock, match(0)).WillOnce(Return(false));

    SizeMatchesMatcher<MockAdapter> uut(adapter);

    std::vector<int> empty;
    EXPECT_FALSE(uut.match(empty));
}

TEST(SizeMatchesMatcherTest_233, WorksWithCStringArray_233) {
    auto mock = std::make_shared<StrictMock<MockSizePredicate>>();
    MockAdapter adapter{mock};

    // Built-in array: size should be 4
    EXPECT_CALL(*mock, match(4)).WillOnce(Return(true));

    SizeMatchesMatcher<MockAdapter> uut(adapter);

    int arr[4] = {1, 2, 3, 4};
    EXPECT_TRUE(uut.match(arr));
}

TEST(SizeMatchesMatcherTest_233, WorksWithStdStringEmpty_233) {
    auto mock = std::make_shared<StrictMock<MockSizePredicate>>();
    MockAdapter adapter{mock};

    // std::string default-constructed -> size 0
    EXPECT_CALL(*mock, match(0)).WillOnce(Return(true));

    SizeMatchesMatcher<MockAdapter> uut(adapter);

    std::string s;
    EXPECT_TRUE(uut.match(s));
}

TEST(SizeMatchesMatcherTest_233, AcceptsRvalueRangeLike_233) {
    auto mock = std::make_shared<StrictMock<MockSizePredicate>>();
    MockAdapter adapter{mock};

    // Temporary vector with 2 elements
    EXPECT_CALL(*mock, match(2)).WillOnce(Return(true));

    SizeMatchesMatcher<MockAdapter> uut(adapter);

    EXPECT_TRUE(uut.match(std::vector<int>{10, 20}));
}
