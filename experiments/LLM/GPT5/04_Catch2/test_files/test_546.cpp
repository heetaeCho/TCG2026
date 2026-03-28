// RedirectGuard_move_assignment_tests_546.cpp
#include <gtest/gtest.h>
#include <gmock/gmock.h>

using ::testing::NiceMock;
using ::testing::StrictMock;
using ::testing::EXPECT_CALL;
using ::testing::Times;

namespace Catch {

// Minimal collaborator interface (based strictly on what the header shows/uses)
struct OutputRedirect {
    virtual ~OutputRedirect() = default;
    virtual bool isActive() const = 0;

    // The destructor/RAII of RedirectGuard might toggle activation.
    // We do not assert on these, but declare them to avoid compilation issues.
    virtual void activate() {}
    virtual void deactivate() {}
};

// Bring in the class under test declarations exactly as the interface implies.
// We do not re-implement any logic here.
class RedirectGuard {
public:
    RedirectGuard(bool activate, OutputRedirect& redirectImpl);
    RedirectGuard(RedirectGuard&& rhs) noexcept;
    RedirectGuard(const RedirectGuard&) = delete;
    RedirectGuard& operator=(const RedirectGuard&) = delete;
    RedirectGuard& operator=(RedirectGuard&& rhs) noexcept;
    ~RedirectGuard() noexcept(false);
};

} // namespace Catch

// -------------------- Mocks --------------------

class MockOutputRedirect : public Catch::OutputRedirect {
public:
    MOCK_METHOD(bool, isActive, (), (const, override));
    // Keep default no-op for (de)activate to be permissive;
    // declare via MOCKs in case the dtor uses them.
    MOCK_METHOD(void, activate, (), (override));
    MOCK_METHOD(void, deactivate, (), (override));
};

// -------------------- Tests --------------------

// Fixture kept simple to make each test explicit about expectations
class RedirectGuard_MoveAssign_Test_546 : public ::testing::Test {};

// [546] Normal: constructing a guard queries isActive() exactly once
TEST_F(RedirectGuard_MoveAssign_Test_546, Ctor_QueriesIsActiveOnce_546) {
    NiceMock<MockOutputRedirect> mock;
    EXPECT_CALL(mock, isActive()).Times(1);

    // activate flag can be either; constructor should still query isActive
    Catch::RedirectGuard g(true, mock);
}

// [546] Move-assign copies observable configuration without extra collaborator calls.
// Specifically, move-assignment should NOT call isActive() on either side.
TEST_F(RedirectGuard_MoveAssign_Test_546, MoveAssign_DoesNotQueryIsActive_546) {
    StrictMock<MockOutputRedirect> leftMock;
    StrictMock<MockOutputRedirect> rightMock;

    // Each construction queries isActive() once.
    EXPECT_CALL(leftMock,  isActive()).Times(1);
    EXPECT_CALL(rightMock, isActive()).Times(1);

    Catch::RedirectGuard lhs(true,  leftMock);
    Catch::RedirectGuard rhs(false, rightMock);

    // After construction, move-assignment should not call isActive on either mock.
    // We do not constrain activate()/deactivate() in this test, because those are not
    // part of the move-assignment operator’s code path we’re validating, and the dtor
    // policy is implementation-defined RAII behavior.
    EXPECT_CALL(leftMock,  isActive()).Times(0);
    EXPECT_CALL(rightMock, isActive()).Times(0);

    auto& ret = (lhs = std::move(rhs));
    EXPECT_EQ(&ret, &lhs); // operator= should return *this
}

// [546] Boundary: self move-assignment should be safe and return *this.
// We do not assert internal state; only that it returns self and makes no extra collaborator queries.
TEST_F(RedirectGuard_MoveAssign_Test_546, SelfMoveAssign_ReturnsSelf_NoExtraQueries_546) {
    StrictMock<MockOutputRedirect> mock;

    // Construction queries once
    EXPECT_CALL(mock, isActive()).Times(1);

    Catch::RedirectGuard g(true, mock);

    // No further queries expected from move-assign itself
    EXPECT_CALL(mock, isActive()).Times(0);

    auto& ret = (g = std::move(g));
    EXPECT_EQ(&ret, &g);
}

// [546] Robustness: move-assigning from an already-moved-from object should not
// trigger extra isActive() calls on either collaborator.
TEST_F(RedirectGuard_MoveAssign_Test_546, MoveAssign_FromMovedFromObject_NoExtraQueries_546) {
    StrictMock<MockOutputRedirect> leftMock;
    StrictMock<MockOutputRedirect> midMock;

    // Each construction queries isActive() once
    EXPECT_CALL(leftMock, isActive()).Times(1);
    EXPECT_CALL(midMock,  isActive()).Times(1);

    Catch::RedirectGuard lhs(true,  leftMock);
    Catch::RedirectGuard mid(false, midMock);

    // First move: mid -> lhs (no queries expected during assignment)
    EXPECT_CALL(leftMock, isActive()).Times(0);
    EXPECT_CALL(midMock,  isActive()).Times(0);
    lhs = std::move(mid);

    // Second move-assign from the (now) moved-from 'mid' should also avoid new queries
    EXPECT_CALL(leftMock, isActive()).Times(0);
    EXPECT_CALL(midMock,  isActive()).Times(0);
    lhs = std::move(mid);
}
