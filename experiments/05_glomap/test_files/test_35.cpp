#include <gtest/gtest.h>

#include "option_manager.h"



namespace glomap {

    class OptionManagerTest_35 : public ::testing::Test {

    protected:

        OptionManager manager{true};



        void SetUp() override {

            // Setup code if needed

        }



        void TearDown() override {

            // Teardown code if needed

        }

    };



    TEST_F(OptionManagerTest_35, AddImageOptions_FirstCall_AddsOption_35) {

        EXPECT_FALSE(manager.added_image_options_);

        manager.AddImageOptions();

        EXPECT_TRUE(manager.added_image_options_);

    }



    TEST_F(OptionManagerTest_35, AddImageOptions_SecondCall_DoesNotAddAgain_35) {

        manager.AddImageOptions();

        EXPECT_TRUE(manager.added_image_options_);

        manager.AddImageOptions();

        EXPECT_TRUE(manager.added_image_options_);

    }



} // namespace glomap
