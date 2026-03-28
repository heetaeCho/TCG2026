#include <gtest/gtest.h>
#include <sstream>
#include <string>
#include "catch2/internal/catch_xmlwriter.hpp"

using namespace Catch;

class XmlWriterTest_468 : public ::testing::Test {
protected:
    std::ostringstream oss;
};

// ==================== XmlWriter Construction ====================

TEST_F(XmlWriterTest_468, ConstructorWritesDeclaration_468) {
    XmlWriter writer(oss);
    std::string output = oss.str();
    EXPECT_TRUE(output.find("<?xml") != std::string::npos);
}

// ==================== startElement / endElement ====================

TEST_F(XmlWriterTest_468, StartElementWritesOpenTag_468) {
    XmlWriter writer(oss);
    writer.startElement("root", XmlFormatting::None);
    writer.endElement(XmlFormatting::None);
    std::string output = oss.str();
    EXPECT_TRUE(output.find("<root") != std::string::npos);
}

TEST_F(XmlWriterTest_468, StartAndEndElementProducesClosingTag_468) {
    XmlWriter writer(oss);
    writer.startElement("root", XmlFormatting::None);
    writer.endElement(XmlFormatting::None);
    std::string output = oss.str();
    // Either self-closing or explicit close tag
    bool hasSelfClose = output.find("/>") != std::string::npos;
    bool hasCloseTag = output.find("</root>") != std::string::npos;
    EXPECT_TRUE(hasSelfClose || hasCloseTag);
}

TEST_F(XmlWriterTest_468, NestedElements_468) {
    XmlWriter writer(oss);
    writer.startElement("parent", XmlFormatting::None);
    writer.startElement("child", XmlFormatting::None);
    writer.endElement(XmlFormatting::None);
    writer.endElement(XmlFormatting::None);
    std::string output = oss.str();
    EXPECT_TRUE(output.find("parent") != std::string::npos);
    EXPECT_TRUE(output.find("child") != std::string::npos);
}

TEST_F(XmlWriterTest_468, StartElementReturnsReference_468) {
    XmlWriter writer(oss);
    XmlWriter& ref = writer.startElement("test", XmlFormatting::None);
    EXPECT_EQ(&ref, &writer);
    writer.endElement(XmlFormatting::None);
}

TEST_F(XmlWriterTest_468, EndElementReturnsReference_468) {
    XmlWriter writer(oss);
    writer.startElement("test", XmlFormatting::None);
    XmlWriter& ref = writer.endElement(XmlFormatting::None);
    EXPECT_EQ(&ref, &writer);
}

// ==================== writeAttribute ====================

TEST_F(XmlWriterTest_468, WriteAttributeStringRef_468) {
    XmlWriter writer(oss);
    writer.startElement("elem", XmlFormatting::None);
    writer.writeAttribute("name"_catch_sr, "value"_catch_sr);
    writer.endElement(XmlFormatting::None);
    std::string output = oss.str();
    EXPECT_TRUE(output.find("name=") != std::string::npos);
    EXPECT_TRUE(output.find("value") != std::string::npos);
}

TEST_F(XmlWriterTest_468, WriteAttributeBoolTrue_468) {
    XmlWriter writer(oss);
    writer.startElement("elem", XmlFormatting::None);
    writer.writeAttribute("flag", true);
    writer.endElement(XmlFormatting::None);
    std::string output = oss.str();
    EXPECT_TRUE(output.find("flag=") != std::string::npos);
    EXPECT_TRUE(output.find("true") != std::string::npos);
}

TEST_F(XmlWriterTest_468, WriteAttributeBoolFalse_468) {
    XmlWriter writer(oss);
    writer.startElement("elem", XmlFormatting::None);
    writer.writeAttribute("flag", false);
    writer.endElement(XmlFormatting::None);
    std::string output = oss.str();
    EXPECT_TRUE(output.find("flag=") != std::string::npos);
    EXPECT_TRUE(output.find("false") != std::string::npos);
}

TEST_F(XmlWriterTest_468, WriteAttributeCharPtr_468) {
    XmlWriter writer(oss);
    writer.startElement("elem", XmlFormatting::None);
    const char* val = "hello";
    writer.writeAttribute("attr", val);
    writer.endElement(XmlFormatting::None);
    std::string output = oss.str();
    EXPECT_TRUE(output.find("attr=") != std::string::npos);
    EXPECT_TRUE(output.find("hello") != std::string::npos);
}

TEST_F(XmlWriterTest_468, WriteAttributeReturnsReference_468) {
    XmlWriter writer(oss);
    writer.startElement("elem", XmlFormatting::None);
    XmlWriter& ref = writer.writeAttribute("a", "b");
    EXPECT_EQ(&ref, &writer);
    writer.endElement(XmlFormatting::None);
}

TEST_F(XmlWriterTest_468, WriteMultipleAttributes_468) {
    XmlWriter writer(oss);
    writer.startElement("elem", XmlFormatting::None);
    writer.writeAttribute("a1", "v1");
    writer.writeAttribute("a2", "v2");
    writer.endElement(XmlFormatting::None);
    std::string output = oss.str();
    EXPECT_TRUE(output.find("a1=") != std::string::npos);
    EXPECT_TRUE(output.find("a2=") != std::string::npos);
}

// ==================== writeText ====================

TEST_F(XmlWriterTest_468, WriteTextInElement_468) {
    XmlWriter writer(oss);
    writer.startElement("elem", XmlFormatting::None);
    writer.writeText("hello world", XmlFormatting::None);
    writer.endElement(XmlFormatting::None);
    std::string output = oss.str();
    EXPECT_TRUE(output.find("hello world") != std::string::npos);
}

TEST_F(XmlWriterTest_468, WriteTextReturnsReference_468) {
    XmlWriter writer(oss);
    writer.startElement("elem", XmlFormatting::None);
    XmlWriter& ref = writer.writeText("text", XmlFormatting::None);
    EXPECT_EQ(&ref, &writer);
    writer.endElement(XmlFormatting::None);
}

TEST_F(XmlWriterTest_468, WriteEmptyText_468) {
    XmlWriter writer(oss);
    writer.startElement("elem", XmlFormatting::None);
    writer.writeText("", XmlFormatting::None);
    writer.endElement(XmlFormatting::None);
    // Should not crash; output should still be valid
    std::string output = oss.str();
    EXPECT_TRUE(output.find("elem") != std::string::npos);
}

// ==================== writeComment ====================

TEST_F(XmlWriterTest_468, WriteCommentProducesXmlComment_468) {
    XmlWriter writer(oss);
    writer.writeComment("this is a comment", XmlFormatting::None);
    std::string output = oss.str();
    EXPECT_TRUE(output.find("<!--") != std::string::npos);
    EXPECT_TRUE(output.find("this is a comment") != std::string::npos);
    EXPECT_TRUE(output.find("-->") != std::string::npos);
}

TEST_F(XmlWriterTest_468, WriteCommentReturnsReference_468) {
    XmlWriter writer(oss);
    XmlWriter& ref = writer.writeComment("comment", XmlFormatting::None);
    EXPECT_EQ(&ref, &writer);
}

// ==================== writeStylesheetRef ====================

TEST_F(XmlWriterTest_468, WriteStylesheetRefContainsUrl_468) {
    XmlWriter writer(oss);
    writer.writeStylesheetRef("style.xsl");
    std::string output = oss.str();
    EXPECT_TRUE(output.find("style.xsl") != std::string::npos);
    EXPECT_TRUE(output.find("xml-stylesheet") != std::string::npos);
}

// ==================== ensureTagClosed ====================

TEST_F(XmlWriterTest_468, EnsureTagClosedClosesOpenTag_468) {
    XmlWriter writer(oss);
    writer.startElement("elem", XmlFormatting::None);
    writer.ensureTagClosed();
    std::string output = oss.str();
    // The tag should be closed with '>'
    EXPECT_TRUE(output.find(">") != std::string::npos);
}

// ==================== ScopedElement ====================

TEST_F(XmlWriterTest_468, ScopedElementClosesOnDestruction_468) {
    {
        XmlWriter writer(oss);
        {
            auto scoped = writer.scopedElement("auto_elem", XmlFormatting::None);
        }
        // After scoped goes out of scope, the element should be closed
        std::string output = oss.str();
        bool hasSelfClose = output.find("/>") != std::string::npos;
        bool hasCloseTag = output.find("</auto_elem>") != std::string::npos;
        EXPECT_TRUE(hasSelfClose || hasCloseTag);
    }
}

TEST_F(XmlWriterTest_468, ScopedElementWriteText_468) {
    XmlWriter writer(oss);
    {
        auto scoped = writer.scopedElement("elem", XmlFormatting::None);
        scoped.writeText("scoped text", XmlFormatting::None);
    }
    std::string output = oss.str();
    EXPECT_TRUE(output.find("scoped text") != std::string::npos);
}

TEST_F(XmlWriterTest_468, ScopedElementWriteAttribute_468) {
    XmlWriter writer(oss);
    {
        auto scoped = writer.scopedElement("elem", XmlFormatting::None);
        scoped.writeAttribute("key", "val");
    }
    std::string output = oss.str();
    EXPECT_TRUE(output.find("key=") != std::string::npos);
    EXPECT_TRUE(output.find("val") != std::string::npos);
}

TEST_F(XmlWriterTest_468, ScopedElementMoveAssignment_468) {
    XmlWriter writer(oss);
    {
        auto scoped1 = writer.scopedElement("first", XmlFormatting::None);
        scoped1 = writer.scopedElement("second", XmlFormatting::None);
        // scoped1 should have ended "first" and now manages "second"
    }
    std::string output = oss.str();
    EXPECT_TRUE(output.find("first") != std::string::npos);
    EXPECT_TRUE(output.find("second") != std::string::npos);
}

TEST_F(XmlWriterTest_468, ScopedElementMoveConstruction_468) {
    XmlWriter writer(oss);
    {
        auto scoped1 = writer.scopedElement("moved", XmlFormatting::None);
        auto scoped2 = std::move(scoped1);
        // scoped2 now owns the element, scoped1 should be inert
    }
    std::string output = oss.str();
    EXPECT_TRUE(output.find("moved") != std::string::npos);
}

TEST_F(XmlWriterTest_468, ScopedElementChainedWriteAttribute_468) {
    XmlWriter writer(oss);
    {
        auto scoped = writer.scopedElement("elem", XmlFormatting::None);
        scoped.writeAttribute("a", "1").writeAttribute("b", "2");
    }
    std::string output = oss.str();
    EXPECT_TRUE(output.find("a=") != std::string::npos);
    EXPECT_TRUE(output.find("b=") != std::string::npos);
}

// ==================== Formatting ====================

TEST_F(XmlWriterTest_468, FormattingIndent_468) {
    XmlWriter writer(oss);
    writer.startElement("parent", XmlFormatting::Indent);
    writer.startElement("child", XmlFormatting::Indent);
    writer.endElement(XmlFormatting::Newline);
    writer.endElement(XmlFormatting::Newline);
    std::string output = oss.str();
    EXPECT_TRUE(output.find("parent") != std::string::npos);
    EXPECT_TRUE(output.find("child") != std::string::npos);
}

TEST_F(XmlWriterTest_468, FormattingNewline_468) {
    XmlWriter writer(oss);
    writer.startElement("elem", XmlFormatting::Newline);
    writer.endElement(XmlFormatting::Newline);
    std::string output = oss.str();
    EXPECT_TRUE(output.find("\n") != std::string::npos);
}

TEST_F(XmlWriterTest_468, FormattingNone_468) {
    XmlWriter writer(oss);
    // Clear the declaration part
    std::string before = oss.str();
    writer.startElement("elem", XmlFormatting::None);
    writer.endElement(XmlFormatting::None);
    std::string output = oss.str();
    // Still valid XML but no extra formatting added around element
    EXPECT_TRUE(output.find("elem") != std::string::npos);
}

// ==================== Destructor auto-closes ====================

TEST_F(XmlWriterTest_468, DestructorClosesAllOpenElements_468) {
    {
        XmlWriter writer(oss);
        writer.startElement("outer", XmlFormatting::None);
        writer.startElement("inner", XmlFormatting::None);
        // Don't explicitly call endElement; destructor should close them
    }
    std::string output = oss.str();
    EXPECT_TRUE(output.find("outer") != std::string::npos);
    EXPECT_TRUE(output.find("inner") != std::string::npos);
}

// ==================== Special characters in text/attributes ====================

TEST_F(XmlWriterTest_468, WriteTextWithSpecialChars_468) {
    XmlWriter writer(oss);
    writer.startElement("elem", XmlFormatting::None);
    writer.writeText("<>&\"'", XmlFormatting::None);
    writer.endElement(XmlFormatting::None);
    std::string output = oss.str();
    // XML special characters should be escaped
    EXPECT_TRUE(output.find("&lt;") != std::string::npos || output.find("<") != std::string::npos);
    EXPECT_TRUE(output.find("&amp;") != std::string::npos);
}

TEST_F(XmlWriterTest_468, WriteAttributeWithSpecialChars_468) {
    XmlWriter writer(oss);
    writer.startElement("elem", XmlFormatting::None);
    writer.writeAttribute("attr", "a&b<c>d\"e");
    writer.endElement(XmlFormatting::None);
    std::string output = oss.str();
    // Should have escaped characters in attribute value
    EXPECT_TRUE(output.find("&amp;") != std::string::npos);
}

// ==================== Numeric attribute (template) ====================

TEST_F(XmlWriterTest_468, WriteAttributeInteger_468) {
    XmlWriter writer(oss);
    writer.startElement("elem", XmlFormatting::None);
    writer.writeAttribute("count", 42);
    writer.endElement(XmlFormatting::None);
    std::string output = oss.str();
    EXPECT_TRUE(output.find("count=") != std::string::npos);
    EXPECT_TRUE(output.find("42") != std::string::npos);
}

// ==================== Empty element ====================

TEST_F(XmlWriterTest_468, EmptyElementSelfCloses_468) {
    XmlWriter writer(oss);
    writer.startElement("empty", XmlFormatting::None);
    writer.endElement(XmlFormatting::None);
    std::string output = oss.str();
    // An empty element can be self-closing
    bool hasSelfClose = output.find("/>") != std::string::npos;
    bool hasExplicitClose = output.find("</empty>") != std::string::npos;
    EXPECT_TRUE(hasSelfClose || hasExplicitClose);
}

// ==================== Multiple elements at same level ====================

TEST_F(XmlWriterTest_468, MultipleSiblingElements_468) {
    XmlWriter writer(oss);
    writer.startElement("root", XmlFormatting::None);
    writer.startElement("child1", XmlFormatting::None);
    writer.endElement(XmlFormatting::None);
    writer.startElement("child2", XmlFormatting::None);
    writer.endElement(XmlFormatting::None);
    writer.endElement(XmlFormatting::None);
    std::string output = oss.str();
    EXPECT_TRUE(output.find("child1") != std::string::npos);
    EXPECT_TRUE(output.find("child2") != std::string::npos);
}

// ==================== ScopedElement with text and attributes ====================

TEST_F(XmlWriterTest_468, ScopedElementWriteTextAndAttribute_468) {
    XmlWriter writer(oss);
    {
        auto scoped = writer.scopedElement("item", XmlFormatting::None);
        scoped.writeAttribute("id", "1");
        scoped.writeText("content", XmlFormatting::None);
    }
    std::string output = oss.str();
    EXPECT_TRUE(output.find("id=") != std::string::npos);
    EXPECT_TRUE(output.find("content") != std::string::npos);
}
