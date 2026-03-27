#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "catch2/reporters/catch_reporter_xml.hpp"

#include "catch2/internal/catch_xmlwriter.hpp"

#include "catch2/interfaces/catch_interfaces_config.hpp"



using namespace Catch;

using ::testing::_;

using ::testing::NiceMock;



class MockXmlWriter : public XmlWriter {

public:

    MOCK_METHOD(void, endElement, (XmlFormatting fmt), (override));

    MOCK_METHOD(XmlWriter&, writeAttribute, (StringRef name, StringRef attribute), (override));

    MOCK_METHOD(XmlWriter&, writeAttribute, (StringRef name, bool attribute), (override));



    MockXmlWriter(std::ostream & os) : XmlWriter(os) {}

};



class MockConfig : public IConfig {

public:

    MOCK_CONST_METHOD0(showDurations, ShowDurations());

};



class XmlReporterTest : public ::testing::Test {

protected:

    std::ostringstream oss;

    NiceMock<MockXmlWriter> mockXmlWriter{oss};

    NiceMock<MockConfig> mockConfig;

    SectionStats sectionStats;



    XmlReporter xmlReporter{ReporterConfig{std::move(mockConfig)}};



    void SetUp() override {

        xmlReporter.m_xml = mockXmlWriter;

        xmlReporter.m_sectionDepth = 1;



        Counts counts;

        counts.passed = 5;

        counts.failed = 3;

        counts.failedButOk = 2;

        counts.skipped = 4;



        sectionStats = SectionStats{SectionInfo{"section", "file", 0}, counts, 1.23, false};

    }

};



TEST_F(XmlReporterTest_840, NormalOperation_WritesAttributesCorrectly_840) {

    EXPECT_CALL(mockXmlWriter, writeAttribute("successes"_sr, StringRef("5")))

        .Times(1);

    EXPECT_CALL(mockXmlWriter, writeAttribute("failures"_sr, StringRef("3")))

        .Times(1);

    EXPECT_CALL(mockXmlWriter, writeAttribute("expectedFailures"_sr, StringRef("2")))

        .Times(1);

    EXPECT_CALL(mockXmlWriter, writeAttribute("skipped"_sr, true))

        .Times(1);

    EXPECT_CALL(mockConfig, showDurations())

        .WillOnce(::testing::Return(ShowDurations::Always));

    EXPECT_CALL(mockXmlWriter, writeAttribute("durationInSeconds"_sr, StringRef("1.23")))

        .Times(1);



    xmlReporter.sectionEnded(sectionStats);

}



TEST_F(XmlReporterTest_840, NoSkipped_WritesSkippedFalse_840) {

    sectionStats.assertions.skipped = 0;



    EXPECT_CALL(mockXmlWriter, writeAttribute("skipped"_sr, false))

        .Times(1);



    xmlReporter.sectionEnded(sectionStats);

}



TEST_F(XmlReporterTest_840, DurationsNever_DoesNotWriteDuration_840) {

    EXPECT_CALL(mockConfig, showDurations())

        .WillOnce(::testing::Return(ShowDurations::Never));

    EXPECT_CALL(mockXmlWriter, writeAttribute("durationInSeconds"_sr, _))

        .Times(0);



    xmlReporter.sectionEnded(sectionStats);

}



TEST_F(XmlReporterTest_840, DurationsDefaultForReporter_DoesNotWriteDuration_840) {

    EXPECT_CALL(mockConfig, showDurations())

        .WillOnce(::testing::Return(ShowDurations::DefaultForReporter));

    EXPECT_CALL(mockXmlWriter, writeAttribute("durationInSeconds"_sr, _))

        .Times(0);



    xmlReporter.sectionEnded(sectionStats);

}



TEST_F(XmlReporterTest_840, SectionDepthZero_DoesNotCallEndElement_840) {

    xmlReporter.m_sectionDepth = 0;



    EXPECT_CALL(mockXmlWriter, endElement(_))

        .Times(0);



    xmlReporter.sectionEnded(sectionStats);

}
