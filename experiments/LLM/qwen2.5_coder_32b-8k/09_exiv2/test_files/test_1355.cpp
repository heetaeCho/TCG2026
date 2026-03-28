#include <gtest/gtest.h>

#include "./TestProjects/exiv2/src/samsungmn_int.hpp"



using namespace Exiv2::Internal;



class Samsung2MakerNoteTest_1355 : public ::testing::Test {

protected:

    void SetUp() override {

        // Setup code if needed

    }



    void TearDown() override {

        // Teardown code if needed

    }

};



TEST_F(Samsung2MakerNoteTest_1355, TagListPw_ReturnsValidPointer_1355) {

    const auto* tagList = Samsung2MakerNote::tagListPw();

    EXPECT_NE(tagList, nullptr);

}



// Assuming tagList() is also part of the interface to test

TEST_F(Samsung2MakerNoteTest_1355, TagList_ReturnsValidPointer_1355) {

    const auto* tagList = Samsung2MakerNote::tagList();

    EXPECT_NE(tagList, nullptr);

}

```


