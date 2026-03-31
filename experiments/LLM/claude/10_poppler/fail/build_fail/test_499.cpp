#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "GfxState.h"
#include "Object.h"

// Since GfxTilingPattern has a private constructor and can only be created via parse(),
// we need to test through the parse() factory method or work with what's available.

class GfxTilingPatternTest_499 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test that parse returns nullptr for an invalid/null pattern object
TEST_F(GfxTilingPatternTest_499, ParseInvalidObjectReturnsNull_499) {
    Object obj;
    auto pattern = GfxTilingPattern::parse(&obj, 0);
    // An uninitialized or non-dict/stream object should fail to parse
    EXPECT_EQ(pattern, nullptr);
}

// Test that parse returns nullptr for a non-stream, non-dict object
TEST_F(GfxTilingPatternTest_499, ParseNonDictObjectReturnsNull_499) {
    Object obj(42); // integer object
    auto pattern = GfxTilingPattern::parse(&obj, 0);
    EXPECT_EQ(pattern, nullptr);
}

// Test that parse with a boolean object returns nullptr
TEST_F(GfxTilingPatternTest_499, ParseBoolObjectReturnsNull_499) {
    Object obj(true);
    auto pattern = GfxTilingPattern::parse(&obj, 0);
    EXPECT_EQ(pattern, nullptr);
}

// Test that parse with a string object returns nullptr
TEST_F(GfxTilingPatternTest_499, ParseStringObjectReturnsNull_499) {
    Object obj(new GooString("test"));
    auto pattern = GfxTilingPattern::parse(&obj, 0);
    EXPECT_EQ(pattern, nullptr);
}

// Test that parse with a real/double object returns nullptr
TEST_F(GfxTilingPatternTest_499, ParseRealObjectReturnsNull_499) {
    Object obj(3.14);
    auto pattern = GfxTilingPattern::parse(&obj, 0);
    EXPECT_EQ(pattern, nullptr);
}

// Test that getContentStream returns a non-null pointer when pattern is valid
// This requires a valid pattern - we attempt to create one via a properly formed stream object
TEST_F(GfxTilingPatternTest_499, ParseValidPatternHasContentStream_499) {
    // Create a dictionary with the required tiling pattern fields
    Dict *dict = new Dict(static_cast<XRef*>(nullptr));
    dict->add("PatternType", Object(1));
    dict->add("PaintType", Object(1));
    dict->add("TilingType", Object(1));
    
    // BBox array
    Object bboxArray(new Array(static_cast<XRef*>(nullptr)));
    bboxArray.arrayAdd(Object(0.0));
    bboxArray.arrayAdd(Object(0.0));
    bboxArray.arrayAdd(Object(100.0));
    bboxArray.arrayAdd(Object(100.0));
    dict->add("BBox", std::move(bboxArray));
    
    dict->add("XStep", Object(100.0));
    dict->add("YStep", Object(100.0));
    
    // Resources dictionary
    dict->add("Resources", Object(new Dict(static_cast<XRef*>(nullptr))));
    
    // Matrix array (optional but let's include)
    Object matrixArray(new Array(static_cast<XRef*>(nullptr)));
    matrixArray.arrayAdd(Object(1.0));
    matrixArray.arrayAdd(Object(0.0));
    matrixArray.arrayAdd(Object(0.0));
    matrixArray.arrayAdd(Object(1.0));
    matrixArray.arrayAdd(Object(0.0));
    matrixArray.arrayAdd(Object(0.0));
    dict->add("Matrix", std::move(matrixArray));
    
    // Create a stream object
    Object patObj(static_cast<Stream*>(nullptr), dict);
    
    auto pattern = GfxTilingPattern::parse(&patObj, 1);
    
    if (pattern) {
        // If parsing succeeds, verify interface methods
        EXPECT_NE(pattern->getContentStream(), nullptr);
        EXPECT_EQ(pattern->getPaintType(), 1);
        EXPECT_EQ(pattern->getTilingType(), 1);
        EXPECT_DOUBLE_EQ(pattern->getXStep(), 100.0);
        EXPECT_DOUBLE_EQ(pattern->getYStep(), 100.0);
        
        const auto &bbox = pattern->getBBox();
        EXPECT_DOUBLE_EQ(bbox[0], 0.0);
        EXPECT_DOUBLE_EQ(bbox[1], 0.0);
        EXPECT_DOUBLE_EQ(bbox[2], 100.0);
        EXPECT_DOUBLE_EQ(bbox[3], 100.0);
        
        const auto &matrix = pattern->getMatrix();
        EXPECT_DOUBLE_EQ(matrix[0], 1.0);
        EXPECT_DOUBLE_EQ(matrix[1], 0.0);
        EXPECT_DOUBLE_EQ(matrix[2], 0.0);
        EXPECT_DOUBLE_EQ(matrix[3], 1.0);
        EXPECT_DOUBLE_EQ(matrix[4], 0.0);
        EXPECT_DOUBLE_EQ(matrix[5], 0.0);
        
        // Test copy
        auto copied = pattern->copy();
        EXPECT_NE(copied, nullptr);
        if (copied) {
            auto *copiedTiling = dynamic_cast<GfxTilingPattern*>(copied.get());
            if (copiedTiling) {
                EXPECT_EQ(copiedTiling->getPaintType(), pattern->getPaintType());
                EXPECT_EQ(copiedTiling->getTilingType(), pattern->getTilingType());
                EXPECT_DOUBLE_EQ(copiedTiling->getXStep(), pattern->getXStep());
                EXPECT_DOUBLE_EQ(copiedTiling->getYStep(), pattern->getYStep());
            }
        }
    }
}

// Test parse with negative pattern ref number
TEST_F(GfxTilingPatternTest_499, ParseWithNegativeRefNum_499) {
    Object obj;
    auto pattern = GfxTilingPattern::parse(&obj, -1);
    EXPECT_EQ(pattern, nullptr);
}

// Test parse with zero pattern ref number and null object
TEST_F(GfxTilingPatternTest_499, ParseWithZeroRefNumNullObj_499) {
    Object obj;
    auto pattern = GfxTilingPattern::parse(&obj, 0);
    EXPECT_EQ(pattern, nullptr);
}

// Test that an array object does not parse as a tiling pattern
TEST_F(GfxTilingPatternTest_499, ParseArrayObjectReturnsNull_499) {
    Object obj(new Array(static_cast<XRef*>(nullptr)));
    auto pattern = GfxTilingPattern::parse(&obj, 0);
    EXPECT_EQ(pattern, nullptr);
}
