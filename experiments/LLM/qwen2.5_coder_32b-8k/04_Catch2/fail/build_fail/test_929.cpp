#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "catch_amalgamated.hpp"



using namespace Catch::Generators;

using ::testing::_;

using ::testing::Eq;



// Mock GeneratorWrapper for U type

template <typename U>

class MockGeneratorWrapper : public GeneratorWrapper<U> {

public:

    MOCK_METHOD(U, get, (), (override));

    MOCK_METHOD(bool, next, (), (override));

};



// Test fixture for MapGenerator tests

class MapGeneratorTest_929 : public ::testing::Test {

protected:

    template <typename T, typename U>

    void SetUpMapGenerator(std::function<T(const U&)> func) {

        mock_generator = std::make_unique<MockGeneratorWrapper<U>>();

        map_generator = std::make_unique<MapGenerator<T, U>>(func, CATCH_MOVE(*mock_generator));

    }



    std::unique_ptr<MockGeneratorWrapper<int>> mock_generator;

    std::unique_ptr<MapGenerator<std::string, int>> map_generator;

};



// Test normal operation

TEST_F(MapGeneratorTest_929, MapFunctionApplied_929) {

    SetUpMapGenerator<std::string, int>([](int x) { return "Number: " + std::to_string(x); });

    EXPECT_CALL(*mock_generator, get()).WillOnce(testing::Return(5));



    EXPECT_EQ(map_generator->get(), "Number: 5");

}



// Test boundary conditions

TEST_F(MapGeneratorTest_929, BoundaryCondition_Zero_929) {

    SetUpMapGenerator<std::string, int>([](int x) { return std::to_string(x); });

    EXPECT_CALL(*mock_generator, get()).WillOnce(testing::Return(0));



    EXPECT_EQ(map_generator->get(), "0");

}



// Test boundary conditions with negative numbers

TEST_F(MapGeneratorTest_929, BoundaryCondition_Negative_929) {

    SetUpMapGenerator<std::string, int>([](int x) { return std::to_string(x); });

    EXPECT_CALL(*mock_generator, get()).WillOnce(testing::Return(-1));



    EXPECT_EQ(map_generator->get(), "-1");

}



// Test next() function interaction

TEST_F(MapGeneratorTest_929, NextFunctionCalled_929) {

    SetUpMapGenerator<std::string, int>([](int x) { return std::to_string(x); });

    EXPECT_CALL(*mock_generator, get()).WillOnce(testing::Return(1)).WillOnce(testing::Return(2));

    EXPECT_CALL(*mock_generator, next()).WillOnce(testing::Return(true));



    map_generator->get();

    EXPECT_TRUE(map_generator->next());

    EXPECT_EQ(map_generator->get(), "2");

}



// Test external interactions

TEST_F(MapGeneratorTest_929, ExternalInteraction_NextReturnsFalse_929) {

    SetUpMapGenerator<std::string, int>([](int x) { return std::to_string(x); });

    EXPECT_CALL(*mock_generator, get()).WillOnce(testing::Return(1));

    EXPECT_CALL(*mock_generator, next()).WillOnce(testing::Return(false));



    map_generator->get();

    EXPECT_FALSE(map_generator->next());

}
