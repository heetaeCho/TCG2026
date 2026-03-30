// RedirectGuardTests_545.cpp
#include <gtest/gtest.h>
#include <gmock/gmock.h>

using ::testing::_;
using ::testing::AnyNumber;
using ::testing::NiceMock;
using ::testing::StrictMock;
using ::testing::Expectation;
using ::testing::InSequence;

// === Minimal interfaces, matching the provided headers ===
namespace Catch {

class OutputRedirect {
public:
    virtual ~OutputRedirect() = default;

    // Public observable interface we can call/verify around:
    bool isActive() const;      // non-virtual (implementation-owned)
    void activate();            // non-virtual, calls virtual activateImpl()
    void deactivate();          // non-virtual, calls virtual deactivateImpl()

    // Other public API (not needed for these tests):
    virtual std::string getStdout();
    virtual std::string getStderr();
    virtual void clearBuffers();

private:
    virtual void activateImpl();    // will be mocked
    virtual void deactivateImpl();  // will be mocked
};

// RAII guard under test (ctor/dtor/operator as per prompt)
class RedirectGuard {
public:
    RedirectGuard(bool activate, OutputRedirect& redirectImpl);
    RedirectGuard(RedirectGuard&& rhs) noexcept;
    RedirectGuard(RedirectGuard const&) = delete;
    RedirectGuard& operator=(RedirectGuard const&) = delete;
    RedirectGuard& operator=(RedirectGuard&& rhs) noexcept;
    ~RedirectGuard() noexcept(false);
};

} // namespace Catch

// === Test doubles ===
class MockOutputRedirect : public Catch::OutputRedirect {
public:
    MOCK_METHOD(void, activateImpl, (), (override));
    MOCK_METHOD(void, deactivateImpl, (), (override));
    // We don't need to mock getStdout/getStderr/clearBuffers for these tests.
};

// === Helper notes for tests ===
// - We control the *previouslyActive* state captured by RedirectGuard's ctor
//   by calling mock.activate()/mock.deactivate() BEFORE constructing the guard.
// - We only assert effects at DESTRUCTION time. To avoid coupling to potential
//   ctor-side effects, we clear any call history/expectations AFTER constructing
//   the guard and BEFORE destroying it.

// ------------------------------------------------------------
// When previouslyActive == activate, the destructor should do nothing.
// ------------------------------------------------------------
TEST(RedirectGuardTest_545, NoChange_WhenActivateMatchesPreviouslyActive_545) {
    NiceMock<MockOutputRedirect> mock;

    // Make redirect active first so previouslyActive==true is captured by the guard.
    // These calls will route to activateImpl(); allow any number during setup.
    ON_CALL(mock, activateImpl()).WillByDefault([]{});
    ON_CALL(mock, deactivateImpl()).WillByDefault([]{});
    mock.activate();
    ASSERT_TRUE(mock.isActive());  // observable precondition via public API

    // Construct guard with activate==true; previouslyActive==true
    auto* guard = new Catch::RedirectGuard(/*activate*/true, mock);

    // Ignore any ctor-time effects; focus assertions on dtor-time only.
    ::testing::Mock::VerifyAndClearExpectations(&mock);

    // At destruction, with activate==previouslyActive, no (de)activation should occur.
    EXPECT_CALL(mock, activateImpl()).Times(0);
    EXPECT_CALL(mock, deactivateImpl()).Times(0);

    delete guard;  // triggers ~RedirectGuard
}

// ------------------------------------------------------------
// If previouslyActive==false and activate==true, dtor should DEACTIVATE.
// ------------------------------------------------------------
TEST(RedirectGuardTest_545, Deactivates_OnDestroy_WhenActivateTrueAndWasInactive_545) {
    NiceMock<MockOutputRedirect> mock;
    ON_CALL(mock, activateImpl()).WillByDefault([]{});
    ON_CALL(mock, deactivateImpl()).WillByDefault([]{});

    // Ensure previouslyActive == false
    mock.deactivate();
    ASSERT_FALSE(mock.isActive());

    auto* guard = new Catch::RedirectGuard(/*activate*/true, mock);

    ::testing::Mock::VerifyAndClearExpectations(&mock);

    // On destruction: because activate(true) != previouslyActive(false) -> call deactivate()
    EXPECT_CALL(mock, deactivateImpl()).Times(1);
    EXPECT_CALL(mock, activateImpl()).Times(0);

    delete guard;  // expect one deactivateImpl at dtor
}

// ------------------------------------------------------------
// If previouslyActive==true and activate==false, dtor should ACTIVATE.
// ------------------------------------------------------------
TEST(RedirectGuardTest_545, Activates_OnDestroy_WhenActivateFalseAndWasActive_545) {
    NiceMock<MockOutputRedirect> mock;
    ON_CALL(mock, activateImpl()).WillByDefault([]{});
    ON_CALL(mock, deactivateImpl()).WillByDefault([]{});

    // Ensure previouslyActive == true
    mock.activate();
    ASSERT_TRUE(mock.isActive());

    auto* guard = new Catch::RedirectGuard(/*activate*/false, mock);

    ::testing::Mock::VerifyAndClearExpectations(&mock);

    // On destruction: because activate(false) != previouslyActive(true) -> call activate()
    EXPECT_CALL(mock, activateImpl()).Times(1);
    EXPECT_CALL(mock, deactivateImpl()).Times(0);

    delete guard;  // expect one activateImpl at dtor
}

// ------------------------------------------------------------
// Move-constructed guard: moved-from dtor should do NOTHING,
// moved-to dtor should perform the appropriate action once.
// ------------------------------------------------------------
TEST(RedirectGuardTest_545, MoveConstruction_MovedFromDoesNothing_MovedToPerformsOneAction_545) {
    NiceMock<MockOutputRedirect> mock;
    ON_CALL(mock, activateImpl()).WillByDefault([]{});
    ON_CALL(mock, deactivateImpl()).WillByDefault([]{});

    // previouslyActive == false to make the dtor path unambiguous with activate==true
    mock.deactivate();
    ASSERT_FALSE(mock.isActive());

    // Construct original guard (would capture previouslyActive==false)
    Catch::RedirectGuard g1(/*activate*/true, mock);

    // Move-construct g2 from g1. After this, only g2 should be "active" guard object.
    Catch::RedirectGuard g2(std::move(g1));

    // Clear any ctor-time effects. From now on we only care about dtor effects.
    ::testing::Mock::VerifyAndClearExpectations(&mock);

    // At scope exit:
    // - g2 dtor should call deactivate() exactly once (activate==true, prev==false)
    // - g1 dtor should do NOTHING because it's moved-from
    EXPECT_CALL(mock, deactivateImpl()).Times(1);
    EXPECT_CALL(mock, activateImpl()).Times(0);
    // (If g1 erroneously triggers anything in its dtor, that would be an unexpected extra call and fail the test.)
}
