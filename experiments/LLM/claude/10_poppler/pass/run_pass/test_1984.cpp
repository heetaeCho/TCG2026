#include <gtest/gtest.h>
#include <cstring>
#include "GooString.h"

// We need to include or declare the function under test.
// Since replaceSuffix is a static function in GlobalParamsWin.cc,
// we need to either include it or re-declare it for testing purposes.
// We'll include a forward declaration and link against the object file.

// For testing a static (file-scope) function, we include the source directly
// or use a test-specific approach. Here we'll define it in the test file
// by including the relevant portion. Since the function is static, we
// replicate its signature for linkage. In practice, you'd make it accessible
// for testing (e.g., via a header or removing static for test builds).

// Replicating the function here since it's static and not exposed via header:
static GooString *replaceSuffix(GooString *path, const char *suffixA, const char *suffixB)
{
    int suffLenA = strlen(suffixA);
    int suffLenB = strlen(suffixB);
    int baseLenA = path->size() - suffLenA;
    int baseLenB = path->size() - suffLenB;
    if (!strcasecmp(path->c_str() + baseLenA, suffixA)) {
        path->erase(baseLenA, suffLenA);
        path->append(suffixB);
    } else if (!strcasecmp(path->c_str() + baseLenB, suffixB)) {
        path->erase(baseLenB, suffLenB);
        path->append(suffixA);
    }
    return path;
}

class ReplaceSuffixTest_1984 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test: When path ends with suffixA, it should be replaced with suffixB
TEST_F(ReplaceSuffixTest_1984, ReplacesSuffixAWithSuffixB_1984)
{
    GooString path("document.txt");
    GooString *result = replaceSuffix(&path, ".txt", ".pdf");
    EXPECT_STREQ(result->c_str(), "document.pdf");
}

// Test: When path ends with suffixB, it should be replaced with suffixA
TEST_F(ReplaceSuffixTest_1984, ReplacesSuffixBWithSuffixA_1984)
{
    GooString path("document.pdf");
    GooString *result = replaceSuffix(&path, ".txt", ".pdf");
    EXPECT_STREQ(result->c_str(), "document.txt");
}

// Test: Case-insensitive matching of suffixA
TEST_F(ReplaceSuffixTest_1984, CaseInsensitiveMatchSuffixA_1984)
{
    GooString path("document.TXT");
    GooString *result = replaceSuffix(&path, ".txt", ".pdf");
    EXPECT_STREQ(result->c_str(), "document.pdf");
}

// Test: Case-insensitive matching of suffixB
TEST_F(ReplaceSuffixTest_1984, CaseInsensitiveMatchSuffixB_1984)
{
    GooString path("document.PDF");
    GooString *result = replaceSuffix(&path, ".txt", ".pdf");
    EXPECT_STREQ(result->c_str(), "document.txt");
}

// Test: When path ends with neither suffixA nor suffixB, path should remain unchanged
TEST_F(ReplaceSuffixTest_1984, NoMatchLeavesPathUnchanged_1984)
{
    GooString path("document.doc");
    GooString *result = replaceSuffix(&path, ".txt", ".pdf");
    EXPECT_STREQ(result->c_str(), "document.doc");
}

// Test: Returns the same pointer that was passed in
TEST_F(ReplaceSuffixTest_1984, ReturnsSamePointer_1984)
{
    GooString path("file.txt");
    GooString *result = replaceSuffix(&path, ".txt", ".pdf");
    EXPECT_EQ(result, &path);
}

// Test: suffixA replaces with longer suffixB
TEST_F(ReplaceSuffixTest_1984, SuffixAReplacedWithLongerSuffixB_1984)
{
    GooString path("file.a");
    GooString *result = replaceSuffix(&path, ".a", ".longext");
    EXPECT_STREQ(result->c_str(), "file.longext");
}

// Test: suffixA replaces with shorter suffixB
TEST_F(ReplaceSuffixTest_1984, SuffixAReplacedWithShorterSuffixB_1984)
{
    GooString path("file.longext");
    GooString *result = replaceSuffix(&path, ".longext", ".b");
    EXPECT_STREQ(result->c_str(), "file.b");
}

// Test: suffixB replaces with longer suffixA
TEST_F(ReplaceSuffixTest_1984, SuffixBReplacedWithLongerSuffixA_1984)
{
    GooString path("file.b");
    GooString *result = replaceSuffix(&path, ".longext", ".b");
    EXPECT_STREQ(result->c_str(), "file.longext");
}

// Test: Same suffix for both A and B, path should get suffix replaced (effectively same)
TEST_F(ReplaceSuffixTest_1984, SameSuffixForBoth_1984)
{
    GooString path("file.txt");
    GooString *result = replaceSuffix(&path, ".txt", ".txt");
    EXPECT_STREQ(result->c_str(), "file.txt");
}

// Test: Path that is exactly suffixA
TEST_F(ReplaceSuffixTest_1984, PathIsExactlySuffixA_1984)
{
    GooString path(".txt");
    GooString *result = replaceSuffix(&path, ".txt", ".pdf");
    EXPECT_STREQ(result->c_str(), ".pdf");
}

// Test: Path that is exactly suffixB
TEST_F(ReplaceSuffixTest_1984, PathIsExactlySuffixB_1984)
{
    GooString path(".pdf");
    GooString *result = replaceSuffix(&path, ".txt", ".pdf");
    EXPECT_STREQ(result->c_str(), ".txt");
}

// Test: Mixed case in the middle of the path, suffix match at end
TEST_F(ReplaceSuffixTest_1984, MixedCaseInPathBody_1984)
{
    GooString path("MyDocument.TxT");
    GooString *result = replaceSuffix(&path, ".txt", ".pdf");
    EXPECT_STREQ(result->c_str(), "MyDocument.pdf");
}

// Test: Empty suffixes - both empty strings
TEST_F(ReplaceSuffixTest_1984, EmptySuffixes_1984)
{
    GooString path("file.txt");
    GooString *result = replaceSuffix(&path, "", "");
    // Both suffixes are empty, the first branch should match (empty suffix always matches end)
    EXPECT_STREQ(result->c_str(), "file.txt");
}

// Test: Path with multiple dots, suffix at the end matches
TEST_F(ReplaceSuffixTest_1984, MultipleDotsInPath_1984)
{
    GooString path("archive.tar.gz");
    GooString *result = replaceSuffix(&path, ".gz", ".bz2");
    EXPECT_STREQ(result->c_str(), "archive.tar.bz2");
}

// Test: SuffixA is a substring of path but not at the end - no match, check suffixB
TEST_F(ReplaceSuffixTest_1984, SuffixANotAtEnd_1984)
{
    GooString path("txt_file.doc");
    GooString *result = replaceSuffix(&path, ".txt", ".pdf");
    // Neither .txt nor .pdf at end, path unchanged
    EXPECT_STREQ(result->c_str(), "txt_file.doc");
}

// Test: Path with spaces
TEST_F(ReplaceSuffixTest_1984, PathWithSpaces_1984)
{
    GooString path("my document.txt");
    GooString *result = replaceSuffix(&path, ".txt", ".pdf");
    EXPECT_STREQ(result->c_str(), "my document.pdf");
}

// Test: Priority - if path could match both (suffixA is suffix of suffixB), suffixA is checked first
TEST_F(ReplaceSuffixTest_1984, SuffixAPriorityOverSuffixB_1984)
{
    // If suffixA = ".txt" and suffixB = ".txt" they're the same, covered above
    // Test with suffixA being checked first when both could theoretically match
    GooString path("file.abc");
    GooString *result = replaceSuffix(&path, ".abc", ".abc");
    // First branch matches, replaces .abc with .abc - no change
    EXPECT_STREQ(result->c_str(), "file.abc");
}

// Test: Long path with suffix replacement
TEST_F(ReplaceSuffixTest_1984, LongPathWithSuffixReplacement_1984)
{
    GooString path("/usr/local/share/fonts/truetype/dejavu/DejaVuSans.ttf");
    GooString *result = replaceSuffix(&path, ".ttf", ".otf");
    EXPECT_STREQ(result->c_str(), "/usr/local/share/fonts/truetype/dejavu/DejaVuSans.otf");
}

// Test: Replacement from suffixB back to suffixA on the long path
TEST_F(ReplaceSuffixTest_1984, LongPathSuffixBToSuffixA_1984)
{
    GooString path("/usr/local/share/fonts/truetype/dejavu/DejaVuSans.otf");
    GooString *result = replaceSuffix(&path, ".ttf", ".otf");
    EXPECT_STREQ(result->c_str(), "/usr/local/share/fonts/truetype/dejavu/DejaVuSans.ttf");
}
