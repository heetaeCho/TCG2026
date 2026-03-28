#include <gtest/gtest.h>

// Include necessary Catch2 headers to access the interface
#include "catch2/catch_registry_hub.hpp"
#include "catch2/internal/catch_context.hpp"
#include "catch2/catch_session.hpp"

namespace Catch {
    // Declaration of the function under test
    void cleanUp();
}

class CatchCleanUpTest_288 : public ::testing::Test {
protected:
    void SetUp() override {
        // Ensure Catch2 context is initialized before tests
    }

    void TearDown() override {
    }
};

// Test that cleanUp can be called without throwing or crashing
TEST_F(CatchCleanUpTest_288, CleanUpDoesNotThrow_288) {
    EXPECT_NO_THROW(Catch::cleanUp());
}

// Test that cleanUp can be called multiple times without crashing
// This tests idempotency - calling cleanup repeatedly should be safe
TEST_F(CatchCleanUpTest_288, CleanUpCanBeCalledMultipleTimes_288) {
    EXPECT_NO_THROW(Catch::cleanUp());
    EXPECT_NO_THROW(Catch::cleanUp());
    EXPECT_NO_THROW(Catch::cleanUp());
}

// Test that cleanUp is safe to call in sequence (boundary: rapid successive calls)
TEST_F(CatchCleanUpTest_288, CleanUpSuccessiveCalls_288) {
    for (int i = 0; i < 10; ++i) {
        EXPECT_NO_THROW(Catch::cleanUp());
    }
}

// Test that after cleanUp, the function remains callable (no permanent invalid state)
TEST_F(CatchCleanUpTest_288, CleanUpDoesNotLeaveInvalidState_288) {
    Catch::cleanUp();
    // Calling again should not segfault or throw
    EXPECT_NO_THROW(Catch::cleanUp());
}
