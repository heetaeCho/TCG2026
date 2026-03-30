#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "catch_amalgamated.hpp"

#include "catch_interfaces_config.hpp"

#include "catch_test_case_info.hpp"



using namespace Catch;

using namespace testing;



class MockIConfig : public IConfig {

public:

    MOCK_CONST_METHOD0(runOrder, TestRunOrder());

    MOCK_CONST_METHOD0(rngSeed, uint32_t());

};



class SortTestsTest_1012 : public ::testing::Test {

protected:

    MockIConfig mockConfig;

    std::vector<TestCaseHandle> unsortedTestCases;



    void SetUp() override {

        TestCaseInfo info1{"test1", "", 0};

        TestCaseInfo info2{"test2", "", 0};

        TestCaseInfo info3{"test3", "", 0};



        ITestInvoker* invoker1 = nullptr;

        ITestInvoker* invoker2 = nullptr;

        ITestInvoker* invoker3 = nullptr;



        unsortedTestCases.emplace_back(&info1, invoker1);

        unsortedTestCases.emplace_back(&info2, invoker2);

        unsortedTestCases.emplace_back(&info3, invoker3);

    }

};



TEST_F(SortTestsTest_1012, DeclaredOrder_1012) {

    EXPECT_CALL(mockConfig, runOrder()).WillOnce(Return(TestRunOrder::Declared));



    std::vector<TestCaseHandle> sorted = sortTests(mockConfig, unsortedTestCases);



    ASSERT_EQ(sorted.size(), 3);

    EXPECT_EQ(sorted[0].getTestCaseInfo().name, "test1");

    EXPECT_EQ(sorted[1].getTestCaseInfo().name, "test2");

    EXPECT_EQ(sorted[2].getTestCaseInfo().name, "test3");

}



TEST_F(SortTestsTest_1012, LexicographicalOrder_1012) {

    EXPECT_CALL(mockConfig, runOrder()).WillOnce(Return(TestRunOrder::LexicographicallySorted));



    std::vector<TestCaseHandle> sorted = sortTests(mockConfig, unsortedTestCases);



    ASSERT_EQ(sorted.size(), 3);

    EXPECT_EQ(sorted[0].getTestCaseInfo().name, "test1");

    EXPECT_EQ(sorted[1].getTestCaseInfo().name, "test2");

    EXPECT_EQ(sorted[2].getTestCaseInfo().name, "test3");

}



TEST_F(SortTestsTest_1012, RandomizedOrder_SameSeed_1012) {

    uint32_t seed = 42;

    EXPECT_CALL(mockConfig, runOrder()).WillOnce(Return(TestRunOrder::Randomized));

    EXPECT_CALL(mockConfig, rngSeed()).WillRepeatedly(Return(seed));



    std::vector<TestCaseHandle> sorted1 = sortTests(mockConfig, unsortedTestCases);

    std::vector<TestCaseHandle> sorted2 = sortTests(mockConfig, unsortedTestCases);



    ASSERT_EQ(sorted1.size(), 3);

    ASSERT_EQ(sorted2.size(), 3);

    EXPECT_TRUE(std::equal(sorted1.begin(), sorted1.end(), sorted2.begin()));

}



TEST_F(SortTestsTest_1012, RandomizedOrder_DifferentSeeds_1012) {

    uint32_t seed1 = 42;

    uint32_t seed2 = 84;

    EXPECT_CALL(mockConfig, runOrder()).WillOnce(Return(TestRunOrder::Randomized));

    EXPECT_CALL(mockConfig, rngSeed())

        .WillOnce(Return(seed1))

        .WillOnce(Return(seed2));



    std::vector<TestCaseHandle> sorted1 = sortTests(mockConfig, unsortedTestCases);

    std::vector<TestCaseHandle> sorted2 = sortTests(mockConfig, unsortedTestCases);



    ASSERT_EQ(sorted1.size(), 3);

    ASSERT_EQ(sorted2.size(), 3);

    EXPECT_FALSE(std::equal(sorted1.begin(), sorted1.end(), sorted2.begin()));

}



TEST_F(SortTestsTest_1012, InvalidRunOrder_ThrowsException_1012) {

    EXPECT_CALL(mockConfig, runOrder()).WillOnce(Return(static_cast<TestRunOrder>(99)));



    EXPECT_THROW(sortTests(mockConfig, unsortedTestCases), std::logic_error);

}
