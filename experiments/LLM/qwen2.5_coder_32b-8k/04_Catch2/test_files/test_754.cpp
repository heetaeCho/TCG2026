#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/Catch2/src/catch2/reporters/catch_reporter_junit.hpp"

#include "./TestProjects/Catch2/src/catch2/internal/catch_xmlwriter.hpp"

#include "./TestProjects/Catch2/src/catch2/catch_timer.hpp"



using namespace Catch;

using ::testing::_;

using ::testing::Ref;



class MockXmlWriter : public XmlWriter {

public:

    MOCK_METHOD(XmlWriter&, endElement, (XmlFormatting fmt), (override));

};



class JunitReporterTest : public ::testing::Test {

protected:

    ReporterConfig config;

    std::ostringstream stream;

    MockXmlWriter* mockXmlWriter;

    JunitReporter reporter;



    JunitReporterTest()

        : config(ReporterConfig().useColour(false)),

          mockXmlWriter(new MockXmlWriter(stream)),

          reporter(std::move(config)) {

        // Replace the internal XmlWriter with our mock

        reporter.xml = *mockXmlWriter;

    }



    ~JunitReporterTest() override {

        delete &reporter.xml;  // Clean up the mock object

    }

};



TEST_F(JunitReporterTest, TestRunEndedCumulative_CallsEndElement_754) {

    EXPECT_CALL(*mockXmlWriter, endElement(_)).Times(1);

    reporter.testRunEndedCumulative();

}



TEST_F(JunitReporterTest, TestRunEndedCumulative_ReturnsCorrectly_754) {

    // Assuming testRunEndedCumulative is supposed to return void and not throw

    EXPECT_NO_THROW(reporter.testRunEndedCumulative());

}
