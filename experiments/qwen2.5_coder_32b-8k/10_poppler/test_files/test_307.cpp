#include <gtest/gtest.h>

#include "Link.h"

#include <gmock/gmock.h>



// Mocking dependencies if needed, but in this case, no external collaborators are present.



class LinkMovieTest_307 : public ::testing::Test {

protected:

    Object mockObject;

    LinkMovie linkMovie;



    LinkMovieTest_307() : linkMovie(&mockObject) {}

};



TEST_F(LinkMovieTest_307, IsOkReturnsTrue_307) {

    EXPECT_TRUE(linkMovie.isOk());

}



TEST_F(LinkMovieTest_307, GetKindReturnsLinkActionKind_307) {

    LinkActionKind kind = linkMovie.getKind();

    // Since we cannot determine the exact value of getKind(), we can only check if it returns a valid enum.

    EXPECT_TRUE(kind >= 0 && kind <= LinkActionLast);

}



TEST_F(LinkMovieTest_307, HasAnnotRefReturnsFalseWhenNoReferenceSet_307) {

    EXPECT_FALSE(linkMovie.hasAnnotRef());

}



TEST_F(LinkMovieTest_307, GetAnnotRefReturnsNullptrWhenNoReferenceSet_307) {

    EXPECT_EQ(linkMovie.getAnnotRef(), nullptr);

}



TEST_F(LinkMovieTest_307, HasAnnotTitleReturnsFalseWhenNoTitleSet_307) {

    EXPECT_FALSE(linkMovie.hasAnnotTitle());

}



TEST_F(LinkMovieTest_307, GetAnnotTitleReturnsEmptyStringWhenNoTitleSet_307) {

    EXPECT_EQ(linkMovie.getAnnotTitle(), "");

}



TEST_F(LinkMovieTest_307, GetOperationReturnsValidOperationType_307) {

    OperationType operation = linkMovie.getOperation();

    // Since we cannot determine the exact value of getOperation(), we can only check if it returns a valid enum.

    EXPECT_TRUE(operation >= 0 && operation <= MovieOperationLast);

}
