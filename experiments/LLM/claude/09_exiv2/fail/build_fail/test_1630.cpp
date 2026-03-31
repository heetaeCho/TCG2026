#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "tiffvisitor_int.hpp"
#include "tiffcomposite_int.hpp"

using namespace Exiv2::Internal;

// A concrete TiffComponent subclass for testing purposes
// We use TiffEntry which is a known concrete subclass
// But since we need minimal testable components, let's use what's available

namespace {

// Helper to create a simple TiffComponent-derived object for testing
// TiffEntry is a concrete subclass of TiffComponent
class TestTiffComponent : public TiffComponent {
public:
    TestTiffComponent(uint16_t tag, IfdId group) : TiffComponent(tag, group) {}

protected:
    void doAccept(TiffVisitor& visitor) override {
        // Simulate what a real component does - call findObject via visitor
        // For TiffFinder, the visit methods call findObject
    }

    size_t doWrite(IoWrapper&, ByteOrder, size_t, size_t, size_t, size_t&) override { return 0; }
    size_t doWriteData(IoWrapper&, ByteOrder, size_t, size_t, size_t&) const override { return 0; }
    size_t doWriteImage(IoWrapper&, ByteOrder) const override { return 0; }
    size_t doSize() const override { return 0; }
    size_t doCount() const override { return 0; }
    size_t doSizeData() const override { return 0; }
    size_t doSizeImage() const override { return 0; }
};

} // anonymous namespace

class TiffFinderTest_1630 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

class TiffVisitorTest_1630 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test TiffVisitor::go() returns true by default for geTraverse
TEST_F(TiffVisitorTest_1630, GoDefaultTrueForTraverse_1630) {
    TiffFinder finder(0x0100, IfdId::ifd0Id);
    EXPECT_TRUE(finder.go(TiffVisitor::geTraverse));
}

// Test TiffVisitor::go() returns true by default for geKnownMakernote
TEST_F(TiffVisitorTest_1630, GoDefaultTrueForKnownMakernote_1630) {
    TiffFinder finder(0x0100, IfdId::ifd0Id);
    EXPECT_TRUE(finder.go(TiffVisitor::geKnownMakernote));
}

// Test TiffVisitor::setGo() can set geTraverse to false
TEST_F(TiffVisitorTest_1630, SetGoTraverseFalse_1630) {
    TiffFinder finder(0x0100, IfdId::ifd0Id);
    finder.setGo(TiffVisitor::geTraverse, false);
    EXPECT_FALSE(finder.go(TiffVisitor::geTraverse));
}

// Test TiffVisitor::setGo() can set geKnownMakernote to false
TEST_F(TiffVisitorTest_1630, SetGoKnownMakernoteFalse_1630) {
    TiffFinder finder(0x0100, IfdId::ifd0Id);
    finder.setGo(TiffVisitor::geKnownMakernote, false);
    EXPECT_FALSE(finder.go(TiffVisitor::geKnownMakernote));
}

// Test TiffVisitor::setGo() can set back to true
TEST_F(TiffVisitorTest_1630, SetGoBackToTrue_1630) {
    TiffFinder finder(0x0100, IfdId::ifd0Id);
    finder.setGo(TiffVisitor::geTraverse, false);
    EXPECT_FALSE(finder.go(TiffVisitor::geTraverse));
    finder.setGo(TiffVisitor::geTraverse, true);
    EXPECT_TRUE(finder.go(TiffVisitor::geTraverse));
}

// Test TiffFinder::result() returns nullptr initially
TEST_F(TiffFinderTest_1630, ResultInitiallyNull_1630) {
    TiffFinder finder(0x0100, IfdId::ifd0Id);
    EXPECT_EQ(nullptr, finder.result());
}

// Test TiffFinder::findObject() with matching tag and group
TEST_F(TiffFinderTest_1630, FindObjectMatchingTagAndGroup_1630) {
    const uint16_t tag = 0x0100;
    const IfdId group = IfdId::ifd0Id;

    TiffFinder finder(tag, group);
    TestTiffComponent component(tag, group);

    finder.findObject(&component);

    EXPECT_EQ(&component, finder.result());
    // After finding, geTraverse should be set to false
    EXPECT_FALSE(finder.go(TiffVisitor::geTraverse));
}

// Test TiffFinder::findObject() with non-matching tag
TEST_F(TiffFinderTest_1630, FindObjectNonMatchingTag_1630) {
    TiffFinder finder(0x0100, IfdId::ifd0Id);
    TestTiffComponent component(0x0200, IfdId::ifd0Id);

    finder.findObject(&component);

    EXPECT_EQ(nullptr, finder.result());
    // geTraverse should still be true since no match
    EXPECT_TRUE(finder.go(TiffVisitor::geTraverse));
}

// Test TiffFinder::findObject() with non-matching group
TEST_F(TiffFinderTest_1630, FindObjectNonMatchingGroup_1630) {
    TiffFinder finder(0x0100, IfdId::ifd0Id);
    TestTiffComponent component(0x0100, IfdId::ifd1Id);

    finder.findObject(&component);

    EXPECT_EQ(nullptr, finder.result());
    EXPECT_TRUE(finder.go(TiffVisitor::geTraverse));
}

// Test TiffFinder::findObject() with non-matching tag and group
TEST_F(TiffFinderTest_1630, FindObjectNonMatchingTagAndGroup_1630) {
    TiffFinder finder(0x0100, IfdId::ifd0Id);
    TestTiffComponent component(0x0200, IfdId::ifd1Id);

    finder.findObject(&component);

    EXPECT_EQ(nullptr, finder.result());
    EXPECT_TRUE(finder.go(TiffVisitor::geTraverse));
}

// Test TiffFinder::init() resets the finder state
TEST_F(TiffFinderTest_1630, InitResetsState_1630) {
    const uint16_t tag1 = 0x0100;
    const IfdId group1 = IfdId::ifd0Id;

    TiffFinder finder(tag1, group1);
    TestTiffComponent component1(tag1, group1);

    // First find
    finder.findObject(&component1);
    EXPECT_EQ(&component1, finder.result());
    EXPECT_FALSE(finder.go(TiffVisitor::geTraverse));

    // Re-initialize with different tag/group
    const uint16_t tag2 = 0x0200;
    const IfdId group2 = IfdId::ifd1Id;
    finder.init(tag2, group2);

    // After init, result should be reset (null) and we can search again
    EXPECT_EQ(nullptr, finder.result());
}

// Test TiffFinder::init() allows finding a new object
TEST_F(TiffFinderTest_1630, InitAllowsNewSearch_1630) {
    TiffFinder finder(0x0100, IfdId::ifd0Id);
    TestTiffComponent component1(0x0100, IfdId::ifd0Id);
    finder.findObject(&component1);
    EXPECT_EQ(&component1, finder.result());

    // Reinitialize to search for different component
    finder.init(0x0200, IfdId::ifd1Id);
    TestTiffComponent component2(0x0200, IfdId::ifd1Id);
    finder.findObject(&component2);
    EXPECT_EQ(&component2, finder.result());
}

// Test TiffFinder with tag value 0
TEST_F(TiffFinderTest_1630, FindObjectWithZeroTag_1630) {
    TiffFinder finder(0x0000, IfdId::ifd0Id);
    TestTiffComponent component(0x0000, IfdId::ifd0Id);

    finder.findObject(&component);

    EXPECT_EQ(&component, finder.result());
    EXPECT_FALSE(finder.go(TiffVisitor::geTraverse));
}

// Test TiffFinder with maximum tag value
TEST_F(TiffFinderTest_1630, FindObjectWithMaxTag_1630) {
    TiffFinder finder(0xFFFF, IfdId::ifd0Id);
    TestTiffComponent component(0xFFFF, IfdId::ifd0Id);

    finder.findObject(&component);

    EXPECT_EQ(&component, finder.result());
    EXPECT_FALSE(finder.go(TiffVisitor::geTraverse));
}

// Test that geKnownMakernote is not affected by findObject
TEST_F(TiffFinderTest_1630, FindObjectDoesNotAffectKnownMakernote_1630) {
    TiffFinder finder(0x0100, IfdId::ifd0Id);
    TestTiffComponent component(0x0100, IfdId::ifd0Id);

    EXPECT_TRUE(finder.go(TiffVisitor::geKnownMakernote));
    finder.findObject(&component);
    // geKnownMakernote should remain true
    EXPECT_TRUE(finder.go(TiffVisitor::geKnownMakernote));
}

// Test multiple findObject calls - first non-match, then match
TEST_F(TiffFinderTest_1630, FindObjectMultipleCallsFirstMiss_1630) {
    TiffFinder finder(0x0100, IfdId::ifd0Id);
    TestTiffComponent nonMatch(0x0200, IfdId::ifd0Id);
    TestTiffComponent match(0x0100, IfdId::ifd0Id);

    finder.findObject(&nonMatch);
    EXPECT_EQ(nullptr, finder.result());
    EXPECT_TRUE(finder.go(TiffVisitor::geTraverse));

    finder.findObject(&match);
    EXPECT_EQ(&match, finder.result());
    EXPECT_FALSE(finder.go(TiffVisitor::geTraverse));
}

// Test TiffComponent::tag() returns correct tag
TEST_F(TiffFinderTest_1630, ComponentTagReturnsCorrectValue_1630) {
    TestTiffComponent component(0x0100, IfdId::ifd0Id);
    EXPECT_EQ(0x0100, component.tag());
}

// Test TiffComponent::group() returns correct group
TEST_F(TiffFinderTest_1630, ComponentGroupReturnsCorrectValue_1630) {
    TestTiffComponent component(0x0100, IfdId::ifd0Id);
    EXPECT_EQ(IfdId::ifd0Id, component.group());
}

// Test setting go events independently
TEST_F(TiffVisitorTest_1630, SetGoEventsIndependently_1630) {
    TiffFinder finder(0x0100, IfdId::ifd0Id);

    finder.setGo(TiffVisitor::geTraverse, false);
    EXPECT_FALSE(finder.go(TiffVisitor::geTraverse));
    EXPECT_TRUE(finder.go(TiffVisitor::geKnownMakernote));

    finder.setGo(TiffVisitor::geKnownMakernote, false);
    EXPECT_FALSE(finder.go(TiffVisitor::geTraverse));
    EXPECT_FALSE(finder.go(TiffVisitor::geKnownMakernote));

    finder.setGo(TiffVisitor::geTraverse, true);
    EXPECT_TRUE(finder.go(TiffVisitor::geTraverse));
    EXPECT_FALSE(finder.go(TiffVisitor::geKnownMakernote));
}
