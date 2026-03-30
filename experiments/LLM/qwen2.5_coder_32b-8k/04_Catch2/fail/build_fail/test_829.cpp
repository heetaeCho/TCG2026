#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/Catch2/src/catch2/reporters/catch_reporter_sonarqube.hpp"



using namespace Catch;



class MockSectionNode : public SectionNode {

public:

    MOCK_CONST_METHOD0(children, std::vector<Detail::unique_ptr<SectionNode>>());

};



class MockTestCaseNode : public TestCaseNode {

public:

    MockTestCaseNode() {

        ON_CALL(*this, children).WillByDefault(testing::Return(std::vector<Detail::unique_ptr<SectionNode>>{std::make_unique<MockSectionNode>()}));

        ON_CALL(*this, value).WillByDefault(testing::ReturnRef(mockTestCaseInfo));

    }



    MOCK_CONST_METHOD0(children, std::vector<Detail::unique_ptr<SectionNode>>());

    MOCK_CONST_METHOD0(value, const TestCaseInfo&());



    TestCaseInfo mockTestCaseInfo;

};



class SonarQubeReporterTest_829 : public ::testing::Test {

protected:

    ReporterConfig config;

    SonarQubeReporter reporter{std::move(config)};

};



TEST_F(SonarQubeReporterTest_829, WriteTestCase_CallsWriteSectionWithCorrectParameters_829) {

    MockTestCaseNode testCaseNode;

    TestCaseInfo testCaseInfo;

    ON_CALL(testCaseInfo, okToFail).WillByDefault(testing::Return(false));

    EXPECT_CALL(testCaseNode, value).Times(1).WillOnce(testing::ReturnRef(testCaseInfo));



    EXPECT_CALL(*testCaseNode.children.front(), children).Times(1);

    EXPECT_CALL(reporter, writeSection("", testing::A<const SectionNode&>(), false)).Times(1);



    reporter.writeTestCase(testCaseNode);

}



TEST_F(SonarQubeReporterTest_829, WriteTestCase_CallsWriteSectionWithOkToFailTrue_829) {

    MockTestCaseNode testCaseNode;

    TestCaseInfo testCaseInfo;

    ON_CALL(testCaseInfo, okToFail).WillByDefault(testing::Return(true));

    EXPECT_CALL(testCaseNode, value).Times(1).WillOnce(testing::ReturnRef(testCaseInfo));



    EXPECT_CALL(*testCaseNode.children.front(), children).Times(1);

    EXPECT_CALL(reporter, writeSection("", testing::A<const SectionNode&>(), true)).Times(1);



    reporter.writeTestCase(testCaseNode);

}



TEST_F(SonarQubeReporterTest_829, WriteTestCase_AssertsWhenChildrenSizeNotOne_829) {

    MockTestCaseNode testCaseNode;

    ON_CALL(testCaseNode, children).WillByDefault(testing::Return(std::vector<Detail::unique_ptr<SectionNode>>{}));



    EXPECT_DEATH(reporter.writeTestCase(testCaseNode), "Assertion failed");

}



TEST_F(SonarQubeReporterTest_829, WriteTestCase_HandlesOkToFailFalse_829) {

    MockTestCaseNode testCaseNode;

    TestCaseInfo testCaseInfo;

    ON_CALL(testCaseInfo, okToFail).WillByDefault(testing::Return(false));

    EXPECT_CALL(testCaseNode, value).Times(1).WillOnce(testing::ReturnRef(testCaseInfo));



    EXPECT_CALL(*testCaseNode.children.front(), children).Times(1);

    EXPECT_CALL(reporter, writeSection("", testing::A<const SectionNode&>(), false)).Times(1);



    reporter.writeTestCase(testCaseNode);

}



TEST_F(SonarQubeReporterTest_829, WriteTestCase_HandlesOkToFailTrue_829) {

    MockTestCaseNode testCaseNode;

    TestCaseInfo testCaseInfo;

    ON_CALL(testCaseInfo, okToFail).WillByDefault(testing::Return(true));

    EXPECT_CALL(testCaseNode, value).Times(1).WillOnce(testing::ReturnRef(testCaseInfo));



    EXPECT_CALL(*testCaseNode.children.front(), children).Times(1);

    EXPECT_CALL(reporter, writeSection("", testing::A<const SectionNode&>(), true)).Times(1);



    reporter.writeTestCase(testCaseNode);

}
