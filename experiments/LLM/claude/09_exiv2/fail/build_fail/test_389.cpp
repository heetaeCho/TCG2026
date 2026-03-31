#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "tiffcomposite_int.hpp"
#include "tiffimage_int.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

// A minimal concrete TiffComponent subclass for testing
class MockTiffComponent : public TiffComponent {
public:
    MockTiffComponent(uint16_t tag, IfdId group) : TiffComponent(tag, group) {}

    void setMockSize(size_t s) { mockSize_ = s; }
    void setMockSizeData(size_t s) { mockSizeData_ = s; }
    void setMockCount(size_t c) { mockCount_ = c; }

protected:
    size_t doSize() const override { return mockSize_; }
    size_t doSizeData() const override { return mockSizeData_; }
    size_t doSizeImage() const override { return 0; }
    size_t doCount() const override { return mockCount_; }
    size_t doWrite(IoWrapper&, ByteOrder, size_t, size_t, size_t, size_t&) override { return 0; }
    size_t doWriteData(IoWrapper&, ByteOrder, size_t, size_t, size_t&) const override { return 0; }
    size_t doWriteImage(IoWrapper&, ByteOrder) const override { return 0; }
    void doAccept(TiffVisitor&) override {}
    TiffComponent* doClone() const override { return nullptr; }

private:
    size_t mockSize_ = 0;
    size_t mockSizeData_ = 0;
    size_t mockCount_ = 1;
};

class TiffDirectoryTest_389 : public ::testing::Test {
protected:
    // Helper to create a TiffDirectory
    std::unique_ptr<TiffDirectory> makeDir(uint16_t tag, IfdId group, bool hasNext) {
        return std::make_unique<TiffDirectory>(tag, group, hasNext);
    }
};

// Test that an empty directory with no next returns size 0
TEST_F(TiffDirectoryTest_389, EmptyDirectoryNoNext_SizeIsZero_389) {
    auto dir = makeDir(0x0001, IfdId::ifd0Id, false);
    EXPECT_EQ(dir->size(), 0u);
}

// Test that an empty directory with hasNext=true but no next pointer still returns 0
TEST_F(TiffDirectoryTest_389, EmptyDirectoryWithHasNextFlag_SizeIsZero_389) {
    auto dir = makeDir(0x0001, IfdId::ifd0Id, true);
    EXPECT_EQ(dir->size(), 0u);
}

// Test that a directory with one child component and no next has correct base size
TEST_F(TiffDirectoryTest_389, OneChildNoNext_CorrectSize_389) {
    auto dir = makeDir(0x0001, IfdId::ifd0Id, false);
    
    // Add a child component with size <= 4 (fits inline) and sizeData = 0
    auto child = std::make_shared<MockTiffComponent>(0x0100, IfdId::ifd0Id);
    child->setMockSize(4);      // size <= 4, no extra value space
    child->setMockSizeData(0);  // no extra data
    child->setMockCount(1);
    
    dir->addChild(child);
    
    // Expected: 2 (count field) + 12*1 (one entry) + 0 (no next) = 14
    EXPECT_EQ(dir->size(), 14u);
}

// Test that a directory with hasNext=true and one child includes the 4-byte next pointer
TEST_F(TiffDirectoryTest_389, OneChildWithHasNext_IncludesNextPointer_389) {
    auto dir = makeDir(0x0001, IfdId::ifd0Id, true);
    
    auto child = std::make_shared<MockTiffComponent>(0x0100, IfdId::ifd0Id);
    child->setMockSize(4);
    child->setMockSizeData(0);
    child->setMockCount(1);
    
    dir->addChild(child);
    
    // Expected: 2 + 12*1 + 4 (hasNext) = 18
    EXPECT_EQ(dir->size(), 18u);
}

// Test that component with size > 4 adds aligned value to total size
TEST_F(TiffDirectoryTest_389, ComponentSizeGreaterThan4_AddsAlignedValue_389) {
    auto dir = makeDir(0x0001, IfdId::ifd0Id, false);
    
    auto child = std::make_shared<MockTiffComponent>(0x0100, IfdId::ifd0Id);
    child->setMockSize(6);      // > 4, so 6 + (6&1=0) = 6 extra bytes
    child->setMockSizeData(0);
    child->setMockCount(1);
    
    dir->addChild(child);
    
    // Expected: 2 + 12 + 6 = 20
    EXPECT_EQ(dir->size(), 20u);
}

// Test that component with odd size > 4 is word-aligned
TEST_F(TiffDirectoryTest_389, ComponentOddSizeGreaterThan4_AlignedToWordBoundary_389) {
    auto dir = makeDir(0x0001, IfdId::ifd0Id, false);
    
    auto child = std::make_shared<MockTiffComponent>(0x0100, IfdId::ifd0Id);
    child->setMockSize(5);      // > 4, so 5 + (5&1=1) = 6 extra bytes
    child->setMockSizeData(0);
    child->setMockCount(1);
    
    dir->addChild(child);
    
    // Expected: 2 + 12 + 6 = 20
    EXPECT_EQ(dir->size(), 20u);
}

// Test that sizeData is included and aligned
TEST_F(TiffDirectoryTest_389, ComponentWithSizeData_AddsAlignedData_389) {
    auto dir = makeDir(0x0001, IfdId::ifd0Id, false);
    
    auto child = std::make_shared<MockTiffComponent>(0x0100, IfdId::ifd0Id);
    child->setMockSize(4);       // <= 4, no value extra
    child->setMockSizeData(10);  // 10 + (10&1=0) = 10
    child->setMockCount(1);
    
    dir->addChild(child);
    
    // Expected: 2 + 12 + 10 = 24
    EXPECT_EQ(dir->size(), 24u);
}

// Test that odd sizeData is word-aligned
TEST_F(TiffDirectoryTest_389, ComponentWithOddSizeData_AlignedToWordBoundary_389) {
    auto dir = makeDir(0x0001, IfdId::ifd0Id, false);
    
    auto child = std::make_shared<MockTiffComponent>(0x0100, IfdId::ifd0Id);
    child->setMockSize(4);
    child->setMockSizeData(7);   // 7 + (7&1=1) = 8
    child->setMockCount(1);
    
    dir->addChild(child);
    
    // Expected: 2 + 12 + 8 = 22
    EXPECT_EQ(dir->size(), 22u);
}

// Test multiple children
TEST_F(TiffDirectoryTest_389, MultipleChildren_CorrectSize_389) {
    auto dir = makeDir(0x0001, IfdId::ifd0Id, false);
    
    auto child1 = std::make_shared<MockTiffComponent>(0x0100, IfdId::ifd0Id);
    child1->setMockSize(4);
    child1->setMockSizeData(0);
    child1->setMockCount(1);
    
    auto child2 = std::make_shared<MockTiffComponent>(0x0101, IfdId::ifd0Id);
    child2->setMockSize(8);      // 8 > 4 => 8 + (8&1=0) = 8
    child2->setMockSizeData(0);
    child2->setMockCount(1);
    
    dir->addChild(child1);
    dir->addChild(child2);
    
    // Expected: 2 + 12*2 + 8 = 34
    EXPECT_EQ(dir->size(), 34u);
}

// Test that component size exactly 4 does not add extra value
TEST_F(TiffDirectoryTest_389, ComponentSizeExactly4_NoExtraValue_389) {
    auto dir = makeDir(0x0001, IfdId::ifd0Id, false);
    
    auto child = std::make_shared<MockTiffComponent>(0x0100, IfdId::ifd0Id);
    child->setMockSize(4);
    child->setMockSizeData(0);
    child->setMockCount(1);
    
    dir->addChild(child);
    
    // Expected: 2 + 12 = 14
    EXPECT_EQ(dir->size(), 14u);
}

// Test component size exactly 0 (no extra value)
TEST_F(TiffDirectoryTest_389, ComponentSizeZero_NoExtraValue_389) {
    auto dir = makeDir(0x0001, IfdId::ifd0Id, false);
    
    auto child = std::make_shared<MockTiffComponent>(0x0100, IfdId::ifd0Id);
    child->setMockSize(0);
    child->setMockSizeData(0);
    child->setMockCount(1);
    
    dir->addChild(child);
    
    // Expected: 2 + 12 = 14
    EXPECT_EQ(dir->size(), 14u);
}

// Test both large size and sizeData together
TEST_F(TiffDirectoryTest_389, ComponentWithLargeSizeAndData_389) {
    auto dir = makeDir(0x0001, IfdId::ifd0Id, false);
    
    auto child = std::make_shared<MockTiffComponent>(0x0100, IfdId::ifd0Id);
    child->setMockSize(5);       // 5 > 4: 5 + 1 = 6
    child->setMockSizeData(3);   // 3 + 1 = 4
    child->setMockCount(1);
    
    dir->addChild(child);
    
    // Expected: 2 + 12 + 6 + 4 = 24
    EXPECT_EQ(dir->size(), 24u);
}

// Test hasNext getter
TEST_F(TiffDirectoryTest_389, HasNextReturnsCorrectValue_389) {
    auto dir1 = makeDir(0x0001, IfdId::ifd0Id, true);
    EXPECT_TRUE(dir1->hasNext());
    
    auto dir2 = makeDir(0x0001, IfdId::ifd0Id, false);
    EXPECT_FALSE(dir2->hasNext());
}

// Test count on empty directory
TEST_F(TiffDirectoryTest_389, EmptyDirectoryCount_IsZero_389) {
    auto dir = makeDir(0x0001, IfdId::ifd0Id, false);
    EXPECT_EQ(dir->count(), 0u);
}

// Test count with children
TEST_F(TiffDirectoryTest_389, DirectoryWithChildren_CountReflectsComponents_389) {
    auto dir = makeDir(0x0001, IfdId::ifd0Id, false);
    
    auto child1 = std::make_shared<MockTiffComponent>(0x0100, IfdId::ifd0Id);
    child1->setMockCount(1);
    dir->addChild(child1);
    
    // count() should reflect the number of components or their aggregate count
    EXPECT_GE(dir->count(), 1u);
}

// Test tag and group are properly stored
TEST_F(TiffDirectoryTest_389, TagAndGroupStored_389) {
    auto dir = makeDir(0x1234, IfdId::ifd0Id, false);
    EXPECT_EQ(dir->tag(), 0x1234);
    EXPECT_EQ(dir->group(), IfdId::ifd0Id);
}

// Test with three children, mix of sizes
TEST_F(TiffDirectoryTest_389, ThreeChildrenMixedSizes_CorrectTotalSize_389) {
    auto dir = makeDir(0x0001, IfdId::ifd0Id, true);
    
    auto child1 = std::make_shared<MockTiffComponent>(0x0100, IfdId::ifd0Id);
    child1->setMockSize(2);      // <= 4
    child1->setMockSizeData(0);
    
    auto child2 = std::make_shared<MockTiffComponent>(0x0101, IfdId::ifd0Id);
    child2->setMockSize(5);      // > 4: 5+1=6
    child2->setMockSizeData(3);  // 3+1=4
    
    auto child3 = std::make_shared<MockTiffComponent>(0x0102, IfdId::ifd0Id);
    child3->setMockSize(10);     // > 4: 10+0=10
    child3->setMockSizeData(0);
    
    dir->addChild(child1);
    dir->addChild(child2);
    dir->addChild(child3);
    
    // Expected: 2 + 12*3 + 4(hasNext) + 0(child1 val) + 6(child2 val) + 4(child2 data) + 10(child3 val)
    // = 2 + 36 + 4 + 6 + 4 + 10 = 62
    EXPECT_EQ(dir->size(), 62u);
}

// Test size with next directory set via addNext
TEST_F(TiffDirectoryTest_389, DirectoryWithNextDirectory_IncludesNextSize_389) {
    auto dir = makeDir(0x0001, IfdId::ifd0Id, true);
    
    auto child = std::make_shared<MockTiffComponent>(0x0100, IfdId::ifd0Id);
    child->setMockSize(4);
    child->setMockSizeData(0);
    
    dir->addChild(child);
    
    // Create a next directory with one child
    auto nextDir = std::make_unique<TiffDirectory>(0x0001, IfdId::ifd1Id, false);
    auto nextChild = std::make_shared<MockTiffComponent>(0x0200, IfdId::ifd1Id);
    nextChild->setMockSize(4);
    nextChild->setMockSizeData(0);
    nextDir->addChild(nextChild);
    
    dir->addNext(std::move(nextDir));
    
    // dir size: 2 + 12 + 4(hasNext) + nextDir->size()
    // nextDir size: 2 + 12 = 14
    // total: 18 + 14 = 32
    EXPECT_EQ(dir->size(), 32u);
}
