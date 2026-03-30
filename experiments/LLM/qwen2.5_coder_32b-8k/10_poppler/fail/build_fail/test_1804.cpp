#include <gtest/gtest.h>

#include <vector>



// Mocking external collaborators if needed, but in this case, we don't have any.

// We will use a template function directly for testing.



template<typename SizeType, typename ElementType>

bool sizeIsBiggerThanVectorMaxSize(SizeType size, const std::vector<ElementType> &vector);



TEST(sizeIsBiggerThanVectorMaxSizeTest_1804, NormalOperationWithSmallerSize_1804) {

    std::vector<int> vec;

    SizeType size = 10;

    EXPECT_FALSE(sizeIsBiggerThanVectorMaxSize(size, vec));

}



TEST(sizeIsBiggerThanVectorMaxSizeTest_1804, NormalOperationWithEqualSize_1804) {

    std::vector<int> vec;

    SizeType size = vec.max_size();

    EXPECT_FALSE(sizeIsBiggerThanVectorMaxSize(size, vec));

}



TEST(sizeIsBiggerThanVectorMaxSizeTest_1804, BoundaryConditionWithMaxSizePlusOne_1804) {

    std::vector<int> vec;

    SizeType size = vec.max_size() + 1;

    EXPECT_TRUE(sizeIsBiggerThanVectorMaxSize(size, vec));

}



TEST(sizeIsBiggerThanVectorMaxSizeTest_1804, ExceptionalCaseWithMaximumPossibleSize_1804) {

    std::vector<int> vec;

    SizeType size = std::numeric_limits<SizeType>::max();

    EXPECT_TRUE(sizeIsBiggerThanVectorMaxSize(size, vec));

}



TEST(sizeIsBiggerThanVectorMaxSizeTest_1804, BoundaryConditionWithZeroSize_1804) {

    std::vector<int> vec;

    SizeType size = 0;

    EXPECT_FALSE(sizeIsBiggerThanVectorMaxSize(size, vec));

}

```


