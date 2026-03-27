// File: printInfoString_test_2664.cc
#include <gtest/gtest.h>

#include <cstdio>
#include <string>

// Poppler headers (as provided / expected in the codebase)
#include "poppler/Dict.h"
#include "poppler/Object.h"
#include "poppler/UnicodeMap.h"

// ---- Test double hook for the external collaborator ----
// printInfoString() calls printTextString(s1, uMap). We provide a TU-local
// definition to observe the interaction without relying on internal behavior.
namespace {
const GooString *g_last_printTextString_s_2664 = nullptr;
const UnicodeMap *g_last_printTextString_uMap_2664 = nullptr;
int g_printTextString_calls_2664 = 0;

void ResetPrintTextStringSpy_2664()
{
    g_last_printTextString_s_2664 = nullptr;
    g_last_printTextString_uMap_2664 = nullptr;
    g_printTextString_calls_2664 = 0;
}

// Signature must match the one used by pdfinfo.cc
void printTextString(const GooString *s, const UnicodeMap *uMap)
{
    ++g_printTextString_calls_2664;
    g_last_printTextString_s_2664 = s;
    g_last_printTextString_uMap_2664 = uMap;

    // Emit a stable token to stdout so tests can validate behavior without
    // depending on GooString/unicode conversion internals.
    std::fputs("[[PRINTTEXT]]", stdout);
}
} // namespace

// Include the implementation file to access the TU-static function.
// (This is a common pattern for unit testing file-local helpers.)
#include "utils/pdfinfo.cc"

class PrintInfoStringTest_2664 : public ::testing::Test {
protected:
    void SetUp() override { ResetPrintTextStringSpy_2664(); }
};

TEST_F(PrintInfoStringTest_2664, PrintsPrefixCallsPrintTextStringAndAppendsNewline_2664)
{
    Dict infoDict(nullptr);
    infoDict.add("Title", Object(std::string("MyTitle")));

    UnicodeMap uMap("UTF-8", true, 0);

    testing::internal::CaptureStdout();
    printInfoString(&infoDict, "Title", "Title: ", &uMap);
    const std::string out = testing::internal::GetCapturedStdout();

    EXPECT_EQ(g_printTextString_calls_2664, 1);
    EXPECT_NE(g_last_printTextString_s_2664, nullptr);
    EXPECT_EQ(g_last_printTextString_uMap_2664, &uMap);

    EXPECT_EQ(out, std::string("Title: ") + "[[PRINTTEXT]]" + "\n");
}

TEST_F(PrintInfoStringTest_2664, DoesNothingWhenKeyIsMissing_2664)
{
    Dict infoDict(nullptr);
    UnicodeMap uMap("UTF-8", true, 0);

    testing::internal::CaptureStdout();
    printInfoString(&infoDict, "MissingKey", "X: ", &uMap);
    const std::string out = testing::internal::GetCapturedStdout();

    EXPECT_EQ(g_printTextString_calls_2664, 0);
    EXPECT_EQ(out, "");
}

TEST_F(PrintInfoStringTest_2664, DoesNothingWhenValueIsNotString_2664)
{
    Dict infoDict(nullptr);
    infoDict.add("Pages", Object(123)); // non-string
    UnicodeMap uMap("UTF-8", true, 0);

    testing::internal::CaptureStdout();
    printInfoString(&infoDict, "Pages", "Pages: ", &uMap);
    const std::string out = testing::internal::GetCapturedStdout();

    EXPECT_EQ(g_printTextString_calls_2664, 0);
    EXPECT_EQ(out, "");
}

TEST_F(PrintInfoStringTest_2664, HandlesEmptyPrefixText_2664)
{
    Dict infoDict(nullptr);
    infoDict.add("K", Object(std::string("V")));
    UnicodeMap uMap("UTF-8", true, 0);

    testing::internal::CaptureStdout();
    printInfoString(&infoDict, "K", "", &uMap);
    const std::string out = testing::internal::GetCapturedStdout();

    EXPECT_EQ(g_printTextString_calls_2664, 1);
    EXPECT_EQ(out, std::string("[[PRINTTEXT]]\n"));
}

TEST_F(PrintInfoStringTest_2664, HandlesEmptyKeyWhenPresent_2664)
{
    Dict infoDict(nullptr);
    infoDict.add("", Object(std::string("EmptyKeyValue")));
    UnicodeMap uMap("UTF-8", true, 0);

    testing::internal::CaptureStdout();
    printInfoString(&infoDict, "", "E: ", &uMap);
    const std::string out = testing::internal::GetCapturedStdout();

    EXPECT_EQ(g_printTextString_calls_2664, 1);
    EXPECT_EQ(out, std::string("E: [[PRINTTEXT]]\n"));
}

TEST_F(PrintInfoStringTest_2664, DeathOnNullDictPointer_2664)
{
#if GTEST_HAS_DEATH_TEST
    UnicodeMap uMap("UTF-8", true, 0);
    EXPECT_DEATH(
        {
            testing::internal::CaptureStdout();
            printInfoString(nullptr, "Any", "X: ", &uMap);
        },
        "");
#else
    GTEST_SKIP() << "Death tests are not supported in this build.";
#endif
}

TEST_F(PrintInfoStringTest_2664, DeathOnNullTextPrefixWhenStringPresent_2664)
{
#if GTEST_HAS_DEATH_TEST
    Dict infoDict(nullptr);
    infoDict.add("Title", Object(std::string("MyTitle")));
    UnicodeMap uMap("UTF-8", true, 0);

    EXPECT_DEATH(
        {
            testing::internal::CaptureStdout();
            printInfoString(&infoDict, "Title", nullptr, &uMap);
        },
        "");
#else
    GTEST_SKIP() << "Death tests are not supported in this build.";
#endif
}