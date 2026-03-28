#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "tiffcomposite_int.hpp"
#include "basicio.hpp"
#include "types.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

// A concrete subclass of TiffComponent for testing purposes,
// since TiffComponent has pure virtual methods.
class MockTiffComponent : public TiffComponent {
public:
    MockTiffComponent(uint16_t tag, IfdId group) : TiffComponent(tag, group) {}

    MOCK_METHOD(TiffComponent*, doAddPath, (uint16_t tag, TiffPath& tiffPath, TiffComponent* pRoot, TiffComponent::UniquePtr object), (override));
    MOCK_METHOD(TiffComponent*, doAddChild, (TiffComponent::SharedPtr tiffComponent), (override));
    MOCK_METHOD(TiffComponent*, doAddNext, (TiffComponent::UniquePtr tiffComponent), (override));
    MOCK_METHOD(void, doAccept, (TiffVisitor& visitor), (override));
    MOCK_METHOD(size_t, doWrite, (IoWrapper& ioWrapper, ByteOrder byteOrder, size_t offset, size_t valueIdx, size_t dataIdx, size_t& imageIdx), (override));
    MOCK_METHOD(size_t, doWriteData, (IoWrapper& ioWrapper, ByteOrder byteOrder, size_t offset, size_t dataIdx, size_t& imageIdx), (const, override));
    MOCK_METHOD(size_t, doWriteImage, (IoWrapper& ioWrapper, ByteOrder byteOrder), (const, override));
    MOCK_METHOD(size_t, doSize, (), (const, override));
    MOCK_METHOD(size_t, doCount, (), (const, override));
    MOCK_METHOD(size_t, doSizeData, (), (const, override));
    MOCK_METHOD(size_t, doSizeImage, (), (const, override));
    MOCK_METHOD(TiffComponent*, doClone, (), (const, override));
};

class TiffComponentTest_375 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test that tag() returns the tag passed to the constructor
TEST_F(TiffComponentTest_375, TagReturnsConstructorValue_375) {
    MockTiffComponent component(0x0100, IfdId::ifd0Id);
    EXPECT_EQ(component.tag(), 0x0100);
}

// Test that group() returns the group passed to the constructor
TEST_F(TiffComponentTest_375, GroupReturnsConstructorValue_375) {
    MockTiffComponent component(0x0100, IfdId::ifd0Id);
    EXPECT_EQ(component.group(), IfdId::ifd0Id);
}

// Test that tag works with zero value
TEST_F(TiffComponentTest_375, TagZeroValue_375) {
    MockTiffComponent component(0x0000, IfdId::ifd0Id);
    EXPECT_EQ(component.tag(), 0x0000);
}

// Test that tag works with max uint16_t value
TEST_F(TiffComponentTest_375, TagMaxValue_375) {
    MockTiffComponent component(0xFFFF, IfdId::ifd0Id);
    EXPECT_EQ(component.tag(), 0xFFFF);
}

// Test that start() returns nullptr initially
TEST_F(TiffComponentTest_375, StartReturnsNullInitially_375) {
    MockTiffComponent component(0x0100, IfdId::ifd0Id);
    EXPECT_EQ(component.start(), nullptr);
}

// Test that setStart and start work together
TEST_F(TiffComponentTest_375, SetStartAndStart_375) {
    MockTiffComponent component(0x0100, IfdId::ifd0Id);
    byte data[] = {0x01, 0x02, 0x03};
    component.setStart(data);
    EXPECT_EQ(component.start(), data);
}

// Test that setStart with nullptr sets start to nullptr
TEST_F(TiffComponentTest_375, SetStartNullptr_375) {
    MockTiffComponent component(0x0100, IfdId::ifd0Id);
    byte data[] = {0x01};
    component.setStart(data);
    EXPECT_EQ(component.start(), data);
    component.setStart(nullptr);
    EXPECT_EQ(component.start(), nullptr);
}

// Test that idx() returns default value
TEST_F(TiffComponentTest_375, IdxDefaultValue_375) {
    MockTiffComponent component(0x0100, IfdId::ifd0Id);
    // idx() is virtual but has a default implementation in TiffComponent
    // We don't mock it here to test the base implementation
    // The default returns 0
    EXPECT_EQ(component.idx(), 0);
}

// Test that writeData delegates to doWriteData
TEST_F(TiffComponentTest_375, WriteDataDelegatesToDoWriteData_375) {
    MockTiffComponent component(0x0100, IfdId::ifd0Id);
    
    MemIo memIo;
    byte header[] = {0x49, 0x49, 0x2A, 0x00, 0x08, 0x00, 0x00, 0x00};
    IoWrapper ioWrapper(memIo, header, sizeof(header), nullptr);
    
    size_t imageIdx = 0;
    
    EXPECT_CALL(component, doWriteData(testing::Ref(ioWrapper), littleEndian, 0, 0, testing::Ref(imageIdx)))
        .WillOnce(testing::Return(42));
    
    size_t result = component.writeData(ioWrapper, littleEndian, 0, 0, imageIdx);
    EXPECT_EQ(result, 42);
}

// Test that writeImage delegates to doWriteImage
TEST_F(TiffComponentTest_375, WriteImageDelegatesToDoWriteImage_375) {
    MockTiffComponent component(0x0100, IfdId::ifd0Id);
    
    MemIo memIo;
    byte header[] = {0x49, 0x49, 0x2A, 0x00, 0x08, 0x00, 0x00, 0x00};
    IoWrapper ioWrapper(memIo, header, sizeof(header), nullptr);
    
    EXPECT_CALL(component, doWriteImage(testing::Ref(ioWrapper), littleEndian))
        .WillOnce(testing::Return(100));
    
    size_t result = component.writeImage(ioWrapper, littleEndian);
    EXPECT_EQ(result, 100);
}

// Test that size delegates to doSize
TEST_F(TiffComponentTest_375, SizeDelegatesToDoSize_375) {
    MockTiffComponent component(0x0100, IfdId::ifd0Id);
    
    EXPECT_CALL(component, doSize())
        .WillOnce(testing::Return(256));
    
    size_t result = component.size();
    EXPECT_EQ(result, 256);
}

// Test that count delegates to doCount
TEST_F(TiffComponentTest_375, CountDelegatesToDoCount_375) {
    MockTiffComponent component(0x0100, IfdId::ifd0Id);
    
    EXPECT_CALL(component, doCount())
        .WillOnce(testing::Return(10));
    
    size_t result = component.count();
    EXPECT_EQ(result, 10);
}

// Test that sizeData delegates to doSizeData
TEST_F(TiffComponentTest_375, SizeDataDelegatesToDoSizeData_375) {
    MockTiffComponent component(0x0100, IfdId::ifd0Id);
    
    EXPECT_CALL(component, doSizeData())
        .WillOnce(testing::Return(512));
    
    size_t result = component.sizeData();
    EXPECT_EQ(result, 512);
}

// Test that sizeImage delegates to doSizeImage
TEST_F(TiffComponentTest_375, SizeImageDelegatesToDoSizeImage_375) {
    MockTiffComponent component(0x0100, IfdId::ifd0Id);
    
    EXPECT_CALL(component, doSizeImage())
        .WillOnce(testing::Return(1024));
    
    size_t result = component.sizeImage();
    EXPECT_EQ(result, 1024);
}

// Test write delegates to doWrite
TEST_F(TiffComponentTest_375, WriteDelegatesToDoWrite_375) {
    MockTiffComponent component(0x0100, IfdId::ifd0Id);
    
    MemIo memIo;
    byte header[] = {0x49, 0x49, 0x2A, 0x00, 0x08, 0x00, 0x00, 0x00};
    IoWrapper ioWrapper(memIo, header, sizeof(header), nullptr);
    
    size_t imageIdx = 0;
    
    EXPECT_CALL(component, doWrite(testing::Ref(ioWrapper), littleEndian, 8, 0, 0, testing::Ref(imageIdx)))
        .WillOnce(testing::Return(12));
    
    size_t result = component.write(ioWrapper, littleEndian, 8, 0, 0, imageIdx);
    EXPECT_EQ(result, 12);
}

// Test writeData with bigEndian byte order
TEST_F(TiffComponentTest_375, WriteDataBigEndian_375) {
    MockTiffComponent component(0x0100, IfdId::ifd0Id);
    
    MemIo memIo;
    byte header[] = {0x4D, 0x4D, 0x00, 0x2A, 0x00, 0x00, 0x00, 0x08};
    IoWrapper ioWrapper(memIo, header, sizeof(header), nullptr);
    
    size_t imageIdx = 0;
    
    EXPECT_CALL(component, doWriteData(testing::Ref(ioWrapper), bigEndian, 0, 0, testing::Ref(imageIdx)))
        .WillOnce(testing::Return(64));
    
    size_t result = component.writeData(ioWrapper, bigEndian, 0, 0, imageIdx);
    EXPECT_EQ(result, 64);
}

// Test writeData returns zero when doWriteData returns zero
TEST_F(TiffComponentTest_375, WriteDataReturnsZero_375) {
    MockTiffComponent component(0x0100, IfdId::ifd0Id);
    
    MemIo memIo;
    byte header[] = {0x49, 0x49, 0x2A, 0x00, 0x08, 0x00, 0x00, 0x00};
    IoWrapper ioWrapper(memIo, header, sizeof(header), nullptr);
    
    size_t imageIdx = 0;
    
    EXPECT_CALL(component, doWriteData(testing::_, testing::_, testing::_, testing::_, testing::_))
        .WillOnce(testing::Return(0));
    
    size_t result = component.writeData(ioWrapper, littleEndian, 0, 0, imageIdx);
    EXPECT_EQ(result, 0);
}

// Test writeData with non-zero offset and dataIdx
TEST_F(TiffComponentTest_375, WriteDataWithNonZeroOffsetAndDataIdx_375) {
    MockTiffComponent component(0x0100, IfdId::ifd0Id);
    
    MemIo memIo;
    byte header[] = {0x49, 0x49, 0x2A, 0x00, 0x08, 0x00, 0x00, 0x00};
    IoWrapper ioWrapper(memIo, header, sizeof(header), nullptr);
    
    size_t imageIdx = 500;
    
    EXPECT_CALL(component, doWriteData(testing::Ref(ioWrapper), littleEndian, 1024, 2048, testing::Ref(imageIdx)))
        .WillOnce(testing::Return(128));
    
    size_t result = component.writeData(ioWrapper, littleEndian, 1024, 2048, imageIdx);
    EXPECT_EQ(result, 128);
}

// Test that doWriteData modifies imageIdx through reference
TEST_F(TiffComponentTest_375, WriteDataModifiesImageIdx_375) {
    MockTiffComponent component(0x0100, IfdId::ifd0Id);
    
    MemIo memIo;
    byte header[] = {0x49, 0x49, 0x2A, 0x00, 0x08, 0x00, 0x00, 0x00};
    IoWrapper ioWrapper(memIo, header, sizeof(header), nullptr);
    
    size_t imageIdx = 0;
    
    EXPECT_CALL(component, doWriteData(testing::_, testing::_, testing::_, testing::_, testing::_))
        .WillOnce(testing::DoAll(
            testing::SetArgReferee<4>(100),
            testing::Return(50)
        ));
    
    size_t result = component.writeData(ioWrapper, littleEndian, 0, 0, imageIdx);
    EXPECT_EQ(result, 50);
    EXPECT_EQ(imageIdx, 100);
}

// Test construction with different IfdId groups
TEST_F(TiffComponentTest_375, ConstructionWithDifferentGroups_375) {
    MockTiffComponent comp1(0x0100, IfdId::ifd0Id);
    MockTiffComponent comp2(0x0100, IfdId::ifd1Id);
    MockTiffComponent comp3(0x0100, IfdId::exifId);
    
    EXPECT_EQ(comp1.group(), IfdId::ifd0Id);
    EXPECT_EQ(comp2.group(), IfdId::ifd1Id);
    EXPECT_EQ(comp3.group(), IfdId::exifId);
}

// Test multiple calls to writeData
TEST_F(TiffComponentTest_375, MultipleWriteDataCalls_375) {
    MockTiffComponent component(0x0100, IfdId::ifd0Id);
    
    MemIo memIo;
    byte header[] = {0x49, 0x49, 0x2A, 0x00, 0x08, 0x00, 0x00, 0x00};
    IoWrapper ioWrapper(memIo, header, sizeof(header), nullptr);
    
    size_t imageIdx = 0;
    
    EXPECT_CALL(component, doWriteData(testing::_, testing::_, testing::_, testing::_, testing::_))
        .WillOnce(testing::Return(10))
        .WillOnce(testing::Return(20))
        .WillOnce(testing::Return(30));
    
    EXPECT_EQ(component.writeData(ioWrapper, littleEndian, 0, 0, imageIdx), 10);
    EXPECT_EQ(component.writeData(ioWrapper, littleEndian, 10, 10, imageIdx), 20);
    EXPECT_EQ(component.writeData(ioWrapper, littleEndian, 30, 30, imageIdx), 30);
}

// Test IoWrapper construction and basic operation
TEST_F(TiffComponentTest_375, IoWrapperConstruction_375) {
    MemIo memIo;
    byte header[] = {0x49, 0x49, 0x2A, 0x00, 0x08, 0x00, 0x00, 0x00};
    
    // Should not throw
    EXPECT_NO_THROW(IoWrapper(memIo, header, sizeof(header), nullptr));
}

// Test IoWrapper write
TEST_F(TiffComponentTest_375, IoWrapperWrite_375) {
    MemIo memIo;
    byte header[] = {0x49, 0x49, 0x2A, 0x00, 0x08, 0x00, 0x00, 0x00};
    IoWrapper ioWrapper(memIo, header, sizeof(header), nullptr);
    
    byte data[] = {0x01, 0x02, 0x03, 0x04};
    size_t written = ioWrapper.write(data, sizeof(data));
    // First write should include header + data
    EXPECT_GT(written, 0u);
}

// Test IoWrapper putb
TEST_F(TiffComponentTest_375, IoWrapperPutb_375) {
    MemIo memIo;
    byte header[] = {0x49, 0x49, 0x2A, 0x00, 0x08, 0x00, 0x00, 0x00};
    IoWrapper ioWrapper(memIo, header, sizeof(header), nullptr);
    
    int result = ioWrapper.putb(0x42);
    EXPECT_EQ(result, 0x42);
}

// Test large offset values in writeData
TEST_F(TiffComponentTest_375, WriteDataLargeOffset_375) {
    MockTiffComponent component(0x0100, IfdId::ifd0Id);
    
    MemIo memIo;
    byte header[] = {0x49, 0x49, 0x2A, 0x00, 0x08, 0x00, 0x00, 0x00};
    IoWrapper ioWrapper(memIo, header, sizeof(header), nullptr);
    
    size_t imageIdx = SIZE_MAX - 1;
    size_t largeOffset = SIZE_MAX / 2;
    size_t largeDataIdx = SIZE_MAX / 2;
    
    EXPECT_CALL(component, doWriteData(testing::_, testing::_, largeOffset, largeDataIdx, testing::_))
        .WillOnce(testing::Return(0));
    
    size_t result = component.writeData(ioWrapper, littleEndian, largeOffset, largeDataIdx, imageIdx);
    EXPECT_EQ(result, 0);
}
