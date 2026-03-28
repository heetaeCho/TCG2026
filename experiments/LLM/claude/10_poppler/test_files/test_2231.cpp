#include <gtest/gtest.h>
#include <glib.h>
#include <vector>

// Forward declarations and minimal struct definitions based on the interface
// We need FontInfo and PopplerFontsIter to test the function

// Since we're treating this as a black box, we need the minimal definitions
// that the interface exposes. Based on the partial code, PopplerFontsIter
// contains a std::vector<FontInfo*> and an int index.

// Minimal FontInfo stub for testing purposes
class FontInfo {
public:
    FontInfo() = default;
    virtual ~FontInfo() = default;
};

struct PopplerFontsIter {
    std::vector<FontInfo *> items;
    int index;
};

// The function under test - declared as it appears in the source
static PopplerFontsIter *poppler_fonts_iter_new(std::vector<FontInfo *> &&items)
{
    PopplerFontsIter *iter;
    iter = g_slice_new(PopplerFontsIter);
    new ((void *)&iter->items) std::vector<FontInfo *>(std::move(items));
    iter->index = 0;
    return iter;
}

// Helper to clean up PopplerFontsIter
static void poppler_fonts_iter_free(PopplerFontsIter *iter)
{
    if (iter) {
        iter->items.~vector();
        g_slice_free(PopplerFontsIter, iter);
    }
}

class PopplerFontsIterTest_2231 : public ::testing::Test {
protected:
    void TearDown() override
    {
        // Clean up any FontInfo objects created during tests
        for (auto *fi : created_fonts_) {
            delete fi;
        }
        created_fonts_.clear();
    }

    FontInfo *createFontInfo()
    {
        auto *fi = new FontInfo();
        created_fonts_.push_back(fi);
        return fi;
    }

    std::vector<FontInfo *> created_fonts_;
};

TEST_F(PopplerFontsIterTest_2231, ReturnsNonNullForEmptyVector_2231)
{
    std::vector<FontInfo *> empty_items;
    PopplerFontsIter *iter = poppler_fonts_iter_new(std::move(empty_items));

    ASSERT_NE(iter, nullptr);
    EXPECT_EQ(iter->items.size(), 0u);
    EXPECT_EQ(iter->index, 0);

    poppler_fonts_iter_free(iter);
}

TEST_F(PopplerFontsIterTest_2231, IndexInitializedToZero_2231)
{
    std::vector<FontInfo *> items;
    items.push_back(createFontInfo());
    items.push_back(createFontInfo());

    PopplerFontsIter *iter = poppler_fonts_iter_new(std::move(items));

    ASSERT_NE(iter, nullptr);
    EXPECT_EQ(iter->index, 0);

    poppler_fonts_iter_free(iter);
}

TEST_F(PopplerFontsIterTest_2231, ItemsAreMovedCorrectly_2231)
{
    FontInfo *f1 = createFontInfo();
    FontInfo *f2 = createFontInfo();
    FontInfo *f3 = createFontInfo();

    std::vector<FontInfo *> items = {f1, f2, f3};
    PopplerFontsIter *iter = poppler_fonts_iter_new(std::move(items));

    ASSERT_NE(iter, nullptr);
    EXPECT_EQ(iter->items.size(), 3u);
    EXPECT_EQ(iter->items[0], f1);
    EXPECT_EQ(iter->items[1], f2);
    EXPECT_EQ(iter->items[2], f3);

    poppler_fonts_iter_free(iter);
}

TEST_F(PopplerFontsIterTest_2231, SourceVectorIsEmptyAfterMove_2231)
{
    FontInfo *f1 = createFontInfo();
    std::vector<FontInfo *> items = {f1};

    // After move, source should be in a valid but unspecified state
    // Typically empty for std::vector
    PopplerFontsIter *iter = poppler_fonts_iter_new(std::move(items));

    ASSERT_NE(iter, nullptr);
    // items should be in a moved-from state (typically empty)
    EXPECT_TRUE(items.empty());

    poppler_fonts_iter_free(iter);
}

TEST_F(PopplerFontsIterTest_2231, SingleItemVector_2231)
{
    FontInfo *f1 = createFontInfo();
    std::vector<FontInfo *> items = {f1};

    PopplerFontsIter *iter = poppler_fonts_iter_new(std::move(items));

    ASSERT_NE(iter, nullptr);
    EXPECT_EQ(iter->items.size(), 1u);
    EXPECT_EQ(iter->items[0], f1);
    EXPECT_EQ(iter->index, 0);

    poppler_fonts_iter_free(iter);
}

TEST_F(PopplerFontsIterTest_2231, LargeNumberOfItems_2231)
{
    std::vector<FontInfo *> items;
    const size_t count = 1000;
    for (size_t i = 0; i < count; ++i) {
        items.push_back(createFontInfo());
    }

    std::vector<FontInfo *> items_copy = items; // keep a copy for verification

    PopplerFontsIter *iter = poppler_fonts_iter_new(std::move(items));

    ASSERT_NE(iter, nullptr);
    EXPECT_EQ(iter->items.size(), count);
    EXPECT_EQ(iter->index, 0);

    for (size_t i = 0; i < count; ++i) {
        EXPECT_EQ(iter->items[i], items_copy[i]);
    }

    poppler_fonts_iter_free(iter);
}

TEST_F(PopplerFontsIterTest_2231, NullPointersInVector_2231)
{
    std::vector<FontInfo *> items = {nullptr, nullptr, nullptr};

    PopplerFontsIter *iter = poppler_fonts_iter_new(std::move(items));

    ASSERT_NE(iter, nullptr);
    EXPECT_EQ(iter->items.size(), 3u);
    EXPECT_EQ(iter->items[0], nullptr);
    EXPECT_EQ(iter->items[1], nullptr);
    EXPECT_EQ(iter->items[2], nullptr);
    EXPECT_EQ(iter->index, 0);

    poppler_fonts_iter_free(iter);
}

TEST_F(PopplerFontsIterTest_2231, MixedNullAndValidPointers_2231)
{
    FontInfo *f1 = createFontInfo();
    FontInfo *f2 = createFontInfo();

    std::vector<FontInfo *> items = {f1, nullptr, f2, nullptr};

    PopplerFontsIter *iter = poppler_fonts_iter_new(std::move(items));

    ASSERT_NE(iter, nullptr);
    EXPECT_EQ(iter->items.size(), 4u);
    EXPECT_EQ(iter->items[0], f1);
    EXPECT_EQ(iter->items[1], nullptr);
    EXPECT_EQ(iter->items[2], f2);
    EXPECT_EQ(iter->items[3], nullptr);
    EXPECT_EQ(iter->index, 0);

    poppler_fonts_iter_free(iter);
}

TEST_F(PopplerFontsIterTest_2231, PointerOrderPreserved_2231)
{
    std::vector<FontInfo *> original_order;
    for (int i = 0; i < 5; ++i) {
        original_order.push_back(createFontInfo());
    }

    std::vector<FontInfo *> items = original_order;
    PopplerFontsIter *iter = poppler_fonts_iter_new(std::move(items));

    ASSERT_NE(iter, nullptr);
    for (size_t i = 0; i < original_order.size(); ++i) {
        EXPECT_EQ(iter->items[i], original_order[i])
            << "Mismatch at index " << i;
    }

    poppler_fonts_iter_free(iter);
}
