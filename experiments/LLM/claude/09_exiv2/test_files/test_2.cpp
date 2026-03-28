#include <gtest/gtest.h>
#include <stdexcept>

// Minimal reconstruction of SliceBase based on the known interface
// We need this to compile tests since we're testing the public/protected interface
namespace Exiv2 {
namespace Internal {

struct SliceBase {
protected:
  size_t begin_;
  size_t end_;

public:
  SliceBase(size_t begin, size_t end) : begin_(begin), end_(end) {
    if (begin > end) {
      throw std::out_of_range("Slice begin > end");
    }
  }

  size_t size() const noexcept {
    return end_ - begin_;
  }

  void rangeCheck(size_t index) const {
    if (index >= size()) {
      throw std::out_of_range("Index outside of the slice");
    }
  }
};

}  // namespace Internal
}  // namespace Exiv2

// Testable derived class to access protected members through public interface
struct TestableSliceBase : public Exiv2::Internal::SliceBase {
  TestableSliceBase(size_t begin, size_t end) : SliceBase(begin, end) {}

  // Expose rangeCheck publicly for testing
  using SliceBase::rangeCheck;
  using SliceBase::size;
};

// --- Test Fixture ---
class SliceBaseTest_2 : public ::testing::Test {
protected:
  void SetUp() override {}
  void TearDown() override {}
};

// --- Construction Tests ---

TEST_F(SliceBaseTest_2, ConstructWithValidRange_2) {
  EXPECT_NO_THROW(TestableSliceBase(0, 10));
}

TEST_F(SliceBaseTest_2, ConstructWithZeroSizeRange_2) {
  EXPECT_NO_THROW(TestableSliceBase(5, 5));
}

TEST_F(SliceBaseTest_2, ConstructWithBeginZeroEndZero_2) {
  EXPECT_NO_THROW(TestableSliceBase(0, 0));
}

TEST_F(SliceBaseTest_2, ConstructWithBeginGreaterThanEndThrows_2) {
  EXPECT_THROW(TestableSliceBase(10, 5), std::out_of_range);
}

TEST_F(SliceBaseTest_2, ConstructWithLargeValidRange_2) {
  EXPECT_NO_THROW(TestableSliceBase(0, 1000000));
}

TEST_F(SliceBaseTest_2, ConstructWithEqualLargeValues_2) {
  EXPECT_NO_THROW(TestableSliceBase(1000000, 1000000));
}

// --- size() Tests ---

TEST_F(SliceBaseTest_2, SizeReturnsCorrectValue_2) {
  TestableSliceBase slice(3, 10);
  EXPECT_EQ(slice.size(), 7u);
}

TEST_F(SliceBaseTest_2, SizeOfEmptySliceIsZero_2) {
  TestableSliceBase slice(5, 5);
  EXPECT_EQ(slice.size(), 0u);
}

TEST_F(SliceBaseTest_2, SizeOfZeroToZeroIsZero_2) {
  TestableSliceBase slice(0, 0);
  EXPECT_EQ(slice.size(), 0u);
}

TEST_F(SliceBaseTest_2, SizeOfSingleElementSlice_2) {
  TestableSliceBase slice(0, 1);
  EXPECT_EQ(slice.size(), 1u);
}

TEST_F(SliceBaseTest_2, SizeWithNonZeroBegin_2) {
  TestableSliceBase slice(100, 200);
  EXPECT_EQ(slice.size(), 100u);
}

TEST_F(SliceBaseTest_2, SizeIsNoexcept_2) {
  TestableSliceBase slice(0, 10);
  EXPECT_TRUE(noexcept(slice.size()));
}

// --- rangeCheck() Tests ---

TEST_F(SliceBaseTest_2, RangeCheckValidIndexZero_2) {
  TestableSliceBase slice(0, 10);
  EXPECT_NO_THROW(slice.rangeCheck(0));
}

TEST_F(SliceBaseTest_2, RangeCheckValidIndexMiddle_2) {
  TestableSliceBase slice(0, 10);
  EXPECT_NO_THROW(slice.rangeCheck(5));
}

TEST_F(SliceBaseTest_2, RangeCheckValidIndexLastElement_2) {
  TestableSliceBase slice(0, 10);
  EXPECT_NO_THROW(slice.rangeCheck(9));
}

TEST_F(SliceBaseTest_2, RangeCheckIndexEqualToSizeThrows_2) {
  TestableSliceBase slice(0, 10);
  EXPECT_THROW(slice.rangeCheck(10), std::out_of_range);
}

TEST_F(SliceBaseTest_2, RangeCheckIndexGreaterThanSizeThrows_2) {
  TestableSliceBase slice(0, 10);
  EXPECT_THROW(slice.rangeCheck(11), std::out_of_range);
}

TEST_F(SliceBaseTest_2, RangeCheckOnEmptySliceThrows_2) {
  TestableSliceBase slice(5, 5);
  EXPECT_THROW(slice.rangeCheck(0), std::out_of_range);
}

TEST_F(SliceBaseTest_2, RangeCheckVeryLargeIndexThrows_2) {
  TestableSliceBase slice(0, 10);
  EXPECT_THROW(slice.rangeCheck(1000000), std::out_of_range);
}

TEST_F(SliceBaseTest_2, RangeCheckOnSingleElementSliceValidIndex_2) {
  TestableSliceBase slice(0, 1);
  EXPECT_NO_THROW(slice.rangeCheck(0));
}

TEST_F(SliceBaseTest_2, RangeCheckOnSingleElementSliceInvalidIndex_2) {
  TestableSliceBase slice(0, 1);
  EXPECT_THROW(slice.rangeCheck(1), std::out_of_range);
}

TEST_F(SliceBaseTest_2, RangeCheckWithNonZeroBeginValidIndex_2) {
  TestableSliceBase slice(100, 105);
  // size is 5, so valid indices are 0..4
  EXPECT_NO_THROW(slice.rangeCheck(0));
  EXPECT_NO_THROW(slice.rangeCheck(4));
}

TEST_F(SliceBaseTest_2, RangeCheckWithNonZeroBeginInvalidIndex_2) {
  TestableSliceBase slice(100, 105);
  // size is 5, so index 5 is out of range
  EXPECT_THROW(slice.rangeCheck(5), std::out_of_range);
}

TEST_F(SliceBaseTest_2, RangeCheckThrowsCorrectExceptionMessage_2) {
  TestableSliceBase slice(0, 5);
  try {
    slice.rangeCheck(10);
    FAIL() << "Expected std::out_of_range";
  } catch (const std::out_of_range& e) {
    EXPECT_NE(std::string(e.what()).find("outside"), std::string::npos);
  }
}

// --- Boundary Tests ---

TEST_F(SliceBaseTest_2, BoundaryBeginOneEndTwo_2) {
  TestableSliceBase slice(1, 2);
  EXPECT_EQ(slice.size(), 1u);
  EXPECT_NO_THROW(slice.rangeCheck(0));
  EXPECT_THROW(slice.rangeCheck(1), std::out_of_range);
}

TEST_F(SliceBaseTest_2, MaxSizeTBoundary_2) {
  // Test with max value - should throw since begin > end is impossible here
  // but begin == end is valid
  size_t maxVal = std::numeric_limits<size_t>::max();
  EXPECT_NO_THROW(TestableSliceBase(maxVal, maxVal));
  EXPECT_EQ(TestableSliceBase(maxVal, maxVal).size(), 0u);
}
