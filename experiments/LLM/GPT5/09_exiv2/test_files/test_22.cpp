#include <gtest/gtest.h>
#include <vector>

// Assuming Slice is a class template that holds a reference to a container, a start index, and an end index.
namespace Exiv2 {
    template <typename container>
    class Slice {
    public:
        Slice(container& cont, size_t start, size_t end)
            : container_(cont), start_(start), end_(end) {}

        size_t size() const { return end_ - start_; }

        auto begin() const { return container_.begin() + start_; }
        auto end() const { return container_.begin() + end_; }

    private:
        container& container_;
        size_t start_;
        size_t end_;
    };

    template <typename container>
    [[nodiscard]] Slice<container> makeSlice(container& cont) {
        return {cont, 0, cont.size()};
    }
}

// Unit tests
class SliceTest_22 : public ::testing::Test {
protected:
    std::vector<int> vec_ = {1, 2, 3, 4, 5};
};

TEST_F(SliceTest_22, MakeSliceNormalOperation_22) {
    // Test for normal operation, where makeSlice creates a full slice from the container
    auto slice = Exiv2::makeSlice(vec_);

    // Verify size
    EXPECT_EQ(slice.size(), 5);

    // Verify content (can be iterated over)
    std::vector<int> expected = {1, 2, 3, 4, 5};
    int idx = 0;
    for (auto val : slice) {
        EXPECT_EQ(val, expected[idx++]);
    }
}

TEST_F(SliceTest_22, SliceEmptyContainer_22) {
    // Test for empty container input
    std::vector<int> empty_vec;
    auto slice = Exiv2::makeSlice(empty_vec);

    // Verify size of slice for empty container
    EXPECT_EQ(slice.size(), 0);
}

TEST_F(SliceTest_22, SliceBoundaryConditions_22) {
    // Test boundary condition with start and end indices
    auto slice = Exiv2::Slice<std::vector<int>>(vec_, 1, 4);

    // Verify size
    EXPECT_EQ(slice.size(), 3); // Should contain elements {2, 3, 4}

    // Verify content
    std::vector<int> expected = {2, 3, 4};
    int idx = 0;
    for (auto val : slice) {
        EXPECT_EQ(val, expected[idx++]);
    }
}

TEST_F(SliceTest_22, SliceOutOfBounds_22) {
    // Test for out-of-bounds case
    EXPECT_THROW({
        auto slice = Exiv2::Slice<std::vector<int>>(vec_, 2, 10); // End index exceeds container size
    }, std::out_of_range);  // Expecting an exception (or similar error, based on your implementation)
}

TEST_F(SliceTest_22, SliceWithNegativeStart_22) {
    // Test for negative start index (invalid scenario)
    EXPECT_THROW({
        auto slice = Exiv2::Slice<std::vector<int>>(vec_, -1, 3); // Negative index is invalid
    }, std::out_of_range);  // Expecting an exception
}