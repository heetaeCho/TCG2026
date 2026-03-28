#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "tiffcomposite_int.hpp"
#include "basicio.hpp"

#include <cstring>

using namespace Exiv2;
using namespace Exiv2::Internal;

// A concrete TiffComponent subclass for testing purposes
class MockTiffComponent : public TiffComponent {
public:
    MockTiffComponent(uint16_t tag, IfdId group)
        : TiffComponent(tag, group), writeImageReturnValue_(0) {}

    void setWriteImageReturn(size_t val) { writeImageReturnValue_ = val; }

protected:
    size_t doWriteImage(IoWrapper& ioWrapper, ByteOrder byteOrder) const override {
        return writeImageReturnValue_;
    }

    size_t doWrite(IoWrapper& ioWrapper, ByteOrder byteOrder, size_t offset,
                   size_t valueIdx, size_t dataIdx, size_t& imageIdx) override {
        return 0;
    }

    size_t doWriteData(IoWrapper& ioWrapper, ByteOrder byteOrder, size_t offset,
                       size_t dataIdx, size_t& imageIdx) const override {
        return 0;
    }

    size_t doSize() const override { return 0; }
    size_t doCount() const override { return 0; }
    size_t doSizeData() const override { return 0; }
    size_t doSizeImage() const override { return writeImageReturnValue_; }

    void doAccept(TiffVisitor& visitor) override {}

    TiffComponent* doClone() const override {
        return new MockTiffComponent(*this);
    }

private:
    size_t writeImageReturnValue_;
};

class TiffDirectoryWriteImageTest_383 : public ::testing::Test {
protected:
    void SetUp() override {
        // Create a MemIo for IoWrapper
        memIo_ = std::make_unique<MemIo>();
        header_.fill(0);
        ioWrapper_ = std::make_unique<IoWrapper>(*memIo_, header_.data(), header_.size(), nullptr);
    }

    std::unique_ptr<MemIo> memIo_;
    std::array<byte, 8> header_;
    std::unique_ptr<IoWrapper> ioWrapper_;
};

// Test: Empty directory returns 0
TEST_F(TiffDirectoryWriteImageTest_383, EmptyDirectoryReturnsZero_383) {
    TiffDirectory dir(0x0001, IfdId::ifd0Id, false);
    size_t result = dir.writeImage(*ioWrapper_, littleEndian);
    EXPECT_EQ(result, 0u);
}

// Test: Empty directory with hasNext=true but no next set returns 0
TEST_F(TiffDirectoryWriteImageTest_383, EmptyDirectoryWithHasNextReturnsZero_383) {
    TiffDirectory dir(0x0001, IfdId::ifd0Id, true);
    size_t result = dir.writeImage(*ioWrapper_, littleEndian);
    EXPECT_EQ(result, 0u);
}

// Test: Single component (non-subIFD) writes image data
TEST_F(TiffDirectoryWriteImageTest_383, SingleNonSubIfdComponentWritesImage_383) {
    TiffDirectory dir(0x0001, IfdId::ifd0Id, false);

    auto comp = std::make_shared<MockTiffComponent>(0x0100, IfdId::ifd0Id);
    comp->setWriteImageReturn(42);
    dir.addChild(comp);

    size_t result = dir.writeImage(*ioWrapper_, littleEndian);
    EXPECT_EQ(result, 42u);
}

// Test: Multiple non-subIFD components accumulate write sizes
TEST_F(TiffDirectoryWriteImageTest_383, MultipleNonSubIfdComponentsAccumulate_383) {
    TiffDirectory dir(0x0001, IfdId::ifd0Id, false);

    auto comp1 = std::make_shared<MockTiffComponent>(0x0100, IfdId::ifd0Id);
    comp1->setWriteImageReturn(10);
    dir.addChild(comp1);

    auto comp2 = std::make_shared<MockTiffComponent>(0x0101, IfdId::ifd0Id);
    comp2->setWriteImageReturn(20);
    dir.addChild(comp2);

    size_t result = dir.writeImage(*ioWrapper_, littleEndian);
    EXPECT_EQ(result, 30u);
}

// Test: Component with tag 0x014a is written last (after other components)
TEST_F(TiffDirectoryWriteImageTest_383, SubIfdTagWrittenLast_383) {
    TiffDirectory dir(0x0001, IfdId::ifd0Id, false);

    auto subIfd = std::make_shared<MockTiffComponent>(0x014a, IfdId::ifd0Id);
    subIfd->setWriteImageReturn(50);
    dir.addChild(subIfd);

    auto comp = std::make_shared<MockTiffComponent>(0x0100, IfdId::ifd0Id);
    comp->setWriteImageReturn(30);
    dir.addChild(comp);

    size_t result = dir.writeImage(*ioWrapper_, littleEndian);
    EXPECT_EQ(result, 80u);
}

// Test: Only sub-IFD component
TEST_F(TiffDirectoryWriteImageTest_383, OnlySubIfdComponent_383) {
    TiffDirectory dir(0x0001, IfdId::ifd0Id, false);

    auto subIfd = std::make_shared<MockTiffComponent>(0x014a, IfdId::ifd0Id);
    subIfd->setWriteImageReturn(100);
    dir.addChild(subIfd);

    size_t result = dir.writeImage(*ioWrapper_, littleEndian);
    EXPECT_EQ(result, 100u);
}

// Test: Directory with next IFD
TEST_F(TiffDirectoryWriteImageTest_383, DirectoryWithNextIfd_383) {
    TiffDirectory dir(0x0001, IfdId::ifd0Id, true);

    auto comp = std::make_shared<MockTiffComponent>(0x0100, IfdId::ifd0Id);
    comp->setWriteImageReturn(15);
    dir.addChild(comp);

    auto nextDir = std::make_unique<MockTiffComponent>(0x0001, IfdId::ifd1Id);
    nextDir->setWriteImageReturn(25);
    dir.addNext(std::move(nextDir));

    size_t result = dir.writeImage(*ioWrapper_, littleEndian);
    EXPECT_EQ(result, 40u);
}

// Test: All three: regular components, sub-IFD, and next
TEST_F(TiffDirectoryWriteImageTest_383, AllComponentTypesPresent_383) {
    TiffDirectory dir(0x0001, IfdId::ifd0Id, true);

    auto comp1 = std::make_shared<MockTiffComponent>(0x0100, IfdId::ifd0Id);
    comp1->setWriteImageReturn(10);
    dir.addChild(comp1);

    auto subIfd = std::make_shared<MockTiffComponent>(0x014a, IfdId::ifd0Id);
    subIfd->setWriteImageReturn(20);
    dir.addChild(subIfd);

    auto comp2 = std::make_shared<MockTiffComponent>(0x0101, IfdId::ifd0Id);
    comp2->setWriteImageReturn(30);
    dir.addChild(comp2);

    auto nextDir = std::make_unique<MockTiffComponent>(0x0001, IfdId::ifd1Id);
    nextDir->setWriteImageReturn(40);
    dir.addNext(std::move(nextDir));

    size_t result = dir.writeImage(*ioWrapper_, littleEndian);
    // comp1(10) + comp2(30) + subIfd(20) + next(40) = 100
    EXPECT_EQ(result, 100u);
}

// Test: Components with zero write return values
TEST_F(TiffDirectoryWriteImageTest_383, ZeroSizeComponents_383) {
    TiffDirectory dir(0x0001, IfdId::ifd0Id, false);

    auto comp1 = std::make_shared<MockTiffComponent>(0x0100, IfdId::ifd0Id);
    comp1->setWriteImageReturn(0);
    dir.addChild(comp1);

    auto comp2 = std::make_shared<MockTiffComponent>(0x0101, IfdId::ifd0Id);
    comp2->setWriteImageReturn(0);
    dir.addChild(comp2);

    size_t result = dir.writeImage(*ioWrapper_, littleEndian);
    EXPECT_EQ(result, 0u);
}

// Test: BigEndian byte order
TEST_F(TiffDirectoryWriteImageTest_383, BigEndianByteOrder_383) {
    TiffDirectory dir(0x0001, IfdId::ifd0Id, false);

    auto comp = std::make_shared<MockTiffComponent>(0x0100, IfdId::ifd0Id);
    comp->setWriteImageReturn(55);
    dir.addChild(comp);

    size_t result = dir.writeImage(*ioWrapper_, bigEndian);
    EXPECT_EQ(result, 55u);
}

// Test: Multiple sub-IFD tags (0x014a) - only the last one should be used as pSubIfd
TEST_F(TiffDirectoryWriteImageTest_383, MultipleSubIfdTags_383) {
    TiffDirectory dir(0x0001, IfdId::ifd0Id, false);

    auto subIfd1 = std::make_shared<MockTiffComponent>(0x014a, IfdId::ifd0Id);
    subIfd1->setWriteImageReturn(10);
    dir.addChild(subIfd1);

    auto subIfd2 = std::make_shared<MockTiffComponent>(0x014a, IfdId::ifd0Id);
    subIfd2->setWriteImageReturn(20);
    dir.addChild(subIfd2);

    // The code replaces pSubIfd each time, so only the last one (20) gets
    // written via the pSubIfd path. But wait - looking at the code more carefully:
    // It does `continue` for 0x014a tags, so none of them are written in the loop.
    // Only the LAST pSubIfd is written after the loop.
    // So first subIfd1 is skipped (pSubIfd = subIfd1), then subIfd2 replaces it.
    // Only subIfd2 (20) is written.
    size_t result = dir.writeImage(*ioWrapper_, littleEndian);
    EXPECT_EQ(result, 20u);
}

// Test: hasNext() accessor
TEST_F(TiffDirectoryWriteImageTest_383, HasNextAccessor_383) {
    TiffDirectory dirWithNext(0x0001, IfdId::ifd0Id, true);
    EXPECT_TRUE(dirWithNext.hasNext());

    TiffDirectory dirWithoutNext(0x0001, IfdId::ifd0Id, false);
    EXPECT_FALSE(dirWithoutNext.hasNext());
}

// Test: Tag accessor on TiffDirectory
TEST_F(TiffDirectoryWriteImageTest_383, TagAccessor_383) {
    TiffDirectory dir(0x1234, IfdId::ifd0Id, false);
    EXPECT_EQ(dir.tag(), 0x1234);
}

// Test: Directory with only next, no children
TEST_F(TiffDirectoryWriteImageTest_383, OnlyNextNoChildren_383) {
    TiffDirectory dir(0x0001, IfdId::ifd0Id, true);

    auto nextDir = std::make_unique<MockTiffComponent>(0x0001, IfdId::ifd1Id);
    nextDir->setWriteImageReturn(77);
    dir.addNext(std::move(nextDir));

    size_t result = dir.writeImage(*ioWrapper_, littleEndian);
    EXPECT_EQ(result, 77u);
}

// Test: Large number of components
TEST_F(TiffDirectoryWriteImageTest_383, ManyComponents_383) {
    TiffDirectory dir(0x0001, IfdId::ifd0Id, false);

    size_t expected = 0;
    for (uint16_t i = 0; i < 100; ++i) {
        uint16_t tag = static_cast<uint16_t>(0x0100 + i);
        // Avoid 0x014a
        if (tag == 0x014a) continue;
        auto comp = std::make_shared<MockTiffComponent>(tag, IfdId::ifd0Id);
        comp->setWriteImageReturn(1);
        dir.addChild(comp);
        expected += 1;
    }

    size_t result = dir.writeImage(*ioWrapper_, littleEndian);
    EXPECT_EQ(result, expected);
}
