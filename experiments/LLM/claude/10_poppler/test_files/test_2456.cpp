#include <gtest/gtest.h>
#include <memory>

// Include necessary headers
#include "poppler/Annot.h"
#include "poppler/PDFRectangle.h"

// Declaration of the function under test
AnnotQuadrilaterals *new_quads_from_offset_cropbox(const PDFRectangle *crop_box, AnnotQuadrilaterals *quads, gboolean add);

// Helper to create AnnotQuadrilaterals from raw coordinate arrays
static std::unique_ptr<AnnotQuadrilaterals> makeQuads(int count,
    const double* x1, const double* y1,
    const double* x2, const double* y2,
    const double* x3, const double* y3,
    const double* x4, const double* y4)
{
    auto arr = std::make_unique<AnnotQuadrilaterals::AnnotQuadrilateral[]>(count);
    for (int i = 0; i < count; i++) {
        arr[i] = AnnotQuadrilaterals::AnnotQuadrilateral(
            x1[i], y1[i], x2[i], y2[i], x3[i], y3[i], x4[i], y4[i]);
    }
    return std::make_unique<AnnotQuadrilaterals>(std::move(arr), count);
}

class NewQuadsFromOffsetCropboxTest_2456 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test: Adding crop_box offset to a single quadrilateral
TEST_F(NewQuadsFromOffsetCropboxTest_2456, SingleQuadAdd_2456) {
    PDFRectangle crop_box(10.0, 20.0, 100.0, 200.0);

    double x1[] = {1.0}, y1[] = {2.0};
    double x2[] = {3.0}, y2[] = {4.0};
    double x3[] = {5.0}, y3[] = {6.0};
    double x4[] = {7.0}, y4[] = {8.0};

    auto quads = makeQuads(1, x1, y1, x2, y2, x3, y3, x4, y4);

    AnnotQuadrilaterals *result = new_quads_from_offset_cropbox(&crop_box, quads.get(), TRUE);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->getQuadrilateralsLength(), 1);

    // Each coordinate should have crop_box.x1 or crop_box.y1 added
    EXPECT_DOUBLE_EQ(result->getX1(0), 1.0 + 10.0);
    EXPECT_DOUBLE_EQ(result->getY1(0), 2.0 + 20.0);
    EXPECT_DOUBLE_EQ(result->getX2(0), 3.0 + 10.0);
    EXPECT_DOUBLE_EQ(result->getY2(0), 4.0 + 20.0);
    EXPECT_DOUBLE_EQ(result->getX3(0), 5.0 + 10.0);
    EXPECT_DOUBLE_EQ(result->getY3(0), 6.0 + 20.0);
    EXPECT_DOUBLE_EQ(result->getX4(0), 7.0 + 10.0);
    EXPECT_DOUBLE_EQ(result->getY4(0), 8.0 + 20.0);

    delete result;
}

// Test: Subtracting crop_box offset from a single quadrilateral
TEST_F(NewQuadsFromOffsetCropboxTest_2456, SingleQuadSubtract_2456) {
    PDFRectangle crop_box(10.0, 20.0, 100.0, 200.0);

    double x1[] = {11.0}, y1[] = {22.0};
    double x2[] = {13.0}, y2[] = {24.0};
    double x3[] = {15.0}, y3[] = {26.0};
    double x4[] = {17.0}, y4[] = {28.0};

    auto quads = makeQuads(1, x1, y1, x2, y2, x3, y3, x4, y4);

    AnnotQuadrilaterals *result = new_quads_from_offset_cropbox(&crop_box, quads.get(), FALSE);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->getQuadrilateralsLength(), 1);

    EXPECT_DOUBLE_EQ(result->getX1(0), 11.0 - 10.0);
    EXPECT_DOUBLE_EQ(result->getY1(0), 22.0 - 20.0);
    EXPECT_DOUBLE_EQ(result->getX2(0), 13.0 - 10.0);
    EXPECT_DOUBLE_EQ(result->getY2(0), 24.0 - 20.0);
    EXPECT_DOUBLE_EQ(result->getX3(0), 15.0 - 10.0);
    EXPECT_DOUBLE_EQ(result->getY3(0), 26.0 - 20.0);
    EXPECT_DOUBLE_EQ(result->getX4(0), 17.0 - 10.0);
    EXPECT_DOUBLE_EQ(result->getY4(0), 28.0 - 20.0);

    delete result;
}

// Test: Multiple quadrilaterals with add=TRUE
TEST_F(NewQuadsFromOffsetCropboxTest_2456, MultipleQuadsAdd_2456) {
    PDFRectangle crop_box(5.0, 10.0, 50.0, 100.0);

    double x1[] = {0.0, 10.0, 20.0}, y1[] = {0.0, 10.0, 20.0};
    double x2[] = {1.0, 11.0, 21.0}, y2[] = {1.0, 11.0, 21.0};
    double x3[] = {2.0, 12.0, 22.0}, y3[] = {2.0, 12.0, 22.0};
    double x4[] = {3.0, 13.0, 23.0}, y4[] = {3.0, 13.0, 23.0};

    auto quads = makeQuads(3, x1, y1, x2, y2, x3, y3, x4, y4);

    AnnotQuadrilaterals *result = new_quads_from_offset_cropbox(&crop_box, quads.get(), TRUE);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->getQuadrilateralsLength(), 3);

    for (int i = 0; i < 3; i++) {
        EXPECT_DOUBLE_EQ(result->getX1(i), x1[i] + 5.0);
        EXPECT_DOUBLE_EQ(result->getY1(i), y1[i] + 10.0);
        EXPECT_DOUBLE_EQ(result->getX2(i), x2[i] + 5.0);
        EXPECT_DOUBLE_EQ(result->getY2(i), y2[i] + 10.0);
        EXPECT_DOUBLE_EQ(result->getX3(i), x3[i] + 5.0);
        EXPECT_DOUBLE_EQ(result->getY3(i), y3[i] + 10.0);
        EXPECT_DOUBLE_EQ(result->getX4(i), x4[i] + 5.0);
        EXPECT_DOUBLE_EQ(result->getY4(i), y4[i] + 10.0);
    }

    delete result;
}

// Test: Multiple quadrilaterals with add=FALSE
TEST_F(NewQuadsFromOffsetCropboxTest_2456, MultipleQuadsSubtract_2456) {
    PDFRectangle crop_box(5.0, 10.0, 50.0, 100.0);

    double x1[] = {100.0, 200.0}, y1[] = {100.0, 200.0};
    double x2[] = {101.0, 201.0}, y2[] = {101.0, 201.0};
    double x3[] = {102.0, 202.0}, y3[] = {102.0, 202.0};
    double x4[] = {103.0, 203.0}, y4[] = {103.0, 203.0};

    auto quads = makeQuads(2, x1, y1, x2, y2, x3, y3, x4, y4);

    AnnotQuadrilaterals *result = new_quads_from_offset_cropbox(&crop_box, quads.get(), FALSE);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->getQuadrilateralsLength(), 2);

    for (int i = 0; i < 2; i++) {
        EXPECT_DOUBLE_EQ(result->getX1(i), x1[i] - 5.0);
        EXPECT_DOUBLE_EQ(result->getY1(i), y1[i] - 10.0);
        EXPECT_DOUBLE_EQ(result->getX2(i), x2[i] - 5.0);
        EXPECT_DOUBLE_EQ(result->getY2(i), y2[i] - 10.0);
        EXPECT_DOUBLE_EQ(result->getX3(i), x3[i] - 5.0);
        EXPECT_DOUBLE_EQ(result->getY3(i), y3[i] - 10.0);
        EXPECT_DOUBLE_EQ(result->getX4(i), x4[i] - 5.0);
        EXPECT_DOUBLE_EQ(result->getY4(i), y4[i] - 10.0);
    }

    delete result;
}

// Test: Zero crop_box offset should leave coordinates unchanged (add)
TEST_F(NewQuadsFromOffsetCropboxTest_2456, ZeroCropBoxAdd_2456) {
    PDFRectangle crop_box(0.0, 0.0, 100.0, 200.0);

    double x1[] = {5.0}, y1[] = {6.0};
    double x2[] = {7.0}, y2[] = {8.0};
    double x3[] = {9.0}, y3[] = {10.0};
    double x4[] = {11.0}, y4[] = {12.0};

    auto quads = makeQuads(1, x1, y1, x2, y2, x3, y3, x4, y4);

    AnnotQuadrilaterals *result = new_quads_from_offset_cropbox(&crop_box, quads.get(), TRUE);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->getQuadrilateralsLength(), 1);

    EXPECT_DOUBLE_EQ(result->getX1(0), 5.0);
    EXPECT_DOUBLE_EQ(result->getY1(0), 6.0);
    EXPECT_DOUBLE_EQ(result->getX2(0), 7.0);
    EXPECT_DOUBLE_EQ(result->getY2(0), 8.0);
    EXPECT_DOUBLE_EQ(result->getX3(0), 9.0);
    EXPECT_DOUBLE_EQ(result->getY3(0), 10.0);
    EXPECT_DOUBLE_EQ(result->getX4(0), 11.0);
    EXPECT_DOUBLE_EQ(result->getY4(0), 12.0);

    delete result;
}

// Test: Zero crop_box offset should leave coordinates unchanged (subtract)
TEST_F(NewQuadsFromOffsetCropboxTest_2456, ZeroCropBoxSubtract_2456) {
    PDFRectangle crop_box(0.0, 0.0, 100.0, 200.0);

    double x1[] = {5.0}, y1[] = {6.0};
    double x2[] = {7.0}, y2[] = {8.0};
    double x3[] = {9.0}, y3[] = {10.0};
    double x4[] = {11.0}, y4[] = {12.0};

    auto quads = makeQuads(1, x1, y1, x2, y2, x3, y3, x4, y4);

    AnnotQuadrilaterals *result = new_quads_from_offset_cropbox(&crop_box, quads.get(), FALSE);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->getQuadrilateralsLength(), 1);

    EXPECT_DOUBLE_EQ(result->getX1(0), 5.0);
    EXPECT_DOUBLE_EQ(result->getY1(0), 6.0);

    delete result;
}

// Test: Negative crop_box x1/y1 values with add
TEST_F(NewQuadsFromOffsetCropboxTest_2456, NegativeCropBoxAdd_2456) {
    PDFRectangle crop_box(-10.0, -20.0, 100.0, 200.0);

    double x1[] = {50.0}, y1[] = {60.0};
    double x2[] = {70.0}, y2[] = {80.0};
    double x3[] = {90.0}, y3[] = {100.0};
    double x4[] = {110.0}, y4[] = {120.0};

    auto quads = makeQuads(1, x1, y1, x2, y2, x3, y3, x4, y4);

    AnnotQuadrilaterals *result = new_quads_from_offset_cropbox(&crop_box, quads.get(), TRUE);
    ASSERT_NE(result, nullptr);

    EXPECT_DOUBLE_EQ(result->getX1(0), 50.0 + (-10.0));
    EXPECT_DOUBLE_EQ(result->getY1(0), 60.0 + (-20.0));
    EXPECT_DOUBLE_EQ(result->getX2(0), 70.0 + (-10.0));
    EXPECT_DOUBLE_EQ(result->getY2(0), 80.0 + (-20.0));
    EXPECT_DOUBLE_EQ(result->getX3(0), 90.0 + (-10.0));
    EXPECT_DOUBLE_EQ(result->getY3(0), 100.0 + (-20.0));
    EXPECT_DOUBLE_EQ(result->getX4(0), 110.0 + (-10.0));
    EXPECT_DOUBLE_EQ(result->getY4(0), 120.0 + (-20.0));

    delete result;
}

// Test: Negative crop_box x1/y1 values with subtract
TEST_F(NewQuadsFromOffsetCropboxTest_2456, NegativeCropBoxSubtract_2456) {
    PDFRectangle crop_box(-10.0, -20.0, 100.0, 200.0);

    double x1[] = {50.0}, y1[] = {60.0};
    double x2[] = {70.0}, y2[] = {80.0};
    double x3[] = {90.0}, y3[] = {100.0};
    double x4[] = {110.0}, y4[] = {120.0};

    auto quads = makeQuads(1, x1, y1, x2, y2, x3, y3, x4, y4);

    AnnotQuadrilaterals *result = new_quads_from_offset_cropbox(&crop_box, quads.get(), FALSE);
    ASSERT_NE(result, nullptr);

    EXPECT_DOUBLE_EQ(result->getX1(0), 50.0 - (-10.0));
    EXPECT_DOUBLE_EQ(result->getY1(0), 60.0 - (-20.0));
    EXPECT_DOUBLE_EQ(result->getX2(0), 70.0 - (-10.0));
    EXPECT_DOUBLE_EQ(result->getY2(0), 80.0 - (-20.0));

    delete result;
}

// Test: Coordinates with zero values
TEST_F(NewQuadsFromOffsetCropboxTest_2456, ZeroCoordinatesAdd_2456) {
    PDFRectangle crop_box(15.0, 25.0, 100.0, 200.0);

    double x1[] = {0.0}, y1[] = {0.0};
    double x2[] = {0.0}, y2[] = {0.0};
    double x3[] = {0.0}, y3[] = {0.0};
    double x4[] = {0.0}, y4[] = {0.0};

    auto quads = makeQuads(1, x1, y1, x2, y2, x3, y3, x4, y4);

    AnnotQuadrilaterals *result = new_quads_from_offset_cropbox(&crop_box, quads.get(), TRUE);
    ASSERT_NE(result, nullptr);

    EXPECT_DOUBLE_EQ(result->getX1(0), 15.0);
    EXPECT_DOUBLE_EQ(result->getY1(0), 25.0);
    EXPECT_DOUBLE_EQ(result->getX2(0), 15.0);
    EXPECT_DOUBLE_EQ(result->getY2(0), 25.0);
    EXPECT_DOUBLE_EQ(result->getX3(0), 15.0);
    EXPECT_DOUBLE_EQ(result->getY3(0), 25.0);
    EXPECT_DOUBLE_EQ(result->getX4(0), 15.0);
    EXPECT_DOUBLE_EQ(result->getY4(0), 25.0);

    delete result;
}

// Test: Result length matches input length
TEST_F(NewQuadsFromOffsetCropboxTest_2456, ResultLengthMatchesInput_2456) {
    PDFRectangle crop_box(1.0, 2.0, 10.0, 20.0);

    const int count = 5;
    double x1[count], y1[count], x2[count], y2[count];
    double x3[count], y3[count], x4[count], y4[count];
    for (int i = 0; i < count; i++) {
        x1[i] = i * 1.0; y1[i] = i * 2.0;
        x2[i] = i * 3.0; y2[i] = i * 4.0;
        x3[i] = i * 5.0; y3[i] = i * 6.0;
        x4[i] = i * 7.0; y4[i] = i * 8.0;
    }

    auto quads = makeQuads(count, x1, y1, x2, y2, x3, y3, x4, y4);

    AnnotQuadrilaterals *result = new_quads_from_offset_cropbox(&crop_box, quads.get(), TRUE);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->getQuadrilateralsLength(), count);

    delete result;
}

// Test: Large offset values
TEST_F(NewQuadsFromOffsetCropboxTest_2456, LargeOffsetAdd_2456) {
    PDFRectangle crop_box(1e6, 1e6, 2e6, 2e6);

    double x1[] = {1.0}, y1[] = {2.0};
    double x2[] = {3.0}, y2[] = {4.0};
    double x3[] = {5.0}, y3[] = {6.0};
    double x4[] = {7.0}, y4[] = {8.0};

    auto quads = makeQuads(1, x1, y1, x2, y2, x3, y3, x4, y4);

    AnnotQuadrilaterals *result = new_quads_from_offset_cropbox(&crop_box, quads.get(), TRUE);
    ASSERT_NE(result, nullptr);

    EXPECT_DOUBLE_EQ(result->getX1(0), 1.0 + 1e6);
    EXPECT_DOUBLE_EQ(result->getY1(0), 2.0 + 1e6);

    delete result;
}

// Test: Subtraction resulting in negative coordinates
TEST_F(NewQuadsFromOffsetCropboxTest_2456, SubtractResultsInNegative_2456) {
    PDFRectangle crop_box(100.0, 200.0, 500.0, 600.0);

    double x1[] = {50.0}, y1[] = {60.0};
    double x2[] = {70.0}, y2[] = {80.0};
    double x3[] = {90.0}, y3[] = {100.0};
    double x4[] = {10.0}, y4[] = {20.0};

    auto quads = makeQuads(1, x1, y1, x2, y2, x3, y3, x4, y4);

    AnnotQuadrilaterals *result = new_quads_from_offset_cropbox(&crop_box, quads.get(), FALSE);
    ASSERT_NE(result, nullptr);

    EXPECT_DOUBLE_EQ(result->getX1(0), 50.0 - 100.0);
    EXPECT_DOUBLE_EQ(result->getY1(0), 60.0 - 200.0);
    EXPECT_DOUBLE_EQ(result->getX4(0), 10.0 - 100.0);
    EXPECT_DOUBLE_EQ(result->getY4(0), 20.0 - 200.0);

    delete result;
}

// Test: Only x1 and y1 of crop_box are used (not x2, y2)
TEST_F(NewQuadsFromOffsetCropboxTest_2456, OnlyX1Y1OfCropBoxUsed_2456) {
    PDFRectangle crop_box_a(10.0, 20.0, 999.0, 888.0);
    PDFRectangle crop_box_b(10.0, 20.0, 1.0, 2.0);

    double x1[] = {5.0}, y1[] = {6.0};
    double x2[] = {7.0}, y2[] = {8.0};
    double x3[] = {9.0}, y3[] = {10.0};
    double x4[] = {11.0}, y4[] = {12.0};

    auto quads_a = makeQuads(1, x1, y1, x2, y2, x3, y3, x4, y4);
    auto quads_b = makeQuads(1, x1, y1, x2, y2, x3, y3, x4, y4);

    AnnotQuadrilaterals *result_a = new_quads_from_offset_cropbox(&crop_box_a, quads_a.get(), TRUE);
    AnnotQuadrilaterals *result_b = new_quads_from_offset_cropbox(&crop_box_b, quads_b.get(), TRUE);

    ASSERT_NE(result_a, nullptr);
    ASSERT_NE(result_b, nullptr);

    // Since only x1 and y1 matter and they are the same, results should be identical
    EXPECT_DOUBLE_EQ(result_a->getX1(0), result_b->getX1(0));
    EXPECT_DOUBLE_EQ(result_a->getY1(0), result_b->getY1(0));
    EXPECT_DOUBLE_EQ(result_a->getX2(0), result_b->getX2(0));
    EXPECT_DOUBLE_EQ(result_a->getY2(0), result_b->getY2(0));
    EXPECT_DOUBLE_EQ(result_a->getX3(0), result_b->getX3(0));
    EXPECT_DOUBLE_EQ(result_a->getY3(0), result_b->getY3(0));
    EXPECT_DOUBLE_EQ(result_a->getX4(0), result_b->getX4(0));
    EXPECT_DOUBLE_EQ(result_a->getY4(0), result_b->getY4(0));

    delete result_a;
    delete result_b;
}

// Test: Add then subtract should restore original coordinates
TEST_F(NewQuadsFromOffsetCropboxTest_2456, AddThenSubtractRestoresOriginal_2456) {
    PDFRectangle crop_box(30.0, 40.0, 300.0, 400.0);

    double x1[] = {10.0}, y1[] = {20.0};
    double x2[] = {30.0}, y2[] = {40.0};
    double x3[] = {50.0}, y3[] = {60.0};
    double x4[] = {70.0}, y4[] = {80.0};

    auto quads = makeQuads(1, x1, y1, x2, y2, x3, y3, x4, y4);

    // First add
    AnnotQuadrilaterals *added = new_quads_from_offset_cropbox(&crop_box, quads.get(), TRUE);
    ASSERT_NE(added, nullptr);

    // Then subtract
    AnnotQuadrilaterals *restored = new_quads_from_offset_cropbox(&crop_box, added, FALSE);
    ASSERT_NE(restored, nullptr);

    EXPECT_DOUBLE_EQ(restored->getX1(0), 10.0);
    EXPECT_DOUBLE_EQ(restored->getY1(0), 20.0);
    EXPECT_DOUBLE_EQ(restored->getX2(0), 30.0);
    EXPECT_DOUBLE_EQ(restored->getY2(0), 40.0);
    EXPECT_DOUBLE_EQ(restored->getX3(0), 50.0);
    EXPECT_DOUBLE_EQ(restored->getY3(0), 60.0);
    EXPECT_DOUBLE_EQ(restored->getX4(0), 70.0);
    EXPECT_DOUBLE_EQ(restored->getY4(0), 80.0);

    delete added;
    delete restored;
}

// Test: Fractional coordinates
TEST_F(NewQuadsFromOffsetCropboxTest_2456, FractionalCoordinates_2456) {
    PDFRectangle crop_box(0.5, 0.25, 10.0, 20.0);

    double x1[] = {1.1}, y1[] = {2.2};
    double x2[] = {3.3}, y2[] = {4.4};
    double x3[] = {5.5}, y3[] = {6.6};
    double x4[] = {7.7}, y4[] = {8.8};

    auto quads = makeQuads(1, x1, y1, x2, y2, x3, y3, x4, y4);

    AnnotQuadrilaterals *result = new_quads_from_offset_cropbox(&crop_box, quads.get(), TRUE);
    ASSERT_NE(result, nullptr);

    EXPECT_DOUBLE_EQ(result->getX1(0), 1.1 + 0.5);
    EXPECT_DOUBLE_EQ(result->getY1(0), 2.2 + 0.25);
    EXPECT_DOUBLE_EQ(result->getX2(0), 3.3 + 0.5);
    EXPECT_DOUBLE_EQ(result->getY2(0), 4.4 + 0.25);

    delete result;
}
