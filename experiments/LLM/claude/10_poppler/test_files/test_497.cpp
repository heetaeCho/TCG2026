#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "GfxState.h"
#include "Object.h"
#include "Dict.h"
#include "Stream.h"
#include "PDFDoc.h"

// Test fixture for GfxTilingPattern
class GfxTilingPatternTest_497 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test that parse returns nullptr when given an invalid/non-dict object
TEST_F(GfxTilingPatternTest_497, ParseInvalidObjectReturnsNull_497) {
    Object nullObj = Object(objNone);
    auto result = GfxTilingPattern::parse(&nullObj, 0);
    EXPECT_EQ(result, nullptr);
}

// Test that parse returns nullptr for a null object
TEST_F(GfxTilingPatternTest_497, ParseNullObjectReturnsNull_497) {
    Object obj = Object::null();
    auto result = GfxTilingPattern::parse(&obj, 0);
    EXPECT_EQ(result, nullptr);
}

// Test that parse returns nullptr for an integer object (not a stream/dict)
TEST_F(GfxTilingPatternTest_497, ParseIntObjectReturnsNull_497) {
    Object intObj(42);
    auto result = GfxTilingPattern::parse(&intObj, 0);
    EXPECT_EQ(result, nullptr);
}

// Test that parse returns nullptr for a boolean object
TEST_F(GfxTilingPatternTest_497, ParseBoolObjectReturnsNull_497) {
    Object boolObj(true);
    auto result = GfxTilingPattern::parse(&boolObj, 0);
    EXPECT_EQ(result, nullptr);
}

// Test that parse returns nullptr for an error object
TEST_F(GfxTilingPatternTest_497, ParseErrorObjectReturnsNull_497) {
    Object errObj = Object::error();
    auto result = GfxTilingPattern::parse(&errObj, 0);
    EXPECT_EQ(result, nullptr);
}

// Test that parse returns nullptr for an EOF object
TEST_F(GfxTilingPatternTest_497, ParseEofObjectReturnsNull_497) {
    Object eofObj = Object::eof();
    auto result = GfxTilingPattern::parse(&eofObj, 0);
    EXPECT_EQ(result, nullptr);
}

// Test getResDict returns nullptr when resDict is not a dict
// We test this through a pattern that might have a non-dict resDict
// Since we can't construct GfxTilingPattern directly (private constructor),
// we test through parse with a properly constructed stream object if possible.

// Test that getResDict returns a Dict* when resDict is a dict, or nullptr otherwise
// This is tested through the public interface indirectly.
// The method signature shows: Dict *getResDict() { return resDict.isDict() ? resDict.getDict() : nullptr; }

// Since GfxTilingPattern has a private constructor and can only be created via parse(),
// we need a valid stream object to test the getters. We'll create a minimal valid pattern.

class GfxTilingPatternParseTest_497 : public ::testing::Test {
protected:
    std::unique_ptr<XRef> xref;

    void SetUp() override {
    }

    void TearDown() override {
    }

    // Helper to create a Dict with required tiling pattern fields
    Object createMinimalTilingPatternDict() {
        // GfxTilingPattern::parse expects a stream object whose dict has specific entries
        // Since creating a full stream is complex without infrastructure,
        // we focus on testing parse failure cases
        Dict *dict = new Dict(nullptr);
        dict->add("PatternType", Object(1));
        dict->add("PaintType", Object(1));
        dict->add("TilingType", Object(1));

        // BBox array
        Object bboxArray(new Array(nullptr));
        bboxArray.arrayAdd(Object(0.0));
        bboxArray.arrayAdd(Object(0.0));
        bboxArray.arrayAdd(Object(100.0));
        bboxArray.arrayAdd(Object(100.0));
        dict->add("BBox", std::move(bboxArray));

        dict->add("XStep", Object(100.0));
        dict->add("YStep", Object(100.0));

        return Object(dict);
    }
};

// Test that parse with a plain dict (not a stream) returns nullptr
// because tiling patterns are expected to be streams
TEST_F(GfxTilingPatternParseTest_497, ParsePlainDictReturnsNull_497) {
    Object dictObj = createMinimalTilingPatternDict();
    auto result = GfxTilingPattern::parse(&dictObj, 0);
    // A plain dict is not a stream, so parse should return nullptr
    EXPECT_EQ(result, nullptr);
}

// Test parse with a real number object returns nullptr
TEST_F(GfxTilingPatternParseTest_497, ParseRealObjectReturnsNull_497) {
    Object realObj(3.14);
    auto result = GfxTilingPattern::parse(&realObj, 0);
    EXPECT_EQ(result, nullptr);
}

// Test parse with a string object returns nullptr
TEST_F(GfxTilingPatternParseTest_497, ParseStringObjectReturnsNull_497) {
    Object strObj(std::string("test"));
    auto result = GfxTilingPattern::parse(&strObj, 0);
    EXPECT_EQ(result, nullptr);
}

// Test that an empty array object fails parse
TEST_F(GfxTilingPatternParseTest_497, ParseArrayObjectReturnsNull_497) {
    Object arrObj(new Array(nullptr));
    auto result = GfxTilingPattern::parse(&arrObj, 0);
    EXPECT_EQ(result, nullptr);
}
