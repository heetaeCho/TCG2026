#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/Catch2/extras/catch_amalgamated.hpp"



using namespace Catch::Generators;



// Mock GeneratorWrapper class for U type

template<typename U>

class MockGeneratorWrapper : public GeneratorWrapper<U> {

public:

    MOCK_METHOD(bool, next, (), (override));

    MOCK_METHOD(U const&, get, (), (const, override));

};



TEST(MapGeneratorTest_930, NextReturnsFalseWhenUnderlyingGeneratorExhausted_930) {

    MockGeneratorWrapper<int> mockGenerator;

    EXPECT_CALL(mockGenerator, next()).WillOnce(::testing::Return(false));



    MapGenerator<int, int, std::function<int(int)>> mapGen([](int x) { return x * 2; }, CATCH_MOVE(mockGenerator));

    

    ASSERT_FALSE(mapGen.next());

}



TEST(MapGeneratorTest_930, GetReturnsMappedValueAfterNextSuccess_930) {

    MockGeneratorWrapper<int> mockGenerator;

    EXPECT_CALL(mockGenerator, next()).WillOnce(::testing::Return(true)).WillRepeatedly(::testing::Return(false));

    EXPECT_CALL(mockGenerator, get()).WillOnce(::testing::Return(5));



    MapGenerator<int, int, std::function<int(int)>> mapGen([](int x) { return x * 2; }, CATCH_MOVE(mockGenerator));



    ASSERT_TRUE(mapGen.next());

    EXPECT_EQ(mapGen.get(), 10);

}



TEST(MapGeneratorTest_930, GetThrowsIfNextNotCalledFirst_930) {

    MockGeneratorWrapper<int> mockGenerator;

    MapGenerator<int, int, std::function<int(int)>> mapGen([](int x) { return x * 2; }, CATCH_MOVE(mockGenerator));



    EXPECT_THROW(mapGen.get(), std::runtime_error); // Assuming get() throws if next() hasn't been called

}



TEST(MapGeneratorTest_930, MultipleNextCallsUpdateMappedValue_930) {

    MockGeneratorWrapper<int> mockGenerator;

    EXPECT_CALL(mockGenerator, next()).WillOnce(::testing::Return(true)).WillOnce(::testing::Return(true)).WillRepeatedly(::testing::Return(false));

    EXPECT_CALL(mockGenerator, get()).WillOnce(::testing::Return(5)).WillOnce(::testing::Return(10));



    MapGenerator<int, int, std::function<int(int)>> mapGen([](int x) { return x * 2; }, CATCH_MOVE(mockGenerator));



    ASSERT_TRUE(mapGen.next());

    EXPECT_EQ(mapGen.get(), 10);



    ASSERT_TRUE(mapGen.next());

    EXPECT_EQ(mapGen.get(), 20);

}



TEST(MapGeneratorTest_930, MapFunctionIsCalledWithCorrectValue_930) {

    MockGeneratorWrapper<int> mockGenerator;

    EXPECT_CALL(mockGenerator, next()).WillOnce(::testing::Return(true)).WillRepeatedly(::testing::Return(false));

    EXPECT_CALL(mockGenerator, get()).WillOnce(::testing::Return(5));



    std::function<int(int)> mapFunc = [](int x) { return x * 2; };

    MapGenerator<int, int, std::function<int(int)>> mapGen(mapFunc, CATCH_MOVE(mockGenerator));



    ASSERT_TRUE(mapGen.next());

    EXPECT_EQ(mapGen.get(), 10);

}
