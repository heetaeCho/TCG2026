#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/Catch2/extras/catch_amalgamated.hpp"



using namespace Catch::Generators;

using ::testing::Eq;



class RepeatGeneratorTest_927 : public testing::Test {

protected:

    std::vector<int> data = {1, 2, 3};

    GeneratorWrapper<int> generator = Generators::Fixed(data.begin(), data.end());

};



TEST_F(RepeatGeneratorTest_927, Next_ReturnsTrueForFirstElement_927) {

    RepeatGenerator<int> repeatGen(1, CATCH_MOVE(generator));

    EXPECT_TRUE(repeatGen.next());

}



TEST_F(RepeatGeneratorTest_927, Get_ReturnsCorrectValueAfterNext_927) {

    RepeatGenerator<int> repeatGen(1, CATCH_MOVE(generator));

    repeatGen.next();

    EXPECT_EQ(repeatGen.get(), 1);

}



TEST_F(RepeatGeneratorTest_927, Next_IteratesThroughAllElementsOnce_927) {

    RepeatGenerator<int> repeatGen(1, CATCH_MOVE(generator));

    for (int i = 0; i < data.size(); ++i) {

        EXPECT_TRUE(repeatGen.next());

        EXPECT_EQ(repeatGen.get(), data[i]);

    }

    EXPECT_FALSE(repeatGen.next());

}



TEST_F(RepeatGeneratorTest_927, Next_ReturnsTrueForRepeatedElements_927) {

    RepeatGenerator<int> repeatGen(3, CATCH_MOVE(generator));

    for (int i = 0; i < data.size() * 3; ++i) {

        EXPECT_TRUE(repeatGen.next());

    }

}



TEST_F(RepeatGeneratorTest_927, Get_RepeatsElementsCorrectly_927) {

    RepeatGenerator<int> repeatGen(3, CATCH_MOVE(generator));

    for (int i = 0; i < data.size() * 3; ++i) {

        repeatGen.next();

        EXPECT_EQ(repeatGen.get(), data[i % data.size()]);

    }

}



TEST_F(RepeatGeneratorTest_927, Next_ReturnsFalseAfterAllRepeats_927) {

    RepeatGenerator<int> repeatGen(2, CATCH_MOVE(generator));

    for (int i = 0; i < data.size() * 2; ++i) {

        EXPECT_TRUE(repeatGen.next());

    }

    EXPECT_FALSE(repeatGen.next());

}



TEST_F(RepeatGeneratorTest_927, Next_HandlesZeroRepeats_927) {

    RepeatGenerator<int> repeatGen(0, CATCH_MOVE(generator));

    EXPECT_FALSE(repeatGen.next());

}
