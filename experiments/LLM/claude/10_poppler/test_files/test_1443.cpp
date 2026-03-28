#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <QList>
#include <QRectF>
#include <QVector>
#include <cfloat>
#include <vector>

// Forward declarations and minimal types needed
typedef unsigned int Unicode;
typedef unsigned int CharCode;

// Minimal PDFRectangle
class PDFRectangle {
public:
    double x1 = 0.;
    double y1 = 0.;
    double x2 = 0.;
    double y2 = 0.;
    constexpr PDFRectangle() = default;
    constexpr PDFRectangle(double x1A, double y1A, double x2A, double y2A)
        : x1(x1A), y1(y1A), x2(x2A), y2(y2A) {}
};

// Mock TextPage class
class TextPage {
public:
    virtual ~TextPage() = default;
    virtual bool findText(const Unicode *s, int len,
                          bool startAtTop, bool stopAtBottom,
                          bool startAtLast, bool stopAtLast,
                          bool caseSensitive, bool ignoreDiacritics,
                          bool matchAcrossLines, bool backward,
                          bool wholeWord,
                          double *xMin, double *yMin,
                          double *xMax, double *yMax,
                          PDFRectangle *continueMatch,
                          bool *ignoredHyphen) = 0;
};

class MockTextPage : public TextPage {
public:
    MOCK_METHOD(bool, findText,
                (const Unicode *s, int len,
                 bool startAtTop, bool stopAtBottom,
                 bool startAtLast, bool stopAtLast,
                 bool caseSensitive, bool ignoreDiacritics,
                 bool matchAcrossLines, bool backward,
                 bool wholeWord,
                 double *xMin, double *yMin,
                 double *xMax, double *yMax,
                 PDFRectangle *continueMatch,
                 bool *ignoredHyphen),
                (override));
};

// The class under test - extracted from the provided code
namespace Poppler {
class PageData {
public:
    inline QList<QRectF> performMultipleTextSearch(TextPage *textPage, QVector<Unicode> &u, bool sCase, bool sWords, bool sDiacritics, bool sAcrossLines)
    {
        QList<QRectF> results;
        double sLeft = 0.0, sTop = 0.0, sRight = 0.0, sBottom = 0.0;
        bool sIgnoredHyphen = false;
        PDFRectangle continueMatch;
        continueMatch.x1 = DBL_MAX;

        while (textPage->findText(u.data(), u.size(), false, true, true, false, sCase, sDiacritics, sAcrossLines, false, sWords, &sLeft, &sTop, &sRight, &sBottom, &continueMatch, &sIgnoredHyphen)) {
            QRectF result;
            result.setLeft(sLeft);
            result.setTop(sTop);
            result.setRight(sRight);
            result.setBottom(sBottom);
            results.append(result);

            if (sAcrossLines && continueMatch.x1 != DBL_MAX) {
                QRectF resultN;
                resultN.setLeft(continueMatch.x1);
                resultN.setTop(continueMatch.y1);
                resultN.setRight(continueMatch.x2);
                resultN.setBottom(continueMatch.y1);
                results.append(resultN);
                continueMatch.x1 = DBL_MAX;
            }
        }

        return results;
    }
};
}

using namespace Poppler;
using ::testing::_;
using ::testing::DoAll;
using ::testing::Return;
using ::testing::SetArgPointee;
using ::testing::Invoke;

class PageDataMultipleTextSearchTest_1443 : public ::testing::Test {
protected:
    PageData pageData;
    MockTextPage mockTextPage;
};

// Test: No matches found returns empty list
TEST_F(PageDataMultipleTextSearchTest_1443, NoMatchesReturnsEmptyList_1443)
{
    QVector<Unicode> searchText = {'h', 'e', 'l', 'l', 'o'};

    EXPECT_CALL(mockTextPage, findText(_, _, false, true, true, false, true, false, false, false, false, _, _, _, _, _, _))
        .WillOnce(Return(false));

    QList<QRectF> results = pageData.performMultipleTextSearch(&mockTextPage, searchText, true, false, false, false);

    EXPECT_TRUE(results.isEmpty());
}

// Test: Single match found returns one result
TEST_F(PageDataMultipleTextSearchTest_1443, SingleMatchReturnsOneResult_1443)
{
    QVector<Unicode> searchText = {'t', 'e', 's', 't'};

    EXPECT_CALL(mockTextPage, findText(_, _, false, true, true, false, true, false, false, false, false, _, _, _, _, _, _))
        .WillOnce(Invoke([](const Unicode *, int, bool, bool, bool, bool, bool, bool, bool, bool, bool,
                            double *xMin, double *yMin, double *xMax, double *yMax,
                            PDFRectangle *continueMatch, bool *ignoredHyphen) -> bool {
            *xMin = 10.0;
            *yMin = 20.0;
            *xMax = 100.0;
            *yMax = 40.0;
            // Keep continueMatch.x1 as DBL_MAX (no across-lines match)
            return true;
        }))
        .WillOnce(Return(false));

    QList<QRectF> results = pageData.performMultipleTextSearch(&mockTextPage, searchText, true, false, false, false);

    ASSERT_EQ(results.size(), 1);
    EXPECT_DOUBLE_EQ(results[0].left(), 10.0);
    EXPECT_DOUBLE_EQ(results[0].top(), 20.0);
    EXPECT_DOUBLE_EQ(results[0].right(), 100.0);
    EXPECT_DOUBLE_EQ(results[0].bottom(), 40.0);
}

// Test: Multiple matches found returns all results
TEST_F(PageDataMultipleTextSearchTest_1443, MultipleMatchesReturnsAllResults_1443)
{
    QVector<Unicode> searchText = {'a', 'b'};

    EXPECT_CALL(mockTextPage, findText(_, _, false, true, true, false, false, false, false, false, false, _, _, _, _, _, _))
        .WillOnce(Invoke([](const Unicode *, int, bool, bool, bool, bool, bool, bool, bool, bool, bool,
                            double *xMin, double *yMin, double *xMax, double *yMax,
                            PDFRectangle *, bool *) -> bool {
            *xMin = 1.0; *yMin = 2.0; *xMax = 3.0; *yMax = 4.0;
            return true;
        }))
        .WillOnce(Invoke([](const Unicode *, int, bool, bool, bool, bool, bool, bool, bool, bool, bool,
                            double *xMin, double *yMin, double *xMax, double *yMax,
                            PDFRectangle *, bool *) -> bool {
            *xMin = 5.0; *yMin = 6.0; *xMax = 7.0; *yMax = 8.0;
            return true;
        }))
        .WillOnce(Invoke([](const Unicode *, int, bool, bool, bool, bool, bool, bool, bool, bool, bool,
                            double *xMin, double *yMin, double *xMax, double *yMax,
                            PDFRectangle *, bool *) -> bool {
            *xMin = 9.0; *yMin = 10.0; *xMax = 11.0; *yMax = 12.0;
            return true;
        }))
        .WillOnce(Return(false));

    QList<QRectF> results = pageData.performMultipleTextSearch(&mockTextPage, searchText, false, false, false, false);

    ASSERT_EQ(results.size(), 3);
    EXPECT_DOUBLE_EQ(results[0].left(), 1.0);
    EXPECT_DOUBLE_EQ(results[0].top(), 2.0);
    EXPECT_DOUBLE_EQ(results[1].left(), 5.0);
    EXPECT_DOUBLE_EQ(results[1].top(), 6.0);
    EXPECT_DOUBLE_EQ(results[2].left(), 9.0);
    EXPECT_DOUBLE_EQ(results[2].top(), 10.0);
}

// Test: Across lines match with continueMatch populated adds extra rectangle
TEST_F(PageDataMultipleTextSearchTest_1443, AcrossLinesWithContinueMatchAddsExtraRect_1443)
{
    QVector<Unicode> searchText = {'x', 'y'};

    EXPECT_CALL(mockTextPage, findText(_, _, false, true, true, false, false, false, true, false, false, _, _, _, _, _, _))
        .WillOnce(Invoke([](const Unicode *, int, bool, bool, bool, bool, bool, bool, bool, bool, bool,
                            double *xMin, double *yMin, double *xMax, double *yMax,
                            PDFRectangle *continueMatch, bool *) -> bool {
            *xMin = 10.0; *yMin = 20.0; *xMax = 50.0; *yMax = 30.0;
            // Set continueMatch to indicate an across-lines match
            continueMatch->x1 = 0.0;
            continueMatch->y1 = 30.0;
            continueMatch->x2 = 40.0;
            continueMatch->y2 = 40.0;
            return true;
        }))
        .WillOnce(Return(false));

    QList<QRectF> results = pageData.performMultipleTextSearch(&mockTextPage, searchText, false, false, false, true);

    ASSERT_EQ(results.size(), 2);
    // First rect is the main match
    EXPECT_DOUBLE_EQ(results[0].left(), 10.0);
    EXPECT_DOUBLE_EQ(results[0].top(), 20.0);
    EXPECT_DOUBLE_EQ(results[0].right(), 50.0);
    EXPECT_DOUBLE_EQ(results[0].bottom(), 30.0);
    // Second rect is from continueMatch
    EXPECT_DOUBLE_EQ(results[1].left(), 0.0);
    EXPECT_DOUBLE_EQ(results[1].top(), 30.0);
    EXPECT_DOUBLE_EQ(results[1].right(), 40.0);
    // Note: bottom is set to continueMatch.y1, not y2
    EXPECT_DOUBLE_EQ(results[1].bottom(), 30.0);
}

// Test: Across lines enabled but continueMatch.x1 remains DBL_MAX - no extra rect
TEST_F(PageDataMultipleTextSearchTest_1443, AcrossLinesNoContinueMatchNoExtraRect_1443)
{
    QVector<Unicode> searchText = {'z'};

    EXPECT_CALL(mockTextPage, findText(_, _, false, true, true, false, false, false, true, false, false, _, _, _, _, _, _))
        .WillOnce(Invoke([](const Unicode *, int, bool, bool, bool, bool, bool, bool, bool, bool, bool,
                            double *xMin, double *yMin, double *xMax, double *yMax,
                            PDFRectangle *continueMatch, bool *) -> bool {
            *xMin = 10.0; *yMin = 20.0; *xMax = 50.0; *yMax = 30.0;
            // continueMatch.x1 stays DBL_MAX (not set by findText)
            continueMatch->x1 = DBL_MAX;
            return true;
        }))
        .WillOnce(Return(false));

    QList<QRectF> results = pageData.performMultipleTextSearch(&mockTextPage, searchText, false, false, false, true);

    ASSERT_EQ(results.size(), 1);
    EXPECT_DOUBLE_EQ(results[0].left(), 10.0);
    EXPECT_DOUBLE_EQ(results[0].top(), 20.0);
}

// Test: Across lines disabled even if continueMatch is set - no extra rect
TEST_F(PageDataMultipleTextSearchTest_1443, AcrossLinesDisabledIgnoresContinueMatch_1443)
{
    QVector<Unicode> searchText = {'a'};

    EXPECT_CALL(mockTextPage, findText(_, _, false, true, true, false, false, false, false, false, false, _, _, _, _, _, _))
        .WillOnce(Invoke([](const Unicode *, int, bool, bool, bool, bool, bool, bool, bool, bool, bool,
                            double *xMin, double *yMin, double *xMax, double *yMax,
                            PDFRectangle *continueMatch, bool *) -> bool {
            *xMin = 10.0; *yMin = 20.0; *xMax = 50.0; *yMax = 30.0;
            // Even though we set continueMatch, sAcrossLines is false
            continueMatch->x1 = 5.0;
            continueMatch->y1 = 35.0;
            continueMatch->x2 = 45.0;
            continueMatch->y2 = 45.0;
            return true;
        }))
        .WillOnce(Return(false));

    QList<QRectF> results = pageData.performMultipleTextSearch(&mockTextPage, searchText, false, false, false, false);

    // Only the main match, no extra rect since sAcrossLines is false
    ASSERT_EQ(results.size(), 1);
    EXPECT_DOUBLE_EQ(results[0].left(), 10.0);
}

// Test: Multiple across-lines matches each with continue match
TEST_F(PageDataMultipleTextSearchTest_1443, MultipleAcrossLinesMatchesEachWithContinue_1443)
{
    QVector<Unicode> searchText = {'m', 'n'};

    EXPECT_CALL(mockTextPage, findText(_, _, false, true, true, false, false, false, true, false, false, _, _, _, _, _, _))
        .WillOnce(Invoke([](const Unicode *, int, bool, bool, bool, bool, bool, bool, bool, bool, bool,
                            double *xMin, double *yMin, double *xMax, double *yMax,
                            PDFRectangle *continueMatch, bool *) -> bool {
            *xMin = 1.0; *yMin = 2.0; *xMax = 3.0; *yMax = 4.0;
            continueMatch->x1 = 10.0;
            continueMatch->y1 = 20.0;
            continueMatch->x2 = 30.0;
            continueMatch->y2 = 40.0;
            return true;
        }))
        .WillOnce(Invoke([](const Unicode *, int, bool, bool, bool, bool, bool, bool, bool, bool, bool,
                            double *xMin, double *yMin, double *xMax, double *yMax,
                            PDFRectangle *continueMatch, bool *) -> bool {
            *xMin = 50.0; *yMin = 60.0; *xMax = 70.0; *yMax = 80.0;
            continueMatch->x1 = 100.0;
            continueMatch->y1 = 110.0;
            continueMatch->x2 = 120.0;
            continueMatch->y2 = 130.0;
            return true;
        }))
        .WillOnce(Return(false));

    QList<QRectF> results = pageData.performMultipleTextSearch(&mockTextPage, searchText, false, false, false, true);

    // 2 main matches + 2 continue matches = 4 total
    ASSERT_EQ(results.size(), 4);
    // First main match
    EXPECT_DOUBLE_EQ(results[0].left(), 1.0);
    EXPECT_DOUBLE_EQ(results[0].top(), 2.0);
    // First continue match
    EXPECT_DOUBLE_EQ(results[1].left(), 10.0);
    EXPECT_DOUBLE_EQ(results[1].top(), 20.0);
    EXPECT_DOUBLE_EQ(results[1].right(), 30.0);
    EXPECT_DOUBLE_EQ(results[1].bottom(), 20.0); // y1, not y2
    // Second main match
    EXPECT_DOUBLE_EQ(results[2].left(), 50.0);
    EXPECT_DOUBLE_EQ(results[2].top(), 60.0);
    // Second continue match
    EXPECT_DOUBLE_EQ(results[3].left(), 100.0);
    EXPECT_DOUBLE_EQ(results[3].top(), 110.0);
    EXPECT_DOUBLE_EQ(results[3].right(), 120.0);
    EXPECT_DOUBLE_EQ(results[3].bottom(), 110.0); // y1, not y2
}

// Test: Empty search text
TEST_F(PageDataMultipleTextSearchTest_1443, EmptySearchText_1443)
{
    QVector<Unicode> searchText;

    EXPECT_CALL(mockTextPage, findText(_, 0, false, true, true, false, false, false, false, false, false, _, _, _, _, _, _))
        .WillOnce(Return(false));

    QList<QRectF> results = pageData.performMultipleTextSearch(&mockTextPage, searchText, false, false, false, false);

    EXPECT_TRUE(results.isEmpty());
}

// Test: Parameters are correctly forwarded - case sensitive
TEST_F(PageDataMultipleTextSearchTest_1443, CaseSensitiveParameterForwarded_1443)
{
    QVector<Unicode> searchText = {'A'};

    // caseSensitive=true should be forwarded
    EXPECT_CALL(mockTextPage, findText(_, 1, false, true, true, false, true, false, false, false, false, _, _, _, _, _, _))
        .WillOnce(Return(false));

    pageData.performMultipleTextSearch(&mockTextPage, searchText, true, false, false, false);
}

// Test: Parameters are correctly forwarded - whole words
TEST_F(PageDataMultipleTextSearchTest_1443, WholeWordsParameterForwarded_1443)
{
    QVector<Unicode> searchText = {'A'};

    // wholeWord=true should be forwarded
    EXPECT_CALL(mockTextPage, findText(_, 1, false, true, true, false, false, false, false, false, true, _, _, _, _, _, _))
        .WillOnce(Return(false));

    pageData.performMultipleTextSearch(&mockTextPage, searchText, false, true, false, false);
}

// Test: Parameters are correctly forwarded - diacritics
TEST_F(PageDataMultipleTextSearchTest_1443, DiacriticsParameterForwarded_1443)
{
    QVector<Unicode> searchText = {'A'};

    // ignoreDiacritics=true should be forwarded
    EXPECT_CALL(mockTextPage, findText(_, 1, false, true, true, false, false, true, false, false, false, _, _, _, _, _, _))
        .WillOnce(Return(false));

    pageData.performMultipleTextSearch(&mockTextPage, searchText, false, false, true, false);
}

// Test: Parameters are correctly forwarded - across lines
TEST_F(PageDataMultipleTextSearchTest_1443, AcrossLinesParameterForwarded_1443)
{
    QVector<Unicode> searchText = {'A'};

    // matchAcrossLines=true should be forwarded
    EXPECT_CALL(mockTextPage, findText(_, 1, false, true, true, false, false, false, true, false, false, _, _, _, _, _, _))
        .WillOnce(Return(false));

    pageData.performMultipleTextSearch(&mockTextPage, searchText, false, false, false, true);
}

// Test: All parameters set to true
TEST_F(PageDataMultipleTextSearchTest_1443, AllParametersTrue_1443)
{
    QVector<Unicode> searchText = {'A'};

    EXPECT_CALL(mockTextPage, findText(_, 1, false, true, true, false, true, true, true, false, true, _, _, _, _, _, _))
        .WillOnce(Return(false));

    pageData.performMultipleTextSearch(&mockTextPage, searchText, true, true, true, true);
}

// Test: ContinueMatch x1 is reset to DBL_MAX after being used
TEST_F(PageDataMultipleTextSearchTest_1443, ContinueMatchResetAfterUse_1443)
{
    QVector<Unicode> searchText = {'a', 'b'};
    int callCount = 0;

    EXPECT_CALL(mockTextPage, findText(_, _, false, true, true, false, false, false, true, false, false, _, _, _, _, _, _))
        .WillOnce(Invoke([&](const Unicode *, int, bool, bool, bool, bool, bool, bool, bool, bool, bool,
                             double *xMin, double *yMin, double *xMax, double *yMax,
                             PDFRectangle *continueMatch, bool *) -> bool {
            // First call - continueMatch.x1 should be DBL_MAX
            EXPECT_DOUBLE_EQ(continueMatch->x1, DBL_MAX);
            *xMin = 1.0; *yMin = 2.0; *xMax = 3.0; *yMax = 4.0;
            continueMatch->x1 = 5.0;
            continueMatch->y1 = 6.0;
            continueMatch->x2 = 7.0;
            continueMatch->y2 = 8.0;
            return true;
        }))
        .WillOnce(Invoke([&](const Unicode *, int, bool, bool, bool, bool, bool, bool, bool, bool, bool,
                             double *xMin, double *yMin, double *xMax, double *yMax,
                             PDFRectangle *continueMatch, bool *) -> bool {
            // After processing, continueMatch.x1 should be reset to DBL_MAX
            EXPECT_DOUBLE_EQ(continueMatch->x1, DBL_MAX);
            return false;
        }));

    QList<QRectF> results = pageData.performMultipleTextSearch(&mockTextPage, searchText, false, false, false, true);

    ASSERT_EQ(results.size(), 2);
}

// Test: Zero-sized rectangles are handled properly
TEST_F(PageDataMultipleTextSearchTest_1443, ZeroSizedRectangle_1443)
{
    QVector<Unicode> searchText = {'x'};

    EXPECT_CALL(mockTextPage, findText(_, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _))
        .WillOnce(Invoke([](const Unicode *, int, bool, bool, bool, bool, bool, bool, bool, bool, bool,
                            double *xMin, double *yMin, double *xMax, double *yMax,
                            PDFRectangle *, bool *) -> bool {
            *xMin = 5.0; *yMin = 5.0; *xMax = 5.0; *yMax = 5.0;
            return true;
        }))
        .WillOnce(Return(false));

    QList<QRectF> results = pageData.performMultipleTextSearch(&mockTextPage, searchText, false, false, false, false);

    ASSERT_EQ(results.size(), 1);
    EXPECT_DOUBLE_EQ(results[0].left(), 5.0);
    EXPECT_DOUBLE_EQ(results[0].top(), 5.0);
    EXPECT_DOUBLE_EQ(results[0].right(), 5.0);
    EXPECT_DOUBLE_EQ(results[0].bottom(), 5.0);
}

// Test: Negative coordinate values
TEST_F(PageDataMultipleTextSearchTest_1443, NegativeCoordinates_1443)
{
    QVector<Unicode> searchText = {'n'};

    EXPECT_CALL(mockTextPage, findText(_, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _))
        .WillOnce(Invoke([](const Unicode *, int, bool, bool, bool, bool, bool, bool, bool, bool, bool,
                            double *xMin, double *yMin, double *xMax, double *yMax,
                            PDFRectangle *, bool *) -> bool {
            *xMin = -10.0; *yMin = -20.0; *xMax = -5.0; *yMax = -15.0;
            return true;
        }))
        .WillOnce(Return(false));

    QList<QRectF> results = pageData.performMultipleTextSearch(&mockTextPage, searchText, false, false, false, false);

    ASSERT_EQ(results.size(), 1);
    EXPECT_DOUBLE_EQ(results[0].left(), -10.0);
    EXPECT_DOUBLE_EQ(results[0].top(), -20.0);
    EXPECT_DOUBLE_EQ(results[0].right(), -5.0);
    EXPECT_DOUBLE_EQ(results[0].bottom(), -15.0);
}

// Test: Large number of matches
TEST_F(PageDataMultipleTextSearchTest_1443, LargeNumberOfMatches_1443)
{
    QVector<Unicode> searchText = {'q'};
    int matchCount = 0;
    const int totalMatches = 1000;

    EXPECT_CALL(mockTextPage, findText(_, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _))
        .WillRepeatedly(Invoke([&](const Unicode *, int, bool, bool, bool, bool, bool, bool, bool, bool, bool,
                                   double *xMin, double *yMin, double *xMax, double *yMax,
                                   PDFRectangle *, bool *) -> bool {
            if (matchCount < totalMatches) {
                *xMin = matchCount * 1.0;
                *yMin = matchCount * 2.0;
                *xMax = matchCount * 3.0;
                *yMax = matchCount * 4.0;
                matchCount++;
                return true;
            }
            return false;
        }));

    QList<QRectF> results = pageData.performMultipleTextSearch(&mockTextPage, searchText, false, false, false, false);

    ASSERT_EQ(results.size(), totalMatches);
    EXPECT_DOUBLE_EQ(results[0].left(), 0.0);
    EXPECT_DOUBLE_EQ(results[999].left(), 999.0);
}

// Test: searchText data pointer and size are correctly passed
TEST_F(PageDataMultipleTextSearchTest_1443, SearchTextDataAndSizeCorrectlyPassed_1443)
{
    QVector<Unicode> searchText = {'H', 'e', 'l', 'l', 'o'};

    EXPECT_CALL(mockTextPage, findText(searchText.data(), 5, false, true, true, false, false, false, false, false, false, _, _, _, _, _, _))
        .WillOnce(Return(false));

    QList<QRectF> results = pageData.performMultipleTextSearch(&mockTextPage, searchText, false, false, false, false);

    EXPECT_TRUE(results.isEmpty());
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
