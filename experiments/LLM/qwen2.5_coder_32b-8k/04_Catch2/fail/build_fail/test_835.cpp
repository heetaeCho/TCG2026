#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "catch_reporter_xml.hpp"

#include "catch_xmlwriter.hpp"

#include "catch_source_line_info.hpp"



using namespace Catch;

using ::testing::_;

using ::testing::StrEq;



class XmlReporterTest_835 : public ::testing::Test {

protected:

    std::ostringstream oss;

    ReporterConfig config;

    XmlReporter reporter{CATCH_MOVE(config)};

    XmlWriter& xmlWriter = reporter.m_xml;

};



TEST_F(XmlReporterTest_835, WriteSourceInfo_WritesFilenameAndLine_835) {

    SourceLineInfo sourceInfo("test_file.cpp", 42);

    EXPECT_CALL(xmlWriter, writeAttribute(StrEq("filename"), StrEq("test_file.cpp")));

    EXPECT_CALL(xmlWriter, writeAttribute(StrEq("line"), StrEq("42")));



    reporter.writeSourceInfo(sourceInfo);

}



TEST_F(XmlReporterTest_835, WriteSourceInfo_EmptyFilenameAndZeroLine_835) {

    SourceLineInfo sourceInfo("", 0);

    EXPECT_CALL(xmlWriter, writeAttribute(StrEq("filename"), StrEq("")));

    EXPECT_CALL(xmlWriter, writeAttribute(StrEq("line"), StrEq("0")));



    reporter.writeSourceInfo(sourceInfo);

}



TEST_F(XmlReporterTest_835, WriteSourceInfo_LargeLineNumbers_835) {

    SourceLineInfo sourceInfo("large_line_file.cpp", 123456789);

    EXPECT_CALL(xmlWriter, writeAttribute(StrEq("filename"), StrEq("large_line_file.cpp")));

    EXPECT_CALL(xmlWriter, writeAttribute(StrEq("line"), StrEq("123456789")));



    reporter.writeSourceInfo(sourceInfo);

}
