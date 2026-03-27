#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "catch2/reporters/catch_reporter_sonarqube.hpp"

#include "catch2/internal/catch_xmlwriter.hpp"



using namespace Catch;

using namespace testing;



class MockXmlWriter : public XmlWriter {

public:

    MOCK_METHOD(void, endElement, (XmlFormatting fmt), (override));

};



class SonarQubeReporterTest_570 : public Test {

protected:

    void SetUp() override {

        m_stream = std::make_shared<std::ostringstream>();

        m_xmlWriter = new MockXmlWriter(*m_stream);

        m_reporter = new SonarQubeReporter(ReporterConfig {});

        m_reporter->xml = *m_xmlWriter;

    }



    void TearDown() override {

        delete m_reporter;

        delete m_xmlWriter;

    }



    std::shared_ptr<std::ostringstream> m_stream;

    MockXmlWriter* m_xmlWriter;

    SonarQubeReporter* m_reporter;

};



TEST_F(SonarQubeReporterTest_570, TestRunEndedCumulative_CallsEndElementOnce_570) {

    EXPECT_CALL(*m_xmlWriter, endElement(_)).Times(1);

    m_reporter->testRunEndedCumulative();

}



TEST_F(SonarQubeReporterTest_570, TestRunEndedCumulative_OutputStreamNotEmptyAfterCall_570) {

    m_reporter->testRunEndedCumulative();

    EXPECT_FALSE(m_stream->str().empty());

}
