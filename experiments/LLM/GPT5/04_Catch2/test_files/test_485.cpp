// File: tests/fatal_condition_handler_tests_485.cpp

#include <gtest/gtest.h>

// Include the class under test
#include "catch2/internal/catch_fatal_condition_handler.hpp"

// We observe the externally visible global as part of the public namespace.
// This is NOT accessing private class state; it's validating the destructor's
// effect on the module-level global pointer described in the prompt.
namespace Catch {
    extern char* altStackMem;
}

class FatalConditionHandlerTest_485 : public ::testing::Test {
protected:
    void SetUp() override {
        // Start each test from a known baseline.
        // We do not delete here; tests control allocation & the class under
        // test is responsible for cleanup in its destructor.
        Catch::altStackMem = nullptr;
    }

    void TearDown() override {
        // Ensure clean end state for isolation across tests.
        // (No delete here to avoid interfering with the destructor’s ownership.)
        Catch::altStackMem = nullptr;
    }
};

// Verifies: Destructor is safe when altStackMem is already nullptr and leaves it nullptr.
TEST_F(FatalConditionHandlerTest_485, DestructorWithNullAltStackMem_LeavesNull_485) {
    using Catch::FatalConditionHandler;
    {
        FatalConditionHandler h; // ctor — treat as black box
        // Nothing allocated to altStackMem
    } // dtor should do delete[] on nullptr (safe) and set to nullptr

    EXPECT_EQ(nullptr, Catch::altStackMem);
}

// Verifies: If altStackMem points to allocated memory, destructor deletes it and nulls the pointer.
TEST_F(FatalConditionHandlerTest_485, DestructorWithAllocatedAltStackMem_DeletesAndNulls_485) {
    using Catch::FatalConditionHandler;

    // Simulate platform allocation performed elsewhere in the system.
    Catch::altStackMem = new char[128];
    Catch::altStackMem[0] = 'X'; // touch memory to avoid optimizer silliness

    {
        FatalConditionHandler h;
    } // dtor should delete[] altStackMem and set it to nullptr

    EXPECT_EQ(nullptr, Catch::altStackMem);
}

// Verifies: Multiple destructors in sequence remain safe when altStackMem is nullptr after the first.
TEST_F(FatalConditionHandlerTest_485, MultipleDestructorsAreSafeWhenPointerAlreadyNull_485) {
    using Catch::FatalConditionHandler;

    // First lifetime frees and nulls the pointer
    Catch::altStackMem = new char[8];
    {
        FatalConditionHandler h1;
    }
    ASSERT_EQ(nullptr, Catch::altStackMem) << "First destructor should null the global pointer";

    // Second lifetime should be a no-op w.r.t. altStackMem and remain nullptr
    {
        FatalConditionHandler h2;
    }
    EXPECT_EQ(nullptr, Catch::altStackMem);
}

// Verifies: altStackMem allocated during the handler's lifetime is still cleaned up by the destructor.
TEST_F(FatalConditionHandlerTest_485, AllocationDuringLifetime_IsCleanedOnDestruction_485) {
    using Catch::FatalConditionHandler;

    {
        FatalConditionHandler h;

        // During the object's lifetime, the external system allocates alt stack memory.
        Catch::altStackMem = new char[16];
        Catch::altStackMem[0] = 'A';
    } // On leaving scope, destructor should see non-null and delete[] + null it

    EXPECT_EQ(nullptr, Catch::altStackMem);
}
