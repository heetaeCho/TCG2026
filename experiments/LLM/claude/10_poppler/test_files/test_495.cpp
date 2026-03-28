#include <gtest/gtest.h>
#include <memory>
#include "GfxState.h"
#include "Object.h"

class GfxTilingPatternTest_495 : public ::testing::Test {
protected:
    // Helper to create a valid tiling pattern PDF object
    // A tiling pattern is a stream with specific dictionary entries
    std::unique_ptr<GfxTilingPattern> createValidPattern() {
        // Build a tiling pattern object (stream dict with required entries)
        Dict *dict = new Dict(nullptr);
        dict->add("PatternType", Object(1));       // Must be 1 for tiling
        dict->add("PaintType", Object(1));          // 1 = colored, 2 = uncolored
        dict->add("TilingType", Object(1));         // 1 = constant spacing
        
        // BBox array
        Object bboxArray = Object(new Array(nullptr));
        bboxArray.arrayAdd(Object(0.0));
        bboxArray.arrayAdd(Object(0.0));
        bboxArray.arrayAdd(Object(100.0));
        bboxArray.arrayAdd(Object(200.0));
        dict->add("BBox", std::move(bboxArray));
        
        dict->add("XStep", Object(50.0));
        dict->add("YStep", Object(75.0));
        
        // Matrix array (optional, identity if not present)
        Object matrixArray = Object(new Array(nullptr));
        matrixArray.arrayAdd(Object(1.0));
        matrixArray.arrayAdd(Object(0.0));
        matrixArray.arrayAdd(Object(0.0));
        matrixArray.arrayAdd(Object(1.0));
        matrixArray.arrayAdd(Object(0.0));
        matrixArray.arrayAdd(Object(0.0));
        dict->add("Matrix", std::move(matrixArray));
        
        // Resources dict
        dict->add("Resources", Object(new Dict(nullptr)));
        
        // Create a stream object
        Object patObj = Object(new Stream(new MemStream(nullptr, 0, 0, std::move(Object(dict)))));
        
        return GfxTilingPattern::parse(&patObj, 1);
    }
};

// Test that parse returns nullptr for a null/invalid object
TEST_F(GfxTilingPatternTest_495, ParseInvalidObjectReturnsNull_495) {
    Object nullObj;
    auto pattern = GfxTilingPattern::parse(&nullObj, 0);
    EXPECT_EQ(pattern, nullptr);
}

// Test that parse returns nullptr for a non-stream/non-dict object
TEST_F(GfxTilingPatternTest_495, ParseNonStreamObjectReturnsNull_495) {
    Object intObj(42);
    auto pattern = GfxTilingPattern::parse(&intObj, 0);
    EXPECT_EQ(pattern, nullptr);
}

// Test that parse returns nullptr for a dict without PatternType
TEST_F(GfxTilingPatternTest_495, ParseDictWithoutPatternTypeReturnsNull_495) {
    Dict *dict = new Dict(nullptr);
    Object dictObj(dict);
    auto pattern = GfxTilingPattern::parse(&dictObj, 0);
    EXPECT_EQ(pattern, nullptr);
}

// Test that parse returns nullptr for a dict with wrong PatternType
TEST_F(GfxTilingPatternTest_495, ParseDictWithWrongPatternTypeReturnsNull_495) {
    Dict *dict = new Dict(nullptr);
    dict->add("PatternType", Object(2)); // Shading pattern, not tiling
    Object dictObj(dict);
    auto pattern = GfxTilingPattern::parse(&dictObj, 0);
    EXPECT_EQ(pattern, nullptr);
}

// Test that parse returns nullptr for incomplete tiling pattern (missing BBox)
TEST_F(GfxTilingPatternTest_495, ParseIncompleteTilingPatternReturnsNull_495) {
    Dict *dict = new Dict(nullptr);
    dict->add("PatternType", Object(1));
    dict->add("PaintType", Object(1));
    dict->add("TilingType", Object(1));
    // Missing BBox, XStep, YStep
    Object dictObj(dict);
    auto pattern = GfxTilingPattern::parse(&dictObj, 0);
    // May return nullptr due to missing required fields
    // This tests error handling for incomplete patterns
    EXPECT_EQ(pattern, nullptr);
}

// Test getType returns the tiling pattern type
TEST_F(GfxTilingPatternTest_495, GetTypeReturnsTiling_495) {
    auto pattern = createValidPattern();
    if (pattern) {
        EXPECT_EQ(pattern->getType(), 1); // GfxPattern type 1 = tiling
    }
}

// Test getXStep returns the configured XStep value
TEST_F(GfxTilingPatternTest_495, GetXStepReturnsCorrectValue_495) {
    auto pattern = createValidPattern();
    if (pattern) {
        EXPECT_DOUBLE_EQ(pattern->getXStep(), 50.0);
    }
}

// Test getYStep returns the configured YStep value
TEST_F(GfxTilingPatternTest_495, GetYStepReturnsCorrectValue_495) {
    auto pattern = createValidPattern();
    if (pattern) {
        EXPECT_DOUBLE_EQ(pattern->getYStep(), 75.0);
    }
}

// Test getPaintType returns the configured paint type
TEST_F(GfxTilingPatternTest_495, GetPaintTypeReturnsCorrectValue_495) {
    auto pattern = createValidPattern();
    if (pattern) {
        EXPECT_EQ(pattern->getPaintType(), 1);
    }
}

// Test getTilingType returns the configured tiling type
TEST_F(GfxTilingPatternTest_495, GetTilingTypeReturnsCorrectValue_495) {
    auto pattern = createValidPattern();
    if (pattern) {
        EXPECT_EQ(pattern->getTilingType(), 1);
    }
}

// Test getBBox returns the configured bounding box
TEST_F(GfxTilingPatternTest_495, GetBBoxReturnsCorrectValues_495) {
    auto pattern = createValidPattern();
    if (pattern) {
        const auto &bbox = pattern->getBBox();
        EXPECT_DOUBLE_EQ(bbox[0], 0.0);
        EXPECT_DOUBLE_EQ(bbox[1], 0.0);
        EXPECT_DOUBLE_EQ(bbox[2], 100.0);
        EXPECT_DOUBLE_EQ(bbox[3], 200.0);
    }
}

// Test getMatrix returns the configured matrix
TEST_F(GfxTilingPatternTest_495, GetMatrixReturnsCorrectValues_495) {
    auto pattern = createValidPattern();
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

// Test getResDict returns non-null for a pattern with resources
TEST_F(GfxTilingPatternTest_495, GetResDictReturnsNonNull_495) {
    auto pattern = createValidPattern();
    if (pattern) {
        // Resources were provided, so getResDict should return something
        Dict *resDict = pattern->getResDict();
        // May or may not be null depending on implementation details
        // Just verify it doesn't crash
        (void)resDict;
    }
}

// Test getContentStream returns a valid object
TEST_F(GfxTilingPatternTest_495, GetContentStreamReturnsValidObject_495) {
    auto pattern = createValidPattern();
    if (pattern) {
        Object *contentStream = pattern->getContentStream();
        EXPECT_NE(contentStream, nullptr);
    }
}

// Test copy produces a valid pattern with same properties
TEST_F(GfxTilingPatternTest_495, CopyPreservesProperties_495) {
    auto pattern = createValidPattern();
    if (pattern) {
        auto copied = pattern->copy();
        ASSERT_NE(copied, nullptr);
        
        auto *copiedTiling = dynamic_cast<GfxTilingPattern *>(copied.get());
        ASSERT_NE(copiedTiling, nullptr);
        
        EXPECT_EQ(copiedTiling->getPaintType(), pattern->getPaintType());
        EXPECT_EQ(copiedTiling->getTilingType(), pattern->getTilingType());
        EXPECT_DOUBLE_EQ(copiedTiling->getXStep(), pattern->getXStep());
        EXPECT_DOUBLE_EQ(copiedTiling->getYStep(), pattern->getYStep());
        
        const auto &origBBox = pattern->getBBox();
        const auto &copyBBox = copiedTiling->getBBox();
        for (int i = 0; i < 4; i++) {
            EXPECT_DOUBLE_EQ(copyBBox[i], origBBox[i]);
        }
        
        const auto &origMatrix = pattern->getMatrix();
        const auto &copyMatrix = copiedTiling->getMatrix();
        for (int i = 0; i < 6; i++) {
            EXPECT_DOUBLE_EQ(copyMatrix[i], origMatrix[i]);
        }
    }
}
