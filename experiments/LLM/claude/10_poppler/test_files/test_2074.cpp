#include <gtest/gtest.h>
#include <gmock/gmock.h>

extern "C" {
#include <poppler.h>
}

#include <cstring>
#include <cstdio>
#include <memory>

class PopplerAnnotSetRectangleTest_2074 : public ::testing::Test {
protected:
    PopplerDocument *doc = nullptr;
    PopplerPage *page = nullptr;

    void SetUp() override {
        // Create a minimal PDF in memory to get a valid document/page/annot
        // We need a real PDF document to create proper annotations
        GError *error = nullptr;
        
        // Try to create a simple PDF. We'll use a minimal PDF buffer.
        const char *minimal_pdf = 
            "%PDF-1.4\n"
            "1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
            "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
            "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R/Resources<<>>>>endobj\n"
            "xref\n"
            "0 4\n"
            "0000000000 65535 f \n"
            "0000000009 00000 n \n"
            "0000000058 00000 n \n"
            "0000000115 00000 n \n"
            "trailer<</Size 4/Root 1 0 R>>\n"
            "startxref\n"
            "206\n"
            "%%EOF\n";

        doc = poppler_document_new_from_data(const_cast<char*>(minimal_pdf), 
                                              strlen(minimal_pdf), nullptr, &error);
        if (doc) {
            page = poppler_document_get_page(doc, 0);
        }
    }

    void TearDown() override {
        if (page) {
            g_object_unref(page);
        }
        if (doc) {
            g_object_unref(doc);
        }
    }
};

// Test that passing NULL annot doesn't crash (g_return_if_fail should handle it)
TEST_F(PopplerAnnotSetRectangleTest_2074, NullAnnotDoesNotCrash_2074) {
    PopplerRectangle rect;
    rect.x1 = 10.0;
    rect.y1 = 20.0;
    rect.x2 = 100.0;
    rect.y2 = 200.0;

    // Should return without crashing due to g_return_if_fail
    poppler_annot_set_rectangle(nullptr, &rect);
}

// Test that passing NULL rectangle doesn't crash
TEST_F(PopplerAnnotSetRectangleTest_2074, NullRectDoesNotCrash_2074) {
    if (!page) {
        GTEST_SKIP() << "Could not create test PDF page";
    }

    // Create an annotation on the page
    PopplerRectangle rect;
    rect.x1 = 10.0;
    rect.y1 = 20.0;
    rect.x2 = 100.0;
    rect.y2 = 200.0;

    PopplerAnnot *annot = reinterpret_cast<PopplerAnnot*>(
        poppler_annot_text_new(doc, &rect));
    
    if (!annot) {
        GTEST_SKIP() << "Could not create test annotation";
    }

    // Should return without crashing due to g_return_if_fail
    poppler_annot_set_rectangle(annot, nullptr);
    
    g_object_unref(annot);
}

// Test setting rectangle on a valid annotation
TEST_F(PopplerAnnotSetRectangleTest_2074, SetRectangleOnValidAnnot_2074) {
    if (!page || !doc) {
        GTEST_SKIP() << "Could not create test PDF page";
    }

    PopplerRectangle initial_rect;
    initial_rect.x1 = 10.0;
    initial_rect.y1 = 20.0;
    initial_rect.x2 = 100.0;
    initial_rect.y2 = 200.0;

    PopplerAnnot *annot = reinterpret_cast<PopplerAnnot*>(
        poppler_annot_text_new(doc, &initial_rect));

    if (!annot) {
        GTEST_SKIP() << "Could not create test annotation";
    }

    PopplerRectangle new_rect;
    new_rect.x1 = 50.0;
    new_rect.y1 = 60.0;
    new_rect.x2 = 200.0;
    new_rect.y2 = 300.0;

    poppler_annot_set_rectangle(annot, &new_rect);

    // Verify the rectangle was set by reading it back
    PopplerRectangle result_rect;
    poppler_annot_get_rectangle(annot, &result_rect);

    EXPECT_DOUBLE_EQ(result_rect.x1, new_rect.x1);
    EXPECT_DOUBLE_EQ(result_rect.y1, new_rect.y1);
    EXPECT_DOUBLE_EQ(result_rect.x2, new_rect.x2);
    EXPECT_DOUBLE_EQ(result_rect.y2, new_rect.y2);

    g_object_unref(annot);
}

// Test setting rectangle with zero dimensions
TEST_F(PopplerAnnotSetRectangleTest_2074, SetRectangleZeroDimensions_2074) {
    if (!page || !doc) {
        GTEST_SKIP() << "Could not create test PDF page";
    }

    PopplerRectangle initial_rect;
    initial_rect.x1 = 10.0;
    initial_rect.y1 = 20.0;
    initial_rect.x2 = 100.0;
    initial_rect.y2 = 200.0;

    PopplerAnnot *annot = reinterpret_cast<PopplerAnnot*>(
        poppler_annot_text_new(doc, &initial_rect));

    if (!annot) {
        GTEST_SKIP() << "Could not create test annotation";
    }

    PopplerRectangle zero_rect;
    zero_rect.x1 = 0.0;
    zero_rect.y1 = 0.0;
    zero_rect.x2 = 0.0;
    zero_rect.y2 = 0.0;

    poppler_annot_set_rectangle(annot, &zero_rect);

    PopplerRectangle result_rect;
    poppler_annot_get_rectangle(annot, &result_rect);

    EXPECT_DOUBLE_EQ(result_rect.x1, 0.0);
    EXPECT_DOUBLE_EQ(result_rect.y1, 0.0);
    EXPECT_DOUBLE_EQ(result_rect.x2, 0.0);
    EXPECT_DOUBLE_EQ(result_rect.y2, 0.0);

    g_object_unref(annot);
}

// Test setting rectangle with negative coordinates
TEST_F(PopplerAnnotSetRectangleTest_2074, SetRectangleNegativeCoords_2074) {
    if (!page || !doc) {
        GTEST_SKIP() << "Could not create test PDF page";
    }

    PopplerRectangle initial_rect;
    initial_rect.x1 = 10.0;
    initial_rect.y1 = 20.0;
    initial_rect.x2 = 100.0;
    initial_rect.y2 = 200.0;

    PopplerAnnot *annot = reinterpret_cast<PopplerAnnot*>(
        poppler_annot_text_new(doc, &initial_rect));

    if (!annot) {
        GTEST_SKIP() << "Could not create test annotation";
    }

    PopplerRectangle neg_rect;
    neg_rect.x1 = -50.0;
    neg_rect.y1 = -30.0;
    neg_rect.x2 = -10.0;
    neg_rect.y2 = -5.0;

    poppler_annot_set_rectangle(annot, &neg_rect);

    PopplerRectangle result_rect;
    poppler_annot_get_rectangle(annot, &result_rect);

    EXPECT_DOUBLE_EQ(result_rect.x1, neg_rect.x1);
    EXPECT_DOUBLE_EQ(result_rect.y1, neg_rect.y1);
    EXPECT_DOUBLE_EQ(result_rect.x2, neg_rect.x2);
    EXPECT_DOUBLE_EQ(result_rect.y2, neg_rect.y2);

    g_object_unref(annot);
}

// Test setting rectangle with very large coordinates
TEST_F(PopplerAnnotSetRectangleTest_2074, SetRectangleLargeCoords_2074) {
    if (!page || !doc) {
        GTEST_SKIP() << "Could not create test PDF page";
    }

    PopplerRectangle initial_rect;
    initial_rect.x1 = 10.0;
    initial_rect.y1 = 20.0;
    initial_rect.x2 = 100.0;
    initial_rect.y2 = 200.0;

    PopplerAnnot *annot = reinterpret_cast<PopplerAnnot*>(
        poppler_annot_text_new(doc, &initial_rect));

    if (!annot) {
        GTEST_SKIP() << "Could not create test annotation";
    }

    PopplerRectangle large_rect;
    large_rect.x1 = 1e10;
    large_rect.y1 = 1e10;
    large_rect.x2 = 2e10;
    large_rect.y2 = 2e10;

    poppler_annot_set_rectangle(annot, &large_rect);

    PopplerRectangle result_rect;
    poppler_annot_get_rectangle(annot, &result_rect);

    EXPECT_DOUBLE_EQ(result_rect.x1, large_rect.x1);
    EXPECT_DOUBLE_EQ(result_rect.y1, large_rect.y1);
    EXPECT_DOUBLE_EQ(result_rect.x2, large_rect.x2);
    EXPECT_DOUBLE_EQ(result_rect.y2, large_rect.y2);

    g_object_unref(annot);
}

// Test setting rectangle multiple times overwrites previous value
TEST_F(PopplerAnnotSetRectangleTest_2074, SetRectangleMultipleTimes_2074) {
    if (!page || !doc) {
        GTEST_SKIP() << "Could not create test PDF page";
    }

    PopplerRectangle initial_rect;
    initial_rect.x1 = 10.0;
    initial_rect.y1 = 20.0;
    initial_rect.x2 = 100.0;
    initial_rect.y2 = 200.0;

    PopplerAnnot *annot = reinterpret_cast<PopplerAnnot*>(
        poppler_annot_text_new(doc, &initial_rect));

    if (!annot) {
        GTEST_SKIP() << "Could not create test annotation";
    }

    // Set first rectangle
    PopplerRectangle rect1;
    rect1.x1 = 5.0;
    rect1.y1 = 10.0;
    rect1.x2 = 50.0;
    rect1.y2 = 100.0;
    poppler_annot_set_rectangle(annot, &rect1);

    // Set second rectangle
    PopplerRectangle rect2;
    rect2.x1 = 15.0;
    rect2.y1 = 25.0;
    rect2.x2 = 150.0;
    rect2.y2 = 250.0;
    poppler_annot_set_rectangle(annot, &rect2);

    // Should reflect the latest rectangle
    PopplerRectangle result_rect;
    poppler_annot_get_rectangle(annot, &result_rect);

    EXPECT_DOUBLE_EQ(result_rect.x1, rect2.x1);
    EXPECT_DOUBLE_EQ(result_rect.y1, rect2.y1);
    EXPECT_DOUBLE_EQ(result_rect.x2, rect2.x2);
    EXPECT_DOUBLE_EQ(result_rect.y2, rect2.y2);

    g_object_unref(annot);
}

// Test setting rectangle where x1 > x2 and y1 > y2 (inverted)
TEST_F(PopplerAnnotSetRectangleTest_2074, SetRectangleInvertedCoords_2074) {
    if (!page || !doc) {
        GTEST_SKIP() << "Could not create test PDF page";
    }

    PopplerRectangle initial_rect;
    initial_rect.x1 = 10.0;
    initial_rect.y1 = 20.0;
    initial_rect.x2 = 100.0;
    initial_rect.y2 = 200.0;

    PopplerAnnot *annot = reinterpret_cast<PopplerAnnot*>(
        poppler_annot_text_new(doc, &initial_rect));

    if (!annot) {
        GTEST_SKIP() << "Could not create test annotation";
    }

    PopplerRectangle inverted_rect;
    inverted_rect.x1 = 200.0;
    inverted_rect.y1 = 300.0;
    inverted_rect.x2 = 50.0;
    inverted_rect.y2 = 60.0;

    // Should not crash even with inverted coordinates
    poppler_annot_set_rectangle(annot, &inverted_rect);

    PopplerRectangle result_rect;
    poppler_annot_get_rectangle(annot, &result_rect);

    // The function stores the coordinates as provided (possibly adjusted by crop_box)
    EXPECT_DOUBLE_EQ(result_rect.x1, inverted_rect.x1);
    EXPECT_DOUBLE_EQ(result_rect.y1, inverted_rect.y1);
    EXPECT_DOUBLE_EQ(result_rect.x2, inverted_rect.x2);
    EXPECT_DOUBLE_EQ(result_rect.y2, inverted_rect.y2);

    g_object_unref(annot);
}

// Test with annotation added to a page
TEST_F(PopplerAnnotSetRectangleTest_2074, SetRectangleAnnotOnPage_2074) {
    if (!page || !doc) {
        GTEST_SKIP() << "Could not create test PDF page";
    }

    PopplerRectangle initial_rect;
    initial_rect.x1 = 10.0;
    initial_rect.y1 = 20.0;
    initial_rect.x2 = 100.0;
    initial_rect.y2 = 200.0;

    PopplerAnnot *annot = reinterpret_cast<PopplerAnnot*>(
        poppler_annot_text_new(doc, &initial_rect));

    if (!annot) {
        GTEST_SKIP() << "Could not create test annotation";
    }

    // Add annotation to page
    poppler_page_add_annot(page, annot);

    PopplerRectangle new_rect;
    new_rect.x1 = 30.0;
    new_rect.y1 = 40.0;
    new_rect.x2 = 130.0;
    new_rect.y2 = 240.0;

    poppler_annot_set_rectangle(annot, &new_rect);

    PopplerRectangle result_rect;
    poppler_annot_get_rectangle(annot, &result_rect);

    // After adding to page, crop_box might affect the stored values
    // but get_rectangle should return the user-facing coordinates
    EXPECT_DOUBLE_EQ(result_rect.x1, new_rect.x1);
    EXPECT_DOUBLE_EQ(result_rect.y1, new_rect.y1);
    EXPECT_DOUBLE_EQ(result_rect.x2, new_rect.x2);
    EXPECT_DOUBLE_EQ(result_rect.y2, new_rect.y2);

    poppler_page_remove_annot(page, annot);
    g_object_unref(annot);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
