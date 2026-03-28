#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <string>

// We need to include the actual headers or recreate the interface for testing
// Based on the provided interface, we create a mock of OutputRedirect

namespace Catch {

class OutputRedirect {
protected:
    bool m_redirectActive = false;
    virtual void activateImpl() = 0;
    virtual void deactivateImpl() = 0;

public:
    virtual ~OutputRedirect() = default;
    virtual std::string getStdout() { return ""; }
    virtual std::string getStderr() { return ""; }
    virtual void clearBuffers() {}

    bool isActive() const { return m_redirectActive; }

    void activate() {
        m_redirectActive = true;
        activateImpl();
    }

    void deactivate() {
        m_redirectActive = false;
        deactivateImpl();
    }
};

class RedirectGuard {
private:
    OutputRedirect* m_redirect;
    bool m_activate;
    bool m_previouslyActive;
    bool m_moved = false;

public:
    RedirectGuard(bool activate, OutputRedirect& redirectImpl)
        : m_redirect(&redirectImpl),
          m_activate(activate),
          m_previouslyActive(redirectImpl.isActive()) {
        if (m_activate == m_previouslyActive) {
            return;
        }
        if (m_activate) {
            m_redirect->activate();
        } else {
            m_redirect->deactivate();
        }
    }

    RedirectGuard(RedirectGuard&& rhs) noexcept
        : m_redirect(rhs.m_redirect),
          m_activate(rhs.m_activate),
          m_previouslyActive(rhs.m_previouslyActive),
          m_moved(false) {
        rhs.m_moved = true;
    }

    RedirectGuard(RedirectGuard const&) = delete;

    ~RedirectGuard() noexcept(false) {
        if (m_moved) {
            return;
        }
        if (m_activate == m_previouslyActive) {
            return;
        }
        if (m_previouslyActive) {
            m_redirect->activate();
        } else {
            m_redirect->deactivate();
        }
    }

    RedirectGuard& operator=(RedirectGuard&& rhs) noexcept {
        m_redirect = rhs.m_redirect;
        m_activate = rhs.m_activate;
        m_previouslyActive = rhs.m_previouslyActive;
        m_moved = false;
        rhs.m_moved = true;
        return *this;
    }

    RedirectGuard& operator=(RedirectGuard const&) = delete;
};

} // namespace Catch

// Mock for OutputRedirect
class MockOutputRedirect : public Catch::OutputRedirect {
public:
    MOCK_METHOD(void, activateImpl, (), (override));
    MOCK_METHOD(void, deactivateImpl, (), (override));
    MOCK_METHOD(std::string, getStdout, (), (override));
    MOCK_METHOD(std::string, getStderr, (), (override));
    MOCK_METHOD(void, clearBuffers, (), (override));
};

class RedirectGuardTest_1079 : public ::testing::Test {
protected:
    MockOutputRedirect mockRedirect;
};

// Test: When activate=true and redirect is not active, it should activate
TEST_F(RedirectGuardTest_1079, ActivateTrueWhenInactive_CallsActivate_1079) {
    ASSERT_FALSE(mockRedirect.isActive());

    EXPECT_CALL(mockRedirect, activateImpl()).Times(1);

    Catch::RedirectGuard guard(true, mockRedirect);

    EXPECT_TRUE(mockRedirect.isActive());
}

// Test: When activate=false and redirect is not active, nothing happens (same state)
TEST_F(RedirectGuardTest_1079, ActivateFalseWhenInactive_NoAction_1079) {
    ASSERT_FALSE(mockRedirect.isActive());

    EXPECT_CALL(mockRedirect, activateImpl()).Times(0);
    EXPECT_CALL(mockRedirect, deactivateImpl()).Times(0);

    Catch::RedirectGuard guard(false, mockRedirect);

    EXPECT_FALSE(mockRedirect.isActive());
}

// Test: When activate=true and redirect is already active, nothing happens (same state)
TEST_F(RedirectGuardTest_1079, ActivateTrueWhenActive_NoAction_1079) {
    EXPECT_CALL(mockRedirect, activateImpl()).Times(1); // only for the manual activate
    mockRedirect.activate();
    ASSERT_TRUE(mockRedirect.isActive());

    // No additional activate/deactivate calls expected
    Catch::RedirectGuard guard(true, mockRedirect);

    EXPECT_TRUE(mockRedirect.isActive());
}

// Test: When activate=false and redirect is active, it should deactivate
TEST_F(RedirectGuardTest_1079, ActivateFalseWhenActive_CallsDeactivate_1079) {
    EXPECT_CALL(mockRedirect, activateImpl()).Times(1);
    mockRedirect.activate();
    ASSERT_TRUE(mockRedirect.isActive());

    EXPECT_CALL(mockRedirect, deactivateImpl()).Times(1);

    Catch::RedirectGuard guard(false, mockRedirect);

    EXPECT_FALSE(mockRedirect.isActive());
}

// Test: Destructor restores state when activate=true changed from inactive
TEST_F(RedirectGuardTest_1079, DestructorRestoresState_ActivatedFromInactive_1079) {
    ASSERT_FALSE(mockRedirect.isActive());

    EXPECT_CALL(mockRedirect, activateImpl()).Times(1);
    EXPECT_CALL(mockRedirect, deactivateImpl()).Times(1);

    {
        Catch::RedirectGuard guard(true, mockRedirect);
        EXPECT_TRUE(mockRedirect.isActive());
    }
    // After destruction, should be deactivated (restored to previous inactive state)
    EXPECT_FALSE(mockRedirect.isActive());
}

// Test: Destructor restores state when activate=false changed from active
TEST_F(RedirectGuardTest_1079, DestructorRestoresState_DeactivatedFromActive_1079) {
    EXPECT_CALL(mockRedirect, activateImpl()).Times(2); // once manual, once on restore
    mockRedirect.activate();
    ASSERT_TRUE(mockRedirect.isActive());

    EXPECT_CALL(mockRedirect, deactivateImpl()).Times(1);

    {
        Catch::RedirectGuard guard(false, mockRedirect);
        EXPECT_FALSE(mockRedirect.isActive());
    }
    // After destruction, should be reactivated (restored to previous active state)
    EXPECT_TRUE(mockRedirect.isActive());
}

// Test: Destructor does nothing when no state change occurred (activate=false, was inactive)
TEST_F(RedirectGuardTest_1079, DestructorNoOpWhenNoStateChange_FalseFalse_1079) {
    ASSERT_FALSE(mockRedirect.isActive());

    EXPECT_CALL(mockRedirect, activateImpl()).Times(0);
    EXPECT_CALL(mockRedirect, deactivateImpl()).Times(0);

    {
        Catch::RedirectGuard guard(false, mockRedirect);
    }

    EXPECT_FALSE(mockRedirect.isActive());
}

// Test: Destructor does nothing when no state change occurred (activate=true, was active)
TEST_F(RedirectGuardTest_1079, DestructorNoOpWhenNoStateChange_TrueTrue_1079) {
    EXPECT_CALL(mockRedirect, activateImpl()).Times(1); // only manual
    mockRedirect.activate();
    ASSERT_TRUE(mockRedirect.isActive());

    EXPECT_CALL(mockRedirect, deactivateImpl()).Times(0);

    {
        Catch::RedirectGuard guard(true, mockRedirect);
    }

    EXPECT_TRUE(mockRedirect.isActive());
}

// Test: Move constructor transfers ownership and original doesn't restore
TEST_F(RedirectGuardTest_1079, MoveConstructor_TransfersOwnership_1079) {
    ASSERT_FALSE(mockRedirect.isActive());

    EXPECT_CALL(mockRedirect, activateImpl()).Times(1);
    EXPECT_CALL(mockRedirect, deactivateImpl()).Times(1);

    {
        Catch::RedirectGuard guard(true, mockRedirect);
        EXPECT_TRUE(mockRedirect.isActive());

        Catch::RedirectGuard movedGuard(std::move(guard));
        // Original guard should be marked as moved
    }
    // Only movedGuard should restore state
    EXPECT_FALSE(mockRedirect.isActive());
}

// Test: Move assignment transfers ownership
TEST_F(RedirectGuardTest_1079, MoveAssignment_TransfersOwnership_1079) {
    ASSERT_FALSE(mockRedirect.isActive());

    EXPECT_CALL(mockRedirect, activateImpl()).Times(1);
    EXPECT_CALL(mockRedirect, deactivateImpl()).Times(1);

    {
        Catch::RedirectGuard guard(true, mockRedirect);
        EXPECT_TRUE(mockRedirect.isActive());

        // Create another guard that does nothing (same state)
        Catch::RedirectGuard guard2(true, mockRedirect);

        guard2 = std::move(guard);
        // guard is now moved, guard2 takes over guard's responsibility
    }
    EXPECT_FALSE(mockRedirect.isActive());
}

// Test: isActive reflects correct state through OutputRedirect
TEST_F(RedirectGuardTest_1079, IsActiveReflectsState_1079) {
    EXPECT_FALSE(mockRedirect.isActive());

    EXPECT_CALL(mockRedirect, activateImpl()).Times(1);
    mockRedirect.activate();
    EXPECT_TRUE(mockRedirect.isActive());

    EXPECT_CALL(mockRedirect, deactivateImpl()).Times(1);
    mockRedirect.deactivate();
    EXPECT_FALSE(mockRedirect.isActive());
}

// Test: Multiple guards in sequence
TEST_F(RedirectGuardTest_1079, MultipleGuardsInSequence_1079) {
    ASSERT_FALSE(mockRedirect.isActive());

    EXPECT_CALL(mockRedirect, activateImpl()).Times(2);
    EXPECT_CALL(mockRedirect, deactivateImpl()).Times(2);

    {
        Catch::RedirectGuard guard1(true, mockRedirect);
        EXPECT_TRUE(mockRedirect.isActive());
    }
    EXPECT_FALSE(mockRedirect.isActive());

    {
        Catch::RedirectGuard guard2(true, mockRedirect);
        EXPECT_TRUE(mockRedirect.isActive());
    }
    EXPECT_FALSE(mockRedirect.isActive());
}

// Test: Nested guards - activate then deactivate inside
TEST_F(RedirectGuardTest_1079, NestedGuards_ActivateThenDeactivate_1079) {
    ASSERT_FALSE(mockRedirect.isActive());

    EXPECT_CALL(mockRedirect, activateImpl()).Times(2); // outer activate + inner restore
    EXPECT_CALL(mockRedirect, deactivateImpl()).Times(2); // inner deactivate + outer restore

    {
        Catch::RedirectGuard outerGuard(true, mockRedirect);
        EXPECT_TRUE(mockRedirect.isActive());

        {
            Catch::RedirectGuard innerGuard(false, mockRedirect);
            EXPECT_FALSE(mockRedirect.isActive());
        }
        // Inner guard destructor should restore to active
        EXPECT_TRUE(mockRedirect.isActive());
    }
    // Outer guard destructor should restore to inactive
    EXPECT_FALSE(mockRedirect.isActive());
}

// Test: Copy constructor is deleted (compile-time, verified by type traits)
TEST_F(RedirectGuardTest_1079, CopyConstructorIsDeleted_1079) {
    EXPECT_FALSE(std::is_copy_constructible<Catch::RedirectGuard>::value);
}

// Test: Copy assignment is deleted
TEST_F(RedirectGuardTest_1079, CopyAssignmentIsDeleted_1079) {
    EXPECT_FALSE(std::is_copy_assignable<Catch::RedirectGuard>::value);
}

// Test: Move constructor is available
TEST_F(RedirectGuardTest_1079, MoveConstructorIsAvailable_1079) {
    EXPECT_TRUE(std::is_move_constructible<Catch::RedirectGuard>::value);
}
