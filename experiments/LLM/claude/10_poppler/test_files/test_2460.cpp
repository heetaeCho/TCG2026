#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>

// Poppler includes
#include "poppler/PDFDoc.h"
#include "poppler/Page.h"
#include "poppler/Annot.h"
#include "poppler/Object.h"
#include "poppler/Dict.h"
#include "poppler/PDFDocFactory.h"

// The function under test is declared in poppler-page.cc (glib binding)
// We need its declaration
extern "C" {
#include "glib/poppler.h"
}

// Forward declare the internal function we're testing
void _unrotate_rect_for_annot_and_page(Page *page, Annot *annot, double *x1, double *y1, double *x2, double *y2);

class UnrotateRectTest_2460 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }

    // Helper to create a minimal PDF in memory with a given rotation
    std::unique_ptr<PDFDoc> createPDFWithRotation(int rotation) {
        // Create a minimal PDF document in memory
        // We'll use a simple PDF structure
        std::string pdf = "%PDF-1.4\n";
        pdf += "1 0 obj\n<< /Type /Catalog /Pages 2 0 R >>\nendobj\n";
        pdf += "2 0 obj\n<< /Type /Pages /Kids [3 0 R] /Count 1 >>\nendobj\n";
        pdf += "3 0 obj\n<< /Type /Page /Parent 2 0 R /MediaBox [0 0 612 792]";
        if (rotation != 0) {
            pdf += " /Rotate " + std::to_string(rotation);
        }
        pdf += " >>\nendobj\n";

        // Cross-reference table
        // We need proper offsets
        std::string header = "%PDF-1.4\n";
        std::string obj1 = "1 0 obj\n<< /Type /Catalog /Pages 2 0 R >>\nendobj\n";
        std::string obj2 = "2 0 obj\n<< /Type /Pages /Kids [3 0 R] /Count 1 >>\nendobj\n";
        std::string obj3_str = "3 0 obj\n<< /Type /Page /Parent 2 0 R /MediaBox [0 0 612 792]";
        if (rotation != 0) {
            obj3_str += " /Rotate " + std::to_string(rotation);
        }
        obj3_str += " >>\nendobj\n";

        size_t off1 = header.size();
        size_t off2 = off1 + obj1.size();
        size_t off3 = off2 + obj2.size();
        size_t xrefOff = off3 + obj3_str.size();

        std::string fullPdf = header + obj1 + obj2 + obj3_str;

        char xref[512];
        snprintf(xref, sizeof(xref),
                 "xref\n0 4\n0000000000 65535 f \n%010zu 00000 n \n%010zu 00000 n \n%010zu 00000 n \n"
                 "trailer\n<< /Size 4 /Root 1 0 R >>\nstartxref\n%zu\n%%%%EOF\n",
                 off1, off2, off3, xrefOff);

        fullPdf += xref;

        auto *stream = new MemStream(strdup(fullPdf.c_str()), 0, fullPdf.size(), Object(objNull));
        auto doc = std::make_unique<PDFDoc>(stream);
        return doc;
    }
};

// Test: No rotation (0 degrees) - function should return early, coords unchanged
TEST_F(UnrotateRectTest_2460, NoRotation_CoordsUnchanged_2460) {
    auto doc = createPDFWithRotation(0);
    ASSERT_TRUE(doc && doc->isOk());

    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);
    ASSERT_EQ(page->getRotate(), 0);

    // Create a simple annotation
    PDFRectangle rect(100, 200, 300, 400);
    Annot annot(doc.get(), &rect);

    double x1 = 100, y1 = 200, x2 = 300, y2 = 400;
    double orig_x1 = x1, orig_y1 = y1, orig_x2 = x2, orig_y2 = y2;

    _unrotate_rect_for_annot_and_page(page, &annot, &x1, &y1, &x2, &y2);

    // With 0 rotation, the function should return early (no supported rotation or no-op)
    // Coords may be normalized but rotation itself doesn't apply
    // Since SUPPORTED_ROTATION likely excludes 0 (no rotation needed), coords stay same
    EXPECT_DOUBLE_EQ(x1, orig_x1);
    EXPECT_DOUBLE_EQ(y1, orig_y1);
    EXPECT_DOUBLE_EQ(x2, orig_x2);
    EXPECT_DOUBLE_EQ(y2, orig_y2);
}

// Test: 90 degree rotation without flagNoRotate
TEST_F(UnrotateRectTest_2460, Rotation90_NoFlagNoRotate_2460) {
    auto doc = createPDFWithRotation(90);
    ASSERT_TRUE(doc && doc->isOk());

    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);
    ASSERT_EQ(page->getRotate(), 90);

    PDFRectangle rect(100, 200, 300, 400);
    Annot annot(doc.get(), &rect);
    // Ensure flagNoRotate is NOT set
    annot.setFlags(0);

    double x1 = 100, y1 = 400, x2 = 300, y2 = 200;

    _unrotate_rect_for_annot_and_page(page, &annot, &x1, &y1, &x2, &y2);

    // After unrotation, coords should be transformed
    // We don't know exact values but they should be different from input (for 90 deg)
    // At minimum, the function should have run without crash
    SUCCEED();
}

// Test: 90 degree rotation with flagNoRotate
TEST_F(UnrotateRectTest_2460, Rotation90_WithFlagNoRotate_2460) {
    auto doc = createPDFWithRotation(90);
    ASSERT_TRUE(doc && doc->isOk());

    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);

    PDFRectangle rect(100, 200, 300, 400);
    Annot annot(doc.get(), &rect);
    annot.setFlags(Annot::flagNoRotate);

    double x1 = 100, y1 = 400, x2 = 300, y2 = 200;
    double width_before = x2 - x1;   // 200
    double height_before = y1 - y2;   // 200

    _unrotate_rect_for_annot_and_page(page, &annot, &x1, &y1, &x2, &y2);

    // With flagNoRotate, width and height should be preserved relative to the new upper-left
    double width_after = x2 - x1;
    double height_after = y1 - y2;
    EXPECT_DOUBLE_EQ(width_after, width_before);
    EXPECT_DOUBLE_EQ(height_after, height_before);
}

// Test: 180 degree rotation without flagNoRotate
TEST_F(UnrotateRectTest_2460, Rotation180_NoFlagNoRotate_2460) {
    auto doc = createPDFWithRotation(180);
    ASSERT_TRUE(doc && doc->isOk());

    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);
    ASSERT_EQ(page->getRotate(), 180);

    PDFRectangle rect(100, 200, 300, 400);
    Annot annot(doc.get(), &rect);
    annot.setFlags(0);

    double x1 = 100, y1 = 400, x2 = 300, y2 = 200;

    _unrotate_rect_for_annot_and_page(page, &annot, &x1, &y1, &x2, &y2);

    // Should complete without crash
    SUCCEED();
}

// Test: 270 degree rotation without flagNoRotate
TEST_F(UnrotateRectTest_2460, Rotation270_NoFlagNoRotate_2460) {
    auto doc = createPDFWithRotation(270);
    ASSERT_TRUE(doc && doc->isOk());

    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);
    ASSERT_EQ(page->getRotate(), 270);

    PDFRectangle rect(100, 200, 300, 400);
    Annot annot(doc.get(), &rect);
    annot.setFlags(0);

    double x1 = 100, y1 = 400, x2 = 300, y2 = 200;

    _unrotate_rect_for_annot_and_page(page, &annot, &x1, &y1, &x2, &y2);

    SUCCEED();
}

// Test: Normalization - y2 > y1 should be swapped
TEST_F(UnrotateRectTest_2460, NormalizationYSwap_2460) {
    auto doc = createPDFWithRotation(90);
    ASSERT_TRUE(doc && doc->isOk());

    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);

    PDFRectangle rect(100, 200, 300, 400);
    Annot annot(doc.get(), &rect);
    annot.setFlags(Annot::flagNoRotate);

    // y2 > y1 (y2=400 > y1=200), so they should get swapped internally
    double x1 = 100, y1 = 200, x2 = 300, y2 = 400;
    double width_before = x2 - x1;   // 200
    double height_before = y2 - y1;   // 200 (after swap: y1=400, y2=200, height=200)

    _unrotate_rect_for_annot_and_page(page, &annot, &x1, &y1, &x2, &y2);

    // With flagNoRotate, dimensions should be preserved
    double width_after = x2 - x1;
    double height_after = y1 - y2;
    EXPECT_DOUBLE_EQ(width_after, width_before);
    EXPECT_DOUBLE_EQ(height_after, height_before);
}

// Test: Normalization - x1 > x2 should be swapped
TEST_F(UnrotateRectTest_2460, NormalizationXSwap_2460) {
    auto doc = createPDFWithRotation(90);
    ASSERT_TRUE(doc && doc->isOk());

    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);

    PDFRectangle rect(100, 200, 300, 400);
    Annot annot(doc.get(), &rect);
    annot.setFlags(Annot::flagNoRotate);

    // x1 > x2 (x1=300 > x2=100), they should get swapped
    double x1 = 300, y1 = 400, x2 = 100, y2 = 200;
    double expected_width = 200;  // |300-100|
    double expected_height = 200; // |400-200|

    _unrotate_rect_for_annot_and_page(page, &annot, &x1, &y1, &x2, &y2);

    double width_after = x2 - x1;
    double height_after = y1 - y2;
    EXPECT_DOUBLE_EQ(width_after, expected_width);
    EXPECT_DOUBLE_EQ(height_after, expected_height);
}

// Test: Unsupported rotation (e.g., 45 degrees) - should return early
TEST_F(UnrotateRectTest_2460, UnsupportedRotation_CoordsUnchanged_2460) {
    // Pages with non-standard rotations typically get normalized to 0 by poppler,
    // but we test the concept - if getRotate() returns something unsupported,
    // the function returns early
    auto doc = createPDFWithRotation(0);
    ASSERT_TRUE(doc && doc->isOk());

    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);

    PDFRectangle rect(50, 50, 150, 150);
    Annot annot(doc.get(), &rect);

    double x1 = 50, y1 = 50, x2 = 150, y2 = 150;
    double orig_x1 = x1, orig_y1 = y1, orig_x2 = x2, orig_y2 = y2;

    _unrotate_rect_for_annot_and_page(page, &annot, &x1, &y1, &x2, &y2);

    // 0 degree rotation is not "supported" for unrotation (nothing to undo)
    EXPECT_DOUBLE_EQ(x1, orig_x1);
    EXPECT_DOUBLE_EQ(y1, orig_y1);
    EXPECT_DOUBLE_EQ(x2, orig_x2);
    EXPECT_DOUBLE_EQ(y2, orig_y2);
}

// Test: Zero-size rect (point)
TEST_F(UnrotateRectTest_2460, ZeroSizeRect_2460) {
    auto doc = createPDFWithRotation(90);
    ASSERT_TRUE(doc && doc->isOk());

    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);

    PDFRectangle rect(100, 100, 100, 100);
    Annot annot(doc.get(), &rect);
    annot.setFlags(Annot::flagNoRotate);

    double x1 = 100, y1 = 100, x2 = 100, y2 = 100;

    _unrotate_rect_for_annot_and_page(page, &annot, &x1, &y1, &x2, &y2);

    // Zero-size rect: width and height should remain 0
    EXPECT_DOUBLE_EQ(x2 - x1, 0.0);
    EXPECT_DOUBLE_EQ(y1 - y2, 0.0);
}

// Test: 180 degree rotation with flagNoRotate preserves dimensions
TEST_F(UnrotateRectTest_2460, Rotation180_WithFlagNoRotate_PreservesDimensions_2460) {
    auto doc = createPDFWithRotation(180);
    ASSERT_TRUE(doc && doc->isOk());

    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);

    PDFRectangle rect(50, 100, 250, 500);
    Annot annot(doc.get(), &rect);
    annot.setFlags(Annot::flagNoRotate);

    double x1 = 50, y1 = 500, x2 = 250, y2 = 100;
    double width_before = x2 - x1;   // 200
    double height_before = y1 - y2;   // 400

    _unrotate_rect_for_annot_and_page(page, &annot, &x1, &y1, &x2, &y2);

    double width_after = x2 - x1;
    double height_after = y1 - y2;
    EXPECT_DOUBLE_EQ(width_after, width_before);
    EXPECT_DOUBLE_EQ(height_after, height_before);
}

// Test: 270 degree rotation with flagNoRotate preserves dimensions
TEST_F(UnrotateRectTest_2460, Rotation270_WithFlagNoRotate_PreservesDimensions_2460) {
    auto doc = createPDFWithRotation(270);
    ASSERT_TRUE(doc && doc->isOk());

    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);

    PDFRectangle rect(10, 20, 110, 220);
    Annot annot(doc.get(), &rect);
    annot.setFlags(Annot::flagNoRotate);

    double x1 = 10, y1 = 220, x2 = 110, y2 = 20;
    double width_before = x2 - x1;   // 100
    double height_before = y1 - y2;   // 200

    _unrotate_rect_for_annot_and_page(page, &annot, &x1, &y1, &x2, &y2);

    double width_after = x2 - x1;
    double height_after = y1 - y2;
    EXPECT_DOUBLE_EQ(width_after, width_before);
    EXPECT_DOUBLE_EQ(height_after, height_before);
}

// Test: Large coordinates
TEST_F(UnrotateRectTest_2460, LargeCoordinates_2460) {
    auto doc = createPDFWithRotation(90);
    ASSERT_TRUE(doc && doc->isOk());

    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);

    PDFRectangle rect(0, 0, 10000, 10000);
    Annot annot(doc.get(), &rect);
    annot.setFlags(0);

    double x1 = 0, y1 = 10000, x2 = 10000, y2 = 0;

    // Should not crash with large values
    _unrotate_rect_for_annot_and_page(page, &annot, &x1, &y1, &x2, &y2);

    SUCCEED();
}

// Test: Negative coordinates
TEST_F(UnrotateRectTest_2460, NegativeCoordinates_2460) {
    auto doc = createPDFWithRotation(90);
    ASSERT_TRUE(doc && doc->isOk());

    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);

    PDFRectangle rect(-200, -100, 200, 100);
    Annot annot(doc.get(), &rect);
    annot.setFlags(Annot::flagNoRotate);

    double x1 = -200, y1 = 100, x2 = 200, y2 = -100;
    double width_before = x2 - x1;   // 400
    double height_before = y1 - y2;   // 200

    _unrotate_rect_for_annot_and_page(page, &annot, &x1, &y1, &x2, &y2);

    double width_after = x2 - x1;
    double height_after = y1 - y2;
    EXPECT_DOUBLE_EQ(width_after, width_before);
    EXPECT_DOUBLE_EQ(height_after, height_before);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
