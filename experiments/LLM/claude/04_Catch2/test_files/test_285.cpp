#include "gtest/gtest.h"
#include "gmock/gmock.h"

// We need to include the necessary Catch2 headers to access TestCaseHandle and TestCaseInfo
#include "catch2/catch_test_case_info.hpp"

// Forward declarations and mock for ITestInvoker
// Since ITestInvoker is a dependency, we can mock it
namespace Catch {

// Mock for ITestInvoker if needed
class MockTestInvoker : public ITestInvoker {
public:
    MOCK_METHOD(void, invoke, (), (const, override));
    // Add destructor if ITestInvoker has a virtual destructor
    ~MockTestInvoker() override = default;
};

} // namespace Catch

class TestCaseHandleTest_285 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that getTestCaseInfo returns a reference to the TestCaseInfo provided at construction
TEST_F(TestCaseHandleTest_285, GetTestCaseInfoReturnsCorrectInfo_285) {
    // Create a TestCaseInfo object
    // TestCaseInfo typically needs some parameters; we'll construct one
    Catch::TestCaseInfo info(
        "",                              // _className
        { "test_file.cpp", 10 },         // _lineInfo
        "TestName",                      // _name
        { "tag1" },                      // _tags
        Catch::TestCaseInfo::None        // _properties (or similar)
    );

    Catch::MockTestInvoker invoker;
    Catch::TestCaseHandle handle(&info, &invoker);

    const Catch::TestCaseInfo& retrievedInfo = handle.getTestCaseInfo();

    // Verify it returns the same object
    EXPECT_EQ(&retrievedInfo, &info);
}

// Test that getTestCaseInfo returns consistent results on multiple calls
TEST_F(TestCaseHandleTest_285, GetTestCaseInfoIsConsistent_285) {
    Catch::TestCaseInfo info(
        "",
        { "test_file.cpp", 20 },
        "AnotherTest",
        { "tag2" },
        Catch::TestCaseInfo::None
    );

    Catch::MockTestInvoker invoker;
    Catch::TestCaseHandle handle(&info, &invoker);

    const Catch::TestCaseInfo& first = handle.getTestCaseInfo();
    const Catch::TestCaseInfo& second = handle.getTestCaseInfo();

    EXPECT_EQ(&first, &second);
}

// Test that the name field of TestCaseInfo is accessible through getTestCaseInfo
TEST_F(TestCaseHandleTest_285, GetTestCaseInfoNameAccessible_285) {
    Catch::TestCaseInfo info(
        "",
        { "source.cpp", 42 },
        "MyTestCase",
        {},
        Catch::TestCaseInfo::None
    );

    Catch::MockTestInvoker invoker;
    Catch::TestCaseHandle handle(&info, &invoker);

    const Catch::TestCaseInfo& retrievedInfo = handle.getTestCaseInfo();
    EXPECT_EQ(retrievedInfo.name, "MyTestCase");
}

// Test that getTestCaseInfo preserves tags from TestCaseInfo
TEST_F(TestCaseHandleTest_285, GetTestCaseInfoPreservesTags_285) {
    Catch::TestCaseInfo info(
        "MyClass",
        { "tagged_test.cpp", 5 },
        "TaggedTest",
        { "[unit]", "[fast]" },
        Catch::TestCaseInfo::None
    );

    Catch::MockTestInvoker invoker;
    Catch::TestCaseHandle handle(&info, &invoker);

    const Catch::TestCaseInfo& retrievedInfo = handle.getTestCaseInfo();
    EXPECT_FALSE(retrievedInfo.tags.empty());
}

// Test that invoke calls through to the invoker
TEST_F(TestCaseHandleTest_285, InvokeCallsInvoker_285) {
    Catch::TestCaseInfo info(
        "",
        { "invoke_test.cpp", 1 },
        "InvokeTest",
        {},
        Catch::TestCaseInfo::None
    );

    Catch::MockTestInvoker invoker;
    EXPECT_CALL(invoker, invoke()).Times(1);

    Catch::TestCaseHandle handle(&info, &invoker);
    handle.invoke();
}

// Test that the returned reference is const
TEST_F(TestCaseHandleTest_285, GetTestCaseInfoReturnsConstRef_285) {
    Catch::TestCaseInfo info(
        "",
        { "const_test.cpp", 100 },
        "ConstTest",
        {},
        Catch::TestCaseInfo::None
    );

    Catch::MockTestInvoker invoker;
    Catch::TestCaseHandle handle(&info, &invoker);

    // This should compile - getting a const reference
    const Catch::TestCaseInfo& constRef = handle.getTestCaseInfo();
    EXPECT_EQ(&constRef, &info);
}

// Test with className set
TEST_F(TestCaseHandleTest_285, GetTestCaseInfoWithClassName_285) {
    Catch::TestCaseInfo info(
        "TestFixture",
        { "fixture_test.cpp", 55 },
        "FixtureTest",
        {},
        Catch::TestCaseInfo::None
    );

    Catch::MockTestInvoker invoker;
    Catch::TestCaseHandle handle(&info, &invoker);

    const Catch::TestCaseInfo& retrievedInfo = handle.getTestCaseInfo();
    EXPECT_EQ(retrievedInfo.className, "TestFixture");
}

// Test line info is preserved
TEST_F(TestCaseHandleTest_285, GetTestCaseInfoPreservesLineInfo_285) {
    Catch::SourceLineInfo lineInfo("myfile.cpp", 99);
    Catch::TestCaseInfo info(
        "",
        lineInfo,
        "LineInfoTest",
        {},
        Catch::TestCaseInfo::None
    );

    Catch::MockTestInvoker invoker;
    Catch::TestCaseHandle handle(&info, &invoker);

    const Catch::TestCaseInfo& retrievedInfo = handle.getTestCaseInfo();
    EXPECT_EQ(retrievedInfo.lineInfo.line, 99u);
    EXPECT_STREQ(retrievedInfo.lineInfo.file, "myfile.cpp");
}
