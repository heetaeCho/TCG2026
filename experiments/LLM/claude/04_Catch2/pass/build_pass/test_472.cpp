#include <gtest/gtest.h>
#include <sstream>
#include <string>
#include "catch2/internal/catch_xmlwriter.hpp"

using namespace Catch;

class XmlWriterTest_472 : public ::testing::Test {
protected:
    std::ostringstream oss;
};

// Test: Constructor writes XML declaration
TEST_F(XmlWriterTest_472, ConstructorWritesDeclaration_472) {
    XmlWriter writer(oss);
    std::string output = oss.str();
    EXPECT_TRUE(output.find("<?xml") != std::string::npos);
}

// Test: Destructor closes all open tags
TEST_F(XmlWriterTest_472, DestructorClosesAllOpenTags_472) {
    {
        XmlWriter writer(oss);
        writer.startElement("root");
        writer.startElement("child");
    }
    std::string output = oss.str();
    EXPECT_TRUE(output.find("</child>") != std::string::npos);
    EXPECT_TRUE(output.find("</root>") != std::string::npos);
}

// Test: startElement creates an opening tag
TEST_F(XmlWriterTest_472, StartElementCreatesOpeningTag_472) {
    XmlWriter writer(oss);
    writer.startElement("TestElement");
    writer.endElement();
    std::string output = oss.str();
    EXPECT_TRUE(output.find("<TestElement") != std::string::npos);
    EXPECT_TRUE(output.find("</TestElement>") != std::string::npos);
}

// Test: endElement closes the most recent tag
TEST_F(XmlWriterTest_472, EndElementClosesRecentTag_472) {
    XmlWriter writer(oss);
    writer.startElement("outer");
    writer.startElement("inner");
    writer.endElement();
    writer.endElement();
    std::string output = oss.str();
    EXPECT_TRUE(output.find("</inner>") != std::string::npos);
    EXPECT_TRUE(output.find("</outer>") != std::string::npos);
}

// Test: writeAttribute adds attribute to element (StringRef)
TEST_F(XmlWriterTest_472, WriteAttributeStringRef_472) {
    XmlWriter writer(oss);
    writer.startElement("elem");
    writer.writeAttribute("name"_catch_sr, "value"_catch_sr);
    writer.endElement();
    std::string output = oss.str();
    EXPECT_TRUE(output.find("name=\"value\"") != std::string::npos);
}

// Test: writeAttribute with bool true
TEST_F(XmlWriterTest_472, WriteAttributeBoolTrue_472) {
    XmlWriter writer(oss);
    writer.startElement("elem");
    writer.writeAttribute("flag"_catch_sr, true);
    writer.endElement();
    std::string output = oss.str();
    EXPECT_TRUE(output.find("flag=\"true\"") != std::string::npos);
}

// Test: writeAttribute with bool false
TEST_F(XmlWriterTest_472, WriteAttributeBoolFalse_472) {
    XmlWriter writer(oss);
    writer.startElement("elem");
    writer.writeAttribute("flag"_catch_sr, false);
    writer.endElement();
    std::string output = oss.str();
    EXPECT_TRUE(output.find("flag=\"false\"") != std::string::npos);
}

// Test: writeAttribute with const char*
TEST_F(XmlWriterTest_472, WriteAttributeConstCharPtr_472) {
    XmlWriter writer(oss);
    writer.startElement("elem");
    const char* val = "myvalue";
    writer.writeAttribute("attr"_catch_sr, val);
    writer.endElement();
    std::string output = oss.str();
    EXPECT_TRUE(output.find("attr=\"myvalue\"") != std::string::npos);
}

// Test: writeText writes text content
TEST_F(XmlWriterTest_472, WriteTextContent_472) {
    XmlWriter writer(oss);
    writer.startElement("elem");
    writer.writeText("Hello World"_catch_sr, XmlFormatting::None);
    writer.endElement();
    std::string output = oss.str();
    EXPECT_TRUE(output.find("Hello World") != std::string::npos);
}

// Test: writeComment writes XML comment
TEST_F(XmlWriterTest_472, WriteComment_472) {
    XmlWriter writer(oss);
    writer.writeComment("This is a comment"_catch_sr, XmlFormatting::None);
    std::string output = oss.str();
    EXPECT_TRUE(output.find("<!--") != std::string::npos);
    EXPECT_TRUE(output.find("This is a comment") != std::string::npos);
    EXPECT_TRUE(output.find("-->") != std::string::npos);
}

// Test: writeStylesheetRef writes a processing instruction
TEST_F(XmlWriterTest_472, WriteStylesheetRef_472) {
    XmlWriter writer(oss);
    writer.writeStylesheetRef("style.xsl"_catch_sr);
    std::string output = oss.str();
    EXPECT_TRUE(output.find("style.xsl") != std::string::npos);
    EXPECT_TRUE(output.find("<?xml-stylesheet") != std::string::npos);
}

// Test: scopedElement auto-closes on scope exit
TEST_F(XmlWriterTest_472, ScopedElementAutoCloses_472) {
    XmlWriter writer(oss);
    writer.startElement("root");
    {
        auto scoped = writer.scopedElement("scoped");
    }
    writer.endElement();
    std::string output = oss.str();
    EXPECT_TRUE(output.find("<scoped") != std::string::npos);
    EXPECT_TRUE(output.find("</scoped>") != std::string::npos);
}

// Test: Nested elements produce properly nested XML
TEST_F(XmlWriterTest_472, NestedElementsProperNesting_472) {
    XmlWriter writer(oss);
    writer.startElement("a");
    writer.startElement("b");
    writer.startElement("c");
    writer.endElement(); // c
    writer.endElement(); // b
    writer.endElement(); // a
    std::string output = oss.str();
    // Check closing order
    auto posCloseC = output.find("</c>");
    auto posCloseB = output.find("</b>");
    auto posCloseA = output.find("</a>");
    EXPECT_TRUE(posCloseC != std::string::npos);
    EXPECT_TRUE(posCloseB != std::string::npos);
    EXPECT_TRUE(posCloseA != std::string::npos);
    EXPECT_LT(posCloseC, posCloseB);
    EXPECT_LT(posCloseB, posCloseA);
}

// Test: ensureTagClosed closes the current open tag
TEST_F(XmlWriterTest_472, EnsureTagClosed_472) {
    XmlWriter writer(oss);
    writer.startElement("elem");
    writer.ensureTagClosed();
    std::string output = oss.str();
    EXPECT_TRUE(output.find(">") != std::string::npos);
}

// Test: writeText with special characters is escaped
TEST_F(XmlWriterTest_472, WriteTextEscapesSpecialChars_472) {
    XmlWriter writer(oss);
    writer.startElement("elem");
    writer.writeText("<>&\""_catch_sr, XmlFormatting::None);
    writer.endElement();
    std::string output = oss.str();
    // Should not contain raw < or > inside text (they should be escaped)
    // After the closing of the tag, we check for escaped versions
    EXPECT_TRUE(output.find("&lt;") != std::string::npos);
    EXPECT_TRUE(output.find("&gt;") != std::string::npos);
    EXPECT_TRUE(output.find("&amp;") != std::string::npos);
}

// Test: writeAttribute escapes special characters in attribute values
TEST_F(XmlWriterTest_472, WriteAttributeEscapesSpecialChars_472) {
    XmlWriter writer(oss);
    writer.startElement("elem");
    writer.writeAttribute("key"_catch_sr, "a<b>c&d\"e"_catch_sr);
    writer.endElement();
    std::string output = oss.str();
    EXPECT_TRUE(output.find("&lt;") != std::string::npos);
    EXPECT_TRUE(output.find("&gt;") != std::string::npos);
    EXPECT_TRUE(output.find("&amp;") != std::string::npos);
    EXPECT_TRUE(output.find("&quot;") != std::string::npos);
}

// Test: Multiple attributes on same element
TEST_F(XmlWriterTest_472, MultipleAttributes_472) {
    XmlWriter writer(oss);
    writer.startElement("elem");
    writer.writeAttribute("a"_catch_sr, "1"_catch_sr);
    writer.writeAttribute("b"_catch_sr, "2"_catch_sr);
    writer.endElement();
    std::string output = oss.str();
    EXPECT_TRUE(output.find("a=\"1\"") != std::string::npos);
    EXPECT_TRUE(output.find("b=\"2\"") != std::string::npos);
}

// Test: startElement returns reference to self for chaining
TEST_F(XmlWriterTest_472, StartElementReturnsSelfReference_472) {
    XmlWriter writer(oss);
    XmlWriter& ref = writer.startElement("elem");
    EXPECT_EQ(&ref, &writer);
    writer.endElement();
}

// Test: endElement returns reference to self for chaining
TEST_F(XmlWriterTest_472, EndElementReturnsSelfReference_472) {
    XmlWriter writer(oss);
    writer.startElement("elem");
    XmlWriter& ref = writer.endElement();
    EXPECT_EQ(&ref, &writer);
}

// Test: writeAttribute returns reference to self for chaining
TEST_F(XmlWriterTest_472, WriteAttributeReturnsSelfReference_472) {
    XmlWriter writer(oss);
    writer.startElement("elem");
    XmlWriter& ref = writer.writeAttribute("key"_catch_sr, "val"_catch_sr);
    EXPECT_EQ(&ref, &writer);
    writer.endElement();
}

// Test: writeText returns reference to self for chaining
TEST_F(XmlWriterTest_472, WriteTextReturnsSelfReference_472) {
    XmlWriter writer(oss);
    writer.startElement("elem");
    XmlWriter& ref = writer.writeText("text"_catch_sr, XmlFormatting::None);
    EXPECT_EQ(&ref, &writer);
    writer.endElement();
}

// Test: writeComment returns reference to self for chaining
TEST_F(XmlWriterTest_472, WriteCommentReturnsSelfReference_472) {
    XmlWriter writer(oss);
    XmlWriter& ref = writer.writeComment("comment"_catch_sr, XmlFormatting::None);
    EXPECT_EQ(&ref, &writer);
}

// Test: Empty element (start then immediately end)
TEST_F(XmlWriterTest_472, EmptyElement_472) {
    XmlWriter writer(oss);
    writer.startElement("empty");
    writer.endElement();
    std::string output = oss.str();
    // Should have either <empty/> or <empty></empty>
    bool selfClosing = output.find("<empty/>") != std::string::npos;
    bool openClose = output.find("<empty>") != std::string::npos && output.find("</empty>") != std::string::npos;
    EXPECT_TRUE(selfClosing || openClose);
}

// Test: writeAttribute with numeric type (template version)
TEST_F(XmlWriterTest_472, WriteAttributeNumeric_472) {
    XmlWriter writer(oss);
    writer.startElement("elem");
    writer.writeAttribute("count"_catch_sr, 42);
    writer.endElement();
    std::string output = oss.str();
    EXPECT_TRUE(output.find("count=\"42\"") != std::string::npos);
}

// Test: Writing with XmlFormatting::Newline
TEST_F(XmlWriterTest_472, WriteTextWithNewlineFormatting_472) {
    XmlWriter writer(oss);
    writer.startElement("elem", XmlFormatting::Newline);
    writer.writeText("text"_catch_sr, XmlFormatting::Newline);
    writer.endElement(XmlFormatting::Newline);
    std::string output = oss.str();
    // Just verify it doesn't crash and produces output
    EXPECT_FALSE(output.empty());
}

// Test: No elements - only declaration
TEST_F(XmlWriterTest_472, NoElementsOnlyDeclaration_472) {
    {
        XmlWriter writer(oss);
    }
    std::string output = oss.str();
    EXPECT_TRUE(output.find("<?xml") != std::string::npos);
}

// Test: writeText with empty string
TEST_F(XmlWriterTest_472, WriteTextEmptyString_472) {
    XmlWriter writer(oss);
    writer.startElement("elem");
    writer.writeText(""_catch_sr, XmlFormatting::None);
    writer.endElement();
    std::string output = oss.str();
    EXPECT_TRUE(output.find("elem") != std::string::npos);
}

// Test: writeComment with empty string
TEST_F(XmlWriterTest_472, WriteCommentEmptyString_472) {
    XmlWriter writer(oss);
    writer.writeComment(""_catch_sr, XmlFormatting::None);
    std::string output = oss.str();
    EXPECT_TRUE(output.find("<!--") != std::string::npos);
    EXPECT_TRUE(output.find("-->") != std::string::npos);
}

// Test: Copy constructor and assignment are deleted (compile-time check - just structural)
// This is verified by the fact that the class declares them as deleted.
// We don't test compile failures, but we note it here.

// Test: Deeply nested elements
TEST_F(XmlWriterTest_472, DeeplyNestedElements_472) {
    XmlWriter writer(oss);
    const int depth = 20;
    for (int i = 0; i < depth; ++i) {
        writer.startElement("level");
    }
    for (int i = 0; i < depth; ++i) {
        writer.endElement();
    }
    std::string output = oss.str();
    // Count occurrences of </level>
    size_t count = 0;
    size_t pos = 0;
    while ((pos = output.find("</level>", pos)) != std::string::npos) {
        ++count;
        pos += 8;
    }
    EXPECT_EQ(count, static_cast<size_t>(depth));
}

// Test: Interleaved text and child elements
TEST_F(XmlWriterTest_472, InterleavedTextAndChildren_472) {
    XmlWriter writer(oss);
    writer.startElement("parent");
    writer.writeText("before"_catch_sr, XmlFormatting::None);
    writer.startElement("child");
    writer.endElement();
    writer.writeText("after"_catch_sr, XmlFormatting::None);
    writer.endElement();
    std::string output = oss.str();
    EXPECT_TRUE(output.find("before") != std::string::npos);
    EXPECT_TRUE(output.find("after") != std::string::npos);
    EXPECT_TRUE(output.find("<child") != std::string::npos);
}
