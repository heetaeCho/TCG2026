#include <gtest/gtest.h>
#include <sstream>
#include <string>

#include "catch2/reporters/catch_reporter_xml.hpp"
#include "catch2/internal/catch_xmlwriter.hpp"
#include "catch2/internal/catch_stringref.hpp"
#include "catch2/catch_reporter_registrars.hpp"
#include "catch2/interfaces/catch_interfaces_reporter.hpp"
#include "catch2/internal/catch_move_and_forward.hpp"
#include "catch2/catch_config.hpp"
#include "catch2/catch_session.hpp"

using namespace Catch;

// Test XmlWriter ScopedElement and writeAttribute directly to verify the pattern
// used by benchmarkFailed
class XmlWriterTest_846 : public ::testing::Test {
protected:
    std::ostringstream oss;
};

TEST_F(XmlWriterTest_846, ScopedElementWritesFailedWithMessage_846) {
    {
        XmlWriter xml(oss);
        xml.scopedElement("failed")
            .writeAttribute("message"_sr, "some error"_sr);
    }
    std::string output = oss.str();
    // Should contain a <failed> element with message attribute
    EXPECT_NE(output.find("failed"), std::string::npos);
    EXPECT_NE(output.find("message"), std::string::npos);
    EXPECT_NE(output.find("some error"), std::string::npos);
}

TEST_F(XmlWriterTest_846, ScopedElementWithEmptyMessage_846) {
    {
        XmlWriter xml(oss);
        xml.scopedElement("failed")
            .writeAttribute("message"_sr, ""_sr);
    }
    std::string output = oss.str();
    EXPECT_NE(output.find("failed"), std::string::npos);
    EXPECT_NE(output.find("message"), std::string::npos);
}

TEST_F(XmlWriterTest_846, ScopedElementWithSpecialCharactersInMessage_846) {
    {
        XmlWriter xml(oss);
        xml.scopedElement("failed")
            .writeAttribute("message"_sr, "error with <special> & \"chars\""_sr);
    }
    std::string output = oss.str();
    EXPECT_NE(output.find("failed"), std::string::npos);
    // Special characters should be escaped in XML
    EXPECT_NE(output.find("message"), std::string::npos);
}

TEST_F(XmlWriterTest_846, ScopedElementWithLongMessage_846) {
    std::string longError(1000, 'x');
    {
        XmlWriter xml(oss);
        xml.scopedElement("failed")
            .writeAttribute("message"_sr, StringRef(longError));
    }
    std::string output = oss.str();
    EXPECT_NE(output.find("failed"), std::string::npos);
    // The long string of x's should appear in output (possibly escaped but x doesn't need escaping)
    EXPECT_NE(output.find(std::string(100, 'x')), std::string::npos);
}

TEST_F(XmlWriterTest_846, StartElementThenEndElement_846) {
    {
        XmlWriter xml(oss);
        xml.startElement("benchmark");
        xml.scopedElement("failed")
            .writeAttribute("message"_sr, "timeout"_sr);
        xml.endElement();
    }
    std::string output = oss.str();
    EXPECT_NE(output.find("benchmark"), std::string::npos);
    EXPECT_NE(output.find("failed"), std::string::npos);
    EXPECT_NE(output.find("timeout"), std::string::npos);
}

TEST_F(XmlWriterTest_846, EndElementAfterScopedElement_846) {
    // Simulates the pattern in benchmarkFailed: scopedElement + endElement
    {
        XmlWriter xml(oss);
        xml.startElement("outer");
        xml.startElement("benchmark");
        // This is the pattern from benchmarkFailed
        xml.scopedElement("failed")
            .writeAttribute("message"_sr, "test error"_sr);
        xml.endElement(); // ends "benchmark"
        xml.endElement(); // ends "outer"
    }
    std::string output = oss.str();
    EXPECT_NE(output.find("failed"), std::string::npos);
    EXPECT_NE(output.find("test error"), std::string::npos);
}

TEST_F(XmlWriterTest_846, WriteAttributeWithStringRef_846) {
    {
        XmlWriter xml(oss);
        StringRef name("message");
        StringRef value("benchmark failed due to error");
        xml.scopedElement("failed")
            .writeAttribute(name, value);
    }
    std::string output = oss.str();
    EXPECT_NE(output.find("message"), std::string::npos);
    EXPECT_NE(output.find("benchmark failed due to error"), std::string::npos);
}

TEST_F(XmlWriterTest_846, MultipleAttributesOnScopedElement_846) {
    {
        XmlWriter xml(oss);
        xml.scopedElement("failed")
            .writeAttribute("message"_sr, "error1"_sr)
            .writeAttribute("code"_sr, "42"_sr);
    }
    std::string output = oss.str();
    EXPECT_NE(output.find("message"), std::string::npos);
    EXPECT_NE(output.find("error1"), std::string::npos);
    EXPECT_NE(output.find("code"), std::string::npos);
    EXPECT_NE(output.find("42"), std::string::npos);
}

TEST_F(XmlWriterTest_846, ScopedElementProducesWellFormedXml_846) {
    {
        XmlWriter xml(oss);
        xml.scopedElement("failed")
            .writeAttribute("message"_sr, "err"_sr);
    }
    std::string output = oss.str();
    // Should have proper XML closing - either self-closing /> or </failed>
    bool hasSelfClose = (output.find("/>") != std::string::npos);
    bool hasEndTag = (output.find("</failed>") != std::string::npos);
    EXPECT_TRUE(hasSelfClose || hasEndTag);
}

TEST_F(XmlWriterTest_846, NewlineAndWhitespaceCharactersInError_846) {
    {
        XmlWriter xml(oss);
        xml.scopedElement("failed")
            .writeAttribute("message"_sr, "line1\nline2\ttab"_sr);
    }
    std::string output = oss.str();
    EXPECT_NE(output.find("failed"), std::string::npos);
    EXPECT_NE(output.find("message"), std::string::npos);
}
