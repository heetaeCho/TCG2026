#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "catch_interfaces_registry_hub.hpp"

#include "catch_interfaces_config.hpp"

#include "catch_interfaces_testcase.hpp"



using namespace Catch;

using ::testing::Return;

using ::testing::ElementsAre;



class IRegistryHubMock : public IRegistryHub {

public:

    MOCK_CONST_METHOD0(getTestCaseRegistry, const ITestCaseRegistry&());

};



class IConfigMock : public IConfig {

public:

    MOCK_CONST_METHOD0(testSpec, const TestSpec&());

};



class ITestCaseRegistryMock : public ITestCaseRegistry {

public:

    MOCK_CONST_METHOD1(getAllTestsSorted, const std::vector<TestCaseHandle>&(const IConfig& config));

};



TEST_F(IRegistryHubTest_1015, GetTestCaseRegistry_ReturnsValidInstance_1015) {

    IRegistryHubMock registryHubMock;

    EXPECT_CALL(registryHubMock, getTestCaseRegistry()).WillOnce(testing::ReturnRef(ITestCaseRegistryMock()));



    const auto& testCaseRegistry = registryHubMock.getTestCaseRegistry();

}



TEST_F(ITestCaseRegistryTest_1015, GetAllTestsSorted_ReturnsEmptyVectorForNoTests_1015) {

    IConfigMock configMock;

    ITestCaseRegistryMock testCaseRegistryMock;



    EXPECT_CALL(testCaseRegistryMock, getAllTestsSorted(configMock)).WillOnce(Return(std::vector<TestCaseHandle>{}));



    auto result = testCaseRegistryMock.getAllTestsSorted(configMock);

    EXPECT_TRUE(result.empty());

}



TEST_F(ITestCaseRegistryTest_1015, GetAllTestsSorted_ReturnsNonEmptyVectorForSomeTests_1015) {

    IConfigMock configMock;

    ITestCaseRegistryMock testCaseRegistryMock;

    TestCaseHandle testHandle1 = TestCaseHandle();

    TestCaseHandle testHandle2 = TestCaseHandle();



    EXPECT_CALL(testCaseRegistryMock, getAllTestsSorted(configMock)).WillOnce(Return(std::vector<TestCaseHandle>{testHandle1, testHandle2}));



    auto result = testCaseRegistryMock.getAllTestsSorted(configMock);

    EXPECT_THAT(result, ElementsAre(testHandle1, testHandle2));

}



TEST_F(getAllTestCasesSortedTest_1015, ReturnsEmptyVectorWhenNoTests_1015) {

    IConfigMock configMock;

    ITestCaseRegistryMock testCaseRegistryMock;

    IRegistryHubMock registryHubMock;



    EXPECT_CALL(registryHubMock, getTestCaseRegistry()).WillOnce(ReturnRef(testCaseRegistryMock));

    EXPECT_CALL(testCaseRegistryMock, getAllTestsSorted(configMock)).WillOnce(Return(std::vector<TestCaseHandle>{}));



    std::vector<TestCaseHandle> result = getAllTestCasesSorted(configMock);

    EXPECT_TRUE(result.empty());

}



TEST_F(getAllTestCasesSortedTest_1015, ReturnsNonEmptyVectorWhenSomeTestsExist_1015) {

    IConfigMock configMock;

    ITestCaseRegistryMock testCaseRegistryMock;

    IRegistryHubMock registryHubMock;



    TestCaseHandle testHandle1 = TestCaseHandle();

    TestCaseHandle testHandle2 = TestCaseHandle();



    EXPECT_CALL(registryHubMock, getTestCaseRegistry()).WillOnce(ReturnRef(testCaseRegistryMock));

    EXPECT_CALL(testCaseRegistryMock, getAllTestsSorted(configMock)).WillOnce(Return(std::vector<TestCaseHandle>{testHandle1, testHandle2}));



    std::vector<TestCaseHandle> result = getAllTestCasesSorted(configMock);

    EXPECT_THAT(result, ElementsAre(testHandle1, testHandle2));

}
