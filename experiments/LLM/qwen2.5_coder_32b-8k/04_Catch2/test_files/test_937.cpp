#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/Catch2/extras/catch_amalgamated.hpp"



using namespace Catch::Generators;

using ::testing::_;



// Assuming there is a class that uses the range generator from Catch, let's create a mock for testing purposes.

class MockRangeUser {

public:

    MOCK_METHOD(void, UseRange, (GeneratorWrapper<int>), ());

};



TEST_F(MockRangeUserTest_937, RangeWithPositiveStep_937) {

    MockRangeUser mock;

    EXPECT_CALL(mock, UseRange(_)).Times(1);



    auto gen = range(0, 5, 1);

    mock.UseRange(gen);

}



TEST_F(MockRangeUserTest_937, RangeWithNegativeStep_937) {

    MockRangeUser mock;

    EXPECT_CALL(mock, UseRange(_)).Times(1);



    auto gen = range(5, 0, -1);

    mock.UseRange(gen);

}



TEST_F(MockRangeUserTest_937, RangeWithZeroStepThrows_937) {

    MockRangeUser mock;



    EXPECT_THROW(range(0, 5, 0), std::logic_error);

}



TEST_F(MockRangeUserTest_937, RangeStartEqualsEnd_937) {

    MockRangeUser mock;

    EXPECT_CALL(mock, UseRange(_)).Times(1);



    auto gen = range(5, 5, 1);

    mock.UseRange(gen);

}



TEST_F(MockRangeUserTest_937, RangeSingleElement_937) {

    MockRangeUser mock;

    EXPECT_CALL(mock, UseRange(_)).Times(1);



    auto gen = range(0, 1, 1);

    mock.UseRange(gen);

}

```


