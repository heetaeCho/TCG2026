#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "crwimage_int.hpp"
#include "types.hpp"  // For DataBuf and related types

namespace Exiv2 {
namespace Internal {

class MockCiffComponent : public CiffComponent {
public:
    MOCK_METHOD(DataLocId, dataLocation, (uint16_t tag), (override));
};

class CiffComponentTest_1783 : public ::testing::Test {
protected:
    CiffComponentTest_1783() : component_(0x1234, 0x5678) {}

    CiffComponent component_;
    MockCiffComponent mock_component_;
};

// Normal Operation: Test that setValue updates the internal state
TEST_F(CiffComponentTest_1783, SetValueUpdatesInternalState_1783) {
    DataBuf buf(10);  // A non-empty buffer
    component_.setValue(std::move(buf));

    // Ensure the internal size has been updated
    ASSERT_EQ(component_.size(), 10);
    // Ensure pData_ is correctly updated to the data from the buffer
    ASSERT_NE(component_.pData(), nullptr);
}

// Boundary Case: Test with an empty DataBuf
TEST_F(CiffComponentTest_1783, SetValueWithEmptyBuffer_1783) {
    DataBuf buf(0);  // An empty buffer
    component_.setValue(std::move(buf));

    // Ensure that size is 0
    ASSERT_EQ(component_.size(), 0);
    // Ensure pData_ is still nullptr
    ASSERT_EQ(component_.pData(), nullptr);
}

// Boundary Case: Test with exactly 8-byte buffer (tag_ should not be modified)
TEST_F(CiffComponentTest_1783, SetValueWithEightByteBuffer_1783) {
    DataBuf buf(8);  // Exactly 8 bytes
    component_.setValue(std::move(buf));

    // Verify the size is updated to 8
    ASSERT_EQ(component_.size(), 8);
    // Since size is not > 8, tag_ should not change
    ASSERT_EQ(component_.tag(), 0x1234);
}

// Exceptional Case: Test behavior with a size greater than 8, and dataLocation() returns directoryData
TEST_F(CiffComponentTest_1783, SetValueWithLargeBuffer_ModifyTag_1783) {
    DataBuf buf(20);  // Size greater than 8
    EXPECT_CALL(mock_component_, dataLocation(::testing::_))
        .WillOnce(::testing::Return(DataLocId::directoryData));

    mock_component_.setValue(std::move(buf));

    // Ensure tag_ is modified (only if dataLocation() returns directoryData)
    ASSERT_EQ(mock_component_.tag(), 0x3fff);
}

// Verify the interaction between dataLocation and tag modification
TEST_F(CiffComponentTest_1783, VerifyDataLocationCall_1783) {
    DataBuf buf(15);  // Size greater than 8
    EXPECT_CALL(mock_component_, dataLocation(::testing::_))
        .WillOnce(::testing::Return(DataLocId::directoryData));

    mock_component_.setValue(std::move(buf));

    // Ensure that dataLocation was called and tag_ was modified
    ASSERT_EQ(mock_component_.tag(), 0x3fff);
}

}  // namespace Internal
}  // namespace Exiv2