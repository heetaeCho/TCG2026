#include <gtest/gtest.h>
#include <sstream>
#include <string>

#include "catch2/reporters/catch_reporter_xml.hpp"
#include "catch2/internal/catch_xmlwriter.hpp"
#include "catch2/internal/catch_source_line_info.hpp"
#include "catch2/catch_session.hpp"
#include "catch2/internal/catch_config_wchar.hpp"
#include "catch2/catch_test_macros.hpp"
#include "catch2/interfaces/catch_interfaces_config.hpp"
#include "catch2/internal/catch_reporter_spec_parser.hpp"
#include "catch2/reporters/catch_reporter_streaming_base.hpp"

using namespace Catch;

// Test XmlWriter directly since writeSourceInfo delegates to it
class XmlWriterTest_835 : public ::testing::Test {
protected:
    std::ostringstream oss;
};

TEST_F(XmlWriterTest_835, WriteAttributeStringRef_835) {
    XmlWriter writer(oss);
    writer.startElement("TestElement", XmlFormatting::None);
    writer.writeAttribute("name"_sr, "value"_sr);
    writer.endElement(XmlFormatting::None);
    
    std::string output = oss.str();
    EXPECT_NE(output.find("name=\"value\""), std::string::npos);
}

TEST_F(XmlWriterTest_835, WriteAttributeNumeric_835) {
    XmlWriter writer(oss);
    writer.startElement("TestElement", XmlFormatting::None);
    writer.writeAttribute("line"_sr, static_cast<std::size_t>(42));
    writer.endElement(XmlFormatting::None);
    
    std::string output = oss.str();
    EXPECT_NE(output.find("line=\"42\""), std::string::npos);
}

TEST_F(XmlWriterTest_835, WriteMultipleAttributes_835) {
    XmlWriter writer(oss);
    writer.startElement("TestElement", XmlFormatting::None);
    writer.writeAttribute("filename"_sr, "test.cpp"_sr);
    writer.writeAttribute("line"_sr, static_cast<std::size_t>(100));
    writer.endElement(XmlFormatting::None);
    
    std::string output = oss.str();
    EXPECT_NE(output.find("filename=\"test.cpp\""), std::string::npos);
    EXPECT_NE(output.find("line=\"100\""), std::string::npos);
}

TEST_F(XmlWriterTest_835, WriteAttributeChaining_835) {
    XmlWriter writer(oss);
    writer.startElement("TestElement", XmlFormatting::None);
    writer.writeAttribute("filename"_sr, "file.cpp"_sr)
          .writeAttribute("line"_sr, static_cast<std::size_t>(55));
    writer.endElement(XmlFormatting::None);
    
    std::string output = oss.str();
    EXPECT_NE(output.find("filename=\"file.cpp\""), std::string::npos);
    EXPECT_NE(output.find("line=\"55\""), std::string::npos);
}

TEST_F(XmlWriterTest_835, WriteAttributeEmptyFilename_835) {
    XmlWriter writer(oss);
    writer.startElement("TestElement", XmlFormatting::None);
    writer.writeAttribute("filename"_sr, ""_sr);
    writer.endElement(XmlFormatting::None);
    
    std::string output = oss.str();
    EXPECT_NE(output.find("filename=\"\""), std::string::npos);
}

TEST_F(XmlWriterTest_835, WriteAttributeLineBoundaryZero_835) {
    XmlWriter writer(oss);
    writer.startElement("TestElement", XmlFormatting::None);
    writer.writeAttribute("line"_sr, static_cast<std::size_t>(0));
    writer.endElement(XmlFormatting::None);
    
    std::string output = oss.str();
    EXPECT_NE(output.find("line=\"0\""), std::string::npos);
}

TEST_F(XmlWriterTest_835, WriteAttributeLineLargeValue_835) {
    XmlWriter writer(oss);
    writer.startElement("TestElement", XmlFormatting::None);
    writer.writeAttribute("line"_sr, static_cast<std::size_t>(999999));
    writer.endElement(XmlFormatting::None);
    
    std::string output = oss.str();
    EXPECT_NE(output.find("line=\"999999\""), std::string::npos);
}

TEST_F(XmlWriterTest_835, WriteAttributeSpecialCharsInFilename_835) {
    XmlWriter writer(oss);
    writer.startElement("TestElement", XmlFormatting::None);
    writer.writeAttribute("filename"_sr, "path/to/test&file.cpp"_sr);
    writer.endElement(XmlFormatting::None);
    
    std::string output = oss.str();
    // Special chars should be escaped in XML
    EXPECT_NE(output.find("filename="), std::string::npos);
}

TEST_F(XmlWriterTest_835, WriteAttributeBool_835) {
    XmlWriter writer(oss);
    writer.startElement("TestElement", XmlFormatting::None);
    writer.writeAttribute("flag"_sr, true);
    writer.endElement(XmlFormatting::None);
    
    std::string output = oss.str();
    EXPECT_NE(output.find("flag="), std::string::npos);
}

TEST_F(XmlWriterTest_835, StartAndEndElement_835) {
    XmlWriter writer(oss);
    writer.startElement("Outer", XmlFormatting::None);
    writer.startElement("Inner", XmlFormatting::None);
    writer.endElement(XmlFormatting::None);
    writer.endElement(XmlFormatting::None);
    
    std::string output = oss.str();
    EXPECT_NE(output.find("<Outer"), std::string::npos);
    EXPECT_NE(output.find("<Inner"), std::string::npos);
}

TEST_F(XmlWriterTest_835, ScopedElement_835) {
    {
        XmlWriter writer(oss);
        {
            auto scoped = writer.scopedElement("ScopedTag", XmlFormatting::None);
        }
    }
    std::string output = oss.str();
    EXPECT_NE(output.find("ScopedTag"), std::string::npos);
}

TEST_F(XmlWriterTest_835, WriteText_835) {
    XmlWriter writer(oss);
    writer.startElement("Element", XmlFormatting::None);
    writer.writeText("Hello World"_sr, XmlFormatting::None);
    writer.endElement(XmlFormatting::None);
    
    std::string output = oss.str();
    EXPECT_NE(output.find("Hello World"), std::string::npos);
}

TEST_F(XmlWriterTest_835, WriteComment_835) {
    XmlWriter writer(oss);
    writer.writeComment("This is a comment"_sr, XmlFormatting::None);
    
    std::string output = oss.str();
    EXPECT_NE(output.find("This is a comment"), std::string::npos);
}

// SourceLineInfo tests
class SourceLineInfoTest_835 : public ::testing::Test {};

TEST_F(SourceLineInfoTest_835, Construction_835) {
    SourceLineInfo info("test.cpp", 42);
    EXPECT_STREQ(info.file, "test.cpp");
    EXPECT_EQ(info.line, 42u);
}

TEST_F(SourceLineInfoTest_835, EqualityOperator_835) {
    SourceLineInfo info1("test.cpp", 42);
    SourceLineInfo info2("test.cpp", 42);
    EXPECT_TRUE(info1 == info2);
}

TEST_F(SourceLineInfoTest_835, EqualityOperatorDifferentFile_835) {
    SourceLineInfo info1("test1.cpp", 42);
    SourceLineInfo info2("test2.cpp", 42);
    EXPECT_FALSE(info1 == info2);
}

TEST_F(SourceLineInfoTest_835, EqualityOperatorDifferentLine_835) {
    SourceLineInfo info1("test.cpp", 42);
    SourceLineInfo info2("test.cpp", 43);
    EXPECT_FALSE(info1 == info2);
}

TEST_F(SourceLineInfoTest_835, LessThanOperator_835) {
    SourceLineInfo info1("a.cpp", 10);
    SourceLineInfo info2("b.cpp", 10);
    EXPECT_TRUE(info1 < info2);
}

TEST_F(SourceLineInfoTest_835, LessThanOperatorSameFileDifferentLine_835) {
    SourceLineInfo info1("test.cpp", 10);
    SourceLineInfo info2("test.cpp", 20);
    EXPECT_TRUE(info1 < info2);
}

TEST_F(SourceLineInfoTest_835, ZeroLine_835) {
    SourceLineInfo info("test.cpp", 0);
    EXPECT_STREQ(info.file, "test.cpp");
    EXPECT_EQ(info.line, 0u);
}

// Simulate what writeSourceInfo does using XmlWriter
TEST_F(XmlWriterTest_835, SimulateWriteSourceInfo_835) {
    XmlWriter writer(oss);
    writer.startElement("TestCase", XmlFormatting::None);
    
    SourceLineInfo sourceInfo("myfile.cpp", 123);
    writer.writeAttribute("filename"_sr, sourceInfo.file)
          .writeAttribute("line"_sr, sourceInfo.line);
    
    writer.endElement(XmlFormatting::None);
    
    std::string output = oss.str();
    EXPECT_NE(output.find("filename=\"myfile.cpp\""), std::string::npos);
    EXPECT_NE(output.find("line=\"123\""), std::string::npos);
}

TEST_F(XmlWriterTest_835, SimulateWriteSourceInfoWithPath_835) {
    XmlWriter writer(oss);
    writer.startElement("TestCase", XmlFormatting::None);
    
    SourceLineInfo sourceInfo("/usr/src/project/test.cpp", 9999);
    writer.writeAttribute("filename"_sr, sourceInfo.file)
          .writeAttribute("line"_sr, sourceInfo.line);
    
    writer.endElement(XmlFormatting::None);
    
    std::string output = oss.str();
    EXPECT_NE(output.find("filename=\"/usr/src/project/test.cpp\""), std::string::npos);
    EXPECT_NE(output.find("line=\"9999\""), std::string::npos);
}

TEST_F(XmlWriterTest_835, SimulateWriteSourceInfoLineOne_835) {
    XmlWriter writer(oss);
    writer.startElement("TestCase", XmlFormatting::None);
    
    SourceLineInfo sourceInfo("a.cpp", 1);
    writer.writeAttribute("filename"_sr, sourceInfo.file)
          .writeAttribute("line"_sr, sourceInfo.line);
    
    writer.endElement(XmlFormatting::None);
    
    std::string output = oss.str();
    EXPECT_NE(output.find("filename=\"a.cpp\""), std::string::npos);
    EXPECT_NE(output.find("line=\"1\""), std::string::npos);
}

TEST_F(XmlWriterTest_835, EnsureTagClosed_835) {
    XmlWriter writer(oss);
    writer.startElement("Element", XmlFormatting::None);
    writer.ensureTagClosed();
    
    std::string output = oss.str();
    EXPECT_NE(output.find(">"), std::string::npos);
}

TEST_F(XmlWriterTest_835, WriteAttributeCharPointer_835) {
    XmlWriter writer(oss);
    writer.startElement("TestElement", XmlFormatting::None);
    const char* value = "charvalue";
    writer.writeAttribute("attr"_sr, value);
    writer.endElement(XmlFormatting::None);
    
    std::string output = oss.str();
    EXPECT_NE(output.find("attr=\"charvalue\""), std::string::npos);
}

TEST_F(XmlWriterTest_835, WriteStylesheetRef_835) {
    XmlWriter writer(oss);
    writer.writeStylesheetRef("style.xsl"_sr);
    
    std::string output = oss.str();
    EXPECT_NE(output.find("style.xsl"), std::string::npos);
}
