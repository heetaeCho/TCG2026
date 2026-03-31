#include <gtest/gtest.h>

// Include necessary headers from the project
#include "tiffvisitor_int.hpp"

namespace Exiv2 {
namespace Internal {

// Since TiffVisitor has pure virtual methods, we need a concrete subclass for testing
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

class TiffVisitorTest_1627 : public ::testing::Test {
protected:
    ConcreteTiffVisitor visitor;
};

// Test that go() returns true by default for geTraverse event (index 0)
TEST_F(TiffVisitorTest_1627, GoDefaultTrueForTraverse_1627) {
    EXPECT_TRUE(visitor.go(geTraverse));
}

// Test that go() returns true by default for geKnownMakernote event (index 1)
TEST_F(TiffVisitorTest_1627, GoDefaultTrueForKnownMakernote_1627) {
    EXPECT_TRUE(visitor.go(geKnownMakernote));
}

// Test setGo can disable geTraverse
TEST_F(TiffVisitorTest_1627, SetGoDisableTraverse_1627) {
    visitor.setGo(geTraverse, false);
    EXPECT_FALSE(visitor.go(geTraverse));
}

// Test setGo can disable geKnownMakernote
TEST_F(TiffVisitorTest_1627, SetGoDisableKnownMakernote_1627) {
    visitor.setGo(geKnownMakernote, false);
    EXPECT_FALSE(visitor.go(geKnownMakernote));
}

// Test setGo can re-enable geTraverse after disabling
TEST_F(TiffVisitorTest_1627, SetGoReenableTraverse_1627) {
    visitor.setGo(geTraverse, false);
    EXPECT_FALSE(visitor.go(geTraverse));
    visitor.setGo(geTraverse, true);
    EXPECT_TRUE(visitor.go(geTraverse));
}

// Test setGo can re-enable geKnownMakernote after disabling
TEST_F(TiffVisitorTest_1627, SetGoReenableKnownMakernote_1627) {
    visitor.setGo(geKnownMakernote, false);
    EXPECT_FALSE(visitor.go(geKnownMakernote));
    visitor.setGo(geKnownMakernote, true);
    EXPECT_TRUE(visitor.go(geKnownMakernote));
}

// Test that setting one event does not affect the other
TEST_F(TiffVisitorTest_1627, SetGoIndependentEvents_1627) {
    visitor.setGo(geTraverse, false);
    EXPECT_FALSE(visitor.go(geTraverse));
    EXPECT_TRUE(visitor.go(geKnownMakernote));
}

// Test that setting geKnownMakernote does not affect geTraverse
TEST_F(TiffVisitorTest_1627, SetGoKnownMakernoteDoesNotAffectTraverse_1627) {
    visitor.setGo(geKnownMakernote, false);
    EXPECT_TRUE(visitor.go(geTraverse));
    EXPECT_FALSE(visitor.go(geKnownMakernote));
}

// Test setting the same value multiple times (idempotency)
TEST_F(TiffVisitorTest_1627, SetGoIdempotentTrue_1627) {
    visitor.setGo(geTraverse, true);
    visitor.setGo(geTraverse, true);
    EXPECT_TRUE(visitor.go(geTraverse));
}

// Test setting false multiple times (idempotency)
TEST_F(TiffVisitorTest_1627, SetGoIdempotentFalse_1627) {
    visitor.setGo(geTraverse, false);
    visitor.setGo(geTraverse, false);
    EXPECT_FALSE(visitor.go(geTraverse));
}

// Test both events can be disabled simultaneously
TEST_F(TiffVisitorTest_1627, BothEventsDisabled_1627) {
    visitor.setGo(geTraverse, false);
    visitor.setGo(geKnownMakernote, false);
    EXPECT_FALSE(visitor.go(geTraverse));
    EXPECT_FALSE(visitor.go(geKnownMakernote));
}

// Test both events can be re-enabled simultaneously
TEST_F(TiffVisitorTest_1627, BothEventsReenabled_1627) {
    visitor.setGo(geTraverse, false);
    visitor.setGo(geKnownMakernote, false);
    visitor.setGo(geTraverse, true);
    visitor.setGo(geKnownMakernote, true);
    EXPECT_TRUE(visitor.go(geTraverse));
    EXPECT_TRUE(visitor.go(geKnownMakernote));
}

// Test that visitDirectoryNext does not crash (it's a no-op by default)
TEST_F(TiffVisitorTest_1627, VisitDirectoryNextNoOp_1627) {
    EXPECT_NO_THROW(visitor.visitDirectoryNext(nullptr));
}

// Test that visitDirectoryEnd does not crash (it's a no-op by default)
TEST_F(TiffVisitorTest_1627, VisitDirectoryEndNoOp_1627) {
    EXPECT_NO_THROW(visitor.visitDirectoryEnd(nullptr));
}

// Test that visitIfdMakernoteEnd does not crash (it's a no-op by default)
TEST_F(TiffVisitorTest_1627, VisitIfdMakernoteEndNoOp_1627) {
    EXPECT_NO_THROW(visitor.visitIfdMakernoteEnd(nullptr));
}

// Test that visitBinaryArrayEnd does not crash (it's a no-op by default)
TEST_F(TiffVisitorTest_1627, VisitBinaryArrayEndNoOp_1627) {
    EXPECT_NO_THROW(visitor.visitBinaryArrayEnd(nullptr));
}

}  // namespace Internal
}  // namespace Exiv2
