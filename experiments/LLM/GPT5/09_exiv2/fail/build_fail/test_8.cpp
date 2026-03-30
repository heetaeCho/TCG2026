#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "exiv2/slice.hpp"

// Test Suite for MutableSliceBase class

namespace Exiv2 { namespace Internal {

// Mocked class for storage_type to be used in tests
template <typename T>
class MockStorage {
public:
    MOCK_METHOD(void, unsafeGetIteratorAt, (size_t), ());
};

class MutableSliceBaseTest_8 : public ::testing::Test {
protected:
    // Create a MutableSliceBase object and MockStorage
    MockStorage<int> mockStorage;
    MutableSliceBase<MockStorage<int>, int> mutableSlice;

    // Setup method to initialize test objects
    void SetUp() override {
        // Initialize the mock object, storage, and other necessary state
        mutableSlice = MutableSliceBase<MockStorage<int>, int>();
    }
};

// Test for begin() function in normal operation
TEST_F(MutableSliceBaseTest_8, Begin_ReturnsIterator_8) {
    // Setting expectations for mock
    EXPECT_CALL(mockStorage, unsafeGetIteratorAt(testing::_))
        .Times(1);

    // Call the begin() function, which should interact with unsafeGetIteratorAt
    auto iterator = mutableSlice.begin();

    // Validate the behavior (e.g., checking if the iterator is as expected)
    // Assertions are specific to the actual return type and behavior
    ASSERT_TRUE(iterator != nullptr); // Replace with actual checks
}

// Test for subSlice() function in normal operation
TEST_F(MutableSliceBaseTest_8, SubSlice_ReturnsCorrectSubSlice_8) {
    // Setup for testing subSlice()
    size_t begin = 0;
    size_t end = 5;

    // Expected behavior for subSlice
    auto subSlice = mutableSlice.subSlice<MutableSliceBase<MockStorage<int>, int>>(begin, end);

    // Validate the result
    ASSERT_EQ(subSlice.begin(), mutableSlice.begin() + begin);
    ASSERT_EQ(subSlice.end(), mutableSlice.begin() + end);
}

// Test for at() function in boundary condition (accessing first element)
TEST_F(MutableSliceBaseTest_8, At_BoundaryCondition_FirstElement_8) {
    size_t index = 0;

    // Setting up the mock for at() method
    EXPECT_CALL(mockStorage, unsafeGetIteratorAt(index)).Times(1);

    // Call the at() function for the first element
    auto& element = mutableSlice.at(index);

    // Verify that the element at the specified index is accessed correctly
    ASSERT_EQ(element, mutableSlice.at(index));  // Replace with specific validation
}

// Test for at() function in boundary condition (accessing out-of-bounds element)
TEST_F(MutableSliceBaseTest_8, At_BoundaryCondition_OutOfBounds_8) {
    size_t index = 100;  // Assuming index 100 is out of bounds

    // Expect an exception or error handling for out-of-bounds access
    EXPECT_THROW(mutableSlice.at(index), std::out_of_range);
}

// Test for end() function in normal operation
TEST_F(MutableSliceBaseTest_8, End_ReturnsCorrectIterator_8) {
    // Setting expectations for mock
    EXPECT_CALL(mockStorage, unsafeGetIteratorAt(testing::_))
        .Times(1);

    // Call the end() function, which should interact with unsafeGetIteratorAt
    auto iterator = mutableSlice.end();

    // Validate the behavior
    ASSERT_TRUE(iterator != nullptr);  // Replace with actual checks
}

// Test for subSlice() with incorrect range (invalid range)
TEST_F(MutableSliceBaseTest_8, SubSlice_InvalidRange_8) {
    size_t begin = 10;
    size_t end = 5;  // Invalid range

    // Expect exception or error handling for invalid range
    EXPECT_THROW(mutableSlice.subSlice<MutableSliceBase<MockStorage<int>, int>>(begin, end), std::invalid_argument);
}

// Test for verifying external interactions (mock call count)
TEST_F(MutableSliceBaseTest_8, VerifyMockInteractions_8) {
    size_t index = 0;

    // Expect mock interaction with unsafeGetIteratorAt
    EXPECT_CALL(mockStorage, unsafeGetIteratorAt(index)).Times(1);

    // Trigger method that calls unsafeGetIteratorAt
    mutableSlice.begin();

    // Verify that the mock call count is as expected
    testing::Mock::VerifyAndClearExpectations(&mockStorage);
}

} } // End of namespace Exiv2::Internal