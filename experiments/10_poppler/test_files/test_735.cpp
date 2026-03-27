#include <gtest/gtest.h>



// Mocking external collaborators if needed (none in this case)



class AnnotCoordTest_735 : public ::testing::Test {

protected:

    // Setup and teardown functions can be added here if needed



    AnnotCoord defaultCoord;

    AnnotCoord customCoord;



    AnnotCoordTest_735() : defaultCoord(), customCoord(1.0, 2.0) {}

};



TEST_F(AnnotCoordTest_735, DefaultConstructorInitializesZeroValues_735) {

    EXPECT_EQ(defaultCoord.getX(), 0.0);

    EXPECT_EQ(defaultCoord.getY(), 0.0);

}



TEST_F(AnnotCoordTest_735, ParameterizedConstructorInitializesCorrectValues_735) {

    EXPECT_EQ(customCoord.getX(), 1.0);

    EXPECT_EQ(customCoord.getY(), 2.0);

}



TEST_F(AnnotCoordTest_735, getYReturnsCorrectValueForDefaultConstructor_735) {

    EXPECT_EQ(defaultCoord.getY(), 0.0);

}



TEST_F(AnnotCoordTest_735, getYReturnsCorrectValueForParameterizedConstructor_735) {

    EXPECT_EQ(customCoord.getY(), 2.0);

}
