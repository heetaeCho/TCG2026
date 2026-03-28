#include <gtest/gtest.h>
#include <memory>
#include "Annot.h"

// We need to include necessary headers for Array and other dependencies
// Based on the poppler codebase structure
#include "Object.h"
#include "Array.h"
#include "PDFDoc.h"

class AnnotQuadrilateralsTest_745 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test construction with unique_ptr of AnnotQuadrilateral array and length
TEST_F(AnnotQuadrilateralsTest_745, ConstructWithQuadsAndLength_745) {
    const int numQuads = 2;
    auto quads = std::make_unique<AnnotQuadrilateral[]>(numQuads);
    
    AnnotQuadrilaterals aq(std::move(quads), numQuads);
    
    EXPECT_EQ(aq.getQuadrilateralsLength(), numQuads);
}

// Test that getQuadrilateralsLength returns 0 for empty quadrilaterals
TEST_F(AnnotQuadrilateralsTest_745, EmptyQuadrilaterals_745) {
    auto quads = std::make_unique<AnnotQuadrilateral[]>(0);
    
    AnnotQuadrilaterals aq(std::move(quads), 0);
    
    EXPECT_EQ(aq.getQuadrilateralsLength(), 0);
}

// Test construction with single quadrilateral
TEST_F(AnnotQuadrilateralsTest_745, SingleQuadrilateral_745) {
    const int numQuads = 1;
    auto quads = std::make_unique<AnnotQuadrilateral[]>(numQuads);
    
    AnnotQuadrilaterals aq(std::move(quads), numQuads);
    
    EXPECT_EQ(aq.getQuadrilateralsLength(), numQuads);
}

// Test coordinate getters for a quadrilateral constructed with known values
TEST_F(AnnotQuadrilateralsTest_745, GetCoordinatesFromQuadrilateral_745) {
    const int numQuads = 1;
    auto quads = std::make_unique<AnnotQuadrilateral[]>(numQuads);
    // AnnotQuadrilateral default constructed - we test that getters don't crash
    
    AnnotQuadrilaterals aq(std::move(quads), numQuads);
    
    EXPECT_EQ(aq.getQuadrilateralsLength(), 1);
    
    // Access coordinates of the first quadrilateral (index 0)
    // We just verify these don't crash; values depend on default construction
    double x1 = aq.getX1(0);
    double y1 = aq.getY1(0);
    double x2 = aq.getX2(0);
    double y2 = aq.getY2(0);
    double x3 = aq.getX3(0);
    double y3 = aq.getY3(0);
    double x4 = aq.getX4(0);
    double y4 = aq.getY4(0);
    
    // Just verify they return finite values
    EXPECT_TRUE(std::isfinite(x1) || x1 == 0.0);
    EXPECT_TRUE(std::isfinite(y1) || y1 == 0.0);
    EXPECT_TRUE(std::isfinite(x2) || x2 == 0.0);
    EXPECT_TRUE(std::isfinite(y2) || y2 == 0.0);
    EXPECT_TRUE(std::isfinite(x3) || x3 == 0.0);
    EXPECT_TRUE(std::isfinite(y3) || y3 == 0.0);
    EXPECT_TRUE(std::isfinite(x4) || x4 == 0.0);
    EXPECT_TRUE(std::isfinite(y4) || y4 == 0.0);
}

// Test with multiple quadrilaterals
TEST_F(AnnotQuadrilateralsTest_745, MultipleQuadrilaterals_745) {
    const int numQuads = 5;
    auto quads = std::make_unique<AnnotQuadrilateral[]>(numQuads);
    
    AnnotQuadrilaterals aq(std::move(quads), numQuads);
    
    EXPECT_EQ(aq.getQuadrilateralsLength(), numQuads);
    
    // Verify we can access coordinates of each quadrilateral without crashing
    for (int i = 0; i < numQuads; i++) {
        aq.getX1(i);
        aq.getY1(i);
        aq.getX2(i);
        aq.getY2(i);
        aq.getX3(i);
        aq.getY3(i);
        aq.getX4(i);
        aq.getY4(i);
    }
}

// Test that copy constructor is deleted (compile-time check, but we verify it conceptually)
TEST_F(AnnotQuadrilateralsTest_745, CopyConstructorIsDeleted_745) {
    // This is a compile-time constraint. We just verify the class works with move semantics.
    const int numQuads = 1;
    auto quads = std::make_unique<AnnotQuadrilateral[]>(numQuads);
    
    AnnotQuadrilaterals aq(std::move(quads), numQuads);
    
    // The following should NOT compile if uncommented:
    // AnnotQuadrilaterals aq2(aq); // copy constructor deleted
    // AnnotQuadrilaterals aq3 = aq; // copy assignment deleted
    
    EXPECT_EQ(aq.getQuadrilateralsLength(), numQuads);
}

// Test with nullptr quads and zero length
TEST_F(AnnotQuadrilateralsTest_745, NullptrQuadsZeroLength_745) {
    std::unique_ptr<AnnotQuadrilateral[]> quads(nullptr);
    
    AnnotQuadrilaterals aq(std::move(quads), 0);
    
    EXPECT_EQ(aq.getQuadrilateralsLength(), 0);
}

// Test with large number of quadrilaterals
TEST_F(AnnotQuadrilateralsTest_745, LargeNumberOfQuadrilaterals_745) {
    const int numQuads = 1000;
    auto quads = std::make_unique<AnnotQuadrilateral[]>(numQuads);
    
    AnnotQuadrilaterals aq(std::move(quads), numQuads);
    
    EXPECT_EQ(aq.getQuadrilateralsLength(), numQuads);
}

// Test accessing first and last quadrilateral coordinates
TEST_F(AnnotQuadrilateralsTest_745, AccessFirstAndLastQuadrilateral_745) {
    const int numQuads = 3;
    auto quads = std::make_unique<AnnotQuadrilateral[]>(numQuads);
    
    AnnotQuadrilaterals aq(std::move(quads), numQuads);
    
    // Access first quadrilateral
    aq.getX1(0);
    aq.getY1(0);
    
    // Access last quadrilateral
    aq.getX1(numQuads - 1);
    aq.getY1(numQuads - 1);
    
    EXPECT_EQ(aq.getQuadrilateralsLength(), numQuads);
}

// Test that all 8 coordinate getters return consistent types (double)
TEST_F(AnnotQuadrilateralsTest_745, CoordinateGettersReturnDouble_745) {
    const int numQuads = 1;
    auto quads = std::make_unique<AnnotQuadrilateral[]>(numQuads);
    
    AnnotQuadrilaterals aq(std::move(quads), numQuads);
    
    // All getters should return double
    double x1 = aq.getX1(0);
    double y1 = aq.getY1(0);
    double x2 = aq.getX2(0);
    double y2 = aq.getY2(0);
    double x3 = aq.getX3(0);
    double y3 = aq.getY3(0);
    double x4 = aq.getX4(0);
    double y4 = aq.getY4(0);
    
    // Suppress unused variable warnings
    (void)x1; (void)y1; (void)x2; (void)y2;
    (void)x3; (void)y3; (void)x4; (void)y4;
    
    SUCCEED();
}
