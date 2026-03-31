#include "gtest/gtest.h"
#include "tinyxml2.h"
#include <cstdio>
#include <cstring>
#include <string>

using namespace tinyxml2;

// Helper to create a temporary XML file
class TempXMLFile {
public:
    TempXMLFile(const char* filename, const char* content) : _filename(filename) {
        FILE* fp = fopen(filename, "wb");
        if (fp) {
            fwrite(content, 1, strlen(content), fp);
            fclose(fp);
        }
    }
    ~TempXMLFile() {
        remove(_filename.c_str());
    }
    const char* Filename() const { return _filename.c_str(); }
private:
    std::string _filename;
};

// ==================== XMLDocument Construction Tests ====================

TEST(XMLDocumentTest_279, DefaultConstruction_279) {
    XMLDocument doc;
    EXPECT_FALSE(doc.Error());
    EXPECT_EQ(doc.ErrorID(), XML_SUCCESS);
    EXPECT_EQ(doc.ErrorLineNum(), 0);
    EXPECT_FALSE(doc.HasBOM());
    EXPECT_TRUE(doc.ProcessEntities());
}

TEST(XMLDocumentTest_279, ConstructionWithProcessEntitiesFalse_279) {
    XMLDocument doc(false);
    EXPECT_TRUE(doc.ProcessEntities() == false);
    EXPECT_FALSE(doc.Error());
}

TEST(XMLDocumentTest_279, ConstructionWithWhitespaceMode_279) {
    XMLDocument doc(true, PRESERVE_WHITESPACE);
    EXPECT_EQ(doc.WhitespaceMode(), PRESERVE_WHITESPACE);
}

// ==================== LoadFile Tests ====================

TEST(XMLDocumentLoadFileTest_279, LoadFileNonExistent_279) {
    XMLDocument doc;
    XMLError err = doc.LoadFile("nonexistent_file_that_does_not_exist_279.xml");
    EXPECT_NE(err, XML_SUCCESS);
    EXPECT_EQ(err, XML_ERROR_FILE_NOT_FOUND);
    EXPECT_TRUE(doc.Error());
    EXPECT_EQ(doc.ErrorID(), XML_ERROR_FILE_NOT_FOUND);
}

TEST(XMLDocumentLoadFileTest_279, LoadFileValidXML_279) {
    const char* filename = "test_valid_279.xml";
    const char* content = "<?xml version=\"1.0\"?><root><child>text</child></root>";
    TempXMLFile tempFile(filename, content);

    XMLDocument doc;
    XMLError err = doc.LoadFile(filename);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_FALSE(doc.Error());
    EXPECT_NE(doc.RootElement(), nullptr);
}

TEST(XMLDocumentLoadFileTest_279, LoadFileEmptyContent_279) {
    const char* filename = "test_empty_279.xml";
    const char* content = "";
    TempXMLFile tempFile(filename, content);

    XMLDocument doc;
    XMLError err = doc.LoadFile(filename);
    EXPECT_NE(err, XML_SUCCESS);
    EXPECT_TRUE(doc.Error());
}

TEST(XMLDocumentLoadFileTest_279, LoadFileFP_279) {
    const char* filename = "test_fp_279.xml";
    const char* content = "<root>hello</root>";
    TempXMLFile tempFile(filename, content);

    FILE* fp = fopen(filename, "rb");
    ASSERT_NE(fp, nullptr);

    XMLDocument doc;
    XMLError err = doc.LoadFile(fp);
    fclose(fp);

    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_FALSE(doc.Error());
    EXPECT_NE(doc.RootElement(), nullptr);
}

// ==================== Parse Tests ====================

TEST(XMLDocumentParseTest_279, ParseValidXML_279) {
    XMLDocument doc;
    XMLError err = doc.Parse("<root><child attr=\"value\">text</child></root>");
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_FALSE(doc.Error());
    EXPECT_NE(doc.RootElement(), nullptr);
}

TEST(XMLDocumentParseTest_279, ParseNullString_279) {
    XMLDocument doc;
    XMLError err = doc.Parse(nullptr);
    EXPECT_NE(err, XML_SUCCESS);
    EXPECT_TRUE(doc.Error());
}

TEST(XMLDocumentParseTest_279, ParseEmptyString_279) {
    XMLDocument doc;
    XMLError err = doc.Parse("");
    EXPECT_NE(err, XML_SUCCESS);
    EXPECT_TRUE(doc.Error());
}

TEST(XMLDocumentParseTest_279, ParseMismatchedTags_279) {
    XMLDocument doc;
    XMLError err = doc.Parse("<root><child></root>");
    EXPECT_NE(err, XML_SUCCESS);
    EXPECT_TRUE(doc.Error());
}

TEST(XMLDocumentParseTest_279, ParseWithSize_279) {
    XMLDocument doc;
    const char* xml = "<root>text</root>EXTRA_GARBAGE";
    XMLError err = doc.Parse(xml, 17); // length of "<root>text</root>"
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_FALSE(doc.Error());
}

TEST(XMLDocumentParseTest_279, ParseWithBOM_279) {
    XMLDocument doc;
    const char bom[] = "\xef\xbb\xbf<root/>";
    XMLError err = doc.Parse(bom);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_TRUE(doc.HasBOM());
}

// ==================== SaveFile Tests ====================

TEST(XMLDocumentSaveFileTest_279, SaveFileToPath_279) {
    XMLDocument doc;
    doc.Parse("<root><child>text</child></root>");
    ASSERT_FALSE(doc.Error());

    const char* filename = "test_save_279.xml";
    XMLError err = doc.SaveFile(filename, false);
    EXPECT_EQ(err, XML_SUCCESS);

    // Verify by loading it back
    XMLDocument doc2;
    XMLError err2 = doc2.LoadFile(filename);
    EXPECT_EQ(err2, XML_SUCCESS);
    EXPECT_NE(doc2.RootElement(), nullptr);

    remove(filename);
}

TEST(XMLDocumentSaveFileTest_279, SaveFileCompact_279) {
    XMLDocument doc;
    doc.Parse("<root> <child> text </child> </root>");

    const char* filename = "test_save_compact_279.xml";
    XMLError err = doc.SaveFile(filename, true);
    EXPECT_EQ(err, XML_SUCCESS);

    remove(filename);
}

TEST(XMLDocumentSaveFileTest_279, SaveFileToFP_279) {
    XMLDocument doc;
    doc.Parse("<root>hello</root>");

    const char* filename = "test_save_fp_279.xml";
    FILE* fp = fopen(filename, "w");
    ASSERT_NE(fp, nullptr);

    XMLError err = doc.SaveFile(fp, false);
    fclose(fp);
    EXPECT_EQ(err, XML_SUCCESS);

    remove(filename);
}

// ==================== Error Handling Tests ====================

TEST(XMLDocumentErrorTest_279, ClearError_279) {
    XMLDocument doc;
    doc.Parse("");
    EXPECT_TRUE(doc.Error());

    doc.ClearError();
    EXPECT_FALSE(doc.Error());
    EXPECT_EQ(doc.ErrorID(), XML_SUCCESS);
}

TEST(XMLDocumentErrorTest_279, ErrorName_279) {
    XMLDocument doc;
    doc.Parse("<root>");
    EXPECT_TRUE(doc.Error());
    const char* name = doc.ErrorName();
    EXPECT_NE(name, nullptr);
    EXPECT_GT(strlen(name), 0u);
}

TEST(XMLDocumentErrorTest_279, ErrorStr_279) {
    XMLDocument doc;
    doc.LoadFile("does_not_exist_279.xml");
    const char* errStr = doc.ErrorStr();
    EXPECT_NE(errStr, nullptr);
    EXPECT_GT(strlen(errStr), 0u);
}

TEST(XMLDocumentErrorTest_279, ErrorIDToName_279) {
    const char* name = XMLDocument::ErrorIDToName(XML_SUCCESS);
    EXPECT_NE(name, nullptr);

    const char* name2 = XMLDocument::ErrorIDToName(XML_ERROR_FILE_NOT_FOUND);
    EXPECT_NE(name2, nullptr);
    EXPECT_STRNE(name, name2);
}

TEST(XMLDocumentErrorTest_279, ErrorLineNum_279) {
    XMLDocument doc;
    doc.Parse("<root>\n<child>\n</root>");
    EXPECT_TRUE(doc.Error());
    EXPECT_GT(doc.ErrorLineNum(), 0);
}

// ==================== New Node Creation Tests ====================

TEST(XMLDocumentNodeCreationTest_279, NewElement_279) {
    XMLDocument doc;
    XMLElement* elem = doc.NewElement("test");
    EXPECT_NE(elem, nullptr);
    EXPECT_STREQ(elem->Name(), "test");
    doc.DeleteNode(elem);
}

TEST(XMLDocumentNodeCreationTest_279, NewComment_279) {
    XMLDocument doc;
    XMLComment* comment = doc.NewComment("this is a comment");
    EXPECT_NE(comment, nullptr);
    doc.DeleteNode(comment);
}

TEST(XMLDocumentNodeCreationTest_279, NewText_279) {
    XMLDocument doc;
    XMLText* text = doc.NewText("hello world");
    EXPECT_NE(text, nullptr);
    doc.DeleteNode(text);
}

TEST(XMLDocumentNodeCreationTest_279, NewDeclaration_279) {
    XMLDocument doc;
    XMLDeclaration* decl = doc.NewDeclaration();
    EXPECT_NE(decl, nullptr);
    doc.DeleteNode(decl);
}

TEST(XMLDocumentNodeCreationTest_279, NewUnknown_279) {
    XMLDocument doc;
    XMLUnknown* unknown = doc.NewUnknown("unknown stuff");
    EXPECT_NE(unknown, nullptr);
    doc.DeleteNode(unknown);
}

// ==================== Clear Tests ====================

TEST(XMLDocumentClearTest_279, ClearResetsDocument_279) {
    XMLDocument doc;
    doc.Parse("<root><child/></root>");
    EXPECT_FALSE(doc.Error());
    EXPECT_NE(doc.RootElement(), nullptr);

    doc.Clear();
    EXPECT_EQ(doc.RootElement(), nullptr);
    EXPECT_FALSE(doc.Error());
}

// ==================== DeepCopy Tests ====================

TEST(XMLDocumentDeepCopyTest_279, DeepCopyValidDocument_279) {
    XMLDocument src;
    src.Parse("<root><child attr=\"val\">text</child></root>");
    ASSERT_FALSE(src.Error());

    XMLDocument dest;
    src.DeepCopy(&dest);
    EXPECT_FALSE(dest.Error());
    EXPECT_NE(dest.RootElement(), nullptr);
    EXPECT_STREQ(dest.RootElement()->Name(), "root");
}

TEST(XMLDocumentDeepCopyTest_279, DeepCopyEmptyDocument_279) {
    XMLDocument src;
    XMLDocument dest;
    dest.Parse("<root/>");

    src.DeepCopy(&dest);
    EXPECT_EQ(dest.RootElement(), nullptr);
}

// ==================== BOM Tests ====================

TEST(XMLDocumentBOMTest_279, SetBOM_279) {
    XMLDocument doc;
    EXPECT_FALSE(doc.HasBOM());
    doc.SetBOM(true);
    EXPECT_TRUE(doc.HasBOM());
    doc.SetBOM(false);
    EXPECT_FALSE(doc.HasBOM());
}

// ==================== RootElement Tests ====================

TEST(XMLDocumentRootElementTest_279, RootElementAfterParse_279) {
    XMLDocument doc;
    doc.Parse("<myroot/>");
    ASSERT_NE(doc.RootElement(), nullptr);
    EXPECT_STREQ(doc.RootElement()->Name(), "myroot");
}

TEST(XMLDocumentRootElementTest_279, RootElementEmpty_279) {
    XMLDocument doc;
    EXPECT_EQ(doc.RootElement(), nullptr);
}

// ==================== ToDocument Tests ====================

TEST(XMLDocumentToDocumentTest_279, ToDocumentReturnsSelf_279) {
    XMLDocument doc;
    XMLDocument* ptr = doc.ToDocument();
    EXPECT_EQ(ptr, &doc);
}

// ==================== ShallowClone / ShallowEqual Tests ====================

TEST(XMLDocumentShallowTest_279, ShallowCloneReturnsNull_279) {
    XMLDocument doc;
    XMLNode* clone = doc.ShallowClone(&doc);
    EXPECT_EQ(clone, nullptr);
}

TEST(XMLDocumentShallowTest_279, ShallowEqualReturnsFalse_279) {
    XMLDocument doc1;
    XMLDocument doc2;
    EXPECT_FALSE(doc1.ShallowEqual(&doc2));
}

// ==================== Accept Tests ====================

TEST(XMLDocumentAcceptTest_279, AcceptWithPrinter_279) {
    XMLDocument doc;
    doc.Parse("<root><child/></root>");
    ASSERT_FALSE(doc.Error());

    XMLPrinter printer;
    bool result = doc.Accept(&printer);
    EXPECT_TRUE(result);
    const char* output = printer.CStr();
    EXPECT_NE(output, nullptr);
    EXPECT_NE(strstr(output, "root"), nullptr);
}

// ==================== Print Tests ====================

TEST(XMLDocumentPrintTest_279, PrintToStreamer_279) {
    XMLDocument doc;
    doc.Parse("<root>value</root>");
    ASSERT_FALSE(doc.Error());

    XMLPrinter printer;
    doc.Print(&printer);
    const char* output = printer.CStr();
    EXPECT_NE(output, nullptr);
    EXPECT_NE(strstr(output, "root"), nullptr);
    EXPECT_NE(strstr(output, "value"), nullptr);
}

TEST(XMLDocumentPrintTest_279, PrintNullStreamer_279) {
    // Print with null streamer should print to stdout (no crash expected)
    XMLDocument doc;
    doc.Parse("<root/>");
    ASSERT_FALSE(doc.Error());
    // This should not crash; it prints to stdout
    doc.Print(nullptr);
}

// ==================== Complex XML Tests ====================

TEST(XMLDocumentComplexTest_279, ParseMultipleElements_279) {
    XMLDocument doc;
    XMLError err = doc.Parse(
        "<root>"
        "  <a>1</a>"
        "  <b>2</b>"
        "  <c attr=\"3\"/>"
        "</root>");
    EXPECT_EQ(err, XML_SUCCESS);
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);
    EXPECT_NE(root->FirstChildElement("a"), nullptr);
    EXPECT_NE(root->FirstChildElement("b"), nullptr);
    EXPECT_NE(root->FirstChildElement("c"), nullptr);
}

TEST(XMLDocumentComplexTest_279, ParseDeclaration_279) {
    XMLDocument doc;
    XMLError err = doc.Parse("<?xml version=\"1.0\" encoding=\"UTF-8\"?><root/>");
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_NE(doc.RootElement(), nullptr);
}

TEST(XMLDocumentComplexTest_279, ParseComment_279) {
    XMLDocument doc;
    XMLError err = doc.Parse("<!-- comment --><root/>");
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_NE(doc.RootElement(), nullptr);
}

TEST(XMLDocumentComplexTest_279, ParseCDATA_279) {
    XMLDocument doc;
    XMLError err = doc.Parse("<root><![CDATA[some <data>]]></root>");
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_NE(doc.RootElement(), nullptr);
}

// ==================== DeleteNode Tests ====================

TEST(XMLDocumentDeleteNodeTest_279, DeleteRootElement_279) {
    XMLDocument doc;
    doc.Parse("<root><child/></root>");
    ASSERT_NE(doc.RootElement(), nullptr);

    doc.DeleteNode(doc.RootElement());
    EXPECT_EQ(doc.RootElement(), nullptr);
}

TEST(XMLDocumentDeleteNodeTest_279, DeleteChildElement_279) {
    XMLDocument doc;
    doc.Parse("<root><child/></root>");
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);
    XMLElement* child = root->FirstChildElement("child");
    ASSERT_NE(child, nullptr);

    doc.DeleteNode(child);
    EXPECT_EQ(root->FirstChildElement("child"), nullptr);
}

// ==================== Successive Parse/Load Tests ====================

TEST(XMLDocumentReparseTest_279, ParseTwice_279) {
    XMLDocument doc;
    XMLError err1 = doc.Parse("<root1/>");
    EXPECT_EQ(err1, XML_SUCCESS);
    EXPECT_STREQ(doc.RootElement()->Name(), "root1");

    XMLError err2 = doc.Parse("<root2/>");
    EXPECT_EQ(err2, XML_SUCCESS);
    EXPECT_STREQ(doc.RootElement()->Name(), "root2");
}

TEST(XMLDocumentReparseTest_279, LoadAfterError_279) {
    XMLDocument doc;
    doc.Parse("invalid xml <<<<");
    EXPECT_TRUE(doc.Error());

    // Parse valid XML after error
    XMLError err = doc.Parse("<root/>");
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_FALSE(doc.Error());
}

// ==================== Entity Processing Tests ====================

TEST(XMLDocumentEntityTest_279, ProcessEntitiesEnabled_279) {
    XMLDocument doc(true);
    doc.Parse("<root>&amp;</root>");
    EXPECT_FALSE(doc.Error());
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);
    EXPECT_STREQ(root->GetText(), "&");
}

TEST(XMLDocumentEntityTest_279, ProcessEntitiesDisabled_279) {
    XMLDocument doc(false);
    doc.Parse("<root>&amp;</root>");
    EXPECT_FALSE(doc.Error());
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);
    EXPECT_STREQ(root->GetText(), "&amp;");
}

// ==================== ErrorIDToName comprehensive test ====================

TEST(XMLDocumentErrorIDToNameTest_279, AllErrorCodes_279) {
    for (int i = 0; i < XML_ERROR_COUNT; ++i) {
        const char* name = XMLDocument::ErrorIDToName(static_cast<XMLError>(i));
        EXPECT_NE(name, nullptr);
        EXPECT_GT(strlen(name), 0u);
    }
}

// ==================== PrintError Tests ====================

TEST(XMLDocumentPrintErrorTest_279, PrintErrorAfterLoadFailure_279) {
    XMLDocument doc;
    doc.LoadFile("no_such_file_279.xml");
    EXPECT_TRUE(doc.Error());
    // PrintError should not crash
    doc.PrintError();
}

TEST(XMLDocumentPrintErrorTest_279, PrintErrorWhenNoError_279) {
    XMLDocument doc;
    // Should not crash even with no error
    doc.PrintError();
}
