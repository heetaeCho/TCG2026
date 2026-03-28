#include <gtest/gtest.h>

// Include the header for FatalConditionHandler
#include "catch2/internal/catch_fatal_condition_handler.hpp"

namespace {

// Test fixture for FatalConditionHandler tests
class FatalConditionHandlerTest_485 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that FatalConditionHandler can be default constructed and destructed without error
TEST_F(FatalConditionHandlerTest_485, DefaultConstructionAndDestruction_485) {
    ASSERT_NO_THROW({
        Catch::FatalConditionHandler handler;
    });
}

// Test that engage can be called on a newly constructed handler
TEST_F(FatalConditionHandlerTest_485, EngageAfterConstruction_485) {
    Catch::FatalConditionHandler handler;
    ASSERT_NO_THROW(handler.engage());
    // Disengage to clean up properly
    handler.disengage();
}

// Test that disengage can be called after engage
TEST_F(FatalConditionHandlerTest_485, DisengageAfterEngage_485) {
    Catch::FatalConditionHandler handler;
    handler.engage();
    ASSERT_NO_THROW(handler.disengage());
}

// Test that engage followed by disengage can be repeated
TEST_F(FatalConditionHandlerTest_485, EngageDisengageCycle_485) {
    Catch::FatalConditionHandler handler;
    ASSERT_NO_THROW({
        handler.engage();
        handler.disengage();
        handler.engage();
        handler.disengage();
    });
}

// Test that disengage is noexcept (calling on non-engaged handler)
TEST_F(FatalConditionHandlerTest_485, DisengageIsNoexcept_485) {
    Catch::FatalConditionHandler handler;
    // disengage is declared noexcept, verify it doesn't throw
    ASSERT_NO_THROW(handler.disengage());
}

// Test that multiple handlers can be created and destroyed independently
TEST_F(FatalConditionHandlerTest_485, MultipleHandlersCreated_485) {
    ASSERT_NO_THROW({
        Catch::FatalConditionHandler handler1;
        Catch::FatalConditionHandler handler2;
    });
}

// Test that destruction after engage (without disengage) doesn't crash
TEST_F(FatalConditionHandlerTest_485, DestructionAfterEngageWithoutDisengage_485) {
    ASSERT_NO_THROW({
        Catch::FatalConditionHandler handler;
        handler.engage();
        // Destructor should handle cleanup
    });
}

// Test that the handler can be constructed on the heap and properly deleted
TEST_F(FatalConditionHandlerTest_485, HeapAllocationAndDeletion_485) {
    Catch::FatalConditionHandler* handler = nullptr;
    ASSERT_NO_THROW({
        handler = new Catch::FatalConditionHandler();
        handler->engage();
        handler->disengage();
        delete handler;
    });
}

} // namespace
