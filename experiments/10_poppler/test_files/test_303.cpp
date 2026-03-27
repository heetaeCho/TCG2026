#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "Link.h"

#include "Object.h"



class LinkMovieTest_303 : public ::testing::Test {

protected:

    Ref validRef;

    Object obj;



    void SetUp() override {

        validRef.num = 1;

        validRef.gen = 0;

    }

};



TEST_F(LinkMovieTest_303, HasAnnotRef_ReturnsFalse_WhenInvalidRef_303) {

    LinkMovie linkMovie(&obj);

    EXPECT_FALSE(linkMovie.hasAnnotRef());

}



TEST_F(LinkMovieTest_303, HasAnnotRef_ReturnsTrue_WhenValidRef_303) {

    validRef = Ref{1, 0};

    Object objWithValidRef;

    // Assuming there is a way to set the ref in the object for testing purposes

    LinkMovie linkMovie(&objWithValidRef);

    EXPECT_TRUE(linkMovie.hasAnnotRef());

}



TEST_F(LinkMovieTest_303, GetAnnotRef_ReturnsNullptr_WhenInvalidRef_303) {

    LinkMovie linkMovie(&obj);

    EXPECT_EQ(nullptr, linkMovie.getAnnotRef());

}



TEST_F(LinkMovieTest_303, GetAnnotRef_ReturnsValidPointer_WhenValidRef_303) {

    validRef = Ref{1, 0};

    Object objWithValidRef;

    // Assuming there is a way to set the ref in the object for testing purposes

    LinkMovie linkMovie(&objWithValidRef);

    EXPECT_NE(nullptr, linkMovie.getAnnotRef());

}



TEST_F(LinkMovieTest_303, HasAnnotTitle_ReturnsFalse_ByDefault_303) {

    LinkMovie linkMovie(&obj);

    EXPECT_FALSE(linkMovie.hasAnnotTitle());

}



TEST_F(LinkMovieTest_303, GetAnnotTitle_ReturnsEmptyString_ByDefault_303) {

    LinkMovie linkMovie(&obj);

    EXPECT_EQ("", linkMovie.getAnnotTitle());

}



TEST_F(LinkMovieTest_303, IsOk_ReturnsTrue_ByDefault_303) {

    LinkMovie linkMovie(&obj);

    EXPECT_TRUE(linkMovie.isOk());

}



TEST_F(LinkMovieTest_303, GetKind_ReturnsExpectedValue_ByDefault_303) {

    LinkMovie linkMovie(&obj);

    EXPECT_EQ(LinkActionKind::movie, linkMovie.getKind());

}



TEST_F(LinkMovieTest_303, GetOperation_ReturnsExpectedValue_ByDefault_303) {

    LinkMovie linkMovie(&obj);

    EXPECT_EQ(OperationType::unknown, linkMovie.getOperation());

}
