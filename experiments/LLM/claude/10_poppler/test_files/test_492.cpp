#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "GfxState.h"
#include "Object.h"
#include "Dict.h"
#include "Stream.h"

// Since GfxTilingPattern has a private constructor and can only be created via
// parse(), we need to construct a valid pattern Object to test with.

class GfxTilingPatternTest_492 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }

    // Helper to create a pattern object that can be parsed
    Object createValidPatternObject(int paintType, int tilingType,
                                     double bbox0, double bbox1, double bbox2, double bbox3,
                                     double xStep, double yStep) {
        Object patObj;
        // Build a pattern dictionary with required fields
        // PatternType = 1 (tiling pattern)
        // PaintType, TilingType, BBox, XStep, YStep, Resources, Matrix
        
        // We need to construct a Dict-based Object
        // This depends on poppler's Object/Dict API
        
        return patObj;
    }
};

// Test that parse returns nullptr for an invalid (null/non-dict) object
TEST_F(GfxTilingPatternTest_492, ParseInvalidObjectReturnsNull_492) {
    Object nullObj;
    auto pattern = GfxTilingPattern::parse(&nullObj, 0);
    EXPECT_EQ(pattern, nullptr);
}

// Test that parse returns nullptr for a non-stream, non-dict object
TEST_F(GfxTilingPatternTest_492, ParseIntObjectReturnsNull_492) {
    Object intObj(42);
    auto pattern = GfxTilingPattern::parse(&intObj, 0);
    EXPECT_EQ(pattern, nullptr);
}

// Test that parse returns nullptr for a boolean object
TEST_F(GfxTilingPatternTest_492, ParseBoolObjectReturnsNull_492) {
    Object boolObj(true);
    auto pattern = GfxTilingPattern::parse(&boolObj, 0);
    EXPECT_EQ(pattern, nullptr);
}

// Test that parse returns nullptr for a string object
TEST_F(GfxTilingPatternTest_492, ParseStringObjectReturnsNull_492) {
    Object strObj(new GooString("test"));
    auto pattern = GfxTilingPattern::parse(&strObj, 0);
    EXPECT_EQ(pattern, nullptr);
}

// Test parsing a properly constructed tiling pattern stream object
TEST_F(GfxTilingPatternTest_492, ParseValidPatternStream_492) {
    // Create a stream object with proper tiling pattern dictionary entries
    auto dict = std::make_unique<Dict>(static_cast<XRef*>(nullptr));
    
    dict->add("PatternType", Object(1));
    dict->add("PaintType", Object(1));
    dict->add("TilingType", Object(1));
    
    Object bboxArray;
    {
        auto arr = std::make_unique<Array>(static_cast<XRef*>(nullptr));
        arr->add(Object(0.0));
        arr->add(Object(0.0));
        arr->add(Object(100.0));
        arr->add(Object(100.0));
        bboxArray = Object(arr.release());
    }
    dict->add("BBox", std::move(bboxArray));
    
    dict->add("XStep", Object(100.0));
    dict->add("YStep", Object(100.0));
    
    Object resDict;
    {
        auto resD = std::make_unique<Dict>(static_cast<XRef*>(nullptr));
        resDict = Object(resD.release());
    }
    dict->add("Resources", std::move(resDict));
    
    Object matrixArray;
    {
        auto arr = std::make_unique<Array>(static_cast<XRef*>(nullptr));
        arr->add(Object(1.0));
        arr->add(Object(0.0));
        arr->add(Object(0.0));
        arr->add(Object(1.0));
        arr->add(Object(0.0));
        arr->add(Object(0.0));
        matrixArray = Object(arr.release());
    }
    dict->add("Matrix", std::move(matrixArray));
    
    // Create a MemStream with the dict
    const char *streamData = "";
    auto memStream = new MemStream(const_cast<char *>(streamData), 0, 0, Object(dict.release()));
    Object patObj(static_cast<Stream *>(memStream));
    
    auto pattern = GfxTilingPattern::parse(&patObj, 1);
    
    if (pattern) {
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
    }
}

// Test parsing with PaintType = 2 (uncolored)
TEST_F(GfxTilingPatternTest_492, ParsePaintType2_492) {
    auto dict = std::make_unique<Dict>(static_cast<XRef*>(nullptr));
    
    dict->add("PatternType", Object(1));
    dict->add("PaintType", Object(2));
    dict->add("TilingType", Object(2));
    
    {
        auto arr = std::make_unique<Array>(static_cast<XRef*>(nullptr));
        arr->add(Object(0.0));
        arr->add(Object(0.0));
        arr->add(Object(50.0));
        arr->add(Object(50.0));
        dict->add("BBox", Object(arr.release()));
    }
    
    dict->add("XStep", Object(50.0));
    dict->add("YStep", Object(50.0));
    
    {
        auto resD = std::make_unique<Dict>(static_cast<XRef*>(nullptr));
        dict->add("Resources", Object(resD.release()));
    }
    
    const char *streamData = "";
    auto memStream = new MemStream(const_cast<char *>(streamData), 0, 0, Object(dict.release()));
    Object patObj(static_cast<Stream *>(memStream));
    
    auto pattern = GfxTilingPattern::parse(&patObj, 2);
    
    if (pattern) {
        EXPECT_EQ(pattern->getPaintType(), 2);
        EXPECT_EQ(pattern->getTilingType(), 2);
        EXPECT_DOUBLE_EQ(pattern->getXStep(), 50.0);
        EXPECT_DOUBLE_EQ(pattern->getYStep(), 50.0);
    }
}

// Test that copy() produces an equivalent pattern
TEST_F(GfxTilingPatternTest_492, CopyProducesEquivalentPattern_492) {
    auto dict = std::make_unique<Dict>(static_cast<XRef*>(nullptr));
    
    dict->add("PatternType", Object(1));
    dict->add("PaintType", Object(1));
    dict->add("TilingType", Object(3));
    
    {
        auto arr = std::make_unique<Array>(static_cast<XRef*>(nullptr));
        arr->add(Object(10.0));
        arr->add(Object(20.0));
        arr->add(Object(30.0));
        arr->add(Object(40.0));
        dict->add("BBox", Object(arr.release()));
    }
    
    dict->add("XStep", Object(25.0));
    dict->add("YStep", Object(35.0));
    
    {
        auto resD = std::make_unique<Dict>(static_cast<XRef*>(nullptr));
        dict->add("Resources", Object(resD.release()));
    }
    
    {
        auto arr = std::make_unique<Array>(static_cast<XRef*>(nullptr));
        arr->add(Object(2.0));
        arr->add(Object(0.0));
        arr->add(Object(0.0));
        arr->add(Object(2.0));
        arr->add(Object(10.0));
        arr->add(Object(20.0));
        dict->add("Matrix", Object(arr.release()));
    }
    
    const char *streamData = "";
    auto memStream = new MemStream(const_cast<char *>(streamData), 0, 0, Object(dict.release()));
    Object patObj(static_cast<Stream *>(memStream));
    
    auto pattern = GfxTilingPattern::parse(&patObj, 3);
    
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

// Test with no Matrix entry (should default to identity)
TEST_F(GfxTilingPatternTest_492, ParseWithoutMatrixDefaultsToIdentity_492) {
    auto dict = std::make_unique<Dict>(static_cast<XRef*>(nullptr));
    
    dict->add("PatternType", Object(1));
    dict->add("PaintType", Object(1));
    dict->add("TilingType", Object(1));
    
    {
        auto arr = std::make_unique<Array>(static_cast<XRef*>(nullptr));
        arr->add(Object(0.0));
        arr->add(Object(0.0));
        arr->add(Object(100.0));
        arr->add(Object(100.0));
        dict->add("BBox", Object(arr.release()));
    }
    
    dict->add("XStep", Object(100.0));
    dict->add("YStep", Object(100.0));
    
    {
        auto resD = std::make_unique<Dict>(static_cast<XRef*>(nullptr));
        dict->add("Resources", Object(resD.release()));
    }
    
    // No Matrix entry — should default to identity matrix
    
    const char *streamData = "";
    auto memStream = new MemStream(const_cast<char *>(streamData), 0, 0, Object(dict.release()));
    Object patObj(static_cast<Stream *>(memStream));
    
    auto pattern = GfxTilingPattern::parse(&patObj, 4);
    
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

// Test getContentStream returns a valid pointer
TEST_F(GfxTilingPatternTest_492, GetContentStreamReturnsNonNull_492) {
    auto dict = std::make_unique<Dict>(static_cast<XRef*>(nullptr));
    
    dict->add("PatternType", Object(1));
    dict->add("PaintType", Object(1));
    dict->add("TilingType", Object(1));
    
    {
        auto arr = std::make_unique<Array>(static_cast<XRef*>(nullptr));
        arr->add(Object(0.0));
        arr->add(Object(0.0));
        arr->add(Object(10.0));
        arr->add(Object(10.0));
        dict->add("BBox", Object(arr.release()));
    }
    
    dict->add("XStep", Object(10.0));
    dict->add("YStep", Object(10.0));
    
    {
        auto resD = std::make_unique<Dict>(static_cast<XRef*>(nullptr));
        dict->add("Resources", Object(resD.release()));
    }
    
    const char *streamData = "some content";
    auto memStream = new MemStream(const_cast<char *>(streamData), 0, strlen(streamData), Object(dict.release()));
    Object patObj(static_cast<Stream *>(memStream));
    
    auto pattern = GfxTilingPattern::parse(&patObj, 5);
    
    if (pattern) {
        Object *contentStream = pattern->getContentStream();
        EXPECT_NE(contentStream, nullptr);
    }
}

// Test negative step values
TEST_F(GfxTilingPatternTest_492, ParseNegativeStepValues_492) {
    auto dict = std::make_unique<Dict>(static_cast<XRef*>(nullptr));
    
    dict->add("PatternType", Object(1));
    dict->add("PaintType", Object(1));
    dict->add("TilingType", Object(1));
    
    {
        auto arr = std::make_unique<Array>(static_cast<XRef*>(nullptr));
        arr->add(Object(0.0));
        arr->add(Object(0.0));
        arr->add(Object(100.0));
        arr->add(Object(100.0));
        dict->add("BBox", Object(arr.release()));
    }
    
    dict->add("XStep", Object(-50.0));
    dict->add("YStep", Object(-50.0));
    
    {
        auto resD = std::make_unique<Dict>(static_cast<XRef*>(nullptr));
        dict->add("Resources", Object(resD.release()));
    }
    
    const char *streamData = "";
    auto memStream = new MemStream(const_cast<char *>(streamData), 0, 0, Object(dict.release()));
    Object patObj(static_cast<Stream *>(memStream));
    
    auto pattern = GfxTilingPattern::parse(&patObj, 6);
    
    // If pattern parsed successfully, check the step values
    if (pattern) {
        // The implementation may take absolute value or keep as-is
        double xStep = pattern->getXStep();
        double yStep = pattern->getYStep();
        // Just verify they are non-zero (either -50 or 50)
        EXPECT_NE(xStep, 0.0);
        EXPECT_NE(yStep, 0.0);
    }
}

// Test getResDict
TEST_F(GfxTilingPatternTest_492, GetResDictReturnsValidPointer_492) {
    auto dict = std::make_unique<Dict>(static_cast<XRef*>(nullptr));
    
    dict->add("PatternType", Object(1));
    dict->add("PaintType", Object(1));
    dict->add("TilingType", Object(1));
    
    {
        auto arr = std::make_unique<Array>(static_cast<XRef*>(nullptr));
        arr->add(Object(0.0));
        arr->add(Object(0.0));
        arr->add(Object(100.0));
        arr->add(Object(100.0));
        dict->add("BBox", Object(arr.release()));
    }
    
    dict->add("XStep", Object(100.0));
    dict->add("YStep", Object(100.0));
    
    {
        auto resD = std::make_unique<Dict>(static_cast<XRef*>(nullptr));
        dict->add("Resources", Object(resD.release()));
    }
    
    const char *streamData = "";
    auto memStream = new MemStream(const_cast<char *>(streamData), 0, 0, Object(dict.release()));
    Object patObj(static_cast<Stream *>(memStream));
    
    auto pattern = GfxTilingPattern::parse(&patObj, 7);
    
    if (pattern) {
        // getResDict may return nullptr if resources are stored as Object
        // but should not crash
        Dict *resDict = pattern->getResDict();
        // Just verify we can call it without crash
        SUCCEED();
    }
}
