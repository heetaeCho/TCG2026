#include <gtest/gtest.h>

#include "./TestProjects/poppler/qt6/src/poppler-private.h"

#include "./TestProjects/poppler/poppler/Error.h"



class PopplerPrivateTest_1242 : public ::testing::Test {

protected:

    // You can set up any common state here if needed.

};



TEST_F(PopplerPrivateTest_1242, FromPopplerCore_ReturnsErrorCodeString_1242) {

    EXPECT_EQ(Poppler::fromPopplerCore(::ErrorStringType::ErrorCodeString), Poppler::ErrorStringType::ErrorCodeString);

}



TEST_F(PopplerPrivateTest_1242, FromPopplerCore_ReturnsUserString_1242) {

    EXPECT_EQ(Poppler::fromPopplerCore(::ErrorStringType::UserString), Poppler::ErrorStringType::UserString);

}



TEST_F(PopplerPrivateTest_1242, FromPopplerCore_DefaultCase_ReturnsErrorCodeString_1242) {

    // Assuming that the default case returns ErrorCodeString

    EXPECT_EQ(Poppler::fromPopplerCore(static_cast<::ErrorStringType>(99)), Poppler::ErrorStringType::ErrorCodeString);

}
