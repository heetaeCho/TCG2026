#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/Catch2/extras/catch_amalgamated.hpp"



using namespace Catch::Generators;

using ::testing::_;



class MockGeneratorWrapper : public GeneratorWrapper<int> {

public:

    MOCK_METHOD(int, get, (), (override));

    MOCK_METHOD(bool, next, (), (override));

};



class ChunkGeneratorTest_1110 : public ::testing::Test {

protected:

    std::unique_ptr<MockGeneratorWrapper> mock_generator;

    std::unique_ptr<ChunkGenerator<int>> chunk_generator;



    void SetUp() override {

        mock_generator = std::make_unique<MockGeneratorWrapper>();

        chunk_generator = std::make_unique<ChunkGenerator<int>>(3, *mock_generator);

    }

};



TEST_F(ChunkGeneratorTest_1110, InitialGetReturnsFirstChunk_1110) {

    EXPECT_CALL(*mock_generator, get())

        .WillOnce(testing::Return(1))

        .WillOnce(testing::Return(2))

        .WillOnce(testing::Return(3));

    EXPECT_CALL(*mock_generator, next()).WillRepeatedly(testing::Return(true));



    auto& chunk = chunk_generator->get();

    EXPECT_EQ(chunk.size(), 3);

    EXPECT_EQ(chunk[0], 1);

    EXPECT_EQ(chunk[1], 2);

    EXPECT_EQ(chunk[2], 3);

}



TEST_F(ChunkGeneratorTest_1110, NextReturnsNextChunk_1110) {

    EXPECT_CALL(*mock_generator, get())

        .WillOnce(testing::Return(1))

        .WillOnce(testing::Return(2))

        .WillOnce(testing::Return(3))

        .WillOnce(testing::Return(4))

        .WillOnce(testing::Return(5))

        .WillOnce(testing::Return(6));

    EXPECT_CALL(*mock_generator, next()).WillRepeatedly(testing::Return(true));



    chunk_generator->get(); // First chunk

    chunk_generator->next();



    auto& chunk = chunk_generator->get();

    EXPECT_EQ(chunk.size(), 3);

    EXPECT_EQ(chunk[0], 4);

    EXPECT_EQ(chunk[1], 5);

    EXPECT_EQ(chunk[2], 6);

}



TEST_F(ChunkGeneratorTest_1110, NextReturnsFalseWhenNoMoreValues_1110) {

    EXPECT_CALL(*mock_generator, get())

        .WillOnce(testing::Return(1))

        .WillOnce(testing::Return(2));

    EXPECT_CALL(*mock_generator, next())

        .WillOnce(testing::Return(true))

        .WillOnce(testing::Return(false));



    chunk_generator->get(); // First chunk

    bool result = chunk_generator->next();

    EXPECT_FALSE(result);

}



TEST_F(ChunkGeneratorTest_1110, ChunkSizeZeroDoesNotCallGet_1110) {

    mock_generator = std::make_unique<MockGeneratorWrapper>();

    chunk_generator = std::make_unique<ChunkGenerator<int>>(0, *mock_generator);



    EXPECT_CALL(*mock_generator, get()).Times(0);

    EXPECT_CALL(*mock_generator, next()).Times(0);



    auto& chunk = chunk_generator->get();

    EXPECT_EQ(chunk.size(), 0);

}



TEST_F(ChunkGeneratorTest_1110, BoundaryConditionExactMultipleOfChunkSize_1110) {

    EXPECT_CALL(*mock_generator, get())

        .WillOnce(testing::Return(1))

        .WillOnce(testing::Return(2))

        .WillOnce(testing::Return(3))

        .WillOnce(testing::Return(4))

        .WillOnce(testing::Return(5))

        .WillOnce(testing::Return(6));

    EXPECT_CALL(*mock_generator, next())

        .WillOnce(testing::Return(true))

        .WillOnce(testing::Return(true))

        .WillOnce(testing::Return(true))

        .WillOnce(testing::Return(false));



    chunk_generator->get(); // First chunk

    bool result = chunk_generator->next();

    EXPECT_TRUE(result);



    auto& chunk = chunk_generator->get();

    EXPECT_EQ(chunk.size(), 3);

    EXPECT_EQ(chunk[0], 4);

    EXPECT_EQ(chunk[1], 5);

    EXPECT_EQ(chunk[2], 6);

}



TEST_F(ChunkGeneratorTest_1110, BoundaryConditionLessThanChunkSize_1110) {

    EXPECT_CALL(*mock_generator, get())

        .WillOnce(testing::Return(1))

        .WillOnce(testing::Return(2));

    EXPECT_CALL(*mock_generator, next())

        .WillOnce(testing::Return(true))

        .WillOnce(testing::Return(false));



    chunk_generator->get(); // First chunk

    bool result = chunk_generator->next();

    EXPECT_FALSE(result);



    auto& chunk = chunk_generator->get();

    EXPECT_EQ(chunk.size(), 2);

    EXPECT_EQ(chunk[0], 1);

    EXPECT_EQ(chunk[1], 2);

}
