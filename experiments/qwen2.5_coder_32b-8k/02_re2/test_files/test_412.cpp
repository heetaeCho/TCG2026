#include <gtest/gtest.h>

#include "re2/prog.h"



using namespace re2;



class ProgTest_412 : public ::testing::Test {

protected:

    void SetUp() override {

        prog = new Prog();

    }



    void TearDown() override {

        delete prog;

    }



    Prog* prog;

};



TEST_F(ProgTest_412, FlattenNormalOperation_412) {

    // Arrange

    prog->set_start(0);

    prog->set_start_unanchored(1);



    // Act

    prog->Flatten();



    // Assert

    EXPECT_TRUE(prog->did_flatten());

}



TEST_F(ProgTest_412, FlattenBoundaryConditionStartUnanchoredZero_412) {

    // Arrange

    prog->set_start(0);

    prog->set_start_unanchored(0);



    // Act

    prog->Flatten();



    // Assert

    EXPECT_EQ(prog->start(), 0);

    EXPECT_EQ(prog->start_unanchored(), 0);

}



TEST_F(ProgTest_412, FlattenBoundaryConditionStartEqualsUnanchored_412) {

    // Arrange

    prog->set_start(1);

    prog->set_start_unanchored(1);



    // Act

    prog->Flatten();



    // Assert

    EXPECT_EQ(prog->start(), 1);

    EXPECT_EQ(prog->start_unanchored(), 1);

}



TEST_F(ProgTest_412, FlattenBoundaryConditionStartDifferentFromUnanchored_412) {

    // Arrange

    prog->set_start(1);

    prog->set_start_unanchored(2);



    // Act

    prog->Flatten();



    // Assert

    EXPECT_EQ(prog->start(), 2);

    EXPECT_EQ(prog->start_unanchored(), 2);

}



TEST_F(ProgTest_412, FlattenIdempotency_412) {

    // Arrange

    prog->set_start(0);

    prog->set_start_unanchored(1);



    // Act

    prog->Flatten();

    prog->Flatten();



    // Assert

    EXPECT_TRUE(prog->did_flatten());

}



TEST_F(ProgTest_412, FlattenNoChangeWhenAlreadyFlattened_412) {

    // Arrange

    prog->set_start(0);

    prog->set_start_unanchored(1);

    prog->Flatten();



    // Act & Assert (no change expected)

    EXPECT_TRUE(prog->did_flatten());

}
