#include <gtest/gtest.h>

#include "Link.h"



class LinkMovieTest_302 : public ::testing::Test {

protected:

    std::unique_ptr<LinkMovie> link_movie;



    void SetUp() override {

        // Assuming Object is properly constructed and passed to LinkMovie constructor

        Object obj; // This should be a valid object as per the actual implementation

        link_movie = std::make_unique<LinkMovie>(&obj);

    }

};



TEST_F(LinkMovieTest_302, GetKindReturnsCorrectValue_302) {

    EXPECT_EQ(link_movie->getKind(), actionMovie);

}



TEST_F(LinkMovieTest_302, IsOkReturnsTrue_302) {

    // Assuming the object passed to constructor is valid

    EXPECT_TRUE(link_movie->isOk());

}



TEST_F(LinkMovieTest_302, HasAnnotRefFalseByDefault_302) {

    // Testing boundary condition where annotRef might not be set by default

    EXPECT_FALSE(link_movie->hasAnnotRef());

}



TEST_F(LinkMovieTest_302, HasAnnotTitleFalseByDefault_302) {

    // Testing boundary condition where annotTitle might not be set by default

    EXPECT_FALSE(link_movie->hasAnnotTitle());

}



TEST_F(LinkMovieTest_302, GetAnnotRefReturnsNullptrByDefault_302) {

    // Testing boundary condition where getAnnotRef might return nullptr if not set

    EXPECT_EQ(link_movie->getAnnotRef(), nullptr);

}



TEST_F(LinkMovieTest_302, GetAnnotTitleReturnsEmptyStringByDefault_302) {

    // Testing boundary condition where getAnnotTitle might return empty string if not set

    EXPECT_EQ(link_movie->getAnnotTitle(), "");

}



TEST_F(LinkMovieTest_302, GetOperationIsObservable_302) {

    // Assuming OperationType has a default value or is set by the constructor

    OperationType operation = link_movie->getOperation();

    // Depending on actual implementation, this might be a valid check

    EXPECT_NE(operation, static_cast<OperationType>(-1));

}
