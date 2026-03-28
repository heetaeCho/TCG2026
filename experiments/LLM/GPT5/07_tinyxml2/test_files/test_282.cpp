// TEST_ID: 282
#include <gtest/gtest.h>

#include <cstdio>
#include <cstring>
#include <string>

#include "tinyxml2.h"

namespace {

std::string ReadAllFromFile(FILE* fp) {
    if (!fp) return {};
    std::fflush(fp);
    std::fseek(fp, 0, SEEK_END);
    long size = std::ftell(fp);
    if (size < 0) {
        std::rewind(fp);
        return {};
    }
    std::rewind(fp);

    std::string out;
    out.resize(static_cast<size_t>(size));
    if (size > 0) {
        const size_t n = std::fread(&out[0], 1, static_cast<size_t>(size), fp);
        out.resize(n);
    }
    return out;
}

}  // namespace

class XMLDocumentSaveFileFILETest_282 : public ::testing::Test {
protected:
    tinyxml2::XMLDocument doc{true, tinyxml2::PRESERVE_WHITESPACE};
};

TEST_F(XMLDocumentSaveFileFILETest_282, SavesParsedDocumentProducesNonEmptyOutput_282) {
    const char* xml = "<root><child>text</child></root>";
    ASSERT_EQ(doc.Parse(xml, std::strlen(xml)), tinyxml2::XML_SUCCESS);
    ASSERT_FALSE(doc.Error());

    FILE* fp = std::tmpfile();
    if (!fp) GTEST_SKIP() << "std::tmpfile() unavailable in this environment.";

    const tinyxml2::XMLError err = doc.SaveFile(fp, /*compact=*/false);
    EXPECT_EQ(err, tinyxml2::XML_SUCCESS);

    const std::string out = ReadAllFromFile(fp);
    std::fclose(fp);

    EXPECT_FALSE(out.empty());
    EXPECT_NE(out.find("<root"), std::string::npos);
    EXPECT_NE(out.find("</root>"), std::string::npos);
    EXPECT_NE(out.find("<child"), std::string::npos);
    EXPECT_NE(out.find("</child>"), std::string::npos);
}

TEST_F(XMLDocumentSaveFileFILETest_282, ClearsPreviousErrorAndReturnsSuccess_282) {
    // Put the document into an error state via a clearly invalid XML.
    const char* badXml = "<root><unclosed></root>";
    EXPECT_NE(doc.Parse(badXml, std::strlen(badXml)), tinyxml2::XML_SUCCESS);
    EXPECT_TRUE(doc.Error());
    EXPECT_NE(doc.ErrorID(), tinyxml2::XML_SUCCESS);

    FILE* fp = std::tmpfile();
    if (!fp) GTEST_SKIP() << "std::tmpfile() unavailable in this environment.";

    // SaveFile() is specified (by the provided implementation) to call ClearError() first.
    const tinyxml2::XMLError err = doc.SaveFile(fp, /*compact=*/true);
    EXPECT_EQ(err, tinyxml2::XML_SUCCESS);
    EXPECT_FALSE(doc.Error());
    EXPECT_EQ(doc.ErrorID(), tinyxml2::XML_SUCCESS);

    const std::string out = ReadAllFromFile(fp);
    std::fclose(fp);

    // We don't assume specific formatting; just that something printable is produced.
    EXPECT_FALSE(out.empty());
}

TEST_F(XMLDocumentSaveFileFILETest_282, WorksForCompactAndNonCompactModes_282) {
    const char* xml = "<root><a>1</a><b>2</b></root>";
    ASSERT_EQ(doc.Parse(xml, std::strlen(xml)), tinyxml2::XML_SUCCESS);

    FILE* fpCompact = std::tmpfile();
    FILE* fpPretty = std::tmpfile();
    if (!fpCompact || !fpPretty) {
        if (fpCompact) std::fclose(fpCompact);
        if (fpPretty) std::fclose(fpPretty);
        GTEST_SKIP() << "std::tmpfile() unavailable in this environment.";
    }

    EXPECT_EQ(doc.SaveFile(fpCompact, /*compact=*/true), tinyxml2::XML_SUCCESS);
    EXPECT_EQ(doc.SaveFile(fpPretty, /*compact=*/false), tinyxml2::XML_SUCCESS);

    const std::string outCompact = ReadAllFromFile(fpCompact);
    const std::string outPretty = ReadAllFromFile(fpPretty);

    std::fclose(fpCompact);
    std::fclose(fpPretty);

    EXPECT_FALSE(outCompact.empty());
    EXPECT_FALSE(outPretty.empty());

    // Both should contain the same essential elements/tags.
    EXPECT_NE(outCompact.find("<root"), std::string::npos);
    EXPECT_NE(outPretty.find("<root"), std::string::npos);
    EXPECT_NE(outCompact.find("<a"), std::string::npos);
    EXPECT_NE(outPretty.find("<a"), std::string::npos);
    EXPECT_NE(outCompact.find("<b"), std::string::npos);
    EXPECT_NE(outPretty.find("<b"), std::string::npos);
}

TEST_F(XMLDocumentSaveFileFILETest_282, DoesNotCloseFilePointer_282) {
    const char* xml = "<root/>";
    ASSERT_EQ(doc.Parse(xml, std::strlen(xml)), tinyxml2::XML_SUCCESS);

    FILE* fp = std::tmpfile();
    if (!fp) GTEST_SKIP() << "std::tmpfile() unavailable in this environment.";

    ASSERT_EQ(doc.SaveFile(fp, /*compact=*/true), tinyxml2::XML_SUCCESS);

    // If SaveFile closed fp internally, the following write would typically fail.
    const char extra[] = "\n<!--extra-->\n";
    const int written = std::fputs(extra, fp);
    EXPECT_NE(written, EOF);

    const std::string out = ReadAllFromFile(fp);
    std::fclose(fp);

    EXPECT_NE(out.find("<root"), std::string::npos);
    EXPECT_NE(out.find("extra"), std::string::npos);
}
