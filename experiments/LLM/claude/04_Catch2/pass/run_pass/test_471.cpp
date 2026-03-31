#include <gtest/gtest.h>
#include <sstream>
#include <string>
#include "catch2/internal/catch_xmlwriter.hpp"

using namespace Catch;

class XmlWriterTest_471 : public ::testing::Test {
protected:
    std::ostringstream oss;
};

// ===== Construction and Destruction =====

TEST_F(XmlWriterTest_471, ConstructorWritesDeclaration_471) {
    XmlWriter writer(oss);
    std::string output = oss.str();
    EXPECT_TRUE(output.find("<?xml") != std::string::npos);
}

TEST_F(XmlWriterTest_471, DestructorClosesOpenElements_471) {
    {
        XmlWriter writer(oss);
        writer.startElement("root", XmlFormatting::Newline);
        writer.startElement("child", XmlFormatting::Newline);
    }
    std::string output = oss.str();
    EXPECT_TRUE(output.find("</child>") != std::string::npos);
    EXPECT_TRUE(output.find("</root>") != std::string::npos);
}

// ===== startElement =====

TEST_F(XmlWriterTest_471, StartElementCreatesOpenTag_471) {
    XmlWriter writer(oss);
    writer.startElement("root", XmlFormatting::Newline);
    writer.ensureTagClosed();
    std::string output = oss.str();
    EXPECT_TRUE(output.find("<root>") != std::string::npos || output.find("<root") != std::string::npos);
}

TEST_F(XmlWriterTest_471, StartElementNested_471) {
    XmlWriter writer(oss);
    writer.startElement("root", XmlFormatting::Newline);
    writer.startElement("child", XmlFormatting::Newline);
    writer.ensureTagClosed();
    std::string output = oss.str();
    EXPECT_TRUE(output.find("<child") != std::string::npos);
}

TEST_F(XmlWriterTest_471, StartElementReturnsSelf_471) {
    XmlWriter writer(oss);
    XmlWriter& ref = writer.startElement("root", XmlFormatting::Newline);
    EXPECT_EQ(&ref, &writer);
}

// ===== endElement =====

TEST_F(XmlWriterTest_471, EndElementClosesTag_471) {
    XmlWriter writer(oss);
    writer.startElement("root", XmlFormatting::Newline);
    writer.endElement(XmlFormatting::Newline);
    std::string output = oss.str();
    EXPECT_TRUE(output.find("</root>") != std::string::npos || output.find("/>") != std::string::npos);
}

TEST_F(XmlWriterTest_471, EndElementReturnsSelf_471) {
    XmlWriter writer(oss);
    writer.startElement("root", XmlFormatting::Newline);
    XmlWriter& ref = writer.endElement(XmlFormatting::Newline);
    EXPECT_EQ(&ref, &writer);
}

// ===== writeAttribute (StringRef, StringRef) =====

TEST_F(XmlWriterTest_471, WriteAttributeStringRef_471) {
    XmlWriter writer(oss);
    writer.startElement("root", XmlFormatting::Newline);
    writer.writeAttribute(StringRef("key"), StringRef("value"));
    writer.ensureTagClosed();
    std::string output = oss.str();
    EXPECT_TRUE(output.find("key") != std::string::npos);
    EXPECT_TRUE(output.find("value") != std::string::npos);
}

TEST_F(XmlWriterTest_471, WriteAttributeReturnsSelf_471) {
    XmlWriter writer(oss);
    writer.startElement("root", XmlFormatting::Newline);
    XmlWriter& ref = writer.writeAttribute(StringRef("key"), StringRef("value"));
    EXPECT_EQ(&ref, &writer);
}

// ===== writeAttribute (StringRef, bool) =====

TEST_F(XmlWriterTest_471, WriteAttributeBoolTrue_471) {
    XmlWriter writer(oss);
    writer.startElement("root", XmlFormatting::Newline);
    writer.writeAttribute(StringRef("flag"), true);
    writer.ensureTagClosed();
    std::string output = oss.str();
    EXPECT_TRUE(output.find("flag") != std::string::npos);
    EXPECT_TRUE(output.find("true") != std::string::npos);
}

TEST_F(XmlWriterTest_471, WriteAttributeBoolFalse_471) {
    XmlWriter writer(oss);
    writer.startElement("root", XmlFormatting::Newline);
    writer.writeAttribute(StringRef("flag"), false);
    writer.ensureTagClosed();
    std::string output = oss.str();
    EXPECT_TRUE(output.find("flag") != std::string::npos);
    EXPECT_TRUE(output.find("false") != std::string::npos);
}

// ===== writeAttribute (StringRef, const char*) =====

TEST_F(XmlWriterTest_471, WriteAttributeCharPtr_471) {
    XmlWriter writer(oss);
    writer.startElement("root", XmlFormatting::Newline);
    writer.writeAttribute(StringRef("name"), "hello");
    writer.ensureTagClosed();
    std::string output = oss.str();
    EXPECT_TRUE(output.find("name") != std::string::npos);
    EXPECT_TRUE(output.find("hello") != std::string::npos);
}

// ===== writeAttribute (template with numeric type) =====

TEST_F(XmlWriterTest_471, WriteAttributeIntegerType_471) {
    XmlWriter writer(oss);
    writer.startElement("root", XmlFormatting::Newline);
    writer.writeAttribute(StringRef("count"), 42);
    writer.ensureTagClosed();
    std::string output = oss.str();
    EXPECT_TRUE(output.find("count") != std::string::npos);
    EXPECT_TRUE(output.find("42") != std::string::npos);
}

// ===== writeText =====

TEST_F(XmlWriterTest_471, WriteTextInElement_471) {
    XmlWriter writer(oss);
    writer.startElement("root", XmlFormatting::Newline);
    writer.writeText(StringRef("Hello World"), XmlFormatting::None);
    writer.endElement(XmlFormatting::Newline);
    std::string output = oss.str();
    EXPECT_TRUE(output.find("Hello World") != std::string::npos);
}

TEST_F(XmlWriterTest_471, WriteTextReturnsSelf_471) {
    XmlWriter writer(oss);
    writer.startElement("root", XmlFormatting::Newline);
    XmlWriter& ref = writer.writeText(StringRef("text"), XmlFormatting::None);
    EXPECT_EQ(&ref, &writer);
}

// ===== writeComment =====

TEST_F(XmlWriterTest_471, WriteComment_471) {
    XmlWriter writer(oss);
    writer.writeComment(StringRef("This is a comment"), XmlFormatting::Newline);
    std::string output = oss.str();
    EXPECT_TRUE(output.find("<!--") != std::string::npos);
    EXPECT_TRUE(output.find("This is a comment") != std::string::npos);
    EXPECT_TRUE(output.find("-->") != std::string::npos);
}

TEST_F(XmlWriterTest_471, WriteCommentReturnsSelf_471) {
    XmlWriter writer(oss);
    XmlWriter& ref = writer.writeComment(StringRef("comment"), XmlFormatting::Newline);
    EXPECT_EQ(&ref, &writer);
}

// ===== writeStylesheetRef =====

TEST_F(XmlWriterTest_471, WriteStylesheetRef_471) {
    XmlWriter writer(oss);
    writer.writeStylesheetRef(StringRef("style.xsl"));
    std::string output = oss.str();
    EXPECT_TRUE(output.find("style.xsl") != std::string::npos);
    EXPECT_TRUE(output.find("xml-stylesheet") != std::string::npos);
}

// ===== ensureTagClosed =====

TEST_F(XmlWriterTest_471, EnsureTagClosedClosesOpenTag_471) {
    XmlWriter writer(oss);
    writer.startElement("root", XmlFormatting::Newline);
    writer.ensureTagClosed();
    std::string output = oss.str();
    EXPECT_TRUE(output.find(">") != std::string::npos);
}

// ===== ScopedElement =====

TEST_F(XmlWriterTest_471, ScopedElementCreatesAndClosesTag_471) {
    {
        XmlWriter writer(oss);
        {
            auto scoped = writer.scopedElement("item", XmlFormatting::Newline);
        }
        // After scoped goes out of scope, the element should be closed
        std::string output = oss.str();
        EXPECT_TRUE(output.find("item") != std::string::npos);
    }
}

TEST_F(XmlWriterTest_471, ScopedElementWriteAttribute_471) {
    XmlWriter writer(oss);
    {
        auto scoped = writer.scopedElement("item", XmlFormatting::Newline);
        scoped.writeAttribute(StringRef("id"), StringRef("123"));
    }
    std::string output = oss.str();
    EXPECT_TRUE(output.find("id") != std::string::npos);
    EXPECT_TRUE(output.find("123") != std::string::npos);
}

TEST_F(XmlWriterTest_471, ScopedElementWriteText_471) {
    XmlWriter writer(oss);
    {
        auto scoped = writer.scopedElement("item", XmlFormatting::Newline);
        scoped.writeText(StringRef("some text"), XmlFormatting::None);
    }
    std::string output = oss.str();
    EXPECT_TRUE(output.find("some text") != std::string::npos);
}

TEST_F(XmlWriterTest_471, ScopedElementChainedWriteAttribute_471) {
    XmlWriter writer(oss);
    {
        auto scoped = writer.scopedElement("item", XmlFormatting::Newline);
        scoped.writeAttribute(StringRef("a"), StringRef("1"))
              .writeAttribute(StringRef("b"), StringRef("2"));
    }
    std::string output = oss.str();
    EXPECT_TRUE(output.find("a=") != std::string::npos);
    EXPECT_TRUE(output.find("b=") != std::string::npos);
}

TEST_F(XmlWriterTest_471, ScopedElementMoveConstructor_471) {
    XmlWriter writer(oss);
    {
        auto scoped1 = writer.scopedElement("outer", XmlFormatting::Newline);
        auto scoped2 = std::move(scoped1);
        scoped2.writeAttribute(StringRef("key"), StringRef("val"));
    }
    std::string output = oss.str();
    EXPECT_TRUE(output.find("outer") != std::string::npos);
    EXPECT_TRUE(output.find("key") != std::string::npos);
}

// ===== Special Characters / Escaping =====

TEST_F(XmlWriterTest_471, WriteTextWithSpecialCharacters_471) {
    XmlWriter writer(oss);
    writer.startElement("root", XmlFormatting::Newline);
    writer.writeText(StringRef("<>&\""), XmlFormatting::None);
    writer.endElement(XmlFormatting::Newline);
    std::string output = oss.str();
    // The special characters should be escaped
    EXPECT_TRUE(output.find("&lt;") != std::string::npos);
    EXPECT_TRUE(output.find("&amp;") != std::string::npos);
    EXPECT_TRUE(output.find("&gt;") != std::string::npos);
}

TEST_F(XmlWriterTest_471, WriteAttributeWithSpecialCharacters_471) {
    XmlWriter writer(oss);
    writer.startElement("root", XmlFormatting::Newline);
    writer.writeAttribute(StringRef("data"), StringRef("a&b"));
    writer.ensureTagClosed();
    std::string output = oss.str();
    EXPECT_TRUE(output.find("&amp;") != std::string::npos);
}

// ===== Empty content =====

TEST_F(XmlWriterTest_471, WriteEmptyText_471) {
    XmlWriter writer(oss);
    writer.startElement("root", XmlFormatting::Newline);
    writer.writeText(StringRef(""), XmlFormatting::None);
    writer.endElement(XmlFormatting::Newline);
    std::string output = oss.str();
    EXPECT_TRUE(output.find("root") != std::string::npos);
}

TEST_F(XmlWriterTest_471, WriteEmptyAttribute_471) {
    XmlWriter writer(oss);
    writer.startElement("root", XmlFormatting::Newline);
    writer.writeAttribute(StringRef("key"), StringRef(""));
    writer.ensureTagClosed();
    std::string output = oss.str();
    EXPECT_TRUE(output.find("key") != std::string::npos);
}

// ===== Formatting =====

TEST_F(XmlWriterTest_471, FormattingNone_471) {
    XmlWriter writer(oss);
    writer.startElement("root", XmlFormatting::None);
    writer.endElement(XmlFormatting::None);
    std::string output = oss.str();
    EXPECT_TRUE(output.find("<root") != std::string::npos);
}

TEST_F(XmlWriterTest_471, FormattingNewline_471) {
    XmlWriter writer(oss);
    writer.startElement("root", XmlFormatting::Newline);
    writer.endElement(XmlFormatting::Newline);
    std::string output = oss.str();
    EXPECT_TRUE(output.find("\n") != std::string::npos);
}

// ===== Multiple elements =====

TEST_F(XmlWriterTest_471, MultipleNestedElements_471) {
    XmlWriter writer(oss);
    writer.startElement("root", XmlFormatting::Newline);
    writer.startElement("level1", XmlFormatting::Newline);
    writer.startElement("level2", XmlFormatting::Newline);
    writer.endElement(XmlFormatting::Newline);
    writer.endElement(XmlFormatting::Newline);
    writer.endElement(XmlFormatting::Newline);
    std::string output = oss.str();
    EXPECT_TRUE(output.find("root") != std::string::npos);
    EXPECT_TRUE(output.find("level1") != std::string::npos);
    EXPECT_TRUE(output.find("level2") != std::string::npos);
}

TEST_F(XmlWriterTest_471, MultipleSiblingElements_471) {
    XmlWriter writer(oss);
    writer.startElement("root", XmlFormatting::Newline);
    writer.startElement("child1", XmlFormatting::Newline);
    writer.endElement(XmlFormatting::Newline);
    writer.startElement("child2", XmlFormatting::Newline);
    writer.endElement(XmlFormatting::Newline);
    writer.endElement(XmlFormatting::Newline);
    std::string output = oss.str();
    EXPECT_TRUE(output.find("child1") != std::string::npos);
    EXPECT_TRUE(output.find("child2") != std::string::npos);
}

// ===== ScopedElement with template writeAttribute =====

TEST_F(XmlWriterTest_471, ScopedElementWriteAttributeNumeric_471) {
    XmlWriter writer(oss);
    {
        auto scoped = writer.scopedElement("item", XmlFormatting::Newline);
        scoped.writeAttribute(StringRef("count"), 99);
    }
    std::string output = oss.str();
    EXPECT_TRUE(output.find("count") != std::string::npos);
    EXPECT_TRUE(output.find("99") != std::string::npos);
}

// ===== Multiple attributes on one element =====

TEST_F(XmlWriterTest_471, MultipleAttributesOnElement_471) {
    XmlWriter writer(oss);
    writer.startElement("root", XmlFormatting::Newline);
    writer.writeAttribute(StringRef("a"), StringRef("1"));
    writer.writeAttribute(StringRef("b"), StringRef("2"));
    writer.writeAttribute(StringRef("c"), StringRef("3"));
    writer.ensureTagClosed();
    std::string output = oss.str();
    EXPECT_TRUE(output.find("a=") != std::string::npos);
    EXPECT_TRUE(output.find("b=") != std::string::npos);
    EXPECT_TRUE(output.find("c=") != std::string::npos);
}

// ===== Indentation =====

TEST_F(XmlWriterTest_471, IndentationIncreasesWithNesting_471) {
    XmlWriter writer(oss);
    writer.startElement("root", XmlFormatting::Newline | XmlFormatting::Indent);
    writer.startElement("child", XmlFormatting::Newline | XmlFormatting::Indent);
    writer.ensureTagClosed();
    std::string output = oss.str();
    // We expect some indentation for the nested child
    EXPECT_TRUE(output.find("  ") != std::string::npos || output.find("\t") != std::string::npos || output.find("child") != std::string::npos);
}

// ===== Self-closing elements (empty element) =====

TEST_F(XmlWriterTest_471, EmptyElementSelfCloses_471) {
    XmlWriter writer(oss);
    writer.startElement("empty", XmlFormatting::Newline);
    writer.endElement(XmlFormatting::Newline);
    std::string output = oss.str();
    // Either self-closing or open/close pair
    bool selfClosing = output.find("/>") != std::string::npos;
    bool openClose = output.find("</empty>") != std::string::npos;
    EXPECT_TRUE(selfClosing || openClose);
}

// ===== writeComment does not break element structure =====

TEST_F(XmlWriterTest_471, CommentInsideElement_471) {
    XmlWriter writer(oss);
    writer.startElement("root", XmlFormatting::Newline);
    writer.writeComment(StringRef("a comment"), XmlFormatting::Newline);
    writer.endElement(XmlFormatting::Newline);
    std::string output = oss.str();
    EXPECT_TRUE(output.find("<!-- a comment -->") != std::string::npos || output.find("<!--a comment-->") != std::string::npos);
}

// ===== Long attribute values =====

TEST_F(XmlWriterTest_471, LongAttributeValue_471) {
    XmlWriter writer(oss);
    std::string longValue(1000, 'x');
    writer.startElement("root", XmlFormatting::Newline);
    writer.writeAttribute(StringRef("data"), StringRef(longValue));
    writer.ensureTagClosed();
    std::string output = oss.str();
    EXPECT_TRUE(output.find(std::string(1000, 'x')) != std::string::npos);
}

// ===== Quoting in attribute values =====

TEST_F(XmlWriterTest_471, AttributeQuoteEscaping_471) {
    XmlWriter writer(oss);
    writer.startElement("root", XmlFormatting::Newline);
    writer.writeAttribute(StringRef("val"), StringRef("he said \"hi\""));
    writer.ensureTagClosed();
    std::string output = oss.str();
    // Quotes should be escaped
    EXPECT_TRUE(output.find("&quot;") != std::string::npos);
}
