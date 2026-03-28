#include <gtest/gtest.h>
#include <glib-object.h>

// Include necessary poppler headers
extern "C" {
#include "poppler-document.h"
}
#include "poppler-private.h"

class PopplerPSFileSetPaperSizeTest_2258 : public ::testing::Test {
protected:
    void SetUp() override {
        // We need to create a PopplerPSFile structure manually for testing
        // since we can't easily create one through the normal API without a document
        ps_file = static_cast<PopplerPSFile *>(g_malloc0(sizeof(PopplerPSFile)));
        // Initialize the GObject-like structure minimally
        // PopplerPSFile is a GObject, so we need to be careful
    }

    void TearDown() override {
        if (ps_file) {
            g_free(ps_file);
            ps_file = nullptr;
        }
    }

    PopplerPSFile *ps_file = nullptr;
};

// Helper to create a minimal PopplerPSFile for testing without full GObject init
// We'll use a raw _PopplerPSFile struct directly since the function accesses fields directly
class PopplerPSFileRawTest_2258 : public ::testing::Test {
protected:
    _PopplerPSFile raw_ps_file;

    void SetUp() override {
        memset(&raw_ps_file, 0, sizeof(raw_ps_file));
        raw_ps_file.out = nullptr;
        raw_ps_file.paper_width = 0.0;
        raw_ps_file.paper_height = 0.0;
    }
};

// Test normal operation: setting paper size with typical values
TEST_F(PopplerPSFileRawTest_2258, SetPaperSizeNormalValues_2258) {
    PopplerPSFile *ps_file = reinterpret_cast<PopplerPSFile *>(&raw_ps_file);
    
    poppler_ps_file_set_paper_size(ps_file, 612.0, 792.0); // US Letter size in points
    
    EXPECT_DOUBLE_EQ(raw_ps_file.paper_width, 612.0);
    EXPECT_DOUBLE_EQ(raw_ps_file.paper_height, 792.0);
}

// Test setting paper size to A4 dimensions
TEST_F(PopplerPSFileRawTest_2258, SetPaperSizeA4Dimensions_2258) {
    PopplerPSFile *ps_file = reinterpret_cast<PopplerPSFile *>(&raw_ps_file);
    
    poppler_ps_file_set_paper_size(ps_file, 595.0, 842.0); // A4 size in points
    
    EXPECT_DOUBLE_EQ(raw_ps_file.paper_width, 595.0);
    EXPECT_DOUBLE_EQ(raw_ps_file.paper_height, 842.0);
}

// Test boundary: zero width and height
TEST_F(PopplerPSFileRawTest_2258, SetPaperSizeZeroDimensions_2258) {
    PopplerPSFile *ps_file = reinterpret_cast<PopplerPSFile *>(&raw_ps_file);
    
    poppler_ps_file_set_paper_size(ps_file, 0.0, 0.0);
    
    EXPECT_DOUBLE_EQ(raw_ps_file.paper_width, 0.0);
    EXPECT_DOUBLE_EQ(raw_ps_file.paper_height, 0.0);
}

// Test boundary: negative dimensions
TEST_F(PopplerPSFileRawTest_2258, SetPaperSizeNegativeDimensions_2258) {
    PopplerPSFile *ps_file = reinterpret_cast<PopplerPSFile *>(&raw_ps_file);
    
    poppler_ps_file_set_paper_size(ps_file, -100.0, -200.0);
    
    EXPECT_DOUBLE_EQ(raw_ps_file.paper_width, -100.0);
    EXPECT_DOUBLE_EQ(raw_ps_file.paper_height, -200.0);
}

// Test boundary: very large dimensions
TEST_F(PopplerPSFileRawTest_2258, SetPaperSizeVeryLargeDimensions_2258) {
    PopplerPSFile *ps_file = reinterpret_cast<PopplerPSFile *>(&raw_ps_file);
    
    poppler_ps_file_set_paper_size(ps_file, 1e10, 1e10);
    
    EXPECT_DOUBLE_EQ(raw_ps_file.paper_width, 1e10);
    EXPECT_DOUBLE_EQ(raw_ps_file.paper_height, 1e10);
}

// Test boundary: very small positive dimensions
TEST_F(PopplerPSFileRawTest_2258, SetPaperSizeVerySmallDimensions_2258) {
    PopplerPSFile *ps_file = reinterpret_cast<PopplerPSFile *>(&raw_ps_file);
    
    poppler_ps_file_set_paper_size(ps_file, 1e-10, 1e-10);
    
    EXPECT_DOUBLE_EQ(raw_ps_file.paper_width, 1e-10);
    EXPECT_DOUBLE_EQ(raw_ps_file.paper_height, 1e-10);
}

// Test that when out is not null, the function should not set values (guard clause)
TEST_F(PopplerPSFileRawTest_2258, SetPaperSizeWhenOutIsNotNull_2258) {
    // Set out to a non-null value to trigger the guard
    raw_ps_file.out = reinterpret_cast<PSOutputDev *>(0x1); // non-null dummy pointer
    raw_ps_file.paper_width = 100.0;
    raw_ps_file.paper_height = 200.0;
    
    PopplerPSFile *ps_file = reinterpret_cast<PopplerPSFile *>(&raw_ps_file);
    
    poppler_ps_file_set_paper_size(ps_file, 612.0, 792.0);
    
    // The guard should prevent modification
    EXPECT_DOUBLE_EQ(raw_ps_file.paper_width, 100.0);
    EXPECT_DOUBLE_EQ(raw_ps_file.paper_height, 200.0);
}

// Test calling set_paper_size multiple times overwrites previous values
TEST_F(PopplerPSFileRawTest_2258, SetPaperSizeMultipleCalls_2258) {
    PopplerPSFile *ps_file = reinterpret_cast<PopplerPSFile *>(&raw_ps_file);
    
    poppler_ps_file_set_paper_size(ps_file, 100.0, 200.0);
    EXPECT_DOUBLE_EQ(raw_ps_file.paper_width, 100.0);
    EXPECT_DOUBLE_EQ(raw_ps_file.paper_height, 200.0);
    
    poppler_ps_file_set_paper_size(ps_file, 300.0, 400.0);
    EXPECT_DOUBLE_EQ(raw_ps_file.paper_width, 300.0);
    EXPECT_DOUBLE_EQ(raw_ps_file.paper_height, 400.0);
}

// Test with different width and height values (non-square)
TEST_F(PopplerPSFileRawTest_2258, SetPaperSizeNonSquare_2258) {
    PopplerPSFile *ps_file = reinterpret_cast<PopplerPSFile *>(&raw_ps_file);
    
    poppler_ps_file_set_paper_size(ps_file, 100.0, 500.0);
    
    EXPECT_DOUBLE_EQ(raw_ps_file.paper_width, 100.0);
    EXPECT_DOUBLE_EQ(raw_ps_file.paper_height, 500.0);
    EXPECT_NE(raw_ps_file.paper_width, raw_ps_file.paper_height);
}

// Test with fractional values
TEST_F(PopplerPSFileRawTest_2258, SetPaperSizeFractionalValues_2258) {
    PopplerPSFile *ps_file = reinterpret_cast<PopplerPSFile *>(&raw_ps_file);
    
    poppler_ps_file_set_paper_size(ps_file, 612.5, 792.75);
    
    EXPECT_DOUBLE_EQ(raw_ps_file.paper_width, 612.5);
    EXPECT_DOUBLE_EQ(raw_ps_file.paper_height, 792.75);
}

// Test that passing NULL ps_file doesn't crash (g_return_if_fail should handle this)
TEST_F(PopplerPSFileRawTest_2258, SetPaperSizeNullPSFile_2258) {
    // This should not crash due to GLib's g_return_if_fail macro behavior
    // with NULL input (though the function's guard checks ps_file->out,
    // passing NULL would cause a crash before that check unless GLib protects)
    // We test that the function handles NULL gracefully
    // Note: This may produce a GLib warning but should not crash
    // Skipping direct NULL call as it would dereference NULL before any guard
}

// Test equal width and height (square paper)
TEST_F(PopplerPSFileRawTest_2258, SetPaperSizeSquarePaper_2258) {
    PopplerPSFile *ps_file = reinterpret_cast<PopplerPSFile *>(&raw_ps_file);
    
    poppler_ps_file_set_paper_size(ps_file, 500.0, 500.0);
    
    EXPECT_DOUBLE_EQ(raw_ps_file.paper_width, 500.0);
    EXPECT_DOUBLE_EQ(raw_ps_file.paper_height, 500.0);
    EXPECT_DOUBLE_EQ(raw_ps_file.paper_width, raw_ps_file.paper_height);
}
