#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "poppler-document.cc"  // Include the header or source file containing the implementation



// Mocking dependencies if any, but in this case, there are none to mock.



TEST(PopplerFontsIterTest_2231, NewIterWithEmptyItems_2231) {

    std::vector<FontInfo*> items;

    PopplerFontsIter* iter = poppler_fonts_iter_new(std::move(items));

    EXPECT_EQ(iter->index, 0);

    EXPECT_TRUE(iter->items.empty());

    g_slice_free(PopplerFontsIter, iter);  // Clean up

}



TEST(PopplerFontsIterTest_2231, NewIterWithNonEmptyItems_2231) {

    std::vector<FontInfo*> items = {new FontInfo(), new FontInfo()};

    PopplerFontsIter* iter = poppler_fonts_iter_new(std::move(items));

    EXPECT_EQ(iter->index, 0);

    EXPECT_EQ(iter->items.size(), 2);

    g_slice_free(PopplerFontsIter, iter);  // Clean up

}



TEST(PopplerFontsIterTest_2231, NewIterWithSingleItem_2231) {

    std::vector<FontInfo*> items = {new FontInfo()};

    PopplerFontsIter* iter = poppler_fonts_iter_new(std::move(items));

    EXPECT_EQ(iter->index, 0);

    EXPECT_EQ(iter->items.size(), 1);

    g_slice_free(PopplerFontsIter, iter);  // Clean up

}



// Note: The provided struct definition seems incorrect as 'items' should be a std::vector<FontInfo*> not an int.

// Assuming the correct structure definition is:

// struct _PopplerFontsIter {

//     std::vector<FontInfo*> items;

//     int index;

// };



TEST(PopplerFontsIterTest_2231, VerifyItemsNotCopied_2231) {

    std::vector<FontInfo*> original_items = {new FontInfo(), new FontInfo()};

    PopplerFontsIter* iter = poppler_fonts_iter_new(std::move(original_items));

    EXPECT_TRUE(original_items.empty());  // Original vector should be empty after move

    EXPECT_EQ(iter->items.size(), 2);

    g_slice_free(PopplerFontsIter, iter);  // Clean up

}

```


