#include <gtest/gtest.h>
#include <sstream>
#include <string>
#include "catch2/internal/catch_xmlwriter.hpp"

using namespace Catch;

class XmlWriterTest_469 : public ::testing::Test {
protected:
    std::ostringstream oss;
};

// Test that construction writes an XML declaration
TEST_F(XmlWriterTest_469, ConstructorWritesDeclaration_469) {
    XmlWriter writer(oss);
    std::string output = oss.str();
    EXPECT_NE(output.find("<?xml"), std::string::npos);
}

// Test that a simple element can be started and ended
TEST_F(XmlWriterTest_469, StartAndEndElement_469) {
    {
        XmlWriter writer(oss);
        writer.startElement("root", XmlFormatting::Newline);
        writer.endElement(XmlFormatting::Newline);
    }
    std::string output = oss.str();
    EXPECT_NE(output.find("<root"), std::string::npos);
    EXPECT_NE(output.find("</root>"), std::string::npos);
}

// Test that writeAttribute adds an attribute to the current element
TEST_F(XmlWriterTest_469, WriteAttributeStringRef_469) {
    {
        XmlWriter writer(oss);
        writer.startElement("elem", XmlFormatting::Newline)
              .writeAttribute("key"_catch_sr, "value"_catch_sr);
        writer.endElement(XmlFormatting::Newline);
    }
    std::string output = oss.str();
    EXPECT_NE(output.find("key=\"value\""), std::string::npos);
}

// Test that writeAttribute with bool writes true/false
TEST_F(XmlWriterTest_469, WriteAttributeBoolTrue_469) {
    {
        XmlWriter writer(oss);
        writer.startElement("elem", XmlFormatting::Newline)
              .writeAttribute("flag", true);
        writer.endElement(XmlFormatting::Newline);
    }
    std::string output = oss.str();
    EXPECT_NE(output.find("flag=\"true\""), std::string::npos);
}

TEST_F(XmlWriterTest_469, WriteAttributeBoolFalse_469) {
    {
        XmlWriter writer(oss);
        writer.startElement("elem", XmlFormatting::Newline)
              .writeAttribute("flag", false);
        writer.endElement(XmlFormatting::Newline);
    }
    std::string output = oss.str();
    EXPECT_NE(output.find("flag=\"false\""), std::string::npos);
}

// Test that writeAttribute with const char* works
TEST_F(XmlWriterTest_469, WriteAttributeConstChar_469) {
    {
        XmlWriter writer(oss);
        writer.startElement("elem", XmlFormatting::Newline)
              .writeAttribute("name", "hello");
        writer.endElement(XmlFormatting::Newline);
    }
    std::string output = oss.str();
    EXPECT_NE(output.find("name=\"hello\""), std::string::npos);
}

// Test writeText adds text content inside an element
TEST_F(XmlWriterTest_469, WriteText_469) {
    {
        XmlWriter writer(oss);
        writer.startElement("elem", XmlFormatting::Newline);
        writer.writeText("some text", XmlFormatting::Newline);
        writer.endElement(XmlFormatting::Newline);
    }
    std::string output = oss.str();
    EXPECT_NE(output.find("some text"), std::string::npos);
}

// Test writeComment writes an XML comment
TEST_F(XmlWriterTest_469, WriteComment_469) {
    {
        XmlWriter writer(oss);
        writer.writeComment("this is a comment", XmlFormatting::Newline);
    }
    std::string output = oss.str();
    EXPECT_NE(output.find("<!--"), std::string::npos);
    EXPECT_NE(output.find("this is a comment"), std::string::npos);
    EXPECT_NE(output.find("-->"), std::string::npos);
}

// Test writeStylesheetRef writes a stylesheet processing instruction
TEST_F(XmlWriterTest_469, WriteStylesheetRef_469) {
    {
        XmlWriter writer(oss);
        writer.writeStylesheetRef("style.xsl");
    }
    std::string output = oss.str();
    EXPECT_NE(output.find("style.xsl"), std::string::npos);
    EXPECT_NE(output.find("xml-stylesheet"), std::string::npos);
}

// Test scopedElement auto-closes on scope exit
TEST_F(XmlWriterTest_469, ScopedElementAutoCloses_469) {
    {
        XmlWriter writer(oss);
        {
            auto scoped = writer.scopedElement("child", XmlFormatting::Newline);
        }
    }
    std::string output = oss.str();
    // The element should have been opened and closed
    EXPECT_NE(output.find("child"), std::string::npos);
}

// Test nested elements produce correct nesting
TEST_F(XmlWriterTest_469, NestedElements_469) {
    {
        XmlWriter writer(oss);
        writer.startElement("parent", XmlFormatting::Newline);
        writer.startElement("child", XmlFormatting::Newline);
        writer.endElement(XmlFormatting::Newline);
        writer.endElement(XmlFormatting::Newline);
    }
    std::string output = oss.str();
    EXPECT_NE(output.find("<parent"), std::string::npos);
    EXPECT_NE(output.find("<child"), std::string::npos);
    EXPECT_NE(output.find("</child>"), std::string::npos);
    EXPECT_NE(output.find("</parent>"), std::string::npos);
}

// Test ScopedElement writeText
TEST_F(XmlWriterTest_469, ScopedElementWriteText_469) {
    {
        XmlWriter writer(oss);
        {
            auto scoped = writer.scopedElement("elem", XmlFormatting::Newline);
            scoped.writeText("inner text", XmlFormatting::Newline);
        }
    }
    std::string output = oss.str();
    EXPECT_NE(output.find("inner text"), std::string::npos);
}

// Test ScopedElement writeAttribute
TEST_F(XmlWriterTest_469, ScopedElementWriteAttribute_469) {
    {
        XmlWriter writer(oss);
        {
            auto scoped = writer.scopedElement("elem", XmlFormatting::Newline);
            scoped.writeAttribute("attr", "val");
        }
    }
    std::string output = oss.str();
    EXPECT_NE(output.find("attr=\"val\""), std::string::npos);
}

// Test that XmlWriter destructor closes all open tags
TEST_F(XmlWriterTest_469, DestructorClosesAllTags_469) {
    {
        XmlWriter writer(oss);
        writer.startElement("outer", XmlFormatting::Newline);
        writer.startElement("inner", XmlFormatting::Newline);
        // Not explicitly closing — destructor should handle it
    }
    std::string output = oss.str();
    EXPECT_NE(output.find("</inner>"), std::string::npos);
    EXPECT_NE(output.find("</outer>"), std::string::npos);
}

// Test ensureTagClosed closes an open tag
TEST_F(XmlWriterTest_469, EnsureTagClosed_469) {
    {
        XmlWriter writer(oss);
        writer.startElement("elem", XmlFormatting::Newline);
        writer.ensureTagClosed();
    }
    std::string output = oss.str();
    // After ensureTagClosed, the tag should be closed (with >)
    EXPECT_NE(output.find("<elem"), std::string::npos);
}

// Test empty text write
TEST_F(XmlWriterTest_469, WriteEmptyText_469) {
    {
        XmlWriter writer(oss);
        writer.startElement("elem", XmlFormatting::Newline);
        writer.writeText("", XmlFormatting::Newline);
        writer.endElement(XmlFormatting::Newline);
    }
    std::string output = oss.str();
    EXPECT_NE(output.find("<elem"), std::string::npos);
}

// Test multiple attributes on the same element
TEST_F(XmlWriterTest_469, MultipleAttributes_469) {
    {
        XmlWriter writer(oss);
        writer.startElement("elem", XmlFormatting::Newline)
              .writeAttribute("a", "1")
              .writeAttribute("b", "2")
              .writeAttribute("c", "3");
        writer.endElement(XmlFormatting::Newline);
    }
    std::string output = oss.str();
    EXPECT_NE(output.find("a=\"1\""), std::string::npos);
    EXPECT_NE(output.find("b=\"2\""), std::string::npos);
    EXPECT_NE(output.find("c=\"3\""), std::string::npos);
}

// Test XmlFormatting::None doesn't add newlines
TEST_F(XmlWriterTest_469, FormattingNone_469) {
    {
        XmlWriter writer(oss);
        writer.startElement("elem", XmlFormatting::None);
        writer.writeText("text", XmlFormatting::None);
        writer.endElement(XmlFormatting::None);
    }
    std::string output = oss.str();
    EXPECT_NE(output.find("<elem"), std::string::npos);
    EXPECT_NE(output.find("text"), std::string::npos);
}

// Test writeAttribute with numeric type (template version)
TEST_F(XmlWriterTest_469, WriteAttributeNumeric_469) {
    {
        XmlWriter writer(oss);
        writer.startElement("elem", XmlFormatting::Newline)
              .writeAttribute("count", 42);
        writer.endElement(XmlFormatting::Newline);
    }
    std::string output = oss.str();
    EXPECT_NE(output.find("count=\"42\""), std::string::npos);
}

// Test that text with special XML characters is properly escaped
TEST_F(XmlWriterTest_469, WriteTextEscapesSpecialChars_469) {
    {
        XmlWriter writer(oss);
        writer.startElement("elem", XmlFormatting::Newline);
        writer.writeText("<>&\"", XmlFormatting::Newline);
        writer.endElement(XmlFormatting::Newline);
    }
    std::string output = oss.str();
    // The special characters should be escaped
    EXPECT_NE(output.find("&lt;"), std::string::npos);
    EXPECT_NE(output.find("&amp;"), std::string::npos);
    EXPECT_NE(output.find("&gt;"), std::string::npos);
}

// Test attribute value escaping
TEST_F(XmlWriterTest_469, WriteAttributeEscapesSpecialChars_469) {
    {
        XmlWriter writer(oss);
        writer.startElement("elem", XmlFormatting::Newline)
              .writeAttribute("val", "a<b&c\"d");
        writer.endElement(XmlFormatting::Newline);
    }
    std::string output = oss.str();
    EXPECT_NE(output.find("&lt;"), std::string::npos);
    EXPECT_NE(output.find("&amp;"), std::string::npos);
    EXPECT_NE(output.find("&quot;"), std::string::npos);
}

// Test ScopedElement move semantics
TEST_F(XmlWriterTest_469, ScopedElementMoveSemantics_469) {
    {
        XmlWriter writer(oss);
        {
            auto scoped1 = writer.scopedElement("elem", XmlFormatting::Newline);
            auto scoped2 = std::move(scoped1);
            scoped2.writeAttribute("key", "val");
        }
    }
    std::string output = oss.str();
    EXPECT_NE(output.find("key=\"val\""), std::string::npos);
}

// Test chaining on ScopedElement
TEST_F(XmlWriterTest_469, ScopedElementChaining_469) {
    {
        XmlWriter writer(oss);
        {
            writer.scopedElement("elem", XmlFormatting::Newline)
                  .writeAttribute("a", "1")
                  .writeAttribute("b", "2")
                  .writeText("content", XmlFormatting::Newline);
        }
    }
    std::string output = oss.str();
    EXPECT_NE(output.find("a=\"1\""), std::string::npos);
    EXPECT_NE(output.find("b=\"2\""), std::string::npos);
    EXPECT_NE(output.find("content"), std::string::npos);
}

// Test chaining on XmlWriter startElement returns reference
TEST_F(XmlWriterTest_469, StartElementReturnsSelf_469) {
    {
        XmlWriter writer(oss);
        XmlWriter& ref = writer.startElement("elem", XmlFormatting::Newline);
        EXPECT_EQ(&ref, &writer);
        writer.endElement(XmlFormatting::Newline);
    }
}

// Test chaining on XmlWriter endElement returns reference
TEST_F(XmlWriterTest_469, EndElementReturnsSelf_469) {
    {
        XmlWriter writer(oss);
        writer.startElement("elem", XmlFormatting::Newline);
        XmlWriter& ref = writer.endElement(XmlFormatting::Newline);
        EXPECT_EQ(&ref, &writer);
    }
}

// Test writing comment with special characters
TEST_F(XmlWriterTest_469, WriteCommentWithSpecialChars_469) {
    {
        XmlWriter writer(oss);
        writer.writeComment("comment with <special> & chars", XmlFormatting::Newline);
    }
    std::string output = oss.str();
    EXPECT_NE(output.find("<!--"), std::string::npos);
    EXPECT_NE(output.find("-->"), std::string::npos);
}

// Test that an element with no content can be self-closing or properly closed
TEST_F(XmlWriterTest_469, EmptyElement_469) {
    {
        XmlWriter writer(oss);
        writer.startElement("empty", XmlFormatting::Newline);
        writer.endElement(XmlFormatting::Newline);
    }
    std::string output = oss.str();
    // Should contain some form of the element
    EXPECT_NE(output.find("empty"), std::string::npos);
}

// Test deeply nested elements
TEST_F(XmlWriterTest_469, DeeplyNestedElements_469) {
    {
        XmlWriter writer(oss);
        writer.startElement("l1", XmlFormatting::Newline);
        writer.startElement("l2", XmlFormatting::Newline);
        writer.startElement("l3", XmlFormatting::Newline);
        writer.startElement("l4", XmlFormatting::Newline);
        writer.endElement(XmlFormatting::Newline);
        writer.endElement(XmlFormatting::Newline);
        writer.endElement(XmlFormatting::Newline);
        writer.endElement(XmlFormatting::Newline);
    }
    std::string output = oss.str();
    EXPECT_NE(output.find("<l1"), std::string::npos);
    EXPECT_NE(output.find("<l2"), std::string::npos);
    EXPECT_NE(output.find("<l3"), std::string::npos);
    EXPECT_NE(output.find("<l4"), std::string::npos);
    EXPECT_NE(output.find("</l4>"), std::string::npos);
    EXPECT_NE(output.find("</l3>"), std::string::npos);
    EXPECT_NE(output.find("</l2>"), std::string::npos);
    EXPECT_NE(output.find("</l1>"), std::string::npos);
}

// Test ScopedElement with numeric attribute template
TEST_F(XmlWriterTest_469, ScopedElementWriteNumericAttribute_469) {
    {
        XmlWriter writer(oss);
        {
            writer.scopedElement("elem", XmlFormatting::Newline)
                  .writeAttribute("num", 99);
        }
    }
    std::string output = oss.str();
    EXPECT_NE(output.find("num=\"99\""), std::string::npos);
}
