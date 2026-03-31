#include <gtest/gtest.h>
#include <cstdio>
#include <cstring>
#include <string>
#include "tinyxml2.h"

using namespace tinyxml2;

// Helper to create a temporary file path
static std::string GetTempFilePath(const std::string& suffix) {
    return std::string("test_tinyxml2_") + suffix + ".xml";
}

// Helper to remove a file
static void RemoveFile(const std::string& path) {
    std::remove(path.c_str());
}

// Helper to read file contents
static std::string ReadFileContents(const std::string& path) {
    FILE* fp = fopen(path.c_str(), "r");
    if (!fp) return "";
    std::string result;
    char buf[1024];
    while (size_t n = fread(buf, 1, sizeof(buf), fp)) {
        result.append(buf, n);
    }
    fclose(fp);
    return result;
}

//=============================================================================
// Test Fixture
//=============================================================================
class XMLDocumentSaveFileTest_281 : public ::testing::Test {
protected:
    void TearDown() override {
        for (const auto& f : filesToClean) {
            RemoveFile(f);
        }
    }

    void TrackFile(const std::string& f) {
        filesToClean.push_back(f);
    }

    std::vector<std::string> filesToClean;
};

//=============================================================================
// SaveFile(const char* filename, bool compact) tests
//=============================================================================

TEST_F(XMLDocumentSaveFileTest_281, SaveFileNullFilenameReturnsError_281) {
    XMLDocument doc;
    doc.Parse("<root/>");
    ASSERT_FALSE(doc.Error());

    XMLError err = doc.SaveFile(static_cast<const char*>(nullptr), false);
    EXPECT_EQ(err, XML_ERROR_FILE_COULD_NOT_BE_OPENED);
    EXPECT_TRUE(doc.Error());
    EXPECT_EQ(doc.ErrorID(), XML_ERROR_FILE_COULD_NOT_BE_OPENED);
}

TEST_F(XMLDocumentSaveFileTest_281, SaveFileValidFilenameReturnsSuccess_281) {
    std::string path = GetTempFilePath("valid");
    TrackFile(path);

    XMLDocument doc;
    doc.Parse("<root><child/></root>");
    ASSERT_FALSE(doc.Error());

    XMLError err = doc.SaveFile(path.c_str(), false);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_FALSE(doc.Error());

    // Verify the file was actually created and has content
    std::string contents = ReadFileContents(path);
    EXPECT_FALSE(contents.empty());
    EXPECT_NE(contents.find("root"), std::string::npos);
}

TEST_F(XMLDocumentSaveFileTest_281, SaveFileCompactModeProducesSmallerOutput_281) {
    std::string pathCompact = GetTempFilePath("compact");
    std::string pathNormal = GetTempFilePath("normal");
    TrackFile(pathCompact);
    TrackFile(pathNormal);

    XMLDocument doc;
    doc.Parse("<root><child>text</child><child2>more text</child2></root>");
    ASSERT_FALSE(doc.Error());

    XMLError err1 = doc.SaveFile(pathNormal.c_str(), false);
    EXPECT_EQ(err1, XML_SUCCESS);

    XMLError err2 = doc.SaveFile(pathCompact.c_str(), true);
    EXPECT_EQ(err2, XML_SUCCESS);

    std::string normalContents = ReadFileContents(pathNormal);
    std::string compactContents = ReadFileContents(pathCompact);

    // Compact should generally be no larger than normal (usually smaller due to less whitespace)
    EXPECT_LE(compactContents.size(), normalContents.size());
}

TEST_F(XMLDocumentSaveFileTest_281, SaveFileInvalidPathReturnsError_281) {
    XMLDocument doc;
    doc.Parse("<root/>");
    ASSERT_FALSE(doc.Error());

    // Use a path that should fail to open (directory that doesn't exist)
    XMLError err = doc.SaveFile("/nonexistent_dir_xyz/nonexistent_subdir/file.xml", false);
    EXPECT_EQ(err, XML_ERROR_FILE_COULD_NOT_BE_OPENED);
    EXPECT_TRUE(doc.Error());
}

TEST_F(XMLDocumentSaveFileTest_281, SaveFileEmptyDocumentStillSaves_281) {
    std::string path = GetTempFilePath("empty_doc");
    TrackFile(path);

    XMLDocument doc;
    // No parse, empty document
    XMLError err = doc.SaveFile(path.c_str(), false);
    EXPECT_EQ(err, XML_SUCCESS);
}

TEST_F(XMLDocumentSaveFileTest_281, SaveFileThenLoadFileRoundTrip_281) {
    std::string path = GetTempFilePath("roundtrip");
    TrackFile(path);

    const char* xmlInput = "<root attr=\"value\"><child>Hello World</child></root>";

    XMLDocument doc;
    doc.Parse(xmlInput);
    ASSERT_FALSE(doc.Error());

    XMLError saveErr = doc.SaveFile(path.c_str(), false);
    EXPECT_EQ(saveErr, XML_SUCCESS);

    XMLDocument doc2;
    XMLError loadErr = doc2.LoadFile(path.c_str());
    EXPECT_EQ(loadErr, XML_SUCCESS);
    EXPECT_FALSE(doc2.Error());

    // Verify the round-tripped document has the expected structure
    XMLElement* root = doc2.RootElement();
    ASSERT_NE(root, nullptr);
    EXPECT_STREQ(root->Name(), "root");

    const char* attrVal = root->Attribute("attr");
    ASSERT_NE(attrVal, nullptr);
    EXPECT_STREQ(attrVal, "value");

    XMLElement* child = root->FirstChildElement("child");
    ASSERT_NE(child, nullptr);
    EXPECT_STREQ(child->GetText(), "Hello World");
}

TEST_F(XMLDocumentSaveFileTest_281, SaveFileWithBOM_281) {
    std::string path = GetTempFilePath("bom");
    TrackFile(path);

    XMLDocument doc;
    doc.Parse("<root/>");
    ASSERT_FALSE(doc.Error());
    doc.SetBOM(true);

    XMLError err = doc.SaveFile(path.c_str(), false);
    EXPECT_EQ(err, XML_SUCCESS);

    // Read raw bytes and check for BOM
    FILE* fp = fopen(path.c_str(), "rb");
    ASSERT_NE(fp, nullptr);
    unsigned char bom[3] = {0};
    size_t read = fread(bom, 1, 3, fp);
    fclose(fp);
    EXPECT_GE(read, 3u);
    EXPECT_EQ(bom[0], 0xEF);
    EXPECT_EQ(bom[1], 0xBB);
    EXPECT_EQ(bom[2], 0xBF);
}

TEST_F(XMLDocumentSaveFileTest_281, SaveFileWithoutBOM_281) {
    std::string path = GetTempFilePath("nobom");
    TrackFile(path);

    XMLDocument doc;
    doc.Parse("<root/>");
    ASSERT_FALSE(doc.Error());
    doc.SetBOM(false);

    XMLError err = doc.SaveFile(path.c_str(), false);
    EXPECT_EQ(err, XML_SUCCESS);

    // Read raw bytes and verify no BOM
    FILE* fp = fopen(path.c_str(), "rb");
    ASSERT_NE(fp, nullptr);
    unsigned char first[3] = {0};
    size_t read = fread(first, 1, 3, fp);
    fclose(fp);
    if (read >= 3) {
        bool hasBOM = (first[0] == 0xEF && first[1] == 0xBB && first[2] == 0xBF);
        EXPECT_FALSE(hasBOM);
    }
}

//=============================================================================
// SaveFile(FILE* fp, bool compact) tests
//=============================================================================

TEST_F(XMLDocumentSaveFileTest_281, SaveFileToFPReturnsSuccess_281) {
    std::string path = GetTempFilePath("fp_save");
    TrackFile(path);

    XMLDocument doc;
    doc.Parse("<root><item>data</item></root>");
    ASSERT_FALSE(doc.Error());

    FILE* fp = fopen(path.c_str(), "w");
    ASSERT_NE(fp, nullptr);
    XMLError err = doc.SaveFile(fp, false);
    fclose(fp);

    EXPECT_EQ(err, XML_SUCCESS);

    std::string contents = ReadFileContents(path);
    EXPECT_NE(contents.find("root"), std::string::npos);
    EXPECT_NE(contents.find("item"), std::string::npos);
    EXPECT_NE(contents.find("data"), std::string::npos);
}

TEST_F(XMLDocumentSaveFileTest_281, SaveFileToFPCompact_281) {
    std::string pathCompact = GetTempFilePath("fp_compact");
    std::string pathNormal = GetTempFilePath("fp_normal");
    TrackFile(pathCompact);
    TrackFile(pathNormal);

    XMLDocument doc;
    doc.Parse("<root><a>text1</a><b>text2</b></root>");
    ASSERT_FALSE(doc.Error());

    FILE* fp1 = fopen(pathNormal.c_str(), "w");
    ASSERT_NE(fp1, nullptr);
    doc.SaveFile(fp1, false);
    fclose(fp1);

    FILE* fp2 = fopen(pathCompact.c_str(), "w");
    ASSERT_NE(fp2, nullptr);
    doc.SaveFile(fp2, true);
    fclose(fp2);

    std::string normalContents = ReadFileContents(pathNormal);
    std::string compactContents = ReadFileContents(pathCompact);

    EXPECT_LE(compactContents.size(), normalContents.size());
}

//=============================================================================
// ClearError after SaveFile tests
//=============================================================================

TEST_F(XMLDocumentSaveFileTest_281, ClearErrorAfterSaveFileFailure_281) {
    XMLDocument doc;
    doc.Parse("<root/>");
    ASSERT_FALSE(doc.Error());

    // Trigger an error
    doc.SaveFile(static_cast<const char*>(nullptr), false);
    EXPECT_TRUE(doc.Error());

    doc.ClearError();
    EXPECT_FALSE(doc.Error());
    EXPECT_EQ(doc.ErrorID(), XML_SUCCESS);
}

//=============================================================================
// Multiple saves
//=============================================================================

TEST_F(XMLDocumentSaveFileTest_281, MultipleSavesToDifferentFiles_281) {
    std::string path1 = GetTempFilePath("multi1");
    std::string path2 = GetTempFilePath("multi2");
    TrackFile(path1);
    TrackFile(path2);

    XMLDocument doc;
    doc.Parse("<root><child/></root>");
    ASSERT_FALSE(doc.Error());

    XMLError err1 = doc.SaveFile(path1.c_str(), false);
    EXPECT_EQ(err1, XML_SUCCESS);

    XMLError err2 = doc.SaveFile(path2.c_str(), true);
    EXPECT_EQ(err2, XML_SUCCESS);

    // Both files should exist and have content
    std::string contents1 = ReadFileContents(path1);
    std::string contents2 = ReadFileContents(path2);
    EXPECT_FALSE(contents1.empty());
    EXPECT_FALSE(contents2.empty());
}

//=============================================================================
// SaveFile with complex document
//=============================================================================

TEST_F(XMLDocumentSaveFileTest_281, SaveFileComplexDocument_281) {
    std::string path = GetTempFilePath("complex");
    TrackFile(path);

    XMLDocument doc;
    const char* xml =
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>"
        "<root>"
        "  <element attr1=\"val1\" attr2=\"val2\">"
        "    <nested>Some text &amp; entities</nested>"
        "  </element>"
        "  <!-- A comment -->"
        "</root>";
    doc.Parse(xml);
    ASSERT_FALSE(doc.Error());

    XMLError err = doc.SaveFile(path.c_str(), false);
    EXPECT_EQ(err, XML_SUCCESS);

    // Load it back and verify
    XMLDocument doc2;
    EXPECT_EQ(doc2.LoadFile(path.c_str()), XML_SUCCESS);

    XMLElement* root = doc2.RootElement();
    ASSERT_NE(root, nullptr);
    EXPECT_STREQ(root->Name(), "root");
}

//=============================================================================
// SaveFile overwrites existing file
//=============================================================================

TEST_F(XMLDocumentSaveFileTest_281, SaveFileOverwritesExistingFile_281) {
    std::string path = GetTempFilePath("overwrite");
    TrackFile(path);

    // Write first document
    {
        XMLDocument doc;
        doc.Parse("<first>content1</first>");
        ASSERT_FALSE(doc.Error());
        EXPECT_EQ(doc.SaveFile(path.c_str(), false), XML_SUCCESS);
    }

    // Overwrite with second document
    {
        XMLDocument doc;
        doc.Parse("<second>content2</second>");
        ASSERT_FALSE(doc.Error());
        EXPECT_EQ(doc.SaveFile(path.c_str(), false), XML_SUCCESS);
    }

    // Verify the file contains the second document
    XMLDocument doc;
    EXPECT_EQ(doc.LoadFile(path.c_str()), XML_SUCCESS);
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);
    EXPECT_STREQ(root->Name(), "second");
    EXPECT_STREQ(root->GetText(), "content2");
}

//=============================================================================
// ErrorName / ErrorStr after failed save
//=============================================================================

TEST_F(XMLDocumentSaveFileTest_281, ErrorNameAfterFailedSave_281) {
    XMLDocument doc;
    doc.Parse("<root/>");
    ASSERT_FALSE(doc.Error());

    doc.SaveFile("/nonexistent_dir_xyz/file.xml", false);
    EXPECT_TRUE(doc.Error());

    const char* errName = doc.ErrorName();
    ASSERT_NE(errName, nullptr);
    // Should be the name for XML_ERROR_FILE_COULD_NOT_BE_OPENED
    EXPECT_STRNE(errName, "");

    const char* errStr = doc.ErrorStr();
    ASSERT_NE(errStr, nullptr);
    EXPECT_STRNE(errStr, "");
}

//=============================================================================
// SaveFile with declaration
//=============================================================================

TEST_F(XMLDocumentSaveFileTest_281, SaveFilePreservesDeclaration_281) {
    std::string path = GetTempFilePath("declaration");
    TrackFile(path);

    XMLDocument doc;
    XMLDeclaration* decl = doc.NewDeclaration("xml version=\"1.0\" encoding=\"UTF-8\"");
    doc.InsertFirstChild(decl);
    XMLElement* root = doc.NewElement("root");
    doc.InsertEndChild(root);

    XMLError err = doc.SaveFile(path.c_str(), false);
    EXPECT_EQ(err, XML_SUCCESS);

    std::string contents = ReadFileContents(path);
    EXPECT_NE(contents.find("<?xml"), std::string::npos);
    EXPECT_NE(contents.find("root"), std::string::npos);
}

//=============================================================================
// ErrorID consistency
//=============================================================================

TEST_F(XMLDocumentSaveFileTest_281, ErrorIDConsistentWithReturnValue_281) {
    XMLDocument doc;
    doc.Parse("<root/>");

    // Successful save
    std::string path = GetTempFilePath("errid");
    TrackFile(path);
    XMLError ret = doc.SaveFile(path.c_str(), false);
    EXPECT_EQ(ret, doc.ErrorID());
    EXPECT_EQ(ret, XML_SUCCESS);

    // Failed save
    XMLError ret2 = doc.SaveFile("/nonexistent_xyz/file.xml", false);
    EXPECT_EQ(ret2, doc.ErrorID());
    EXPECT_EQ(ret2, XML_ERROR_FILE_COULD_NOT_BE_OPENED);
}
