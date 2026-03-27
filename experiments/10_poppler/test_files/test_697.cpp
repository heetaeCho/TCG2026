#include <gtest/gtest.h>

#include "poppler/Page.h"

#include "poppler/Object.h"



class PageAttrsTest_697 : public ::testing::Test {

protected:

    void SetUp() override {

        separationInfoDict = std::make_unique<Dict>();

        pageAttrs = std::make_unique<PageAttrs>(nullptr, nullptr);

        pageAttrs->separationInfo = Object(separationInfoDict.get());

    }



    void TearDown() override {

        // No need to manually delete unique_ptr managed objects

    }



    std::unique_ptr<Dict> separationInfoDict;

    std::unique_ptr<PageAttrs> pageAttrs;

};



TEST_F(PageAttrsTest_697, GetSeparationInfo_ReturnsDictPointerWhenIsDict_697) {

    EXPECT_EQ(pageAttrs->getSeparationInfo(), separationInfoDict.get());

}



TEST_F(PageAttrsTest_697, GetSeparationInfo_ReturnsNullptrWhenNotDict_697) {

    pageAttrs->separationInfo = Object();

    EXPECT_EQ(pageAttrs->getSeparationInfo(), nullptr);

}
