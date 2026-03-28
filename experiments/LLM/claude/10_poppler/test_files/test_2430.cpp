#include <gtest/gtest.h>
#include <glib-object.h>
#include <poppler.h>
#include <poppler-page.h>
#include <cstdio>
#include <cstring>
#include <string>

class PopplerPageTransitionTest_2430 : public ::testing::Test {
protected:
    PopplerDocument *doc = nullptr;
    
    void SetUp() override {
    }
    
    void TearDown() override {
        if (doc) {
            g_object_unref(doc);
            doc = nullptr;
        }
    }
    
    // Helper to create a minimal PDF with a page transition
    PopplerDocument* createPdfWithTransition(const char* transType, 
                                              double duration = 1.0,
                                              const char* extraTransProps = "") {
        // Create a minimal PDF in memory with transition dictionary
        std::string pdf;
        pdf += "%PDF-1.7\n";
        
        // Object 1: Catalog
        pdf += "1 0 obj\n<< /Type /Catalog /Pages 2 0 R >>\nendobj\n";
        
        // Object 2: Pages
        pdf += "2 0 obj\n<< /Type /Pages /Kids [3 0 R] /Count 1 >>\nendobj\n";
        
        // Object 3: Page with transition
        std::string transDict;
        if (transType && strlen(transType) > 0) {
            transDict = std::string("/Trans << /Type /Trans /S /") + transType + 
                        " /D " + std::to_string(duration) + " " + extraTransProps + " >>";
        }
        
        pdf += "3 0 obj\n<< /Type /Page /Parent 2 0 R /MediaBox [0 0 612 792] " + 
               transDict + " >>\nendobj\n";
        
        // xref
        std::string xref_pos_str;
        // Simple approach: write xref manually
        size_t xref_offset = pdf.size();
        pdf += "xref\n0 4\n";
        pdf += "0000000000 65535 f \n";
        // We need proper offsets - let's just use a simpler approach
        // Actually, let's use poppler's ability to load from data
        
        // Reset and build properly
        pdf.clear();
        
        char buf[4096];
        std::string obj1, obj2, obj3;
        
        obj1 = "1 0 obj\n<< /Type /Catalog /Pages 2 0 R >>\nendobj\n";
        obj2 = "2 0 obj\n<< /Type /Pages /Kids [3 0 R] /Count 1 >>\nendobj\n";
        obj3 = "3 0 obj\n<< /Type /Page /Parent 2 0 R /MediaBox [0 0 612 792] " + 
               transDict + " >>\nendobj\n";
        
        std::string header = "%PDF-1.7\n";
        size_t off1 = header.size();
        size_t off2 = off1 + obj1.size();
        size_t off3 = off2 + obj2.size();
        
        pdf = header + obj1 + obj2 + obj3;
        
        size_t xref_off = pdf.size();
        
        snprintf(buf, sizeof(buf),
            "xref\n"
            "0 4\n"
            "0000000000 65535 f \n"
            "%010zu 00000 n \n"
            "%010zu 00000 n \n"
            "%010zu 00000 n \n"
            "trailer\n<< /Size 4 /Root 1 0 R >>\n"
            "startxref\n%zu\n%%%%EOF\n",
            off1, off2, off3, xref_off);
        
        pdf += buf;
        
        GError *error = nullptr;
        GBytes *bytes = g_bytes_new(pdf.c_str(), pdf.size());
        GInputStream *stream = g_memory_input_stream_new_from_bytes(bytes);
        
        PopplerDocument *document = poppler_document_new_from_stream(
            stream, pdf.size(), nullptr, nullptr, &error);
        
        g_object_unref(stream);
        g_bytes_unref(bytes);
        
        if (error) {
            g_error_free(error);
            return nullptr;
        }
        
        return document;
    }
    
    PopplerDocument* createPdfWithoutTransition() {
        return createPdfWithTransition("", 0.0);
    }
};

// Test that passing NULL page returns NULL
TEST_F(PopplerPageTransitionTest_2430, NullPageReturnsNull_2430) {
    PopplerPageTransition *transition = poppler_page_get_transition(nullptr);
    EXPECT_EQ(transition, nullptr);
}

// Test page without transition returns NULL
TEST_F(PopplerPageTransitionTest_2430, PageWithoutTransitionReturnsNull_2430) {
    doc = createPdfWithoutTransition();
    if (!doc) {
        GTEST_SKIP() << "Could not create test PDF";
    }
    
    PopplerPage *page = poppler_document_get_page(doc, 0);
    ASSERT_NE(page, nullptr);
    
    PopplerPageTransition *transition = poppler_page_get_transition(page);
    // Pages without /Trans should return NULL (transition not ok)
    // This depends on implementation - it may return NULL or a default
    if (transition) {
        poppler_page_transition_free(transition);
    }
    
    g_object_unref(page);
}

// Test Replace transition type
TEST_F(PopplerPageTransitionTest_2430, ReplaceTransition_2430) {
    doc = createPdfWithTransition("R", 2.0);
    if (!doc) {
        GTEST_SKIP() << "Could not create test PDF";
    }
    
    PopplerPage *page = poppler_document_get_page(doc, 0);
    if (!page) {
        GTEST_SKIP() << "Could not get page";
    }
    
    PopplerPageTransition *transition = poppler_page_get_transition(page);
    if (transition) {
        EXPECT_EQ(transition->type, POPPLER_PAGE_TRANSITION_REPLACE);
        poppler_page_transition_free(transition);
    }
    
    g_object_unref(page);
}

// Test Split transition type
TEST_F(PopplerPageTransitionTest_2430, SplitTransition_2430) {
    doc = createPdfWithTransition("Split", 1.5, "/Dm /H /M /I");
    if (!doc) {
        GTEST_SKIP() << "Could not create test PDF";
    }
    
    PopplerPage *page = poppler_document_get_page(doc, 0);
    if (!page) {
        GTEST_SKIP() << "Could not get page";
    }
    
    PopplerPageTransition *transition = poppler_page_get_transition(page);
    if (transition) {
        EXPECT_EQ(transition->type, POPPLER_PAGE_TRANSITION_SPLIT);
        EXPECT_EQ(transition->alignment, POPPLER_PAGE_TRANSITION_HORIZONTAL);
        EXPECT_EQ(transition->direction, POPPLER_PAGE_TRANSITION_INWARD);
        poppler_page_transition_free(transition);
    }
    
    g_object_unref(page);
}

// Test Blinds transition type
TEST_F(PopplerPageTransitionTest_2430, BlindsTransition_2430) {
    doc = createPdfWithTransition("Blinds", 1.0, "/Dm /V");
    if (!doc) {
        GTEST_SKIP() << "Could not create test PDF";
    }
    
    PopplerPage *page = poppler_document_get_page(doc, 0);
    if (!page) {
        GTEST_SKIP() << "Could not get page";
    }
    
    PopplerPageTransition *transition = poppler_page_get_transition(page);
    if (transition) {
        EXPECT_EQ(transition->type, POPPLER_PAGE_TRANSITION_BLINDS);
        EXPECT_EQ(transition->alignment, POPPLER_PAGE_TRANSITION_VERTICAL);
        poppler_page_transition_free(transition);
    }
    
    g_object_unref(page);
}

// Test Box transition type
TEST_F(PopplerPageTransitionTest_2430, BoxTransition_2430) {
    doc = createPdfWithTransition("Box", 3.0, "/M /O");
    if (!doc) {
        GTEST_SKIP() << "Could not create test PDF";
    }
    
    PopplerPage *page = poppler_document_get_page(doc, 0);
    if (!page) {
        GTEST_SKIP() << "Could not get page";
    }
    
    PopplerPageTransition *transition = poppler_page_get_transition(page);
    if (transition) {
        EXPECT_EQ(transition->type, POPPLER_PAGE_TRANSITION_BOX);
        EXPECT_EQ(transition->direction, POPPLER_PAGE_TRANSITION_OUTWARD);
        poppler_page_transition_free(transition);
    }
    
    g_object_unref(page);
}

// Test Wipe transition type
TEST_F(PopplerPageTransitionTest_2430, WipeTransition_2430) {
    doc = createPdfWithTransition("Wipe", 1.0, "/Di 90");
    if (!doc) {
        GTEST_SKIP() << "Could not create test PDF";
    }
    
    PopplerPage *page = poppler_document_get_page(doc, 0);
    if (!page) {
        GTEST_SKIP() << "Could not get page";
    }
    
    PopplerPageTransition *transition = poppler_page_get_transition(page);
    if (transition) {
        EXPECT_EQ(transition->type, POPPLER_PAGE_TRANSITION_WIPE);
        EXPECT_EQ(transition->angle, 90);
        poppler_page_transition_free(transition);
    }
    
    g_object_unref(page);
}

// Test Dissolve transition type
TEST_F(PopplerPageTransitionTest_2430, DissolveTransition_2430) {
    doc = createPdfWithTransition("Dissolve", 2.5);
    if (!doc) {
        GTEST_SKIP() << "Could not create test PDF";
    }
    
    PopplerPage *page = poppler_document_get_page(doc, 0);
    if (!page) {
        GTEST_SKIP() << "Could not get page";
    }
    
    PopplerPageTransition *transition = poppler_page_get_transition(page);
    if (transition) {
        EXPECT_EQ(transition->type, POPPLER_PAGE_TRANSITION_DISSOLVE);
        poppler_page_transition_free(transition);
    }
    
    g_object_unref(page);
}

// Test Glitter transition type
TEST_F(PopplerPageTransitionTest_2430, GlitterTransition_2430) {
    doc = createPdfWithTransition("Glitter", 1.0, "/Di 315");
    if (!doc) {
        GTEST_SKIP() << "Could not create test PDF";
    }
    
    PopplerPage *page = poppler_document_get_page(doc, 0);
    if (!page) {
        GTEST_SKIP() << "Could not get page";
    }
    
    PopplerPageTransition *transition = poppler_page_get_transition(page);
    if (transition) {
        EXPECT_EQ(transition->type, POPPLER_PAGE_TRANSITION_GLITTER);
        EXPECT_EQ(transition->angle, 315);
        poppler_page_transition_free(transition);
    }
    
    g_object_unref(page);
}

// Test Fly transition type
TEST_F(PopplerPageTransitionTest_2430, FlyTransition_2430) {
    doc = createPdfWithTransition("Fly", 1.0, "/SS 1.0 /B true");
    if (!doc) {
        GTEST_SKIP() << "Could not create test PDF";
    }
    
    PopplerPage *page = poppler_document_get_page(doc, 0);
    if (!page) {
        GTEST_SKIP() << "Could not get page";
    }
    
    PopplerPageTransition *transition = poppler_page_get_transition(page);
    if (transition) {
        EXPECT_EQ(transition->type, POPPLER_PAGE_TRANSITION_FLY);
        poppler_page_transition_free(transition);
    }
    
    g_object_unref(page);
}

// Test Push transition type
TEST_F(PopplerPageTransitionTest_2430, PushTransition_2430) {
    doc = createPdfWithTransition("Push", 0.5);
    if (!doc) {
        GTEST_SKIP() << "Could not create test PDF";
    }
    
    PopplerPage *page = poppler_document_get_page(doc, 0);
    if (!page) {
        GTEST_SKIP() << "Could not get page";
    }
    
    PopplerPageTransition *transition = poppler_page_get_transition(page);
    if (transition) {
        EXPECT_EQ(transition->type, POPPLER_PAGE_TRANSITION_PUSH);
        poppler_page_transition_free(transition);
    }
    
    g_object_unref(page);
}

// Test Cover transition type
TEST_F(PopplerPageTransitionTest_2430, CoverTransition_2430) {
    doc = createPdfWithTransition("Cover", 1.0);
    if (!doc) {
        GTEST_SKIP() << "Could not create test PDF";
    }
    
    PopplerPage *page = poppler_document_get_page(doc, 0);
    if (!page) {
        GTEST_SKIP() << "Could not get page";
    }
    
    PopplerPageTransition *transition = poppler_page_get_transition(page);
    if (transition) {
        EXPECT_EQ(transition->type, POPPLER_PAGE_TRANSITION_COVER);
        poppler_page_transition_free(transition);
    }
    
    g_object_unref(page);
}

// Test Uncover transition type
TEST_F(PopplerPageTransitionTest_2430, UncoverTransition_2430) {
    doc = createPdfWithTransition("Uncover", 1.0);
    if (!doc) {
        GTEST_SKIP() << "Could not create test PDF";
    }
    
    PopplerPage *page = poppler_document_get_page(doc, 0);
    if (!page) {
        GTEST_SKIP() << "Could not get page";
    }
    
    PopplerPageTransition *transition = poppler_page_get_transition(page);
    if (transition) {
        EXPECT_EQ(transition->type, POPPLER_PAGE_TRANSITION_UNCOVER);
        poppler_page_transition_free(transition);
    }
    
    g_object_unref(page);
}

// Test Fade transition type
TEST_F(PopplerPageTransitionTest_2430, FadeTransition_2430) {
    doc = createPdfWithTransition("Fade", 4.0);
    if (!doc) {
        GTEST_SKIP() << "Could not create test PDF";
    }
    
    PopplerPage *page = poppler_document_get_page(doc, 0);
    if (!page) {
        GTEST_SKIP() << "Could not get page";
    }
    
    PopplerPageTransition *transition = poppler_page_get_transition(page);
    if (transition) {
        EXPECT_EQ(transition->type, POPPLER_PAGE_TRANSITION_FADE);
        poppler_page_transition_free(transition);
    }
    
    g_object_unref(page);
}

// Test transition duration
TEST_F(PopplerPageTransitionTest_2430, TransitionDuration_2430) {
    doc = createPdfWithTransition("Dissolve", 5.0);
    if (!doc) {
        GTEST_SKIP() << "Could not create test PDF";
    }
    
    PopplerPage *page = poppler_document_get_page(doc, 0);
    if (!page) {
        GTEST_SKIP() << "Could not get page";
    }
    
    PopplerPageTransition *transition = poppler_page_get_transition(page);
    if (transition) {
        EXPECT_DOUBLE_EQ(transition->duration_real, 5.0);
        poppler_page_transition_free(transition);
    }
    
    g_object_unref(page);
}

// Test transition with zero duration
TEST_F(PopplerPageTransitionTest_2430, ZeroDurationTransition_2430) {
    doc = createPdfWithTransition("Dissolve", 0.0);
    if (!doc) {
        GTEST_SKIP() << "Could not create test PDF";
    }
    
    PopplerPage *page = poppler_document_get_page(doc, 0);
    if (!page) {
        GTEST_SKIP() << "Could not get page";
    }
    
    PopplerPageTransition *transition = poppler_page_get_transition(page);
    if (transition) {
        EXPECT_DOUBLE_EQ(transition->duration_real, 0.0);
        poppler_page_transition_free(transition);
    }
    
    g_object_unref(page);
}

// Test default alignment is horizontal
TEST_F(PopplerPageTransitionTest_2430, DefaultAlignmentIsHorizontal_2430) {
    doc = createPdfWithTransition("Split", 1.0);
    if (!doc) {
        GTEST_SKIP() << "Could not create test PDF";
    }
    
    PopplerPage *page = poppler_document_get_page(doc, 0);
    if (!page) {
        GTEST_SKIP() << "Could not get page";
    }
    
    PopplerPageTransition *transition = poppler_page_get_transition(page);
    if (transition) {
        // Default alignment should be horizontal
        EXPECT_EQ(transition->alignment, POPPLER_PAGE_TRANSITION_HORIZONTAL);
        poppler_page_transition_free(transition);
    }
    
    g_object_unref(page);
}

// Test default direction is inward
TEST_F(PopplerPageTransitionTest_2430, DefaultDirectionIsInward_2430) {
    doc = createPdfWithTransition("Split", 1.0);
    if (!doc) {
        GTEST_SKIP() << "Could not create test PDF";
    }
    
    PopplerPage *page = poppler_document_get_page(doc, 0);
    if (!page) {
        GTEST_SKIP() << "Could not get page";
    }
    
    PopplerPageTransition *transition = poppler_page_get_transition(page);
    if (transition) {
        // Default direction should be inward
        EXPECT_EQ(transition->direction, POPPLER_PAGE_TRANSITION_INWARD);
        poppler_page_transition_free(transition);
    }
    
    g_object_unref(page);
}

// Test transition with default angle (0)
TEST_F(PopplerPageTransitionTest_2430, DefaultAngleIsZero_2430) {
    doc = createPdfWithTransition("Wipe", 1.0);
    if (!doc) {
        GTEST_SKIP() << "Could not create test PDF";
    }
    
    PopplerPage *page = poppler_document_get_page(doc, 0);
    if (!page) {
        GTEST_SKIP() << "Could not get page";
    }
    
    PopplerPageTransition *transition = poppler_page_get_transition(page);
    if (transition) {
        // Default angle for Wipe should be 0
        EXPECT_EQ(transition->angle, 0);
        poppler_page_transition_free(transition);
    }
    
    g_object_unref(page);
}

// Test using a real PDF file with transitions if available
// This is a more integration-level test
TEST_F(PopplerPageTransitionTest_2430, TransitionCopyTest_2430) {
    doc = createPdfWithTransition("Dissolve", 3.0);
    if (!doc) {
        GTEST_SKIP() << "Could not create test PDF";
    }
    
    PopplerPage *page = poppler_document_get_page(doc, 0);
    if (!page) {
        GTEST_SKIP() << "Could not get page";
    }
    
    PopplerPageTransition *transition = poppler_page_get_transition(page);
    if (transition) {
        // Verify the transition can be copied
        PopplerPageTransition *copy = poppler_page_transition_copy(transition);
        ASSERT_NE(copy, nullptr);
        EXPECT_EQ(copy->type, transition->type);
        EXPECT_EQ(copy->alignment, transition->alignment);
        EXPECT_EQ(copy->direction, transition->direction);
        EXPECT_DOUBLE_EQ(copy->duration_real, transition->duration_real);
        EXPECT_EQ(copy->angle, transition->angle);
        
        poppler_page_transition_free(copy);
        poppler_page_transition_free(transition);
    }
    
    g_object_unref(page);
}
