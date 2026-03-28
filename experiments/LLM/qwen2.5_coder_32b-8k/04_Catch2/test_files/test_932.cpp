#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "catch_amalgamated.hpp"



using namespace Catch::Generators;

using ::testing::Return;



class ChunkGeneratorTest_932 : public ::testing::Test {

protected:

    std::vector<int> sampleData = {1, 2, 3, 4, 5};

    GeneratorWrapper<int> generator = Generators::Fixed(sampleData.begin(), sampleData.end());

    size_t chunkSize = 2;

    ChunkGenerator<int> chunkGen = ChunkGenerator<int>(chunkSize, CATCH_MOVE(generator));

};



TEST_F(ChunkGeneratorTest_932, GetReturnsCorrectChunk_932) {

    EXPECT_EQ(chunkGen.get(), std::vector<int>({1, 2}));

}



TEST_F(ChunkGeneratorTest_932, NextAdvancesToNextChunk_932) {

    chunkGen.next();

    EXPECT_EQ(chunkGen.get(), std::vector<int>({3, 4}));

}



TEST_F(ChunkGeneratorTest_932, LastChunkContainsRemainingElements_932) {

    chunkGen.next();

    chunkGen.next();

    EXPECT_EQ(chunkGen.get(), std::vector<int>({5}));

}



TEST_F(ChunkGeneratorTest_932, NextReturnsFalseWhenExhausted_932) {

    chunkGen.next();

    chunkGen.next();

    chunkGen.next(); // Move to the end

    EXPECT_FALSE(chunkGen.next());

}



TEST_F(ChunkGeneratorTest_932, GetOnExhaustedGeneratorReturnsLastChunk_932) {

    chunkGen.next();

    chunkGen.next();

    chunkGen.next(); // Move to the end

    EXPECT_EQ(chunkGen.get(), std::vector<int>({5}));

}
