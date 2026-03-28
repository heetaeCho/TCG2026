#include <gtest/gtest.h>

#include "Page.h"

#include "Object.h"



class PageAttrsTest : public ::testing::Test {

protected:

    Dict* dict;

    Object pieceInfoObj;



    void SetUp() override {

        dict = new Dict();

        pieceInfoObj = Object(new Dict());

    }



    void TearDown() override {

        delete dict;

    }

};



TEST_F(PageAttrsTest_696, GetPieceInfo_ReturnsNull_WhenPieceInfoNotSet_696) {

    PageAttrs pageAttrs(nullptr, dict);

    EXPECT_EQ(pageAttrs.getPieceInfo(), nullptr);

}



TEST_F(PageAttrsTest_696, GetPieceInfo_ReturnsDict_WhenPieceInfoIsSet_696) {

    dict->dictAdd("PieceInfo", std::move(pieceInfoObj));

    PageAttrs pageAttrs(nullptr, dict);

    EXPECT_NE(pageAttrs.getPieceInfo(), nullptr);

}



TEST_F(PageAttrsTest_696, GetPieceInfo_ReturnsSameDictPtr_WhenCalledMultipleTimes_696) {

    dict->dictAdd("PieceInfo", std::move(pieceInfoObj));

    PageAttrs pageAttrs(nullptr, dict);

    Dict* firstCall = pageAttrs.getPieceInfo();

    Dict* secondCall = pageAttrs.getPieceInfo();

    EXPECT_EQ(firstCall, secondCall);

}
