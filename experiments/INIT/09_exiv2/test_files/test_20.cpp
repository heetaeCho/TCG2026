#include <gtest/gtest.h>
#include <vector>  // For testing with containers like std::vector

namespace Exiv2 {
    template <typename T>
    struct Slice {
        T& container;
        size_t begin;
        size_t end;
    };

    template <typename T> [[nodiscard]] Slice<T> makeSlice(T& cont, size_t begin, size_t end) {
        return {cont, begin, end};
    }
}

class SliceTest_20 : public ::testing::Test {
protected:
    std::vector<int> testContainer;

    void SetUp() override {
        // Set up some default test data
        testContainer = {1, 2, 3, 4, 5, 6};
    }
};

// Normal operation test
TEST_F(SliceTest_20, MakeSlice_NormalOperation_20) {
    auto slice = Exiv2::makeSlice(testContainer, 1, 4);  // should return a slice from index 1 to 3 (inclusive)
    
    EXPECT_EQ(slice.begin, 1);
    EXPECT_EQ(slice.end, 4);
    EXPECT_EQ(slice.container[slice.begin], 2);  // container[1] = 2
    EXPECT_EQ(slice.container[slice.end - 1], 4);  // container[3] = 4
}

// Boundary condition tests
TEST_F(SliceTest_20, MakeSlice_EmptyContainer_20) {
    std::vector<int> emptyContainer;
    auto slice = Exiv2::makeSlice(emptyContainer, 0, 0);
    
    EXPECT_EQ(slice.begin, 0);
    EXPECT_EQ(slice.end, 0);
    EXPECT_TRUE(slice.container.empty());  // The container should be empty
}

TEST_F(SliceTest_20, MakeSlice_BeginEqualsEnd_20) {
    auto slice = Exiv2::makeSlice(testContainer, 2, 2);  // slice with the same begin and end
    
    EXPECT_EQ(slice.begin, 2);
    EXPECT_EQ(slice.end, 2);
    EXPECT_EQ(slice.container[slice.begin], 3);  // container[2] = 3
}

// Exceptional or error case tests
TEST_F(SliceTest_20, MakeSlice_InvalidRange_20) {
    // End is out of range
    EXPECT_THROW(Exiv2::makeSlice(testContainer, 2, 10), std::out_of_range);
    
    // Begin is greater than end
    EXPECT_THROW(Exiv2::makeSlice(testContainer, 4, 3), std::invalid_argument);
}

// Verify external interactions (mock test case example)
// Example: If there were external handlers passed into the function, we could mock them
// For now, we assume that no external dependencies are passed for the current function.