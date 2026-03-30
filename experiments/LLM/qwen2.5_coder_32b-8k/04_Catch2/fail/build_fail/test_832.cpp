#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "catch_reporter_sonarqube.hpp"

#include "catch_assertion_result.hpp"

#include "catch_interfaces_reporter.hpp"



using namespace Catch;

using ::testing::_;

using ::testing::MockFunction;



class MockXmlWriter : public XmlWriter {

public:

    MockXmlWriter(std::ostream& os) : XmlWriter(os) {}



    MOCK_METHOD1(startElement, XmlWriter&(const std::string & name));

    MOCK_METHOD2(writeAttribute, XmlWriter&(StringRef name, StringRef attribute));

    MOCK_METHOD2(writeText, XmlWriter&(StringRef text, XmlFormatting fmt));

};



class MockAssertionResult : public AssertionResult {

public:

    MockAssertionResult(AssertionInfo const& info, AssertionResultData&& data) 

        : AssertionResult(info, CATCH_MOVE(data)) {}



    MOCK_CONST_METHOD0(isOk, bool());

    MOCK_CONST_METHOD0(getResultType, ResultWas::OfType());

    MOCK_CONST_METHOD0(hasExpression, bool());

    MOCK_CONST_METHOD0(getExpression, std::string());

    MOCK_CONST_METHOD0(getExpressionInMacro, std::string());

    MOCK_CONST_METHOD0(hasExpandedExpression, bool());

    MOCK_CONST_METHOD0(getExpandedExpression, std::string());

    MOCK_CONST_METHOD0(getMessage, StringRef());

    MOCK_CONST_METHOD0(getSourceInfo, SourceLineInfo());

    MOCK_CONST_METHOD0(getTestMacroName, StringRef());

};



class SonarQubeReporterTest : public ::testing::Test {

protected:

    MockXmlWriter mock_xml;

    std::ostringstream oss;



    SonarQubeReporterTest() 

        : mock_xml(oss) {}



    void SetUp() override {

        reporter = new SonarQubeReporter({mock_xml});

    }



    void TearDown() override {

        delete reporter;

    }



    SonarQubeReporter* reporter;

};



TEST_F(SonarQubeReporterTest_832, WriteAssertion_Pass_832) {

    AssertionInfo info("", SourceLineInfo());

    AssertionResultData data(ResultWas::OfType::Ok);

    MockAssertionResult result(info, CATCH_MOVE(data));



    EXPECT_CALL(result, isOk()).WillOnce(::testing::Return(true));

    EXPECT_CALL(mock_xml, writeAttribute(_, _)).Times(0);

    EXPECT_CALL(mock_xml, writeText(_, _)).Times(0);



    reporter->writeAssertion(AssertionStats(result, {}, Totals()), false);

}



TEST_F(SonarQubeReporterTest_832, WriteAssertion_Error_ThrewException_832) {

    AssertionInfo info("CHECK_THROWS", SourceLineInfo());

    AssertionResultData data(ResultWas::OfType::ThrewException);

    MockAssertionResult result(info, CATCH_MOVE(data));



    EXPECT_CALL(result, isOk()).WillOnce(::testing::Return(false));

    EXPECT_CALL(result, getResultType()).WillRepeatedly(::testing::Return(ResultWas::OfType::ThrewException));

    EXPECT_CALL(mock_xml, startElement("error")).Times(1);

    EXPECT_CALL(mock_xml, writeAttribute(_, _)).Times(3);

    EXPECT_CALL(mock_xml, writeText(_, _)).Times(1);



    reporter->writeAssertion(AssertionStats(result, {}, Totals()), false);

}



TEST_F(SonarQubeReporterTest_832, WriteAssertion_Error_ExplicitFailure_832) {

    AssertionInfo info("CHECK_FALSE", SourceLineInfo());

    AssertionResultData data(ResultWas::OfType::ExplicitFailure);

    MockAssertionResult result(info, CATCH_MOVE(data));



    EXPECT_CALL(result, isOk()).WillOnce(::testing::Return(false));

    EXPECT_CALL(result, getResultType()).WillRepeatedly(::testing::Return(ResultWas::OfType::ExplicitFailure));

    EXPECT_CALL(mock_xml, startElement("failure")).Times(1);

    EXPECT_CALL(mock_xml, writeAttribute(_, _)).Times(3);

    EXPECT_CALL(mock_xml, writeText(_, _)).Times(1);



    reporter->writeAssertion(AssertionStats(result, {}, Totals()), false);

}



TEST_F(SonarQubeReporterTest_832, WriteAssertion_Skip_ExplicitSkip_832) {

    AssertionInfo info("CHECK", SourceLineInfo());

    AssertionResultData data(ResultWas::OfType::ExplicitSkip);

    MockAssertionResult result(info, CATCH_MOVE(data));



    EXPECT_CALL(result, isOk()).WillOnce(::testing::Return(false));

    EXPECT_CALL(result, getResultType()).WillRepeatedly(::testing::Return(ResultWas::OfType::ExplicitSkip));

    EXPECT_CALL(mock_xml, startElement("skipped")).Times(1);

    EXPECT_CALL(mock_xml, writeAttribute(_, _)).Times(3);

    EXPECT_CALL(mock_xml, writeText(_, _)).Times(1);



    reporter->writeAssertion(AssertionStats(result, {}, Totals()), false);

}



TEST_F(SonarQubeReporterTest_832, WriteAssertion_Skip_OkToFail_832) {

    AssertionInfo info("CHECK", SourceLineInfo());

    AssertionResultData data(ResultWas::OfType::ExpressionFailed);

    MockAssertionResult result(info, CATCH_MOVE(data));



    EXPECT_CALL(result, isOk()).WillOnce(::testing::Return(false));

    EXPECT_CALL(mock_xml, startElement("skipped")).Times(1);

    EXPECT_CALL(mock_xml, writeAttribute(_, _)).Times(3);

    EXPECT_CALL(mock_xml, writeText(_, _)).Times(1);



    reporter->writeAssertion(AssertionStats(result, {}, Totals()), true);

}



TEST_F(SonarQubeReporterTest_832, WriteAssertion_InternalError_UndefinedResultType_832) {

    AssertionInfo info("CHECK", SourceLineInfo());

    AssertionResultData data(static_cast<ResultWas::OfType>(-1));

    MockAssertionResult result(info, CATCH_MOVE(data));



    EXPECT_CALL(result, isOk()).WillOnce(::testing::Return(false));

    EXPECT_CALL(result, getResultType()).WillRepeatedly(::testing::Return(ResultWas::OfType(-1)));

    EXPECT_CALL(mock_xml, startElement("internalError")).Times(1);

    EXPECT_CALL(mock_xml, writeAttribute(_, _)).Times(3);

    EXPECT_CALL(mock_xml, writeText(_, _)).Times(1);



    reporter->writeAssertion(AssertionStats(result, {}, Totals()), false);

}
