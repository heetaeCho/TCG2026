#include <gtest/gtest.h>
#include <gmock/gmock.h>

// Include necessary headers from the project
#include "tiffcomposite_int.hpp"
#include "types.hpp"

namespace Exiv2 {
namespace Internal {

// A concrete mock/test subclass of TiffComponent to allow instantiation
// and testing of the public interface via the virtual dispatch mechanism.
class MockTiffComponent : public TiffComponent {
public:
    MockTiffComponent(uint16_t tag, IfdId group) : TiffComponent(tag, group) {}

    // Mock the protected virtual methods
    MOCK_METHOD(TiffComponent*, doAddPath,
                (uint16_t tag, TiffPath& tiffPath, TiffComponent* pRoot, UniquePtr object),
                (override));
    MOCK_METHOD(TiffComponent*, doAddChild, (SharedPtr tiffComponent), (override));
    MOCK_METHOD(TiffComponent*, doAddNext, (UniquePtr tiffComponent), (override));
    MOCK_METHOD(void, doAccept, (TiffVisitor & visitor), (override));
    MOCK_METHOD(size_t, doWrite,
                (IoWrapper & ioWrapper, ByteOrder byteOrder, size_t offset, size_t valueIdx,
                 size_t dataIdx, size_t& imageIdx),
                (override));
    MOCK_METHOD(size_t, doWriteData,
                (IoWrapper & ioWrapper, ByteOrder byteOrder, size_t offset, size_t dataIdx,
                 size_t& imageIdx),
                (const, override));
    MOCK_METHOD(size_t, doWriteImage, (IoWrapper & ioWrapper, ByteOrder byteOrder),
                (const, override));
    MOCK_METHOD(size_t, doSize, (), (const, override));
    MOCK_METHOD(size_t, doCount, (), (const, override));
    MOCK_METHOD(size_t, doSizeData, (), (const, override));
    MOCK_METHOD(size_t, doSizeImage, (), (const, override));
};

// Test fixture
class TiffComponentTest_318 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that tag() returns the tag set in the constructor
TEST_F(TiffComponentTest_318, TagReturnsConstructorValue_318) {
    MockTiffComponent comp(0x0100, IfdId::ifd0Id);
    EXPECT_EQ(comp.tag(), 0x0100);
}

// Test that group() returns the group set in the constructor
TEST_F(TiffComponentTest_318, GroupReturnsConstructorValue_318) {
    MockTiffComponent comp(0x0100, IfdId::ifd0Id);
    EXPECT_EQ(comp.group(), IfdId::ifd0Id);
}

// Test tag with zero value
TEST_F(TiffComponentTest_318, TagZero_318) {
    MockTiffComponent comp(0x0000, IfdId::ifd0Id);
    EXPECT_EQ(comp.tag(), 0x0000);
}

// Test tag with maximum uint16_t value
TEST_F(TiffComponentTest_318, TagMaxValue_318) {
    MockTiffComponent comp(0xFFFF, IfdId::ifd0Id);
    EXPECT_EQ(comp.tag(), 0xFFFF);
}

// Test that start() returns nullptr initially
TEST_F(TiffComponentTest_318, StartInitiallyNull_318) {
    MockTiffComponent comp(0x0100, IfdId::ifd0Id);
    EXPECT_EQ(comp.start(), nullptr);
}

// Test setStart and start
TEST_F(TiffComponentTest_318, SetStartAndGetStart_318) {
    MockTiffComponent comp(0x0100, IfdId::ifd0Id);
    byte data[] = {0x01, 0x02, 0x03};
    comp.setStart(data);
    EXPECT_EQ(comp.start(), data);
}

// Test setStart with nullptr
TEST_F(TiffComponentTest_318, SetStartNullptr_318) {
    MockTiffComponent comp(0x0100, IfdId::ifd0Id);
    byte data[] = {0x01};
    comp.setStart(data);
    EXPECT_EQ(comp.start(), data);
    comp.setStart(nullptr);
    EXPECT_EQ(comp.start(), nullptr);
}

// Test that count() delegates to doCount()
TEST_F(TiffComponentTest_318, CountDelegatesToDoCount_318) {
    MockTiffComponent comp(0x0100, IfdId::ifd0Id);
    EXPECT_CALL(comp, doCount()).WillOnce(::testing::Return(42));
    EXPECT_EQ(comp.count(), 42u);
}

// Test that size() delegates to doSize()
TEST_F(TiffComponentTest_318, SizeDelegatesToDoSize_318) {
    MockTiffComponent comp(0x0100, IfdId::ifd0Id);
    EXPECT_CALL(comp, doSize()).WillOnce(::testing::Return(128));
    EXPECT_EQ(comp.size(), 128u);
}

// Test that sizeData() delegates to doSizeData()
TEST_F(TiffComponentTest_318, SizeDataDelegatesToDoSizeData_318) {
    MockTiffComponent comp(0x0100, IfdId::ifd0Id);
    EXPECT_CALL(comp, doSizeData()).WillOnce(::testing::Return(256));
    EXPECT_EQ(comp.sizeData(), 256u);
}

// Test that sizeImage() delegates to doSizeImage()
TEST_F(TiffComponentTest_318, SizeImageDelegatesToDoSizeImage_318) {
    MockTiffComponent comp(0x0100, IfdId::ifd0Id);
    EXPECT_CALL(comp, doSizeImage()).WillOnce(::testing::Return(1024));
    EXPECT_EQ(comp.sizeImage(), 1024u);
}

// Test that count() returns zero when doCount returns zero
TEST_F(TiffComponentTest_318, CountReturnsZero_318) {
    MockTiffComponent comp(0x0100, IfdId::ifd0Id);
    EXPECT_CALL(comp, doCount()).WillOnce(::testing::Return(0));
    EXPECT_EQ(comp.count(), 0u);
}

// Test that size() returns zero when doSize returns zero
TEST_F(TiffComponentTest_318, SizeReturnsZero_318) {
    MockTiffComponent comp(0x0100, IfdId::ifd0Id);
    EXPECT_CALL(comp, doSize()).WillOnce(::testing::Return(0));
    EXPECT_EQ(comp.size(), 0u);
}

// Test different group values
TEST_F(TiffComponentTest_318, DifferentGroupValues_318) {
    MockTiffComponent comp1(0x0100, IfdId::ifd1Id);
    EXPECT_EQ(comp1.group(), IfdId::ifd1Id);

    MockTiffComponent comp2(0x0100, IfdId::exifId);
    EXPECT_EQ(comp2.group(), IfdId::exifId);
}

// Test that addPath delegates to doAddPath
TEST_F(TiffComponentTest_318, AddPathDelegatesToDoAddPath_318) {
    MockTiffComponent comp(0x0100, IfdId::ifd0Id);
    TiffPath tiffPath;

    EXPECT_CALL(comp, doAddPath(::testing::_, ::testing::Ref(tiffPath), ::testing::_, ::testing::_))
        .WillOnce(::testing::Return(&comp));

    TiffComponent::UniquePtr obj;
    TiffComponent* result = comp.addPath(0x0100, tiffPath, &comp, std::move(obj));
    EXPECT_EQ(result, &comp);
}

// Test that addPath returns nullptr when doAddPath returns nullptr
TEST_F(TiffComponentTest_318, AddPathReturnsNull_318) {
    MockTiffComponent comp(0x0100, IfdId::ifd0Id);
    TiffPath tiffPath;

    EXPECT_CALL(comp, doAddPath(::testing::_, ::testing::_, ::testing::_, ::testing::_))
        .WillOnce(::testing::Return(nullptr));

    TiffComponent::UniquePtr obj;
    TiffComponent* result = comp.addPath(0x0100, tiffPath, nullptr, std::move(obj));
    EXPECT_EQ(result, nullptr);
}

// Test multiple setStart calls - last one wins
TEST_F(TiffComponentTest_318, SetStartOverwrites_318) {
    MockTiffComponent comp(0x0100, IfdId::ifd0Id);
    byte data1[] = {0x01};
    byte data2[] = {0x02};
    comp.setStart(data1);
    EXPECT_EQ(comp.start(), data1);
    comp.setStart(data2);
    EXPECT_EQ(comp.start(), data2);
}

}  // namespace Internal
}  // namespace Exiv2
