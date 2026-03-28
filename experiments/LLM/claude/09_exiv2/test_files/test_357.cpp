#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "tiffcomposite_int.hpp"
#include "tiffvisitor_int.hpp"
#include "types.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;
using ::testing::Return;
using ::testing::_;

// A concrete mock subclass of TiffComponent to test the public interface
class MockTiffComponent : public TiffComponent {
public:
    MockTiffComponent(uint16_t tag, IfdId group) : TiffComponent(tag, group) {}

    MOCK_METHOD(TiffComponent*, doAddPath, (uint16_t, TiffPath&, TiffComponent*, TiffComponent::UniquePtr), (override));
    MOCK_METHOD(TiffComponent*, doAddChild, (TiffComponent::SharedPtr), (override));
    MOCK_METHOD(TiffComponent*, doAddNext, (TiffComponent::UniquePtr), (override));
    MOCK_METHOD(void, doAccept, (TiffVisitor&), (override));
    MOCK_METHOD(size_t, doWrite, (IoWrapper&, ByteOrder, size_t, size_t, size_t, size_t&), (override));
    MOCK_METHOD(size_t, doWriteData, (IoWrapper&, ByteOrder, size_t, size_t, size_t&), (const, override));
    MOCK_METHOD(size_t, doWriteImage, (IoWrapper&, ByteOrder), (const, override));
    MOCK_METHOD(size_t, doSize, (), (const, override));
    MOCK_METHOD(size_t, doCount, (), (const, override));
    MOCK_METHOD(size_t, doSizeData, (), (const, override));
    MOCK_METHOD(size_t, doSizeImage, (), (const, override));
};

class TiffComponentTest_357 : public ::testing::Test {
protected:
    void SetUp() override {
    }
};

// Test that tag() returns the tag passed in the constructor
TEST_F(TiffComponentTest_357, TagReturnsConstructorValue_357) {
    MockTiffComponent comp(0x0100, IfdId::ifd0Id);
    EXPECT_EQ(comp.tag(), 0x0100);
}

// Test that group() returns the group passed in the constructor
TEST_F(TiffComponentTest_357, GroupReturnsConstructorValue_357) {
    MockTiffComponent comp(0x0100, IfdId::ifd0Id);
    EXPECT_EQ(comp.group(), IfdId::ifd0Id);
}

// Test tag with zero value
TEST_F(TiffComponentTest_357, TagZeroValue_357) {
    MockTiffComponent comp(0x0000, IfdId::ifd0Id);
    EXPECT_EQ(comp.tag(), 0x0000);
}

// Test tag with max uint16_t value
TEST_F(TiffComponentTest_357, TagMaxValue_357) {
    MockTiffComponent comp(0xFFFF, IfdId::ifd0Id);
    EXPECT_EQ(comp.tag(), 0xFFFF);
}

// Test that start() returns nullptr initially
TEST_F(TiffComponentTest_357, StartInitiallyNull_357) {
    MockTiffComponent comp(0x0100, IfdId::ifd0Id);
    EXPECT_EQ(comp.start(), nullptr);
}

// Test that setStart and start work together
TEST_F(TiffComponentTest_357, SetStartAndStart_357) {
    MockTiffComponent comp(0x0100, IfdId::ifd0Id);
    byte data[] = {0x01, 0x02, 0x03};
    comp.setStart(data);
    EXPECT_EQ(comp.start(), data);
}

// Test that setStart with nullptr works
TEST_F(TiffComponentTest_357, SetStartWithNullptr_357) {
    MockTiffComponent comp(0x0100, IfdId::ifd0Id);
    comp.setStart(nullptr);
    EXPECT_EQ(comp.start(), nullptr);
}

// Test count() delegates to doCount()
TEST_F(TiffComponentTest_357, CountDelegatesToDoCount_357) {
    MockTiffComponent comp(0x0100, IfdId::ifd0Id);
    EXPECT_CALL(comp, doCount()).WillOnce(Return(42));
    EXPECT_EQ(comp.count(), 42u);
}

// Test count() returns zero
TEST_F(TiffComponentTest_357, CountReturnsZero_357) {
    MockTiffComponent comp(0x0100, IfdId::ifd0Id);
    EXPECT_CALL(comp, doCount()).WillOnce(Return(0));
    EXPECT_EQ(comp.count(), 0u);
}

// Test count() returns large value
TEST_F(TiffComponentTest_357, CountReturnsLargeValue_357) {
    MockTiffComponent comp(0x0100, IfdId::ifd0Id);
    EXPECT_CALL(comp, doCount()).WillOnce(Return(999999));
    EXPECT_EQ(comp.count(), 999999u);
}

// Test size() delegates to doSize()
TEST_F(TiffComponentTest_357, SizeDelegatesToDoSize_357) {
    MockTiffComponent comp(0x0100, IfdId::ifd0Id);
    EXPECT_CALL(comp, doSize()).WillOnce(Return(128));
    EXPECT_EQ(comp.size(), 128u);
}

// Test size() returns zero
TEST_F(TiffComponentTest_357, SizeReturnsZero_357) {
    MockTiffComponent comp(0x0100, IfdId::ifd0Id);
    EXPECT_CALL(comp, doSize()).WillOnce(Return(0));
    EXPECT_EQ(comp.size(), 0u);
}

// Test sizeData() delegates to doSizeData()
TEST_F(TiffComponentTest_357, SizeDataDelegatesToDoSizeData_357) {
    MockTiffComponent comp(0x0100, IfdId::ifd0Id);
    EXPECT_CALL(comp, doSizeData()).WillOnce(Return(256));
    EXPECT_EQ(comp.sizeData(), 256u);
}

// Test sizeImage() delegates to doSizeImage()
TEST_F(TiffComponentTest_357, SizeImageDelegatesToDoSizeImage_357) {
    MockTiffComponent comp(0x0100, IfdId::ifd0Id);
    EXPECT_CALL(comp, doSizeImage()).WillOnce(Return(1024));
    EXPECT_EQ(comp.sizeImage(), 1024u);
}

// Test sizeImage() returns zero
TEST_F(TiffComponentTest_357, SizeImageReturnsZero_357) {
    MockTiffComponent comp(0x0100, IfdId::ifd0Id);
    EXPECT_CALL(comp, doSizeImage()).WillOnce(Return(0));
    EXPECT_EQ(comp.sizeImage(), 0u);
}

// Test idx() default returns zero
TEST_F(TiffComponentTest_357, IdxDefaultValue_357) {
    MockTiffComponent comp(0x0100, IfdId::ifd0Id);
    // idx() is virtual with a default implementation; test the default
    EXPECT_EQ(comp.idx(), 0);
}

// Test multiple calls to count() with different return values
TEST_F(TiffComponentTest_357, CountMultipleCalls_357) {
    MockTiffComponent comp(0x0100, IfdId::ifd0Id);
    EXPECT_CALL(comp, doCount())
        .WillOnce(Return(1))
        .WillOnce(Return(5))
        .WillOnce(Return(10));
    EXPECT_EQ(comp.count(), 1u);
    EXPECT_EQ(comp.count(), 5u);
    EXPECT_EQ(comp.count(), 10u);
}

// Test that different TiffComponent instances have independent state
TEST_F(TiffComponentTest_357, IndependentInstances_357) {
    MockTiffComponent comp1(0x0100, IfdId::ifd0Id);
    MockTiffComponent comp2(0x0200, IfdId::ifd1Id);

    EXPECT_EQ(comp1.tag(), 0x0100);
    EXPECT_EQ(comp2.tag(), 0x0200);
    EXPECT_EQ(comp1.group(), IfdId::ifd0Id);
    EXPECT_EQ(comp2.group(), IfdId::ifd1Id);
}

// Test setStart can be called multiple times
TEST_F(TiffComponentTest_357, SetStartMultipleTimes_357) {
    MockTiffComponent comp(0x0100, IfdId::ifd0Id);
    byte data1[] = {0x01};
    byte data2[] = {0x02};

    comp.setStart(data1);
    EXPECT_EQ(comp.start(), data1);

    comp.setStart(data2);
    EXPECT_EQ(comp.start(), data2);

    comp.setStart(nullptr);
    EXPECT_EQ(comp.start(), nullptr);
}

// Test sizeData returns zero
TEST_F(TiffComponentTest_357, SizeDataReturnsZero_357) {
    MockTiffComponent comp(0x0100, IfdId::ifd0Id);
    EXPECT_CALL(comp, doSizeData()).WillOnce(Return(0));
    EXPECT_EQ(comp.sizeData(), 0u);
}

// Test destruction does not crash (virtual destructor)
TEST_F(TiffComponentTest_357, DestructorSafety_357) {
    auto comp = std::make_unique<MockTiffComponent>(0x0100, IfdId::ifd0Id);
    // Simply ensure the destructor runs without issue
    comp.reset();
}

// Test with different IfdId groups
TEST_F(TiffComponentTest_357, DifferentGroupValues_357) {
    MockTiffComponent comp1(0x0001, IfdId::exifId);
    EXPECT_EQ(comp1.group(), IfdId::exifId);

    MockTiffComponent comp2(0x0002, IfdId::gpsId);
    EXPECT_EQ(comp2.group(), IfdId::gpsId);
}
