#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "tiffcomposite_int.hpp"

using namespace Exiv2::Internal;
using testing::Mock;

namespace {
    
// Mocking IoWrapper for testing I/O operations
class MockIoWrapper : public IoWrapper {
public:
    MOCK_METHOD(size_t, write, (const byte* buffer, size_t length), (override));
};

// Test fixture for the TiffComponent class
class TiffComponentTest : public ::testing::Test {
protected:
    TiffComponentTest() : component(1, IfdId::ExifIFD) {}

    TiffComponent component;
};

// Normal operation tests
TEST_F(TiffComponentTest, SizeReturnsCorrectValue_388) {
    EXPECT_CALL(component, doSize()).WillOnce(testing::Return(128));
    
    EXPECT_EQ(component.size(), 128);
}

TEST_F(TiffComponentTest, CountReturnsCorrectValue_389) {
    EXPECT_CALL(component, doCount()).WillOnce(testing::Return(42));
    
    EXPECT_EQ(component.count(), 42);
}

// Boundary conditions
TEST_F(TiffComponentTest, SizeReturnsZeroForEmptyComponent_390) {
    EXPECT_CALL(component, doSize()).WillOnce(testing::Return(0));
    
    EXPECT_EQ(component.size(), 0);
}

TEST_F(TiffComponentTest, CountReturnsZeroForEmptyComponent_391) {
    EXPECT_CALL(component, doCount()).WillOnce(testing::Return(0));
    
    EXPECT_EQ(component.count(), 0);
}

// Exceptional or error cases
TEST_F(TiffComponentTest, WriteThrowsErrorWhenIoWrapperFails_392) {
    MockIoWrapper mockIoWrapper;
    EXPECT_CALL(mockIoWrapper, write(testing::_, testing::_))
        .WillOnce(testing::Throw(std::runtime_error("Write failed")));

    EXPECT_THROW(component.write(mockIoWrapper, ByteOrder::BigEndian, 0, 0, 0, 0), std::runtime_error);
}

// Verification of external interactions
TEST_F(TiffComponentTest, WriteDataCallsIoWrapperWrite_393) {
    MockIoWrapper mockIoWrapper;
    EXPECT_CALL(mockIoWrapper, write(testing::_, testing::_))
        .WillOnce(testing::Return(128));

    size_t imageIdx = 0;
    EXPECT_EQ(component.writeData(mockIoWrapper, ByteOrder::BigEndian, 0, 0, imageIdx), 128);
}

TEST_F(TiffComponentTest, AddChildCallsDoAddChild_394) {
    TiffComponent::SharedPtr childComponent = std::make_shared<TiffComponent>(2, IfdId::ExifIFD);
    EXPECT_CALL(component, doAddChild(testing::_)).WillOnce(testing::Return(childComponent.get()));

    EXPECT_EQ(component.addChild(childComponent), childComponent.get());
}

TEST_F(TiffComponentTest, AddNextCallsDoAddNext_395) {
    TiffComponent::UniquePtr nextComponent = std::make_unique<TiffComponent>(3, IfdId::ExifIFD);
    EXPECT_CALL(component, doAddNext(testing::_)).WillOnce(testing::Return(nextComponent.get()));

    EXPECT_EQ(component.addNext(std::move(nextComponent)), nextComponent.get());
}

} // namespace