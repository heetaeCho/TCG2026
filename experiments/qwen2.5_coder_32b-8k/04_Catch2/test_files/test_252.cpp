#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "catch2/internal/catch_context.hpp"



using namespace Catch;



class ContextTest_252 : public ::testing::Test {

protected:

    Context context;

};



TEST_F(ContextTest_252, GetResultCapture_ReturnsNullByDefault_252) {

    EXPECT_EQ(context.getResultCapture(), nullptr);

}



TEST_F(ContextTest_252, SetAndGetResultCapture_WorksCorrectly_252) {

    IResultCapture mockResultCapture;

    context.setResultCapture(&mockResultCapture);

    EXPECT_EQ(context.getResultCapture(), &mockResultCapture);

}



TEST_F(ContextTest_252, GetConfig_ReturnsNullByDefault_252) {

    EXPECT_EQ(context.getConfig(), nullptr);

}



TEST_F(ContextTest_252, SetAndGetConfig_WorksCorrectly_252) {

    IConfig mockConfig;

    context.setConfig(&mockConfig);

    EXPECT_EQ(context.getConfig(), &mockConfig);

}
