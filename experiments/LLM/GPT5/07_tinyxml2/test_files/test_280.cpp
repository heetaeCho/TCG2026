// File: ./TestProjects/tinyxml2/tests/XMLDocumentLoadFileFpTest_280.cpp

#include <gtest/gtest.h>

#include <cstdio>
#include <cstring>

#include "tinyxml2.h"

using namespace tinyxml2;

namespace {

class XMLDocumentLoadFileFpTest_280 : public ::testing::Test {
protected:
    static FILE* MakeTempFileWithContents(const char* bytes) {
        FILE* fp = std::tmpfile();
        if (!fp) return nullptr;

        if (bytes && bytes[0] != '\0') {
            const size_t len = std::strlen(bytes);
            const size_t written = std::fwrite(bytes, 1, len, fp);
            // If writing fails, return nullptr so the test can fail clearly.
            if (written != len) {
                std::fclose(fp);
                return nullptr;
            }
        }
        std::fflush(fp);
        std::rewind(fp);
        return fp;
    }

    static void CloseFile(FILE*& fp) {
        if (fp) {
            std::fclose(fp);
            fp = nullptr;
        }
    }
};

TEST_F(XMLDocumentLoadFileFpTest_280, EmptyFileReturnsEmptyDocumentError_280) {
    XMLDocument doc(/*processEntities=*/true, Whitespace::PRESERVE_WHITESPACE);

    FILE* fp = MakeTempFileWithContents("");
    ASSERT_NE(fp, nullptr);

    const XMLError err = doc.LoadFile(fp);

    EXPECT_EQ(err, XML_ERROR_EMPTY_DOCUMENT);
    EXPECT_TRUE(doc.Error());
    EXPECT_EQ(doc.ErrorID(), XML_ERROR_EMPTY_DOCUMENT);
    EXPECT_EQ(doc.RootElement(), nullptr);

    CloseFile(fp);
}

TEST_F(XMLDocumentLoadFileFpTest_280, ValidXmlReturnsSuccessAndRootElement_280) {
    XMLDocument doc(/*processEntities=*/true, Whitespace::PRESERVE_WHITESPACE);

    FILE* fp = MakeTempFileWithContents("<root/>");
    ASSERT_NE(fp, nullptr);

    const XMLError err = doc.LoadFile(fp);

    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_FALSE(doc.Error());
    EXPECT_EQ(doc.ErrorID(), XML_SUCCESS);

    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);
    EXPECT_STREQ(root->Name(), "root");

    CloseFile(fp);
}

TEST_F(XMLDocumentLoadFileFpTest_280, InvalidXmlReturnsNonSuccessAndSetsErrorFlag_280) {
    XMLDocument doc(/*processEntities=*/true, Whitespace::PRESERVE_WHITESPACE);

    // Malformed XML: missing closing tag for <root>
    FILE* fp = MakeTempFileWithContents("<root>");
    ASSERT_NE(fp, nullptr);

    const XMLError err = doc.LoadFile(fp);

    EXPECT_NE(err, XML_SUCCESS);
    EXPECT_TRUE(doc.Error());
    EXPECT_NE(doc.ErrorID(), XML_SUCCESS);

    // RootElement() may or may not exist depending on parser behavior when it errors;
    // don't assert either way (black-box requirement).

    CloseFile(fp);
}

TEST_F(XMLDocumentLoadFileFpTest_280, LoadFileClearsPreviousDocumentBeforeLoading_280) {
    XMLDocument doc(/*processEntities=*/true, Whitespace::PRESERVE_WHITESPACE);

    // First load a valid document.
    FILE* fp1 = MakeTempFileWithContents("<root><child/></root>");
    ASSERT_NE(fp1, nullptr);
    EXPECT_EQ(doc.LoadFile(fp1), XML_SUCCESS);
    ASSERT_NE(doc.RootElement(), nullptr);
    EXPECT_STREQ(doc.RootElement()->Name(), "root");
    CloseFile(fp1);

    // Then load an empty document; observable behavior should reflect a cleared state.
    FILE* fp2 = MakeTempFileWithContents("");
    ASSERT_NE(fp2, nullptr);

    const XMLError err2 = doc.LoadFile(fp2);

    EXPECT_EQ(err2, XML_ERROR_EMPTY_DOCUMENT);
    EXPECT_TRUE(doc.Error());
    EXPECT_EQ(doc.ErrorID(), XML_ERROR_EMPTY_DOCUMENT);
    EXPECT_EQ(doc.RootElement(), nullptr);

    CloseFile(fp2);
}

}  // namespace
