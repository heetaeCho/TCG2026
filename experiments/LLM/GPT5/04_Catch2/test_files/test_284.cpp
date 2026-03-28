// tests/test_case_handle_test_284.cpp
#include <gtest/gtest.h>
#include <gmock/gmock.h>

using ::testing::InSequence;
using ::testing::Sequence;
using ::testing::StrictMock;
using ::testing::Exactly;

namespace Catch {

// Minimal public-facing declarations to compile tests against the interface.
// These mirror the provided partial headers without re-implementing logic.

class TestCaseInfo {
public:
    // Give it some trivially observable state for identity-only checks.
    // The tests will not depend on contents, only on the object identity.
    const char* name = "dummy";
};

class ITestInvoker {
public:
    virtual ~ITestInvoker() = default;
    virtual void prepareTestCase() = 0;
    virtual void tearDownTestCase() = 0;
    virtual void invoke() = 0;
};

class TestCaseHandle {
public:
    // Constructor & public API per the provided interface.
    constexpr TestCaseHandle(TestCaseInfo* info, ITestInvoker* invoker)
        : m_info(info), m_invoker(invoker) {}

    void prepareTestCase() const;
    void tearDownTestCase() const;
    void invoke() const { m_invoker->invoke(); }
    constexpr TestCaseInfo const& getTestCaseInfo() const;

private:
    TestCaseInfo* m_info;
    ITestInvoker* m_invoker;
};

} // namespace Catch

// ---- Mocks ----
namespace Catch {
class MockTestInvoker : public ITestInvoker {
public:
    MOCK_METHOD(void, prepareTestCase, (), (override));
    MOCK_METHOD(void, tearDownTestCase, (), (override));
    MOCK_METHOD(void, invoke, (), (override));
};
} // namespace Catch

// ---- Test Fixture ----
class TestCaseHandleTest_284 : public ::testing::Test {
protected:
    Catch::TestCaseInfo info_;                 // identity only
    StrictMock<Catch::MockTestInvoker> mock_;  // strict to catch any unexpected calls
};

// ---------- Tests ----------

// Normal operation: invoke forwards exactly once to ITestInvoker::invoke
TEST_F(TestCaseHandleTest_284, Invoke_CallsInvokerOnce_284) {
    Catch::TestCaseHandle handle(&info_, &mock_);
    EXPECT_CALL(mock_, invoke()).Times(Exactly(1));

    handle.invoke();
}

// Normal operation: prepareTestCase forwards exactly once
TEST_F(TestCaseHandleTest_284, PrepareTestCase_ForwardsToInvoker_284) {
    Catch::TestCaseHandle handle(&info_, &mock_);
    EXPECT_CALL(mock_, prepareTestCase()).Times(Exactly(1));

    handle.prepareTestCase();
}

// Normal operation: tearDownTestCase forwards exactly once
TEST_F(TestCaseHandleTest_284, TearDownTestCase_ForwardsToInvoker_284) {
    Catch::TestCaseHandle handle(&info_, &mock_);
    EXPECT_CALL(mock_, tearDownTestCase()).Times(Exactly(1));

    handle.tearDownTestCase();
}

// Boundary/identity: getTestCaseInfo returns a reference to the same object passed in
TEST_F(TestCaseHandleTest_284, GetTestCaseInfo_ReturnsSameObject_284) {
    Catch::TestCaseHandle handle(&info_, &mock_);

    // Check identity via address equality of the returned reference.
    const Catch::TestCaseInfo& got = handle.getTestCaseInfo();
    EXPECT_EQ(&got, &info_);
}

// Interaction order (external interactions): prepare -> invoke -> tearDown in-sequence call forwarding
TEST_F(TestCaseHandleTest_284, Operations_AreForwardedInOrder_284) {
    Catch::TestCaseHandle handle(&info_, &mock_);

    InSequence seq;
    EXPECT_CALL(mock_, prepareTestCase()).Times(Exactly(1));
    EXPECT_CALL(mock_, invoke()).Times(Exactly(1));
    EXPECT_CALL(mock_, tearDownTestCase()).Times(Exactly(1));

    handle.prepareTestCase();
    handle.invoke();
    handle.tearDownTestCase();
}

// Const-correctness: methods callable on const handle and still forward appropriately
TEST_F(TestCaseHandleTest_284, WorksWithConstHandle_284) {
    const Catch::TestCaseHandle handle(&info_, &mock_);

    EXPECT_CALL(mock_, prepareTestCase()).Times(Exactly(1));
    EXPECT_CALL(mock_, invoke()).Times(Exactly(1));
    EXPECT_CALL(mock_, tearDownTestCase()).Times(Exactly(1));

    handle.prepareTestCase();
    handle.invoke();
    handle.tearDownTestCase();

    // Also verify getTestCaseInfo on const
    const Catch::TestCaseInfo& got = handle.getTestCaseInfo();
    EXPECT_EQ(&got, &info_);
}
