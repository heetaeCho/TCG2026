#include <gtest/gtest.h>
#include <gmock/gmock.h>

// Include necessary headers
extern "C" {
#include <glib-object.h>
}

#include "poppler-document.h"
#include "poppler-private.h"
#include "poppler.h"

#include <string>
#include <cstdio>
#include <cstdlib>

class PopplerDocumentPrintScalingTest_2197 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}

    // Helper to create a PopplerDocument from a PDF file path
    PopplerDocument *loadDocument(const char *uri, GError **error) {
        return poppler_document_new_from_file(uri, nullptr, error);
    }

    // Helper to create a minimal PDF in memory with optional ViewerPreferences
    PopplerDocument *createPdfWithPrintScaling(const char *printScalingValue) {
        std::string pdf;
        
        std::string viewerPrefsObj;
        std::string catalogExtra;
        
        if (printScalingValue != nullptr) {
            viewerPrefsObj = "4 0 obj\n<< /PrintScaling /" + std::string(printScalingValue) + " >>\nendobj\n";
            catalogExtra = " /ViewerPreferences 4 0 R";
        }

        // Build a minimal PDF
        pdf += "%PDF-1.4\n";
        
        // Object 1: Catalog
        std::string obj1 = "1 0 obj\n<< /Type /Catalog /Pages 2 0 R" + catalogExtra + " >>\nendobj\n";
        
        // Object 2: Pages
        std::string obj2 = "2 0 obj\n<< /Type /Pages /Kids [3 0 R] /Count 1 >>\nendobj\n";
        
        // Object 3: Page
        std::string obj3 = "3 0 obj\n<< /Type /Page /Parent 2 0 R /MediaBox [0 0 612 792] >>\nendobj\n";
        
        size_t offset = pdf.size();
        size_t xrefOffsets[5] = {0};
        
        xrefOffsets[1] = offset;
        pdf += obj1;
        
        xrefOffsets[2] = pdf.size();
        pdf += obj2;
        
        xrefOffsets[3] = pdf.size();
        pdf += obj3;
        
        int numObjects = 4;
        if (printScalingValue != nullptr) {
            xrefOffsets[4] = pdf.size();
            pdf += viewerPrefsObj;
            numObjects = 5;
        }
        
        size_t xrefStart = pdf.size();
        pdf += "xref\n";
        pdf += "0 " + std::to_string(numObjects) + "\n";
        pdf += "0000000000 65535 f \n";
        
        for (int i = 1; i < numObjects; i++) {
            char buf[32];
            snprintf(buf, sizeof(buf), "%010zu 00000 n \n", xrefOffsets[i]);
            pdf += buf;
        }
        
        pdf += "trailer\n<< /Size " + std::to_string(numObjects) + " /Root 1 0 R >>\n";
        pdf += "startxref\n" + std::to_string(xrefStart) + "\n%%EOF\n";
        
        GError *error = nullptr;
        PopplerDocument *doc = poppler_document_new_from_data(
            reinterpret_cast<const char*>(pdf.data()), pdf.size(), nullptr, &error);
        
        if (error) {
            g_error_free(error);
            return nullptr;
        }
        
        return doc;
    }
};

// Test that passing NULL document returns the default value
TEST_F(PopplerDocumentPrintScalingTest_2197, NullDocumentReturnsDefault_2197) {
    // Passing NULL should trigger g_return_val_if_fail and return POPPLER_PRINT_SCALING_APP_DEFAULT
    PopplerPrintScaling result = poppler_document_get_print_scaling(nullptr);
    EXPECT_EQ(result, POPPLER_PRINT_SCALING_APP_DEFAULT);
}

// Test a PDF with no ViewerPreferences returns default
TEST_F(PopplerDocumentPrintScalingTest_2197, NoViewerPreferencesReturnsDefault_2197) {
    PopplerDocument *doc = createPdfWithPrintScaling(nullptr);
    if (doc == nullptr) {
        GTEST_SKIP() << "Could not create test PDF";
    }
    
    PopplerPrintScaling result = poppler_document_get_print_scaling(doc);
    EXPECT_EQ(result, POPPLER_PRINT_SCALING_APP_DEFAULT);
    
    g_object_unref(doc);
}

// Test a PDF with PrintScaling set to AppDefault
TEST_F(PopplerDocumentPrintScalingTest_2197, PrintScalingAppDefault_2197) {
    PopplerDocument *doc = createPdfWithPrintScaling("AppDefault");
    if (doc == nullptr) {
        GTEST_SKIP() << "Could not create test PDF";
    }
    
    PopplerPrintScaling result = poppler_document_get_print_scaling(doc);
    EXPECT_EQ(result, POPPLER_PRINT_SCALING_APP_DEFAULT);
    
    g_object_unref(doc);
}

// Test a PDF with PrintScaling set to None
TEST_F(PopplerDocumentPrintScalingTest_2197, PrintScalingNone_2197) {
    PopplerDocument *doc = createPdfWithPrintScaling("None");
    if (doc == nullptr) {
        GTEST_SKIP() << "Could not create test PDF";
    }
    
    PopplerPrintScaling result = poppler_document_get_print_scaling(doc);
    EXPECT_EQ(result, POPPLER_PRINT_SCALING_NONE);
    
    g_object_unref(doc);
}

// Test that calling the function multiple times on same document yields consistent results
TEST_F(PopplerDocumentPrintScalingTest_2197, ConsistentResults_2197) {
    PopplerDocument *doc = createPdfWithPrintScaling("None");
    if (doc == nullptr) {
        GTEST_SKIP() << "Could not create test PDF";
    }
    
    PopplerPrintScaling result1 = poppler_document_get_print_scaling(doc);
    PopplerPrintScaling result2 = poppler_document_get_print_scaling(doc);
    EXPECT_EQ(result1, result2);
    
    g_object_unref(doc);
}

// Test with ViewerPreferences present but with an empty dictionary (no PrintScaling key)
TEST_F(PopplerDocumentPrintScalingTest_2197, ViewerPrefsWithoutPrintScaling_2197) {
    // Build a PDF with ViewerPreferences that has no PrintScaling entry
    std::string pdf;
    pdf += "%PDF-1.4\n";
    
    size_t xrefOffsets[5] = {0};
    
    xrefOffsets[1] = pdf.size();
    pdf += "1 0 obj\n<< /Type /Catalog /Pages 2 0 R /ViewerPreferences 4 0 R >>\nendobj\n";
    
    xrefOffsets[2] = pdf.size();
    pdf += "2 0 obj\n<< /Type /Pages /Kids [3 0 R] /Count 1 >>\nendobj\n";
    
    xrefOffsets[3] = pdf.size();
    pdf += "3 0 obj\n<< /Type /Page /Parent 2 0 R /MediaBox [0 0 612 792] >>\nendobj\n";
    
    xrefOffsets[4] = pdf.size();
    // ViewerPreferences with only HideToolbar, no PrintScaling
    pdf += "4 0 obj\n<< /HideToolbar true >>\nendobj\n";
    
    size_t xrefStart = pdf.size();
    pdf += "xref\n0 5\n";
    pdf += "0000000000 65535 f \n";
    for (int i = 1; i <= 4; i++) {
        char buf[32];
        snprintf(buf, sizeof(buf), "%010zu 00000 n \n", xrefOffsets[i]);
        pdf += buf;
    }
    pdf += "trailer\n<< /Size 5 /Root 1 0 R >>\n";
    pdf += "startxref\n" + std::to_string(xrefStart) + "\n%%EOF\n";
    
    GError *error = nullptr;
    PopplerDocument *doc = poppler_document_new_from_data(
        reinterpret_cast<const char*>(pdf.data()), pdf.size(), nullptr, &error);
    
    if (doc == nullptr) {
        if (error) g_error_free(error);
        GTEST_SKIP() << "Could not create test PDF";
    }
    
    PopplerPrintScaling result = poppler_document_get_print_scaling(doc);
    // Without explicit PrintScaling, default should be AppDefault
    EXPECT_EQ(result, POPPLER_PRINT_SCALING_APP_DEFAULT);
    
    g_object_unref(doc);
}

// Test return value enum values are distinct
TEST_F(PopplerDocumentPrintScalingTest_2197, EnumValuesAreDifferent_2197) {
    EXPECT_NE(POPPLER_PRINT_SCALING_APP_DEFAULT, POPPLER_PRINT_SCALING_NONE);
}
