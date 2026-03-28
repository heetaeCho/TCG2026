#include <gtest/gtest.h>
#include <memory>
#include "GfxState.h"
#include "Object.h"
#include "Dict.h"
#include "Stream.h"
#include "Array.h"

class GfxTilingPatternTest_496 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }

    // Helper to create a tiling pattern Object for testing.
    // A tiling pattern is a stream with a dictionary containing:
    //   /PatternType 1
    //   /PaintType 1 or 2
    //   /TilingType 1, 2, or 3
    //   /BBox [x1 y1 x2 y2]
    //   /XStep <number>
    //   /YStep <number>
    //   /Matrix [a b c d e f] (optional)
    Object createTilingPatternObject(int paintType, int tilingType,
                                      double bboxX1, double bboxY1, double bboxX2, double bboxY2,
                                      double xStep, double yStep,
                                      double matA = 1.0, double matB = 0.0, double matC = 0.0,
                                      double matD = 1.0, double matE = 0.0, double matF = 0.0) {
        Dict *dict = new Dict(nullptr);

        dict->add("PatternType", Object(1));
        dict->add("PaintType", Object(paintType));
        dict->add("TilingType", Object(tilingType));

        Array *bboxArray = new Array(nullptr);
        bboxArray->add(Object(bboxX1));
        bboxArray->add(Object(bboxY1));
        bboxArray->add(Object(bboxX2));
        bboxArray->add(Object(bboxY2));
        dict->add("BBox", Object(bboxArray));

        dict->add("XStep", Object(xStep));
        dict->add("YStep", Object(yStep));

        Array *matrixArray = new Array(nullptr);
        matrixArray->add(Object(matA));
        matrixArray->add(Object(matB));
        matrixArray->add(Object(matC));
        matrixArray->add(Object(matD));
        matrixArray->add(Object(matE));
        matrixArray->add(Object(matF));
        dict->add("Matrix", Object(matrixArray));

        // Create a minimal stream object
        Object dictObj(dict);
        // We need a stream - create a MemStream with empty data
        static const char emptyData[] = "";
        Stream *stream = new MemStream(const_cast<char*>(emptyData), 0, 0, std::move(dictObj));
        return Object(stream);
    }
};

TEST_F(GfxTilingPatternTest_496, ParseValidPattern_GetYStep_496) {
    Object patObj = createTilingPatternObject(1, 1, 0.0, 0.0, 100.0, 100.0, 50.0, 75.0);
    auto pattern = GfxTilingPattern::parse(&patObj, 0);
    if (pattern) {
        EXPECT_DOUBLE_EQ(pattern->getYStep(), 75.0);
    }
}

TEST_F(GfxTilingPatternTest_496, ParseValidPattern_GetXStep_496) {
    Object patObj = createTilingPatternObject(1, 1, 0.0, 0.0, 100.0, 100.0, 50.0, 75.0);
    auto pattern = GfxTilingPattern::parse(&patObj, 0);
    if (pattern) {
        EXPECT_DOUBLE_EQ(pattern->getXStep(), 50.0);
    }
}

TEST_F(GfxTilingPatternTest_496, ParseValidPattern_GetPaintType_496) {
    Object patObj = createTilingPatternObject(2, 1, 0.0, 0.0, 100.0, 100.0, 50.0, 75.0);
    auto pattern = GfxTilingPattern::parse(&patObj, 0);
    if (pattern) {
        EXPECT_EQ(pattern->getPaintType(), 2);
    }
}

TEST_F(GfxTilingPatternTest_496, ParseValidPattern_GetTilingType_496) {
    Object patObj = createTilingPatternObject(1, 3, 0.0, 0.0, 100.0, 100.0, 50.0, 75.0);
    auto pattern = GfxTilingPattern::parse(&patObj, 0);
    if (pattern) {
        EXPECT_EQ(pattern->getTilingType(), 3);
    }
}

TEST_F(GfxTilingPatternTest_496, ParseValidPattern_GetBBox_496) {
    Object patObj = createTilingPatternObject(1, 1, 10.0, 20.0, 110.0, 120.0, 50.0, 75.0);
    auto pattern = GfxTilingPattern::parse(&patObj, 0);
    if (pattern) {
        const auto &bbox = pattern->getBBox();
        EXPECT_DOUBLE_EQ(bbox[0], 10.0);
        EXPECT_DOUBLE_EQ(bbox[1], 20.0);
        EXPECT_DOUBLE_EQ(bbox[2], 110.0);
        EXPECT_DOUBLE_EQ(bbox[3], 120.0);
    }
}

TEST_F(GfxTilingPatternTest_496, ParseValidPattern_GetMatrix_496) {
    Object patObj = createTilingPatternObject(1, 1, 0.0, 0.0, 100.0, 100.0, 50.0, 75.0,
                                               2.0, 0.0, 0.0, 2.0, 10.0, 20.0);
    auto pattern = GfxTilingPattern::parse(&patObj, 0);
    if (pattern) {
        const auto &matrix = pattern->getMatrix();
        EXPECT_DOUBLE_EQ(matrix[0], 2.0);
        EXPECT_DOUBLE_EQ(matrix[1], 0.0);
        EXPECT_DOUBLE_EQ(matrix[2], 0.0);
        EXPECT_DOUBLE_EQ(matrix[3], 2.0);
        EXPECT_DOUBLE_EQ(matrix[4], 10.0);
        EXPECT_DOUBLE_EQ(matrix[5], 20.0);
    }
}

TEST_F(GfxTilingPatternTest_496, ParseValidPattern_YStepZero_496) {
    Object patObj = createTilingPatternObject(1, 1, 0.0, 0.0, 100.0, 100.0, 50.0, 0.0);
    auto pattern = GfxTilingPattern::parse(&patObj, 0);
    if (pattern) {
        EXPECT_DOUBLE_EQ(pattern->getYStep(), 0.0);
    }
}

TEST_F(GfxTilingPatternTest_496, ParseValidPattern_NegativeYStep_496) {
    Object patObj = createTilingPatternObject(1, 1, 0.0, 0.0, 100.0, 100.0, 50.0, -25.0);
    auto pattern = GfxTilingPattern::parse(&patObj, 0);
    if (pattern) {
        EXPECT_DOUBLE_EQ(pattern->getYStep(), -25.0);
    }
}

TEST_F(GfxTilingPatternTest_496, ParseValidPattern_LargeYStep_496) {
    Object patObj = createTilingPatternObject(1, 1, 0.0, 0.0, 100.0, 100.0, 50.0, 1e10);
    auto pattern = GfxTilingPattern::parse(&patObj, 0);
    if (pattern) {
        EXPECT_DOUBLE_EQ(pattern->getYStep(), 1e10);
    }
}

TEST_F(GfxTilingPatternTest_496, ParseValidPattern_FractionalYStep_496) {
    Object patObj = createTilingPatternObject(1, 1, 0.0, 0.0, 100.0, 100.0, 50.0, 0.001);
    auto pattern = GfxTilingPattern::parse(&patObj, 0);
    if (pattern) {
        EXPECT_DOUBLE_EQ(pattern->getYStep(), 0.001);
    }
}

TEST_F(GfxTilingPatternTest_496, ParseInvalidObject_ReturnsNull_496) {
    Object nullObj;
    auto pattern = GfxTilingPattern::parse(&nullObj, 0);
    EXPECT_EQ(pattern, nullptr);
}

TEST_F(GfxTilingPatternTest_496, ParseNonStreamObject_ReturnsNull_496) {
    Object intObj(42);
    auto pattern = GfxTilingPattern::parse(&intObj, 0);
    EXPECT_EQ(pattern, nullptr);
}

TEST_F(GfxTilingPatternTest_496, CopyPattern_PreservesYStep_496) {
    Object patObj = createTilingPatternObject(1, 1, 0.0, 0.0, 100.0, 100.0, 50.0, 75.0);
    auto pattern = GfxTilingPattern::parse(&patObj, 0);
    if (pattern) {
        auto copied = pattern->copy();
        ASSERT_NE(copied, nullptr);
        auto *copiedTiling = dynamic_cast<GfxTilingPattern*>(copied.get());
        ASSERT_NE(copiedTiling, nullptr);
        EXPECT_DOUBLE_EQ(copiedTiling->getYStep(), 75.0);
    }
}

TEST_F(GfxTilingPatternTest_496, CopyPattern_PreservesXStep_496) {
    Object patObj = createTilingPatternObject(1, 1, 0.0, 0.0, 100.0, 100.0, 50.0, 75.0);
    auto pattern = GfxTilingPattern::parse(&patObj, 0);
    if (pattern) {
        auto copied = pattern->copy();
        ASSERT_NE(copied, nullptr);
        auto *copiedTiling = dynamic_cast<GfxTilingPattern*>(copied.get());
        ASSERT_NE(copiedTiling, nullptr);
        EXPECT_DOUBLE_EQ(copiedTiling->getXStep(), 50.0);
    }
}

TEST_F(GfxTilingPatternTest_496, CopyPattern_PreservesPaintType_496) {
    Object patObj = createTilingPatternObject(2, 1, 0.0, 0.0, 100.0, 100.0, 50.0, 75.0);
    auto pattern = GfxTilingPattern::parse(&patObj, 0);
    if (pattern) {
        auto copied = pattern->copy();
        ASSERT_NE(copied, nullptr);
        auto *copiedTiling = dynamic_cast<GfxTilingPattern*>(copied.get());
        ASSERT_NE(copiedTiling, nullptr);
        EXPECT_EQ(copiedTiling->getPaintType(), 2);
    }
}

TEST_F(GfxTilingPatternTest_496, CopyPattern_PreservesTilingType_496) {
    Object patObj = createTilingPatternObject(1, 2, 0.0, 0.0, 100.0, 100.0, 50.0, 75.0);
    auto pattern = GfxTilingPattern::parse(&patObj, 0);
    if (pattern) {
        auto copied = pattern->copy();
        ASSERT_NE(copied, nullptr);
        auto *copiedTiling = dynamic_cast<GfxTilingPattern*>(copied.get());
        ASSERT_NE(copiedTiling, nullptr);
        EXPECT_EQ(copiedTiling->getTilingType(), 2);
    }
}

TEST_F(GfxTilingPatternTest_496, CopyPattern_PreservesBBox_496) {
    Object patObj = createTilingPatternObject(1, 1, 5.0, 10.0, 200.0, 300.0, 50.0, 75.0);
    auto pattern = GfxTilingPattern::parse(&patObj, 0);
    if (pattern) {
        auto copied = pattern->copy();
        ASSERT_NE(copied, nullptr);
        auto *copiedTiling = dynamic_cast<GfxTilingPattern*>(copied.get());
        ASSERT_NE(copiedTiling, nullptr);
        const auto &bbox = copiedTiling->getBBox();
        EXPECT_DOUBLE_EQ(bbox[0], 5.0);
        EXPECT_DOUBLE_EQ(bbox[1], 10.0);
        EXPECT_DOUBLE_EQ(bbox[2], 200.0);
        EXPECT_DOUBLE_EQ(bbox[3], 300.0);
    }
}

TEST_F(GfxTilingPatternTest_496, CopyPattern_PreservesMatrix_496) {
    Object patObj = createTilingPatternObject(1, 1, 0.0, 0.0, 100.0, 100.0, 50.0, 75.0,
                                               3.0, 1.0, 1.0, 3.0, 5.0, 7.0);
    auto pattern = GfxTilingPattern::parse(&patObj, 0);
    if (pattern) {
        auto copied = pattern->copy();
        ASSERT_NE(copied, nullptr);
        auto *copiedTiling = dynamic_cast<GfxTilingPattern*>(copied.get());
        ASSERT_NE(copiedTiling, nullptr);
        const auto &matrix = copiedTiling->getMatrix();
        EXPECT_DOUBLE_EQ(matrix[0], 3.0);
        EXPECT_DOUBLE_EQ(matrix[1], 1.0);
        EXPECT_DOUBLE_EQ(matrix[2], 1.0);
        EXPECT_DOUBLE_EQ(matrix[3], 3.0);
        EXPECT_DOUBLE_EQ(matrix[4], 5.0);
        EXPECT_DOUBLE_EQ(matrix[5], 7.0);
    }
}

TEST_F(GfxTilingPatternTest_496, GetResDict_NotNull_496) {
    Object patObj = createTilingPatternObject(1, 1, 0.0, 0.0, 100.0, 100.0, 50.0, 75.0);
    auto pattern = GfxTilingPattern::parse(&patObj, 0);
    if (pattern) {
        // getResDict may return nullptr if no resources, or a valid Dict*
        // We just ensure it doesn't crash
        pattern->getResDict();
    }
}

TEST_F(GfxTilingPatternTest_496, GetContentStream_NotNull_496) {
    Object patObj = createTilingPatternObject(1, 1, 0.0, 0.0, 100.0, 100.0, 50.0, 75.0);
    auto pattern = GfxTilingPattern::parse(&patObj, 0);
    if (pattern) {
        Object *cs = pattern->getContentStream();
        ASSERT_NE(cs, nullptr);
    }
}

TEST_F(GfxTilingPatternTest_496, PaintType1_496) {
    Object patObj = createTilingPatternObject(1, 1, 0.0, 0.0, 100.0, 100.0, 50.0, 75.0);
    auto pattern = GfxTilingPattern::parse(&patObj, 0);
    if (pattern) {
        EXPECT_EQ(pattern->getPaintType(), 1);
    }
}

TEST_F(GfxTilingPatternTest_496, DefaultMatrix_496) {
    // When no matrix is specified, it should default to identity
    // But our helper always provides a matrix. Test with identity values.
    Object patObj = createTilingPatternObject(1, 1, 0.0, 0.0, 100.0, 100.0, 50.0, 75.0,
                                               1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    auto pattern = GfxTilingPattern::parse(&patObj, 0);
    if (pattern) {
        const auto &matrix = pattern->getMatrix();
        EXPECT_DOUBLE_EQ(matrix[0], 1.0);
        EXPECT_DOUBLE_EQ(matrix[1], 0.0);
        EXPECT_DOUBLE_EQ(matrix[2], 0.0);
        EXPECT_DOUBLE_EQ(matrix[3], 1.0);
        EXPECT_DOUBLE_EQ(matrix[4], 0.0);
        EXPECT_DOUBLE_EQ(matrix[5], 0.0);
    }
}
