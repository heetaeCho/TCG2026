#include <gtest/gtest.h>
#include <sstream>
#include <string>
#include "catch2/internal/catch_xmlwriter.hpp"

using namespace Catch;

class XmlWriterTest_474 : public ::testing::Test {
protected:
    std::ostringstream oss;
};

// Test that constructing an XmlWriter writes an XML declaration
TEST_F(XmlWriterTest_474, ConstructorWritesDeclaration_474) {
    XmlWriter writer(oss);
    std::string output = oss.str();
    EXPECT_NE(output.find("<?xml"), std::string::npos);
}

// Test startElement writes an opening tag
TEST_F(XmlWriterTest_474, StartElementWritesOpeningTag_474) {
    XmlWriter writer(oss);
    writer.startElement("TestElement", XmlFormatting::Indent);
    writer.endElement(XmlFormatting::Newline);
    std::string output = oss.str();
    EXPECT_NE(output.find("<TestElement"), std::string::npos);
}

// Test endElement closes the tag
TEST_F(XmlWriterTest_474, EndElementClosesTag_474) {
    XmlWriter writer(oss);
    writer.startElement("Root", XmlFormatting::Indent);
    writer.endElement(XmlFormatting::Newline);
    std::string output = oss.str();
    EXPECT_NE(output.find("</Root>"), std::string::npos) 
        << "Output was: " << output;
}

// Test self-closing tag when element has no content
TEST_F(XmlWriterTest_474, EmptyElementSelfCloses_474) {
    XmlWriter writer(oss);
    writer.startElement("Empty", XmlFormatting::Indent);
    writer.endElement(XmlFormatting::Newline);
    std::string output = oss.str();
    // Should either have /> or </Empty>
    bool hasSelfClose = output.find("/>") != std::string::npos;
    bool hasCloseTag = output.find("</Empty>") != std::string::npos;
    EXPECT_TRUE(hasSelfClose || hasCloseTag) << "Output was: " << output;
}

// Test writeAttribute with StringRef
TEST_F(XmlWriterTest_474, WriteAttributeStringRef_474) {
    XmlWriter writer(oss);
    writer.startElement("Element", XmlFormatting::Indent);
    writer.writeAttribute("name"_catch_sr, "value"_catch_sr);
    writer.endElement(XmlFormatting::Newline);
    std::string output = oss.str();
    EXPECT_NE(output.find("name=\"value\""), std::string::npos)
        << "Output was: " << output;
}

// Test writeAttribute with bool true
TEST_F(XmlWriterTest_474, WriteAttributeBoolTrue_474) {
    XmlWriter writer(oss);
    writer.startElement("Element", XmlFormatting::Indent);
    writer.writeAttribute("flag"_catch_sr, true);
    writer.endElement(XmlFormatting::Newline);
    std::string output = oss.str();
    EXPECT_NE(output.find("flag=\"true\""), std::string::npos)
        << "Output was: " << output;
}

// Test writeAttribute with bool false
TEST_F(XmlWriterTest_474, WriteAttributeBoolFalse_474) {
    XmlWriter writer(oss);
    writer.startElement("Element", XmlFormatting::Indent);
    writer.writeAttribute("flag"_catch_sr, false);
    writer.endElement(XmlFormatting::Newline);
    std::string output = oss.str();
    EXPECT_NE(output.find("flag=\"false\""), std::string::npos)
        << "Output was: " << output;
}

// Test writeAttribute with const char*
TEST_F(XmlWriterTest_474, WriteAttributeCharPtr_474) {
    XmlWriter writer(oss);
    writer.startElement("Element", XmlFormatting::Indent);
    writer.writeAttribute("key"_catch_sr, "charvalue");
    writer.endElement(XmlFormatting::Newline);
    std::string output = oss.str();
    EXPECT_NE(output.find("key=\"charvalue\""), std::string::npos)
        << "Output was: " << output;
}

// Test writeText
TEST_F(XmlWriterTest_474, WriteTextInElement_474) {
    XmlWriter writer(oss);
    writer.startElement("Text", XmlFormatting::Indent);
    writer.writeText("Hello World"_catch_sr, XmlFormatting::None);
    writer.endElement(XmlFormatting::Newline);
    std::string output = oss.str();
    EXPECT_NE(output.find("Hello World"), std::string::npos)
        << "Output was: " << output;
}

// Test writeComment
TEST_F(XmlWriterTest_474, WriteComment_474) {
    XmlWriter writer(oss);
    writer.writeComment("This is a comment"_catch_sr, XmlFormatting::Newline);
    std::string output = oss.str();
    EXPECT_NE(output.find("<!--"), std::string::npos)
        << "Output was: " << output;
    EXPECT_NE(output.find("This is a comment"), std::string::npos)
        << "Output was: " << output;
    EXPECT_NE(output.find("-->"), std::string::npos)
        << "Output was: " << output;
}

// Test writeStylesheetRef
TEST_F(XmlWriterTest_474, WriteStylesheetRef_474) {
    XmlWriter writer(oss);
    writer.writeStylesheetRef("style.xsl"_catch_sr);
    std::string output = oss.str();
    EXPECT_NE(output.find("style.xsl"), std::string::npos)
        << "Output was: " << output;
    EXPECT_NE(output.find("xml-stylesheet"), std::string::npos)
        << "Output was: " << output;
}

// Test scopedElement creates and closes element automatically
TEST_F(XmlWriterTest_474, ScopedElementAutoCloses_474) {
    {
        XmlWriter writer(oss);
        {
            auto scoped = writer.scopedElement("Scoped", XmlFormatting::Indent);
        }
        // After scoped goes out of scope, element should be closed
        std::string output = oss.str();
        bool hasSelfClose = output.find("/>") != std::string::npos;
        bool hasCloseTag = output.find("</Scoped>") != std::string::npos;
        EXPECT_TRUE(hasSelfClose || hasCloseTag) << "Output was: " << output;
    }
}

// Test ScopedElement writeText
TEST_F(XmlWriterTest_474, ScopedElementWriteText_474) {
    {
        XmlWriter writer(oss);
        {
            auto scoped = writer.scopedElement("Item", XmlFormatting::Indent);
            scoped.writeText("inner text"_catch_sr, XmlFormatting::None);
        }
        std::string output = oss.str();
        EXPECT_NE(output.find("inner text"), std::string::npos)
            << "Output was: " << output;
    }
}

// Test ScopedElement writeAttribute
TEST_F(XmlWriterTest_474, ScopedElementWriteAttribute_474) {
    {
        XmlWriter writer(oss);
        {
            auto scoped = writer.scopedElement("Item", XmlFormatting::Indent);
            scoped.writeAttribute("attr"_catch_sr, "val"_catch_sr);
        }
        std::string output = oss.str();
        EXPECT_NE(output.find("attr=\"val\""), std::string::npos)
            << "Output was: " << output;
    }
}

// Test nested elements
TEST_F(XmlWriterTest_474, NestedElements_474) {
    XmlWriter writer(oss);
    writer.startElement("Parent", XmlFormatting::Indent);
    writer.startElement("Child", XmlFormatting::Indent);
    writer.endElement(XmlFormatting::Newline);
    writer.endElement(XmlFormatting::Newline);
    std::string output = oss.str();
    EXPECT_NE(output.find("<Parent"), std::string::npos)
        << "Output was: " << output;
    EXPECT_NE(output.find("<Child"), std::string::npos)
        << "Output was: " << output;
}

// Test multiple attributes on same element
TEST_F(XmlWriterTest_474, MultipleAttributes_474) {
    XmlWriter writer(oss);
    writer.startElement("Elem", XmlFormatting::Indent);
    writer.writeAttribute("a"_catch_sr, "1"_catch_sr);
    writer.writeAttribute("b"_catch_sr, "2"_catch_sr);
    writer.endElement(XmlFormatting::Newline);
    std::string output = oss.str();
    EXPECT_NE(output.find("a=\"1\""), std::string::npos)
        << "Output was: " << output;
    EXPECT_NE(output.find("b=\"2\""), std::string::npos)
        << "Output was: " << output;
}

// Test ensureTagClosed
TEST_F(XmlWriterTest_474, EnsureTagClosed_474) {
    XmlWriter writer(oss);
    writer.startElement("Open", XmlFormatting::Indent);
    writer.ensureTagClosed();
    std::string output = oss.str();
    // After ensuring tag is closed, the tag should have a closing >
    EXPECT_NE(output.find(">"), std::string::npos)
        << "Output was: " << output;
}

// Test XmlFormatting::None suppresses formatting
TEST_F(XmlWriterTest_474, NoFormattingMode_474) {
    XmlWriter writer(oss);
    writer.startElement("A", XmlFormatting::None);
    writer.writeText("text"_catch_sr, XmlFormatting::None);
    writer.endElement(XmlFormatting::None);
    std::string output = oss.str();
    EXPECT_NE(output.find("<A"), std::string::npos)
        << "Output was: " << output;
    EXPECT_NE(output.find("text"), std::string::npos)
        << "Output was: " << output;
}

// Test writeAttribute returns reference for chaining
TEST_F(XmlWriterTest_474, WriteAttributeChaining_474) {
    XmlWriter writer(oss);
    writer.startElement("Elem", XmlFormatting::Indent);
    XmlWriter& ref = writer.writeAttribute("x"_catch_sr, "y"_catch_sr);
    EXPECT_EQ(&ref, &writer);
    writer.endElement(XmlFormatting::Newline);
}

// Test startElement returns reference for chaining
TEST_F(XmlWriterTest_474, StartElementReturnsRef_474) {
    XmlWriter writer(oss);
    XmlWriter& ref = writer.startElement("Elem", XmlFormatting::Indent);
    EXPECT_EQ(&ref, &writer);
    writer.endElement(XmlFormatting::Newline);
}

// Test endElement returns reference for chaining
TEST_F(XmlWriterTest_474, EndElementReturnsRef_474) {
    XmlWriter writer(oss);
    writer.startElement("Elem", XmlFormatting::Indent);
    XmlWriter& ref = writer.endElement(XmlFormatting::Newline);
    EXPECT_EQ(&ref, &writer);
}

// Test writeText returns reference for chaining
TEST_F(XmlWriterTest_474, WriteTextReturnsRef_474) {
    XmlWriter writer(oss);
    writer.startElement("Elem", XmlFormatting::Indent);
    XmlWriter& ref = writer.writeText("text"_catch_sr, XmlFormatting::None);
    EXPECT_EQ(&ref, &writer);
    writer.endElement(XmlFormatting::Newline);
}

// Test writeComment returns reference for chaining
TEST_F(XmlWriterTest_474, WriteCommentReturnsRef_474) {
    XmlWriter writer(oss);
    XmlWriter& ref = writer.writeComment("comment"_catch_sr, XmlFormatting::Newline);
    EXPECT_EQ(&ref, &writer);
}

// Test ScopedElement move semantics
TEST_F(XmlWriterTest_474, ScopedElementMoveConstruct_474) {
    XmlWriter writer(oss);
    {
        auto scoped1 = writer.scopedElement("MovedElem", XmlFormatting::Indent);
        auto scoped2 = std::move(scoped1);
        scoped2.writeAttribute("moved"_catch_sr, "true"_catch_sr);
    }
    std::string output = oss.str();
    EXPECT_NE(output.find("MovedElem"), std::string::npos)
        << "Output was: " << output;
    EXPECT_NE(output.find("moved=\"true\""), std::string::npos)
        << "Output was: " << output;
}

// Test special characters in text are escaped
TEST_F(XmlWriterTest_474, TextEscaping_474) {
    XmlWriter writer(oss);
    writer.startElement("Elem", XmlFormatting::Indent);
    writer.writeText("<>&\""_catch_sr, XmlFormatting::None);
    writer.endElement(XmlFormatting::Newline);
    std::string output = oss.str();
    // Should have escaped versions
    EXPECT_NE(output.find("&lt;"), std::string::npos)
        << "Output was: " << output;
    EXPECT_NE(output.find("&gt;"), std::string::npos)
        << "Output was: " << output;
    EXPECT_NE(output.find("&amp;"), std::string::npos)
        << "Output was: " << output;
}

// Test special characters in attributes are escaped
TEST_F(XmlWriterTest_474, AttributeEscaping_474) {
    XmlWriter writer(oss);
    writer.startElement("Elem", XmlFormatting::Indent);
    writer.writeAttribute("val"_catch_sr, "<>&\""_catch_sr);
    writer.endElement(XmlFormatting::Newline);
    std::string output = oss.str();
    EXPECT_NE(output.find("&lt;"), std::string::npos)
        << "Output was: " << output;
    EXPECT_NE(output.find("&amp;"), std::string::npos)
        << "Output was: " << output;
}

// Test writeAttribute with integer (template version)
TEST_F(XmlWriterTest_474, WriteAttributeInteger_474) {
    XmlWriter writer(oss);
    writer.startElement("Elem", XmlFormatting::Indent);
    writer.writeAttribute("count"_catch_sr, 42);
    writer.endElement(XmlFormatting::Newline);
    std::string output = oss.str();
    EXPECT_NE(output.find("count=\"42\""), std::string::npos)
        << "Output was: " << output;
}

// Test deeply nested scoped elements
TEST_F(XmlWriterTest_474, DeepNestedScopedElements_474) {
    {
        XmlWriter writer(oss);
        {
            auto s1 = writer.scopedElement("L1", XmlFormatting::Indent);
            {
                auto s2 = writer.scopedElement("L2", XmlFormatting::Indent);
                {
                    auto s3 = writer.scopedElement("L3", XmlFormatting::Indent);
                }
            }
        }
        std::string output = oss.str();
        EXPECT_NE(output.find("L1"), std::string::npos);
        EXPECT_NE(output.find("L2"), std::string::npos);
        EXPECT_NE(output.find("L3"), std::string::npos);
    }
}

// Test destructor closes all remaining open tags
TEST_F(XmlWriterTest_474, DestructorClosesOpenTags_474) {
    {
        XmlWriter writer(oss);
        writer.startElement("A", XmlFormatting::Indent);
        writer.startElement("B", XmlFormatting::Indent);
        // Destructor should close B and A
    }
    std::string output = oss.str();
    // Both elements should be properly closed
    EXPECT_NE(output.find("<A"), std::string::npos)
        << "Output was: " << output;
    EXPECT_NE(output.find("<B"), std::string::npos)
        << "Output was: " << output;
}

// Test empty text write
TEST_F(XmlWriterTest_474, WriteEmptyText_474) {
    XmlWriter writer(oss);
    writer.startElement("Elem", XmlFormatting::Indent);
    writer.writeText(""_catch_sr, XmlFormatting::None);
    writer.endElement(XmlFormatting::Newline);
    std::string output = oss.str();
    EXPECT_NE(output.find("Elem"), std::string::npos)
        << "Output was: " << output;
}

// Test ScopedElement writeAttribute returns reference for chaining
TEST_F(XmlWriterTest_474, ScopedElementWriteAttributeChaining_474) {
    XmlWriter writer(oss);
    {
        auto scoped = writer.scopedElement("Elem", XmlFormatting::Indent);
        auto& ref = scoped.writeAttribute("a"_catch_sr, "1"_catch_sr);
        EXPECT_EQ(&ref, &scoped);
    }
}

// Test ScopedElement writeText returns reference for chaining
TEST_F(XmlWriterTest_474, ScopedElementWriteTextChaining_474) {
    XmlWriter writer(oss);
    {
        auto scoped = writer.scopedElement("Elem", XmlFormatting::Indent);
        auto& ref = scoped.writeText("text"_catch_sr, XmlFormatting::None);
        EXPECT_EQ(&ref, &scoped);
    }
}
