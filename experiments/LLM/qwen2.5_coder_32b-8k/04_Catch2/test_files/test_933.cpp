#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/Catch2/extras/catch_amalgamated.hpp"



using namespace Catch::Generators;

using ::testing::_;



class MockGenerator : public IGenerator<int> {

public:

    MOCK_METHOD(bool, next, (), (override));

    MOCK_METHOD(int, get, (), (const override));

};



TEST_F(ChunkGeneratorTest_933, NextReturnsTrueWhenUnderlyingGeneratorHasMoreElements_933) {

    auto mock_generator = std::make_unique<MockGenerator>();

    EXPECT_CALL(*mock_generator.get(), next()).WillOnce(::testing::Return(true));



    ChunkGenerator<int> chunk_gen(1, GeneratorWrapper<int>(std::move(mock_generator)));

    

    ASSERT_TRUE(chunk_gen.next());

}



TEST_F(ChunkGeneratorTest_933, NextReturnsFalseWhenUnderlyingGeneratorExhausted_933) {

    auto mock_generator = std::make_unique<MockGenerator>();

    EXPECT_CALL(*mock_generator.get(), next()).WillOnce(::testing::Return(false));



    ChunkGenerator<int> chunk_gen(1, GeneratorWrapper<int>(std::move(mock_generator)));

    

    ASSERT_FALSE(chunk_gen.next());

}



TEST_F(ChunkGeneratorTest_933, GetReturnsCorrectChunkWhenUnderlyingGeneratorHasMoreElements_933) {

    auto mock_generator = std::make_unique<MockGenerator>();

    EXPECT_CALL(*mock_generator.get(), next()).WillOnce(::testing::Return(true));

    EXPECT_CALL(*mock_generator.get(), get()).WillOnce(::testing::Return(42));



    ChunkGenerator<int> chunk_gen(1, GeneratorWrapper<int>(std::move(mock_generator)));

    

    ASSERT_TRUE(chunk_gen.next());

    const std::vector<int>& chunk = chunk_gen.get();

    ASSERT_EQ(chunk.size(), 1);

    ASSERT_EQ(chunk[0], 42);

}



TEST_F(ChunkGeneratorTest_933, GetReturnsEmptyChunkWhenUnderlyingGeneratorExhausted_933) {

    auto mock_generator = std::make_unique<MockGenerator>();

    EXPECT_CALL(*mock_generator.get(), next()).WillOnce(::testing::Return(false));



    ChunkGenerator<int> chunk_gen(1, GeneratorWrapper<int>(std::move(mock_generator)));

    

    ASSERT_FALSE(chunk_gen.next());

    const std::vector<int>& chunk = chunk_gen.get();

    ASSERT_EQ(chunk.size(), 0);

}



TEST_F(ChunkGeneratorTest_933, GetReturnsFullChunkWhenUnderlyingGeneratorHasEnoughElements_933) {

    auto mock_generator = std::make_unique<MockGenerator>();

    EXPECT_CALL(*mock_generator.get(), next()).WillRepeatedly(::testing::Return(true));

    EXPECT_CALL(*mock_generator.get(), get())

        .WillOnce(::testing::Return(1))

        .WillOnce(::testing::Return(2));



    ChunkGenerator<int> chunk_gen(2, GeneratorWrapper<int>(std::move(mock_generator)));



    ASSERT_TRUE(chunk_gen.next());

    const std::vector<int>& chunk = chunk_gen.get();

    ASSERT_EQ(chunk.size(), 2);

    ASSERT_EQ(chunk[0], 1);

    ASSERT_EQ(chunk[1], 2);

}



TEST_F(ChunkGeneratorTest_933, GetReturnsPartialChunkWhenUnderlyingGeneratorExhaustedPrematurely_933) {

    auto mock_generator = std::make_unique<MockGenerator>();

    EXPECT_CALL(*mock_generator.get(), next()).WillOnce(::testing::Return(true)).WillOnce(::testing::Return(false));

    EXPECT_CALL(*mock_generator.get(), get())

        .WillOnce(::testing::Return(1));



    ChunkGenerator<int> chunk_gen(2, GeneratorWrapper<int>(std::move(mock_generator)));



    ASSERT_TRUE(chunk_gen.next());

    const std::vector<int>& chunk = chunk_gen.get();

    ASSERT_EQ(chunk.size(), 1);

    ASSERT_EQ(chunk[0], 1);

}
