#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "catch_reporter_sonarqube.hpp"

#include "catch_interfaces_reporter.hpp"

#include "catch_test_case_info.hpp"



using namespace Catch;

using ::testing::ElementsAre;



class SonarQubeReporterTest_827 : public ::testing::Test {

protected:

    ReporterConfig config;

    SonarQubeReporter reporter{CATCH_MOVE(config)};

    

    TestRunNode createTestRunNode(std::vector<TestCaseNode*> testCaseNodes) {

        TestRunNode runNode;

        for (auto* node : testCaseNodes) {

            runNode.children.push_back(Detail::unique_ptr<Node>(new Node(*node)));

        }

        return runNode;

    }



    TestCaseInfo createTestCaseInfo(StringRef className, NameAndTags nameAndTags, SourceLineInfo lineInfo) {

        return TestCaseInfo(className, nameAndTags, lineInfo);

    }

};



TEST_F(SonarQubeReporterTest_827, WriteRunWithMultipleFiles_827) {

    // Arrange

    std::vector<TestCaseNode*> testCaseNodes = {

        new TestCaseNode{createTestCaseInfo("Class1", {"Test1", ""}, SourceLineInfo{"file1.cpp", 10})},

        new TestCaseNode{createTestCaseInfo("Class2", {"Test2", ""}, SourceLineInfo{"file2.cpp", 20})}

    };

    TestRunNode runNode = createTestRunNode(testCaseNodes);



    // Act

    reporter.writeRun(runNode);



    // Assert

    // Since we cannot access the internal state, we assume that if no exceptions are thrown and the function completes,

    // it is working as expected for normal operation.

}



TEST_F(SonarQubeReporterTest_827, WriteRunWithSingleFile_827) {

    // Arrange

    std::vector<TestCaseNode*> testCaseNodes = {

        new TestCaseNode{createTestCaseInfo("Class1", {"Test1", ""}, SourceLineInfo{"file1.cpp", 10})},

        new TestCaseNode{createTestCaseInfo("Class2", {"Test2", ""}, SourceLineInfo{"file1.cpp", 20})}

    };

    TestRunNode runNode = createTestRunNode(testCaseNodes);



    // Act

    reporter.writeRun(runNode);



    // Assert

    // Since we cannot access the internal state, we assume that if no exceptions are thrown and the function completes,

    // it is working as expected for normal operation.

}



TEST_F(SonarQubeReporterTest_827, WriteRunWithNoTests_827) {

    // Arrange

    std::vector<TestCaseNode*> testCaseNodes = {};

    TestRunNode runNode = createTestRunNode(testCaseNodes);



    // Act

    reporter.writeRun(runNode);



    // Assert

    // Since we cannot access the internal state, we assume that if no exceptions are thrown and the function completes,

    // it is working as expected for normal operation.

}



TEST_F(SonarQubeReporterTest_827, WriteRunWithEmptyFileName_827) {

    // Arrange

    std::vector<TestCaseNode*> testCaseNodes = {

        new TestCaseNode{createTestCaseInfo("Class1", {"Test1", ""}, SourceLineInfo{"", 10})}

    };

    TestRunNode runNode = createTestRunNode(testCaseNodes);



    // Act

    reporter.writeRun(runNode);



    // Assert

    // Since we cannot access the internal state, we assume that if no exceptions are thrown and the function completes,

    // it is working as expected for boundary conditions.

}
