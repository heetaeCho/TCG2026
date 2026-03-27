// TEST_ID: 324
// Unit tests for XMLPrinterHTML5::isVoidElement
//
// Notes:
// - We treat XMLPrinterHTML5 as a black box and only validate observable behavior
//   via the public/protected interface.
// - In some codebases, isVoidElement may be protected (as hinted in the optional
//   dependency snippet). To keep tests robust, we expose it through a small
//   derived "Testable" adapter.

#include <gtest/gtest.h>

#include <cstdio>

// Include the implementation unit to access XMLPrinterHTML5 in this test build.
// This is common for contrib-style single-file utilities that don't ship headers.
#include "TestProjects/tinyxml2/contrib/html5-printer.cpp"

namespace {

class TestableXMLPrinterHTML5_324 : public XMLPrinterHTML5 {
public:
    // Use the base constructors if available; otherwise fall back to default.
    using XMLPrinterHTML5::XMLPrinterHTML5;

    // Expose isVoidElement for testing even if it's protected in the real class.
    using XMLPrinterHTML5::isVoidElement;
};

class XMLPrinterHTML5Test_324 : public ::testing::Test {
protected:
    TestableXMLPrinterHTML5_324 printer_;
};

}  // namespace

TEST_F(XMLPrinterHTML5Test_324, RecognizesVoidElements_Lowercase_324) {
    EXPECT_TRUE(printer_.isVoidElement("br"));
    EXPECT_TRUE(printer_.isVoidElement("img"));
    EXPECT_TRUE(printer_.isVoidElement("meta"));
    EXPECT_TRUE(printer_.isVoidElement("input"));
    EXPECT_TRUE(printer_.isVoidElement("hr"));
}

TEST_F(XMLPrinterHTML5Test_324, RecognizesVoidElements_CaseInsensitive_324) {
    EXPECT_TRUE(printer_.isVoidElement("BR"));
    EXPECT_TRUE(printer_.isVoidElement("Img"));
    EXPECT_TRUE(printer_.isVoidElement("MeTa"));
    EXPECT_TRUE(printer_.isVoidElement("InPuT"));
    EXPECT_TRUE(printer_.isVoidElement("wBr"));
}

TEST_F(XMLPrinterHTML5Test_324, ReturnsFalseForNonVoidElements_324) {
    EXPECT_FALSE(printer_.isVoidElement("div"));
    EXPECT_FALSE(printer_.isVoidElement("span"));
    EXPECT_FALSE(printer_.isVoidElement("p"));
    EXPECT_FALSE(printer_.isVoidElement("script"));
    EXPECT_FALSE(printer_.isVoidElement("style"));
}

TEST_F(XMLPrinterHTML5Test_324, Boundary_EmptyStringIsNotVoid_324) {
    EXPECT_FALSE(printer_.isVoidElement(""));
}

TEST_F(XMLPrinterHTML5Test_324, Boundary_PrefixOrSuffixDoesNotMatch_324) {
    // Ensure exact-name matching behavior is observable (no partial matches).
    EXPECT_FALSE(printer_.isVoidElement("br/"));
    EXPECT_FALSE(printer_.isVoidElement(" br"));
    EXPECT_FALSE(printer_.isVoidElement("br "));
    EXPECT_FALSE(printer_.isVoidElement("img1"));
    EXPECT_FALSE(printer_.isVoidElement("meta-data"));
}

TEST_F(XMLPrinterHTML5Test_324, Boundary_SimilarButDifferentNamesAreNotVoid_324) {
    // Names close to known void elements should still be false if not exact.
    EXPECT_FALSE(printer_.isVoidElement("inputs"));
    EXPECT_FALSE(printer_.isVoidElement("images"));
    EXPECT_FALSE(printer_.isVoidElement("links"));
    EXPECT_FALSE(printer_.isVoidElement("params"));
}

TEST_F(XMLPrinterHTML5Test_324, RecognizesAllListedVoidElements_324) {
    // Validate that each listed HTML5 void element is recognized.
    // (Still black-box: we only check observable outputs for known names.)
    const char* voids[] = {
        "area",   "base",  "br",    "col",   "command", "embed", "hr",   "img",
        "input",  "keygen","link",  "meta",  "param",   "source","track","wbr",
        nullptr
    };

    for (const char** p = voids; *p != nullptr; ++p) {
        EXPECT_TRUE(printer_.isVoidElement(*p)) << "Expected void element: " << *p;
    }
}
