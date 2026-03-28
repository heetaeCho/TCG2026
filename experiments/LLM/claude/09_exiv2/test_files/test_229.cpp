#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "tiffcomposite_int.hpp"
#include "types.hpp"
#include "tags_int.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

// Concrete subclass of TiffComponent for testing purposes
// We need this because TiffComponent has pure virtual methods
class TestableTiffComponent : public TiffComponent {
public:
    TestableTiffComponent(uint16_t tag, IfdId group) : TiffComponent(tag, group) {}

protected:
    TiffComponent* doAddPath(uint16_t tag, TiffPath& tiffPath, TiffComponent* pRoot, TiffComponent::UniquePtr object) override {
        return nullptr;
    }
    TiffComponent* doAddChild(TiffComponent::SharedPtr tiffComponent) override {
        return nullptr;
    }
    TiffComponent* doAddNext(TiffComponent::UniquePtr tiffComponent) override {
        return nullptr;
    }
    void doAccept(TiffVisitor& visitor) override {}
    size_t doWrite(IoWrapper& ioWrapper, ByteOrder byteOrder, size_t offset, size_t valueIdx, size_t dataIdx, size_t& imageIdx) override {
        return 0;
    }
    size_t doWriteData(IoWrapper& ioWrapper, ByteOrder byteOrder, size_t offset, size_t dataIdx, size_t& imageIdx) const override {
        return 0;
    }
    size_t doWriteImage(IoWrapper& ioWrapper, ByteOrder byteOrder) const override {
        return 0;
    }
    size_t doSize() const override {
        return 0;
    }
    size_t doCount() const override {
        return 0;
    }
    size_t doSizeData() const override {
        return 0;
    }
    size_t doSizeImage() const override {
        return 0;
    }
};

class TiffComponentTest_229 : public ::testing::Test {
protected:
    void SetUp() override {
    }
    void TearDown() override {
    }
};

// Test that tag() returns the tag value passed in the constructor
TEST_F(TiffComponentTest_229, TagReturnsConstructorValue_229) {
    TestableTiffComponent component(0x0100, IfdId::ifd0Id);
    EXPECT_EQ(0x0100, component.tag());
}

// Test that group() returns the group value passed in the constructor
TEST_F(TiffComponentTest_229, GroupReturnsConstructorValue_229) {
    TestableTiffComponent component(0x0100, IfdId::ifd0Id);
    EXPECT_EQ(IfdId::ifd0Id, component.group());
}

// Test with tag value of 0
TEST_F(TiffComponentTest_229, TagZeroValue_229) {
    TestableTiffComponent component(0x0000, IfdId::ifd0Id);
    EXPECT_EQ(0x0000, component.tag());
}

// Test with maximum uint16_t tag value
TEST_F(TiffComponentTest_229, TagMaxValue_229) {
    TestableTiffComponent component(0xFFFF, IfdId::ifd0Id);
    EXPECT_EQ(0xFFFF, component.tag());
}

// Test that start() returns nullptr initially (pStart_ is default initialized)
TEST_F(TiffComponentTest_229, StartInitiallyNull_229) {
    TestableTiffComponent component(0x0100, IfdId::ifd0Id);
    EXPECT_EQ(nullptr, component.start());
}

// Test setStart and start
TEST_F(TiffComponentTest_229, SetStartAndRetrieve_229) {
    TestableTiffComponent component(0x0100, IfdId::ifd0Id);
    byte data[] = {0x01, 0x02, 0x03};
    component.setStart(data);
    EXPECT_EQ(data, component.start());
}

// Test setStart with nullptr
TEST_F(TiffComponentTest_229, SetStartToNull_229) {
    TestableTiffComponent component(0x0100, IfdId::ifd0Id);
    byte data[] = {0x01, 0x02};
    component.setStart(data);
    EXPECT_EQ(data, component.start());
    component.setStart(nullptr);
    EXPECT_EQ(nullptr, component.start());
}

// Test idx() returns default value
TEST_F(TiffComponentTest_229, IdxDefaultValue_229) {
    TestableTiffComponent component(0x0100, IfdId::ifd0Id);
    int result = component.idx();
    EXPECT_EQ(0, result);
}

// Test count() delegates to doCount() and returns 0 for our test implementation
TEST_F(TiffComponentTest_229, CountReturnsZeroForTestImpl_229) {
    TestableTiffComponent component(0x0100, IfdId::ifd0Id);
    EXPECT_EQ(0u, component.count());
}

// Test size() delegates to doSize() and returns 0 for our test implementation
TEST_F(TiffComponentTest_229, SizeReturnsZeroForTestImpl_229) {
    TestableTiffComponent component(0x0100, IfdId::ifd0Id);
    EXPECT_EQ(0u, component.size());
}

// Test sizeData() delegates to doSizeData() and returns 0
TEST_F(TiffComponentTest_229, SizeDataReturnsZeroForTestImpl_229) {
    TestableTiffComponent component(0x0100, IfdId::ifd0Id);
    EXPECT_EQ(0u, component.sizeData());
}

// Test sizeImage() delegates to doSizeImage() and returns 0
TEST_F(TiffComponentTest_229, SizeImageReturnsZeroForTestImpl_229) {
    TestableTiffComponent component(0x0100, IfdId::ifd0Id);
    EXPECT_EQ(0u, component.sizeImage());
}

// Test addChild returns nullptr for base test implementation
TEST_F(TiffComponentTest_229, AddChildReturnsNull_229) {
    TestableTiffComponent component(0x0100, IfdId::ifd0Id);
    auto child = std::make_shared<TestableTiffComponent>(0x0101, IfdId::ifd0Id);
    TiffComponent* result = component.addChild(child);
    EXPECT_EQ(nullptr, result);
}

// Test addNext returns nullptr for base test implementation
TEST_F(TiffComponentTest_229, AddNextReturnsNull_229) {
    TestableTiffComponent component(0x0100, IfdId::ifd0Id);
    auto next = std::make_unique<TestableTiffComponent>(0x0102, IfdId::ifd0Id);
    TiffComponent* result = component.addNext(std::move(next));
    EXPECT_EQ(nullptr, result);
}

// Test multiple components with different tags
TEST_F(TiffComponentTest_229, DifferentTagValues_229) {
    TestableTiffComponent comp1(0x0100, IfdId::ifd0Id);
    TestableTiffComponent comp2(0x0110, IfdId::ifd0Id);
    TestableTiffComponent comp3(0x0112, IfdId::ifd0Id);

    EXPECT_EQ(0x0100, comp1.tag());
    EXPECT_EQ(0x0110, comp2.tag());
    EXPECT_EQ(0x0112, comp3.tag());
    EXPECT_NE(comp1.tag(), comp2.tag());
    EXPECT_NE(comp2.tag(), comp3.tag());
}

// Test multiple components with different groups
TEST_F(TiffComponentTest_229, DifferentGroupValues_229) {
    TestableTiffComponent comp1(0x0100, IfdId::ifd0Id);
    TestableTiffComponent comp2(0x0100, IfdId::ifd1Id);

    EXPECT_EQ(IfdId::ifd0Id, comp1.group());
    EXPECT_EQ(IfdId::ifd1Id, comp2.group());
    EXPECT_NE(comp1.group(), comp2.group());
}

// Test that setStart can be called multiple times
TEST_F(TiffComponentTest_229, SetStartMultipleTimes_229) {
    TestableTiffComponent component(0x0100, IfdId::ifd0Id);
    byte data1[] = {0x01};
    byte data2[] = {0x02};

    component.setStart(data1);
    EXPECT_EQ(data1, component.start());

    component.setStart(data2);
    EXPECT_EQ(data2, component.start());
}

// Test with a common TIFF tag value (ImageWidth = 0x0100)
TEST_F(TiffComponentTest_229, CommonTiffTagImageWidth_229) {
    TestableTiffComponent component(0x0100, IfdId::ifd0Id);
    EXPECT_EQ(0x0100, component.tag());
}

// Test with ExifTag (0x8769)
TEST_F(TiffComponentTest_229, ExifTag_229) {
    TestableTiffComponent component(0x8769, IfdId::ifd0Id);
    EXPECT_EQ(0x8769, component.tag());
}

// Test boundary: tag value 1
TEST_F(TiffComponentTest_229, TagValueOne_229) {
    TestableTiffComponent component(1, IfdId::ifd0Id);
    EXPECT_EQ(1, component.tag());
}

// Test boundary: tag value 0x7FFF (max signed int16)
TEST_F(TiffComponentTest_229, TagMaxSignedInt16_229) {
    TestableTiffComponent component(0x7FFF, IfdId::ifd0Id);
    EXPECT_EQ(0x7FFF, component.tag());
}

// Test boundary: tag value 0x8000 
TEST_F(TiffComponentTest_229, TagValue0x8000_229) {
    TestableTiffComponent component(0x8000, IfdId::ifd0Id);
    EXPECT_EQ(0x8000, component.tag());
}
