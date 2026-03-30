#include <gtest/gtest.h>

#include "catch2/internal/catch_clara.hpp"



using namespace Catch::Clara::Detail;



// Mocking an external collaborator if needed

class MockLambda {

public:

    MOCK_METHOD(bool, operator(), (), (const));

};



TEST_F(BoundManyLambdaTest_383, IsContainerReturnsTrue_383) {

    MockLambda mockLambda;

    BoundManyLambda<MockLambda> boundManyLambda(mockLambda);

    

    EXPECT_TRUE(boundManyLambda.isContainer());

}



// No additional test cases for normal operation as there are no other public methods to test.

// Boundary conditions and exceptional/error cases are not applicable given the current interface.



// Verification of external interactions (e.g., mock handler calls and their parameters)

TEST_F(BoundManyLambdaTest_383, LambdaOperatorNotCalledByIsContainer_383) {

    MockLambda mockLambda;

    EXPECT_CALL(mockLambda, operator()).Times(0);



    BoundManyLambda<MockLambda> boundManyLambda(mockLambda);

    boundManyLambda.isContainer();

}
