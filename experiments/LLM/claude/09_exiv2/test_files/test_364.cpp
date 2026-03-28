#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "tiffcomposite_int.hpp"
#include "basicio.hpp"
#include "types.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;
using namespace testing;

// A concrete subclass of TiffComponent for testing purposes
class TestableTiffComponent : public TiffComponent {
public:
    TestableTiffComponent(uint16_t tag, IfdId group) : TiffComponent(tag, group) {}

    MOCK_METHOD(size_t, doWrite, (IoWrapper& ioWrapper, ByteOrder byteOrder, size_t offset, size_t valueIdx, size_t dataIdx, size_t& imageIdx), (override));
    MOCK_METHOD(size_t, doWriteData, (IoWrapper& ioWrapper, ByteOrder byteOrder, size_t offset, size_t dataIdx, size_t& imageIdx), (const, override));
    MOCK_METHOD(size_t, doWriteImage, (IoWrapper& ioWrapper, ByteOrder byteOrder), (const, override));
    MOCK_METHOD(size_t, doSize, (), (const, override));
    MOCK_METHOD(size_t, doCount, (), (const, override));
    MOCK_METHOD(size_t, doSizeData, (), (const, override));
    MOCK_METHOD(size_t, doSizeImage, (), (const, override));
    MOCK_METHOD(void, doAccept, (TiffVisitor& visitor), (override));
    MOCK_METHOD(TiffComponent*, doAddPath, (uint16_t tag, TiffPath& tiffPath, TiffComponent* pRoot, TiffComponent::UniquePtr object), (override));
    MOCK_METHOD(TiffComponent*, doAddChild, (TiffComponent::SharedPtr tiffComponent), (override));
    MOCK_METHOD(TiffComponent*, doAddNext, (TiffComponent::UniquePtr tiffComponent), (override));
};

class TiffComponentTest_364 : public ::testing::Test {
protected:
    void SetUp() override {
    }
};

// Test that tag() returns the tag passed in the constructor
TEST_F(TiffComponentTest_364, TagReturnsConstructorValue_364) {
    TestableTiffComponent comp(0x0100, IfdId::ifd0Id);
    EXPECT_EQ(comp.tag(), 0x0100);
}

// Test that group() returns the group passed in the constructor
TEST_F(TiffComponentTest_364, GroupReturnsConstructorValue_364) {
    TestableTiffComponent comp(0x0100, IfdId::ifd0Id);
    EXPECT_EQ(comp.group(), IfdId::ifd0Id);
}

// Test tag with zero value
TEST_F(TiffComponentTest_364, TagZero_364) {
    TestableTiffComponent comp(0x0000, IfdId::ifd0Id);
    EXPECT_EQ(comp.tag(), 0x0000);
}

// Test tag with maximum uint16_t value
TEST_F(TiffComponentTest_364, TagMaxValue_364) {
    TestableTiffComponent comp(0xFFFF, IfdId::ifd0Id);
    EXPECT_EQ(comp.tag(), 0xFFFF);
}

// Test that write delegates to doWrite
TEST_F(TiffComponentTest_364, WriteDelegatesToDoWrite_364) {
    TestableTiffComponent comp(0x0100, IfdId::ifd0Id);
    
    MemIo memIo;
    const byte header[] = {0x49, 0x49, 0x2A, 0x00, 0x08, 0x00, 0x00, 0x00};
    IoWrapper ioWrapper(memIo, header, sizeof(header), nullptr);
    
    size_t imageIdx = 0;
    
    EXPECT_CALL(comp, doWrite(Ref(ioWrapper), littleEndian, 0, 0, 0, Ref(imageIdx)))
        .WillOnce(Return(42));
    
    size_t result = comp.write(ioWrapper, littleEndian, 0, 0, 0, imageIdx);
    EXPECT_EQ(result, 42);
}

// Test that write delegates with bigEndian byte order
TEST_F(TiffComponentTest_364, WriteBigEndian_364) {
    TestableTiffComponent comp(0x0100, IfdId::ifd0Id);
    
    MemIo memIo;
    const byte header[] = {0x4D, 0x4D, 0x00, 0x2A, 0x00, 0x00, 0x00, 0x08};
    IoWrapper ioWrapper(memIo, header, sizeof(header), nullptr);
    
    size_t imageIdx = 0;
    
    EXPECT_CALL(comp, doWrite(_, bigEndian, _, _, _, _))
        .WillOnce(Return(100));
    
    size_t result = comp.write(ioWrapper, bigEndian, 0, 0, 0, imageIdx);
    EXPECT_EQ(result, 100);
}

// Test write with non-zero offset values
TEST_F(TiffComponentTest_364, WriteWithNonZeroOffsets_364) {
    TestableTiffComponent comp(0x0110, IfdId::ifd1Id);
    
    MemIo memIo;
    const byte header[] = {0x49, 0x49, 0x2A, 0x00, 0x08, 0x00, 0x00, 0x00};
    IoWrapper ioWrapper(memIo, header, sizeof(header), nullptr);
    
    size_t imageIdx = 500;
    
    EXPECT_CALL(comp, doWrite(_, _, 100, 200, 300, _))
        .WillOnce(Return(50));
    
    size_t result = comp.write(ioWrapper, littleEndian, 100, 200, 300, imageIdx);
    EXPECT_EQ(result, 50);
}

// Test that count delegates to doCount
TEST_F(TiffComponentTest_364, CountDelegatesToDoCount_364) {
    TestableTiffComponent comp(0x0100, IfdId::ifd0Id);
    
    EXPECT_CALL(comp, doCount())
        .WillOnce(Return(5));
    
    EXPECT_EQ(comp.count(), 5);
}

// Test that size delegates to doSize
TEST_F(TiffComponentTest_364, SizeDelegatesToDoSize_364) {
    TestableTiffComponent comp(0x0100, IfdId::ifd0Id);
    
    EXPECT_CALL(comp, doSize())
        .WillOnce(Return(128));
    
    EXPECT_EQ(comp.size(), 128);
}

// Test that sizeData delegates to doSizeData
TEST_F(TiffComponentTest_364, SizeDataDelegatesToDoSizeData_364) {
    TestableTiffComponent comp(0x0100, IfdId::ifd0Id);
    
    EXPECT_CALL(comp, doSizeData())
        .WillOnce(Return(256));
    
    EXPECT_EQ(comp.sizeData(), 256);
}

// Test that sizeImage delegates to doSizeImage
TEST_F(TiffComponentTest_364, SizeImageDelegatesToDoSizeImage_364) {
    TestableTiffComponent comp(0x0100, IfdId::ifd0Id);
    
    EXPECT_CALL(comp, doSizeImage())
        .WillOnce(Return(1024));
    
    EXPECT_EQ(comp.sizeImage(), 1024);
}

// Test writeData delegates to doWriteData
TEST_F(TiffComponentTest_364, WriteDataDelegatesToDoWriteData_364) {
    TestableTiffComponent comp(0x0100, IfdId::ifd0Id);
    
    MemIo memIo;
    const byte header[] = {0x49, 0x49, 0x2A, 0x00, 0x08, 0x00, 0x00, 0x00};
    IoWrapper ioWrapper(memIo, header, sizeof(header), nullptr);
    
    size_t imageIdx = 0;
    
    EXPECT_CALL(comp, doWriteData(_, _, 0, 0, _))
        .WillOnce(Return(64));
    
    size_t result = comp.writeData(ioWrapper, littleEndian, 0, 0, imageIdx);
    EXPECT_EQ(result, 64);
}

// Test writeImage delegates to doWriteImage
TEST_F(TiffComponentTest_364, WriteImageDelegatesToDoWriteImage_364) {
    TestableTiffComponent comp(0x0100, IfdId::ifd0Id);
    
    MemIo memIo;
    const byte header[] = {0x49, 0x49, 0x2A, 0x00, 0x08, 0x00, 0x00, 0x00};
    IoWrapper ioWrapper(memIo, header, sizeof(header), nullptr);
    
    EXPECT_CALL(comp, doWriteImage(_, _))
        .WillOnce(Return(2048));
    
    size_t result = comp.writeImage(ioWrapper, littleEndian);
    EXPECT_EQ(result, 2048);
}

// Test that doWrite returning 0 is propagated
TEST_F(TiffComponentTest_364, WriteReturnsZero_364) {
    TestableTiffComponent comp(0x0100, IfdId::ifd0Id);
    
    MemIo memIo;
    const byte header[] = {0x49, 0x49, 0x2A, 0x00, 0x08, 0x00, 0x00, 0x00};
    IoWrapper ioWrapper(memIo, header, sizeof(header), nullptr);
    
    size_t imageIdx = 0;
    
    EXPECT_CALL(comp, doWrite(_, _, _, _, _, _))
        .WillOnce(Return(0));
    
    size_t result = comp.write(ioWrapper, littleEndian, 0, 0, 0, imageIdx);
    EXPECT_EQ(result, 0);
}

// Test that start() returns nullptr initially (pStart_ is default initialized)
TEST_F(TiffComponentTest_364, StartInitiallyNull_364) {
    TestableTiffComponent comp(0x0100, IfdId::ifd0Id);
    EXPECT_EQ(comp.start(), nullptr);
}

// Test setStart and start
TEST_F(TiffComponentTest_364, SetStartAndStart_364) {
    TestableTiffComponent comp(0x0100, IfdId::ifd0Id);
    byte data[] = {0x01, 0x02, 0x03};
    comp.setStart(data);
    EXPECT_EQ(comp.start(), data);
}

// Test idx returns default value
TEST_F(TiffComponentTest_364, IdxDefaultValue_364) {
    TestableTiffComponent comp(0x0100, IfdId::ifd0Id);
    // idx() has a default implementation that returns 0
    int result = comp.idx();
    EXPECT_EQ(result, 0);
}

// Test write with large offset values
TEST_F(TiffComponentTest_364, WriteWithLargeOffsets_364) {
    TestableTiffComponent comp(0x0100, IfdId::ifd0Id);
    
    MemIo memIo;
    const byte header[] = {0x49, 0x49, 0x2A, 0x00, 0x08, 0x00, 0x00, 0x00};
    IoWrapper ioWrapper(memIo, header, sizeof(header), nullptr);
    
    size_t imageIdx = SIZE_MAX;
    size_t largeOffset = SIZE_MAX / 2;
    
    EXPECT_CALL(comp, doWrite(_, _, largeOffset, largeOffset, largeOffset, _))
        .WillOnce(Return(largeOffset));
    
    size_t result = comp.write(ioWrapper, littleEndian, largeOffset, largeOffset, largeOffset, imageIdx);
    EXPECT_EQ(result, largeOffset);
}

// Test IoWrapper construction and write
class IoWrapperTest_364 : public ::testing::Test {
protected:
    void SetUp() override {
    }
};

TEST_F(IoWrapperTest_364, WriteDataToMemIo_364) {
    MemIo memIo;
    const byte header[] = {0x49, 0x49, 0x2A, 0x00, 0x08, 0x00, 0x00, 0x00};
    IoWrapper ioWrapper(memIo, header, sizeof(header), nullptr);
    
    const byte data[] = {0x01, 0x02, 0x03, 0x04};
    size_t written = ioWrapper.write(data, sizeof(data));
    // First write should also write the header
    EXPECT_GT(written, 0u);
}

TEST_F(IoWrapperTest_364, PutbWritesSingleByte_364) {
    MemIo memIo;
    const byte header[] = {0x49, 0x49, 0x2A, 0x00, 0x08, 0x00, 0x00, 0x00};
    IoWrapper ioWrapper(memIo, header, sizeof(header), nullptr);
    
    int result = ioWrapper.putb(0x42);
    EXPECT_EQ(result, 0x42);
}

TEST_F(IoWrapperTest_364, WriteZeroBytes_364) {
    MemIo memIo;
    const byte header[] = {0x49, 0x49};
    IoWrapper ioWrapper(memIo, header, sizeof(header), nullptr);
    
    const byte data[] = {0x00};
    size_t written = ioWrapper.write(data, 0);
    // Writing 0 bytes - the header may still be written
    // Just ensure no crash
    EXPECT_GE(written, 0u);
}

// Test multiple writes
TEST_F(IoWrapperTest_364, MultipleWrites_364) {
    MemIo memIo;
    const byte header[] = {0x49, 0x49, 0x2A, 0x00, 0x08, 0x00, 0x00, 0x00};
    IoWrapper ioWrapper(memIo, header, sizeof(header), nullptr);
    
    const byte data1[] = {0x01, 0x02};
    const byte data2[] = {0x03, 0x04};
    
    size_t written1 = ioWrapper.write(data1, sizeof(data1));
    size_t written2 = ioWrapper.write(data2, sizeof(data2));
    
    // First write includes header, second write should just be data
    EXPECT_GT(written1, 0u);
    EXPECT_GT(written2, 0u);
}

// Test with different IfdId groups
TEST_F(TiffComponentTest_364, DifferentGroups_364) {
    TestableTiffComponent comp1(0x0100, IfdId::ifd0Id);
    TestableTiffComponent comp2(0x0100, IfdId::ifd1Id);
    
    EXPECT_EQ(comp1.group(), IfdId::ifd0Id);
    EXPECT_EQ(comp2.group(), IfdId::ifd1Id);
    EXPECT_NE(comp1.group(), comp2.group());
}

// Test count returns zero for default
TEST_F(TiffComponentTest_364, CountReturnsZeroDefault_364) {
    TestableTiffComponent comp(0x0100, IfdId::ifd0Id);
    
    EXPECT_CALL(comp, doCount())
        .WillOnce(Return(0));
    
    EXPECT_EQ(comp.count(), 0u);
}

// Test that imageIdx is modifiable by doWrite through reference
TEST_F(TiffComponentTest_364, WriteModifiesImageIdx_364) {
    TestableTiffComponent comp(0x0100, IfdId::ifd0Id);
    
    MemIo memIo;
    const byte header[] = {0x49, 0x49, 0x2A, 0x00, 0x08, 0x00, 0x00, 0x00};
    IoWrapper ioWrapper(memIo, header, sizeof(header), nullptr);
    
    size_t imageIdx = 0;
    
    EXPECT_CALL(comp, doWrite(_, _, _, _, _, _))
        .WillOnce(DoAll(SetArgReferee<5>(999), Return(10)));
    
    comp.write(ioWrapper, littleEndian, 0, 0, 0, imageIdx);
    EXPECT_EQ(imageIdx, 999u);
}
