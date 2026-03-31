#include <gtest/gtest.h>
#include <cstdio>
#include <cstring>
#include <string>
#include "tinyxml2.h"

using namespace tinyxml2;

class XMLDocumentSaveFileTest_282 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test saving an empty document to a FILE pointer
TEST_F(XMLDocumentSaveFileTest_282, SaveEmptyDocument_282) {
    XMLDocument doc;
    FILE* fp = tmpfile();
    ASSERT_NE(fp, nullptr);

    XMLError err = doc.SaveFile(fp, false);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_FALSE(doc.Error());

    fclose(fp);
}

// Test saving a document with content to a FILE pointer (non-compact)
TEST_F(XMLDocumentSaveFileTest_282, SaveDocumentWithContent_282) {
    XMLDocument doc;
    doc.Parse("<root><child>text</child></root>");
    ASSERT_FALSE(doc.Error());

    FILE* fp = tmpfile();
    ASSERT_NE(fp, nullptr);

    XMLError err = doc.SaveFile(fp, false);
    EXPECT_EQ(err, XML_SUCCESS);

    // Verify content was written
    fseek(fp, 0, SEEK_END);
    long size = ftell(fp);
    EXPECT_GT(size, 0);

    // Read back and verify it contains expected XML
    fseek(fp, 0, SEEK_SET);
    std::string content(size, '\0');
    fread(&content[0], 1, size, fp);
    EXPECT_NE(content.find("<root>"), std::string::npos);
    EXPECT_NE(content.find("<child>text</child>"), std::string::npos);

    fclose(fp);
}

// Test saving a document in compact mode
TEST_F(XMLDocumentSaveFileTest_282, SaveDocumentCompactMode_282) {
    XMLDocument doc;
    doc.Parse("<root>\n    <child>text</child>\n</root>");
    ASSERT_FALSE(doc.Error());

    FILE* fpCompact = tmpfile();
    ASSERT_NE(fpCompact, nullptr);
    XMLError errCompact = doc.SaveFile(fpCompact, true);
    EXPECT_EQ(errCompact, XML_SUCCESS);

    fseek(fpCompact, 0, SEEK_END);
    long sizeCompact = ftell(fpCompact);

    FILE* fpNormal = tmpfile();
    ASSERT_NE(fpNormal, nullptr);
    XMLError errNormal = doc.SaveFile(fpNormal, false);
    EXPECT_EQ(errNormal, XML_SUCCESS);

    fseek(fpNormal, 0, SEEK_END);
    long sizeNormal = ftell(fpNormal);

    // Compact mode should generally produce smaller or equal output
    EXPECT_LE(sizeCompact, sizeNormal);

    fclose(fpCompact);
    fclose(fpNormal);
}

// Test that SaveFile clears previous errors
TEST_F(XMLDocumentSaveFileTest_282, SaveFileClearsError_282) {
    XMLDocument doc;
    // Parse invalid XML to set an error
    doc.Parse("<root><unclosed>");
    // The document may or may not have an error depending on implementation,
    // but let's force an error by loading a non-existent file
    doc.LoadFile("nonexistent_file_that_does_not_exist_282.xml");
    EXPECT_TRUE(doc.Error());

    // Now parse valid content
    XMLDocument doc2;
    doc2.Parse("<root/>");
    ASSERT_FALSE(doc2.Error());

    FILE* fp = tmpfile();
    ASSERT_NE(fp, nullptr);

    // SaveFile should clear error before proceeding
    XMLError err = doc2.SaveFile(fp, false);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_FALSE(doc2.Error());

    fclose(fp);
}

// Test saving a document with declaration
TEST_F(XMLDocumentSaveFileTest_282, SaveDocumentWithDeclaration_282) {
    XMLDocument doc;
    doc.Parse("<?xml version=\"1.0\" encoding=\"UTF-8\"?><root/>");
    ASSERT_FALSE(doc.Error());

    FILE* fp = tmpfile();
    ASSERT_NE(fp, nullptr);

    XMLError err = doc.SaveFile(fp, false);
    EXPECT_EQ(err, XML_SUCCESS);

    fseek(fp, 0, SEEK_SET);
    fseek(fp, 0, SEEK_END);
    long size = ftell(fp);
    EXPECT_GT(size, 0);

    fseek(fp, 0, SEEK_SET);
    std::string content(size, '\0');
    fread(&content[0], 1, size, fp);
    EXPECT_NE(content.find("<?xml"), std::string::npos);
    EXPECT_NE(content.find("<root"), std::string::npos);

    fclose(fp);
}

// Test saving a complex document with nested elements and attributes
TEST_F(XMLDocumentSaveFileTest_282, SaveComplexDocument_282) {
    XMLDocument doc;
    const char* xml =
        "<root attr=\"value\">"
        "  <child1 id=\"1\">Text1</child1>"
        "  <child2 id=\"2\">"
        "    <grandchild>Deep text</grandchild>"
        "  </child2>"
        "  <!-- comment -->"
        "</root>";
    doc.Parse(xml);
    ASSERT_FALSE(doc.Error());

    FILE* fp = tmpfile();
    ASSERT_NE(fp, nullptr);

    XMLError err = doc.SaveFile(fp, false);
    EXPECT_EQ(err, XML_SUCCESS);

    fseek(fp, 0, SEEK_END);
    long size = ftell(fp);
    EXPECT_GT(size, 0);

    fseek(fp, 0, SEEK_SET);
    std::string content(size, '\0');
    fread(&content[0], 1, size, fp);
    EXPECT_NE(content.find("attr=\"value\""), std::string::npos);
    EXPECT_NE(content.find("<grandchild>"), std::string::npos);
    EXPECT_NE(content.find("Deep text"), std::string::npos);

    fclose(fp);
}

// Test SaveFile to a named file
TEST_F(XMLDocumentSaveFileTest_282, SaveFileByName_282) {
    XMLDocument doc;
    doc.Parse("<root><item>hello</item></root>");
    ASSERT_FALSE(doc.Error());

    const char* filename = "test_save_282.xml";
    XMLError err = doc.SaveFile(filename, false);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_FALSE(doc.Error());

    // Verify by loading back
    XMLDocument doc2;
    XMLError loadErr = doc2.LoadFile(filename);
    EXPECT_EQ(loadErr, XML_SUCCESS);
    EXPECT_FALSE(doc2.Error());

    XMLElement* root = doc2.RootElement();
    ASSERT_NE(root, nullptr);
    EXPECT_STREQ(root->Name(), "root");

    std::remove(filename);
}

// Test SaveFile with compact mode to a named file
TEST_F(XMLDocumentSaveFileTest_282, SaveFileByNameCompact_282) {
    XMLDocument doc;
    doc.Parse("<root>\n  <child>text</child>\n</root>");
    ASSERT_FALSE(doc.Error());

    const char* filename = "test_save_compact_282.xml";
    XMLError err = doc.SaveFile(filename, true);
    EXPECT_EQ(err, XML_SUCCESS);

    // Load back and verify
    XMLDocument doc2;
    EXPECT_EQ(doc2.LoadFile(filename), XML_SUCCESS);
    EXPECT_NE(doc2.RootElement(), nullptr);

    std::remove(filename);
}

// Test saving to an invalid filename
TEST_F(XMLDocumentSaveFileTest_282, SaveFileInvalidFilename_282) {
    XMLDocument doc;
    doc.Parse("<root/>");
    ASSERT_FALSE(doc.Error());

    // Try to save to a path that should fail
    XMLError err = doc.SaveFile("/nonexistent_dir_282/nonexistent_subdir/file.xml", false);
    EXPECT_NE(err, XML_SUCCESS);
    EXPECT_TRUE(doc.Error());
}

// Test SaveFile returns XML_SUCCESS for an error-free document
TEST_F(XMLDocumentSaveFileTest_282, SaveFileReturnsSuccess_282) {
    XMLDocument doc;
    XMLElement* root = doc.NewElement("root");
    doc.InsertEndChild(root);
    XMLElement* child = doc.NewElement("child");
    child->SetText("value");
    root->InsertEndChild(child);

    FILE* fp = tmpfile();
    ASSERT_NE(fp, nullptr);

    XMLError err = doc.SaveFile(fp, false);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_EQ(doc.ErrorID(), XML_SUCCESS);

    fclose(fp);
}

// Test saving document with BOM
TEST_F(XMLDocumentSaveFileTest_282, SaveDocumentWithBOM_282) {
    XMLDocument doc;
    doc.Parse("<root/>");
    ASSERT_FALSE(doc.Error());
    doc.SetBOM(true);

    FILE* fp = tmpfile();
    ASSERT_NE(fp, nullptr);

    XMLError err = doc.SaveFile(fp, false);
    EXPECT_EQ(err, XML_SUCCESS);

    // Check that BOM is written (UTF-8 BOM: 0xEF 0xBB 0xBF)
    fseek(fp, 0, SEEK_SET);
    unsigned char bom[3] = {0};
    size_t read = fread(bom, 1, 3, fp);
    EXPECT_EQ(read, 3u);
    EXPECT_EQ(bom[0], 0xEF);
    EXPECT_EQ(bom[1], 0xBB);
    EXPECT_EQ(bom[2], 0xBF);

    fclose(fp);
}

// Test saving document without BOM
TEST_F(XMLDocumentSaveFileTest_282, SaveDocumentWithoutBOM_282) {
    XMLDocument doc;
    doc.Parse("<root/>");
    ASSERT_FALSE(doc.Error());
    doc.SetBOM(false);

    FILE* fp = tmpfile();
    ASSERT_NE(fp, nullptr);

    XMLError err = doc.SaveFile(fp, false);
    EXPECT_EQ(err, XML_SUCCESS);

    fseek(fp, 0, SEEK_SET);
    unsigned char firstByte = 0;
    fread(&firstByte, 1, 1, fp);
    // Should not start with BOM byte
    EXPECT_NE(firstByte, 0xEF);

    fclose(fp);
}

// Test that error state is cleared by SaveFile
TEST_F(XMLDocumentSaveFileTest_282, ErrorClearedBySaveFile_282) {
    XMLDocument doc;
    // Induce an error
    doc.LoadFile("this_file_does_not_exist_at_all_282.xml");
    EXPECT_TRUE(doc.Error());
    EXPECT_NE(doc.ErrorID(), XML_SUCCESS);

    // Parse valid content to have something to save
    doc.Parse("<root/>");

    FILE* fp = tmpfile();
    ASSERT_NE(fp, nullptr);

    XMLError err = doc.SaveFile(fp, false);
    // After SaveFile, error should be cleared (ClearError is called)
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_FALSE(doc.Error());

    fclose(fp);
}

// Test round-trip: save and load back
TEST_F(XMLDocumentSaveFileTest_282, RoundTripSaveLoad_282) {
    XMLDocument doc;
    const char* xml = "<root><a attr=\"1\">text</a><b/></root>";
    doc.Parse(xml);
    ASSERT_FALSE(doc.Error());

    const char* filename = "test_roundtrip_282.xml";
    EXPECT_EQ(doc.SaveFile(filename, false), XML_SUCCESS);

    XMLDocument doc2;
    EXPECT_EQ(doc2.LoadFile(filename), XML_SUCCESS);
    ASSERT_FALSE(doc2.Error());

    XMLElement* root = doc2.RootElement();
    ASSERT_NE(root, nullptr);
    EXPECT_STREQ(root->Name(), "root");

    XMLElement* a = root->FirstChildElement("a");
    ASSERT_NE(a, nullptr);
    EXPECT_STREQ(a->Attribute("attr"), "1");
    EXPECT_STREQ(a->GetText(), "text");

    XMLElement* b = root->FirstChildElement("b");
    ASSERT_NE(b, nullptr);

    std::remove(filename);
}

// Test saving a document with special characters
TEST_F(XMLDocumentSaveFileTest_282, SaveDocumentWithSpecialChars_282) {
    XMLDocument doc;
    doc.Parse("<root>&amp;&lt;&gt;&quot;</root>");
    ASSERT_FALSE(doc.Error());

    FILE* fp = tmpfile();
    ASSERT_NE(fp, nullptr);

    XMLError err = doc.SaveFile(fp, false);
    EXPECT_EQ(err, XML_SUCCESS);

    fseek(fp, 0, SEEK_END);
    long size = ftell(fp);
    fseek(fp, 0, SEEK_SET);
    std::string content(size, '\0');
    fread(&content[0], 1, size, fp);

    // The special characters should be preserved in entity form
    EXPECT_NE(content.find("&amp;"), std::string::npos);
    EXPECT_NE(content.find("&lt;"), std::string::npos);
    EXPECT_NE(content.find("&gt;"), std::string::npos);

    fclose(fp);
}

// Test saving an empty document (no root element) to named file
TEST_F(XMLDocumentSaveFileTest_282, SaveEmptyDocumentToFile_282) {
    XMLDocument doc;

    const char* filename = "test_empty_save_282.xml";
    XMLError err = doc.SaveFile(filename, false);
    EXPECT_EQ(err, XML_SUCCESS);

    // File should exist but may be empty or minimal
    FILE* fp = fopen(filename, "r");
    EXPECT_NE(fp, nullptr);
    if (fp) fclose(fp);

    std::remove(filename);
}
