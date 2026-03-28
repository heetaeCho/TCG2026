#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "option_manager.h"



using namespace glomap;

using ::testing::Test;



class OptionManagerTest_43 : public Test {

protected:

    void SetUp() override {

        option_manager = std::make_unique<OptionManager>(false);

    }



    std::unique_ptr<OptionManager> option_manager;

};



TEST_F(OptionManagerTest_43, AddTrackEstablishmentOptions_AddsOptionsOnce_43) {

    EXPECT_FALSE(option_manager->added_track_establishment_options_);

    option_manager->AddTrackEstablishmentOptions();

    EXPECT_TRUE(option_manager->added_track_establishment_options_);

}



TEST_F(OptionManagerTest_43, AddTrackEstablishmentOptions_Idempotent_43) {

    option_manager->AddTrackEstablishmentOptions();

    auto initial_state = option_manager->added_track_establishment_options_;

    option_manager->AddTrackEstablishmentOptions();

    EXPECT_EQ(option_manager->added_track_establishment_options_, initial_state);

}



TEST_F(OptionManagerTest_43, AddTrackEstablishmentOptions_DefaultValuesSet_43) {

    option_manager->mapper = std::make_shared<GlobalMapperOptions>();

    option_manager->AddTrackEstablishmentOptions();

    EXPECT_EQ(option_manager->mapper->opt_track.min_num_tracks_per_view, -1);

    EXPECT_EQ(option_manager->mapper->opt_track.max_num_view_per_track, 100);

    EXPECT_EQ(option_manager->mapper->opt_track.max_num_tracks, 10000000);

}



TEST_F(OptionManagerTest_43, AddTrackEstablishmentOptions_MapperNotInitializedThrows_43) {

    EXPECT_THROW(option_manager->AddTrackEstablishmentOptions(), std::runtime_error);

}
