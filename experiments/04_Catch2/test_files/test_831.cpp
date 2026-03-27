#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "catch2/reporters/catch_reporter_sonarqube.hpp"

#include "catch2/internal/catch_assertionhandler.hpp"



using namespace Catch;

using namespace testing;



class MockAssertionStats : public AssertionStats {

public:

    MockAssertionStats() : AssertionStats(AssertionResult(), "", SourceLineInfo("", 0)) {}

};



class SonarQubeReporterTest_831 : public Test {

protected:

    NiceMock<MockFunction<void(const AssertionStats&, bool)>> mockWriteAssertion;

    ReporterConfig config;

    SonarQubeReporter reporter{CATCH_MOVE(config)};

    SectionNode sectionNode;



    void SetUp() override {

        ON_CALL(mockWriteAssertion, Call(_, _)).WillByDefault(Invoke([](const AssertionStats& stats, bool okToFail) {}));

    }



    void addAssertionToSection(const AssertionStats& assertion, bool isOk = true) {

        Detail::AssertionOrBenchmarkResult result(assertion);

        sectionNode.assertionsAndBenchmarks.push_back(result);

    }

};



TEST_F(SonarQubeReporterTest_831, WriteAssertions_CallsWriteAssertionForAssertions_831) {

    MockAssertionStats assertion;

    addAssertionToSection(assertion);



    EXPECT_CALL(mockWriteAssertion, Call(Ref(assertion), Eq(true))).Times(1);

    reporter.writeAssertions(sectionNode, true);

}



TEST_F(SonarQubeReporterTest_831, WriteAssertions_NoAssertionsDoesNothing_831) {

    EXPECT_CALL(mockWriteAssertion, Call(_, _)).Times(0);

    reporter.writeAssertions(sectionNode, true);

}



TEST_F(SonarQubeReporterTest_831, WriteAssertions_MultipleAssertionsCallsWriteAssertionEach_831) {

    MockAssertionStats assertion1;

    MockAssertionStats assertion2;



    addAssertionToSection(assertion1);

    addAssertionToSection(assertion2);



    EXPECT_CALL(mockWriteAssertion, Call(Ref(assertion1), Eq(true))).Times(1);

    EXPECT_CALL(mockWriteAssertion, Call(Ref(assertion2), Eq(true))).Times(1);

    reporter.writeAssertions(sectionNode, true);

}



TEST_F(SonarQubeReporterTest_831, WriteAssertions_OkToFailFlagPassedCorrectly_831) {

    MockAssertionStats assertion;



    addAssertionToSection(assertion);



    EXPECT_CALL(mockWriteAssertion, Call(Ref(assertion), Eq(false))).Times(1);

    reporter.writeAssertions(sectionNode, false);

}
