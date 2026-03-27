#include <gmock/gmock.h>

#include <gtest/gtest.h>

#include "catch_reporter_xml.hpp"

#include "catch_xmlwriter.hpp"

#include "catch_estimate.hpp"

#include "catch_outlier_classification.hpp"



using namespace Catch;

using namespace Catch::Benchmark;



class XmlReporterTest : public ::testing::Test {

protected:

    XmlWriterMock m_xmlMock;

    XmlReporter m_reporter{std::move(ReporterConfig{})};

    

    XmlReporterTest() : m_reporter{ReporterConfig{}} {

        // Redirect internal XmlWriter to mock for testing

        new(&m_reporter.m_xml) XmlWriter(reinterpret_cast<std::ostream&>(m_xmlMock));

    }



    struct XmlWriterMock : public XmlWriter {

        using XmlWriter::XmlWriter;

        

        MOCK_METHOD2(startElement, XmlWriter&(const std::string&, XmlFormatting));

        MOCK_METHOD1(scopedElement, ScopedElement(const std::string&, XmlFormatting));

        MOCK_METHOD1(endElement, XmlWriter&(XmlFormatting));

        MOCK_METHOD3(writeAttribute, XmlWriter&(StringRef, StringRef, double));

    };

};



TEST_F(XmlReporterTest_845, BenchmarkEnded_WritesMeanAttributes_845) {

    BenchmarkStats<> stats;

    stats.mean = Estimate<FDuration>{100.0, 90.0, 110.0, 0.95};

    

    EXPECT_CALL(m_xmlMock, scopedElement("mean", XmlFormatting::None))

        .WillOnce(testing::Return(ByMove(XmlWriter::ScopedElement(&m_xmlMock, XmlFormatting::None))));

    

    EXPECT_CALL(m_xmlMock, writeAttribute("value"_sr, "100.0"_sr));

    EXPECT_CALL(m_xmlMock, writeAttribute("lowerBound"_sr, "90.0"_sr));

    EXPECT_CALL(m_xmlMock, writeAttribute("upperBound"_sr, "110.0"_sr));

    EXPECT_CALL(m_xmlMock, writeAttribute("ci"_sr, 0.95));



    m_reporter.benchmarkEnded(stats);

}



TEST_F(XmlReporterTest_845, BenchmarkEnded_WritesStandardDeviationAttributes_845) {

    BenchmarkStats<> stats;

    stats.standardDeviation = Estimate<FDuration>{10.0, 8.0, 12.0, 0.9};



    EXPECT_CALL(m_xmlMock, scopedElement("standardDeviation", XmlFormatting::None))

        .WillOnce(testing::Return(ByMove(XmlWriter::ScopedElement(&m_xmlMock, XmlFormatting::None))));

    

    EXPECT_CALL(m_xmlMock, writeAttribute("value"_sr, "10.0"_sr));

    EXPECT_CALL(m_xmlMock, writeAttribute("lowerBound"_sr, "8.0"_sr));

    EXPECT_CALL(m_xmlMock, writeAttribute("upperBound"_sr, "12.0"_sr));

    EXPECT_CALL(m_xmlMock, writeAttribute("ci"_sr, 0.9));



    m_reporter.benchmarkEnded(stats);

}



TEST_F(XmlReporterTest_845, BenchmarkEnded_WritesOutliersAttributes_845) {

    BenchmarkStats<> stats;

    stats.outlierVariance = 15.0;

    stats.outliers = OutlierClassification{100, 5, 10, 15, 20};



    EXPECT_CALL(m_xmlMock, scopedElement("outliers", XmlFormatting::None))

        .WillOnce(testing::Return(ByMove(XmlWriter::ScopedElement(&m_xmlMock, XmlFormatting::None))));

    

    EXPECT_CALL(m_xmlMock, writeAttribute("variance"_sr, "15.0"_sr));

    EXPECT_CALL(m_xmlMock, writeAttribute("lowMild"_sr, "10"_sr));

    EXPECT_CALL(m_xmlMock, writeAttribute("lowSevere"_sr, "5"_sr));

    EXPECT_CALL(m_xmlMock, writeAttribute("highMild"_sr, "15"_sr));

    EXPECT_CALL(m_xmlMock, writeAttribute("highSevere"_sr, "20"_sr));



    m_reporter.benchmarkEnded(stats);

}



TEST_F(XmlReporterTest_845, BenchmarkEnded_EndsElementAfterWritingStats_845) {

    BenchmarkStats<> stats;



    EXPECT_CALL(m_xmlMock, endElement(XmlFormatting::None))

        .Times(1);



    m_reporter.benchmarkEnded(stats);

}
