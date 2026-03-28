#include <gtest/gtest.h>
#include "tiffvisitor_int.hpp"
#include "exiv2/exiv2.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

// Concrete subclass of TiffVisitor for testing base class functionality
class ConcreteTiffVisitor : public TiffVisitor {
public:
    void visitEntry(TiffEntry* object) override {}
    void visitDataEntry(TiffDataEntry* object) override {}
    void visitImageEntry(TiffImageEntry* object) override {}
    void visitSizeEntry(TiffSizeEntry* object) override {}
    void visitDirectory(TiffDirectory* object) override {}
    void visitSubIfd(TiffSubIfd* object) override {}
    void visitMnEntry(TiffMnEntry* object) override {}
    void visitIfdMakernote(TiffIfdMakernote* object) override {}
    void visitBinaryArray(TiffBinaryArray* object) override {}
    void visitBinaryElement(TiffBinaryElement* object) override {}
};

// Tests for TiffVisitor::setGo and TiffVisitor::go
class TiffVisitorTest_1666 : public ::testing::Test {
protected:
    ConcreteTiffVisitor visitor;
};

TEST_F(TiffVisitorTest_1666, DefaultGoStateIsTrue_geTraverse_1666) {
    // By default, go_ array is initialized to {true, true}
    EXPECT_TRUE(visitor.go(geTraverse));
}

TEST_F(TiffVisitorTest_1666, DefaultGoStateIsTrue_geKnownMakernote_1666) {
    EXPECT_TRUE(visitor.go(geKnownMakernote));
}

TEST_F(TiffVisitorTest_1666, SetGoTraverseFalse_1666) {
    visitor.setGo(geTraverse, false);
    EXPECT_FALSE(visitor.go(geTraverse));
}

TEST_F(TiffVisitorTest_1666, SetGoTraverseTrue_1666) {
    visitor.setGo(geTraverse, false);
    EXPECT_FALSE(visitor.go(geTraverse));
    visitor.setGo(geTraverse, true);
    EXPECT_TRUE(visitor.go(geTraverse));
}

TEST_F(TiffVisitorTest_1666, SetGoKnownMakernoteFalse_1666) {
    visitor.setGo(geKnownMakernote, false);
    EXPECT_FALSE(visitor.go(geKnownMakernote));
}

TEST_F(TiffVisitorTest_1666, SetGoKnownMakernoteTrue_1666) {
    visitor.setGo(geKnownMakernote, false);
    visitor.setGo(geKnownMakernote, true);
    EXPECT_TRUE(visitor.go(geKnownMakernote));
}

TEST_F(TiffVisitorTest_1666, SetGoTraverseDoesNotAffectKnownMakernote_1666) {
    visitor.setGo(geTraverse, false);
    EXPECT_FALSE(visitor.go(geTraverse));
    EXPECT_TRUE(visitor.go(geKnownMakernote));
}

TEST_F(TiffVisitorTest_1666, SetGoKnownMakernoteDoesNotAffectTraverse_1666) {
    visitor.setGo(geKnownMakernote, false);
    EXPECT_TRUE(visitor.go(geTraverse));
    EXPECT_FALSE(visitor.go(geKnownMakernote));
}

TEST_F(TiffVisitorTest_1666, SetBothGoEventsFalse_1666) {
    visitor.setGo(geTraverse, false);
    visitor.setGo(geKnownMakernote, false);
    EXPECT_FALSE(visitor.go(geTraverse));
    EXPECT_FALSE(visitor.go(geKnownMakernote));
}

TEST_F(TiffVisitorTest_1666, SetGoMultipleTimes_1666) {
    visitor.setGo(geTraverse, false);
    visitor.setGo(geTraverse, false);
    EXPECT_FALSE(visitor.go(geTraverse));
    visitor.setGo(geTraverse, true);
    visitor.setGo(geTraverse, true);
    EXPECT_TRUE(visitor.go(geTraverse));
}

TEST_F(TiffVisitorTest_1666, ToggleGoState_1666) {
    for (int i = 0; i < 10; ++i) {
        bool val = (i % 2 == 0);
        visitor.setGo(geTraverse, val);
        EXPECT_EQ(visitor.go(geTraverse), val);
    }
}
