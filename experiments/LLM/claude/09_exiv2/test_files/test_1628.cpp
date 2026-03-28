#include <gtest/gtest.h>

// Include necessary headers from the project
#include "tiffvisitor_int.hpp"

using namespace Exiv2::Internal;

// Since TiffVisitor is abstract (has virtual methods), we need a concrete subclass for testing
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

class TiffVisitorTest_1628 : public ::testing::Test {
protected:
    ConcreteTiffVisitor visitor;
};

// Test that go() returns true by default for GoEvent 0 (first event)
TEST_F(TiffVisitorTest_1628, GoReturnsDefaultTrueForFirstEvent_1628) {
    EXPECT_TRUE(visitor.go(static_cast<GoEvent>(0)));
}

// Test that go() returns true by default for GoEvent 1 (second event)
TEST_F(TiffVisitorTest_1628, GoReturnsDefaultTrueForSecondEvent_1628) {
    EXPECT_TRUE(visitor.go(static_cast<GoEvent>(1)));
}

// Test that setGo can set the first event to false
TEST_F(TiffVisitorTest_1628, SetGoFalseForFirstEvent_1628) {
    visitor.setGo(static_cast<GoEvent>(0), false);
    EXPECT_FALSE(visitor.go(static_cast<GoEvent>(0)));
}

// Test that setGo can set the second event to false
TEST_F(TiffVisitorTest_1628, SetGoFalseForSecondEvent_1628) {
    visitor.setGo(static_cast<GoEvent>(1), false);
    EXPECT_FALSE(visitor.go(static_cast<GoEvent>(1)));
}

// Test that setGo on one event does not affect the other event
TEST_F(TiffVisitorTest_1628, SetGoOnOneEventDoesNotAffectOther_1628) {
    visitor.setGo(static_cast<GoEvent>(0), false);
    EXPECT_FALSE(visitor.go(static_cast<GoEvent>(0)));
    EXPECT_TRUE(visitor.go(static_cast<GoEvent>(1)));
}

// Test that setGo can set a value back to true after being set to false
TEST_F(TiffVisitorTest_1628, SetGoBackToTrueAfterFalse_1628) {
    visitor.setGo(static_cast<GoEvent>(0), false);
    EXPECT_FALSE(visitor.go(static_cast<GoEvent>(0)));
    visitor.setGo(static_cast<GoEvent>(0), true);
    EXPECT_TRUE(visitor.go(static_cast<GoEvent>(0)));
}

// Test setting both events to false
TEST_F(TiffVisitorTest_1628, SetBothEventsToFalse_1628) {
    visitor.setGo(static_cast<GoEvent>(0), false);
    visitor.setGo(static_cast<GoEvent>(1), false);
    EXPECT_FALSE(visitor.go(static_cast<GoEvent>(0)));
    EXPECT_FALSE(visitor.go(static_cast<GoEvent>(1)));
}

// Test setting both events to true explicitly (should remain true)
TEST_F(TiffVisitorTest_1628, SetBothEventsToTrueExplicitly_1628) {
    visitor.setGo(static_cast<GoEvent>(0), true);
    visitor.setGo(static_cast<GoEvent>(1), true);
    EXPECT_TRUE(visitor.go(static_cast<GoEvent>(0)));
    EXPECT_TRUE(visitor.go(static_cast<GoEvent>(1)));
}

// Test multiple toggles of setGo
TEST_F(TiffVisitorTest_1628, MultipleToggles_1628) {
    visitor.setGo(static_cast<GoEvent>(0), false);
    EXPECT_FALSE(visitor.go(static_cast<GoEvent>(0)));
    visitor.setGo(static_cast<GoEvent>(0), true);
    EXPECT_TRUE(visitor.go(static_cast<GoEvent>(0)));
    visitor.setGo(static_cast<GoEvent>(0), false);
    EXPECT_FALSE(visitor.go(static_cast<GoEvent>(0)));
}

// Test that setting the same value multiple times is idempotent
TEST_F(TiffVisitorTest_1628, SetGoIdempotent_1628) {
    visitor.setGo(static_cast<GoEvent>(1), false);
    visitor.setGo(static_cast<GoEvent>(1), false);
    EXPECT_FALSE(visitor.go(static_cast<GoEvent>(1)));
    
    visitor.setGo(static_cast<GoEvent>(1), true);
    visitor.setGo(static_cast<GoEvent>(1), true);
    EXPECT_TRUE(visitor.go(static_cast<GoEvent>(1)));
}

// Test that virtual methods can be called without crashing (visitDirectoryNext, visitDirectoryEnd, etc.)
TEST_F(TiffVisitorTest_1628, VirtualMethodsDoNotCrash_1628) {
    EXPECT_NO_THROW(visitor.visitDirectoryNext(nullptr));
    EXPECT_NO_THROW(visitor.visitDirectoryEnd(nullptr));
    EXPECT_NO_THROW(visitor.visitIfdMakernoteEnd(nullptr));
    EXPECT_NO_THROW(visitor.visitBinaryArrayEnd(nullptr));
}
