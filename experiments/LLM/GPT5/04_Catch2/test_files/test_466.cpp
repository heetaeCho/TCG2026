// XmlEncode_encodeTo_tests_466.cpp
#include <gtest/gtest.h>
#include <sstream>
#include <string>

// Headers under test (paths based on prompt)
#include "catch2/internal/catch_xmlwriter.hpp"
#include "catch2/internal/catch_stringref.hpp"

using Catch::XmlEncode;
using Catch::StringRef;

// The enum appears in the XmlEncode scope per provided interface.
using ForWhat = Catch::XmlEncode::ForWhat;
constexpr ForWhat ForTextNodes = Catch::XmlEncode::ForTextNodes;
constexpr ForWhat ForAttributes = Catch::XmlEncode::ForAttributes;

class XmlEncodeTest_466 : public ::testing::Test {
protected:
    static std::string encodeToString(const std::string& in, ForWhat forWhat) {
        std::ostringstream os;
        // Use the public streaming interface (which delegates to encodeTo)
        os << XmlEncode(StringRef(in), forWhat);
        return os.str();
    }
};

// Normal text remains unchanged for text nodes
TEST_F(XmlEncodeTest_466, PlainAscii_NoEscaping_ForTextNodes_466) {
    const std::string input = "abcXYZ012 -_=+/";
    const auto out = encodeToString(input, ForTextNodes);
    EXPECT_EQ(out, input);
}

// '<' and '&' are always escaped
TEST_F(XmlEncodeTest_466, Escapes_LessThan_And_Ampersand_466) {
    const std::string input = "< &";
    const auto out = encodeToString(input, ForTextNodes);
    EXPECT_EQ(out, "&lt; &amp;");
}

// '"' is escaped only for attributes; left as-is for text nodes
TEST_F(XmlEncodeTest_466, Quote_Escaped_Only_ForAttributes_466) {
    const std::string input = "\"hello\"";
    const auto outAttr = encodeToString(input, ForAttributes);
    const auto outText = encodeToString(input, ForTextNodes);

    EXPECT_EQ(outAttr, "&quot;hello&quot;");
    EXPECT_EQ(outText, "\"hello\"");
}

// '>' is escaped when it directly follows "]]" (i.e., "]]>")
TEST_F(XmlEncodeTest_466, GreaterThan_Escaped_After_CDATA_Close_Sequence_466) {
    const std::string input = "a]]>b";
    const auto out = encodeToString(input, ForTextNodes);
    EXPECT_EQ(out, "a]]&gt;b");
}

// Otherwise '>' is not escaped
TEST_F(XmlEncodeTest_466, GreaterThan_NotEscaped_Otherwise_466) {
    const std::string input = "a>b";
    const auto out = encodeToString(input, ForTextNodes);
    EXPECT_EQ(out, "a>b");
}

// Boundary: when the string is exactly "]]>", based on the provided interface,
// the '>' at index 2 is not escaped by the implementation's rule.
TEST_F(XmlEncodeTest_466, Boundary_Exact_CDATA_Close_Sequence_NotEscaped_466) {
    const std::string input = "]]>";
    const auto out = encodeToString(input, ForTextNodes);
    EXPECT_EQ(out, "]]>");
}

// Valid UTF-8 (non-ASCII) bytes are preserved
TEST_F(XmlEncodeTest_466, ValidUtf8_Preserved_466) {
    // Use a simple non-ASCII string (e.g., pi symbol and a Hangul char)
    const std::string input = u8"π 한";
    const auto out = encodeToString(input, ForTextNodes);
    EXPECT_EQ(out, input);
}
