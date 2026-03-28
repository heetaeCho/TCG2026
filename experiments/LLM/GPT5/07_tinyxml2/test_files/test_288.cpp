// File: ./TestProjects/tinyxml2/test_xmldocument_printerror_288.cpp

#include <gtest/gtest.h>
#include <string>

#include "tinyxml2.h"

namespace {

class XMLDocumentPrintErrorTest_288 : public ::testing::Test {
protected:
    // Construct with explicit args to match the provided header signature.
    tinyxml2::XMLDocument MakeDoc() {
        return tinyxml2::XMLDocument(true, tinyxml2::PRESERVE_WHITESPACE);
    }
};

TEST_F(XMLDocumentPrintErrorTest_288, PrintsExactlyErrorStrPlusNewline_288) {
    auto doc = MakeDoc();

    const char* before = doc.ErrorStr();
    ASSERT_NE(before, nullptr);

    testing::internal::CaptureStdout();
    doc.PrintError();
    const std::string out = testing::internal::GetCapturedStdout();

    EXPECT_EQ(out, std::string(before) + "\n");
}

TEST_F(XMLDocumentPrintErrorTest_288, PrintsCurrentErrorStrAfterParseFailure_288) {
    auto doc = MakeDoc();

    // Intentionally malformed XML to trigger an observable error state.
    const char* badXml = "<root>"; // missing closing tag
    const tinyxml2::XMLError err = doc.Parse(badXml, std::strlen(badXml));

    // We don't assume which error code, only that it isn't success for malformed input.
    EXPECT_NE(err, tinyxml2::XML_SUCCESS);

    const char* errStr = doc.ErrorStr();
    ASSERT_NE(errStr, nullptr);

    testing::internal::CaptureStdout();
    doc.PrintError();
    const std::string out = testing::internal::GetCapturedStdout();

    EXPECT_EQ(out, std::string(errStr) + "\n");
}

TEST_F(XMLDocumentPrintErrorTest_288, PrintErrorDoesNotChangeErrorStr_288) {
    auto doc = MakeDoc();

    // Trigger an error so ErrorStr is likely meaningful, but we still don't assume contents.
    const char* badXml = "<root>";
    (void)doc.Parse(badXml, std::strlen(badXml));

    const std::string before = doc.ErrorStr() ? doc.ErrorStr() : "";

    testing::internal::CaptureStdout();
    doc.PrintError();
    (void)testing::internal::GetCapturedStdout();

    const std::string after = doc.ErrorStr() ? doc.ErrorStr() : "";
    EXPECT_EQ(after, before);
}

TEST_F(XMLDocumentPrintErrorTest_288, PrintErrorDoesNotChangeErrorIdOrErrorFlag_288) {
    auto doc = MakeDoc();

    const char* badXml = "<root>";
    (void)doc.Parse(badXml, std::strlen(badXml));

    const bool beforeErrorFlag = doc.Error();
    const tinyxml2::XMLError beforeId = doc.ErrorID();

    testing::internal::CaptureStdout();
    doc.PrintError();
    (void)testing::internal::GetCapturedStdout();

    EXPECT_EQ(doc.Error(), beforeErrorFlag);
    EXPECT_EQ(doc.ErrorID(), beforeId);
}

TEST_F(XMLDocumentPrintErrorTest_288, WhenErrorStrIsEmptyPrintsJustNewline_288) {
    auto doc = MakeDoc();

    const char* errStr = doc.ErrorStr();
    ASSERT_NE(errStr, nullptr);

    // Only assert the strict output format based on the observable current ErrorStr.
    // If ErrorStr() happens to be empty on a new doc, this becomes "\n".
    testing::internal::CaptureStdout();
    doc.PrintError();
    const std::string out = testing::internal::GetCapturedStdout();

    EXPECT_EQ(out, std::string(errStr) + "\n");
    // And specifically verify the "empty => newline" behavior if the library returns empty here.
    if (std::string(errStr).empty()) {
        EXPECT_EQ(out, "\n");
    }
}

} // namespace
