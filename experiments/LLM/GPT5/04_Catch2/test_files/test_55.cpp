// Columns_begin_tests_55.cpp
#include <gtest/gtest.h>

// Include the interface under test
// Adjust the include path if your project layout differs.
#include "Catch2/src/catch2/internal/catch_textflow.hpp"

using Catch::TextFlow::Columns;

class ColumnsBeginTest_55 : public ::testing::Test {};

// [Normal] begin() is callable on const Columns and returns something usable
TEST_F(ColumnsBeginTest_55, BeginCallableOnConst_55) {
    const Columns cols;
    auto it = cols.begin();  // should compile and be valid to hold
    (void)it;                // silence unused variable warning
}

// [Boundary/Empty] For a default-constructed Columns, begin() == end()
TEST_F(ColumnsBeginTest_55, BeginEqualsEndWhenEmpty_55) {
    const Columns cols;
    EXPECT_EQ(cols.begin(), cols.end());
}

// [Consistency] Multiple calls to begin() on the same const object are consistent
TEST_F(ColumnsBeginTest_55, MultipleBeginCallsConsistent_55) {
    const Columns cols;
    auto it1 = cols.begin();
    auto it2 = cols.begin();
    EXPECT_EQ(it1, it2);
}

// [Iterator semantics] Copy-constructing the iterator preserves position
TEST_F(ColumnsBeginTest_55, IteratorCopyPreservesPosition_55) {
    const Columns cols;
    auto it = cols.begin();
    auto copy = it;      // copy-construct
    EXPECT_EQ(it, copy); // should refer to the same position
}

// [Observable behavior] Range-for over empty Columns performs zero iterations
TEST_F(ColumnsBeginTest_55, RangeForOverEmptyHasZeroIterations_55) {
    const Columns cols;
    int count = 0;
    for (auto&& _ : cols) {
        (void)_;
        ++count;
    }
    EXPECT_EQ(count, 0);
}
