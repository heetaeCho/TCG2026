#include <gtest/gtest.h>

#include <gmock/gmock.h>



// Assuming the necessary headers and types are included or declared as per the context.

extern "C" {

    struct PopplerFontInfo;

    struct _PopplerFontsIter;

    typedef struct _PopplerFontsIter* PopplerFontsIter;

    gboolean poppler_font_info_scan(PopplerFontInfo *font_info, int n_pages, PopplerFontsIter **iter);

}



class FontInfoScannerMock {

public:

    MOCK_METHOD(std::vector<FontInfo*>, scan, (int), ());

};



using ::testing::Return;

using ::testing::NotNull;



TEST_F(FontInfoScannerTest_2236, ScanReturnsEmptyVector_2236) {

    PopplerFontInfo font_info;

    FontInfoScannerMock scanner_mock;

    font_info.scanner = &scanner_mock;



    EXPECT_CALL(scanner_mock, scan(1)).WillOnce(Return(std::vector<FontInfo*>()));



    PopplerFontsIter *iter = nullptr;

    gboolean result = poppler_font_info_scan(&font_info, 1, &iter);



    ASSERT_FALSE(result);

    EXPECT_EQ(iter, nullptr);

}



TEST_F(FontInfoScannerTest_2236, ScanReturnsNonEmptyVector_2236) {

    PopplerFontInfo font_info;

    FontInfoScannerMock scanner_mock;

    font_info.scanner = &scanner_mock;



    std::vector<FontInfo*> items = {new FontInfo(), new FontInfo()};

    EXPECT_CALL(scanner_mock, scan(2)).WillOnce(Return(items));



    PopplerFontsIter *iter = nullptr;

    gboolean result = poppler_font_info_scan(&font_info, 2, &iter);



    ASSERT_TRUE(result);

    EXPECT_NE(iter, nullptr);

    // Assuming poppler_fonts_iter_new initializes items count correctly.

    EXPECT_EQ(iter->items, 2);



    // Clean up allocated FontInfo objects

    for (FontInfo* item : items) {

        delete item;

    }

}



TEST_F(FontInfoScannerTest_2236, NullIterPointerProvided_2236) {

    PopplerFontInfo font_info;

    FontInfoScannerMock scanner_mock;

    font_info.scanner = &scanner_mock;



    EXPECT_CALL(scanner_mock, scan(1)).WillOnce(Return(std::vector<FontInfo*>()));



    gboolean result = poppler_font_info_scan(&font_info, 1, nullptr);



    ASSERT_FALSE(result);

}



TEST_F(FontInfoScannerTest_2236, ScanWithZeroPages_2236) {

    PopplerFontInfo font_info;

    FontInfoScannerMock scanner_mock;

    font_info.scanner = &scanner_mock;



    EXPECT_CALL(scanner_mock, scan(0)).WillOnce(Return(std::vector<FontInfo*>()));



    PopplerFontsIter *iter = nullptr;

    gboolean result = poppler_font_info_scan(&font_info, 0, &iter);



    ASSERT_FALSE(result);

    EXPECT_EQ(iter, nullptr);

}



TEST_F(FontInfoScannerTest_2236, ScanWithNegativePages_2236) {

    PopplerFontInfo font_info;

    FontInfoScannerMock scanner_mock;

    font_info.scanner = &scanner_mock;



    EXPECT_CALL(scanner_mock, scan(-1)).WillOnce(Return(std::vector<FontInfo*>()));



    PopplerFontsIter *iter = nullptr;

    gboolean result = poppler_font_info_scan(&font_info, -1, &iter);



    ASSERT_FALSE(result);

    EXPECT_EQ(iter, nullptr);

}
