#include <gtest/gtest.h>

#include "exiv2/image.hpp"

#include <memory>

#include <string>



namespace Exiv2 {

    class BasicIo;

}



using namespace Exiv2;



class ImageTest_1082 : public ::testing::Test {

protected:

    void SetUp() override {

        auto io = std::make_unique<BasicIo>();

        image = std::make_unique<Image>(ImageType::jpeg, 0, std::move(io));

    }



    std::unique_ptr<Image> image;

};



TEST_F(ImageTest_1082, ClearComment_NoCommentSet_1082) {

    // No comment set initially

    image->clearComment();

    EXPECT_EQ(image->comment(), "");

}



TEST_F(ImageTest_1082, ClearComment_CommentSet_1082) {

    std::string test_comment = "Sample Comment";

    image->setComment(test_comment);

    image->clearComment();

    EXPECT_EQ(image->comment(), "");

}



TEST_F(ImageTest_1082, SetAndClearComment_BoundaryConditions_1082) {

    // Test with empty string

    std::string empty_comment = "";

    image->setComment(empty_comment);

    EXPECT_EQ(image->comment(), empty_comment);

    image->clearComment();

    EXPECT_EQ(image->comment(), "");



    // Test with single character

    std::string single_char_comment = "A";

    image->setComment(single_char_comment);

    EXPECT_EQ(image->comment(), single_char_comment);

    image->clearComment();

    EXPECT_EQ(image->comment(), "");

}



TEST_F(ImageTest_1082, SetAndClearComment_NormalOperation_1082) {

    std::string test_comment = "This is a test comment.";

    image->setComment(test_comment);

    EXPECT_EQ(image->comment(), test_comment);

    image->clearComment();

    EXPECT_EQ(image->comment(), "");

}



TEST_F(ImageTest_1082, ClearComment_MultipleTimes_1082) {

    std::string test_comment = "Multiple clear calls.";

    image->setComment(test_comment);

    image->clearComment();

    image->clearComment(); // Additional call

    EXPECT_EQ(image->comment(), "");

}
