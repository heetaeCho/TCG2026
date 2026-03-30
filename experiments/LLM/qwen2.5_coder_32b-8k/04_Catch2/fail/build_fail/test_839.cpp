#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "catch_reporter_xml.hpp"

#include "catch_interfaces_config.hpp"



using namespace Catch;

using ::testing::Return;

using ::testing::_;



class MockConfig : public IConfig {

public:

    MOCK_METHOD(bool, includeSuccessfulResults, (), (const, override));

};



class XmlReporterTest_839 : public ::testing::Test {

protected:

    XmlWriter mockXmlWriter{std::cout};

    MockConfig mockConfig;

    ReporterConfig reporterConfig{&mockConfig};

    XmlReporter xmlReporter{CATCH_MOVE(reporterConfig)};



    AssertionResult createAssertionResult(ResultWas::OfType resultType, bool hasExpression = false, bool succeeded = true) {

        AssertionInfo info{"TestMacro", SourceLineInfo{"file.cpp", 123}};

        AssertionResultData data;

        data.resultType = resultType;

        data.hasExpression = hasExpression;

        data.succeeded = succeeded;



        return AssertionResult{info, CATCH_MOVE(data)};

    }



    AssertionStats createAssertionStats(ResultWas::OfType resultType, bool includeInfoMessage = false) {

        std::vector<MessageInfo> infoMessages;

        if (includeInfoMessage) {

            MessageInfo msg{"macroName", SourceLineInfo{"file.cpp", 123}, ResultWas::Info};

            infoMessages.push_back(msg);

        }



        return AssertionStats{createAssertionResult(resultType), CATCH_MOVE(infoMessages), Totals{}};

    }

};



TEST_F(XmlReporterTest_839, AssertionEnded_SuccessfulAssertionIncluded_839) {

    EXPECT_CALL(mockConfig, includeSuccessfulResults()).WillOnce(Return(true));



    xmlReporter.assertionEnded(createAssertionStats(ResultWas::Ok));

}



TEST_F(XmlReporterTest_839, AssertionEnded_InfoMessageWritten_839) {

    EXPECT_CALL(mockConfig, includeSuccessfulResults()).WillOnce(Return(false));



    xmlReporter.assertionEnded(createAssertionStats(ResultWas::Info, true));

}



TEST_F(XmlReporterTest_839, AssertionEnded_WarningWritten_839) {

    xmlReporter.assertionEnded(createAssertionStats(ResultWas::Warning));

}



TEST_F(XmlReporterTest_839, AssertionEnded_ExceptionWritten_839) {

    xmlReporter.assertionEnded(createAssertionStats(ResultWas::ThrewException));

}



TEST_F(XmlReporterTest_839, AssertionEnded_ExplicitFailureWritten_839) {

    xmlReporter.assertionEnded(createAssertionStats(ResultWas::ExplicitFailure));

}



TEST_F(XmlReporterTest_839, AssertionEnded_SkipWritten_839) {

    xmlReporter.assertionEnded(createAssertionStats(ResultWas::ExplicitSkip));

}



TEST_F(XmlReporterTest_839, AssertionEnded_FatalErrorConditionWritten_839) {

    xmlReporter.assertionEnded(createAssertionStats(ResultWas::FatalErrorCondition));

}



TEST_F(XmlReporterTest_839, AssertionEnded_NoExpressionNoWriting_839) {

    EXPECT_CALL(mockConfig, includeSuccessfulResults()).WillOnce(Return(false));



    xmlReporter.assertionEnded(createAssertionStats(ResultWas::Ok, false));

}
