#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/Catch2/src/catch2/interfaces/catch_interfaces_config.hpp"

#include "./TestProjects/Catch2/src/catch2/internal/catch_test_case_registry_impl.hpp"



using namespace Catch;

using ::testing::_;

using ::testing::NiceMock;



class MockConfig : public IConfig {

public:

    MOCK_CONST_METHOD0(runOrder, TestRunOrder());

};



class TestRegistryTest_1019 : public ::testing::Test {

protected:

    TestRegistry registry;

    NiceMock<MockConfig> mockConfig;

};



TEST_F(TestRegistryTest_1019, GetSortedTests_ReturnsEmptyVector_WhenNoTestsRegistered_1019) {

    EXPECT_CALL(mockConfig, runOrder()).Times(1).WillOnce(::testing::Return(TestRunOrder::Declared));

    const auto& sortedTests = registry.getAllTestsSorted(mockConfig);

    EXPECT_EQ(sortedTests.size(), 0);

}



TEST_F(TestRegistryTest_1019, GetSortedTests_ReturnsRegisteredTestsInSameOrder_WhenRunOrderIsDeclared_1019) {

    // Arrange

    Detail::unique_ptr<TestCaseInfo> testInfo1(new TestCaseInfo("Test1", "", "", 0));

    Detail::unique_ptr<ITestInvoker> testInvoker1(new ITestInvoker());

    registry.registerTest(std::move(testInfo1), std::move(testInvoker1));



    Detail::unique_ptr<TestCaseInfo> testInfo2(new TestCaseInfo("Test2", "", "", 0));

    Detail::unique_ptr<ITestInvoker> testInvoker2(new ITestInvoker());

    registry.registerTest(std::move(testInfo2), std::move(testInvoker2));



    EXPECT_CALL(mockConfig, runOrder()).WillOnce(::testing::Return(TestRunOrder::Declared));



    // Act

    const auto& sortedTests = registry.getAllTestsSorted(mockConfig);



    // Assert

    ASSERT_EQ(sortedTests.size(), 2);

    EXPECT_EQ(sortedTests[0]->name, "Test1");

    EXPECT_EQ(sortedTests[1]->name, "Test2");

}



TEST_F(TestRegistryTest_1019, GetSortedTests_ReturnsRegisteredTestsInAlphabeticalOrder_WhenRunOrderIsLexicographic_1019) {

    // Arrange

    Detail::unique_ptr<TestCaseInfo> testInfo1(new TestCaseInfo("Zebra", "", "", 0));

    Detail::unique_ptr<ITestInvoker> testInvoker1(new ITestInvoker());

    registry.registerTest(std::move(testInfo1), std::move(testInvoker1));



    Detail::unique_ptr<TestCaseInfo> testInfo2(new TestCaseInfo("Apple", "", "", 0));

    Detail::unique_ptr<ITestInvoker> testInvoker2(new ITestInvoker());

    registry.registerTest(std::move(testInfo2), std::move(testInvoker2));



    EXPECT_CALL(mockConfig, runOrder()).WillOnce(::testing::Return(TestRunOrder::Lexicographic));



    // Act

    const auto& sortedTests = registry.getAllTestsSorted(mockConfig);



    // Assert

    ASSERT_EQ(sortedTests.size(), 2);

    EXPECT_EQ(sortedTests[0]->name, "Apple");

    EXPECT_EQ(sortedTests[1]->name, "Zebra");

}
