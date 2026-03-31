#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "catch2/internal/catch_output_redirect.hpp"

// We need to create a mock or concrete OutputRedirect to test RedirectGuard.
// Since OutputRedirect is a dependency, we'll create a testable version.

namespace Catch {

// Mock OutputRedirect for testing purposes
class MockOutputRedirect : public OutputRedirect {
public:
    MOCK_METHOD(bool, isActive, (), (const));
    MOCK_METHOD(void, activate, ());
    MOCK_METHOD(void, deactivate, ());
};

} // namespace Catch

using namespace Catch;
using ::testing::Return;
using ::testing::_;

class RedirectGuardTest_1080 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that constructing a RedirectGuard with activate=true works
TEST_F(RedirectGuardTest_1080, ConstructWithActivateTrue_1080) {
    MockOutputRedirect redirect;
    EXPECT_CALL(redirect, isActive()).WillOnce(Return(false));
    EXPECT_CALL(redirect, activate()).Times(1);
    
    {
        RedirectGuard guard(true, redirect);
        // Guard should activate the redirect on construction
    }
    // Destructor called here
}

// Test that constructing a RedirectGuard with activate=false works
TEST_F(RedirectGuardTest_1080, ConstructWithActivateFalse_1080) {
    MockOutputRedirect redirect;
    EXPECT_CALL(redirect, isActive()).WillOnce(Return(false));
    EXPECT_CALL(redirect, activate()).Times(0);
    
    {
        RedirectGuard guard(false, redirect);
    }
}

// Test move constructor transfers ownership
TEST_F(RedirectGuardTest_1080, MoveConstructorTransfersOwnership_1080) {
    MockOutputRedirect redirect;
    EXPECT_CALL(redirect, isActive()).WillRepeatedly(Return(false));
    EXPECT_CALL(redirect, activate()).Times(::testing::AtMost(1));
    EXPECT_CALL(redirect, deactivate()).Times(::testing::AtMost(1));
    
    {
        RedirectGuard guard1(true, redirect);
        RedirectGuard guard2(std::move(guard1));
        // guard1 is moved-from, guard2 should handle cleanup
    }
}

// Test move assignment operator
TEST_F(RedirectGuardTest_1080, MoveAssignmentOperator_1080) {
    MockOutputRedirect redirect1;
    MockOutputRedirect redirect2;
    
    EXPECT_CALL(redirect1, isActive()).WillRepeatedly(Return(false));
    EXPECT_CALL(redirect2, isActive()).WillRepeatedly(Return(false));
    EXPECT_CALL(redirect1, activate()).Times(::testing::AnyNumber());
    EXPECT_CALL(redirect2, activate()).Times(::testing::AnyNumber());
    EXPECT_CALL(redirect1, deactivate()).Times(::testing::AnyNumber());
    EXPECT_CALL(redirect2, deactivate()).Times(::testing::AnyNumber());
    
    {
        RedirectGuard guard1(true, redirect1);
        RedirectGuard guard2(true, redirect2);
        guard2 = std::move(guard1);
    }
}

// Test constructing when redirect is already active
TEST_F(RedirectGuardTest_1080, ConstructWhenAlreadyActive_1080) {
    MockOutputRedirect redirect;
    EXPECT_CALL(redirect, isActive()).WillOnce(Return(true));
    EXPECT_CALL(redirect, activate()).Times(::testing::AnyNumber());
    EXPECT_CALL(redirect, deactivate()).Times(::testing::AnyNumber());
    
    {
        RedirectGuard guard(true, redirect);
    }
}

// Test that moved-from guard doesn't deactivate on destruction
TEST_F(RedirectGuardTest_1080, MovedFromGuardDoesNotDeactivate_1080) {
    MockOutputRedirect redirect;
    EXPECT_CALL(redirect, isActive()).WillRepeatedly(Return(false));
    // activate should be called once (by the original guard)
    // deactivate should be called once (by the moved-to guard, not the moved-from)
    EXPECT_CALL(redirect, activate()).Times(::testing::AtMost(1));
    EXPECT_CALL(redirect, deactivate()).Times(::testing::AtMost(1));
    
    {
        RedirectGuard guard1(true, redirect);
        RedirectGuard guard2(std::move(guard1));
        // guard1 destructor should NOT call deactivate (moved-from)
        // guard2 destructor SHOULD call deactivate
    }
}

// Test copy constructor is deleted (compile-time check - just verify it compiles with move)
TEST_F(RedirectGuardTest_1080, CopyConstructorDeleted_1080) {
    // This is a compile-time check: RedirectGuard(const RedirectGuard&) = delete
    // We verify that move works, implying copy is not used
    EXPECT_TRUE(!std::is_copy_constructible<RedirectGuard>::value);
}

// Test copy assignment is deleted
TEST_F(RedirectGuardTest_1080, CopyAssignmentDeleted_1080) {
    EXPECT_TRUE(!std::is_copy_assignable<RedirectGuard>::value);
}

// Test that the class is move constructible
TEST_F(RedirectGuardTest_1080, IsMoveConstructible_1080) {
    EXPECT_TRUE(std::is_move_constructible<RedirectGuard>::value);
}

// Test that the class is move assignable
TEST_F(RedirectGuardTest_1080, IsMoveAssignable_1080) {
    EXPECT_TRUE(std::is_move_assignable<RedirectGuard>::value);
}

// Test self move assignment
TEST_F(RedirectGuardTest_1080, SelfMoveAssignment_1080) {
    MockOutputRedirect redirect;
    EXPECT_CALL(redirect, isActive()).WillRepeatedly(Return(false));
    EXPECT_CALL(redirect, activate()).Times(::testing::AnyNumber());
    EXPECT_CALL(redirect, deactivate()).Times(::testing::AnyNumber());
    
    {
        RedirectGuard guard(true, redirect);
        guard = std::move(guard);
        // Should handle self-assignment gracefully
    }
}

// Test construction with activate=false when previously active
TEST_F(RedirectGuardTest_1080, ConstructWithActivateFalseWhenPreviouslyActive_1080) {
    MockOutputRedirect redirect;
    EXPECT_CALL(redirect, isActive()).WillOnce(Return(true));
    EXPECT_CALL(redirect, activate()).Times(0);
    EXPECT_CALL(redirect, deactivate()).Times(::testing::AnyNumber());
    
    {
        RedirectGuard guard(false, redirect);
    }
}
