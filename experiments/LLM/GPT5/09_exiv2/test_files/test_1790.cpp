#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "crwimage_int.hpp"

// Mock CrwDirs class for external dependency
class MockCrwDirs : public Exiv2::Internal::CrwDirs {
public:
    MOCK_METHOD(void, someMethod, (), (override)); // Mock methods if necessary
};

// Test class for CiffComponent
class CiffComponentTest_1790 : public ::testing::Test {
protected:
    Exiv2::Internal::CiffComponent component_1{123, 456};  // Test component with tag=123, dir=456
    Exiv2::Internal::CiffComponent component_2{789, 101};  // Another component for comparison
};

// Test for add method with UniquePtr
TEST_F(CiffComponentTest_1790, AddComponent_1790) {
    Exiv2::Internal::CiffComponent::UniquePtr newComponent = std::make_unique<Exiv2::Internal::CiffComponent>(987, 654);

    // Expect the call to doAdd when add is called
    EXPECT_CALL(component_1, doAdd(::testing::_)).WillOnce(::testing::ReturnRef(newComponent));

    // Call the method
    auto result = component_1.add(std::move(newComponent));

    // Verify that the result is as expected
    EXPECT_EQ(result.get(), newComponent.get());
}

// Test for add method with CrwDirs and crwTagId
TEST_F(CiffComponentTest_1790, AddCrwDirs_1790) {
    MockCrwDirs crwDirsMock;
    uint16_t crwTagId = 567;

    // Expect the call to doAdd for CrwDirs version of add
    Exiv2::Internal::CiffComponent::UniquePtr newComponent = std::make_unique<Exiv2::Internal::CiffComponent>(567, 890);
    EXPECT_CALL(component_1, doAdd(::testing::Ref(crwDirsMock), crwTagId))
        .WillOnce(::testing::ReturnRef(newComponent));

    // Call the method
    auto result = component_1.add(crwDirsMock, crwTagId);

    // Verify the result
    EXPECT_EQ(result.get(), newComponent.get());
}

// Test for remove method
TEST_F(CiffComponentTest_1790, RemoveComponent_1790) {
    MockCrwDirs crwDirsMock;
    uint16_t crwTagId = 123;

    // Expect the call to doRemove when remove is called
    EXPECT_CALL(component_1, doRemove(::testing::Ref(crwDirsMock), crwTagId))
        .Times(1);

    // Call the method
    component_1.remove(crwDirsMock, crwTagId);
}

// Test for read method
TEST_F(CiffComponentTest_1790, ReadComponent_1790) {
    const uint8_t data[] = { 1, 2, 3, 4 };
    size_t size = sizeof(data);
    uint32_t start = 0;
    Exiv2::ByteOrder byteOrder = Exiv2::BigEndian;

    // Expect the call to doRead when read is called
    EXPECT_CALL(component_1, doRead(::testing::_, size, start, byteOrder))
        .Times(1);

    // Call the method
    component_1.read(data, size, start, byteOrder);
}

// Test for write method
TEST_F(CiffComponentTest_1790, WriteComponent_1790) {
    Exiv2::Blob blob;
    Exiv2::ByteOrder byteOrder = Exiv2::BigEndian;
    size_t offset = 0;

    // Expect the call to doWrite when write is called
    EXPECT_CALL(component_1, doWrite(::testing::Ref(blob), byteOrder, offset))
        .Times(1)
        .WillOnce(::testing::Return(10));  // Return a size of 10

    // Call the method
    size_t result = component_1.write(blob, byteOrder, offset);

    // Verify the result
    EXPECT_EQ(result, 10);
}

// Test for empty method
TEST_F(CiffComponentTest_1790, EmptyComponent_1790) {
    // Expect the call to doEmpty when empty is called
    EXPECT_CALL(component_1, doEmpty())
        .Times(1)
        .WillOnce(::testing::Return(true));  // Return true for empty

    // Call the method
    bool result = component_1.empty();

    // Verify the result
    EXPECT_TRUE(result);
}

// Test for findComponent method
TEST_F(CiffComponentTest_1790, FindComponent_1790) {
    uint16_t crwTagId = 123;
    uint16_t crwDir = 456;

    // Expect the call to doFindComponent when findComponent is called
    Exiv2::Internal::CiffComponent* foundComponent = &component_1;
    EXPECT_CALL(component_1, doFindComponent(crwTagId, crwDir))
        .WillOnce(::testing::Return(foundComponent));

    // Call the method
    Exiv2::Internal::CiffComponent* result = component_1.findComponent(crwTagId, crwDir);

    // Verify the result
    EXPECT_EQ(result, foundComponent);
}

// Exceptional case for empty component
TEST_F(CiffComponentTest_1790, FindComponent_NotFound_1790) {
    uint16_t crwTagId = 999;
    uint16_t crwDir = 888;

    // Expect the call to doFindComponent and return nullptr
    EXPECT_CALL(component_1, doFindComponent(crwTagId, crwDir))
        .WillOnce(::testing::Return(nullptr));

    // Call the method
    Exiv2::Internal::CiffComponent* result = component_1.findComponent(crwTagId, crwDir);

    // Verify that no component is found
    EXPECT_EQ(result, nullptr);
}