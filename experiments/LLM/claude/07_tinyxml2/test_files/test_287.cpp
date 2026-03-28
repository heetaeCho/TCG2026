#include <gtest/gtest.h>
#include "tinyxml2.h"

using namespace tinyxml2;

// Test fixture for XMLDocument tests
class XMLDocumentTest_287 : public ::testing::Test {
protected:
    XMLDocument doc;
};

// ==================== ErrorStr Tests ====================

TEST_F(XMLDocumentTest_287, ErrorStr_ReturnsEmptyStringOnNewDocument_287) {
    // A freshly constructed document should have no error
    const char* errStr = doc.ErrorStr();
    ASSERT_NE(errStr, nullptr);
    EXPECT_STREQ(errStr, "");
}

TEST_F(XMLDocumentTest_287, ErrorStr_ReturnsEmptyStringAfterSuccessfulParse_287) {
    XMLError err = doc.Parse("<root><child/></root>");
    EXPECT_EQ(err, XML_SUCCESS);
    const char* errStr = doc.ErrorStr();
    ASSERT_NE(errStr, nullptr);
    EXPECT_STREQ(errStr, "");
}

TEST_F(XMLDocumentTest_287, ErrorStr_ReturnsNonEmptyStringAfterParseError_287) {
    XMLError err = doc.Parse("<root><child></root>");
    EXPECT_NE(err, XML_SUCCESS);
    const char* errStr = doc.ErrorStr();
    ASSERT_NE(errStr, nullptr);
    EXPECT_STRNE(errStr, "");
}

TEST_F(XMLDocumentTest_287, ErrorStr_ReturnsEmptyAfterClearError_287) {
    // First cause an error
    doc.Parse("<root><child></root>");
    EXPECT_TRUE(doc.Error());
    
    // Clear the error
    doc.ClearError();
    
    const char* errStr = doc.ErrorStr();
    ASSERT_NE(errStr, nullptr);
    EXPECT_STREQ(errStr, "");
}

// ==================== Parse Tests ====================

TEST_F(XMLDocumentTest_287, Parse_ValidXML_ReturnsSuccess_287) {
    XMLError err = doc.Parse("<root/>");
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_FALSE(doc.Error());
}

TEST_F(XMLDocumentTest_287, Parse_ValidXMLWithContent_ReturnsSuccess_287) {
    XMLError err = doc.Parse("<root><child attr=\"value\">text</child></root>");
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_FALSE(doc.Error());
}

TEST_F(XMLDocumentTest_287, Parse_EmptyString_ReturnsError_287) {
    XMLError err = doc.Parse("");
    EXPECT_NE(err, XML_SUCCESS);
    EXPECT_TRUE(doc.Error());
}

TEST_F(XMLDocumentTest_287, Parse_NullPtr_ReturnsError_287) {
    XMLError err = doc.Parse(nullptr, 0);
    EXPECT_NE(err, XML_SUCCESS);
    EXPECT_TRUE(doc.Error());
}

TEST_F(XMLDocumentTest_287, Parse_MalformedXML_ReturnsError_287) {
    XMLError err = doc.Parse("<root><unclosed>");
    EXPECT_NE(err, XML_SUCCESS);
    EXPECT_TRUE(doc.Error());
}

TEST_F(XMLDocumentTest_287, Parse_MismatchedTags_ReturnsError_287) {
    XMLError err = doc.Parse("<root></other>");
    EXPECT_NE(err, XML_SUCCESS);
    EXPECT_TRUE(doc.Error());
}

TEST_F(XMLDocumentTest_287, Parse_WithNBytes_287) {
    const char* xml = "<root/>EXTRA_GARBAGE";
    XMLError err = doc.Parse(xml, 7); // Only parse "<root/>"
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_FALSE(doc.Error());
}

// ==================== Error / ErrorID / ErrorLineNum Tests ====================

TEST_F(XMLDocumentTest_287, Error_ReturnsFalseOnNewDocument_287) {
    EXPECT_FALSE(doc.Error());
}

TEST_F(XMLDocumentTest_287, ErrorID_ReturnsSuccessOnNewDocument_287) {
    EXPECT_EQ(doc.ErrorID(), XML_SUCCESS);
}

TEST_F(XMLDocumentTest_287, ErrorLineNum_ReturnsZeroOnNewDocument_287) {
    EXPECT_EQ(doc.ErrorLineNum(), 0);
}

TEST_F(XMLDocumentTest_287, ErrorID_ReturnsNonSuccessOnParseError_287) {
    doc.Parse("<root><child></root>");
    EXPECT_NE(doc.ErrorID(), XML_SUCCESS);
}

TEST_F(XMLDocumentTest_287, ErrorLineNum_ReturnsNonZeroOnMultilineError_287) {
    doc.Parse("<root>\n<child>\n</root>");
    // If there's an error, line number should be > 0
    if (doc.Error()) {
        EXPECT_GT(doc.ErrorLineNum(), 0);
    }
}

// ==================== ClearError Tests ====================

TEST_F(XMLDocumentTest_287, ClearError_ResetsErrorState_287) {
    doc.Parse("<root><child></root>");
    EXPECT_TRUE(doc.Error());
    
    doc.ClearError();
    
    EXPECT_FALSE(doc.Error());
    EXPECT_EQ(doc.ErrorID(), XML_SUCCESS);
}

// ==================== ErrorName Tests ====================

TEST_F(XMLDocumentTest_287, ErrorName_ReturnsNonNullOnNewDocument_287) {
    const char* name = doc.ErrorName();
    ASSERT_NE(name, nullptr);
    EXPECT_STRNE(name, "");
}

TEST_F(XMLDocumentTest_287, ErrorName_ReturnsNonNullOnError_287) {
    doc.Parse("");
    const char* name = doc.ErrorName();
    ASSERT_NE(name, nullptr);
}

// ==================== ErrorIDToName Tests ====================

TEST_F(XMLDocumentTest_287, ErrorIDToName_ReturnsNonNullForSuccess_287) {
    const char* name = XMLDocument::ErrorIDToName(XML_SUCCESS);
    ASSERT_NE(name, nullptr);
}

TEST_F(XMLDocumentTest_287, ErrorIDToName_ReturnsNonNullForKnownErrors_287) {
    const char* name = XMLDocument::ErrorIDToName(XML_ERROR_PARSING);
    ASSERT_NE(name, nullptr);
    EXPECT_STRNE(name, "");
}

// ==================== NewElement / NewComment / NewText / NewDeclaration / NewUnknown ====================

TEST_F(XMLDocumentTest_287, NewElement_ReturnsNonNull_287) {
    XMLElement* elem = doc.NewElement("test");
    ASSERT_NE(elem, nullptr);
}

TEST_F(XMLDocumentTest_287, NewComment_ReturnsNonNull_287) {
    XMLComment* comment = doc.NewComment("test comment");
    ASSERT_NE(comment, nullptr);
}

TEST_F(XMLDocumentTest_287, NewText_ReturnsNonNull_287) {
    XMLText* text = doc.NewText("hello");
    ASSERT_NE(text, nullptr);
}

TEST_F(XMLDocumentTest_287, NewDeclaration_ReturnsNonNull_287) {
    XMLDeclaration* decl = doc.NewDeclaration();
    ASSERT_NE(decl, nullptr);
}

TEST_F(XMLDocumentTest_287, NewUnknown_ReturnsNonNull_287) {
    XMLUnknown* unknown = doc.NewUnknown("unknown stuff");
    ASSERT_NE(unknown, nullptr);
}

// ==================== RootElement Tests ====================

TEST_F(XMLDocumentTest_287, RootElement_ReturnsNullOnEmptyDocument_287) {
    EXPECT_EQ(doc.RootElement(), nullptr);
}

TEST_F(XMLDocumentTest_287, RootElement_ReturnsNonNullAfterParse_287) {
    doc.Parse("<root/>");
    EXPECT_NE(doc.RootElement(), nullptr);
}

TEST_F(XMLDocumentTest_287, RootElement_NameMatches_287) {
    doc.Parse("<myroot/>");
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);
    EXPECT_STREQ(root->Name(), "myroot");
}

// ==================== Clear Tests ====================

TEST_F(XMLDocumentTest_287, Clear_RemovesAllNodes_287) {
    doc.Parse("<root><child/></root>");
    ASSERT_NE(doc.RootElement(), nullptr);
    
    doc.Clear();
    
    EXPECT_EQ(doc.RootElement(), nullptr);
    EXPECT_FALSE(doc.Error());
}

// ==================== DeepCopy Tests ====================

TEST_F(XMLDocumentTest_287, DeepCopy_CopiesDocument_287) {
    doc.Parse("<root><child attr=\"val\">text</child></root>");
    ASSERT_FALSE(doc.Error());
    
    XMLDocument target;
    doc.DeepCopy(&target);
    
    ASSERT_NE(target.RootElement(), nullptr);
    EXPECT_STREQ(target.RootElement()->Name(), "root");
}

TEST_F(XMLDocumentTest_287, DeepCopy_TargetIsIndependent_287) {
    doc.Parse("<root/>");
    XMLDocument target;
    doc.DeepCopy(&target);
    
    doc.Clear();
    EXPECT_EQ(doc.RootElement(), nullptr);
    EXPECT_NE(target.RootElement(), nullptr);
}

// ==================== BOM Tests ====================

TEST_F(XMLDocumentTest_287, HasBOM_DefaultFalse_287) {
    EXPECT_FALSE(doc.HasBOM());
}

TEST_F(XMLDocumentTest_287, SetBOM_True_287) {
    doc.SetBOM(true);
    EXPECT_TRUE(doc.HasBOM());
}

TEST_F(XMLDocumentTest_287, SetBOM_False_287) {
    doc.SetBOM(true);
    doc.SetBOM(false);
    EXPECT_FALSE(doc.HasBOM());
}

// ==================== ProcessEntities / WhitespaceMode Tests ====================

TEST_F(XMLDocumentTest_287, ProcessEntities_DefaultTrue_287) {
    EXPECT_TRUE(doc.ProcessEntities());
}

TEST_F(XMLDocumentTest_287, ProcessEntities_FalseWhenConstructedWithFalse_287) {
    XMLDocument doc2(false);
    EXPECT_FALSE(doc2.ProcessEntities());
}

TEST_F(XMLDocumentTest_287, WhitespaceMode_DefaultPreserve_287) {
    // Default whitespace mode
    Whitespace mode = doc.WhitespaceMode();
    EXPECT_EQ(mode, PRESERVE_WHITESPACE);
}

TEST_F(XMLDocumentTest_287, WhitespaceMode_CollapseWhenSpecified_287) {
    XMLDocument doc2(true, COLLAPSE_WHITESPACE);
    EXPECT_EQ(doc2.WhitespaceMode(), COLLAPSE_WHITESPACE);
}

// ==================== ToDocument Tests ====================

TEST_F(XMLDocumentTest_287, ToDocument_ReturnsSelf_287) {
    XMLDocument* result = doc.ToDocument();
    EXPECT_EQ(result, &doc);
}

// ==================== ShallowClone / ShallowEqual Tests ====================

TEST_F(XMLDocumentTest_287, ShallowClone_ReturnsNull_287) {
    XMLNode* clone = doc.ShallowClone(&doc);
    EXPECT_EQ(clone, nullptr);
}

TEST_F(XMLDocumentTest_287, ShallowEqual_ReturnsFalse_287) {
    XMLDocument other;
    EXPECT_FALSE(doc.ShallowEqual(&other));
}

// ==================== DeleteNode Tests ====================

TEST_F(XMLDocumentTest_287, DeleteNode_RemovesElement_287) {
    doc.Parse("<root><child/></root>");
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);
    
    XMLElement* child = root->FirstChildElement("child");
    ASSERT_NE(child, nullptr);
    
    doc.DeleteNode(child);
    
    EXPECT_EQ(root->FirstChildElement("child"), nullptr);
}

// ==================== LoadFile / SaveFile Tests ====================

TEST_F(XMLDocumentTest_287, LoadFile_NonExistentFile_ReturnsError_287) {
    XMLError err = doc.LoadFile("nonexistent_file_that_does_not_exist_287.xml");
    EXPECT_NE(err, XML_SUCCESS);
    EXPECT_TRUE(doc.Error());
}

TEST_F(XMLDocumentTest_287, LoadFile_NullFILE_ReturnsError_287) {
    XMLError err = doc.LoadFile(static_cast<FILE*>(nullptr));
    EXPECT_NE(err, XML_SUCCESS);
    EXPECT_TRUE(doc.Error());
}

TEST_F(XMLDocumentTest_287, SaveFile_NullFILE_ReturnsError_287) {
    doc.Parse("<root/>");
    XMLError err = doc.SaveFile(static_cast<FILE*>(nullptr), false);
    EXPECT_NE(err, XML_SUCCESS);
}

// ==================== Print Tests ====================

TEST_F(XMLDocumentTest_287, Print_NullPrinter_DoesNotCrash_287) {
    doc.Parse("<root/>");
    // Passing nullptr to streamer should use stdout (default behavior)
    // This should not crash
    // Note: we don't capture stdout, just verify no crash
    doc.Print(nullptr);
}

// ==================== Accept Tests ====================

TEST_F(XMLDocumentTest_287, Accept_WithNullVisitor_287) {
    doc.Parse("<root/>");
    // Passing null visitor - behavior depends on implementation
    // Just checking it doesn't crash or returns false
    bool result = doc.Accept(nullptr);
    // The result is implementation-defined, just ensure no crash
    (void)result;
}

// ==================== Complex Parse Scenarios ====================

TEST_F(XMLDocumentTest_287, Parse_XMLDeclaration_287) {
    XMLError err = doc.Parse("<?xml version=\"1.0\" encoding=\"UTF-8\"?><root/>");
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_NE(doc.RootElement(), nullptr);
}

TEST_F(XMLDocumentTest_287, Parse_WithComments_287) {
    XMLError err = doc.Parse("<!-- comment --><root/>");
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_NE(doc.RootElement(), nullptr);
}

TEST_F(XMLDocumentTest_287, Parse_NestedElements_287) {
    XMLError err = doc.Parse("<a><b><c><d/></c></b></a>");
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_NE(doc.RootElement(), nullptr);
    EXPECT_STREQ(doc.RootElement()->Name(), "a");
}

TEST_F(XMLDocumentTest_287, Parse_WithAttributes_287) {
    XMLError err = doc.Parse("<root a=\"1\" b=\"2\" c=\"3\"/>");
    EXPECT_EQ(err, XML_SUCCESS);
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);
    EXPECT_STREQ(root->Attribute("a"), "1");
    EXPECT_STREQ(root->Attribute("b"), "2");
    EXPECT_STREQ(root->Attribute("c"), "3");
}

TEST_F(XMLDocumentTest_287, Parse_WithEntities_287) {
    XMLError err = doc.Parse("<root>&lt;&gt;&amp;</root>");
    EXPECT_EQ(err, XML_SUCCESS);
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);
    EXPECT_STREQ(root->GetText(), "<>&");
}

TEST_F(XMLDocumentTest_287, Parse_RepeatedParseClearsOld_287) {
    doc.Parse("<first/>");
    ASSERT_NE(doc.RootElement(), nullptr);
    EXPECT_STREQ(doc.RootElement()->Name(), "first");
    
    doc.Parse("<second/>");
    ASSERT_NE(doc.RootElement(), nullptr);
    EXPECT_STREQ(doc.RootElement()->Name(), "second");
}

// ==================== SaveFile and LoadFile round-trip ====================

TEST_F(XMLDocumentTest_287, SaveAndLoadFile_RoundTrip_287) {
    const char* filename = "test_roundtrip_287.xml";
    
    doc.Parse("<root><child>hello</child></root>");
    ASSERT_FALSE(doc.Error());
    
    XMLError saveErr = doc.SaveFile(filename, false);
    EXPECT_EQ(saveErr, XML_SUCCESS);
    
    XMLDocument loaded;
    XMLError loadErr = loaded.LoadFile(filename);
    EXPECT_EQ(loadErr, XML_SUCCESS);
    ASSERT_NE(loaded.RootElement(), nullptr);
    EXPECT_STREQ(loaded.RootElement()->Name(), "root");
    
    // Cleanup
    std::remove(filename);
}

// ==================== ErrorStr after multiple errors ====================

TEST_F(XMLDocumentTest_287, ErrorStr_ChangesAfterDifferentErrors_287) {
    doc.Parse("<root><child></root>");
    EXPECT_TRUE(doc.Error());
    const char* errStr1 = doc.ErrorStr();
    ASSERT_NE(errStr1, nullptr);
    EXPECT_STRNE(errStr1, "");
    
    // Parse again with different error
    doc.Parse("");
    EXPECT_TRUE(doc.Error());
    const char* errStr2 = doc.ErrorStr();
    ASSERT_NE(errStr2, nullptr);
    EXPECT_STRNE(errStr2, "");
}
