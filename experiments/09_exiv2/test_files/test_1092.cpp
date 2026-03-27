#include <gtest/gtest.h>

#include "exiv2/image.hpp"



using namespace Exiv2;



class ImageTest_1092 : public ::testing::Test {

protected:

    std::unique_ptr<BasicIo> io = std::make_unique<BasicIo>();

    Image image{ImageType::jpeg, 0x7fff, std::move(io)};



    void SetUp() override {

        // Setup if needed

    }



    void TearDown() override {

        // Teardown if needed

    }

};



TEST_F(ImageTest_1092, CommentInitiallyEmpty_1092) {

    EXPECT_EQ(image.comment(), "");

}



TEST_F(ImageTest_1092, SetAndGetCommentNormal_1092) {

    image.setComment("Sample comment");

    EXPECT_EQ(image.comment(), "Sample comment");

}



TEST_F(ImageTest_1092, ClearCommentRestoresEmpty_1092) {

    image.setComment("Another sample comment");

    image.clearComment();

    EXPECT_EQ(image.comment(), "");

}



TEST_F(ImageTest_1092, SetAndClearMultipleComments_1092) {

    image.setComment("First comment");

    image.setComment("Second comment");

    image.clearComment();

    EXPECT_EQ(image.comment(), "");

}



TEST_F(ImageTest_1092, BoundaryConditionEmptyString_1092) {

    image.setComment("");

    EXPECT_EQ(image.comment(), "");

}



TEST_F(ImageTest_1092, BoundaryConditionVeryLongString_1092) {

    std::string veryLongString(10000, 'a');

    image.setComment(veryLongString);

    EXPECT_EQ(image.comment(), veryLongString);

}
