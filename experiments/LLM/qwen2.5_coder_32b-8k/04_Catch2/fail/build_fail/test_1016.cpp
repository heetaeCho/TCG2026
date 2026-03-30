#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "catch_amalgamated.cpp"



using namespace Catch;

using namespace Catch::Detail;



class MockITestInvoker : public ITestInvoker {

public:

    MOCK_METHOD(void, invoke, (), (override));

};



class TestRegistryTest_1016 : public ::testing::Test {

protected:

    TestRegistry registry;

    std::unique_ptr<TestCaseInfo> testInfo;

    std::unique_ptr<MockITestInvoker> mockInvoker;



    void SetUp() override {

        testInfo = std::make_unique<TestCaseInfo>("testName", "testDescription", "filePath", 1, nullptr);

        mockInvoker = std::make_unique<MockITestInvoker>();

    }

};



TEST_F(TestRegistryTest_1016, RegisterTestIncreasesHandlesCount_1016) {

    size_t initialSize = registry.m_handles.size();

    registry.registerTest(std::move(testInfo), std::move(mockInvoker));

    EXPECT_EQ(registry.m_handles.size(), initialSize + 1);

}



TEST_F(TestRegistryTest_1016, RegisterTestAddsToViewedTestInfos_1016) {

    size_t initialSize = registry.m_viewed_test_infos.size();

    auto testInfoCopy = std::make_unique<TestCaseInfo>("testName", "testDescription", "filePath", 1, nullptr);

    auto mockInvokerCopy = std::make_unique<MockITestInvoker>();

    registry.registerTest(std::move(testInfoCopy), std::move(mockInvokerCopy));

    EXPECT_EQ(registry.m_viewed_test_infos.size(), initialSize + 1);

}



TEST_F(TestRegistryTest_1016, RegisterTestAddsToOwnedTestInfos_1016) {

    size_t initialSize = registry.m_owned_test_infos.size();

    registry.registerTest(std::move(testInfo), std::move(mockInvoker));

    EXPECT_EQ(registry.m_owned_test_infos.size(), initialSize + 1);

}



TEST_F(TestRegistryTest_1016, RegisterTestAddsToInvokers_1016) {

    size_t initialSize = registry.m_invokers.size();

    registry.registerTest(std::make_unique<TestCaseInfo>("testName", "testDescription", "filePath", 1, nullptr), std::make_unique<MockITestInvoker>());

    EXPECT_EQ(registry.m_invokers.size(), initialSize + 1);

}



TEST_F(TestRegistryTest_1016, GetAllInfosReturnsCorrectSize_1016) {

    registry.registerTest(std::move(testInfo), std::move(mockInvoker));

    EXPECT_EQ(registry.getAllInfos().size(), 1);

}



TEST_F(TestRegistryTest_1016, GetAllTestsReturnsCorrectSize_1016) {

    registry.registerTest(std::make_unique<TestCaseInfo>("testName", "testDescription", "filePath", 1, nullptr), std::make_unique<MockITestInvoker>());

    EXPECT_EQ(registry.getAllTests().size(), 1);

}



TEST_F(TestRegistryTest_1016, GetAllTestsSortedReturnsCorrectSizeWithDefaultConfig_1016) {

    registry.registerTest(std::make_unique<TestCaseInfo>("testName", "testDescription", "filePath", 1, nullptr), std::make_unique<MockITestInvoker>());

    MockIConfig mockConfig;

    EXPECT_EQ(registry.getAllTestsSorted(mockConfig).size(), 1);

}
