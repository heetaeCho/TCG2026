#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "catch_amalgamated.cpp"



using namespace Catch;



class TestRegistryTest_1017 : public ::testing::Test {

protected:

    TestRegistry registry;

};



TEST_F(TestRegistryTest_1017, GetAllInfos_ReturnsEmptyVectorInitially_1017) {

    EXPECT_TRUE(registry.getAllInfos().empty());

}



// Assuming registerTest adds to the internal state and affects getAllInfos

TEST_F(TestRegistryTest_1017, RegisterTest_AddsTestCaseInfoToAllInfos_1017) {

    auto testInfo = Detail::make_unique<TestCaseInfo>("test_name", "description", SourceLineInfo{"filename.cpp", 1});

    auto testInvoker = Detail::make_unique<ITestInvoker>();

    

    registry.registerTest(std::move(testInfo), std::move(testInvoker));

    

    EXPECT_EQ(registry.getAllInfos().size(), 1);

}



TEST_F(TestRegistryTest_1017, GetAllTests_ReturnsEmptyVectorInitially_1017) {

    EXPECT_TRUE(registry.getAllTests().empty());

}



// Assuming registerTest adds to the internal state and affects getAllTests

TEST_F(TestRegistryTest_1017, RegisterTest_AddsTestCaseHandleToAllTests_1017) {

    auto testInfo = Detail::make_unique<TestCaseInfo>("test_name", "description", SourceLineInfo{"filename.cpp", 1});

    auto testInvoker = Detail::make_unique<ITestInvoker>();

    

    registry.registerTest(std::move(testInfo), std::move(testInvoker));

    

    EXPECT_EQ(registry.getAllTests().size(), 1);

}



TEST_F(TestRegistryTest_1017, GetAllTestsSorted_ReturnsEmptyVectorInitially_1017) {

    Mock<IConfig> mockConfig;

    EXPECT_TRUE(registry.getAllTestsSorted(mockConfig).empty());

}



// Assuming registerTest adds to the internal state and affects getAllTestsSorted

TEST_F(TestRegistryTest_1017, RegisterTest_AddsTestCaseHandleToAllTestsSorted_1017) {

    auto testInfo = Detail::make_unique<TestCaseInfo>("test_name", "description", SourceLineInfo{"filename.cpp", 1});

    auto testInvoker = Detail::make_unique<ITestInvoker>();

    

    registry.registerTest(std::move(testInfo), std::move(testInvoker));

    

    Mock<IConfig> mockConfig;

    EXPECT_EQ(registry.getAllTestsSorted(mockConfig).size(), 1);

}
