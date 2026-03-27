#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "catch_reporter_xml.hpp"

#include "catch_xmlwriter.hpp"

#include "catch_stringref.hpp"



using namespace Catch;

using ::testing::_;

using ::testing::Return;



class MockXmlWriter : public XmlWriter {

public:

    MOCK_METHOD2(startElement, XmlWriter&(const std::string&, XmlFormatting));

    MOCK_METHOD3(writeAttribute, XmlWriter&(StringRef, StringRef, XmlFormatting));



    MockXmlWriter(std::ostream& os) : XmlWriter(os) {}

};



class XmlReporterTest_843 : public ::testing::Test {

protected:

    ReporterConfig config;

    std::ostringstream oss;

    MockXmlWriter mockXmlWriter{oss};

    XmlReporter reporter{CATCH_MOVE(config)};

};



TEST_F(XmlReporterTest_843, BenchmarkPreparing_StartsBenchmarkResultsElement_843) {

    EXPECT_CALL(mockXmlWriter, startElement("BenchmarkResults", _)).Times(1);

    StringRef name("SampleBenchmark");

    reporter.benchmarkPreparing(name);

}



TEST_F(XmlReporterTest_843, BenchmarkPreparing_WritesNameAttribute_843) {

    EXPECT_CALL(mockXmlWriter, writeAttribute(StringRef("name"), "SampleBenchmark")).Times(1);

    StringRef name("SampleBenchmark");

    reporter.benchmarkPreparing(name);

}



TEST_F(XmlReporterTest_843, BenchmarkPreparing_HandlesEmptyString_843) {

    EXPECT_CALL(mockXmlWriter, writeAttribute(StringRef("name"), "")).Times(1);

    StringRef name("");

    reporter.benchmarkPreparing(name);

}



TEST_F(XmlReporterTest_843, BenchmarkPreparing_HandlesLargeName_843) {

    std::string largeName(1024, 'a'); // Large string

    EXPECT_CALL(mockXmlWriter, writeAttribute(StringRef("name"), StringRef(largeName))).Times(1);

    StringRef name(largeName.c_str());

    reporter.benchmarkPreparing(name);

}
