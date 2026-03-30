#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "poppler-action.h"

#include "Link.h"



using namespace testing;



class PopplerActionTest_2293 : public Test {

protected:

    PopplerAction action;

    std::unique_ptr<LinkLaunch> linkLaunch;

    const char* fileName = "test_file.pdf";

    const char* params = "param1=value1&param2=value2";



    void SetUp() override {

        linkLaunch = std::make_unique<LinkLaunch>(nullptr);

    }



    void TearDown() override {

        if (action.launch.file_name) {

            g_free(action.launch.file_name);

        }

        if (action.launch.params) {

            g_free(action.launch.params);

        }

    }

};



TEST_F(PopplerActionTest_2293, BuildLaunchWithFileName_2293) {

    EXPECT_CALL(*linkLaunch, getFileName()).WillOnce(Return(new GooString(fileName)));

    build_launch(&action, linkLaunch.get());

    ASSERT_STREQ(action.launch.file_name, fileName);

}



TEST_F(PopplerActionTest_2293, BuildLaunchWithParams_2293) {

    EXPECT_CALL(*linkLaunch, getFileName()).WillOnce(Return(new GooString(fileName)));

    EXPECT_CALL(*linkLaunch, getParams()).WillOnce(Return(new GooString(params)));

    build_launch(&action, linkLaunch.get());

    ASSERT_STREQ(action.launch.params, params);

}



TEST_F(PopplerActionTest_2293, BuildLaunchWithEmptyFileName_2293) {

    EXPECT_CALL(*linkLaunch, getFileName()).WillOnce(Return(nullptr));

    build_launch(&action, linkLaunch.get());

    ASSERT_EQ(action.launch.file_name, nullptr);

}



TEST_F(PopplerActionTest_2293, BuildLaunchWithEmptyParams_2293) {

    EXPECT_CALL(*linkLaunch, getFileName()).WillOnce(Return(new GooString(fileName)));

    EXPECT_CALL(*linkLaunch, getParams()).WillOnce(Return(nullptr));

    build_launch(&action, linkLaunch.get());

    ASSERT_EQ(action.launch.params, nullptr);

}



TEST_F(PopplerActionTest_2293, BuildLaunchWithBothFileNameAndParams_2293) {

    EXPECT_CALL(*linkLaunch, getFileName()).WillOnce(Return(new GooString(fileName)));

    EXPECT_CALL(*linkLaunch, getParams()).WillOnce(Return(new GooString(params)));

    build_launch(&action, linkLaunch.get());

    ASSERT_STREQ(action.launch.file_name, fileName);

    ASSERT_STREQ(action.launch.params, params);

}



TEST_F(PopplerActionTest_2293, BuildLaunchWithoutFileNameOrParams_2293) {

    EXPECT_CALL(*linkLaunch, getFileName()).WillOnce(Return(nullptr));

    EXPECT_CALL(*linkLaunch, getParams()).WillOnce(Return(nullptr));

    build_launch(&action, linkLaunch.get());

    ASSERT_EQ(action.launch.file_name, nullptr);

    ASSERT_EQ(action.launch.params, nullptr);

}
