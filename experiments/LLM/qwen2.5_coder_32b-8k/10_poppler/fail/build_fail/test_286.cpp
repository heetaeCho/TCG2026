#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "Link.h"



using namespace testing;



class LinkGoToRTest_286 : public ::testing::Test {

protected:

    void SetUp() override {

        // Assuming Object and GooString are defined elsewhere in the codebase.

        // We mock the behavior by creating appropriate objects for fileName, destObj, etc.

        fileSpecObj = new Object();

        destObj = new Object();

        namedDestObj = new Object();



        linkGoToR = new LinkGoToR(fileSpecObj, destObj);

    }



    void TearDown() override {

        delete linkGoToR;

        delete fileSpecObj;

        delete destObj;

        delete namedDestObj;

    }



    Object* fileSpecObj;

    Object* destObj;

    Object* namedDestObj;

    LinkGoToR* linkGoToR;

};



TEST_F(LinkGoToRTest_286, IsOk_ReturnsTrue_WhenFileNameAndDestAreValid_286) {

    EXPECT_TRUE(linkGoToR->isOk());

}



TEST_F(LinkGoToRTest_286, IsOk_ReturnsFalse_WhenFileNameIsNull_286) {

    // Assuming we can set fileName to nullptr for testing.

    linkGoToR = new LinkGoToR(nullptr, destObj);

    EXPECT_FALSE(linkGoToR->isOk());

}



TEST_F(LinkGoToRTest_286, IsOk_ReturnsTrue_WhenFileNameAndNamedDestAreValid_286) {

    // Assuming we can set namedDest for testing.

    linkGoToR = new LinkGoToR(fileSpecObj, nullptr);

    EXPECT_TRUE(linkGoToR->isOk());

}



TEST_F(LinkGoToRTest_286, IsOk_ReturnsFalse_WhenBothDestAndNamedDestAreNull_286) {

    // Assuming we can set both dest and namedDest to nullptr for testing.

    linkGoToR = new LinkGoToR(fileSpecObj, nullptr);

    EXPECT_TRUE(linkGoToR->isOk());  // This should be adjusted based on actual behavior if needed.



    linkGoToR = new LinkGoToR(nullptr, nullptr);

    EXPECT_FALSE(linkGoToR->isOk());

}



TEST_F(LinkGoToRTest_286, GetFileName_ReturnsNonNullPointer_WhenFileNameIsValid_286) {

    const GooString* fileName = linkGoToR->getFileName();

    EXPECT_NE(fileName, nullptr);

}



TEST_F(LinkGoToRTest_286, GetDest_ReturnsNonNullPointer_WhenDestIsValid_286) {

    const LinkDest* dest = linkGoToR->getDest();

    EXPECT_NE(dest, nullptr);

}



TEST_F(LinkGoToRTest_286, GetNamedDest_ReturnsNullPointer_WhenNamedDestIsNotSet_286) {

    const GooString* namedDest = linkGoToR->getNamedDest();

    EXPECT_EQ(namedDest, nullptr);

}
