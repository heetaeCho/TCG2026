#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "exiv2/slice.hpp"  // Include the header file for ConstSliceBase class

namespace Exiv2 {
namespace Internal {

// Mock class to simulate external interaction with `storage_`
template <typename T>
class MockStorage {
public:
    MOCK_METHOD(const T&, unsafeAt, (size_t), (const));
};

}  // namespace Internal
}  // namespace Exiv2

// Unit Test Class
class ConstSliceBaseTest : public ::testing::Test {
protected:
    // Set up common test data
    Exiv2::Internal::MockStorage<int> mockStorage;
    Exiv2::Internal::ConstSliceBase<int, int> slice;

    void SetUp() override {
        // Example setup logic (this might vary depending on constructor)
        slice = Exiv2::Internal::ConstSliceBase<int, int>(mockStorage, 0, 5);
    }
};

// Test normal operation
TEST_F(ConstSliceBaseTest, At_ReturnsCorrectElement) {
    size_t index = 2;
    int expected = 42;

    // Mock the behavior of `unsafeAt` for this test
    EXPECT_CALL(mockStorage, unsafeAt(index)).WillOnce(testing::ReturnRef(expected));

    // Test the `at` function and verify its output
    const auto& result = slice.at(index);
    EXPECT_EQ(result, expected);
    EXPECT_CALL(mockStorage, unsafeAt(index)).Times(1);  // Verify that `unsafeAt` is called once
}

// Test boundary condition: Accessing first element
TEST_F(ConstSliceBaseTest, At_FirstElement) {
    size_t index = 0;
    int expected = 10;

    // Mock the behavior of `unsafeAt` for this test
    EXPECT_CALL(mockStorage, unsafeAt(index)).WillOnce(testing::ReturnRef(expected));

    const auto& result = slice.at(index);
    EXPECT_EQ(result, expected);
}

// Test boundary condition: Accessing last element
TEST_F(ConstSliceBaseTest, At_LastElement) {
    size_t index = 4;
    int expected = 99;

    // Mock the behavior of `unsafeAt` for this test
    EXPECT_CALL(mockStorage, unsafeAt(index)).WillOnce(testing::ReturnRef(expected));

    const auto& result = slice.at(index);
    EXPECT_EQ(result, expected);
}

// Test exceptional case: Out of bounds index
TEST_F(ConstSliceBaseTest, At_OutOfBounds) {
    size_t index = 10; // Invalid index beyond the slice range

    // Set expectation for rangeCheck to throw an exception
    EXPECT_THROW(slice.at(index), std::out_of_range);
}

// Test subSlice behavior
TEST_F(ConstSliceBaseTest, SubSlice_CreatesCorrectSubSlice) {
    size_t subBegin = 1;
    size_t subEnd = 3;

    // Mocking subSlice, assuming it returns a new subSlice object
    EXPECT_CALL(mockStorage, unsafeAt(testing::_)).Times(testing::AtLeast(1));

    auto subSlice = slice.subSlice<int>(subBegin, subEnd);
    // Verify that the subSlice is created properly (this could be further validated based on actual behavior)
    EXPECT_EQ(subSlice.size(), subEnd - subBegin);
}

// Test that the `rangeCheck` method works correctly (testing internal logic)
TEST_F(ConstSliceBaseTest, RangeCheck_ValidIndex) {
    size_t validIndex = 1;
    EXPECT_NO_THROW(slice.rangeCheck(validIndex));
}

// Test exceptional case: Range check with invalid index
TEST_F(ConstSliceBaseTest, RangeCheck_InvalidIndex) {
    size_t invalidIndex = 10; // Assuming the slice is from 0 to 5
    EXPECT_THROW(slice.rangeCheck(invalidIndex), std::out_of_range);
}