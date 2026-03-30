// tests/textflow_isBoundary_613.cpp
#include <gtest/gtest.h>

// Include the production code so we can access the internal static function.
#include "Catch2/src/catch2/internal/catch_textflow.cpp"
#include "Catch2/src/catch2/internal/catch_textflow.hpp"

using Catch::TextFlow::AnsiSkippingString;
using Catch::TextFlow::isBoundary;

class TextFlowIsBoundaryTest_613 : public ::testing::Test {
protected:
    // Utility: advance const_iterator by n steps from begin()
    static AnsiSkippingString::const_iterator adv(AnsiSkippingString const& s, std::size_t n) {
        auto it = s.begin();
        for (std::size_t i = 0; i < n; ++i) { ++it; }
        return it;
    }
};

// End iterator is always a boundary
TEST_F(TextFlowIsBoundaryTest_613, EndIteratorIsBoundary_613) {
    AnsiSkippingString line{"hello"};
    auto it = line.end();
    EXPECT_TRUE(isBoundary(line, it));
}

// Whitespace that follows a non-whitespace is a boundary (observable via iterator/dereference only)
TEST_F(TextFlowIsBoundaryTest_613, SpaceFollowingNonSpaceIsBoundary_613) {
    AnsiSkippingString line{"a b"};
    // iterator pointing at the space
    auto it = adv(line, 1);
    // Sanity: we are not at end()
    ASSERT_TRUE(it != line.end());
    EXPECT_TRUE(isBoundary(line, it));
}

// Whitespace following whitespace is not (necessarily) a boundary
TEST_F(TextFlowIsBoundaryTest_613, ConsecutiveSpacesNotBoundary_613) {
    AnsiSkippingString line{"  b"};
    // iterator pointing at the second space (index 1)
    auto it = adv(line, 1);
    ASSERT_TRUE(it != line.end());
    EXPECT_FALSE(isBoundary(line, it));
}

// Inside a simple word (non-whitespace flanked), iterator is not a boundary
TEST_F(TextFlowIsBoundaryTest_613, InsideWordNotBoundary_613) {
    AnsiSkippingString line{"ab"};
    // iterator pointing at 'b' (index 1), previous is 'a'
    auto it = adv(line, 1);
    ASSERT_TRUE(it != line.end());
    EXPECT_FALSE(isBoundary(line, it));
}
