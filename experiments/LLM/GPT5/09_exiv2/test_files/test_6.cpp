#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <stdexcept>
#include <vector>

namespace Exiv2 {
namespace Internal {

// Mock class for testing
class MockConstSliceBase : public ConstSliceBase<std::vector<int>, int> {
public:
    MockConstSliceBase(std::vector<int>& data, size_t begin, size_t end)
        : ConstSliceBase<std::vector<int>, int>(data, begin, end) {}

    MOCK_METHOD(void, rangeCheck, (size_t index), (const, override));  // Mocking the rangeCheck method
};

// Test Fixture
class ConstSliceBaseTest : public ::testing::Test {
protected:
    // Sample data for testing
    std::vector<int> data = {1, 2, 3, 4, 5, 6, 7, 8, 9};
};

// TEST_ID 6 - Testing Normal operation of subSlice
TEST_F(ConstSliceBaseTest, SubSlice_NormalOperation_6) {
    MockConstSliceBase slice(data, 2, 7);

    auto sub_slice = slice.subSlice<ConstSliceBase<std::vector<int>, int>>(3, 6);
    
    ASSERT_EQ(sub_slice.size(), 3);  // Should return a slice of 3 elements
    EXPECT_EQ(sub_slice.at(0), 4);   // First element should be 4
    EXPECT_EQ(sub_slice.at(1), 5);   // Second element should be 5
    EXPECT_EQ(sub_slice.at(2), 6);   // Third element should be 6
}

// TEST_ID 7 - Testing Boundary condition when begin == end
TEST_F(ConstSliceBaseTest, SubSlice_BoundaryCondition_7) {
    MockConstSliceBase slice(data, 2, 7);

    auto sub_slice = slice.subSlice<ConstSliceBase<std::vector<int>, int>>(4, 4);
    
    ASSERT_EQ(sub_slice.size(), 0);  // Should return an empty slice
}

// TEST_ID 8 - Testing Exception when out-of-bounds access is made
TEST_F(ConstSliceBaseTest, SubSlice_OutOfBounds_8) {
    MockConstSliceBase slice(data, 2, 7);

    EXPECT_THROW(slice.subSlice<ConstSliceBase<std::vector<int>, int>>(6, 9), std::out_of_range);
}

// TEST_ID 9 - Verifying external interactions with rangeCheck method
TEST_F(ConstSliceBaseTest, SubSlice_VerifyRangeCheck_9) {
    MockConstSliceBase slice(data, 2, 7);

    // Expect rangeCheck to be called twice (once for each bound)
    EXPECT_CALL(slice, rangeCheck(2)).Times(1);  // rangeCheck for begin
    EXPECT_CALL(slice, rangeCheck(6)).Times(1);  // rangeCheck for end
    
    slice.subSlice<ConstSliceBase<std::vector<int>, int>>(3, 6);
}

// TEST_ID 10 - Testing normal operation with a different set of data type
TEST_F(ConstSliceBaseTest, SubSlice_DifferentDataType_10) {
    std::vector<double> double_data = {1.1, 2.2, 3.3, 4.4, 5.5};
    MockConstSliceBase slice(double_data, 1, 4);

    auto sub_slice = slice.subSlice<ConstSliceBase<std::vector<double>, double>>(2, 4);
    
    ASSERT_EQ(sub_slice.size(), 2);  // Should return a slice of 2 elements
    EXPECT_EQ(sub_slice.at(0), 3.3); // First element should be 3.3
    EXPECT_EQ(sub_slice.at(1), 4.4); // Second element should be 4.4
}

}  // namespace Internal
}  // namespace Exiv2