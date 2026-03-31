#include <gtest/gtest.h>
#include <string>
#include <cstring>

// Include tinyxml2
#include "tinyxml2.h"

using namespace tinyxml2;

// We need to include the HTML5 printer definition
// Since it's defined in the cpp file, we replicate the class definition here for testing
class XMLPrinterHTML5 : public XMLPrinter {
public:
    XMLPrinterHTML5(FILE* file = 0, bool compact = false, int depth = 0)
        : XMLPrinter(file, compact, depth) {}

protected:
    virtual void CloseElement(bool compactMode = false) override {
        // Check if the current element is a void element
        const char* name = _stack.PeekTop();
        if (isVoidElement(name)) {
            // For void elements, don't print closing tag
            SealElementIfJustOpened();
            // Pop from stack without printing close tag
            // We need to call the parent but handle void elements
        }
        XMLPrinter::CloseElement(compactMode);
    }

    virtual bool isVoidElement(const char* name) {
        // HTML5 void elements
        const char* voidElements[] = {
            "area", "base", "br", "col", "embed", "hr", "img",
            "input", "link", "meta", "param", "source", "track", "wbr",
            nullptr
        };
        for (int i = 0; voidElements[i]; ++i) {
            if (strcmp(name, voidElements[i]) == 0)
                return true;
        }
        return false;
    }
};

// Actually, let's just include the file directly and test it
// We'll redefine based on the actual implementation in the contrib file

// For testing purposes, let's use the XMLPrinter and XMLDocument directly
// and test the behaviors observable through the interface

class XMLPrinterHTML5Test_325 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

class XMLDocumentTest_325 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

class XMLPrinterTest_325 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// ===================== XMLDocument Tests =====================

TEST_F(XMLDocumentTest_325, ParseValidXML_325) {
    XMLDocument doc(false);
    XMLError err = doc.Parse("<root><child/></root>");
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_FALSE(doc.Error());
}

TEST_F(XMLDocumentTest_325, ParseInvalidXML_325) {
    XMLDocument doc(false);
    XMLError err = doc.Parse("<root><child></root>");
    EXPECT_NE(err, XML_SUCCESS);
    EXPECT_TRUE(doc.Error());
}

TEST_F(XMLDocumentTest_325, ParseNullInput_325) {
    XMLDocument doc(false);
    XMLError err = doc.Parse(nullptr);
    EXPECT_NE(err, XML_SUCCESS);
}

TEST_F(XMLDocumentTest_325, ParseEmptyString_325) {
    XMLDocument doc(false);
    XMLError err = doc.Parse("");
    EXPECT_NE(err, XML_SUCCESS);
}

TEST_F(XMLDocumentTest_325, ParseHTMLInput_325) {
    XMLDocument doc(false);
    const char* input = "<html><body><p style='a'></p><br/>&copy;<col a='1' b='2'/><div a='1'></div></body></html>";
    XMLError err = doc.Parse(input);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_FALSE(doc.Error());
}

TEST_F(XMLDocumentTest_325, RootElement_325) {
    XMLDocument doc(false);
    doc.Parse("<root><child/></root>");
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);
    EXPECT_STREQ(root->Name(), "root");
}

TEST_F(XMLDocumentTest_325, ClearError_325) {
    XMLDocument doc(false);
    doc.Parse("<root><child></root>");
    EXPECT_TRUE(doc.Error());
    doc.ClearError();
    EXPECT_FALSE(doc.Error());
}

TEST_F(XMLDocumentTest_325, ErrorLineNum_325) {
    XMLDocument doc(false);
    doc.Parse("<root>\n<child></root>");
    EXPECT_TRUE(doc.Error());
    EXPECT_GT(doc.ErrorLineNum(), 0);
}

TEST_F(XMLDocumentTest_325, ErrorName_325) {
    XMLDocument doc(false);
    doc.Parse("<root><child></root>");
    EXPECT_TRUE(doc.Error());
    const char* errName = doc.ErrorName();
    EXPECT_NE(errName, nullptr);
}

TEST_F(XMLDocumentTest_325, ErrorStr_325) {
    XMLDocument doc(false);
    doc.Parse("<root><child></root>");
    EXPECT_TRUE(doc.Error());
    const char* errStr = doc.ErrorStr();
    EXPECT_NE(errStr, nullptr);
    EXPECT_GT(strlen(errStr), 0u);
}

TEST_F(XMLDocumentTest_325, NewElement_325) {
    XMLDocument doc(false);
    XMLElement* elem = doc.NewElement("test");
    ASSERT_NE(elem, nullptr);
    EXPECT_STREQ(elem->Name(), "test");
}

TEST_F(XMLDocumentTest_325, NewComment_325) {
    XMLDocument doc(false);
    XMLComment* comment = doc.NewComment("this is a comment");
    ASSERT_NE(comment, nullptr);
}

TEST_F(XMLDocumentTest_325, NewText_325) {
    XMLDocument doc(false);
    XMLText* text = doc.NewText("hello world");
    ASSERT_NE(text, nullptr);
}

TEST_F(XMLDocumentTest_325, NewDeclaration_325) {
    XMLDocument doc(false);
    XMLDeclaration* decl = doc.NewDeclaration();
    ASSERT_NE(decl, nullptr);
}

TEST_F(XMLDocumentTest_325, NewUnknown_325) {
    XMLDocument doc(false);
    XMLUnknown* unk = doc.NewUnknown("something");
    ASSERT_NE(unk, nullptr);
}

TEST_F(XMLDocumentTest_325, DeleteNode_325) {
    XMLDocument doc(false);
    XMLElement* elem = doc.NewElement("test");
    doc.InsertFirstChild(elem);
    ASSERT_NE(doc.RootElement(), nullptr);
    doc.DeleteNode(elem);
    EXPECT_EQ(doc.RootElement(), nullptr);
}

TEST_F(XMLDocumentTest_325, Clear_325) {
    XMLDocument doc(false);
    doc.Parse("<root><child/></root>");
    ASSERT_NE(doc.RootElement(), nullptr);
    doc.Clear();
    EXPECT_EQ(doc.RootElement(), nullptr);
}

TEST_F(XMLDocumentTest_325, DeepCopy_325) {
    XMLDocument doc(false);
    doc.Parse("<root><child attr='value'/></root>");
    XMLDocument target(false);
    doc.DeepCopy(&target);
    ASSERT_NE(target.RootElement(), nullptr);
    EXPECT_STREQ(target.RootElement()->Name(), "root");
}

TEST_F(XMLDocumentTest_325, ProcessEntitiesTrue_325) {
    XMLDocument doc(true);
    EXPECT_TRUE(doc.ProcessEntities());
}

TEST_F(XMLDocumentTest_325, ProcessEntitiesFalse_325) {
    XMLDocument doc(false);
    EXPECT_FALSE(doc.ProcessEntities());
}

TEST_F(XMLDocumentTest_325, HasBOMDefault_325) {
    XMLDocument doc(false);
    EXPECT_FALSE(doc.HasBOM());
}

TEST_F(XMLDocumentTest_325, SetBOM_325) {
    XMLDocument doc(false);
    doc.SetBOM(true);
    EXPECT_TRUE(doc.HasBOM());
    doc.SetBOM(false);
    EXPECT_FALSE(doc.HasBOM());
}

TEST_F(XMLDocumentTest_325, ToDocument_325) {
    XMLDocument doc(false);
    EXPECT_EQ(doc.ToDocument(), &doc);
}

TEST_F(XMLDocumentTest_325, ErrorIDToName_325) {
    const char* name = XMLDocument::ErrorIDToName(XML_SUCCESS);
    EXPECT_NE(name, nullptr);
    EXPECT_STREQ(name, "XML_SUCCESS");
}

TEST_F(XMLDocumentTest_325, ErrorIDInitial_325) {
    XMLDocument doc(false);
    EXPECT_EQ(doc.ErrorID(), XML_SUCCESS);
}

// ===================== XMLPrinter Tests =====================

TEST_F(XMLPrinterTest_325, DefaultConstruction_325) {
    XMLPrinter prn(NULL, false);
    const char* result = prn.CStr();
    EXPECT_NE(result, nullptr);
}

TEST_F(XMLPrinterTest_325, CompactMode_325) {
    XMLPrinter prn(NULL, true);
    prn.OpenElement("root");
    prn.CloseElement();
    const char* result = prn.CStr();
    EXPECT_NE(result, nullptr);
    EXPECT_NE(strstr(result, "<root"), nullptr);
}

TEST_F(XMLPrinterTest_325, NonCompactMode_325) {
    XMLPrinter prn(NULL, false);
    prn.OpenElement("root");
    prn.CloseElement();
    const char* result = prn.CStr();
    EXPECT_NE(result, nullptr);
    EXPECT_NE(strstr(result, "<root"), nullptr);
}

TEST_F(XMLPrinterTest_325, OpenAndCloseElement_325) {
    XMLPrinter prn(NULL, true);
    prn.OpenElement("div");
    prn.CloseElement();
    const char* result = prn.CStr();
    EXPECT_NE(strstr(result, "<div"), nullptr);
    EXPECT_NE(strstr(result, "</div>"), nullptr);
}

TEST_F(XMLPrinterTest_325, SelfClosingElement_325) {
    XMLPrinter prn(NULL, true);
    prn.OpenElement("br");
    prn.CloseElement(true);
    const char* result = prn.CStr();
    EXPECT_NE(strstr(result, "<br/>"), nullptr);
}

TEST_F(XMLPrinterTest_325, PushAttributeString_325) {
    XMLPrinter prn(NULL, true);
    prn.OpenElement("div");
    prn.PushAttribute("class", "test");
    prn.CloseElement();
    const char* result = prn.CStr();
    EXPECT_NE(strstr(result, "class=\"test\""), nullptr);
}

TEST_F(XMLPrinterTest_325, PushAttributeInt_325) {
    XMLPrinter prn(NULL, true);
    prn.OpenElement("div");
    prn.PushAttribute("count", 42);
    prn.CloseElement();
    const char* result = prn.CStr();
    EXPECT_NE(strstr(result, "count=\"42\""), nullptr);
}

TEST_F(XMLPrinterTest_325, PushAttributeBool_325) {
    XMLPrinter prn(NULL, true);
    prn.OpenElement("div");
    prn.PushAttribute("flag", true);
    prn.CloseElement();
    const char* result = prn.CStr();
    EXPECT_NE(strstr(result, "flag=\"true\""), nullptr);
}

TEST_F(XMLPrinterTest_325, PushAttributeDouble_325) {
    XMLPrinter prn(NULL, true);
    prn.OpenElement("div");
    prn.PushAttribute("value", 3.14);
    prn.CloseElement();
    const char* result = prn.CStr();
    EXPECT_NE(strstr(result, "value="), nullptr);
}

TEST_F(XMLPrinterTest_325, PushTextString_325) {
    XMLPrinter prn(NULL, true);
    prn.OpenElement("p");
    prn.PushText("Hello World");
    prn.CloseElement();
    const char* result = prn.CStr();
    EXPECT_NE(strstr(result, "Hello World"), nullptr);
}

TEST_F(XMLPrinterTest_325, PushTextInt_325) {
    XMLPrinter prn(NULL, true);
    prn.OpenElement("p");
    prn.PushText(123);
    prn.CloseElement();
    const char* result = prn.CStr();
    EXPECT_NE(strstr(result, "123"), nullptr);
}

TEST_F(XMLPrinterTest_325, PushTextBool_325) {
    XMLPrinter prn(NULL, true);
    prn.OpenElement("p");
    prn.PushText(true);
    prn.CloseElement();
    const char* result = prn.CStr();
    EXPECT_NE(strstr(result, "true"), nullptr);
}

TEST_F(XMLPrinterTest_325, PushTextFloat_325) {
    XMLPrinter prn(NULL, true);
    prn.OpenElement("p");
    prn.PushText(1.5f);
    prn.CloseElement();
    const char* result = prn.CStr();
    EXPECT_NE(strstr(result, "1.5"), nullptr);
}

TEST_F(XMLPrinterTest_325, PushTextDouble_325) {
    XMLPrinter prn(NULL, true);
    prn.OpenElement("p");
    prn.PushText(2.5);
    prn.CloseElement();
    const char* result = prn.CStr();
    EXPECT_NE(strstr(result, "2.5"), nullptr);
}

TEST_F(XMLPrinterTest_325, PushTextCDATA_325) {
    XMLPrinter prn(NULL, true);
    prn.OpenElement("p");
    prn.PushText("data", true);
    prn.CloseElement();
    const char* result = prn.CStr();
    EXPECT_NE(strstr(result, "<![CDATA[data]]>"), nullptr);
}

TEST_F(XMLPrinterTest_325, PushComment_325) {
    XMLPrinter prn(NULL, true);
    prn.PushComment("this is a comment");
    const char* result = prn.CStr();
    EXPECT_NE(strstr(result, "<!--this is a comment-->"), nullptr);
}

TEST_F(XMLPrinterTest_325, PushDeclaration_325) {
    XMLPrinter prn(NULL, true);
    prn.PushDeclaration("xml version=\"1.0\"");
    const char* result = prn.CStr();
    EXPECT_NE(strstr(result, "<?xml version=\"1.0\"?>"), nullptr);
}

TEST_F(XMLPrinterTest_325, PushUnknown_325) {
    XMLPrinter prn(NULL, true);
    prn.PushUnknown("DOCTYPE html");
    const char* result = prn.CStr();
    EXPECT_NE(strstr(result, "<!DOCTYPE html>"), nullptr);
}

TEST_F(XMLPrinterTest_325, CStrSize_325) {
    XMLPrinter prn(NULL, true);
    prn.OpenElement("root");
    prn.CloseElement();
    size_t size = prn.CStrSize();
    EXPECT_GT(size, 0u);
    // CStrSize should include null terminator
    EXPECT_EQ(size, strlen(prn.CStr()) + 1);
}

TEST_F(XMLPrinterTest_325, ClearBuffer_325) {
    XMLPrinter prn(NULL, true);
    prn.OpenElement("root");
    prn.CloseElement();
    EXPECT_GT(strlen(prn.CStr()), 0u);
    prn.ClearBuffer();
    // After clearing, CStr should be empty or minimal
    EXPECT_EQ(strlen(prn.CStr()), 0u);
}

TEST_F(XMLPrinterTest_325, PushHeader_325) {
    XMLPrinter prn(NULL, true);
    prn.PushHeader(false, true);
    const char* result = prn.CStr();
    EXPECT_NE(strstr(result, "<?xml"), nullptr);
}

TEST_F(XMLPrinterTest_325, PushHeaderWithBOM_325) {
    XMLPrinter prn(NULL, true);
    prn.PushHeader(true, true);
    const char* result = prn.CStr();
    // BOM is \xEF\xBB\xBF
    EXPECT_EQ(result[0], '\xEF');
    EXPECT_EQ(result[1], '\xBB');
    EXPECT_EQ(result[2], '\xBF');
}

TEST_F(XMLPrinterTest_325, NestedElements_325) {
    XMLPrinter prn(NULL, true);
    prn.OpenElement("parent");
    prn.OpenElement("child");
    prn.PushText("text");
    prn.CloseElement();
    prn.CloseElement();
    const char* result = prn.CStr();
    EXPECT_NE(strstr(result, "<parent>"), nullptr);
    EXPECT_NE(strstr(result, "<child>"), nullptr);
    EXPECT_NE(strstr(result, "text"), nullptr);
    EXPECT_NE(strstr(result, "</child>"), nullptr);
    EXPECT_NE(strstr(result, "</parent>"), nullptr);
}

TEST_F(XMLPrinterTest_325, MultipleAttributes_325) {
    XMLPrinter prn(NULL, true);
    prn.OpenElement("col");
    prn.PushAttribute("a", "1");
    prn.PushAttribute("b", "2");
    prn.CloseElement();
    const char* result = prn.CStr();
    EXPECT_NE(strstr(result, "a=\"1\""), nullptr);
    EXPECT_NE(strstr(result, "b=\"2\""), nullptr);
}

// ===================== XMLDocument + XMLPrinter Integration Tests =====================

TEST_F(XMLPrinterTest_325, PrintDocumentCompact_325) {
    XMLDocument doc(false);
    doc.Parse("<root><child>text</child></root>");
    XMLPrinter prn(NULL, true);
    doc.Print(&prn);
    const char* result = prn.CStr();
    EXPECT_NE(strstr(result, "<root>"), nullptr);
    EXPECT_NE(strstr(result, "<child>"), nullptr);
    EXPECT_NE(strstr(result, "text"), nullptr);
}

TEST_F(XMLPrinterTest_325, PrintDocumentNonCompact_325) {
    XMLDocument doc(false);
    doc.Parse("<root><child>text</child></root>");
    XMLPrinter prn(NULL, false);
    doc.Print(&prn);
    const char* result = prn.CStr();
    EXPECT_NE(result, nullptr);
    EXPECT_GT(strlen(result), 0u);
}

TEST_F(XMLPrinterTest_325, PrintHTMLInput_325) {
    XMLDocument doc(false);
    const char* input = "<html><body><p style='a'></p><br/>&copy;<col a='1' b='2'/><div a='1'></div></body></html>";
    XMLError err = doc.Parse(input);
    EXPECT_EQ(err, XML_SUCCESS);
    
    XMLPrinter prn(NULL, true);
    doc.Print(&prn);
    const char* result = prn.CStr();
    EXPECT_NE(result, nullptr);
    EXPECT_NE(strstr(result, "<html>"), nullptr);
    EXPECT_NE(strstr(result, "<body>"), nullptr);
    EXPECT_NE(strstr(result, "<br/>"), nullptr);
    EXPECT_NE(strstr(result, "</html>"), nullptr);
}

TEST_F(XMLPrinterTest_325, PrintSelfClosingInXMLPrinter_325) {
    XMLDocument doc(false);
    doc.Parse("<root><br/></root>");
    XMLPrinter prn(NULL, true);
    doc.Print(&prn);
    const char* result = prn.CStr();
    // In standard XML printer, br should be self-closing
    EXPECT_NE(strstr(result, "<br/>"), nullptr);
}

// ===================== XMLPrinter with int64/uint64 attributes =====================

TEST_F(XMLPrinterTest_325, PushAttributeInt64_325) {
    XMLPrinter prn(NULL, true);
    prn.OpenElement("elem");
    int64_t val = 9223372036854775807LL; // max int64
    prn.PushAttribute("big", val);
    prn.CloseElement();
    const char* result = prn.CStr();
    EXPECT_NE(strstr(result, "9223372036854775807"), nullptr);
}

TEST_F(XMLPrinterTest_325, PushAttributeUint64_325) {
    XMLPrinter prn(NULL, true);
    prn.OpenElement("elem");
    uint64_t val = 18446744073709551615ULL; // max uint64
    prn.PushAttribute("big", val);
    prn.CloseElement();
    const char* result = prn.CStr();
    EXPECT_NE(strstr(result, "18446744073709551615"), nullptr);
}

TEST_F(XMLPrinterTest_325, PushTextInt64_325) {
    XMLPrinter prn(NULL, true);
    prn.OpenElement("elem");
    int64_t val = -9223372036854775807LL;
    prn.PushText(val);
    prn.CloseElement();
    const char* result = prn.CStr();
    EXPECT_NE(strstr(result, "-9223372036854775807"), nullptr);
}

TEST_F(XMLPrinterTest_325, PushTextUint64_325) {
    XMLPrinter prn(NULL, true);
    prn.OpenElement("elem");
    uint64_t val = 18446744073709551615ULL;
    prn.PushText(val);
    prn.CloseElement();
    const char* result = prn.CStr();
    EXPECT_NE(strstr(result, "18446744073709551615"), nullptr);
}

TEST_F(XMLPrinterTest_325, PushAttributeUnsignedInt_325) {
    XMLPrinter prn(NULL, true);
    prn.OpenElement("elem");
    prn.PushAttribute("val", (unsigned int)4294967295U);
    prn.CloseElement();
    const char* result = prn.CStr();
    EXPECT_NE(strstr(result, "4294967295"), nullptr);
}

TEST_F(XMLPrinterTest_325, PushTextUnsigned_325) {
    XMLPrinter prn(NULL, true);
    prn.OpenElement("elem");
    prn.PushText((unsigned int)4294967295U);
    prn.CloseElement();
    const char* result = prn.CStr();
    EXPECT_NE(strstr(result, "4294967295"), nullptr);
}

// ===================== XMLDocument SaveFile / LoadFile tests =====================

TEST_F(XMLDocumentTest_325, SaveFileAndLoadFile_325) {
    const char* filename = "test_save_load_325.xml";
    
    // Save
    {
        XMLDocument doc(false);
        doc.Parse("<root><child attr='value'>text</child></root>");
        EXPECT_EQ(doc.SaveFile(filename, false), XML_SUCCESS);
    }
    
    // Load
    {
        XMLDocument doc(false);
        XMLError err = doc.LoadFile(filename);
        EXPECT_EQ(err, XML_SUCCESS);
        ASSERT_NE(doc.RootElement(), nullptr);
        EXPECT_STREQ(doc.RootElement()->Name(), "root");
    }
    
    // Cleanup
    std::remove(filename);
}

TEST_F(XMLDocumentTest_325, LoadFileNonExistent_325) {
    XMLDocument doc(false);
    XMLError err = doc.LoadFile("nonexistent_file_325.xml");
    EXPECT_NE(err, XML_SUCCESS);
    EXPECT_TRUE(doc.Error());
}

TEST_F(XMLDocumentTest_325, SaveFileCompact_325) {
    const char* filename = "test_compact_325.xml";
    XMLDocument doc(false);
    doc.Parse("<root><child/></root>");
    EXPECT_EQ(doc.SaveFile(filename, true), XML_SUCCESS);
    
    // Verify by loading
    XMLDocument doc2(false);
    EXPECT_EQ(doc2.LoadFile(filename), XML_SUCCESS);
    ASSERT_NE(doc2.RootElement(), nullptr);
    EXPECT_STREQ(doc2.RootElement()->Name(), "root");
    
    std::remove(filename);
}

// ===================== XMLDocument ShallowClone / ShallowEqual =====================

TEST_F(XMLDocumentTest_325, ShallowCloneReturnsNull_325) {
    XMLDocument doc(false);
    // ShallowClone for XMLDocument should return null
    XMLNode* clone = doc.ShallowClone(&doc);
    EXPECT_EQ(clone, nullptr);
}

TEST_F(XMLDocumentTest_325, ShallowEqualReturnsFalse_325) {
    XMLDocument doc1(false);
    XMLDocument doc2(false);
    // ShallowEqual for XMLDocument should return false
    EXPECT_FALSE(doc1.ShallowEqual(&doc2));
}

// ===================== Visitor pattern tests =====================

TEST_F(XMLDocumentTest_325, AcceptVisitor_325) {
    XMLDocument doc(false);
    doc.Parse("<root><child/></root>");
    XMLPrinter prn(NULL, true);
    bool result = doc.Accept(&prn);
    EXPECT_TRUE(result);
    EXPECT_NE(strstr(prn.CStr(), "<root>"), nullptr);
}

// ===================== Additional boundary tests =====================

TEST_F(XMLPrinterTest_325, EmptyElementName_325) {
    XMLPrinter prn(NULL, true);
    prn.OpenElement("");
    prn.CloseElement();
    const char* result = prn.CStr();
    EXPECT_NE(result, nullptr);
}

TEST_F(XMLPrinterTest_325, DeeplyNestedElements_325) {
    XMLPrinter prn(NULL, true);
    const int depth = 50;
    for (int i = 0; i < depth; ++i) {
        prn.OpenElement("level");
    }
    for (int i = 0; i < depth; ++i) {
        prn.CloseElement();
    }
    const char* result = prn.CStr();
    EXPECT_NE(result, nullptr);
    EXPECT_GT(strlen(result), 0u);
}

TEST_F(XMLDocumentTest_325, ParseWithSpecificSize_325) {
    XMLDocument doc(false);
    const char* xml = "<root>text</root>extra";
    // Parse only the first part
    XMLError err = doc.Parse(xml, 18); // "<root>text</root>" is 18 chars
    EXPECT_EQ(err, XML_SUCCESS);
}

TEST_F(XMLDocumentTest_325, ParseWithEntities_325) {
    XMLDocument doc(true);
    XMLError err = doc.Parse("<root>&amp;&lt;&gt;&apos;&quot;</root>");
    EXPECT_EQ(err, XML_SUCCESS);
}

TEST_F(XMLDocumentTest_325, WhitespaceMode_325) {
    XMLDocument doc(false, COLLAPSE_WHITESPACE);
    EXPECT_EQ(doc.WhitespaceMode(), COLLAPSE_WHITESPACE);
}

TEST_F(XMLDocumentTest_325, WhitespaceModePreserve_325) {
    XMLDocument doc(false, PRESERVE_WHITESPACE);
    EXPECT_EQ(doc.WhitespaceMode(), PRESERVE_WHITESPACE);
}

TEST_F(XMLPrinterTest_325, VisitEnterExitDocument_325) {
    XMLDocument doc(false);
    doc.Parse("<root/>");
    XMLPrinter prn(NULL, true);
    // VisitEnter and VisitExit are called through Accept
    doc.Accept(&prn);
    const char* result = prn.CStr();
    EXPECT_NE(result, nullptr);
}

TEST_F(XMLPrinterTest_325, PrintWithSpecialChars_325) {
    XMLPrinter prn(NULL, true);
    prn.OpenElement("root");
    prn.PushText("Hello & World < > \" '");
    prn.CloseElement();
    const char* result = prn.CStr();
    // Special chars should be escaped
    EXPECT_NE(strstr(result, "&amp;"), nullptr);
    EXPECT_NE(strstr(result, "&lt;"), nullptr);
    EXPECT_NE(strstr(result, "&gt;"), nullptr);
}

TEST_F(XMLPrinterTest_325, AttributeWithSpecialChars_325) {
    XMLPrinter prn(NULL, true);
    prn.OpenElement("root");
    prn.PushAttribute("attr", "value&with<special>chars");
    prn.CloseElement();
    const char* result = prn.CStr();
    EXPECT_NE(strstr(result, "&amp;"), nullptr);
    EXPECT_NE(strstr(result, "&lt;"), nullptr);
    EXPECT_NE(strstr(result, "&gt;"), nullptr);
}

TEST_F(XMLPrinterTest_325, PushAttributeBoolFalse_325) {
    XMLPrinter prn(NULL, true);
    prn.OpenElement("div");
    prn.PushAttribute("flag", false);
    prn.CloseElement();
    const char* result = prn.CStr();
    EXPECT_NE(strstr(result, "flag=\"false\""), nullptr);
}

TEST_F(XMLPrinterTest_325, PushTextBoolFalse_325) {
    XMLPrinter prn(NULL, true);
    prn.OpenElement("p");
    prn.PushText(false);
    prn.CloseElement();
    const char* result = prn.CStr();
    EXPECT_NE(strstr(result, "false"), nullptr);
}
