// File: test_testcasehandle_teardown_283.cpp

#include <gtest/gtest.h>
#include <gmock/gmock.h>

// Use the real headers if available in your project layout.
// If paths differ, adjust includes accordingly.
#include "catch2/catch_test_case_info.hpp"
#include "catch2/interfaces/catch_interfaces_test_invoker.hpp"

using ::testing::StrictMock;
using ::testing::EXPECT_CALL;
using ::testing::Times;

namespace Catch {

// GMock for the external collaborator ITestInvoker.
// We only mock public virtual functions exposed by the interface.
class MockTestInvoker : public ITestInvoker {
public:
    MOCK_METHOD(void, prepareTestCase, (), (override));
    MOCK_METHOD(void, tearDownTestCase, (), (override));
    // Catch2's invoker::invoke() is const; match that to avoid signature mismatch.
    MOCK_METHOD(void, invoke, (), (const, override));
    // Ensure a virtual dtor exists (base already has virtual dtor).
    ~MockTestInvoker() override = default;
};

} // namespace Catch

// Test fixture. Keeps naming consistent and embeds TEST_ID in the fixture name.
class TestCaseHandleTest_283 : public ::testing::Test {
protected:
    // Minimal pointer for TestCaseInfo; TestCaseHandle only stores it.
    // We don't depend on any of its internals.
    Catch::TestCaseInfo* info_ = nullptr;

    StrictMock<Catch::MockTestInvoker> mockInvoker_;
    // Create the SUT with provided interface (black-box).
    Catch::TestCaseHandle sut_{info_, &mockInvoker_};
};

// [Normal operation] Single call should delegate exactly once to ITestInvoker::tearDownTestCase.
TEST_F(TestCaseHandleTest_283, TearDown_DelegatesToInvokerOnce_283) {
    EXPECT_CALL(mockInvoker_, tearDownTestCase()).Times(1);

    sut_.tearDownTestCase();
}

// [Boundary] Multiple calls should delegate one-for-one (idempotence not assumed; just interaction check).
TEST_F(TestCaseHandleTest_283, TearDown_CanBeCalledMultipleTimes_283) {
    EXPECT_CALL(mockInvoker_, tearDownTestCase()).Times(2);

    sut_.tearDownTestCase();
    sut_.tearDownTestCase();
}

// [Interaction safety] Calling tearDown should not invoke unrelated invoker methods.
TEST_F(TestCaseHandleTest_283, TearDown_DoesNotCallOtherInvokerMethods_283) {
    EXPECT_CALL(mockInvoker_, prepareTestCase()).Times(0);
    EXPECT_CALL(mockInvoker_, invoke()).Times(0);
    EXPECT_CALL(mockInvoker_, tearDownTestCase()).Times(1);

    sut_.tearDownTestCase();
}

// [Const-correctness observable] Method is callable via const reference and still delegates.
TEST_F(TestCaseHandleTest_283, TearDown_ConstCall_Delegates_283) {
    const Catch::TestCaseHandle& cref = sut_;
    EXPECT_CALL(mockInvoker_, tearDownTestCase()).Times(1);

    cref.tearDownTestCase();
}
