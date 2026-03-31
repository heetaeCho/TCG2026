#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <vector>

// Forward declarations and necessary types to compile the tests

// We need to mock FontInfoScanner since it's a dependency
// First, let's define the minimal structures needed

struct FontInfo {
    // Minimal definition for testing
};

// Mock for FontInfoScanner
class FontInfoScanner {
public:
    virtual ~FontInfoScanner() = default;
    virtual std::vector<FontInfo *> scan(int n_pages) = 0;
};

class MockFontInfoScanner : public FontInfoScanner {
public:
    MOCK_METHOD(std::vector<FontInfo *>, scan, (int n_pages), (override));
};

// Replicate the structures from the private headers
typedef int gboolean;
#ifndef TRUE
#define TRUE 1
#endif
#ifndef FALSE
#define FALSE 0
#endif

// g_return_val_if_fail macro simulation
#define g_return_val_if_fail(expr, val) \
    do {                                \
        if (!(expr))                    \
            return (val);               \
    } while (0)

struct _PopplerFontInfo {
    FontInfoScanner *scanner;
};
typedef struct _PopplerFontInfo PopplerFontInfo;

struct _PopplerFontsIter {
    int items;
};
typedef struct _PopplerFontsIter PopplerFontsIter;

// We need to provide the poppler_fonts_iter_new function
static PopplerFontsIter *poppler_fonts_iter_new(std::vector<FontInfo *> items)
{
    PopplerFontsIter *iter = new PopplerFontsIter();
    iter->items = static_cast<int>(items.size());
    return iter;
}

// Now include the function under test (reimplemented from the provided code)
// Since we can't include the actual source, we replicate the function signature
// exactly as provided
gboolean poppler_font_info_scan(PopplerFontInfo *font_info, int n_pages, PopplerFontsIter **iter)
{
    g_return_val_if_fail(iter != nullptr, FALSE);

    std::vector<FontInfo *> items = font_info->scanner->scan(n_pages);

    if (items.empty()) {
        *iter = nullptr;
        return FALSE;
    }

    *iter = poppler_fonts_iter_new(std::move(items));
    return TRUE;
}

// Test fixture
class PopplerFontInfoScanTest_2236 : public ::testing::Test {
protected:
    void SetUp() override
    {
        mock_scanner = new MockFontInfoScanner();
        font_info.scanner = mock_scanner;
    }

    void TearDown() override
    {
        delete mock_scanner;
    }

    PopplerFontInfo font_info;
    MockFontInfoScanner *mock_scanner;
};

// Test: When scanner returns non-empty results, function returns TRUE and iter is set
TEST_F(PopplerFontInfoScanTest_2236, ReturnsTrue_WhenScannerFindsFont_2236)
{
    FontInfo *fi = new FontInfo();
    std::vector<FontInfo *> results = {fi};

    EXPECT_CALL(*mock_scanner, scan(1))
        .WillOnce(::testing::Return(results));

    PopplerFontsIter *iter = nullptr;
    gboolean result = poppler_font_info_scan(&font_info, 1, &iter);

    EXPECT_EQ(result, TRUE);
    EXPECT_NE(iter, nullptr);

    delete iter;
    delete fi;
}

// Test: When scanner returns empty results, function returns FALSE and iter is nullptr
TEST_F(PopplerFontInfoScanTest_2236, ReturnsFalse_WhenScannerFindsNoFonts_2236)
{
    std::vector<FontInfo *> empty_results;

    EXPECT_CALL(*mock_scanner, scan(5))
        .WillOnce(::testing::Return(empty_results));

    PopplerFontsIter *iter = nullptr;
    gboolean result = poppler_font_info_scan(&font_info, 5, &iter);

    EXPECT_EQ(result, FALSE);
    EXPECT_EQ(iter, nullptr);
}

// Test: When iter is nullptr (null pointer passed), returns FALSE immediately
TEST_F(PopplerFontInfoScanTest_2236, ReturnsFalse_WhenIterIsNull_2236)
{
    // scanner->scan should NOT be called since we bail out early
    EXPECT_CALL(*mock_scanner, scan(::testing::_)).Times(0);

    gboolean result = poppler_font_info_scan(&font_info, 1, nullptr);

    EXPECT_EQ(result, FALSE);
}

// Test: Scanner is called with the correct n_pages parameter
TEST_F(PopplerFontInfoScanTest_2236, PassesCorrectNPagesToScanner_2236)
{
    std::vector<FontInfo *> empty_results;

    EXPECT_CALL(*mock_scanner, scan(42))
        .WillOnce(::testing::Return(empty_results));

    PopplerFontsIter *iter = nullptr;
    poppler_font_info_scan(&font_info, 42, &iter);
}

// Test: Multiple fonts returned by scanner
TEST_F(PopplerFontInfoScanTest_2236, ReturnsTrue_WhenMultipleFontsFound_2236)
{
    FontInfo *fi1 = new FontInfo();
    FontInfo *fi2 = new FontInfo();
    FontInfo *fi3 = new FontInfo();
    std::vector<FontInfo *> results = {fi1, fi2, fi3};

    EXPECT_CALL(*mock_scanner, scan(10))
        .WillOnce(::testing::Return(results));

    PopplerFontsIter *iter = nullptr;
    gboolean result = poppler_font_info_scan(&font_info, 10, &iter);

    EXPECT_EQ(result, TRUE);
    EXPECT_NE(iter, nullptr);
    EXPECT_EQ(iter->items, 3);

    delete iter;
    delete fi1;
    delete fi2;
    delete fi3;
}

// Test: n_pages is 0
TEST_F(PopplerFontInfoScanTest_2236, HandlesZeroPages_2236)
{
    std::vector<FontInfo *> empty_results;

    EXPECT_CALL(*mock_scanner, scan(0))
        .WillOnce(::testing::Return(empty_results));

    PopplerFontsIter *iter = nullptr;
    gboolean result = poppler_font_info_scan(&font_info, 0, &iter);

    EXPECT_EQ(result, FALSE);
    EXPECT_EQ(iter, nullptr);
}

// Test: n_pages is negative
TEST_F(PopplerFontInfoScanTest_2236, HandlesNegativePages_2236)
{
    std::vector<FontInfo *> empty_results;

    EXPECT_CALL(*mock_scanner, scan(-1))
        .WillOnce(::testing::Return(empty_results));

    PopplerFontsIter *iter = nullptr;
    gboolean result = poppler_font_info_scan(&font_info, -1, &iter);

    EXPECT_EQ(result, FALSE);
    EXPECT_EQ(iter, nullptr);
}

// Test: Single font returned, verify iter is properly allocated
TEST_F(PopplerFontInfoScanTest_2236, IterHasCorrectItemCount_SingleFont_2236)
{
    FontInfo *fi = new FontInfo();
    std::vector<FontInfo *> results = {fi};

    EXPECT_CALL(*mock_scanner, scan(1))
        .WillOnce(::testing::Return(results));

    PopplerFontsIter *iter = nullptr;
    gboolean result = poppler_font_info_scan(&font_info, 1, &iter);

    EXPECT_EQ(result, TRUE);
    EXPECT_NE(iter, nullptr);
    EXPECT_EQ(iter->items, 1);

    delete iter;
    delete fi;
}

// Test: Calling scan multiple times - first returns fonts, second returns empty
TEST_F(PopplerFontInfoScanTest_2236, SequentialScans_FirstNonEmptyThenEmpty_2236)
{
    FontInfo *fi = new FontInfo();
    std::vector<FontInfo *> results = {fi};
    std::vector<FontInfo *> empty_results;

    EXPECT_CALL(*mock_scanner, scan(1))
        .WillOnce(::testing::Return(results))
        .WillOnce(::testing::Return(empty_results));

    // First scan
    PopplerFontsIter *iter1 = nullptr;
    gboolean result1 = poppler_font_info_scan(&font_info, 1, &iter1);
    EXPECT_EQ(result1, TRUE);
    EXPECT_NE(iter1, nullptr);

    // Second scan
    PopplerFontsIter *iter2 = nullptr;
    gboolean result2 = poppler_font_info_scan(&font_info, 1, &iter2);
    EXPECT_EQ(result2, FALSE);
    EXPECT_EQ(iter2, nullptr);

    delete iter1;
    delete fi;
}

// Test: Large n_pages value
TEST_F(PopplerFontInfoScanTest_2236, HandlesLargeNPages_2236)
{
    FontInfo *fi = new FontInfo();
    std::vector<FontInfo *> results = {fi};

    EXPECT_CALL(*mock_scanner, scan(100000))
        .WillOnce(::testing::Return(results));

    PopplerFontsIter *iter = nullptr;
    gboolean result = poppler_font_info_scan(&font_info, 100000, &iter);

    EXPECT_EQ(result, TRUE);
    EXPECT_NE(iter, nullptr);

    delete iter;
    delete fi;
}

// Test: Existing iter pointer is overwritten with nullptr when no fonts found
TEST_F(PopplerFontInfoScanTest_2236, OverwritesExistingIterWithNull_WhenNoFonts_2236)
{
    std::vector<FontInfo *> empty_results;

    EXPECT_CALL(*mock_scanner, scan(1))
        .WillOnce(::testing::Return(empty_results));

    // Set iter to a non-null value to verify it gets overwritten
    PopplerFontsIter dummy;
    PopplerFontsIter *iter = &dummy;

    gboolean result = poppler_font_info_scan(&font_info, 1, &iter);

    EXPECT_EQ(result, FALSE);
    EXPECT_EQ(iter, nullptr);
}
