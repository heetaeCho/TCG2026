// File: test_testcasehandle_getinfo_285.cpp
#include <gtest/gtest.h>
#include <gmock/gmock.h>

// The real environment should provide this header.
// If your build already exposes Catch2's real declarations, just keep this include.
// (No internal logic is used beyond what’s observable via the interface.)
#include "catch2/catch_test_case_info.hpp"

using ::testing::StrictMock;
using ::testing::Times;

// ---- Minimal test doubles (interface-only) ----------------------------------
// If your environment already defines these in the included header, you can
// remove the below block. They exist only to make the tests compile in isolation
// without relying on private/internal logic.

namespace Catch {

// Forward declarations in case the real headers aren’t present.
// Replace/remove this section if your build already provides these types.
struct TestCaseInfo {
    // Test code never relies on internal fields; we keep this trivial.
    // Presence of a type is enough to compile and compare addresses.
};

struct ITestInvoker {
    virtual ~ITestInvoker() = default;
    virtual void invoke() const = 0;
    virtual void prepare() const = 0;
    virtual void tearDown() const = 0;
};

class TestCaseHandle {
    TestCaseInfo* m_info;
    ITestInvoker* m_invoker;
public:
    // Interface-only ctor; logic is not asserted in tests except via public API.
    constexpr TestCaseHandle(TestCaseInfo* info, ITestInvoker* invoker)
        : m_info(info), m_invoker(invoker) {}

    // We don’t call these in tests; included only to match the interface.
    void prepareTestCase() const {}
    void tearDownTestCase() const {}
    void invoke() const {}

    // The function under test — taken from the provided partial code.
    constexpr TestCaseInfo const& getTestCaseInfo() const { return *m_info; }
};

} // namespace Catch

// ---- Google Mock for ITestInvoker (external collaborator) -------------------
class MockInvoker : public Catch::ITestInvoker {
public:
    MOCK_METHOD(void, invoke,   (), (const, override));
    MOCK_METHOD(void, prepare,  (), (const, override));
    MOCK_METHOD(void, tearDown, (), (const, override));
};

// ---- Test Fixture -----------------------------------------------------------
class TestCaseHandleTest_285 : public ::testing::Test {
protected:
    Catch::TestCaseInfo info_{};
    StrictMock<MockInvoker> invoker_{};
    // Handle under test
    Catch::TestCaseHandle handle_{ &info_, &invoker_ };
};

// ---- Tests ------------------------------------------------------------------

// Normal operation: returns a const reference to the exact TestCaseInfo.
TEST_F(TestCaseHandleTest_285, GetTestCaseInfo_ReturnsSameObjectAddress_285) {
    // No external interactions expected when just reading info
    // (StrictMock ensures unexpected calls cause test failure).
    const Catch::TestCaseInfo& ref = handle_.getTestCaseInfo();
    // Compare identity by address (observable without peeking internals).
    EXPECT_EQ(&ref, &info_);
}

// Boundary: after copying the handle, accessor still refers to the same object.
TEST_F(TestCaseHandleTest_285, GetTestCaseInfo_FromCopiedHandle_StillSameObject_285) {
    Catch::TestCaseHandle copied = handle_; // copy constructed
    const Catch::TestCaseInfo& ref = copied.getTestCaseInfo();
    EXPECT_EQ(&ref, &info_);
}

// External interactions: accessor must not call the invoker at all.
TEST_F(TestCaseHandleTest_285, GetTestCaseInfo_DoesNotTriggerInvoker_285) {
    // StrictMock + no EXPECT_CALL => any call would fail the test.
    // Simply call the accessor and ensure test completes without unexpected calls.
    (void)handle_.getTestCaseInfo();
    SUCCEED();
}

// Type property: accessor returns a const reference (compile-time check).
TEST_F(TestCaseHandleTest_285, GetTestCaseInfo_ReturnTypeIsConstRef_285) {
    // This is a compile-time property validated at compile step.
    using Ret = decltype(std::declval<const Catch::TestCaseHandle&>().getTestCaseInfo());
    static_assert(std::is_reference<Ret>::value, "Should return a reference");
    static_assert(std::is_const<std::remove_reference_t<Ret>>::value, "Should be const");
    SUCCEED(); // Runtime no-op so the test appears in results.
}
