#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "catch2/internal/catch_singletons.hpp"



using namespace Catch;

using ::testing::_;



class MockSingleton : public ISingleton {

public:

    MOCK_METHOD0(~MockSingleton, void());

};



TEST_F(CatchSingletonsTest_673, AddSingletonIncreasesCount_673) {

    auto initial_count = getSingletons()->size();

    MockSingleton singleton1;

    addSingleton(&singleton1);

    EXPECT_EQ(getSingletons()->size(), initial_count + 1);

}



TEST_F(CatchSingletonsTest_673, AddMultipleSingletonsIncreasesCountCorrectly_673) {

    auto initial_count = getSingletons()->size();

    MockSingleton singleton1;

    MockSingleton singleton2;

    addSingleton(&singleton1);

    addSingleton(&singleton2);

    EXPECT_EQ(getSingletons()->size(), initial_count + 2);

}



TEST_F(CatchSingletonsTest_673, AddNullptrDoesNotIncreaseCount_673) {

    auto initial_count = getSingletons()->size();

    addSingleton(nullptr);

    EXPECT_EQ(getSingletons()->size(), initial_count);

}
