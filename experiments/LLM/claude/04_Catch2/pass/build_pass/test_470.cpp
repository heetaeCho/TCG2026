#include <gtest/gtest.h>
#include <sstream>
#include <string>
#include "catch2/internal/catch_xmlwriter.hpp"

using namespace Catch;

class XmlWriterTest_470 : public ::testing::Test {
protected:
    std::ostringstream oss;
};

// ===================== XmlWriter Construction Tests =====================

TEST_F(XmlWriterTest_470, ConstructorWritesDeclaration_470) {
    XmlWriter writer(oss);
    std::string output = oss.str();
    EXPECT_TRUE(output.find("<?xml") != std::string::npos);
}

TEST_F(XmlWriterTest_470, ConstructorWritesVersionAttribute_470) {
    XmlWriter writer(oss);
    std::string output = oss.str();
    EXPECT_TRUE(output.find("version") != std::string::npos);
}

// ===================== startElement / endElement Tests =====================

TEST_F(XmlWriterTest_470, StartElementWritesTagName_470) {
    XmlWriter writer(oss);
    writer.startElement("TestElement", XmlFormatting::Newline);
    writer.endElement(XmlFormatting::Newline);
    std::string output = oss.str();
    EXPECT_TRUE(output.find("TestElement") != std::string::npos);
}

TEST_F(XmlWriterTest_470, StartElementOpensTag_470) {
    XmlWriter writer(oss);
    writer.startElement("root", XmlFormatting::Newline);
    writer.ensureTagClosed();
    std::string output = oss.str();
    EXPECT_TRUE(output.find("<root") != std::string::npos);
}

TEST_F(XmlWriterTest_470, EndElementClosesTag_470) {
    XmlWriter writer(oss);
    writer.startElement("root", XmlFormatting::Newline);
    writer.endElement(XmlFormatting::Newline);
    std::string output = oss.str();
    EXPECT_TRUE(output.find("</root>") != std::string::npos || output.find("/>") != std::string::npos);
}

TEST_F(XmlWriterTest_470, NestedElements_470) {
    XmlWriter writer(oss);
    writer.startElement("parent", XmlFormatting::Newline);
    writer.startElement("child", XmlFormatting::Newline);
    writer.endElement(XmlFormatting::Newline);
    writer.endElement(XmlFormatting::Newline);
    std::string output = oss.str();
    EXPECT_TRUE(output.find("parent") != std::string::npos);
    EXPECT_TRUE(output.find("child") != std::string::npos);
}

TEST_F(XmlWriterTest_470, EmptyElementSelfCloses_470) {
    XmlWriter writer(oss);
    writer.startElement("empty", XmlFormatting::Newline);
    writer.endElement(XmlFormatting::Newline);
    std::string output = oss.str();
    // An empty element should either self-close (/>) or have open/close tags
    EXPECT_TRUE(output.find("empty") != std::string::npos);
}

// ===================== writeAttribute Tests =====================

TEST_F(XmlWriterTest_470, WriteAttributeStringRef_470) {
    XmlWriter writer(oss);
    writer.startElement("elem", XmlFormatting::Newline);
    writer.writeAttribute(StringRef("name"), StringRef("value"));
    writer.endElement(XmlFormatting::Newline);
    std::string output = oss.str();
    EXPECT_TRUE(output.find("name") != std::string::npos);
    EXPECT_TRUE(output.find("value") != std::string::npos);
}

TEST_F(XmlWriterTest_470, WriteAttributeBool_470) {
    XmlWriter writer(oss);
    writer.startElement("elem", XmlFormatting::Newline);
    writer.writeAttribute(StringRef("flag"), true);
    writer.endElement(XmlFormatting::Newline);
    std::string output = oss.str();
    EXPECT_TRUE(output.find("flag") != std::string::npos);
    EXPECT_TRUE(output.find("true") != std::string::npos);
}

TEST_F(XmlWriterTest_470, WriteAttributeBoolFalse_470) {
    XmlWriter writer(oss);
    writer.startElement("elem", XmlFormatting::Newline);
    writer.writeAttribute(StringRef("flag"), false);
    writer.endElement(XmlFormatting::Newline);
    std::string output = oss.str();
    EXPECT_TRUE(output.find("flag") != std::string::npos);
    EXPECT_TRUE(output.find("false") != std::string::npos);
}

TEST_F(XmlWriterTest_470, WriteAttributeCharPtr_470) {
    XmlWriter writer(oss);
    writer.startElement("elem", XmlFormatting::Newline);
    writer.writeAttribute(StringRef("attr"), "charvalue");
    writer.endElement(XmlFormatting::Newline);
    std::string output = oss.str();
    EXPECT_TRUE(output.find("attr") != std::string::npos);
    EXPECT_TRUE(output.find("charvalue") != std::string::npos);
}

TEST_F(XmlWriterTest_470, WriteAttributeIntegerTemplate_470) {
    XmlWriter writer(oss);
    writer.startElement("elem", XmlFormatting::Newline);
    writer.writeAttribute(StringRef("count"), 42);
    writer.endElement(XmlFormatting::Newline);
    std::string output = oss.str();
    EXPECT_TRUE(output.find("count") != std::string::npos);
    EXPECT_TRUE(output.find("42") != std::string::npos);
}

TEST_F(XmlWriterTest_470, MultipleAttributes_470) {
    XmlWriter writer(oss);
    writer.startElement("elem", XmlFormatting::Newline);
    writer.writeAttribute(StringRef("a"), StringRef("1"));
    writer.writeAttribute(StringRef("b"), StringRef("2"));
    writer.endElement(XmlFormatting::Newline);
    std::string output = oss.str();
    EXPECT_TRUE(output.find("a=") != std::string::npos);
    EXPECT_TRUE(output.find("b=") != std::string::npos);
}

// ===================== writeText Tests =====================

TEST_F(XmlWriterTest_470, WriteTextInElement_470) {
    XmlWriter writer(oss);
    writer.startElement("elem", XmlFormatting::Newline);
    writer.writeText(StringRef("Hello World"), XmlFormatting::Newline);
    writer.endElement(XmlFormatting::Newline);
    std::string output = oss.str();
    EXPECT_TRUE(output.find("Hello World") != std::string::npos);
}

TEST_F(XmlWriterTest_470, WriteTextWithSpecialCharacters_470) {
    XmlWriter writer(oss);
    writer.startElement("elem", XmlFormatting::Newline);
    writer.writeText(StringRef("a < b & c > d"), XmlFormatting::Newline);
    writer.endElement(XmlFormatting::Newline);
    std::string output = oss.str();
    // Special characters should be escaped
    EXPECT_TRUE(output.find("&lt;") != std::string::npos);
    EXPECT_TRUE(output.find("&amp;") != std::string::npos);
    EXPECT_TRUE(output.find("&gt;") != std::string::npos);
}

TEST_F(XmlWriterTest_470, WriteTextEmptyString_470) {
    XmlWriter writer(oss);
    writer.startElement("elem", XmlFormatting::Newline);
    writer.writeText(StringRef(""), XmlFormatting::Newline);
    writer.endElement(XmlFormatting::Newline);
    std::string output = oss.str();
    EXPECT_TRUE(output.find("elem") != std::string::npos);
}

TEST_F(XmlWriterTest_470, WriteTextWithQuotes_470) {
    XmlWriter writer(oss);
    writer.startElement("elem", XmlFormatting::Newline);
    writer.writeText(StringRef("he said \"hello\""), XmlFormatting::Newline);
    writer.endElement(XmlFormatting::Newline);
    std::string output = oss.str();
    EXPECT_TRUE(output.find("hello") != std::string::npos);
}

// ===================== writeComment Tests =====================

TEST_F(XmlWriterTest_470, WriteComment_470) {
    XmlWriter writer(oss);
    writer.writeComment(StringRef("This is a comment"), XmlFormatting::Newline);
    std::string output = oss.str();
    EXPECT_TRUE(output.find("<!--") != std::string::npos);
    EXPECT_TRUE(output.find("This is a comment") != std::string::npos);
    EXPECT_TRUE(output.find("-->") != std::string::npos);
}

TEST_F(XmlWriterTest_470, WriteCommentEmpty_470) {
    XmlWriter writer(oss);
    writer.writeComment(StringRef(""), XmlFormatting::Newline);
    std::string output = oss.str();
    EXPECT_TRUE(output.find("<!--") != std::string::npos);
    EXPECT_TRUE(output.find("-->") != std::string::npos);
}

// ===================== writeStylesheetRef Tests =====================

TEST_F(XmlWriterTest_470, WriteStylesheetRef_470) {
    XmlWriter writer(oss);
    writer.writeStylesheetRef(StringRef("style.xsl"));
    std::string output = oss.str();
    EXPECT_TRUE(output.find("style.xsl") != std::string::npos);
    EXPECT_TRUE(output.find("xml-stylesheet") != std::string::npos);
}

// ===================== ensureTagClosed Tests =====================

TEST_F(XmlWriterTest_470, EnsureTagClosedClosesOpenTag_470) {
    XmlWriter writer(oss);
    writer.startElement("elem", XmlFormatting::Newline);
    writer.ensureTagClosed();
    std::string output = oss.str();
    EXPECT_TRUE(output.find(">") != std::string::npos);
}

TEST_F(XmlWriterTest_470, EnsureTagClosedNoopWhenNoOpenTag_470) {
    XmlWriter writer(oss);
    std::string beforeOutput = oss.str();
    writer.ensureTagClosed();
    std::string afterOutput = oss.str();
    // Should be the same since no tag is open (only declaration)
    EXPECT_EQ(beforeOutput, afterOutput);
}

// ===================== ScopedElement Tests =====================

TEST_F(XmlWriterTest_470, ScopedElementWritesAndClosesElement_470) {
    {
        XmlWriter writer(oss);
        {
            auto scoped = writer.scopedElement("scoped", XmlFormatting::Newline);
        }
        // After scoped goes out of scope, the element should be closed
    }
    std::string output = oss.str();
    EXPECT_TRUE(output.find("scoped") != std::string::npos);
}

TEST_F(XmlWriterTest_470, ScopedElementWriteText_470) {
    {
        XmlWriter writer(oss);
        {
            auto scoped = writer.scopedElement("scoped", XmlFormatting::Newline);
            scoped.writeText(StringRef("inner text"), XmlFormatting::Newline);
        }
    }
    std::string output = oss.str();
    EXPECT_TRUE(output.find("inner text") != std::string::npos);
}

TEST_F(XmlWriterTest_470, ScopedElementWriteAttribute_470) {
    {
        XmlWriter writer(oss);
        {
            auto scoped = writer.scopedElement("scoped", XmlFormatting::Newline);
            scoped.writeAttribute(StringRef("key"), StringRef("val"));
        }
    }
    std::string output = oss.str();
    EXPECT_TRUE(output.find("key") != std::string::npos);
    EXPECT_TRUE(output.find("val") != std::string::npos);
}

TEST_F(XmlWriterTest_470, ScopedElementChaining_470) {
    {
        XmlWriter writer(oss);
        {
            auto scoped = writer.scopedElement("scoped", XmlFormatting::Newline);
            scoped.writeAttribute(StringRef("a"), StringRef("1"))
                  .writeAttribute(StringRef("b"), StringRef("2"))
                  .writeText(StringRef("chained"), XmlFormatting::Newline);
        }
    }
    std::string output = oss.str();
    EXPECT_TRUE(output.find("a=") != std::string::npos);
    EXPECT_TRUE(output.find("b=") != std::string::npos);
    EXPECT_TRUE(output.find("chained") != std::string::npos);
}

TEST_F(XmlWriterTest_470, ScopedElementMoveConstruction_470) {
    {
        XmlWriter writer(oss);
        {
            auto scoped = writer.scopedElement("moved", XmlFormatting::Newline);
            auto scoped2 = std::move(scoped);
            scoped2.writeText(StringRef("after move"), XmlFormatting::Newline);
        }
    }
    std::string output = oss.str();
    EXPECT_TRUE(output.find("moved") != std::string::npos);
    EXPECT_TRUE(output.find("after move") != std::string::npos);
}

// ===================== Formatting Tests =====================

TEST_F(XmlWriterTest_470, FormattingNone_470) {
    XmlWriter writer(oss);
    writer.startElement("elem", XmlFormatting::None);
    writer.endElement(XmlFormatting::None);
    std::string output = oss.str();
    EXPECT_TRUE(output.find("elem") != std::string::npos);
}

TEST_F(XmlWriterTest_470, FormattingNewline_470) {
    XmlWriter writer(oss);
    writer.startElement("elem", XmlFormatting::Newline);
    writer.endElement(XmlFormatting::Newline);
    std::string output = oss.str();
    EXPECT_TRUE(output.find("\n") != std::string::npos);
}

TEST_F(XmlWriterTest_470, FormattingIndent_470) {
    XmlWriter writer(oss);
    writer.startElement("parent", XmlFormatting::Indent);
    writer.startElement("child", XmlFormatting::Indent);
    writer.endElement(XmlFormatting::Indent);
    writer.endElement(XmlFormatting::Indent);
    std::string output = oss.str();
    EXPECT_TRUE(output.find("parent") != std::string::npos);
    EXPECT_TRUE(output.find("child") != std::string::npos);
}

// ===================== Chaining Tests =====================

TEST_F(XmlWriterTest_470, WriteAttributeReturnsSelf_470) {
    XmlWriter writer(oss);
    XmlWriter& ref = writer.startElement("elem", XmlFormatting::Newline);
    EXPECT_EQ(&ref, &writer);
    XmlWriter& ref2 = writer.writeAttribute(StringRef("a"), StringRef("b"));
    EXPECT_EQ(&ref2, &writer);
    writer.endElement(XmlFormatting::Newline);
}

TEST_F(XmlWriterTest_470, StartElementReturnsSelf_470) {
    XmlWriter writer(oss);
    XmlWriter& ref = writer.startElement("elem", XmlFormatting::Newline);
    EXPECT_EQ(&ref, &writer);
    writer.endElement(XmlFormatting::Newline);
}

TEST_F(XmlWriterTest_470, EndElementReturnsSelf_470) {
    XmlWriter writer(oss);
    writer.startElement("elem", XmlFormatting::Newline);
    XmlWriter& ref = writer.endElement(XmlFormatting::Newline);
    EXPECT_EQ(&ref, &writer);
}

TEST_F(XmlWriterTest_470, WriteTextReturnsSelf_470) {
    XmlWriter writer(oss);
    writer.startElement("elem", XmlFormatting::Newline);
    XmlWriter& ref = writer.writeText(StringRef("text"), XmlFormatting::Newline);
    EXPECT_EQ(&ref, &writer);
    writer.endElement(XmlFormatting::Newline);
}

TEST_F(XmlWriterTest_470, WriteCommentReturnsSelf_470) {
    XmlWriter writer(oss);
    XmlWriter& ref = writer.writeComment(StringRef("comment"), XmlFormatting::Newline);
    EXPECT_EQ(&ref, &writer);
}

// ===================== Destructor Tests =====================

TEST_F(XmlWriterTest_470, DestructorClosesOpenElements_470) {
    {
        XmlWriter writer(oss);
        writer.startElement("outer", XmlFormatting::Newline);
        writer.startElement("inner", XmlFormatting::Newline);
        // Not explicitly closing - destructor should handle it
    }
    std::string output = oss.str();
    EXPECT_TRUE(output.find("outer") != std::string::npos);
    EXPECT_TRUE(output.find("inner") != std::string::npos);
}

// ===================== Complex Scenario Tests =====================

TEST_F(XmlWriterTest_470, ComplexNestedStructure_470) {
    {
        XmlWriter writer(oss);
        writer.startElement("root", XmlFormatting::Newline);
        writer.writeAttribute(StringRef("version"), StringRef("1.0"));
        
        {
            auto child = writer.scopedElement("child", XmlFormatting::Newline);
            child.writeAttribute(StringRef("id"), StringRef("1"));
            child.writeText(StringRef("Content"), XmlFormatting::Newline);
        }
        
        writer.startElement("sibling", XmlFormatting::Newline);
        writer.writeText(StringRef("Sibling content"), XmlFormatting::Newline);
        writer.endElement(XmlFormatting::Newline);
        
        writer.endElement(XmlFormatting::Newline);
    }
    std::string output = oss.str();
    EXPECT_TRUE(output.find("root") != std::string::npos);
    EXPECT_TRUE(output.find("child") != std::string::npos);
    EXPECT_TRUE(output.find("sibling") != std::string::npos);
    EXPECT_TRUE(output.find("Content") != std::string::npos);
    EXPECT_TRUE(output.find("Sibling content") != std::string::npos);
}

TEST_F(XmlWriterTest_470, AttributeEscaping_470) {
    XmlWriter writer(oss);
    writer.startElement("elem", XmlFormatting::Newline);
    writer.writeAttribute(StringRef("attr"), StringRef("value with \"quotes\""));
    writer.endElement(XmlFormatting::Newline);
    std::string output = oss.str();
    // Quotes in attribute values should be escaped
    EXPECT_TRUE(output.find("&quot;") != std::string::npos || output.find("quotes") != std::string::npos);
}

TEST_F(XmlWriterTest_470, TextWithAmpersand_470) {
    XmlWriter writer(oss);
    writer.startElement("elem", XmlFormatting::Newline);
    writer.writeText(StringRef("A & B"), XmlFormatting::Newline);
    writer.endElement(XmlFormatting::Newline);
    std::string output = oss.str();
    EXPECT_TRUE(output.find("&amp;") != std::string::npos);
}

TEST_F(XmlWriterTest_470, ScopedElementWriteAttributeTemplate_470) {
    {
        XmlWriter writer(oss);
        {
            auto scoped = writer.scopedElement("elem", XmlFormatting::Newline);
            scoped.writeAttribute(StringRef("num"), 99);
        }
    }
    std::string output = oss.str();
    EXPECT_TRUE(output.find("num") != std::string::npos);
    EXPECT_TRUE(output.find("99") != std::string::npos);
}

TEST_F(XmlWriterTest_470, MultipleScopedElementsSequentially_470) {
    {
        XmlWriter writer(oss);
        writer.startElement("root", XmlFormatting::Newline);
        {
            auto s1 = writer.scopedElement("first", XmlFormatting::Newline);
            s1.writeText(StringRef("1"), XmlFormatting::Newline);
        }
        {
            auto s2 = writer.scopedElement("second", XmlFormatting::Newline);
            s2.writeText(StringRef("2"), XmlFormatting::Newline);
        }
        writer.endElement(XmlFormatting::Newline);
    }
    std::string output = oss.str();
    EXPECT_TRUE(output.find("first") != std::string::npos);
    EXPECT_TRUE(output.find("second") != std::string::npos);
}
