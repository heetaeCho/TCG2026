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

class TiffComponentTest_382 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test that tag() returns the tag passed to the constructor
TEST_F(TiffComponentTest_382, TagReturnsConstructorValue_382) {
    MockTiffComponent component(0x0100, IfdId::ifd0Id);
    EXPECT_EQ(component.tag(), 0x0100);
}

// Test that group() returns the group passed to the constructor
TEST_F(TiffComponentTest_382, GroupReturnsConstructorValue_382) {
    MockTiffComponent component(0x0100, IfdId::ifd0Id);
    EXPECT_EQ(component.group(), IfdId::ifd0Id);
}

// Test tag with zero value
TEST_F(TiffComponentTest_382, TagZeroValue_382) {
    MockTiffComponent component(0x0000, IfdId::ifd0Id);
    EXPECT_EQ(component.tag(), 0x0000);
}

// Test tag with max uint16 value
TEST_F(TiffComponentTest_382, TagMaxValue_382) {
    MockTiffComponent component(0xFFFF, IfdId::ifd0Id);
    EXPECT_EQ(component.tag(), 0xFFFF);
}

// Test that start() returns nullptr initially (pStart_ default initialized)
TEST_F(TiffComponentTest_382, StartInitiallyNull_382) {
    MockTiffComponent component(0x0100, IfdId::ifd0Id);
    EXPECT_EQ(component.start(), nullptr);
}

// Test setStart and start
TEST_F(TiffComponentTest_382, SetStartAndStart_382) {
    MockTiffComponent component(0x0100, IfdId::ifd0Id);
    byte data[] = {0x01, 0x02, 0x03};
    component.setStart(data);
    EXPECT_EQ(component.start(), data);
}

// Test that idx() returns default value (0)
TEST_F(TiffComponentTest_382, IdxReturnsDefaultValue_382) {
    MockTiffComponent component(0x0100, IfdId::ifd0Id);
    // idx() is virtual but has a default implementation returning 0
    EXPECT_EQ(component.TiffComponent::idx(), 0);
}

// Test writeImage delegates to doWriteImage
TEST_F(TiffComponentTest_382, WriteImageDelegatesToDoWriteImage_382) {
    MockTiffComponent component(0x0100, IfdId::ifd0Id);
    
    MemIo memIo;
    byte header[] = {0x4D, 0x4D};
    IoWrapper ioWrapper(memIo, header, sizeof(header), nullptr);
    
    EXPECT_CALL(component, doWriteImage(testing::Ref(ioWrapper), bigEndian))
        .WillOnce(testing::Return(42));
    
    size_t result = component.writeImage(ioWrapper, bigEndian);
    EXPECT_EQ(result, 42);
}

// Test writeImage with littleEndian byte order
TEST_F(TiffComponentTest_382, WriteImageLittleEndian_382) {
    MockTiffComponent component(0x0100, IfdId::ifd0Id);
    
    MemIo memIo;
    byte header[] = {0x49, 0x49};
    IoWrapper ioWrapper(memIo, header, sizeof(header), nullptr);
    
    EXPECT_CALL(component, doWriteImage(testing::Ref(ioWrapper), littleEndian))
        .WillOnce(testing::Return(100));
    
    size_t result = component.writeImage(ioWrapper, littleEndian);
    EXPECT_EQ(result, 100);
}

// Test writeImage returns zero when doWriteImage returns zero
TEST_F(TiffComponentTest_382, WriteImageReturnsZero_382) {
    MockTiffComponent component(0x0100, IfdId::ifd0Id);
    
    MemIo memIo;
    byte header[] = {0x4D, 0x4D};
    IoWrapper ioWrapper(memIo, header, sizeof(header), nullptr);
    
    EXPECT_CALL(component, doWriteImage(testing::_, testing::_))
        .WillOnce(testing::Return(0));
    
    size_t result = component.writeImage(ioWrapper, bigEndian);
    EXPECT_EQ(result, 0);
}

// Test count delegates to doCount
TEST_F(TiffComponentTest_382, CountDelegatesToDoCount_382) {
    MockTiffComponent component(0x0100, IfdId::ifd0Id);
    
    EXPECT_CALL(component, doCount())
        .WillOnce(testing::Return(5));
    
    size_t result = component.count();
    EXPECT_EQ(result, 5);
}

// Test size delegates to doSize
TEST_F(TiffComponentTest_382, SizeDelegatesToDoSize_382) {
    MockTiffComponent component(0x0100, IfdId::ifd0Id);
    
    EXPECT_CALL(component, doSize())
        .WillOnce(testing::Return(128));
    
    size_t result = component.size();
    EXPECT_EQ(result, 128);
}

// Test sizeData delegates to doSizeData
TEST_F(TiffComponentTest_382, SizeDataDelegatesToDoSizeData_382) {
    MockTiffComponent component(0x0100, IfdId::ifd0Id);
    
    EXPECT_CALL(component, doSizeData())
        .WillOnce(testing::Return(256));
    
    size_t result = component.sizeData();
    EXPECT_EQ(result, 256);
}

// Test sizeImage delegates to doSizeImage
TEST_F(TiffComponentTest_382, SizeImageDelegatesToDoSizeImage_382) {
    MockTiffComponent component(0x0100, IfdId::ifd0Id);
    
    EXPECT_CALL(component, doSizeImage())
        .WillOnce(testing::Return(1024));
    
    size_t result = component.sizeImage();
    EXPECT_EQ(result, 1024);
}

// Test write delegates to doWrite
TEST_F(TiffComponentTest_382, WriteDelegatesToDoWrite_382) {
    MockTiffComponent component(0x0100, IfdId::ifd0Id);
    
    MemIo memIo;
    byte header[] = {0x4D, 0x4D};
    IoWrapper ioWrapper(memIo, header, sizeof(header), nullptr);
    size_t imageIdx = 0;
    
    EXPECT_CALL(component, doWrite(testing::Ref(ioWrapper), bigEndian, 0, 0, 0, testing::Ref(imageIdx)))
        .WillOnce(testing::Return(12));
    
    size_t result = component.write(ioWrapper, bigEndian, 0, 0, 0, imageIdx);
    EXPECT_EQ(result, 12);
}

// Test writeData delegates to doWriteData
TEST_F(TiffComponentTest_382, WriteDataDelegatesToDoWriteData_382) {
    MockTiffComponent component(0x0100, IfdId::ifd0Id);
    
    MemIo memIo;
    byte header[] = {0x4D, 0x4D};
    IoWrapper ioWrapper(memIo, header, sizeof(header), nullptr);
    size_t imageIdx = 0;
    
    EXPECT_CALL(component, doWriteData(testing::Ref(ioWrapper), bigEndian, 0, 0, testing::Ref(imageIdx)))
        .WillOnce(testing::Return(64));
    
    size_t result = component.writeData(ioWrapper, bigEndian, 0, 0, imageIdx);
    EXPECT_EQ(result, 64);
}

// Test with large return values from writeImage
TEST_F(TiffComponentTest_382, WriteImageLargeReturnValue_382) {
    MockTiffComponent component(0x0100, IfdId::ifd0Id);
    
    MemIo memIo;
    byte header[] = {0x4D, 0x4D};
    IoWrapper ioWrapper(memIo, header, sizeof(header), nullptr);
    
    size_t largeValue = static_cast<size_t>(1) << 30; // 1 GB
    EXPECT_CALL(component, doWriteImage(testing::_, testing::_))
        .WillOnce(testing::Return(largeValue));
    
    size_t result = component.writeImage(ioWrapper, bigEndian);
    EXPECT_EQ(result, largeValue);
}

// Test multiple calls to writeImage
TEST_F(TiffComponentTest_382, WriteImageMultipleCalls_382) {
    MockTiffComponent component(0x0100, IfdId::ifd0Id);
    
    MemIo memIo;
    byte header[] = {0x4D, 0x4D};
    IoWrapper ioWrapper(memIo, header, sizeof(header), nullptr);
    
    EXPECT_CALL(component, doWriteImage(testing::_, testing::_))
        .WillOnce(testing::Return(10))
        .WillOnce(testing::Return(20))
        .WillOnce(testing::Return(30));
    
    EXPECT_EQ(component.writeImage(ioWrapper, bigEndian), 10);
    EXPECT_EQ(component.writeImage(ioWrapper, bigEndian), 20);
    EXPECT_EQ(component.writeImage(ioWrapper, bigEndian), 30);
}

// Test setStart with nullptr
TEST_F(TiffComponentTest_382, SetStartWithNullptr_382) {
    MockTiffComponent component(0x0100, IfdId::ifd0Id);
    byte data[] = {0x01};
    component.setStart(data);
    EXPECT_EQ(component.start(), data);
    component.setStart(nullptr);
    EXPECT_EQ(component.start(), nullptr);
}

// Test different IfdId groups
TEST_F(TiffComponentTest_382, DifferentGroups_382) {
    MockTiffComponent comp1(0x0100, IfdId::ifd0Id);
    MockTiffComponent comp2(0x0100, IfdId::ifd1Id);
    MockTiffComponent comp3(0x0100, IfdId::exifId);
    
    EXPECT_EQ(comp1.group(), IfdId::ifd0Id);
    EXPECT_EQ(comp2.group(), IfdId::ifd1Id);
    EXPECT_EQ(comp3.group(), IfdId::exifId);
}

// Test IoWrapper construction and write
TEST_F(TiffComponentTest_382, IoWrapperWrite_382) {
    MemIo memIo;
    byte header[] = {0x4D, 0x4D, 0x00, 0x2A};
    IoWrapper ioWrapper(memIo, header, sizeof(header), nullptr);
    
    byte data[] = {0x01, 0x02, 0x03, 0x04};
    size_t written = ioWrapper.write(data, sizeof(data));
    // The first write should include header + data
    EXPECT_GT(written, 0u);
}

// Test IoWrapper putb
TEST_F(TiffComponentTest_382, IoWrapperPutb_382) {
    MemIo memIo;
    byte header[] = {0x4D, 0x4D};
    IoWrapper ioWrapper(memIo, header, sizeof(header), nullptr);
    
    int result = ioWrapper.putb(0x42);
    // putb should succeed (non-negative or specific return)
    EXPECT_GE(result, 0);
}
