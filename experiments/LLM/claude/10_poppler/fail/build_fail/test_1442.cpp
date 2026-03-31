#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <QVector>
#include <vector>
#include <memory>

// Forward declarations and minimal types needed
typedef unsigned int Unicode;
typedef unsigned int CharCode;

// Minimal stubs for types referenced by TextPage
class GfxState;
class GfxColor;
class OutputDev;
class AnnotLink;
class UnicodeMap;
class GooString;
class TextWord;
class TextFontInfo;
class TextFlow;
class TextBlock;
class TextLine;
class TextLineFrag;
class TextPool;
class TextUnderline;
class TextLink;
class TextWordSelection;
class TextWordList;
class TextSelectionVisitor;

struct PDFRectangle {
    double x1, y1, x2, y2;
};

enum SelectionStyle { selectionStyleGlyph, selectionStyleWord, selectionStyleLine };
enum EndOfLineKind { eolUnix, eolDOS, eolMac };
typedef void (*TextOutputFunc)(void *stream, const char *text, int len);

// Mock TextPage class
class TextPage {
public:
    TextPage(bool rawOrderA, bool discardDiagA) {}
    virtual ~TextPage() {}

    MOCK_METHOD(bool, findText,
        (const Unicode *s, int len, bool startAtTop, bool stopAtBottom,
         bool startAtLast, bool stopAtLast, bool caseSensitive,
         bool ignoreDiacritics, bool matchAcrossLines, bool backward,
         bool wholeWord, double *xMin, double *yMin, double *xMax, double *yMax,
         PDFRectangle *continueMatch, bool *ignoredHyphen));
};

// Poppler namespace with Page enum and PageData
namespace Poppler {

class Page {
public:
    enum SearchDirection { FromTop, NextResult, PreviousResult };
    enum Rotation { Rotate0, Rotate90, Rotate180, Rotate270 };
};

class PageData {
public:
    inline bool performSingleTextSearch(TextPage *textPage, QVector<Unicode> &u,
        double &sLeft, double &sTop, double &sRight, double &sBottom,
        Page::SearchDirection direction, bool sCase, bool sWords,
        bool sDiacritics, bool sAcrossLines)
    {
        if (direction == Page::FromTop) {
            return textPage->findText(u.data(), u.size(), true, true, false, false,
                sCase, sDiacritics, sAcrossLines, false, sWords,
                &sLeft, &sTop, &sRight, &sBottom, nullptr, nullptr);
        }
        if (direction == Page::NextResult) {
            return textPage->findText(u.data(), u.size(), false, true, true, false,
                sCase, sDiacritics, sAcrossLines, false, sWords,
                &sLeft, &sTop, &sRight, &sBottom, nullptr, nullptr);
        }
        if (direction == Page::PreviousResult) {
            return textPage->findText(u.data(), u.size(), false, true, true, false,
                sCase, sDiacritics, sAcrossLines, true, sWords,
                &sLeft, &sTop, &sRight, &sBottom, nullptr, nullptr);
        }
        return false;
    }
};

} // namespace Poppler

using namespace Poppler;
using ::testing::_;
using ::testing::Return;
using ::testing::DoAll;

class PageDataSearchTest_1442 : public ::testing::Test {
protected:
    PageData pageData;
    TextPage textPage{false, false};

    double sLeft = 0.0, sTop = 0.0, sRight = 0.0, sBottom = 0.0;
    QVector<Unicode> searchText;

    void SetUp() override {
        searchText = {72, 101, 108, 108, 111}; // "Hello" in Unicode codepoints
    }
};

// Test FromTop direction calls findText with correct parameters
TEST_F(PageDataSearchTest_1442, FromTop_CallsFindTextWithCorrectParams_1442) {
    EXPECT_CALL(textPage, findText(
        searchText.data(), searchText.size(),
        true,   // startAtTop
        true,   // stopAtBottom
        false,  // startAtLast
        false,  // stopAtLast
        true,   // caseSensitive
        false,  // ignoreDiacritics
        false,  // matchAcrossLines
        false,  // backward
        false,  // wholeWord
        &sLeft, &sTop, &sRight, &sBottom,
        nullptr, nullptr
    )).WillOnce(Return(true));

    bool result = pageData.performSingleTextSearch(&textPage, searchText,
        sLeft, sTop, sRight, sBottom, Page::FromTop,
        true, false, false, false);

    EXPECT_TRUE(result);
}

// Test NextResult direction calls findText with correct parameters
TEST_F(PageDataSearchTest_1442, NextResult_CallsFindTextWithCorrectParams_1442) {
    EXPECT_CALL(textPage, findText(
        searchText.data(), searchText.size(),
        false,  // startAtTop
        true,   // stopAtBottom
        true,   // startAtLast
        false,  // stopAtLast
        true,   // caseSensitive
        false,  // ignoreDiacritics
        false,  // matchAcrossLines
        false,  // backward
        false,  // wholeWord
        &sLeft, &sTop, &sRight, &sBottom,
        nullptr, nullptr
    )).WillOnce(Return(true));

    bool result = pageData.performSingleTextSearch(&textPage, searchText,
        sLeft, sTop, sRight, sBottom, Page::NextResult,
        true, false, false, false);

    EXPECT_TRUE(result);
}

// Test PreviousResult direction calls findText with correct parameters (backward=true)
TEST_F(PageDataSearchTest_1442, PreviousResult_CallsFindTextWithBackwardTrue_1442) {
    EXPECT_CALL(textPage, findText(
        searchText.data(), searchText.size(),
        false,  // startAtTop
        true,   // stopAtBottom
        true,   // startAtLast
        false,  // stopAtLast
        false,  // caseSensitive
        true,   // ignoreDiacritics
        true,   // matchAcrossLines
        true,   // backward (key difference for PreviousResult)
        true,   // wholeWord
        &sLeft, &sTop, &sRight, &sBottom,
        nullptr, nullptr
    )).WillOnce(Return(true));

    bool result = pageData.performSingleTextSearch(&textPage, searchText,
        sLeft, sTop, sRight, sBottom, Page::PreviousResult,
        false, true, true, true);

    EXPECT_TRUE(result);
}

// Test FromTop direction when findText returns false
TEST_F(PageDataSearchTest_1442, FromTop_ReturnsFalseWhenNotFound_1442) {
    EXPECT_CALL(textPage, findText(_, _, true, true, false, false, _, _, _, false, _, _, _, _, _, _, _))
        .WillOnce(Return(false));

    bool result = pageData.performSingleTextSearch(&textPage, searchText,
        sLeft, sTop, sRight, sBottom, Page::FromTop,
        true, false, false, false);

    EXPECT_FALSE(result);
}

// Test NextResult direction when findText returns false
TEST_F(PageDataSearchTest_1442, NextResult_ReturnsFalseWhenNotFound_1442) {
    EXPECT_CALL(textPage, findText(_, _, false, true, true, false, _, _, _, false, _, _, _, _, _, _, _))
        .WillOnce(Return(false));

    bool result = pageData.performSingleTextSearch(&textPage, searchText,
        sLeft, sTop, sRight, sBottom, Page::NextResult,
        false, false, false, false);

    EXPECT_FALSE(result);
}

// Test PreviousResult direction when findText returns false
TEST_F(PageDataSearchTest_1442, PreviousResult_ReturnsFalseWhenNotFound_1442) {
    EXPECT_CALL(textPage, findText(_, _, false, true, true, false, _, _, _, true, _, _, _, _, _, _, _))
        .WillOnce(Return(false));

    bool result = pageData.performSingleTextSearch(&textPage, searchText,
        sLeft, sTop, sRight, sBottom, Page::PreviousResult,
        false, false, false, false);

    EXPECT_FALSE(result);
}

// Test that caseSensitive flag is correctly passed through for FromTop
TEST_F(PageDataSearchTest_1442, FromTop_CaseSensitiveFlagPassedCorrectly_1442) {
    EXPECT_CALL(textPage, findText(_, _, true, true, false, false,
        false, // caseSensitive = false
        _, _, false, _, _, _, _, _, _, _))
        .WillOnce(Return(true));

    bool result = pageData.performSingleTextSearch(&textPage, searchText,
        sLeft, sTop, sRight, sBottom, Page::FromTop,
        false, false, false, false);

    EXPECT_TRUE(result);
}

// Test that wholeWord flag is correctly passed through
TEST_F(PageDataSearchTest_1442, FromTop_WholeWordFlagPassedCorrectly_1442) {
    EXPECT_CALL(textPage, findText(_, _, true, true, false, false, _, _, _, false,
        true, // wholeWord = true
        _, _, _, _, _, _))
        .WillOnce(Return(true));

    bool result = pageData.performSingleTextSearch(&textPage, searchText,
        sLeft, sTop, sRight, sBottom, Page::FromTop,
        false, true, false, false);

    EXPECT_TRUE(result);
}

// Test that ignoreDiacritics flag is correctly passed through
TEST_F(PageDataSearchTest_1442, FromTop_IgnoreDiacriticsFlagPassedCorrectly_1442) {
    EXPECT_CALL(textPage, findText(_, _, true, true, false, false, _,
        true, // ignoreDiacritics = true
        _, false, _, _, _, _, _, _, _))
        .WillOnce(Return(true));

    bool result = pageData.performSingleTextSearch(&textPage, searchText,
        sLeft, sTop, sRight, sBottom, Page::FromTop,
        false, false, true, false);

    EXPECT_TRUE(result);
}

// Test that matchAcrossLines flag is correctly passed through
TEST_F(PageDataSearchTest_1442, FromTop_MatchAcrossLinesFlagPassedCorrectly_1442) {
    EXPECT_CALL(textPage, findText(_, _, true, true, false, false, _,  _,
        true, // matchAcrossLines = true
        false, _, _, _, _, _, _, _))
        .WillOnce(Return(true));

    bool result = pageData.performSingleTextSearch(&textPage, searchText,
        sLeft, sTop, sRight, sBottom, Page::FromTop,
        false, false, false, true);

    EXPECT_TRUE(result);
}

// Test with empty search text
TEST_F(PageDataSearchTest_1442, EmptySearchText_FromTop_1442) {
    QVector<Unicode> emptyText;

    EXPECT_CALL(textPage, findText(_, 0, true, true, false, false, _, _, _, false, _, _, _, _, _, _, _))
        .WillOnce(Return(false));

    bool result = pageData.performSingleTextSearch(&textPage, emptyText,
        sLeft, sTop, sRight, sBottom, Page::FromTop,
        false, false, false, false);

    EXPECT_FALSE(result);
}

// Test with single character search text
TEST_F(PageDataSearchTest_1442, SingleCharSearchText_FromTop_1442) {
    QVector<Unicode> singleChar = {65}; // 'A'

    EXPECT_CALL(textPage, findText(singleChar.data(), 1, true, true, false, false, _, _, _, false, _, _, _, _, _, _, _))
        .WillOnce(Return(true));

    bool result = pageData.performSingleTextSearch(&textPage, singleChar,
        sLeft, sTop, sRight, sBottom, Page::FromTop,
        false, false, false, false);

    EXPECT_TRUE(result);
}

// Test that coordinates are passed by reference (modifiable by findText)
TEST_F(PageDataSearchTest_1442, FromTop_CoordinatesUpdatedByFindText_1442) {
    sLeft = 0.0; sTop = 0.0; sRight = 0.0; sBottom = 0.0;

    EXPECT_CALL(textPage, findText(_, _, true, true, false, false, _, _, _, false, _, _, _, _, _, _, _))
        .WillOnce(DoAll(
            ::testing::SetArgPointee<11>(10.0),
            ::testing::SetArgPointee<12>(20.0),
            ::testing::SetArgPointee<13>(100.0),
            ::testing::SetArgPointee<14>(50.0),
            Return(true)));

    bool result = pageData.performSingleTextSearch(&textPage, searchText,
        sLeft, sTop, sRight, sBottom, Page::FromTop,
        false, false, false, false);

    EXPECT_TRUE(result);
    EXPECT_DOUBLE_EQ(sLeft, 10.0);
    EXPECT_DOUBLE_EQ(sTop, 20.0);
    EXPECT_DOUBLE_EQ(sRight, 100.0);
    EXPECT_DOUBLE_EQ(sBottom, 50.0);
}

// Test all flags set to true for FromTop
TEST_F(PageDataSearchTest_1442, FromTop_AllFlagsTrue_1442) {
    EXPECT_CALL(textPage, findText(_, _, true, true, false, false,
        true,  // caseSensitive
        true,  // ignoreDiacritics
        true,  // matchAcrossLines
        false, // backward (always false for FromTop)
        true,  // wholeWord
        _, _, _, _, _, _))
        .WillOnce(Return(true));

    bool result = pageData.performSingleTextSearch(&textPage, searchText,
        sLeft, sTop, sRight, sBottom, Page::FromTop,
        true, true, true, true);

    EXPECT_TRUE(result);
}

// Test all flags set to true for NextResult
TEST_F(PageDataSearchTest_1442, NextResult_AllFlagsTrue_1442) {
    EXPECT_CALL(textPage, findText(_, _, false, true, true, false,
        true,  // caseSensitive
        true,  // ignoreDiacritics
        true,  // matchAcrossLines
        false, // backward (always false for NextResult)
        true,  // wholeWord
        _, _, _, _, _, _))
        .WillOnce(Return(true));

    bool result = pageData.performSingleTextSearch(&textPage, searchText,
        sLeft, sTop, sRight, sBottom, Page::NextResult,
        true, true, true, true);

    EXPECT_TRUE(result);
}

// Test all flags set to true for PreviousResult
TEST_F(PageDataSearchTest_1442, PreviousResult_AllFlagsTrue_1442) {
    EXPECT_CALL(textPage, findText(_, _, false, true, true, false,
        true,  // caseSensitive
        true,  // ignoreDiacritics
        true,  // matchAcrossLines
        true,  // backward (always true for PreviousResult)
        true,  // wholeWord
        _, _, _, _, _, _))
        .WillOnce(Return(true));

    bool result = pageData.performSingleTextSearch(&textPage, searchText,
        sLeft, sTop, sRight, sBottom, Page::PreviousResult,
        true, true, true, true);

    EXPECT_TRUE(result);
}

// Verify that the backward flag distinguishes NextResult from PreviousResult
TEST_F(PageDataSearchTest_1442, NextVsPrevious_BackwardFlagDifference_1442) {
    // NextResult: backward = false
    EXPECT_CALL(textPage, findText(_, _, false, true, true, false, _, _, _,
        false, // backward
        _, _, _, _, _, _, _))
        .WillOnce(Return(true));

    bool resultNext = pageData.performSingleTextSearch(&textPage, searchText,
        sLeft, sTop, sRight, sBottom, Page::NextResult,
        false, false, false, false);
    EXPECT_TRUE(resultNext);

    // PreviousResult: backward = true
    EXPECT_CALL(textPage, findText(_, _, false, true, true, false, _, _, _,
        true, // backward
        _, _, _, _, _, _, _))
        .WillOnce(Return(true));

    bool resultPrev = pageData.performSingleTextSearch(&textPage, searchText,
        sLeft, sTop, sRight, sBottom, Page::PreviousResult,
        false, false, false, false);
    EXPECT_TRUE(resultPrev);
}

// Test with non-zero initial coordinates for NextResult
TEST_F(PageDataSearchTest_1442, NextResult_CoordinatesUpdated_1442) {
    sLeft = 50.0; sTop = 60.0; sRight = 70.0; sBottom = 80.0;

    EXPECT_CALL(textPage, findText(_, _, false, true, true, false, _, _, _, false, _, _, _, _, _, _, _))
        .WillOnce(DoAll(
            ::testing::SetArgPointee<11>(150.0),
            ::testing::SetArgPointee<12>(160.0),
            ::testing::SetArgPointee<13>(170.0),
            ::testing::SetArgPointee<14>(180.0),
            Return(true)));

    bool result = pageData.performSingleTextSearch(&textPage, searchText,
        sLeft, sTop, sRight, sBottom, Page::NextResult,
        false, false, false, false);

    EXPECT_TRUE(result);
    EXPECT_DOUBLE_EQ(sLeft, 150.0);
    EXPECT_DOUBLE_EQ(sTop, 160.0);
    EXPECT_DOUBLE_EQ(sRight, 170.0);
    EXPECT_DOUBLE_EQ(sBottom, 180.0);
}

// Test that the correct data pointer and size are passed
TEST_F(PageDataSearchTest_1442, FromTop_CorrectDataAndSizePassed_1442) {
    QVector<Unicode> customText = {0x41, 0x42, 0x43}; // ABC

    EXPECT_CALL(textPage, findText(
        customText.data(),
        3, // size
        true, true, false, false, _, _, _, false, _, _, _, _, _, _, _))
        .WillOnce(Return(false));

    bool result = pageData.performSingleTextSearch(&textPage, customText,
        sLeft, sTop, sRight, sBottom, Page::FromTop,
        false, false, false, false);

    EXPECT_FALSE(result);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
