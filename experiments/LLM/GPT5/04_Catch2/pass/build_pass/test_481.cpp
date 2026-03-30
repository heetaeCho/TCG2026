// tests/xmlwriter_writeStylesheetRef_tests_481.cpp
#include <gtest/gtest.h>
#include <sstream>
#include <string>

// Use the provided headers from your codebase
#include "Catch2/src/catch2/internal/catch_xmlwriter.hpp"
#include "Catch2/src/catch2/internal/catch_stringref.hpp"

using namespace Catch;

namespace {

class XmlWriterStylesheetTest_481 : public ::testing::Test {
protected:
    std::ostringstream os;
    XmlWriter writer{os};
};

} // namespace

// [Normal operation] Writes the exact PI with a standard URL + newline.
TEST_F(XmlWriterStylesheetTest_481, WritesExpectedPIAndNewline_481) {
    writer.writeStylesheetRef(StringRef("style.xsl"));

    const std::string expected =
        "<?xml-stylesheet type=\"text/xsl\" href=\"style.xsl\"?>\n";
    EXPECT_EQ(os.str(), expected);
}

// [Boundary] Accepts empty URL and still forms a valid PI with trailing newline.
TEST_F(XmlWriterStylesheetTest_481, AllowsEmptyUrl_481) {
    writer.writeStylesheetRef(StringRef(""));

    const std::string expected =
        "<?xml-stylesheet type=\"text/xsl\" href=\"\"?>\n";
    EXPECT_EQ(os.str(), expected);
}

// [Observable interaction with ostream] Appends to existing stream content.
TEST_F(XmlWriterStylesheetTest_481, AppendsToExistingStreamContent_481) {
    os << "prefix\n";

    writer.writeStylesheetRef(StringRef("theme.xsl"));

    const std::string expected =
        std::string("prefix\n") +
        "<?xml-stylesheet type=\"text/xsl\" href=\"theme.xsl\"?>\n";
    EXPECT_EQ(os.str(), expected);
}

// [Special characters passthrough] URL with query/fragment kept as-is (no escaping).
TEST_F(XmlWriterStylesheetTest_481, PreservesUrlWithSpecialChars_481) {
    const char* url = "http://example.com/a?b=1&c=2#frag";
    writer.writeStylesheetRef(StringRef(url));

    const std::string expected =
        "<?xml-stylesheet type=\"text/xsl\" href=\"http://example.com/a?b=1&c=2#frag\"?>\n";
    EXPECT_EQ(os.str(), expected);
}

// [Multiple calls] Each call ends with newline so outputs are line-separated.
TEST_F(XmlWriterStylesheetTest_481, MultipleCallsEachOnNewLine_481) {
    writer.writeStylesheetRef(StringRef("first.xsl"));
    writer.writeStylesheetRef(StringRef("second.xsl"));

    const std::string expected =
        "<?xml-stylesheet type=\"text/xsl\" href=\"first.xsl\"?>\n"
        "<?xml-stylesheet type=\"text/xsl\" href=\"second.xsl\"?>\n";
    EXPECT_EQ(os.str(), expected);
}
