#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/slice.hpp"



using namespace Exiv2::Internal;



// Mocking the storage type for testing purposes

class MockStorage {

public:

    MOCK_METHOD1(unsafeAt, int&(size_t index));

};



TEST_F(MockStorageTest_7, AtReturnsCorrectReferenceForValidIndex_7) {

    MockStorage mockStorage;

    MutableSliceBase<MockStorage, int> slice;

    slice.begin_ = 0;



    EXPECT_CALL(mockStorage, unsafeAt(0)).WillOnce(testing::ReturnRef(slice.storage_.unsafeAt(0)));

    int& value = slice.at(0);

}



TEST_F(MockStorageTest_7, AtThrowsForIndexEqualToSize_7) {

    MockStorage mockStorage;

    MutableSliceBase<MockStorage, int> slice;

    slice.begin_ = 0;



    EXPECT_CALL(mockStorage, unsafeAt(1)).WillOnce(testing::Throw(std::out_of_range("index out of range")));

    EXPECT_THROW(slice.at(1), std::out_of_range);

}



TEST_F(MockStorageTest_7, AtThrowsForIndexGreaterThanSize_7) {

    MockStorage mockStorage;

    MutableSliceBase<MockStorage, int> slice;

    slice.begin_ = 0;



    EXPECT_CALL(mockStorage, unsafeAt(2)).WillOnce(testing::Throw(std::out_of_range("index out of range")));

    EXPECT_THROW(slice.at(2), std::out_of_range);

}



TEST_F(MockStorageTest_7, AtThrowsForNegativeIndexUsingWrapAround_7) {

    MockStorage mockStorage;

    MutableSliceBase<MockStorage, int> slice;

    slice.begin_ = 0;



    // Assuming size_t is unsigned and wraps around on negative index

    EXPECT_CALL(mockStorage, unsafeAt(static_cast<size_t>(-1))).WillOnce(testing::Throw(std::out_of_range("index out of range")));

    EXPECT_THROW(slice.at(-1), std::out_of_range);

}

```


