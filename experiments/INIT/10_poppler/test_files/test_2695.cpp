// set_ps_paper_size_test_2695.cc
#include <gtest/gtest.h>

#include <cstring>

// pdftocairo.cc is a standalone tool and typically defines its own main().
// To include it in this test translation unit (so we can call the internal
// static helper), rename its main symbol to avoid conflicts.
#define main pdftocairo_tool_main_2695
#include "./TestProjects/poppler/utils/pdftocairo.cc"
#undef main

class SetPSPaperSizeTest_2695 : public ::testing::Test {};

TEST_F(SetPSPaperSizeTest_2695, MatchSetsBothToMinusOne_2695)
{
    int w = 123;
    int h = 456;

    char size[] = "match";
    const bool ok = setPSPaperSize(size, w, h);

    EXPECT_TRUE(ok);
    EXPECT_EQ(w, -1);
    EXPECT_EQ(h, -1);
}

TEST_F(SetPSPaperSizeTest_2695, LetterSetsExpectedPoints_2695)
{
    int w = 0;
    int h = 0;

    char size[] = "letter";
    const bool ok = setPSPaperSize(size, w, h);

    EXPECT_TRUE(ok);
    EXPECT_EQ(w, 612);
    EXPECT_EQ(h, 792);
}

TEST_F(SetPSPaperSizeTest_2695, LegalSetsExpectedPoints_2695)
{
    int w = 0;
    int h = 0;

    char size[] = "legal";
    const bool ok = setPSPaperSize(size, w, h);

    EXPECT_TRUE(ok);
    EXPECT_EQ(w, 612);
    EXPECT_EQ(h, 1008);
}

TEST_F(SetPSPaperSizeTest_2695, A4SetsExpectedPoints_2695)
{
    int w = 0;
    int h = 0;

    char size[] = "A4";
    const bool ok = setPSPaperSize(size, w, h);

    EXPECT_TRUE(ok);
    EXPECT_EQ(w, 595);
    EXPECT_EQ(h, 842);
}

TEST_F(SetPSPaperSizeTest_2695, A3SetsExpectedPoints_2695)
{
    int w = 0;
    int h = 0;

    char size[] = "A3";
    const bool ok = setPSPaperSize(size, w, h);

    EXPECT_TRUE(ok);
    EXPECT_EQ(w, 842);
    EXPECT_EQ(h, 1190);
}

TEST_F(SetPSPaperSizeTest_2695, InvalidSizeReturnsFalseAndDoesNotChangeOutputs_2695)
{
    int w = 777;
    int h = 888;

    char size[] = "tabloid"; // not supported by the interface snippet
    const bool ok = setPSPaperSize(size, w, h);

    EXPECT_FALSE(ok);
    EXPECT_EQ(w, 777);
    EXPECT_EQ(h, 888);
}

TEST_F(SetPSPaperSizeTest_2695, EmptyStringReturnsFalseAndDoesNotChangeOutputs_2695)
{
    int w = -42;
    int h = 9999;

    char size[] = "";
    const bool ok = setPSPaperSize(size, w, h);

    EXPECT_FALSE(ok);
    EXPECT_EQ(w, -42);
    EXPECT_EQ(h, 9999);
}

TEST_F(SetPSPaperSizeTest_2695, CaseSensitivityAffectsMatching_2695)
{
    int w = 11;
    int h = 22;

    char size[] = "a4"; // different case than "A4"
    const bool ok = setPSPaperSize(size, w, h);

    EXPECT_FALSE(ok);
    EXPECT_EQ(w, 11);
    EXPECT_EQ(h, 22);
}

TEST_F(SetPSPaperSizeTest_2695, RepeatedCallsOverwritePreviousValues_2695)
{
    int w = 1;
    int h = 2;

    {
        char size1[] = "letter";
        ASSERT_TRUE(setPSPaperSize(size1, w, h));
        EXPECT_EQ(w, 612);
        EXPECT_EQ(h, 792);
    }

    {
        char size2[] = "A4";
        ASSERT_TRUE(setPSPaperSize(size2, w, h));
        EXPECT_EQ(w, 595);
        EXPECT_EQ(h, 842);
    }

    {
        char size3[] = "match";
        ASSERT_TRUE(setPSPaperSize(size3, w, h));
        EXPECT_EQ(w, -1);
        EXPECT_EQ(h, -1);
    }
}