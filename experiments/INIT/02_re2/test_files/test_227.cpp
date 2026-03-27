// AppendLiteral_test_227.cc
#include <gtest/gtest.h>
#include <string>

// Pull the function into this translation unit so we can call the internal-linkage function.
#include "TestProjects/re2/re2/tostring.cc"

using re2::AppendLiteral;

// A small helper to run AppendLiteral on a sequence of runes and return the built string.
static std::string BuildWith(const std::vector<Rune>& runes, bool foldcase) {
    std::string out;
    for (Rune r : runes) {
        AppendLiteral(&out, r, foldcase);
    }
    return out;
}

// --- Normal operation: escaping regex metacharacters (ASCII) ---
TEST(AppendLiteralTest_227, EscapesRegexMetacharacters_227) {
    const char* metas = "(){}[]*+?|.^$\\";
    std::string expected;

    std::vector<Rune> runes;
    for (const char* p = metas; *p; ++p) {
        runes.push_back(static_cast<unsigned char>(*p));
        expected.push_back('\\');
        expected.push_back(*p);
    }

    // foldcase=false
    EXPECT_EQ(BuildWith(runes, /*foldcase=*/false), expected);
}

TEST(AppendLiteralTest_227, EscapesRegexMetacharactersEvenWhenFoldcaseTrue_227) {
    const char* metas = "(){}[]*+?|.^$\\";
    std::string expected;

    std::vector<Rune> runes;
    for (const char* p = metas; *p; ++p) {
        runes.push_back(static_cast<unsigned char>(*p));
        expected.push_back('\\');
        expected.push_back(*p);
    }

    // foldcase=true should NOT change escaping behavior; escape wins.
    EXPECT_EQ(BuildWith(runes, /*foldcase=*/true), expected);
}

// --- Normal operation: foldcase for ASCII lowercase letters ---
TEST(AppendLiteralTest_227, FoldcaseWrapsLowercaseInBracketPair_227) {
    // Pick representative lowercase letters, including boundaries.
    std::vector<Rune> runes = {'a', 'm', 'z'};
    std::string expected;
    expected += "[Aa]";
    expected += "[Mm]";
    expected += "[Zz]";

    EXPECT_EQ(BuildWith(runes, /*foldcase=*/true), expected);
}

// --- Boundary conditions around lowercase range ---
TEST(AppendLiteralTest_227, FoldcaseBoundaryAtAandZ_227) {
    // Explicitly test 'a' and 'z'
    EXPECT_EQ(BuildWith({'a'}, /*foldcase=*/true), std::string("[Aa]"));
    EXPECT_EQ(BuildWith({'z'}, /*foldcase=*/true), std::string("[Zz]"));
}

// --- Special individual characters: backslash and dot ---
TEST(AppendLiteralTest_227, EscapesBackslashAndDotIndividually_227) {
    // Backslash
    EXPECT_EQ(BuildWith({'\\'}, /*foldcase=*/false), std::string("\\\\"));
    // Dot
    EXPECT_EQ(BuildWith({'.'}, /*foldcase=*/false), std::string("\\."));
}

// --- Precedence: escaping happens before foldcase ---
TEST(AppendLiteralTest_227, EscapePrecedenceOverFoldcase_227) {
    // '(' is a metacharacter; even with foldcase=true it must be escaped, not bracket-folded.
    EXPECT_EQ(BuildWith({'('}, /*foldcase=*/true), std::string("\\("));
}
