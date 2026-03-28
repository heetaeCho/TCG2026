#include <gtest/gtest.h>

#include "exiv2/error.hpp"



using namespace Exiv2;



class ErrorTest_726 : public ::testing::Test {

protected:

    void SetUp() override {}

    void TearDown() override {}

};



TEST_F(ErrorTest_726, ConstructorWithoutArguments_ReturnsDefaultMessage_726) {

    Error error(ErrorCode::Unknown);

    EXPECT_STREQ(error.what(), "");

}



TEST_F(ErrorTest_726, ConstructorWithOneArgument_ReturnsFormattedMessage_726) {

    Error error(ErrorCode::BadAccess, "file.txt");

    std::string expectedMsg = "Exiv2::Error: BadAccess ('file.txt')";

    EXPECT_EQ(std::string(error.what()), expectedMsg);

}



TEST_F(ErrorTest_726, ConstructorWithTwoArguments_ReturnsFormattedMessage_726) {

    Error error(ErrorCode::BadFormat, "image.jpg", "JPEG");

    std::string expectedMsg = "Exiv2::Error: BadFormat ('image.jpg', 'JPEG')";

    EXPECT_EQ(std::string(error.what()), expectedMsg);

}



TEST_F(ErrorTest_726, ConstructorWithThreeArguments_ReturnsFormattedMessage_726) {

    Error error(ErrorCode::NoKey, "metadata", "tag", "1");

    std::string expectedMsg = "Exiv2::Error: NoKey ('metadata', 'tag', '1')";

    EXPECT_EQ(std::string(error.what()), expectedMsg);

}



TEST_F(ErrorTest_726, Code_ReturnsCorrectErrorCode_726) {

    Error error(ErrorCode::BadAccess);

    EXPECT_EQ(error.code(), ErrorCode::BadAccess);

}



TEST_F(ErrorTest_726, What_ReturnsConsistentMessage_726) {

    const char* message = "Fixed message";

    Error error(ErrorCode::Unknown);

    error.setMsg(message); // Assuming setMsg is used internally to set the message

    EXPECT_STREQ(error.what(), message);

}

```


