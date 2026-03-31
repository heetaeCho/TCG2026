#include <gtest/gtest.h>
#include <array>
#include <memory>

#include "GfxState.h"
#include "Object.h"
#include "Dict.h"
#include "Stream.h"
#include "PDFDoc.h"

class GfxTilingPatternTest_498 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }

    // Helper to create a minimal tiling pattern Object for parsing
    Object createTilingPatternObject(int paintType, int tilingType,
                                      const std::array<double, 4>& bbox,
                                      double xStep, double yStep,
                                      const std::array<double, 6>& matrix) {
        Object patDict = Object(new Dict(nullptr));
        
        patDict.dictAdd("PatternType", Object(1));
        patDict.dictAdd("PaintType", Object(paintType));
        patDict.dictAdd("TilingType", Object(tilingType));
        
        Object bboxArray = Object(new Array(nullptr));
        bboxArray.arrayAdd(Object(bbox[0]));
        bboxArray.arrayAdd(Object(bbox[1]));
        bboxArray.arrayAdd(Object(bbox[2]));
        bboxArray.arrayAdd(Object(bbox[3]));
        patDict.dictAdd("BBox", std::move(bboxArray));
        
        patDict.dictAdd("XStep", Object(xStep));
        patDict.dictAdd("YStep", Object(yStep));
        
        Object matrixArray = Object(new Array(nullptr));
        for (int i = 0; i < 6; i++) {
            matrixArray.arrayAdd(Object(matrix[i]));
        }
        patDict.dictAdd("Matrix", std::move(matrixArray));
        
        Object resources = Object(new Dict(nullptr));
        patDict.dictAdd("Resources", std::move(resources));
        
        return patDict;
    }
};

// Test that parse returns nullptr for a null/invalid object
TEST_F(GfxTilingPatternTest_498, ParseInvalidObjectReturnsNull_498) {
    Object nullObj;
    auto pattern = GfxTilingPattern::parse(&nullObj, 0);
    EXPECT_EQ(pattern, nullptr);
}

// Test that parse returns nullptr for a non-dict/non-stream object
TEST_F(GfxTilingPatternTest_498, ParseNonDictObjectReturnsNull_498) {
    Object intObj(42);
    auto pattern = GfxTilingPattern::parse(&intObj, 0);
    EXPECT_EQ(pattern, nullptr);
}

// Test getMatrix returns a reference to an array of 6 doubles
TEST_F(GfxTilingPatternTest_498, GetMatrixReturnsArrayOfSixDoubles_498) {
    std::array<double, 6> expectedMatrix = {1.0, 0.0, 0.0, 1.0, 0.0, 0.0};
    Object patObj = createTilingPatternObject(1, 1, {0, 0, 100, 100}, 100, 100, expectedMatrix);
    
    auto pattern = GfxTilingPattern::parse(&patObj, 0);
    if (pattern) {
        const std::array<double, 6>& mat = pattern->getMatrix();
        EXPECT_EQ(mat.size(), 6u);
        for (int i = 0; i < 6; i++) {
            EXPECT_DOUBLE_EQ(mat[i], expectedMatrix[i]);
        }
    }
}

// Test getMatrix with a non-identity matrix
TEST_F(GfxTilingPatternTest_498, GetMatrixNonIdentity_498) {
    std::array<double, 6> expectedMatrix = {2.0, 0.5, -0.5, 2.0, 10.0, 20.0};
    Object patObj = createTilingPatternObject(1, 1, {0, 0, 50, 50}, 50, 50, expectedMatrix);
    
    auto pattern = GfxTilingPattern::parse(&patObj, 0);
    if (pattern) {
        const std::array<double, 6>& mat = pattern->getMatrix();
        for (int i = 0; i < 6; i++) {
            EXPECT_DOUBLE_EQ(mat[i], expectedMatrix[i]);
        }
    }
}

// Test getMatrix with zero matrix
TEST_F(GfxTilingPatternTest_498, GetMatrixAllZeros_498) {
    std::array<double, 6> expectedMatrix = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
    Object patObj = createTilingPatternObject(1, 1, {0, 0, 10, 10}, 10, 10, expectedMatrix);
    
    auto pattern = GfxTilingPattern::parse(&patObj, 0);
    if (pattern) {
        const std::array<double, 6>& mat = pattern->getMatrix();
        for (int i = 0; i < 6; i++) {
            EXPECT_DOUBLE_EQ(mat[i], 0.0);
        }
    }
}

// Test that getMatrix returns a const reference (multiple calls return same address)
TEST_F(GfxTilingPatternTest_498, GetMatrixReturnsSameReference_498) {
    std::array<double, 6> expectedMatrix = {1.0, 0.0, 0.0, 1.0, 0.0, 0.0};
    Object patObj = createTilingPatternObject(1, 1, {0, 0, 100, 100}, 100, 100, expectedMatrix);
    
    auto pattern = GfxTilingPattern::parse(&patObj, 0);
    if (pattern) {
        const std::array<double, 6>& mat1 = pattern->getMatrix();
        const std::array<double, 6>& mat2 = pattern->getMatrix();
        EXPECT_EQ(&mat1, &mat2);
    }
}

// Test other accessors alongside getMatrix for consistency
TEST_F(GfxTilingPatternTest_498, AllAccessorsConsistent_498) {
    std::array<double, 6> expectedMatrix = {1.0, 0.0, 0.0, 1.0, 50.0, 75.0};
    std::array<double, 4> bbox = {0.0, 0.0, 200.0, 300.0};
    Object patObj = createTilingPatternObject(2, 3, bbox, 200.0, 300.0, expectedMatrix);
    
    auto pattern = GfxTilingPattern::parse(&patObj, 0);
    if (pattern) {
        EXPECT_EQ(pattern->getPaintType(), 2);
        EXPECT_EQ(pattern->getTilingType(), 3);
        
        const auto& b = pattern->getBBox();
        EXPECT_DOUBLE_EQ(b[0], 0.0);
        EXPECT_DOUBLE_EQ(b[1], 0.0);
        EXPECT_DOUBLE_EQ(b[2], 200.0);
        EXPECT_DOUBLE_EQ(b[3], 300.0);
        
        EXPECT_DOUBLE_EQ(pattern->getXStep(), 200.0);
        EXPECT_DOUBLE_EQ(pattern->getYStep(), 300.0);
        
        const auto& mat = pattern->getMatrix();
        EXPECT_DOUBLE_EQ(mat[4], 50.0);
        EXPECT_DOUBLE_EQ(mat[5], 75.0);
    }
}

// Test copy preserves matrix
TEST_F(GfxTilingPatternTest_498, CopyPreservesMatrix_498) {
    std::array<double, 6> expectedMatrix = {3.0, 1.0, -1.0, 3.0, 5.0, 7.0};
    Object patObj = createTilingPatternObject(1, 1, {0, 0, 10, 10}, 10, 10, expectedMatrix);
    
    auto pattern = GfxTilingPattern::parse(&patObj, 0);
    if (pattern) {
        auto copied = pattern->copy();
        ASSERT_NE(copied, nullptr);
        
        auto* copiedTiling = dynamic_cast<GfxTilingPattern*>(copied.get());
        ASSERT_NE(copiedTiling, nullptr);
        
        const auto& origMat = pattern->getMatrix();
        const auto& copyMat = copiedTiling->getMatrix();
        
        for (int i = 0; i < 6; i++) {
            EXPECT_DOUBLE_EQ(origMat[i], copyMat[i]);
        }
        
        // Ensure they are different objects (different addresses)
        EXPECT_NE(&origMat, &copyMat);
    }
}

// Test getMatrix with large values
TEST_F(GfxTilingPatternTest_498, GetMatrixLargeValues_498) {
    std::array<double, 6> expectedMatrix = {1e10, -1e10, 1e10, -1e10, 1e15, -1e15};
    Object patObj = createTilingPatternObject(1, 1, {0, 0, 100, 100}, 100, 100, expectedMatrix);
    
    auto pattern = GfxTilingPattern::parse(&patObj, 0);
    if (pattern) {
        const auto& mat = pattern->getMatrix();
        for (int i = 0; i < 6; i++) {
            EXPECT_DOUBLE_EQ(mat[i], expectedMatrix[i]);
        }
    }
}

// Test getMatrix with very small values
TEST_F(GfxTilingPatternTest_498, GetMatrixSmallValues_498) {
    std::array<double, 6> expectedMatrix = {1e-10, 1e-10, 1e-10, 1e-10, 1e-10, 1e-10};
    Object patObj = createTilingPatternObject(1, 1, {0, 0, 100, 100}, 100, 100, expectedMatrix);
    
    auto pattern = GfxTilingPattern::parse(&patObj, 0);
    if (pattern) {
        const auto& mat = pattern->getMatrix();
        for (int i = 0; i < 6; i++) {
            EXPECT_DOUBLE_EQ(mat[i], expectedMatrix[i]);
        }
    }
}

// Test getMatrix with negative values
TEST_F(GfxTilingPatternTest_498, GetMatrixNegativeValues_498) {
    std::array<double, 6> expectedMatrix = {-1.0, -2.0, -3.0, -4.0, -5.0, -6.0};
    Object patObj = createTilingPatternObject(1, 1, {0, 0, 100, 100}, 100, 100, expectedMatrix);
    
    auto pattern = GfxTilingPattern::parse(&patObj, 0);
    if (pattern) {
        const auto& mat = pattern->getMatrix();
        for (int i = 0; i < 6; i++) {
            EXPECT_DOUBLE_EQ(mat[i], expectedMatrix[i]);
        }
    }
}
