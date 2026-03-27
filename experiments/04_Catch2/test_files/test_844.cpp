#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "catch2/reporters/catch_reporter_xml.hpp"

#include "catch2/internal/catch_xmlwriter.hpp"



using namespace Catch;

using namespace testing;



class MockXmlWriter : public XmlWriter {

public:

    MOCK_METHOD(XmlWriter&, writeAttribute, (StringRef name, StringRef attribute), (override));

    MOCK_METHOD(XmlWriter&, writeComment, (StringRef text, XmlFormatting fmt), (override));



    MockXmlWriter(std::ostream& os) : XmlWriter(os) {}

};



class XmlReporterTest_844 : public Test {

protected:

    std::ostringstream oss;

    MockXmlWriter mockXmlWriter;

    XmlReporter reporter{ReporterConfig{}};



    XmlReporterTest_844() : mockXmlWriter(oss), reporter{ReporterConfig{}} {

        // Replace the internal XmlWriter with our mock

        *const_cast<XmlWriter*>(&reporter.m_xml) = mockXmlWriter;

    }

};



TEST_F(XmlReporterTest_844, BenchmarkStarting_WritesAttributesCorrectly_844) {

    BenchmarkInfo info{

        .estimatedDuration = 123.45,

        .iterations = 1000,

        .samples = 10,

        .resamples = 5,

        .clockResolution = 987.65

    };



    EXPECT_CALL(mockXmlWriter, writeAttribute("samples"_sr, "10")).Times(1);

    EXPECT_CALL(mockXmlWriter, writeAttribute("resamples"_sr, "5")).Times(1);

    EXPECT_CALL(mockXmlWriter, writeAttribute("iterations"_sr, "1000")).Times(1);

    EXPECT_CALL(mockXmlWriter, writeAttribute("clockResolution"_sr, "987.65")).Times(1);

    EXPECT_CALL(mockXmlWriter, writeAttribute("estimatedDuration"_sr, "123.45")).Times(1);

    EXPECT_CALL(mockXmlWriter, writeComment("All values in nano seconds"_sr)).Times(1);



    reporter.benchmarkStarting(info);

}



TEST_F(XmlReporterTest_844, BenchmarkStarting_ZeroValues_WritesZeroCorrectly_844) {

    BenchmarkInfo info{

        .estimatedDuration = 0.0,

        .iterations = 0,

        .samples = 0,

        .resamples = 0,

        .clockResolution = 0.0

    };



    EXPECT_CALL(mockXmlWriter, writeAttribute("samples"_sr, "0")).Times(1);

    EXPECT_CALL(mockXmlWriter, writeAttribute("resamples"_sr, "0")).Times(1);

    EXPECT_CALL(mockXmlWriter, writeAttribute("iterations"_sr, "0")).Times(1);

    EXPECT_CALL(mockXmlWriter, writeAttribute("clockResolution"_sr, "0")).Times(1);

    EXPECT_CALL(mockXmlWriter, writeAttribute("estimatedDuration"_sr, "0")).Times(1);

    EXPECT_CALL(mockXmlWriter, writeComment("All values in nano seconds"_sr)).Times(1);



    reporter.benchmarkStarting(info);

}
