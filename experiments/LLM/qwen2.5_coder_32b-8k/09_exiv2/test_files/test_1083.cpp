#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/image.hpp"



using namespace Exiv2;



class ImageTest_1083 : public ::testing::Test {

protected:

    BasicIo::UniquePtr io = std::make_unique<BasicIo>();

    Image image{ImageType::jpeg, 0, std::move(io)};

};



TEST_F(ImageTest_1083, SetComment_NormalOperation_1083) {

    const std::string testComment = "Sample Comment";

    image.setComment(testComment);

    EXPECT_EQ(image.comment(), testComment);

}



TEST_F(ImageTest_1083, SetComment_EmptyString_1083) {

    const std::string emptyComment = "";

    image.setComment(emptyComment);

    EXPECT_EQ(image.comment(), emptyComment);

}



TEST_F(ImageTest_1083, ClearComment_AfterSet_1083) {

    image.setComment("Initial Comment");

    image.clearComment();

    EXPECT_EQ(image.comment(), "");

}



TEST_F(ImageTest_1083, ClearComment_NoPreviousSet_1083) {

    image.clearComment(); // No prior setComment call

    EXPECT_EQ(image.comment(), "");

}
