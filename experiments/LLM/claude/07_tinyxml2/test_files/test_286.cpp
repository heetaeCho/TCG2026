#include <gtest/gtest.h>
#include "tinyxml2.h"

using namespace tinyxml2;

// Helper to get the XML error enum values
// XML_SUCCESS = 0, and errors go up to XML_ERROR_COUNT - 1

class XMLDocumentTest_286 : public ::testing::Test {
protected:
    XMLDocument doc;
};

// ==================== ErrorIDToName Tests ====================

TEST_F(XMLDocumentTest_286, ErrorIDToName_Success_286) {
    const char* name = XMLDocument::ErrorIDToName(XML_SUCCESS);
    ASSERT_NE(name, nullptr);
    EXPECT_STRNE(name, "");
    EXPECT_STREQ(name, "XML_SUCCESS");
}

TEST_F(XMLDocumentTest_286, ErrorIDToName_ErrorFileNotFound_286) {
    const char* name = XMLDocument::ErrorIDToName(XML_ERROR_FILE_NOT_FOUND);
    ASSERT_NE(name, nullptr);
    EXPECT_STRNE(name, "");
}

TEST_F(XMLDocumentTest_286, ErrorIDToName_ErrorFileCouldNotBeOpened_286) {
    const char* name = XMLDocument::ErrorIDToName(XML_ERROR_FILE_COULD_NOT_BE_OPENED);
    ASSERT_NE(name, nullptr);
    EXPECT_STRNE(name, "");
}

TEST_F(XMLDocumentTest_286, ErrorIDToName_ErrorFileReadError_286) {
    const char* name = XMLDocument::ErrorIDToName(XML_ERROR_FILE_READ_ERROR);
    ASSERT_NE(name, nullptr);
    EXPECT_STRNE(name, "");
}

TEST_F(XMLDocumentTest_286, ErrorIDToName_ErrorParsingEmpty_286) {
    const char* name = XMLDocument::ErrorIDToName(XML_ERROR_EMPTY_DOCUMENT);
    ASSERT_NE(name, nullptr);
    EXPECT_STRNE(name, "");
}

TEST_F(XMLDocumentTest_286, ErrorIDToName_ErrorMismatchedElement_286) {
    const char* name = XMLDocument::ErrorIDToName(XML_ERROR_MISMATCHED_ELEMENT);
    ASSERT_NE(name, nullptr);
    EXPECT_STRNE(name, "");
}

TEST_F(XMLDocumentTest_286, ErrorIDToName_ErrorParsing_286) {
    const char* name = XMLDocument::ErrorIDToName(XML_ERROR_PARSING);
    ASSERT_NE(name, nullptr);
    EXPECT_STRNE(name, "");
}

TEST_F(XMLDocumentTest_286, ErrorIDToName_AllValidErrorsReturnNonNull_286) {
    for (int i = 0; i < XML_ERROR_COUNT; ++i) {
        const char* name = XMLDocument::ErrorIDToName(static_cast<XMLError>(i));
        ASSERT_NE(name, nullptr) << "ErrorIDToName returned nullptr for error ID " << i;
        EXPECT_STRNE(name, "") << "ErrorIDToName returned empty string for error ID " << i;
    }
}

TEST_F(XMLDocumentTest_286, ErrorIDToName_UniqueNamesForDifferentErrors_286) {
    // At minimum, XML_SUCCESS should differ from some error
    const char* successName = XMLDocument::ErrorIDToName(XML_SUCCESS);
    if (XML_ERROR_COUNT > 1) {
        const char* errorName = XMLDocument::ErrorIDToName(static_cast<XMLError>(1));
        EXPECT_STRNE(successName, errorName);
    }
}

// ==================== Parse Tests ====================

TEST_F(XMLDocumentTest_286, ParseValidXML_286) {
    const char* xml = "<root><child/></root>";
    XMLError err = doc.Parse(xml);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_FALSE(doc.Error());
    EXPECT_EQ(doc.ErrorID(), XML_SUCCESS);
}

TEST_F(XMLDocumentTest_286, ParseEmptyString_286) {
    XMLError err = doc.Parse("");
    EXPECT_NE(err, XML_SUCCESS);
    EXPECT_TRUE(doc.Error());
}

TEST_F(XMLDocumentTest_286, ParseNullptr_286) {
    XMLError err = doc.Parse(nullptr);
    EXPECT_NE(err, XML_SUCCESS);
    EXPECT_TRUE(doc.Error());
}

TEST_F(XMLDocumentTest_286, ParseMalformedXML_286) {
    const char* xml = "<root><child></root>";
    XMLError err = doc.Parse(xml);
    EXPECT_NE(err, XML_SUCCESS);
    EXPECT_TRUE(doc.Error());
}

TEST_F(XMLDocumentTest_286, ParseWithSize_286) {
    const char* xml = "<root/>EXTRA_GARBAGE";
    XMLError err = doc.Parse(xml, 7); // Only "<root/>"
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_FALSE(doc.Error());
}

TEST_F(XMLDocumentTest_286, ParseValidXMLWithDeclaration_286) {
    const char* xml = "<?xml version=\"1.0\"?><root/>";
    XMLError err = doc.Parse(xml);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_FALSE(doc.Error());
}

TEST_F(XMLDocumentTest_286, ParseValidXMLWithAttributes_286) {
    const char* xml = "<root attr=\"value\"/>";
    XMLError err = doc.Parse(xml);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_FALSE(doc.Error());
}

TEST_F(XMLDocumentTest_286, ParseValidXMLWithText_286) {
    const char* xml = "<root>Hello World</root>";
    XMLError err = doc.Parse(xml);
    EXPECT_EQ(err, XML_SUCCESS);
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);
    EXPECT_STREQ(root->GetText(), "Hello World");
}

// ==================== Constructor / Initial State Tests ====================

TEST_F(XMLDocumentTest_286, DefaultConstructedDocHasNoError_286) {
    EXPECT_FALSE(doc.Error());
    EXPECT_EQ(doc.ErrorID(), XML_SUCCESS);
}

TEST_F(XMLDocumentTest_286, DefaultConstructedDocHasNoBOM_286) {
    EXPECT_FALSE(doc.HasBOM());
}

TEST_F(XMLDocumentTest_286, DefaultConstructedDocRootElementIsNull_286) {
    EXPECT_EQ(doc.RootElement(), nullptr);
}

TEST_F(XMLDocumentTest_286, DefaultConstructedDocErrorLineNumIsZero_286) {
    EXPECT_EQ(doc.ErrorLineNum(), 0);
}

// ==================== ClearError Tests ====================

TEST_F(XMLDocumentTest_286, ClearErrorAfterParseFailure_286) {
    doc.Parse("");
    EXPECT_TRUE(doc.Error());
    doc.ClearError();
    EXPECT_FALSE(doc.Error());
    EXPECT_EQ(doc.ErrorID(), XML_SUCCESS);
}

// ==================== Clear Tests ====================

TEST_F(XMLDocumentTest_286, ClearResetsDocument_286) {
    doc.Parse("<root/>");
    EXPECT_NE(doc.RootElement(), nullptr);
    doc.Clear();
    EXPECT_EQ(doc.RootElement(), nullptr);
    EXPECT_FALSE(doc.Error());
}

// ==================== NewElement Tests ====================

TEST_F(XMLDocumentTest_286, NewElementCreatesElement_286) {
    XMLElement* elem = doc.NewElement("test");
    ASSERT_NE(elem, nullptr);
    EXPECT_STREQ(elem->Name(), "test");
}

// ==================== NewComment Tests ====================

TEST_F(XMLDocumentTest_286, NewCommentCreatesComment_286) {
    XMLComment* comment = doc.NewComment("this is a comment");
    ASSERT_NE(comment, nullptr);
    EXPECT_STREQ(comment->Value(), "this is a comment");
}

// ==================== NewText Tests ====================

TEST_F(XMLDocumentTest_286, NewTextCreatesText_286) {
    XMLText* text = doc.NewText("hello");
    ASSERT_NE(text, nullptr);
    EXPECT_STREQ(text->Value(), "hello");
}

// ==================== NewDeclaration Tests ====================

TEST_F(XMLDocumentTest_286, NewDeclarationCreatesDeclaration_286) {
    XMLDeclaration* decl = doc.NewDeclaration();
    ASSERT_NE(decl, nullptr);
}

TEST_F(XMLDocumentTest_286, NewDeclarationWithCustomString_286) {
    XMLDeclaration* decl = doc.NewDeclaration("xml version=\"1.0\"");
    ASSERT_NE(decl, nullptr);
}

// ==================== NewUnknown Tests ====================

TEST_F(XMLDocumentTest_286, NewUnknownCreatesUnknown_286) {
    XMLUnknown* unknown = doc.NewUnknown("something");
    ASSERT_NE(unknown, nullptr);
    EXPECT_STREQ(unknown->Value(), "something");
}

// ==================== DeleteNode Tests ====================

TEST_F(XMLDocumentTest_286, DeleteNodeRemovesNode_286) {
    doc.Parse("<root><child/></root>");
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);
    XMLElement* child = root->FirstChildElement("child");
    ASSERT_NE(child, nullptr);
    doc.DeleteNode(child);
    EXPECT_EQ(root->FirstChildElement("child"), nullptr);
}

// ==================== SetBOM / HasBOM Tests ====================

TEST_F(XMLDocumentTest_286, SetBOMAndHasBOM_286) {
    EXPECT_FALSE(doc.HasBOM());
    doc.SetBOM(true);
    EXPECT_TRUE(doc.HasBOM());
    doc.SetBOM(false);
    EXPECT_FALSE(doc.HasBOM());
}

// ==================== ProcessEntities Tests ====================

TEST_F(XMLDocumentTest_286, ProcessEntitiesDefault_286) {
    EXPECT_TRUE(doc.ProcessEntities());
}

TEST_F(XMLDocumentTest_286, ProcessEntitiesFalse_286) {
    XMLDocument doc2(false);
    EXPECT_FALSE(doc2.ProcessEntities());
}

// ==================== WhitespaceMode Tests ====================

TEST_F(XMLDocumentTest_286, WhitespaceModeDefault_286) {
    EXPECT_EQ(doc.WhitespaceMode(), PRESERVE_WHITESPACE);
}

// ==================== ErrorName and ErrorStr Tests ====================

TEST_F(XMLDocumentTest_286, ErrorNameAfterSuccess_286) {
    doc.Parse("<root/>");
    const char* name = doc.ErrorName();
    ASSERT_NE(name, nullptr);
    EXPECT_STREQ(name, "XML_SUCCESS");
}

TEST_F(XMLDocumentTest_286, ErrorNameAfterFailure_286) {
    doc.Parse("");
    const char* name = doc.ErrorName();
    ASSERT_NE(name, nullptr);
    EXPECT_STRNE(name, "XML_SUCCESS");
}

TEST_F(XMLDocumentTest_286, ErrorStrAfterSuccess_286) {
    doc.Parse("<root/>");
    const char* errStr = doc.ErrorStr();
    ASSERT_NE(errStr, nullptr);
}

TEST_F(XMLDocumentTest_286, ErrorStrAfterFailure_286) {
    doc.Parse("<root><child></root>");
    const char* errStr = doc.ErrorStr();
    ASSERT_NE(errStr, nullptr);
    EXPECT_STRNE(errStr, "");
}

// ==================== LoadFile Tests ====================

TEST_F(XMLDocumentTest_286, LoadFileNonexistent_286) {
    XMLError err = doc.LoadFile("nonexistent_file_that_does_not_exist.xml");
    EXPECT_NE(err, XML_SUCCESS);
    EXPECT_TRUE(doc.Error());
}

TEST_F(XMLDocumentTest_286, LoadFileNullFilename_286) {
    XMLError err = doc.LoadFile((const char*)nullptr);
    EXPECT_NE(err, XML_SUCCESS);
    EXPECT_TRUE(doc.Error());
}

// ==================== SaveFile Tests ====================

TEST_F(XMLDocumentTest_286, SaveFileToNullFilename_286) {
    doc.Parse("<root/>");
    XMLError err = doc.SaveFile((const char*)nullptr, false);
    EXPECT_NE(err, XML_SUCCESS);
}

// ==================== DeepCopy Tests ====================

TEST_F(XMLDocumentTest_286, DeepCopyCreatesIndependentCopy_286) {
    doc.Parse("<root><child attr=\"val\">text</child></root>");
    ASSERT_FALSE(doc.Error());

    XMLDocument target;
    doc.DeepCopy(&target);
    ASSERT_FALSE(target.Error());

    XMLElement* targetRoot = target.RootElement();
    ASSERT_NE(targetRoot, nullptr);
    EXPECT_STREQ(targetRoot->Name(), "root");

    XMLElement* targetChild = targetRoot->FirstChildElement("child");
    ASSERT_NE(targetChild, nullptr);
    EXPECT_STREQ(targetChild->Attribute("attr"), "val");
    EXPECT_STREQ(targetChild->GetText(), "text");
}

// ==================== ToDocument Tests ====================

TEST_F(XMLDocumentTest_286, ToDocumentReturnsThis_286) {
    XMLDocument* result = doc.ToDocument();
    EXPECT_EQ(result, &doc);
}

// ==================== ShallowClone Tests ====================

TEST_F(XMLDocumentTest_286, ShallowCloneReturnsNull_286) {
    XMLNode* clone = doc.ShallowClone(&doc);
    EXPECT_EQ(clone, nullptr);
}

// ==================== ShallowEqual Tests ====================

TEST_F(XMLDocumentTest_286, ShallowEqualReturnsFalse_286) {
    XMLDocument doc2;
    EXPECT_FALSE(doc.ShallowEqual(&doc2));
}

// ==================== RootElement Tests ====================

TEST_F(XMLDocumentTest_286, RootElementAfterParse_286) {
    doc.Parse("<myroot/>");
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);
    EXPECT_STREQ(root->Name(), "myroot");
}

// ==================== ErrorLineNum Tests ====================

TEST_F(XMLDocumentTest_286, ErrorLineNumOnMismatch_286) {
    const char* xml = "<root>\n<child>\n</root>";
    doc.Parse(xml);
    EXPECT_TRUE(doc.Error());
    EXPECT_GT(doc.ErrorLineNum(), 0);
}

// ==================== Print Tests ====================

TEST_F(XMLDocumentTest_286, PrintToDefaultPrinter_286) {
    doc.Parse("<root><child/></root>");
    ASSERT_FALSE(doc.Error());
    
    XMLPrinter printer;
    doc.Print(&printer);
    const char* result = printer.CStr();
    ASSERT_NE(result, nullptr);
    EXPECT_NE(std::string(result).find("root"), std::string::npos);
    EXPECT_NE(std::string(result).find("child"), std::string::npos);
}

TEST_F(XMLDocumentTest_286, PrintWithNullPrinter_286) {
    doc.Parse("<root/>");
    // Passing nullptr should use stdout - just verify it doesn't crash
    doc.Print(nullptr);
}

// ==================== Accept Tests ====================

TEST_F(XMLDocumentTest_286, AcceptWithPrinter_286) {
    doc.Parse("<root>text</root>");
    ASSERT_FALSE(doc.Error());

    XMLPrinter printer;
    bool result = doc.Accept(&printer);
    EXPECT_TRUE(result);
    const char* output = printer.CStr();
    ASSERT_NE(output, nullptr);
    EXPECT_NE(std::string(output).find("root"), std::string::npos);
}

// ==================== Complex XML Parse Tests ====================

TEST_F(XMLDocumentTest_286, ParseNestedElements_286) {
    const char* xml = "<a><b><c><d/></c></b></a>";
    EXPECT_EQ(doc.Parse(xml), XML_SUCCESS);
    EXPECT_FALSE(doc.Error());
    
    XMLElement* a = doc.RootElement();
    ASSERT_NE(a, nullptr);
    EXPECT_STREQ(a->Name(), "a");
    
    XMLElement* b = a->FirstChildElement("b");
    ASSERT_NE(b, nullptr);
    
    XMLElement* c = b->FirstChildElement("c");
    ASSERT_NE(c, nullptr);
    
    XMLElement* d = c->FirstChildElement("d");
    ASSERT_NE(d, nullptr);
}

TEST_F(XMLDocumentTest_286, ParseXMLWithEntities_286) {
    const char* xml = "<root>&lt;&gt;&amp;</root>";
    EXPECT_EQ(doc.Parse(xml), XML_SUCCESS);
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);
    EXPECT_STREQ(root->GetText(), "<>&");
}

TEST_F(XMLDocumentTest_286, ParseMultipleTimesResets_286) {
    doc.Parse("<first/>");
    ASSERT_FALSE(doc.Error());
    EXPECT_STREQ(doc.RootElement()->Name(), "first");

    doc.Parse("<second/>");
    ASSERT_FALSE(doc.Error());
    EXPECT_STREQ(doc.RootElement()->Name(), "second");
}

// ==================== SaveFile/LoadFile roundtrip via FILE* ====================

TEST_F(XMLDocumentTest_286, SaveAndLoadFileViaFILE_286) {
    doc.Parse("<root><item>value</item></root>");
    ASSERT_FALSE(doc.Error());

    const char* tmpFilename = "test_roundtrip_286.xml";
    FILE* fp = fopen(tmpFilename, "w");
    if (fp) {
        XMLError err = doc.SaveFile(fp, false);
        fclose(fp);
        EXPECT_EQ(err, XML_SUCCESS);

        XMLDocument doc2;
        FILE* fp2 = fopen(tmpFilename, "r");
        if (fp2) {
            XMLError err2 = doc2.LoadFile(fp2);
            fclose(fp2);
            EXPECT_EQ(err2, XML_SUCCESS);
            ASSERT_NE(doc2.RootElement(), nullptr);
            EXPECT_STREQ(doc2.RootElement()->Name(), "root");
        }
        remove(tmpFilename);
    }
}
