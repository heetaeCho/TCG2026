#include <gtest/gtest.h>
#include <gmock/gmock.h>

// Include necessary headers
#include "tiffcomposite_int.hpp"
#include "tiffvisitor_int.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

// ============================================================================
// Mock TiffVisitor for testing accept() and go() behavior
// ============================================================================
class MockTiffVisitor : public TiffVisitor {
public:
    // We track whether go() is called with geTraverse
    // We can control go() behavior via setGo()
    
    // We need to track if visitEntry etc. are called
    MOCK_METHOD(void, visitEntry, (TiffEntry* object), (override));
    MOCK_METHOD(void, visitDataEntry, (TiffDataEntry* object), (override));
    MOCK_METHOD(void, visitImageEntry, (TiffImageEntry* object), (override));
    MOCK_METHOD(void, visitSizeEntry, (TiffSizeEntry* object), (override));
    MOCK_METHOD(void, visitDirectory, (TiffDirectory* object), (override));
    MOCK_METHOD(void, visitDirectoryNext, (TiffDirectory* object), (override));
    MOCK_METHOD(void, visitDirectoryEnd, (TiffDirectory* object), (override));
    MOCK_METHOD(void, visitSubIfd, (TiffSubIfd* object), (override));
    MOCK_METHOD(void, visitMnEntry, (TiffMnEntry* object), (override));
    MOCK_METHOD(void, visitIfdMakernote, (TiffIfdMakernote* object), (override));
    MOCK_METHOD(void, visitIfdMakernoteEnd, (TiffIfdMakernote* object), (override));
    MOCK_METHOD(void, visitBinaryArray, (TiffBinaryArray* object), (override));
    MOCK_METHOD(void, visitBinaryArrayEnd, (TiffBinaryArray* object), (override));
    MOCK_METHOD(void, visitBinaryElement, (TiffBinaryElement* object), (override));
};

// ============================================================================
// Concrete TiffComponent subclass for testing (since TiffComponent has pure virtual methods)
// ============================================================================
class TestTiffComponent : public TiffComponent {
public:
    TestTiffComponent(uint16_t tag, IfdId group) : TiffComponent(tag, group) {}

    bool doAcceptCalled = false;

protected:
    void doAccept(TiffVisitor& visitor) override {
        doAcceptCalled = true;
        // Simulate what a real component might do - call visitEntry
        visitor.visitEntry(nullptr);
    }

    size_t doWrite(IoWrapper& /*ioWrapper*/, ByteOrder /*byteOrder*/, size_t /*offset*/,
                   size_t /*valueIdx*/, size_t /*dataIdx*/, size_t& /*imageIdx*/) override {
        return 0;
    }

    size_t doWriteData(IoWrapper& /*ioWrapper*/, ByteOrder /*byteOrder*/, size_t /*offset*/,
                       size_t /*dataIdx*/, size_t& /*imageIdx*/) const override {
        return 0;
    }

    size_t doWriteImage(IoWrapper& /*ioWrapper*/, ByteOrder /*byteOrder*/) const override {
        return 0;
    }

    size_t doSize() const override { return 0; }
    size_t doCount() const override { return 0; }
    size_t doSizeData() const override { return 0; }
    size_t doSizeImage() const override { return 0; }
};

// ============================================================================
// Test Fixture
// ============================================================================
class TiffComponentTest_337 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

class TiffVisitorTest_337 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// ============================================================================
// TiffComponent Tests
// ============================================================================

// Test constructor initializes tag correctly
TEST_F(TiffComponentTest_337, ConstructorSetsTag_337) {
    TestTiffComponent component(0x0100, IfdId::ifd0Id);
    EXPECT_EQ(component.tag(), 0x0100);
}

// Test constructor initializes group correctly
TEST_F(TiffComponentTest_337, ConstructorSetsGroup_337) {
    TestTiffComponent component(0x0100, IfdId::ifd0Id);
    EXPECT_EQ(component.group(), IfdId::ifd0Id);
}

// Test tag with zero value
TEST_F(TiffComponentTest_337, TagZeroValue_337) {
    TestTiffComponent component(0x0000, IfdId::ifd0Id);
    EXPECT_EQ(component.tag(), 0x0000);
}

// Test tag with max uint16 value
TEST_F(TiffComponentTest_337, TagMaxValue_337) {
    TestTiffComponent component(0xFFFF, IfdId::ifd0Id);
    EXPECT_EQ(component.tag(), 0xFFFF);
}

// Test start() returns nullptr initially
TEST_F(TiffComponentTest_337, StartInitiallyNull_337) {
    TestTiffComponent component(0x0100, IfdId::ifd0Id);
    EXPECT_EQ(component.start(), nullptr);
}

// Test setStart and start
TEST_F(TiffComponentTest_337, SetStartAndGetStart_337) {
    TestTiffComponent component(0x0100, IfdId::ifd0Id);
    byte data[] = {0x01, 0x02, 0x03};
    component.setStart(data);
    EXPECT_EQ(component.start(), data);
}

// Test setStart with nullptr
TEST_F(TiffComponentTest_337, SetStartWithNullptr_337) {
    TestTiffComponent component(0x0100, IfdId::ifd0Id);
    byte data[] = {0x01};
    component.setStart(data);
    EXPECT_EQ(component.start(), data);
    component.setStart(nullptr);
    EXPECT_EQ(component.start(), nullptr);
}

// Test idx() returns default value
TEST_F(TiffComponentTest_337, IdxDefaultValue_337) {
    TestTiffComponent component(0x0100, IfdId::ifd0Id);
    int result = component.idx();
    EXPECT_EQ(result, 0);
}

// Test count() delegates to doCount
TEST_F(TiffComponentTest_337, CountReturnsZeroForDefault_337) {
    TestTiffComponent component(0x0100, IfdId::ifd0Id);
    EXPECT_EQ(component.count(), 0u);
}

// Test size() delegates to doSize
TEST_F(TiffComponentTest_337, SizeReturnsZeroForDefault_337) {
    TestTiffComponent component(0x0100, IfdId::ifd0Id);
    EXPECT_EQ(component.size(), 0u);
}

// Test sizeData() delegates to doSizeData
TEST_F(TiffComponentTest_337, SizeDataReturnsZeroForDefault_337) {
    TestTiffComponent component(0x0100, IfdId::ifd0Id);
    EXPECT_EQ(component.sizeData(), 0u);
}

// Test sizeImage() delegates to doSizeImage
TEST_F(TiffComponentTest_337, SizeImageReturnsZeroForDefault_337) {
    TestTiffComponent component(0x0100, IfdId::ifd0Id);
    EXPECT_EQ(component.sizeImage(), 0u);
}

// Test accept() calls doAccept when go(geTraverse) is true
TEST_F(TiffComponentTest_337, AcceptCallsDoAcceptWhenGoIsTrue_337) {
    TestTiffComponent component(0x0100, IfdId::ifd0Id);
    MockTiffVisitor visitor;

    // By default, go(geTraverse) should be true
    EXPECT_CALL(visitor, visitEntry(nullptr)).Times(1);

    component.accept(visitor);
    EXPECT_TRUE(component.doAcceptCalled);
}

// Test accept() does NOT call doAccept when go(geTraverse) is false
TEST_F(TiffComponentTest_337, AcceptDoesNotCallDoAcceptWhenGoIsFalse_337) {
    TestTiffComponent component(0x0100, IfdId::ifd0Id);
    MockTiffVisitor visitor;

    visitor.setGo(TiffVisitor::geTraverse, false);

    EXPECT_CALL(visitor, visitEntry(testing::_)).Times(0);

    component.accept(visitor);
    EXPECT_FALSE(component.doAcceptCalled);
}

// Test addChild with nullptr (base implementation returns nullptr)
TEST_F(TiffComponentTest_337, AddChildBaseReturnsNull_337) {
    TestTiffComponent component(0x0100, IfdId::ifd0Id);
    TiffComponent* result = component.addChild(nullptr);
    EXPECT_EQ(result, nullptr);
}

// Test addNext with nullptr (base implementation returns nullptr)
TEST_F(TiffComponentTest_337, AddNextBaseReturnsNull_337) {
    TestTiffComponent component(0x0100, IfdId::ifd0Id);
    TiffComponent* result = component.addNext(nullptr);
    EXPECT_EQ(result, nullptr);
}

// ============================================================================
// TiffVisitor Tests
// ============================================================================

// Test go() returns true by default for geTraverse
TEST_F(TiffVisitorTest_337, GoTraverseDefaultTrue_337) {
    MockTiffVisitor visitor;
    EXPECT_TRUE(visitor.go(TiffVisitor::geTraverse));
}

// Test go() returns true by default for geKnownMakernote
TEST_F(TiffVisitorTest_337, GoKnownMakernoteDefaultTrue_337) {
    MockTiffVisitor visitor;
    EXPECT_TRUE(visitor.go(TiffVisitor::geKnownMakernote));
}

// Test setGo can disable geTraverse
TEST_F(TiffVisitorTest_337, SetGoDisableTraverse_337) {
    MockTiffVisitor visitor;
    visitor.setGo(TiffVisitor::geTraverse, false);
    EXPECT_FALSE(visitor.go(TiffVisitor::geTraverse));
}

// Test setGo can disable geKnownMakernote
TEST_F(TiffVisitorTest_337, SetGoDisableKnownMakernote_337) {
    MockTiffVisitor visitor;
    visitor.setGo(TiffVisitor::geKnownMakernote, false);
    EXPECT_FALSE(visitor.go(TiffVisitor::geKnownMakernote));
}

// Test setGo can re-enable geTraverse after disabling
TEST_F(TiffVisitorTest_337, SetGoReEnableTraverse_337) {
    MockTiffVisitor visitor;
    visitor.setGo(TiffVisitor::geTraverse, false);
    EXPECT_FALSE(visitor.go(TiffVisitor::geTraverse));
    visitor.setGo(TiffVisitor::geTraverse, true);
    EXPECT_TRUE(visitor.go(TiffVisitor::geTraverse));
}

// Test setGo can re-enable geKnownMakernote after disabling
TEST_F(TiffVisitorTest_337, SetGoReEnableKnownMakernote_337) {
    MockTiffVisitor visitor;
    visitor.setGo(TiffVisitor::geKnownMakernote, false);
    EXPECT_FALSE(visitor.go(TiffVisitor::geKnownMakernote));
    visitor.setGo(TiffVisitor::geKnownMakernote, true);
    EXPECT_TRUE(visitor.go(TiffVisitor::geKnownMakernote));
}

// Test disabling one event doesn't affect the other
TEST_F(TiffVisitorTest_337, SetGoIndependence_337) {
    MockTiffVisitor visitor;
    visitor.setGo(TiffVisitor::geTraverse, false);
    EXPECT_FALSE(visitor.go(TiffVisitor::geTraverse));
    EXPECT_TRUE(visitor.go(TiffVisitor::geKnownMakernote));
}

// Test disabling geKnownMakernote doesn't affect geTraverse
TEST_F(TiffVisitorTest_337, SetGoIndependenceReverse_337) {
    MockTiffVisitor visitor;
    visitor.setGo(TiffVisitor::geKnownMakernote, false);
    EXPECT_TRUE(visitor.go(TiffVisitor::geTraverse));
    EXPECT_FALSE(visitor.go(TiffVisitor::geKnownMakernote));
}

// Test setting same event multiple times
TEST_F(TiffVisitorTest_337, SetGoMultipleTimes_337) {
    MockTiffVisitor visitor;
    visitor.setGo(TiffVisitor::geTraverse, false);
    visitor.setGo(TiffVisitor::geTraverse, false);
    EXPECT_FALSE(visitor.go(TiffVisitor::geTraverse));
    visitor.setGo(TiffVisitor::geTraverse, true);
    visitor.setGo(TiffVisitor::geTraverse, true);
    EXPECT_TRUE(visitor.go(TiffVisitor::geTraverse));
}

// Test both events can be disabled simultaneously
TEST_F(TiffVisitorTest_337, DisableBothEvents_337) {
    MockTiffVisitor visitor;
    visitor.setGo(TiffVisitor::geTraverse, false);
    visitor.setGo(TiffVisitor::geKnownMakernote, false);
    EXPECT_FALSE(visitor.go(TiffVisitor::geTraverse));
    EXPECT_FALSE(visitor.go(TiffVisitor::geKnownMakernote));
}

// ============================================================================
// Integration Tests: TiffComponent + TiffVisitor
// ============================================================================

// Test accept with visitor where both go events are false
TEST_F(TiffComponentTest_337, AcceptWithAllGoEventsFalse_337) {
    TestTiffComponent component(0x0100, IfdId::ifd0Id);
    MockTiffVisitor visitor;

    visitor.setGo(TiffVisitor::geTraverse, false);
    visitor.setGo(TiffVisitor::geKnownMakernote, false);

    EXPECT_CALL(visitor, visitEntry(testing::_)).Times(0);
    component.accept(visitor);
    EXPECT_FALSE(component.doAcceptCalled);
}

// Test multiple accept calls on same component
TEST_F(TiffComponentTest_337, MultipleAcceptCalls_337) {
    TestTiffComponent component(0x0100, IfdId::ifd0Id);
    MockTiffVisitor visitor;

    EXPECT_CALL(visitor, visitEntry(nullptr)).Times(2);

    component.accept(visitor);
    component.doAcceptCalled = false;
    component.accept(visitor);
    EXPECT_TRUE(component.doAcceptCalled);
}

// Test accept toggles: first with go true, then false
TEST_F(TiffComponentTest_337, AcceptToggleGo_337) {
    TestTiffComponent component(0x0100, IfdId::ifd0Id);
    MockTiffVisitor visitor;

    // First call: go is true, doAccept should be called
    EXPECT_CALL(visitor, visitEntry(nullptr)).Times(1);
    component.accept(visitor);
    EXPECT_TRUE(component.doAcceptCalled);

    // Reset and disable traversal
    component.doAcceptCalled = false;
    visitor.setGo(TiffVisitor::geTraverse, false);
    component.accept(visitor);
    EXPECT_FALSE(component.doAcceptCalled);
}

// Test different tag/group combinations
TEST_F(TiffComponentTest_337, DifferentTagGroupCombinations_337) {
    TestTiffComponent comp1(0x0001, IfdId::ifd0Id);
    TestTiffComponent comp2(0x0002, IfdId::ifd1Id);

    EXPECT_EQ(comp1.tag(), 0x0001);
    EXPECT_EQ(comp2.tag(), 0x0002);
    EXPECT_EQ(comp1.group(), IfdId::ifd0Id);
    EXPECT_EQ(comp2.group(), IfdId::ifd1Id);
}
