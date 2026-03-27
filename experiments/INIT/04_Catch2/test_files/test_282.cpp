// File: test_testcasehandle_282.cpp

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "catch2/catch_test_case_info.hpp"
#include "catch2/interfaces/catch_interfaces_test_invoker.hpp"

using ::testing::InSequence;
using ::testing::StrictMock;
using ::testing::Expectation;

// Minimal visible TestCaseInfo usage: we only need identity checks.
namespace Catch {
    // If your real TestCaseInfo is available via the included header,
    // remove this forward-decl block. Kept harmless for clarity.
    struct TestCaseInfo; // forward decl (do not inspect internals)
}

// Mock for the external collaborator.
// Signatures follow the provided interface (invoke() is const; others are non-const).
namespace Catch {
class MockInvoker_282 : public ITestInvoker {
public:
    MOCK_METHOD(void, prepareTestCase, (), (override));
    MOCK_METHOD(void, tearDownTestCase, (), (override));
    MOCK_METHOD(void, invoke, (), (const, override));
    // Ensure a virtual dtor is available through the base.
    virtual ~MockInvoker_282() = default;
};
} // namespace Catch

// A trivially constructible TestCaseInfo stand-in for address identity checks
// (only used if your real TestCaseInfo is not includable here).
// If the real type is available, delete this and use the real one.
namespace Catch {
struct TestCaseInfo {
    // No fields required; we only compare addresses via the public API.
};
} // namespace Catch

class TestCaseHandleTest_282 : public ::testing::Test {
protected:
    Catch::TestCaseInfo info_{};
    StrictMock<Catch::MockInvoker_282> mock_{};

    // Helper to build the handle under test.
    Catch::TestCaseHandle makeHandle() {
        return Catch::TestCaseHandle(&info_, &mock_);
    }
};

// --- Tests ---

// Verifies that TestCaseHandle::prepareTestCase() forwards the call to ITestInvoker::prepareTestCase().
TEST_F(TestCaseHandleTest_282, Prepare_ForwardsToInvoker_282) {
    auto handle = makeHandle();
    EXPECT_CALL(mock_, prepareTestCase()).Times(1);
    handle.prepareTestCase();
}

// Verifies that TestCaseHandle::tearDownTestCase() forwards the call to ITestInvoker::tearDownTestCase().
TEST_F(TestCaseHandleTest_282, TearDown_ForwardsToInvoker_282) {
    auto handle = makeHandle();
    EXPECT_CALL(mock_, tearDownTestCase()).Times(1);
    handle.tearDownTestCase();
}

// Verifies that TestCaseHandle::invoke() forwards the call to ITestInvoker::invoke().
TEST_F(TestCaseHandleTest_282, Invoke_ForwardsToInvoker_282) {
    auto handle = makeHandle();
    EXPECT_CALL(mock_, invoke()).Times(1);
    handle.invoke();
}

// Verifies that getTestCaseInfo() returns a const reference to the same TestCaseInfo provided at construction.
TEST_F(TestCaseHandleTest_282, GetTestCaseInfo_ReturnsSameReference_282) {
    const auto handle = makeHandle();
    // No expectations on mock — this accessor should not touch the invoker.
    const Catch::TestCaseInfo& returned = handle.getTestCaseInfo();
    // Validate identity via address comparison (observable through the public ref).
    EXPECT_EQ(&returned, &info_);
}

// Verifies repeated calls (normal/typical usage) keep forwarding correctly and preserve ordering.
TEST_F(TestCaseHandleTest_282, MultipleCalls_SequenceIsForwarded_282) {
    auto handle = makeHandle();

    InSequence seq; // enforce ordering
    EXPECT_CALL(mock_, prepareTestCase()).Times(2);
    EXPECT_CALL(mock_, invoke()).Times(2);
    EXPECT_CALL(mock_, tearDownTestCase()).Times(2);

    handle.prepareTestCase();
    handle.prepareTestCase();

    handle.invoke();
    handle.invoke();

    handle.tearDownTestCase();
    handle.tearDownTestCase();
}

// Verifies public methods are callable on a const TestCaseHandle and still forward to the invoker.
// (Covers const-correctness of the handle’s API as observable behavior.)
TEST_F(TestCaseHandleTest_282, ConstHandle_MethodsStillForward_282) {
    const auto handle = makeHandle();
    // We need a non-const pointer to set expectations; the handle itself is const.
    EXPECT_CALL(mock_, prepareTestCase()).Times(1);
    EXPECT_CALL(mock_, invoke()).Times(1);
    EXPECT_CALL(mock_, tearDownTestCase()).Times(1);

    handle.prepareTestCase();
    handle.invoke();
    handle.tearDownTestCase();
}
