// File: convert_into_string_test_257.cpp

#include <gtest/gtest.h>
#include <string>

// Bring in StringRef. (Path based on the prompt; adjust include path as needed.)
#include "catch2/internal/catch_stringref.hpp"

// Forward declaration of the function under test (it is defined in a .cpp).
namespace Catch { namespace Detail {
    std::string convertIntoString(Catch::StringRef string, bool escapeInvisibles);
} }

using Catch::StringRef;
using Catch::Detail::convertIntoString;

//
// Normal operation
//

TEST(ConvertIntoStringTest_257, NoEscape_WrapsWithoutAltering_257) {
    // Contains visible + invisible characters; when not escaping, they must remain as-is.
    const std::string input = "abc\t\n";
    const std::string expected = "\"abc\t\n\"";

    const auto out = convertIntoString(StringRef(input), /*escapeInvisibles=*/false);
    EXPECT_EQ(out, expected);
}

TEST(ConvertIntoStringTest_257, EscapeOn_EscapesCRLFTabFormFeed_257) {
    // Mix of \r, \n, \t, \f should be replaced by their escape sequences.
    const std::string input = "A\r\n\t\fB";
    const std::string expected = "\"A\\r\\n\\t\\fB\"";

    const auto out = convertIntoString(StringRef(input), /*escapeInvisibles=*/true);
    EXPECT_EQ(out, expected);
}

//
// Boundary conditions
//

TEST(ConvertIntoStringTest_257, EmptyString_NoEscape_ReturnsTwoQuotes_257) {
    const std::string input = "";
    const std::string expected = "\"\"";

    const auto out = convertIntoString(StringRef(input), /*escapeInvisibles=*/false);
    EXPECT_EQ(out, expected);
}

TEST(ConvertIntoStringTest_257, EmptyString_EscapeOn_ReturnsTwoQuotes_257) {
    const std::string input = "";
    const std::string expected = "\"\"";

    const auto out = convertIntoString(StringRef(input), /*escapeInvisibles=*/true);
    EXPECT_EQ(out, expected);
}

TEST(ConvertIntoStringTest_257, EscapeOn_NoInvisibles_LeavesContentUnchangedExceptQuotes_257) {
    const std::string input = "Hello World!";
    const std::string expected = "\"Hello World!\"";

    const auto outEsc = convertIntoString(StringRef(input), /*escapeInvisibles=*/true);
    EXPECT_EQ(outEsc, expected);

    // For strings without invisibles, escapeOn and escapeOff should match.
    const auto outNoEsc = convertIntoString(StringRef(input), /*escapeInvisibles=*/false);
    EXPECT_EQ(outEsc, outNoEsc);
}

//
// Edge/exceptional-ish visibility: ensure unhandled characters are preserved
//

TEST(ConvertIntoStringTest_257, EscapeOn_DoesNotEscapeBackslashOrQuote_257) {
    // Function does not specify escaping of backslashes or quotes: they should be preserved.
    const std::string input = R"(path\to\file "name")";
    const std::string expected = "\"" + input + "\"";

    const auto out = convertIntoString(StringRef(input), /*escapeInvisibles=*/true);
    EXPECT_EQ(out, expected);
}

//
// Verification for specific control char mapping
//

TEST(ConvertIntoStringTest_257, EscapeOn_FormFeedGetsMappedToBackslashF_257) {
    const std::string input = "\f";
    const std::string expected = "\"\\f\"";

    const auto out = convertIntoString(StringRef(input), /*escapeInvisibles=*/true);
    EXPECT_EQ(out, expected);
}

//
// Construction coverage: StringRef from std::string vs. const char*
//

TEST(ConvertIntoStringTest_257, AcceptsStringRefConstructedFromStdString_257) {
    const std::string backing = "xyz";
    const std::string expected = "\"xyz\"";

    // Construct StringRef from std::string
    StringRef refFromStd(backing);
    const auto out = convertIntoString(refFromStd, /*escapeInvisibles=*/false);
    EXPECT_EQ(out, expected);
}

TEST(ConvertIntoStringTest_257, AcceptsStringRefConstructedFromCString_257) {
    const char* cstr = "xyz";
    const std::string expected = "\"xyz\"";

    // Construct StringRef from const char*
    StringRef refFromCStr(cstr);
    const auto out = convertIntoString(refFromCStr, /*escapeInvisibles=*/false);
    EXPECT_EQ(out, expected);
}
