#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "tiffcomposite_int.hpp"
#include "types.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;
using ::testing::_;
using ::testing::Return;

// A concrete mock subclass of TiffComponent for testing
class MockTiffComponent : public TiffComponent {
public:
    MockTiffComponent(uint16_t tag, IfdId group) : TiffComponent(tag, group) {}

    MOCK_METHOD(TiffComponent*, doAddChild, (TiffComponent::SharedPtr tiffComponent), (override));
    MOCK_METHOD(TiffComponent*, doAddNext, (TiffComponent::UniquePtr tiffComponent), (override));
    MOCK_METHOD(TiffComponent*, doAddPath, (uint16_t tag, TiffPath& tiffPath, TiffComponent* pRoot, TiffComponent::UniquePtr object), (override));
    MOCK_METHOD(void, doAccept, (TiffVisitor& visitor), (override));
    MOCK_METHOD(size_t, doWrite, (IoWrapper& ioWrapper, ByteOrder byteOrder, size_t offset, size_t valueIdx, size_t dataIdx, size_t& imageIdx), (override));
    MOCK_METHOD(size_t, doWriteData, (IoWrapper& ioWrapper, ByteOrder byteOrder, size_t offset, size_t dataIdx, size_t& imageIdx), (const, override));
    MOCK_METHOD(size_t, doWriteImage, (IoWrapper& ioWrapper, ByteOrder byteOrder), (const, override));
    MOCK_METHOD(size_t, doSize, (), (const, override));
    MOCK_METHOD(size_t, doCount, (), (const, override));
    MOCK_METHOD(size_t, doSizeData, (), (const, override));
    MOCK_METHOD(size_t, doSizeImage, (), (const, override));
};

class TiffComponentTest_325 : public ::testing::Test {
protected:
    void SetUp() override {
        component_ = std::make_unique<MockTiffComponent>(0x0100, IfdId::ifd0Id);
    }

    std::unique_ptr<MockTiffComponent> component_;
};

// Test tag() returns the tag passed to constructor
TEST_F(TiffComponentTest_325, TagReturnsConstructorValue_325) {
    MockTiffComponent comp(0x0110, IfdId::ifd0Id);
    EXPECT_EQ(comp.tag(), 0x0110);
}

// Test group() returns the group passed to constructor
TEST_F(TiffComponentTest_325, GroupReturnsConstructorValue_325) {
    MockTiffComponent comp(0x0100, IfdId::exifId);
    EXPECT_EQ(comp.group(), IfdId::exifId);
}

// Test tag with zero value
TEST_F(TiffComponentTest_325, TagZeroValue_325) {
    MockTiffComponent comp(0x0000, IfdId::ifd0Id);
    EXPECT_EQ(comp.tag(), 0x0000);
}

// Test tag with max uint16_t value
TEST_F(TiffComponentTest_325, TagMaxValue_325) {
    MockTiffComponent comp(0xFFFF, IfdId::ifd0Id);
    EXPECT_EQ(comp.tag(), 0xFFFF);
}

// Test start() returns nullptr initially
TEST_F(TiffComponentTest_325, StartInitiallyNull_325) {
    EXPECT_EQ(component_->start(), nullptr);
}

// Test setStart and start
TEST_F(TiffComponentTest_325, SetStartUpdatesStart_325) {
    byte data[] = {0x01, 0x02, 0x03};
    component_->setStart(data);
    EXPECT_EQ(component_->start(), data);
}

// Test setStart with nullptr
TEST_F(TiffComponentTest_325, SetStartWithNullptr_325) {
    component_->setStart(nullptr);
    EXPECT_EQ(component_->start(), nullptr);
}

// Test addChild delegates to doAddChild
TEST_F(TiffComponentTest_325, AddChildDelegatesToDoAddChild_325) {
    auto child = std::make_shared<MockTiffComponent>(0x0101, IfdId::ifd0Id);
    MockTiffComponent* rawChild = child.get();
    
    EXPECT_CALL(*component_, doAddChild(_))
        .WillOnce(Return(rawChild));
    
    TiffComponent* result = component_->addChild(child);
    EXPECT_EQ(result, rawChild);
}

// Test addChild with nullptr shared_ptr
TEST_F(TiffComponentTest_325, AddChildWithNullSharedPtr_325) {
    TiffComponent::SharedPtr nullChild;
    
    EXPECT_CALL(*component_, doAddChild(_))
        .WillOnce(Return(nullptr));
    
    TiffComponent* result = component_->addChild(nullChild);
    EXPECT_EQ(result, nullptr);
}

// Test addNext delegates to doAddNext
TEST_F(TiffComponentTest_325, AddNextDelegatesToDoAddNext_325) {
    auto next = std::make_unique<MockTiffComponent>(0x0102, IfdId::ifd0Id);
    MockTiffComponent* rawNext = next.get();
    
    EXPECT_CALL(*component_, doAddNext(_))
        .WillOnce(Return(rawNext));
    
    TiffComponent* result = component_->addNext(std::move(next));
    EXPECT_EQ(result, rawNext);
}

// Test addNext with nullptr
TEST_F(TiffComponentTest_325, AddNextWithNull_325) {
    EXPECT_CALL(*component_, doAddNext(_))
        .WillOnce(Return(nullptr));
    
    TiffComponent* result = component_->addNext(nullptr);
    EXPECT_EQ(result, nullptr);
}

// Test count delegates to doCount
TEST_F(TiffComponentTest_325, CountDelegatesToDoCount_325) {
    EXPECT_CALL(*component_, doCount())
        .WillOnce(Return(42));
    
    EXPECT_EQ(component_->count(), 42u);
}

// Test count returns zero
TEST_F(TiffComponentTest_325, CountReturnsZero_325) {
    EXPECT_CALL(*component_, doCount())
        .WillOnce(Return(0));
    
    EXPECT_EQ(component_->count(), 0u);
}

// Test size delegates to doSize
TEST_F(TiffComponentTest_325, SizeDelegatesToDoSize_325) {
    EXPECT_CALL(*component_, doSize())
        .WillOnce(Return(128));
    
    EXPECT_EQ(component_->size(), 128u);
}

// Test sizeData delegates to doSizeData
TEST_F(TiffComponentTest_325, SizeDataDelegatesToDoSizeData_325) {
    EXPECT_CALL(*component_, doSizeData())
        .WillOnce(Return(256));
    
    EXPECT_EQ(component_->sizeData(), 256u);
}

// Test sizeImage delegates to doSizeImage
TEST_F(TiffComponentTest_325, SizeImageDelegatesToDoSizeImage_325) {
    EXPECT_CALL(*component_, doSizeImage())
        .WillOnce(Return(1024));
    
    EXPECT_EQ(component_->sizeImage(), 1024u);
}

// Test idx returns default value
TEST_F(TiffComponentTest_325, IdxReturnsDefaultValue_325) {
    // idx() is virtual but has a default implementation in TiffComponent
    // The default should return 0
    int result = component_->idx();
    EXPECT_EQ(result, 0);
}

// Test multiple setStart calls - last one wins
TEST_F(TiffComponentTest_325, SetStartMultipleCalls_325) {
    byte data1[] = {0x01};
    byte data2[] = {0x02};
    
    component_->setStart(data1);
    EXPECT_EQ(component_->start(), data1);
    
    component_->setStart(data2);
    EXPECT_EQ(component_->start(), data2);
}

// Test that different components can have different tags and groups
TEST_F(TiffComponentTest_325, DifferentComponentsDifferentTagsAndGroups_325) {
    MockTiffComponent comp1(0x0100, IfdId::ifd0Id);
    MockTiffComponent comp2(0x0200, IfdId::exifId);
    
    EXPECT_NE(comp1.tag(), comp2.tag());
    EXPECT_NE(comp1.group(), comp2.group());
}

// Test size returns zero
TEST_F(TiffComponentTest_325, SizeReturnsZero_325) {
    EXPECT_CALL(*component_, doSize())
        .WillOnce(Return(0));
    
    EXPECT_EQ(component_->size(), 0u);
}

// Test sizeData returns zero
TEST_F(TiffComponentTest_325, SizeDataReturnsZero_325) {
    EXPECT_CALL(*component_, doSizeData())
        .WillOnce(Return(0));
    
    EXPECT_EQ(component_->sizeData(), 0u);
}

// Test sizeImage returns zero
TEST_F(TiffComponentTest_325, SizeImageReturnsZero_325) {
    EXPECT_CALL(*component_, doSizeImage())
        .WillOnce(Return(0));
    
    EXPECT_EQ(component_->sizeImage(), 0u);
}

// Test large size values
TEST_F(TiffComponentTest_325, SizeLargeValue_325) {
    size_t largeVal = static_cast<size_t>(-1);
    EXPECT_CALL(*component_, doSize())
        .WillOnce(Return(largeVal));
    
    EXPECT_EQ(component_->size(), largeVal);
}

// Test destructor is virtual (component can be destroyed through base pointer)
TEST_F(TiffComponentTest_325, VirtualDestructorWorks_325) {
    TiffComponent* base = new MockTiffComponent(0x0100, IfdId::ifd0Id);
    // Should not leak or crash
    delete base;
}
