// File: tests/redirect_guard_tests_1079.cpp

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "catch_output_redirect.hpp" // Adjust include path to your tree

using ::testing::_;
using ::testing::Exactly;
using ::testing::Times;

namespace Catch {

// A mock OutputRedirect. We override only the virtual impl hooks that the
// public activate()/deactivate() are expected to call.
// NOTE: RedirectGuard calls activate()/deactivate(), which should, in turn,
//       dispatch to these impl methods. We do NOT rely on private state.
class MockOutputRedirect : public OutputRedirect {
public:
    // The interface shows these as virtual (private in the header snippet),
    // but C++ allows overriding private virtuals in a derived class.
    MOCK_METHOD(void, activateImpl, (), (override));
    MOCK_METHOD(void, deactivateImpl, (), (override));

    // Provide harmless overrides to satisfy the full polymorphic interface.
    MOCK_METHOD(std::string, getStdout, (), (override));
    MOCK_METHOD(std::string, getStderr, (), (override));
    MOCK_METHOD(void, clearBuffers, (), (override));

    // Virtual dtor needed because base declares it virtual.
    ~MockOutputRedirect() override = default;
};

} // namespace Catch

// ---- Test fixture ----------------------------------------------------------

class RedirectGuardTest_1079 : public ::testing::Test {
protected:
    Catch::MockOutputRedirect mock;
};

// ------------------------- Tests -------------------------------------------

// Previously INACTIVE -> request ACTIVATE => calls activateImpl exactly once
// and (observably) ends active via public API.
TEST_F(RedirectGuardTest_1079, InactiveToActivate_CallsActivateOnce_1079) {
    using namespace Catch;

    // Ensure known starting state: inactive
    // If your OutputRedirect starts inactive by default, this is a no-op;
    // otherwise, explicitly deactivate via the public API.
    // We do not assert any expectations for this setup step.
    mock.deactivate();

    // Expect exactly one activation through the impl (triggered by the guard)
    EXPECT_CALL(mock, activateImpl()).Times(Exactly(1));
    EXPECT_CALL(mock, deactivateImpl()).Times(0);

    // Constructing the guard should perform the transition
    RedirectGuard guard(/*activate*/true, mock);

    // Optional observable check via public API (black-box observable behavior)
    // If the underlying OutputRedirect honors activate(), it should now be active.
    EXPECT_TRUE(mock.isActive());
}

// Previously INACTIVE -> request DEACTIVATE => no calls (already desired state)
TEST_F(RedirectGuardTest_1079, InactiveToDeactivate_NoCalls_1079) {
    using namespace Catch;

    // Ensure starting inactive
    mock.deactivate();
    ::testing::Mock::VerifyAndClearExpectations(&mock); // clear any incidental calls

    EXPECT_CALL(mock, activateImpl()).Times(0);
    EXPECT_CALL(mock, deactivateImpl()).Times(0);

    RedirectGuard guard(/*activate*/false, mock);

    // Still inactive per observable API
    EXPECT_FALSE(mock.isActive());
}

// Previously ACTIVE -> request ACTIVATE => no calls (already desired state)
TEST_F(RedirectGuardTest_1079, ActiveToActivate_NoCalls_1079) {
    using namespace Catch;

    // Set initial state to active using the public API.
    // This will call activateImpl() once; clear expectations after setup.
    EXPECT_CALL(mock, activateImpl()).Times(Exactly(1));
    mock.activate();
    ::testing::Mock::VerifyAndClearExpectations(&mock);

    // Now constructing the guard with activate=true should do nothing.
    EXPECT_CALL(mock, activateImpl()).Times(0);
    EXPECT_CALL(mock, deactivateImpl()).Times(0);

    RedirectGuard guard(/*activate*/true, mock);

    EXPECT_TRUE(mock.isActive());
}

// Previously ACTIVE -> request DEACTIVATE => calls deactivateImpl exactly once
TEST_F(RedirectGuardTest_1079, ActiveToDeactivate_CallsDeactivateOnce_1079) {
    using namespace Catch;

    // Ensure starting active
    EXPECT_CALL(mock, activateImpl()).Times(Exactly(1));
    mock.activate();
    ::testing::Mock::VerifyAndClearExpectations(&mock);

    EXPECT_CALL(mock, deactivateImpl()).Times(Exactly(1));
    EXPECT_CALL(mock, activateImpl()).Times(0);

    RedirectGuard guard(/*activate*/false, mock);

    EXPECT_FALSE(mock.isActive());
}

