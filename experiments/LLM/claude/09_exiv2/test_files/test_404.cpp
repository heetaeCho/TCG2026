#include <gtest/gtest.h>
#include <gmock/gmock.h>

// Include necessary headers from exiv2
#include "tiffcomposite_int.hpp"
#include "tiffvisitor_int.hpp"
#include "types.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

// Concrete mock subclass of TiffComponent for testing
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

class TiffComponentTest_404 : public ::testing::Test {
protected:
    void SetUp() override {
    }
};

// Test tag() returns the tag passed in constructor
TEST_F(TiffComponentTest_404, TagReturnsConstructorValue_404) {
    MockTiffComponent comp(0x0100, IfdId::ifd0Id);
    EXPECT_EQ(comp.tag(), 0x0100);
}

// Test group() returns the group passed in constructor
TEST_F(TiffComponentTest_404, GroupReturnsConstructorValue_404) {
    MockTiffComponent comp(0x0100, IfdId::ifd0Id);
    EXPECT_EQ(comp.group(), IfdId::ifd0Id);
}

// Test tag with zero value
TEST_F(TiffComponentTest_404, TagZeroValue_404) {
    MockTiffComponent comp(0x0000, IfdId::ifd0Id);
    EXPECT_EQ(comp.tag(), 0x0000);
}

// Test tag with maximum uint16_t value
TEST_F(TiffComponentTest_404, TagMaxValue_404) {
    MockTiffComponent comp(0xFFFF, IfdId::ifd0Id);
    EXPECT_EQ(comp.tag(), 0xFFFF);
}

// Test start() returns nullptr initially
TEST_F(TiffComponentTest_404, StartInitiallyNull_404) {
    MockTiffComponent comp(0x0100, IfdId::ifd0Id);
    EXPECT_EQ(comp.start(), nullptr);
}

// Test setStart() and start() roundtrip
TEST_F(TiffComponentTest_404, SetStartAndStart_404) {
    MockTiffComponent comp(0x0100, IfdId::ifd0Id);
    byte data[] = {0x01, 0x02, 0x03};
    comp.setStart(data);
    EXPECT_EQ(comp.start(), data);
}

// Test setStart with nullptr
TEST_F(TiffComponentTest_404, SetStartNull_404) {
    MockTiffComponent comp(0x0100, IfdId::ifd0Id);
    byte data[] = {0x01};
    comp.setStart(data);
    EXPECT_EQ(comp.start(), data);
    comp.setStart(nullptr);
    EXPECT_EQ(comp.start(), nullptr);
}

// Test sizeImage delegates to doSizeImage
TEST_F(TiffComponentTest_404, SizeImageDelegatesToDoSizeImage_404) {
    MockTiffComponent comp(0x0100, IfdId::ifd0Id);
    EXPECT_CALL(comp, doSizeImage()).WillOnce(::testing::Return(42));
    EXPECT_EQ(comp.sizeImage(), 42u);
}

// Test sizeImage returns zero
TEST_F(TiffComponentTest_404, SizeImageReturnsZero_404) {
    MockTiffComponent comp(0x0100, IfdId::ifd0Id);
    EXPECT_CALL(comp, doSizeImage()).WillOnce(::testing::Return(0));
    EXPECT_EQ(comp.sizeImage(), 0u);
}

// Test size delegates to doSize
TEST_F(TiffComponentTest_404, SizeDelegatesToDoSize_404) {
    MockTiffComponent comp(0x0100, IfdId::ifd0Id);
    EXPECT_CALL(comp, doSize()).WillOnce(::testing::Return(128));
    EXPECT_EQ(comp.size(), 128u);
}

// Test count delegates to doCount
TEST_F(TiffComponentTest_404, CountDelegatesToDoCount_404) {
    MockTiffComponent comp(0x0100, IfdId::ifd0Id);
    EXPECT_CALL(comp, doCount()).WillOnce(::testing::Return(5));
    EXPECT_EQ(comp.count(), 5u);
}

// Test sizeData delegates to doSizeData
TEST_F(TiffComponentTest_404, SizeDataDelegatesToDoSizeData_404) {
    MockTiffComponent comp(0x0100, IfdId::ifd0Id);
    EXPECT_CALL(comp, doSizeData()).WillOnce(::testing::Return(256));
    EXPECT_EQ(comp.sizeData(), 256u);
}

// Test idx() returns default value
TEST_F(TiffComponentTest_404, IdxReturnsDefaultValue_404) {
    MockTiffComponent comp(0x0100, IfdId::ifd0Id);
    // idx() is virtual but has a default implementation; testing observable return
    int result = comp.idx();
    EXPECT_EQ(result, 0);
}

// Test sizeImage with large value
TEST_F(TiffComponentTest_404, SizeImageLargeValue_404) {
    MockTiffComponent comp(0x0100, IfdId::ifd0Id);
    EXPECT_CALL(comp, doSizeImage()).WillOnce(::testing::Return(static_cast<size_t>(1024 * 1024)));
    EXPECT_EQ(comp.sizeImage(), 1024u * 1024u);
}

// Test count returns zero
TEST_F(TiffComponentTest_404, CountReturnsZero_404) {
    MockTiffComponent comp(0x0100, IfdId::ifd0Id);
    EXPECT_CALL(comp, doCount()).WillOnce(::testing::Return(0));
    EXPECT_EQ(comp.count(), 0u);
}

// Test size returns zero
TEST_F(TiffComponentTest_404, SizeReturnsZero_404) {
    MockTiffComponent comp(0x0100, IfdId::ifd0Id);
    EXPECT_CALL(comp, doSize()).WillOnce(::testing::Return(0));
    EXPECT_EQ(comp.size(), 0u);
}

// Test sizeData returns zero
TEST_F(TiffComponentTest_404, SizeDataReturnsZero_404) {
    MockTiffComponent comp(0x0100, IfdId::ifd0Id);
    EXPECT_CALL(comp, doSizeData()).WillOnce(::testing::Return(0));
    EXPECT_EQ(comp.sizeData(), 0u);
}

// Test different group values
TEST_F(TiffComponentTest_404, DifferentGroupValues_404) {
    MockTiffComponent comp1(0x0100, IfdId::ifd0Id);
    MockTiffComponent comp2(0x0100, IfdId::ifd1Id);
    EXPECT_EQ(comp1.group(), IfdId::ifd0Id);
    EXPECT_EQ(comp2.group(), IfdId::ifd1Id);
    EXPECT_NE(comp1.group(), comp2.group());
}

// Test multiple calls to sizeImage
TEST_F(TiffComponentTest_404, MultipleSizeImageCalls_404) {
    MockTiffComponent comp(0x0100, IfdId::ifd0Id);
    EXPECT_CALL(comp, doSizeImage())
        .WillOnce(::testing::Return(10))
        .WillOnce(::testing::Return(20));
    EXPECT_EQ(comp.sizeImage(), 10u);
    EXPECT_EQ(comp.sizeImage(), 20u);
}

// Test setStart can be called multiple times
TEST_F(TiffComponentTest_404, SetStartMultipleTimes_404) {
    MockTiffComponent comp(0x0100, IfdId::ifd0Id);
    byte data1[] = {0x01};
    byte data2[] = {0x02};
    comp.setStart(data1);
    EXPECT_EQ(comp.start(), data1);
    comp.setStart(data2);
    EXPECT_EQ(comp.start(), data2);
}
