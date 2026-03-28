#include <gtest/gtest.h>
#include "catch2/internal/catch_fatal_condition_handler.hpp"

class FatalConditionHandlerTest_434 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that a default-constructed FatalConditionHandler can be destroyed without issues
TEST_F(FatalConditionHandlerTest_434, DefaultConstructionAndDestruction_434) {
    EXPECT_NO_THROW({
        Catch::FatalConditionHandler handler;
    });
}

// Test that engage followed by disengage works correctly
TEST_F(FatalConditionHandlerTest_434, EngageThenDisengage_434) {
    Catch::FatalConditionHandler handler;
    EXPECT_NO_THROW({
        handler.engage();
        handler.disengage();
    });
}

// Test that engage and disengage can be called multiple times in sequence
TEST_F(FatalConditionHandlerTest_434, MultipleEngageDisengageCycles_434) {
    Catch::FatalConditionHandler handler;
    EXPECT_NO_THROW({
        handler.engage();
        handler.disengage();
        handler.engage();
        handler.disengage();
    });
}

// Test that disengage without engage triggers assertion failure (m_started is false)
// Since disengage has an assert that m_started must be true, calling disengage
// without engage should fail the assertion. In debug builds this would abort.
// We test this as a death test.
TEST_F(FatalConditionHandlerTest_434, DisengageWithoutEngageCausesAssertionFailure_434) {
    EXPECT_DEATH({
        Catch::FatalConditionHandler handler;
        handler.disengage();
    }, "");
}

// Test that calling disengage twice after a single engage causes assertion failure
TEST_F(FatalConditionHandlerTest_434, DoubleDisengageCausesAssertionFailure_434) {
    EXPECT_DEATH({
        Catch::FatalConditionHandler handler;
        handler.engage();
        handler.disengage();
        handler.disengage();
    }, "");
}

// Test that engage can be called and handler can be destroyed (destructor should handle cleanup)
TEST_F(FatalConditionHandlerTest_434, EngageWithoutExplicitDisengage_434) {
    EXPECT_NO_THROW({
        Catch::FatalConditionHandler handler;
        handler.engage();
        // Destructor should handle cleanup
    });
}

// Test that disengage is noexcept
TEST_F(FatalConditionHandlerTest_434, DisengageIsNoexcept_434) {
    Catch::FatalConditionHandler handler;
    handler.engage();
    static_assert(noexcept(handler.disengage()), "disengage() should be noexcept");
    handler.disengage();
}
