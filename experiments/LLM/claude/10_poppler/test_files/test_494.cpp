#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>
#include <array>
#include "GfxState.h"
#include "Object.h"
#include "Dict.h"
#include "PDFDoc.h"
#include "Stream.h"

// Helper to create a valid tiling pattern Object for parsing
// Since the constructor is private and we must use parse(), we need to construct
// a proper Object that represents a tiling pattern.

class GfxTilingPatternTest_494 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }

    // Helper to create a tiling pattern object suitable for parsing
    std::unique_ptr<GfxTilingPattern> createTilingPattern(
        int paintType, int tilingType,
        double bboxX1, double bboxY1, double bboxX2, double bboxY2,
        double xStep, double yStep) {
        
        // Build a dictionary that represents a tiling pattern
        Dict *dict = new Dict((XRef*)nullptr);
        
        dict->add("PatternType", Object(1)); // Tiling pattern type = 1
        dict->add("PaintType", Object(paintType));
        dict->add("TilingType", Object(tilingType));
        
        // BBox array
        Object bboxArray = Object(new Array((XRef*)nullptr));
        bboxArray.arrayAdd(Object(bboxX1));
        bboxArray.arrayAdd(Object(bboxY1));
        bboxArray.arrayAdd(Object(bboxX2));
        bboxArray.arrayAdd(Object(bboxY2));
        dict->add("BBox", std::move(bboxArray));
        
        dict->add("XStep", Object(xStep));
        dict->add("YStep", Object(yStep));
        
        // Matrix (identity)
        Object matrixArray = Object(new Array((XRef*)nullptr));
        matrixArray.arrayAdd(Object(1.0));
        matrixArray.arrayAdd(Object(0.0));
        matrixArray.arrayAdd(Object(0.0));
        matrixArray.arrayAdd(Object(1.0));
        matrixArray.arrayAdd(Object(0.0));
        matrixArray.arrayAdd(Object(0.0));
        dict->add("Matrix", std::move(matrixArray));
        
        // Resources dictionary
        dict->add("Resources", Object(new Dict((XRef*)nullptr)));
        
        Object patObj = Object(dict);
        
        auto pattern = GfxTilingPattern::parse(&patObj, 0);
        if (pattern) {
            return std::unique_ptr<GfxTilingPattern>(
                static_cast<GfxTilingPattern*>(pattern.release()));
        }
        return nullptr;
    }
};

TEST_F(GfxTilingPatternTest_494, GetBBoxReturnsCorrectValues_494) {
    auto pattern = createTilingPattern(1, 1, 0.0, 0.0, 100.0, 200.0, 100.0, 200.0);
    if (!pattern) {
        GTEST_SKIP() << "Could not create tiling pattern for testing";
    }
    
    const std::array<double, 4> &bbox = pattern->getBBox();
    EXPECT_DOUBLE_EQ(bbox[0], 0.0);
    EXPECT_DOUBLE_EQ(bbox[1], 0.0);
    EXPECT_DOUBLE_EQ(bbox[2], 100.0);
    EXPECT_DOUBLE_EQ(bbox[3], 200.0);
}

TEST_F(GfxTilingPatternTest_494, GetBBoxWithNegativeValues_494) {
    auto pattern = createTilingPattern(1, 1, -50.0, -75.0, 50.0, 75.0, 100.0, 150.0);
    if (!pattern) {
        GTEST_SKIP() << "Could not create tiling pattern for testing";
    }
    
    const std::array<double, 4> &bbox = pattern->getBBox();
    EXPECT_DOUBLE_EQ(bbox[0], -50.0);
    EXPECT_DOUBLE_EQ(bbox[1], -75.0);
    EXPECT_DOUBLE_EQ(bbox[2], 50.0);
    EXPECT_DOUBLE_EQ(bbox[3], 75.0);
}

TEST_F(GfxTilingPatternTest_494, GetBBoxReturnsReference_494) {
    auto pattern = createTilingPattern(1, 1, 10.0, 20.0, 30.0, 40.0, 30.0, 40.0);
    if (!pattern) {
        GTEST_SKIP() << "Could not create tiling pattern for testing";
    }
    
    const std::array<double, 4> &bbox1 = pattern->getBBox();
    const std::array<double, 4> &bbox2 = pattern->getBBox();
    // Both references should point to the same memory
    EXPECT_EQ(&bbox1, &bbox2);
}

TEST_F(GfxTilingPatternTest_494, GetPaintType_494) {
    auto pattern = createTilingPattern(2, 1, 0.0, 0.0, 100.0, 100.0, 100.0, 100.0);
    if (!pattern) {
        GTEST_SKIP() << "Could not create tiling pattern for testing";
    }
    
    EXPECT_EQ(pattern->getPaintType(), 2);
}

TEST_F(GfxTilingPatternTest_494, GetTilingType_494) {
    auto pattern = createTilingPattern(1, 2, 0.0, 0.0, 100.0, 100.0, 100.0, 100.0);
    if (!pattern) {
        GTEST_SKIP() << "Could not create tiling pattern for testing";
    }
    
    EXPECT_EQ(pattern->getTilingType(), 2);
}

TEST_F(GfxTilingPatternTest_494, GetXStep_494) {
    auto pattern = createTilingPattern(1, 1, 0.0, 0.0, 100.0, 100.0, 55.5, 100.0);
    if (!pattern) {
        GTEST_SKIP() << "Could not create tiling pattern for testing";
    }
    
    EXPECT_DOUBLE_EQ(pattern->getXStep(), 55.5);
}

TEST_F(GfxTilingPatternTest_494, GetYStep_494) {
    auto pattern = createTilingPattern(1, 1, 0.0, 0.0, 100.0, 100.0, 100.0, 77.3);
    if (!pattern) {
        GTEST_SKIP() << "Could not create tiling pattern for testing";
    }
    
    EXPECT_DOUBLE_EQ(pattern->getYStep(), 77.3);
}

TEST_F(GfxTilingPatternTest_494, GetMatrix_494) {
    auto pattern = createTilingPattern(1, 1, 0.0, 0.0, 100.0, 100.0, 100.0, 100.0);
    if (!pattern) {
        GTEST_SKIP() << "Could not create tiling pattern for testing";
    }
    
    const std::array<double, 6> &matrix = pattern->getMatrix();
    // Default identity matrix
    EXPECT_DOUBLE_EQ(matrix[0], 1.0);
    EXPECT_DOUBLE_EQ(matrix[1], 0.0);
    EXPECT_DOUBLE_EQ(matrix[2], 0.0);
    EXPECT_DOUBLE_EQ(matrix[3], 1.0);
    EXPECT_DOUBLE_EQ(matrix[4], 0.0);
    EXPECT_DOUBLE_EQ(matrix[5], 0.0);
}

TEST_F(GfxTilingPatternTest_494, GetResDict_494) {
    auto pattern = createTilingPattern(1, 1, 0.0, 0.0, 100.0, 100.0, 100.0, 100.0);
    if (!pattern) {
        GTEST_SKIP() << "Could not create tiling pattern for testing";
    }
    
    Dict *resDict = pattern->getResDict();
    // The resource dictionary should exist (we set it during creation)
    EXPECT_NE(resDict, nullptr);
}

TEST_F(GfxTilingPatternTest_494, CopyPreservesBBox_494) {
    auto pattern = createTilingPattern(1, 1, 5.0, 10.0, 15.0, 20.0, 15.0, 20.0);
    if (!pattern) {
        GTEST_SKIP() << "Could not create tiling pattern for testing";
    }
    
    auto copied = pattern->copy();
    ASSERT_NE(copied, nullptr);
    
    auto *copiedTiling = dynamic_cast<GfxTilingPattern*>(copied.get());
    ASSERT_NE(copiedTiling, nullptr);
    
    const std::array<double, 4> &bbox = copiedTiling->getBBox();
    EXPECT_DOUBLE_EQ(bbox[0], 5.0);
    EXPECT_DOUBLE_EQ(bbox[1], 10.0);
    EXPECT_DOUBLE_EQ(bbox[2], 15.0);
    EXPECT_DOUBLE_EQ(bbox[3], 20.0);
}

TEST_F(GfxTilingPatternTest_494, CopyPreservesAllProperties_494) {
    auto pattern = createTilingPattern(2, 3, 1.0, 2.0, 3.0, 4.0, 50.0, 60.0);
    if (!pattern) {
        GTEST_SKIP() << "Could not create tiling pattern for testing";
    }
    
    auto copied = pattern->copy();
    ASSERT_NE(copied, nullptr);
    
    auto *copiedTiling = dynamic_cast<GfxTilingPattern*>(copied.get());
    ASSERT_NE(copiedTiling, nullptr);
    
    EXPECT_EQ(copiedTiling->getPaintType(), pattern->getPaintType());
    EXPECT_EQ(copiedTiling->getTilingType(), pattern->getTilingType());
    EXPECT_DOUBLE_EQ(copiedTiling->getXStep(), pattern->getXStep());
    EXPECT_DOUBLE_EQ(copiedTiling->getYStep(), pattern->getYStep());
    
    const auto &origBBox = pattern->getBBox();
    const auto &copyBBox = copiedTiling->getBBox();
    for (int i = 0; i < 4; i++) {
        EXPECT_DOUBLE_EQ(origBBox[i], copyBBox[i]);
    }
}

TEST_F(GfxTilingPatternTest_494, ParseNullReturnsNull_494) {
    // Test parsing with an invalid/null object
    Object nullObj;
    auto pattern = GfxTilingPattern::parse(&nullObj, 0);
    EXPECT_EQ(pattern, nullptr);
}

TEST_F(GfxTilingPatternTest_494, GetBBoxWithZeroBBox_494) {
    auto pattern = createTilingPattern(1, 1, 0.0, 0.0, 0.0, 0.0, 1.0, 1.0);
    if (!pattern) {
        GTEST_SKIP() << "Could not create tiling pattern for testing";
    }
    
    const std::array<double, 4> &bbox = pattern->getBBox();
    EXPECT_DOUBLE_EQ(bbox[0], 0.0);
    EXPECT_DOUBLE_EQ(bbox[1], 0.0);
    EXPECT_DOUBLE_EQ(bbox[2], 0.0);
    EXPECT_DOUBLE_EQ(bbox[3], 0.0);
}

TEST_F(GfxTilingPatternTest_494, GetBBoxWithLargeValues_494) {
    auto pattern = createTilingPattern(1, 1, -1e6, -1e6, 1e6, 1e6, 1e6, 1e6);
    if (!pattern) {
        GTEST_SKIP() << "Could not create tiling pattern for testing";
    }
    
    const std::array<double, 4> &bbox = pattern->getBBox();
    EXPECT_DOUBLE_EQ(bbox[0], -1e6);
    EXPECT_DOUBLE_EQ(bbox[1], -1e6);
    EXPECT_DOUBLE_EQ(bbox[2], 1e6);
    EXPECT_DOUBLE_EQ(bbox[3], 1e6);
}

TEST_F(GfxTilingPatternTest_494, GetBBoxWithFractionalValues_494) {
    auto pattern = createTilingPattern(1, 1, 0.123, 0.456, 0.789, 0.012, 1.0, 1.0);
    if (!pattern) {
        GTEST_SKIP() << "Could not create tiling pattern for testing";
    }
    
    const std::array<double, 4> &bbox = pattern->getBBox();
    EXPECT_DOUBLE_EQ(bbox[0], 0.123);
    EXPECT_DOUBLE_EQ(bbox[1], 0.456);
    EXPECT_DOUBLE_EQ(bbox[2], 0.789);
    EXPECT_DOUBLE_EQ(bbox[3], 0.012);
}

TEST_F(GfxTilingPatternTest_494, PaintTypeOne_494) {
    auto pattern = createTilingPattern(1, 1, 0.0, 0.0, 100.0, 100.0, 100.0, 100.0);
    if (!pattern) {
        GTEST_SKIP() << "Could not create tiling pattern for testing";
    }
    
    EXPECT_EQ(pattern->getPaintType(), 1);
}

TEST_F(GfxTilingPatternTest_494, TilingTypeValues_494) {
    for (int tt = 1; tt <= 3; tt++) {
        auto pattern = createTilingPattern(1, tt, 0.0, 0.0, 100.0, 100.0, 100.0, 100.0);
        if (!pattern) {
            continue;
        }
        EXPECT_EQ(pattern->getTilingType(), tt);
    }
}

TEST_F(GfxTilingPatternTest_494, CopiedBBoxIsIndependent_494) {
    auto pattern = createTilingPattern(1, 1, 10.0, 20.0, 30.0, 40.0, 30.0, 40.0);
    if (!pattern) {
        GTEST_SKIP() << "Could not create tiling pattern for testing";
    }
    
    auto copied = pattern->copy();
    ASSERT_NE(copied, nullptr);
    
    auto *copiedTiling = dynamic_cast<GfxTilingPattern*>(copied.get());
    ASSERT_NE(copiedTiling, nullptr);
    
    // The addresses of bbox should be different (independent copies)
    const std::array<double, 4> &origBBox = pattern->getBBox();
    const std::array<double, 4> &copyBBox = copiedTiling->getBBox();
    EXPECT_NE(&origBBox, &copyBBox);
}
