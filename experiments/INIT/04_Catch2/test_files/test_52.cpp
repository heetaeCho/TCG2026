// File: column_end_tests_52.cpp
#include <gtest/gtest.h>

#include "catch2/internal/catch_textflow.hpp"

using Catch::TextFlow::Column;

class ColumnEndTest_52 : public ::testing::Test {};

// Verifies that .end() can be called on a const Column and returns a
// value that is equal to another call to .end() (idempotent).
TEST_F(ColumnEndTest_52, EndIsIdempotent_52) {
    const Column col{"Hello world"};
    auto e1 = col.end();
    auto e2 = col.end();
    EXPECT_EQ(e1, e2);
}

// Verifies that iteration from begin() to end() is possible and terminates.
// Does not assert on specific content or count; only that end() is reachable.
TEST_F(ColumnEndTest_52, EndIsReachableFromBegin_52) {
    Column col{"This is a short sample line."};
    std::size_t count = 0;
    for (auto it = col.begin(); it != col.end(); ++it) {
        ++count;
        // Safety net to avoid an accidental infinite loop if the iterator misbehaves.
        ASSERT_LT(count, static_cast<std::size_t>(1000));
    }
    // We only assert that iteration terminated by reaching end().
    SUCCEED();
}

// Verifies that .end() participates in range-based for iteration.
// This checks that begin()/end() interoperate correctly as an observable behavior.
TEST_F(ColumnEndTest_52, EndWorksInRangeFor_52) {
    Column col{"range-based for test"};
    std::size_t hits = 0;
    for (const auto& /*line*/ : col) {
        ++hits;
        ASSERT_LT(hits, static_cast<std::size_t>(1000));
    }
    SUCCEED();
}

// Verifies that taking the distance using manual iteration with fresh end() calls
// yields the same result across repeated traversals (stability of end()).
TEST_F(ColumnEndTest_52, EndStableAcrossTraversals_52) {
    Column col{"Repeatable traversal over the same Column instance."};

    auto count_pass = [](const Column& c) -> std::size_t {
        std::size_t n = 0;
        for (auto it = c.begin(); it != c.end(); ++it) {
            ++n;
            ASSERT_LT(n, static_cast<std::size_t>(1000));
        }
        return n;
    };

    const std::size_t first = count_pass(col);
    const std::size_t second = count_pass(col);
    EXPECT_EQ(first, second);
}
