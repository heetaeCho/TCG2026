#include <gtest/gtest.h>
#include <cstring>

// Forward declarations and minimal type definitions needed for testing
// Based on the provided interface

extern "C" {
#include <glib-object.h>
}

// We need the poppler glib headers
#include "poppler-document.h"

// Include private header to access struct fields for verification
#include "poppler-private.h"

class PopplerFontInfoInitTest_2233 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that poppler_font_info_init sets document to nullptr
TEST_F(PopplerFontInfoInitTest_2233, InitSetsDocumentToNull_2233)
{
    PopplerFontInfo font_info;
    // Set to non-null values first to verify init actually changes them
    font_info.document = reinterpret_cast<PopplerDocument *>(0xDEADBEEF);
    font_info.scanner = reinterpret_cast<FontInfoScanner *>(0xDEADBEEF);

    // Call the init function (this is a GObject instance init function)
    // We simulate calling it directly
    poppler_font_info_init(&font_info);

    EXPECT_EQ(font_info.document, nullptr);
}

// Test that poppler_font_info_init sets scanner to nullptr
TEST_F(PopplerFontInfoInitTest_2233, InitSetsScannerToNull_2233)
{
    PopplerFontInfo font_info;
    font_info.document = reinterpret_cast<PopplerDocument *>(0xDEADBEEF);
    font_info.scanner = reinterpret_cast<FontInfoScanner *>(0xDEADBEEF);

    poppler_font_info_init(&font_info);

    EXPECT_EQ(font_info.scanner, nullptr);
}

// Test that poppler_font_info_init sets both fields to nullptr simultaneously
TEST_F(PopplerFontInfoInitTest_2233, InitSetsBothFieldsToNull_2233)
{
    PopplerFontInfo font_info;
    font_info.document = reinterpret_cast<PopplerDocument *>(0x12345678);
    font_info.scanner = reinterpret_cast<FontInfoScanner *>(0x87654321);

    poppler_font_info_init(&font_info);

    EXPECT_EQ(font_info.document, nullptr);
    EXPECT_EQ(font_info.scanner, nullptr);
}

// Test that calling init on an already initialized (zeroed) struct is idempotent
TEST_F(PopplerFontInfoInitTest_2233, InitIsIdempotent_2233)
{
    PopplerFontInfo font_info;
    memset(&font_info, 0, sizeof(font_info));

    poppler_font_info_init(&font_info);

    EXPECT_EQ(font_info.document, nullptr);
    EXPECT_EQ(font_info.scanner, nullptr);

    // Call again
    poppler_font_info_init(&font_info);

    EXPECT_EQ(font_info.document, nullptr);
    EXPECT_EQ(font_info.scanner, nullptr);
}

// Test that calling init multiple times with different prior values always resets to null
TEST_F(PopplerFontInfoInitTest_2233, InitResetsAfterMultipleCalls_2233)
{
    PopplerFontInfo font_info;

    for (int i = 1; i <= 5; ++i) {
        font_info.document = reinterpret_cast<PopplerDocument *>(static_cast<uintptr_t>(i));
        font_info.scanner = reinterpret_cast<FontInfoScanner *>(static_cast<uintptr_t>(i * 100));

        poppler_font_info_init(&font_info);

        EXPECT_EQ(font_info.document, nullptr) << "Failed on iteration " << i;
        EXPECT_EQ(font_info.scanner, nullptr) << "Failed on iteration " << i;
    }
}

// Boundary: Test with maximum pointer values
TEST_F(PopplerFontInfoInitTest_2233, InitResetsMaxPointerValues_2233)
{
    PopplerFontInfo font_info;
    font_info.document = reinterpret_cast<PopplerDocument *>(UINTPTR_MAX);
    font_info.scanner = reinterpret_cast<FontInfoScanner *>(UINTPTR_MAX);

    poppler_font_info_init(&font_info);

    EXPECT_EQ(font_info.document, nullptr);
    EXPECT_EQ(font_info.scanner, nullptr);
}
