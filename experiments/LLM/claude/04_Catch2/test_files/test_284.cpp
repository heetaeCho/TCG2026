#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "catch2/catch_test_case_info.hpp"
#include "catch2/interfaces/catch_interfaces_test_invoker.hpp"

using namespace Catch;
using ::testing::_;
using ::testing::Exactly;

// Mock for ITestInvoker
class MockTestInvoker : public ITestInvoker {
public:
    MOCK_METHOD(void, invoke, (), (const, override));
    MOCK_METHOD(void, prepareTestCase, (), (override));
    MOCK_METHOD(void, tearDownTestCase, (), (override));
    ~MockTestInvoker() override = default;
};

class TestCaseHandleTest_284 : public ::testing::Test {
protected:
    void SetUp() override {
        mockInvoker = new MockTestInvoker();
    }

    void TearDown() override {
        delete mockInvoker;
    }

    MockTestInvoker* mockInvoker = nullptr;
};

// Test that invoke() delegates to m_invoker->invoke()
TEST_F(TestCaseHandleTest_284, InvokeDelegatesToInvoker_284) {
    TestCaseInfo info("", {"", 0}, "", "", {}, {});
    TestCaseHandle handle(&info, mockInvoker);

    EXPECT_CALL(*mockInvoker, invoke()).Times(Exactly(1));

    handle.invoke();
}

// Test that prepareTestCase() delegates to m_invoker->prepareTestCase()
TEST_F(TestCaseHandleTest_284, PrepareTestCaseDelegatesToInvoker_284) {
    TestCaseInfo info("", {"", 0}, "", "", {}, {});
    TestCaseHandle handle(&info, mockInvoker);

    EXPECT_CALL(*mockInvoker, prepareTestCase()).Times(Exactly(1));

    handle.prepareTestCase();
}

// Test that tearDownTestCase() delegates to m_invoker->tearDownTestCase()
TEST_F(TestCaseHandleTest_284, TearDownTestCaseDelegatesToInvoker_284) {
    TestCaseInfo info("", {"", 0}, "", "", {}, {});
    TestCaseHandle handle(&info, mockInvoker);

    EXPECT_CALL(*mockInvoker, tearDownTestCase()).Times(Exactly(1));

    handle.tearDownTestCase();
}

// Test that getTestCaseInfo() returns a reference to the TestCaseInfo passed in constructor
TEST_F(TestCaseHandleTest_284, GetTestCaseInfoReturnsCorrectInfo_284) {
    TestCaseInfo info("test_name", {"file.cpp", 42}, "tag_string", "description", {}, {});
    TestCaseHandle handle(&info, mockInvoker);

    const TestCaseInfo& retrieved = handle.getTestCaseInfo();
    EXPECT_EQ(&retrieved, &info);
}

// Test that getTestCaseInfo() returns consistent reference across multiple calls
TEST_F(TestCaseHandleTest_284, GetTestCaseInfoIsConsistent_284) {
    TestCaseInfo info("another_test", {"another_file.cpp", 100}, "", "", {}, {});
    TestCaseHandle handle(&info, mockInvoker);

    const TestCaseInfo& first = handle.getTestCaseInfo();
    const TestCaseInfo& second = handle.getTestCaseInfo();
    EXPECT_EQ(&first, &second);
}

// Test that invoke can be called multiple times
TEST_F(TestCaseHandleTest_284, InvokeCanBeCalledMultipleTimes_284) {
    TestCaseInfo info("", {"", 0}, "", "", {}, {});
    TestCaseHandle handle(&info, mockInvoker);

    EXPECT_CALL(*mockInvoker, invoke()).Times(Exactly(3));

    handle.invoke();
    handle.invoke();
    handle.invoke();
}

// Test the constexpr constructor with valid pointers
TEST_F(TestCaseHandleTest_284, ConstructorAcceptsValidPointers_284) {
    TestCaseInfo info("ctor_test", {"test.cpp", 1}, "", "", {}, {});
    TestCaseHandle handle(&info, mockInvoker);

    // Simply verify the handle was constructed and getTestCaseInfo works
    EXPECT_EQ(&handle.getTestCaseInfo(), &info);
}

// Test the full lifecycle: prepare, invoke, teardown
TEST_F(TestCaseHandleTest_284, FullLifecycle_284) {
    TestCaseInfo info("lifecycle_test", {"lifecycle.cpp", 10}, "", "", {}, {});
    TestCaseHandle handle(&info, mockInvoker);

    {
        ::testing::InSequence seq;
        EXPECT_CALL(*mockInvoker, prepareTestCase()).Times(1);
        EXPECT_CALL(*mockInvoker, invoke()).Times(1);
        EXPECT_CALL(*mockInvoker, tearDownTestCase()).Times(1);
    }

    handle.prepareTestCase();
    handle.invoke();
    handle.tearDownTestCase();
}

// Test that getTestCaseInfo returns info with correct name
TEST_F(TestCaseHandleTest_284, GetTestCaseInfoPreservesName_284) {
    TestCaseInfo info("my_special_test", {"source.cpp", 55}, "", "", {}, {});
    TestCaseHandle handle(&info, mockInvoker);

    const TestCaseInfo& retrieved = handle.getTestCaseInfo();
    EXPECT_EQ(retrieved.name, "my_special_test");
}
