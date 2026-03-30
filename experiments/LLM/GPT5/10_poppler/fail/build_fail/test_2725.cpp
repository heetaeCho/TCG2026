// printLine_test_2725.cc
#include <gtest/gtest.h>

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include <vector>

// pdftotext.cc likely defines a main(); avoid ODR conflict by renaming it in this TU.
#define main pdftotext_main_for_test_2725
// Include the implementation file so we can call the internal-linkage (static) function printLine().
#include "./TestProjects/poppler/utils/pdftotext.cc"
#undef main

#include "./TestProjects/poppler/poppler/TextOutputDev.h"

// ---------------------------
// Helpers
// ---------------------------
namespace {

std::string ReadAllFromFILE(FILE *f)
{
    EXPECT_NE(f, nullptr);
    std::string out;

    std::fflush(f);
    std::rewind(f);

    char buf[4096];
    while (true) {
        size_t n = std::fread(buf, 1, sizeof(buf), f);
        if (n > 0) {
            out.append(buf, buf + n);
        }
        if (n < sizeof(buf)) {
            break;
        }
    }
    return out;
}

struct TmpFile
{
    FILE *f{nullptr};
    TmpFile() { f = std::tmpfile(); }
    ~TmpFile()
    {
        if (f) {
            std::fclose(f);
        }
    }
};

} // namespace

// ---------------------------
// Tests
// ---------------------------
class PrintLineTest_2725 : public ::testing::Test
{
};

// Boundary: a TextLine with no words should still print a <line ...> wrapper and closing tag.
TEST_F(PrintLineTest_2725, EmptyLinePrintsLineWrapper_2725)
{
    // Create an "empty" line (no words).
    // TextLine ctor signature: TextLine(TextBlock* blkA, int rotA, double baseA)
    TextLine line(/*blkA=*/nullptr, /*rotA=*/0, /*baseA=*/0.0);

    TmpFile tf;
    ASSERT_NE(tf.f, nullptr);

    printLine(tf.f, &line);

    const std::string s = ReadAllFromFILE(tf.f);

    // With no words, the function prints just the <line ...> open + close, and no <word>.
    EXPECT_NE(s.find(" <line xMin=\""), std::string::npos);
    EXPECT_NE(s.find("</line>"), std::string::npos);
    EXPECT_EQ(s.find("<word"), std::string::npos);

    // For an empty line, x/y mins/maxs are expected to remain at their initial values (0.000000 in %f).
    EXPECT_NE(s.find(" <line xMin=\"0.000000\" yMin=\"0.000000\" xMax=\"0.000000\" yMax=\"0.000000\">"),
              std::string::npos);
}

// Normal-ish: a line with a single (empty) TextWord should output one <word ...> element and a <line ...>.
TEST_F(PrintLineTest_2725, SingleEmptyWordPrintsSingleWordElement_2725)
{
    TextLine line(/*blkA=*/nullptr, /*rotA=*/0, /*baseA=*/0.0);

    // TextWord ctor signature: TextWord(const GfxState* state, int rotA, double fontSize)
    // We pass nullptr state as this is a black-box test and we only observe output text.
    auto *word = new TextWord(/*state=*/nullptr, /*rotA=*/0, /*fontSize=*/10.0);
    line.addWord(word);

    TmpFile tf;
    ASSERT_NE(tf.f, nullptr);

    printLine(tf.f, &line);

    const std::string s = ReadAllFromFILE(tf.f);

    // Expect exactly one <word ...> and the wrapper <line ...>.
    const auto posWord = s.find(" <word xMin=\"");
    ASSERT_NE(posWord, std::string::npos);
    EXPECT_EQ(s.find(" <word xMin=\"", posWord + 1), std::string::npos);

    EXPECT_NE(s.find(" <line xMin=\""), std::string::npos);
    EXPECT_NE(s.find(" </line>\n"), std::string::npos);

    // The word element includes bbox attributes and closing tag.
    EXPECT_NE(s.find("\">"), std::string::npos);
    EXPECT_NE(s.find("</word>\n"), std::string::npos);

    // Cleanup: TextLine destructor typically owns words, but we avoid relying on that;
    // this explicit delete is safe only if ownership is NOT transferred.
    // To keep the test robust in either ownership model, don't delete here.
    // (If TextLine owns words, deleting here would double-free; if it doesn't, leaking is acceptable in tests.)
}

// Boundary: multiple words should output multiple <word> entries (order preserved by traversal).
TEST_F(PrintLineTest_2725, MultipleEmptyWordsPrintMultipleWordElements_2725)
{
    TextLine line(/*blkA=*/nullptr, /*rotA=*/0, /*baseA=*/0.0);

    line.addWord(new TextWord(/*state=*/nullptr, /*rotA=*/0, /*fontSize=*/8.0));
    line.addWord(new TextWord(/*state=*/nullptr, /*rotA=*/0, /*fontSize=*/9.0));
    line.addWord(new TextWord(/*state=*/nullptr, /*rotA=*/0, /*fontSize=*/10.0));

    TmpFile tf;
    ASSERT_NE(tf.f, nullptr);

    printLine(tf.f, &line);

    const std::string s = ReadAllFromFILE(tf.f);

    // Count occurrences of "<word".
    size_t count = 0;
    size_t pos = 0;
    while ((pos = s.find("<word", pos)) != std::string::npos) {
        ++count;
        pos += 5;
    }
    EXPECT_EQ(count, 3u);

    // Still has a single <line ...> wrapper.
    const auto posLine = s.find("<line");
    ASSERT_NE(posLine, std::string::npos);
    EXPECT_EQ(s.find("<line", posLine + 1), std::string::npos);
}

// Output formatting boundary: ensure the <word> attributes are printed with fixed + 6 decimals.
// (We don’t assert specific bbox values, only the formatting style that is observable.)
TEST_F(PrintLineTest_2725, WordBBoxUsesSixDecimalFixedFormatting_2725)
{
    TextLine line(/*blkA=*/nullptr, /*rotA=*/0, /*baseA=*/0.0);
    line.addWord(new TextWord(/*state=*/nullptr, /*rotA=*/0, /*fontSize=*/10.0));

    TmpFile tf;
    ASSERT_NE(tf.f, nullptr);

    printLine(tf.f, &line);

    const std::string s = ReadAllFromFILE(tf.f);

    // Look for patterns like xMin="0.000000" (6 digits after decimal).
    // We check that each bbox attribute appears and has a decimal point followed by 6 digits.
    auto hasSixDecimals = [&](const char *attr) -> bool {
        const std::string needle = std::string(attr) + "=\"";
        const auto p = s.find(needle);
        if (p == std::string::npos) return false;
        const auto q = s.find('"', p + needle.size());
        if (q == std::string::npos) return false;
        const std::string val = s.substr(p + needle.size(), q - (p + needle.size()));
        const auto dot = val.find('.');
        if (dot == std::string::npos) return false;
        if (val.size() < dot + 1 + 6) return false;
        // ensure at least 6 digits after the dot
        for (size_t i = dot + 1; i < dot + 1 + 6; ++i) {
            if (i >= val.size() || val[i] < '0' || val[i] > '9') return false;
        }
        return true;
    };

    EXPECT_TRUE(hasSixDecimals("xMin"));
    EXPECT_TRUE(hasSixDecimals("yMin"));
    EXPECT_TRUE(hasSixDecimals("xMax"));
    EXPECT_TRUE(hasSixDecimals("yMax"));
}