#include <gtest/gtest.h>
#include <cstdio>
#include <cstring>
#include <string>
#include "tinyxml2.h"

using namespace tinyxml2;

// Helper function to create a temporary file with given content
static FILE* CreateTempFileWithContent(const char* content, size_t length) {
    FILE* fp = tmpfile();
    if (fp && content && length > 0) {
        fwrite(content, 1, length, fp);
        rewind(fp);
    }
    return fp;
}

static FILE* CreateTempFileWithContent(const char* content) {
    return CreateTempFileWithContent(content, strlen(content));
}

class XMLDocumentLoadFileTest_280 : public ::testing::Test {
protected:
    XMLDocument doc;
};

// Test loading a valid XML file
TEST_F(XMLDocumentLoadFileTest_280, LoadValidXMLFile_280) {
    const char* xml = "<root><child>text</child></root>";
    FILE* fp = CreateTempFileWithContent(xml);
    ASSERT_NE(fp, nullptr);

    XMLError err = doc.LoadFile(fp);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_FALSE(doc.Error());
    EXPECT_EQ(doc.ErrorID(), XML_SUCCESS);

    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);
    EXPECT_STREQ(root->Name(), "root");

    fclose(fp);
}

// Test loading an empty file returns XML_ERROR_EMPTY_DOCUMENT
TEST_F(XMLDocumentLoadFileTest_280, LoadEmptyFile_280) {
    FILE* fp = tmpfile();
    ASSERT_NE(fp, nullptr);
    // File is empty, no content written

    XMLError err = doc.LoadFile(fp);
    EXPECT_EQ(err, XML_ERROR_EMPTY_DOCUMENT);
    EXPECT_TRUE(doc.Error());
    EXPECT_EQ(doc.ErrorID(), XML_ERROR_EMPTY_DOCUMENT);

    fclose(fp);
}

// Test loading a file with XML declaration
TEST_F(XMLDocumentLoadFileTest_280, LoadFileWithDeclaration_280) {
    const char* xml = "<?xml version=\"1.0\" encoding=\"UTF-8\"?><root/>";
    FILE* fp = CreateTempFileWithContent(xml);
    ASSERT_NE(fp, nullptr);

    XMLError err = doc.LoadFile(fp);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_FALSE(doc.Error());

    fclose(fp);
}

// Test loading a file with nested elements
TEST_F(XMLDocumentLoadFileTest_280, LoadFileWithNestedElements_280) {
    const char* xml = "<a><b><c>deep</c></b></a>";
    FILE* fp = CreateTempFileWithContent(xml);
    ASSERT_NE(fp, nullptr);

    XMLError err = doc.LoadFile(fp);
    EXPECT_EQ(err, XML_SUCCESS);

    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);
    EXPECT_STREQ(root->Name(), "a");

    XMLElement* b = root->FirstChildElement("b");
    ASSERT_NE(b, nullptr);

    XMLElement* c = b->FirstChildElement("c");
    ASSERT_NE(c, nullptr);
    EXPECT_STREQ(c->GetText(), "deep");

    fclose(fp);
}

// Test loading a file with malformed XML
TEST_F(XMLDocumentLoadFileTest_280, LoadFileMalformedXML_280) {
    const char* xml = "<root><child></root>";
    FILE* fp = CreateTempFileWithContent(xml);
    ASSERT_NE(fp, nullptr);

    XMLError err = doc.LoadFile(fp);
    EXPECT_NE(err, XML_SUCCESS);
    EXPECT_TRUE(doc.Error());

    fclose(fp);
}

// Test loading a file with attributes
TEST_F(XMLDocumentLoadFileTest_280, LoadFileWithAttributes_280) {
    const char* xml = "<root attr1=\"value1\" attr2=\"value2\"/>";
    FILE* fp = CreateTempFileWithContent(xml);
    ASSERT_NE(fp, nullptr);

    XMLError err = doc.LoadFile(fp);
    EXPECT_EQ(err, XML_SUCCESS);

    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);
    EXPECT_STREQ(root->Attribute("attr1"), "value1");
    EXPECT_STREQ(root->Attribute("attr2"), "value2");

    fclose(fp);
}

// Test loading a file with comments
TEST_F(XMLDocumentLoadFileTest_280, LoadFileWithComments_280) {
    const char* xml = "<!-- This is a comment --><root/>";
    FILE* fp = CreateTempFileWithContent(xml);
    ASSERT_NE(fp, nullptr);

    XMLError err = doc.LoadFile(fp);
    EXPECT_EQ(err, XML_SUCCESS);

    fclose(fp);
}

// Test that loading clears previous state
TEST_F(XMLDocumentLoadFileTest_280, LoadFileClearsPreviousState_280) {
    // First load
    const char* xml1 = "<first/>";
    FILE* fp1 = CreateTempFileWithContent(xml1);
    ASSERT_NE(fp1, nullptr);
    doc.LoadFile(fp1);
    fclose(fp1);

    XMLElement* root1 = doc.RootElement();
    ASSERT_NE(root1, nullptr);
    EXPECT_STREQ(root1->Name(), "first");

    // Second load should clear previous state
    const char* xml2 = "<second/>";
    FILE* fp2 = CreateTempFileWithContent(xml2);
    ASSERT_NE(fp2, nullptr);
    doc.LoadFile(fp2);
    fclose(fp2);

    XMLElement* root2 = doc.RootElement();
    ASSERT_NE(root2, nullptr);
    EXPECT_STREQ(root2->Name(), "second");
}

// Test loading a file with only whitespace (no valid XML)
TEST_F(XMLDocumentLoadFileTest_280, LoadFileWithOnlyWhitespace_280) {
    const char* xml = "   \n\t  ";
    FILE* fp = CreateTempFileWithContent(xml);
    ASSERT_NE(fp, nullptr);

    XMLError err = doc.LoadFile(fp);
    EXPECT_NE(err, XML_SUCCESS);
    EXPECT_TRUE(doc.Error());

    fclose(fp);
}

// Test loading a valid minimal XML
TEST_F(XMLDocumentLoadFileTest_280, LoadFileMinimalXML_280) {
    const char* xml = "<r/>";
    FILE* fp = CreateTempFileWithContent(xml);
    ASSERT_NE(fp, nullptr);

    XMLError err = doc.LoadFile(fp);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_FALSE(doc.Error());

    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);
    EXPECT_STREQ(root->Name(), "r");

    fclose(fp);
}

// Test that ErrorID is correct after successful load
TEST_F(XMLDocumentLoadFileTest_280, ErrorIDAfterSuccessfulLoad_280) {
    const char* xml = "<root/>";
    FILE* fp = CreateTempFileWithContent(xml);
    ASSERT_NE(fp, nullptr);

    doc.LoadFile(fp);
    EXPECT_EQ(doc.ErrorID(), XML_SUCCESS);
    EXPECT_FALSE(doc.Error());

    fclose(fp);
}

// Test that ErrorID is correct after failed load
TEST_F(XMLDocumentLoadFileTest_280, ErrorIDAfterFailedLoad_280) {
    FILE* fp = tmpfile();
    ASSERT_NE(fp, nullptr);
    // Empty file

    doc.LoadFile(fp);
    EXPECT_EQ(doc.ErrorID(), XML_ERROR_EMPTY_DOCUMENT);
    EXPECT_TRUE(doc.Error());

    fclose(fp);
}

// Test loading file with CDATA section
TEST_F(XMLDocumentLoadFileTest_280, LoadFileWithCDATA_280) {
    const char* xml = "<root><![CDATA[Some <special> data]]></root>";
    FILE* fp = CreateTempFileWithContent(xml);
    ASSERT_NE(fp, nullptr);

    XMLError err = doc.LoadFile(fp);
    EXPECT_EQ(err, XML_SUCCESS);

    fclose(fp);
}

// Test loading file with multiple root elements (should fail or parse first)
TEST_F(XMLDocumentLoadFileTest_280, LoadFileWithContent_280) {
    const char* xml = "<root>Hello World</root>";
    FILE* fp = CreateTempFileWithContent(xml);
    ASSERT_NE(fp, nullptr);

    XMLError err = doc.LoadFile(fp);
    EXPECT_EQ(err, XML_SUCCESS);

    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);
    EXPECT_STREQ(root->GetText(), "Hello World");

    fclose(fp);
}

// Test ClearError after a failed load
TEST_F(XMLDocumentLoadFileTest_280, ClearErrorAfterFailedLoad_280) {
    FILE* fp = tmpfile();
    ASSERT_NE(fp, nullptr);

    doc.LoadFile(fp);
    EXPECT_TRUE(doc.Error());

    doc.ClearError();
    EXPECT_FALSE(doc.Error());
    EXPECT_EQ(doc.ErrorID(), XML_SUCCESS);

    fclose(fp);
}

// Test loading a large XML file
TEST_F(XMLDocumentLoadFileTest_280, LoadLargeXMLFile_280) {
    std::string xml = "<root>";
    for (int i = 0; i < 1000; ++i) {
        xml += "<item id=\"" + std::to_string(i) + "\">value" + std::to_string(i) + "</item>";
    }
    xml += "</root>";

    FILE* fp = CreateTempFileWithContent(xml.c_str());
    ASSERT_NE(fp, nullptr);

    XMLError err = doc.LoadFile(fp);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_FALSE(doc.Error());

    fclose(fp);
}

// Test loading file with special characters / entities
TEST_F(XMLDocumentLoadFileTest_280, LoadFileWithEntities_280) {
    const char* xml = "<root>&lt;&gt;&amp;&apos;&quot;</root>";
    FILE* fp = CreateTempFileWithContent(xml);
    ASSERT_NE(fp, nullptr);

    XMLError err = doc.LoadFile(fp);
    EXPECT_EQ(err, XML_SUCCESS);

    fclose(fp);
}

// Test ErrorName returns non-null after error
TEST_F(XMLDocumentLoadFileTest_280, ErrorNameAfterError_280) {
    FILE* fp = tmpfile();
    ASSERT_NE(fp, nullptr);

    doc.LoadFile(fp);
    EXPECT_TRUE(doc.Error());

    const char* errName = doc.ErrorName();
    EXPECT_NE(errName, nullptr);

    fclose(fp);
}

// Test ErrorStr returns non-null after error
TEST_F(XMLDocumentLoadFileTest_280, ErrorStrAfterError_280) {
    FILE* fp = tmpfile();
    ASSERT_NE(fp, nullptr);

    doc.LoadFile(fp);
    EXPECT_TRUE(doc.Error());

    const char* errStr = doc.ErrorStr();
    EXPECT_NE(errStr, nullptr);

    fclose(fp);
}

// Test loading a file with mismatched tags
TEST_F(XMLDocumentLoadFileTest_280, LoadFileMismatchedTags_280) {
    const char* xml = "<root><child></other></root>";
    FILE* fp = CreateTempFileWithContent(xml);
    ASSERT_NE(fp, nullptr);

    XMLError err = doc.LoadFile(fp);
    EXPECT_NE(err, XML_SUCCESS);
    EXPECT_TRUE(doc.Error());

    fclose(fp);
}

// Test loading a single byte file (non-empty but not valid XML)
TEST_F(XMLDocumentLoadFileTest_280, LoadFileSingleByte_280) {
    const char* xml = "x";
    FILE* fp = CreateTempFileWithContent(xml);
    ASSERT_NE(fp, nullptr);

    XMLError err = doc.LoadFile(fp);
    // Single byte 'x' is not valid XML
    EXPECT_NE(err, XML_SUCCESS);
    EXPECT_TRUE(doc.Error());

    fclose(fp);
}

// Test that loading a second time clears errors from first load
TEST_F(XMLDocumentLoadFileTest_280, LoadFileAfterErrorClearsError_280) {
    // First load with empty file (error)
    FILE* fp1 = tmpfile();
    ASSERT_NE(fp1, nullptr);
    doc.LoadFile(fp1);
    EXPECT_TRUE(doc.Error());
    fclose(fp1);

    // Second load with valid file
    const char* xml = "<root/>";
    FILE* fp2 = CreateTempFileWithContent(xml);
    ASSERT_NE(fp2, nullptr);
    XMLError err = doc.LoadFile(fp2);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_FALSE(doc.Error());
    fclose(fp2);
}
