// File: tests/BoundRefTest_658.cpp

#include <gtest/gtest.h>

// Include the provided interface header
#include "Catch2/src/catch2/internal/catch_clara.hpp"

using Catch::Clara::Detail::BoundRef;

// Test fixture (kept minimal as there are no external collaborators)
class BoundRefTest_658 : public ::testing::Test {};

// [Normal operation] Calling isContainer() should return false.
TEST_F(BoundRefTest_658, IsContainer_ReturnsFalse_658) {
    BoundRef ref;
    EXPECT_FALSE(ref.isContainer());
}

// [Boundary/const-correctness] isContainer() callable on const instances, still false.
TEST_F(BoundRefTest_658, IsContainer_ConstAndNonConst_658) {
    BoundRef ref;
    const BoundRef& cref = ref;  // use a const reference to enforce const-call
    EXPECT_FALSE(cref.isContainer());
    EXPECT_FALSE(ref.isContainer()); // non-const call also remains false
}

// [Stability/idempotence] Multiple calls should be consistent and not change observable state.
TEST_F(BoundRefTest_658, IsContainer_MultipleCallsConsistent_658) {
    BoundRef ref;
    // Call several times; all should be false.
    for (int i = 0; i < 10; ++i) {
        EXPECT_FALSE(ref.isContainer()) << "isContainer() changed on iteration " << i;
    }
}
