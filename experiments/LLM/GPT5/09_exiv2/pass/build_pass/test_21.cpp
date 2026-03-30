#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "exiv2/slice.hpp"

// Mock class for external dependencies (if any)
class MockHandler {
public:
    MOCK_METHOD(void, handle, (int), ());
};

// Test fixture
class SliceTest_21 : public ::testing::Test {
protected:
    void SetUp() override {
        // Set up any needed resources before each test
    }

    void TearDown() override {
        // Clean up any resources after each test
    }
};

// Normal operation tests
TEST_F(SliceTest_21, MakeSlice_CreatesValidSlice_21) {
    int data[] = {1, 2, 3, 4, 5};
    auto slice = Exiv2::makeSlice(data, 1, 4);

    // Verify slice properties
    EXPECT_EQ(slice.begin(), data + 1);
    EXPECT_EQ(slice.end(), data + 4);
    EXPECT_EQ(slice.size(), 3);  // end - begin
}

TEST_F(SliceTest_21, MakeSlice_WithEmptyRange_21) {
    int data[] = {1, 2, 3, 4, 5};
    auto slice = Exiv2::makeSlice(data, 3, 3);

    // Verify slice is empty
    EXPECT_EQ(slice.size(), 0);
    EXPECT_EQ(slice.begin(), data + 3);
    EXPECT_EQ(slice.end(), data + 3);
}

// Boundary condition tests
TEST_F(SliceTest_21, MakeSlice_WithFullRange_21) {
    int data[] = {1, 2, 3, 4, 5};
    auto slice = Exiv2::makeSlice(data, 0, 5);

    // Verify slice covers the entire array
    EXPECT_EQ(slice.size(), 5);
    EXPECT_EQ(slice.begin(), data);
    EXPECT_EQ(slice.end(), data + 5);
}

TEST_F(SliceTest_21, MakeSlice_WithZeroLengthRange_21) {
    int data[] = {1, 2, 3, 4, 5};
    auto slice = Exiv2::makeSlice(data, 4, 4);

    // Verify slice is valid but empty
    EXPECT_EQ(slice.size(), 0);
    EXPECT_EQ(slice.begin(), data + 4);
    EXPECT_EQ(slice.end(), data + 4);
}

// Exceptional cases
TEST_F(SliceTest_21, MakeSlice_OutOfBoundsStart_21) {
    int data[] = {1, 2, 3, 4, 5};

    // Start index beyond array size (should not compile or should throw an exception)
    EXPECT_THROW({
        auto slice = Exiv2::makeSlice(data, 6, 5);
    }, std::out_of_range);
}

TEST_F(SliceTest_21, MakeSlice_EndBeforeStart_21) {
    int data[] = {1, 2, 3, 4, 5};

    // End index smaller than start index (should not compile or should throw an exception)
    EXPECT_THROW({
        auto slice = Exiv2::makeSlice(data, 3, 2);
    }, std::invalid_argument);
}

// Mock external interaction test
TEST_F(SliceTest_21, MockHandler_VerifiesInteraction_21) {
    MockHandler mockHandler;

    // Mocking behavior (this example assumes there might be external handler)
    EXPECT_CALL(mockHandler, handle(3))
        .Times(1);

    // Trigger interaction (in reality, we would call a function that triggers `handle`)
    mockHandler.handle(3);
}