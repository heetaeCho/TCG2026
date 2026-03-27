// File: tests/ColumnsEndTests_56.cpp
#include <gtest/gtest.h>
#include "catch2/internal/catch_textflow.hpp"

using namespace Catch::TextFlow;

class ColumnsEndTest_56 : public ::testing::Test {
protected:
    Columns cols; // Rely on default-constructibility if available
};

// [Normal] Two end() iterators from the same instance compare equal.
TEST_F(ColumnsEndTest_56, EndIteratorEquality_SameInstance_56) {
    auto e1 = cols.end();
    auto e2 = cols.end();
    EXPECT_TRUE(e1 == e2);
    EXPECT_FALSE(e1 != e2);
}

// [Normal] Copy-constructing an end() iterator preserves equality.
TEST_F(ColumnsEndTest_56, EndIteratorCopyConstructible_56) {
    auto e1 = cols.end();
    auto e2 = e1; // copy-constructed
    EXPECT_TRUE(e1 == e2);
}

// [Normal] Copy-assigning an end() iterator preserves equality.
TEST_F(ColumnsEndTest_56, EndIteratorCopyAssignable_56) {
    auto e1 = cols.end();
    auto e2 = cols.end();
    e2 = e1; // copy-assigned
    EXPECT_TRUE(e1 == e2);
}

// [Boundary] Iterating an empty/default-constructed Columns performs zero iterations.
// (Only checks observable loop count; does not assume container internals.)
TEST_F(ColumnsEndTest_56, EmptyIterationYieldsNoElements_56) {
    size_t count = 0;
    for (auto it = cols.begin(); it != cols.end(); ++it) {
        ++count; // Should not execute if iteration is empty
    }
    EXPECT_EQ(count, 0u);
}

// [Boundary] end() is const-correct: it can be called on a const Columns.
TEST_F(ColumnsEndTest_56, EndCallableOnConstInstance_56) {
    const Columns& cref = cols;
    auto e = cref.end();
    // Just ensure it compiles and yields an iterator comparable to another end()
    EXPECT_TRUE(e == cref.end());
}

// [Exceptional / Safety] Do NOT dereference end(); verify only that comparing end() to itself is safe.
// This test documents the contract and avoids undefined behavior.
TEST_F(ColumnsEndTest_56, EndIteratorIsOnlyForSentinelComparison_56) {
    auto e = cols.end();
    // Sentinel comparisons are allowed; dereference would be UB and is intentionally not tested.
    EXPECT_TRUE(e == cols.end());
}
