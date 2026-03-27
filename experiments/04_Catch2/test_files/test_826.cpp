#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "catch2/reporters/catch_reporter_sonarqube.hpp"

#include "catch2/internal/catch_xmlwriter.hpp"

#include "catch2/interfaces/catch_interfaces_reporter.hpp"

#include "catch2/reporters/catch_reporter_cumulative_base.hpp"



using namespace Catch;

using ::testing::_;



class MockXmlWriter : public XmlWriter {

public:

    MOCK_METHOD1(writeComment, void(StringRef text));

    MOCK_METHOD3(startElement, XmlWriter&(const std::string & name, XmlFormatting fmt));

    MOCK_METHOD2(writeAttribute, XmlWriter&(StringRef name, StringRef attribute));



    MockXmlWriter(std::ostream & os) : XmlWriter(os) {}

};



class SonarQubeReporterTest : public ::testing::Test {

protected:

    ReporterConfig config;

    std::ostringstream stream;

    NiceMock<MockXmlWriter> xmlWriter{stream};

    SonarQubeReporter reporter{std::move(config)};

};



TEST_F(SonarQubeReporterTest_NormalOperation_826, TestRunStartingWritesMetadataAndStartsElement_826) {

    TestRunInfo testRunInfo("test_run_name");

    EXPECT_CALL(xmlWriter, writeComment(_)).Times(1);

    EXPECT_CALL(xmlWriter, startElement("testExecutions", _));

    EXPECT_CALL(xmlWriter, writeAttribute("version"_sr, '1'));



    reporter.testRunStarting(testRunInfo);

}



TEST_F(SonarQubeReporterTest_BoundaryConditions_826, TestRunStartingWithEmptyName_826) {

    TestRunInfo testRunInfo("");

    EXPECT_CALL(xmlWriter, writeComment(_)).Times(1);

    EXPECT_CALL(xmlWriter, startElement("testExecutions", _));

    EXPECT_CALL(xmlWriter, writeAttribute("version"_sr, '1'));



    reporter.testRunStarting(testRunInfo);

}



TEST_F(SonarQubeReporterTest_ExceptionalCases_826, TestRunStartingWithNullName_826) {

    // Assuming StringRef can be constructed with nullptr

    TestRunInfo testRunInfo(nullptr);

    EXPECT_CALL(xmlWriter, writeComment(_)).Times(1);

    EXPECT_CALL(xmlWriter, startElement("testExecutions", _));

    EXPECT_CALL(xmlWriter, writeAttribute("version"_sr, '1'));



    reporter.testRunStarting(testRunInfo);

}
