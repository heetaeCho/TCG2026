#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "tiffcomposite_int.hpp"
#include "types.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

// Concrete subclass for testing since TiffComponent has pure virtual methods
class TestableTiffComponent : public TiffComponent {
public:
    TestableTiffComponent(uint16_t tag, IfdId group) : TiffComponent(tag, group) {}

protected:
    void doAccept(TiffVisitor& /*visitor*/) override {}
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

class TiffComponentTest_228 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that tag() returns the tag passed in the constructor
TEST_F(TiffComponentTest_228, TagReturnsConstructorValue_228) {
    TestableTiffComponent component(0x0100, IfdId::ifd0Id);
    EXPECT_EQ(component.tag(), 0x0100);
}

// Test that group() returns the group passed in the constructor
TEST_F(TiffComponentTest_228, GroupReturnsConstructorValue_228) {
    TestableTiffComponent component(0x0100, IfdId::ifd0Id);
    EXPECT_EQ(component.group(), IfdId::ifd0Id);
}

// Test that start() returns nullptr initially (default initialized)
TEST_F(TiffComponentTest_228, StartReturnsNullByDefault_228) {
    TestableTiffComponent component(0x0100, IfdId::ifd0Id);
    EXPECT_EQ(component.start(), nullptr);
}

// Test that setStart sets the start pointer and start() returns it
TEST_F(TiffComponentTest_228, SetStartUpdatesStartPointer_228) {
    TestableTiffComponent component(0x0100, IfdId::ifd0Id);
    byte data[] = {0x01, 0x02, 0x03, 0x04};
    component.setStart(data);
    EXPECT_EQ(component.start(), data);
}

// Test setStart with nullptr
TEST_F(TiffComponentTest_228, SetStartWithNullptr_228) {
    TestableTiffComponent component(0x0100, IfdId::ifd0Id);
    byte data[] = {0x01, 0x02};
    component.setStart(data);
    EXPECT_EQ(component.start(), data);
    component.setStart(nullptr);
    EXPECT_EQ(component.start(), nullptr);
}

// Test with different tag values
TEST_F(TiffComponentTest_228, TagWithZeroValue_228) {
    TestableTiffComponent component(0x0000, IfdId::ifd0Id);
    EXPECT_EQ(component.tag(), 0x0000);
}

// Test with max uint16 tag value
TEST_F(TiffComponentTest_228, TagWithMaxValue_228) {
    TestableTiffComponent component(0xFFFF, IfdId::ifd0Id);
    EXPECT_EQ(component.tag(), 0xFFFF);
}

// Test that setStart can be called multiple times and start() reflects the last value
TEST_F(TiffComponentTest_228, SetStartMultipleTimes_228) {
    TestableTiffComponent component(0x0100, IfdId::ifd0Id);
    byte data1[] = {0x01};
    byte data2[] = {0x02};
    component.setStart(data1);
    EXPECT_EQ(component.start(), data1);
    component.setStart(data2);
    EXPECT_EQ(component.start(), data2);
}

// Test idx() returns default value
TEST_F(TiffComponentTest_228, IdxReturnsDefaultValue_228) {
    TestableTiffComponent component(0x0100, IfdId::ifd0Id);
    // Default implementation returns 0
    EXPECT_EQ(component.idx(), 0);
}

// Test count() delegates to doCount()
TEST_F(TiffComponentTest_228, CountReturnsZeroForTestable_228) {
    TestableTiffComponent component(0x0100, IfdId::ifd0Id);
    EXPECT_EQ(component.count(), 0u);
}

// Test size() delegates to doSize()
TEST_F(TiffComponentTest_228, SizeReturnsZeroForTestable_228) {
    TestableTiffComponent component(0x0100, IfdId::ifd0Id);
    EXPECT_EQ(component.size(), 0u);
}

// Test sizeData() delegates to doSizeData()
TEST_F(TiffComponentTest_228, SizeDataReturnsZeroForTestable_228) {
    TestableTiffComponent component(0x0100, IfdId::ifd0Id);
    EXPECT_EQ(component.sizeData(), 0u);
}

// Test sizeImage() delegates to doSizeImage()
TEST_F(TiffComponentTest_228, SizeImageReturnsZeroForTestable_228) {
    TestableTiffComponent component(0x0100, IfdId::ifd0Id);
    EXPECT_EQ(component.sizeImage(), 0u);
}

// Test with different IfdId group
TEST_F(TiffComponentTest_228, GroupWithDifferentIfdId_228) {
    TestableTiffComponent component(0x0100, IfdId::exifId);
    EXPECT_EQ(component.group(), IfdId::exifId);
}

// Test that setStart with const byte pointer works correctly (const_cast internally)
TEST_F(TiffComponentTest_228, SetStartWithConstBytePointer_228) {
    TestableTiffComponent component(0x0100, IfdId::ifd0Id);
    const byte constData[] = {0xAA, 0xBB, 0xCC};
    component.setStart(constData);
    EXPECT_EQ(component.start(), constData);
}

// Test pointer arithmetic after setStart
TEST_F(TiffComponentTest_228, StartPointerPointsToCorrectData_228) {
    TestableTiffComponent component(0x0100, IfdId::ifd0Id);
    byte data[] = {0x10, 0x20, 0x30, 0x40};
    component.setStart(data);
    byte* p = component.start();
    EXPECT_EQ(p[0], 0x10);
    EXPECT_EQ(p[1], 0x20);
    EXPECT_EQ(p[2], 0x30);
    EXPECT_EQ(p[3], 0x40);
}

// Test that setStart to middle of buffer works
TEST_F(TiffComponentTest_228, SetStartToMiddleOfBuffer_228) {
    TestableTiffComponent component(0x0100, IfdId::ifd0Id);
    byte data[] = {0x10, 0x20, 0x30, 0x40};
    component.setStart(data + 2);
    EXPECT_EQ(component.start(), data + 2);
    EXPECT_EQ(component.start()[0], 0x30);
}
