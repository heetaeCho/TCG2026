#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/poppler/qt5/src/poppler-page.cc"

#include "./TestProjects/poppler/poppler/TextOutputDev.h"



using namespace Poppler;

using namespace testing;



class MockTextPage : public TextPage {

public:

    MOCK_METHOD(bool, findText,

                (const Unicode * s, int len, bool startAtTop, bool stopAtBottom, bool startAtLast, 

                 bool stopAtLast, bool caseSensitive, bool ignoreDiacritics, bool matchAcrossLines, 

                 bool backward, bool wholeWord, double * xMin, double * yMin, double * xMax, double * yMax, PDFRectangle * continueMatch, _Bool * ignoredHyphen),

                (override));

};



class PageDataTest : public Test {

protected:

    MockTextPage mockTextPage;

    PageData pageData;

    QVector<Unicode> searchTerms;

};



TEST_F(PageDataTest, PerformMultipleTextSearch_NormalOperation_1443) {

    double xMin = 1.0, yMin = 2.0, xMax = 3.0, yMax = 4.0;

    PDFRectangle continueMatch(DBL_MAX, DBL_MAX, DBL_MAX, DBL_MAX);

    bool ignoredHyphen = false;



    EXPECT_CALL(mockTextPage, findText(_, _, _, _, _, _, true, false, true, false, false, &xMin, &yMin, &xMax, &yMax, &continueMatch, &ignoredHyphen))

        .WillOnce(Return(true));



    searchTerms << 't' << 'e' << 's' << 't';

    QList<QRectF> results = pageData.performMultipleTextSearch(&mockTextPage, searchTerms, true, false, true, true);



    ASSERT_EQ(results.size(), 1);

    EXPECT_EQ(results.first(), QRectF(1.0, 2.0, 3.0, 4.0));

}



TEST_F(PageDataTest, PerformMultipleTextSearch_NoResults_1443) {

    double xMin = 0.0, yMin = 0.0, xMax = 0.0, yMax = 0.0;

    PDFRectangle continueMatch(DBL_MAX, DBL_MAX, DBL_MAX, DBL_MAX);

    bool ignoredHyphen = false;



    EXPECT_CALL(mockTextPage, findText(_, _, _, _, _, _, true, false, true, false, false, &xMin, &yMin, &xMax, &yMax, &continueMatch, &ignoredHyphen))

        .WillOnce(Return(false));



    searchTerms << 'n' << 'o' << 'r' << 'e' << 's' << 'u' << 'l' << 't';

    QList<QRectF> results = pageData.performMultipleTextSearch(&mockTextPage, searchTerms, true, false, true, true);



    EXPECT_TRUE(results.isEmpty());

}



TEST_F(PageDataTest, PerformMultipleTextSearch_MatchAcrossLines_1443) {

    double xMin = 1.0, yMin = 2.0, xMax = 3.0, yMax = 4.0;

    PDFRectangle continueMatch(5.0, 6.0, 7.0, 8.0);

    bool ignoredHyphen = false;



    EXPECT_CALL(mockTextPage, findText(_, _, _, _, _, _, true, false, true, false, false, &xMin, &yMin, &xMax, &yMax, &continueMatch, &ignoredHyphen))

        .WillOnce(Return(true));



    searchTerms << 'm' << 'a' << 't' << 'c' << 'h';

    QList<QRectF> results = pageData.performMultipleTextSearch(&mockTextPage, searchTerms, true, false, true, true);



    ASSERT_EQ(results.size(), 2);

    EXPECT_EQ(results.first(), QRectF(1.0, 2.0, 3.0, 4.0));

    EXPECT_EQ(results.last(), QRectF(5.0, 6.0, 7.0, 6.0));

}



TEST_F(PageDataTest, PerformMultipleTextSearch_BoundaryCondition_1443) {

    double xMin = DBL_MAX, yMin = DBL_MAX, xMax = DBL_MAX, yMax = DBL_MAX;

    PDFRectangle continueMatch(DBL_MAX, DBL_MAX, DBL_MAX, DBL_MAX);

    bool ignoredHyphen = false;



    EXPECT_CALL(mockTextPage, findText(_, _, _, _, _, _, true, false, true, false, false, &xMin, &yMin, &xMax, &yMax, &continueMatch, &ignoredHyphen))

        .WillOnce(Return(true));



    searchTerms << 'b' << 'o' << 'u' << 'n' << 'd' << 'a' << 'r' << 'y';

    QList<QRectF> results = pageData.performMultipleTextSearch(&mockTextPage, searchTerms, true, false, true, true);



    EXPECT_TRUE(results.isEmpty());

}



TEST_F(PageDataTest, PerformMultipleTextSearch_ExceptionalCase_1443) {

    double xMin = 0.0, yMin = 0.0, xMax = 0.0, yMax = 0.0;

    PDFRectangle continueMatch(DBL_MAX, DBL_MAX, DBL_MAX, DBL_MAX);

    bool ignoredHyphen = false;



    EXPECT_CALL(mockTextPage, findText(_, _, _, _, _, _, true, false, true, false, false, &xMin, &yMin, &xMax, &yMax, &continueMatch, &ignoredHyphen))

        .WillOnce(Return(false));



    searchTerms.clear();

    QList<QRectF> results = pageData.performMultipleTextSearch(&mockTextPage, searchTerms, true, false, true, true);



    EXPECT_TRUE(results.isEmpty());

}
