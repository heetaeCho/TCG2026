#include <gtest/gtest.h>

#include "Link.h"



using namespace poppler;



class LinkMovieTest_305 : public ::testing::Test {

protected:

    Ref mockAnnotRef;

    std::string mockAnnotTitle = "Mock Annot Title";

    bool mockHasAnnotTitleFlag = true;

    OperationType mockOperation = OperationType::Play;



    // Mock Object creation for constructor

    class MockObject : public Object {

    public:

        MockObject() {}

    };



    MockObject mockObj;



    LinkMovie *linkMovie;



    void SetUp() override {

        linkMovie = new LinkMovie(&mockObj);

    }



    void TearDown() override {

        delete linkMovie;

    }

};



TEST_F(LinkMovieTest_305, GetAnnotRef_ReturnsPointerToAnnotRef_305) {

    EXPECT_EQ(linkMovie->getAnnotRef(), &linkMovie->annotRef);

}



TEST_F(LinkMovieTest_305, HasAnnotRef_ReturnsTrue_305) {

    EXPECT_TRUE(linkMovie->hasAnnotRef());

}



TEST_F(LinkMovieTest_305, HasAnnotTitle_ReturnsFlagValue_305) {

    // Assuming the constructor sets hasAnnotTitleFlag correctly based on mockObj

    EXPECT_EQ(linkMovie->hasAnnotTitle(), mockHasAnnotTitleFlag);

}



TEST_F(LinkMovieTest_305, GetAnnotTitle_ReturnsCorrectString_305) {

    // Assuming the constructor sets annotTitle correctly based on mockObj

    EXPECT_EQ(linkMovie->getAnnotTitle(), mockAnnotTitle);

}



TEST_F(LinkMovieTest_305, GetOperation_ReturnsCorrectOperationType_305) {

    // Assuming the constructor sets operation correctly based on mockObj

    EXPECT_EQ(linkMovie->getOperation(), mockOperation);

}



// Assuming isOk() and getKind() are part of the interface and should be tested

TEST_F(LinkMovieTest_305, IsOk_ReturnsTrueForValidObject_305) {

    // Assuming a valid constructed object returns true for isOk()

    EXPECT_TRUE(linkMovie->isOk());

}



TEST_F(LinkMovieTest_305, GetKind_ReturnsLinkActionKindMovie_305) {

    // Assuming getKind() should return the correct kind for LinkMovie

    EXPECT_EQ(linkMovie->getKind(), LinkActionKind::movie);

}
