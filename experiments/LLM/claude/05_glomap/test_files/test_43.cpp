#include <gtest/gtest.h>
#include "glomap/controllers/option_manager.h"

namespace glomap {
namespace {

class OptionManagerTest_43 : public ::testing::Test {
 protected:
  void SetUp() override {
    option_manager_ = std::make_unique<OptionManager>(false);
  }

  std::unique_ptr<OptionManager> option_manager_;
};

// Test that AddTrackEstablishmentOptions can be called without error
TEST_F(OptionManagerTest_43, AddTrackEstablishmentOptionsSucceeds_43) {
  EXPECT_NO_THROW(option_manager_->AddTrackEstablishmentOptions());
}

// Test that calling AddTrackEstablishmentOptions twice is idempotent (guard flag)
TEST_F(OptionManagerTest_43, AddTrackEstablishmentOptionsIdempotent_43) {
  EXPECT_NO_THROW(option_manager_->AddTrackEstablishmentOptions());
  EXPECT_NO_THROW(option_manager_->AddTrackEstablishmentOptions());
}

// Test that the mapper shared pointer is valid and track options have expected defaults
TEST_F(OptionManagerTest_43, TrackEstablishmentDefaultValues_43) {
  option_manager_->AddTrackEstablishmentOptions();
  ASSERT_NE(option_manager_->mapper, nullptr);
  // Verify default values from TrackEstablishmentOptions
  EXPECT_EQ(option_manager_->mapper->opt_track.min_num_tracks_per_view, -1);
  EXPECT_EQ(option_manager_->mapper->opt_track.max_num_view_per_track, 100);
  EXPECT_EQ(option_manager_->mapper->opt_track.max_num_tracks, 10000000);
}

// Test that AddAllOptions includes track establishment without errors
TEST_F(OptionManagerTest_43, AddAllOptionsIncludesTrackEstablishment_43) {
  EXPECT_NO_THROW(option_manager_->AddAllOptions());
}

// Test that AddAllOptions followed by AddTrackEstablishmentOptions doesn't crash (idempotency)
TEST_F(OptionManagerTest_43, AddAllOptionsThenTrackEstablishment_43) {
  EXPECT_NO_THROW(option_manager_->AddAllOptions());
  EXPECT_NO_THROW(option_manager_->AddTrackEstablishmentOptions());
}

// Test Reset followed by re-adding track establishment options
TEST_F(OptionManagerTest_43, ResetThenAddTrackEstablishment_43) {
  option_manager_->AddTrackEstablishmentOptions();
  EXPECT_NO_THROW(option_manager_->Reset());
  EXPECT_NO_THROW(option_manager_->AddTrackEstablishmentOptions());
}

// Test ResetOptions with reset_paths = false
TEST_F(OptionManagerTest_43, ResetOptionsNoPathsThenAddTrackEstablishment_43) {
  option_manager_->AddTrackEstablishmentOptions();
  EXPECT_NO_THROW(option_manager_->ResetOptions(false));
  EXPECT_NO_THROW(option_manager_->AddTrackEstablishmentOptions());
}

// Test ResetOptions with reset_paths = true
TEST_F(OptionManagerTest_43, ResetOptionsWithPathsThenAddTrackEstablishment_43) {
  option_manager_->AddTrackEstablishmentOptions();
  EXPECT_NO_THROW(option_manager_->ResetOptions(true));
  EXPECT_NO_THROW(option_manager_->AddTrackEstablishmentOptions());
}

// Test that mapper is non-null even before adding track options
TEST_F(OptionManagerTest_43, MapperExistsBeforeAddingTrackOptions_43) {
  ASSERT_NE(option_manager_->mapper, nullptr);
}

// Test adding database options alongside track establishment
TEST_F(OptionManagerTest_43, AddDatabaseAndTrackEstablishmentOptions_43) {
  EXPECT_NO_THROW(option_manager_->AddDatabaseOptions());
  EXPECT_NO_THROW(option_manager_->AddTrackEstablishmentOptions());
}

// Test adding image options alongside track establishment
TEST_F(OptionManagerTest_43, AddImageAndTrackEstablishmentOptions_43) {
  EXPECT_NO_THROW(option_manager_->AddImageOptions());
  EXPECT_NO_THROW(option_manager_->AddTrackEstablishmentOptions());
}

// Test that AddGlobalMapperOptions works alongside track establishment
TEST_F(OptionManagerTest_43, AddGlobalMapperAndTrackEstablishmentOptions_43) {
  EXPECT_NO_THROW(option_manager_->AddGlobalMapperOptions());
  EXPECT_NO_THROW(option_manager_->AddTrackEstablishmentOptions());
}

// Test AddGlobalMapperFullOptions includes track establishment
TEST_F(OptionManagerTest_43, AddGlobalMapperFullOptionsIncludesTrack_43) {
  EXPECT_NO_THROW(option_manager_->AddGlobalMapperFullOptions());
  // Should be idempotent since full options likely adds track options
  EXPECT_NO_THROW(option_manager_->AddTrackEstablishmentOptions());
}

// Test constructing OptionManager with add_project_options = true
TEST(OptionManagerConstructionTest_43, ConstructWithProjectOptions_43) {
  EXPECT_NO_THROW(OptionManager om(true));
}

// Test constructing OptionManager with add_project_options = false
TEST(OptionManagerConstructionTest_43, ConstructWithoutProjectOptions_43) {
  EXPECT_NO_THROW(OptionManager om(false));
}

// Test that default track option values are accessible via mapper after construction
TEST(OptionManagerConstructionTest_43, DefaultTrackOptionsAccessible_43) {
  OptionManager om(false);
  ASSERT_NE(om.mapper, nullptr);
  // Default TrackEstablishmentOptions values
  EXPECT_DOUBLE_EQ(om.mapper->opt_track.thres_inconsistency, 10.0);
  EXPECT_EQ(om.mapper->opt_track.min_num_tracks_per_view, -1);
  EXPECT_EQ(om.mapper->opt_track.max_num_view_per_track, 100);
  EXPECT_EQ(om.mapper->opt_track.max_num_tracks, 10000000);
}

// Test Parse with minimal argc/argv after adding track options
TEST_F(OptionManagerTest_43, ParseWithTrackEstablishmentOptions_43) {
  option_manager_->AddTrackEstablishmentOptions();
  const char* argv[] = {"test_program"};
  EXPECT_NO_THROW(option_manager_->Parse(1, const_cast<char**>(argv)));
}

// Test Parse with track establishment option specified on command line
TEST_F(OptionManagerTest_43, ParseTrackEstablishmentMaxNumTracks_43) {
  option_manager_->AddTrackEstablishmentOptions();
  const char* argv[] = {
      "test_program",
      "--TrackEstablishment.max_num_tracks=500"
  };
  EXPECT_NO_THROW(option_manager_->Parse(2, const_cast<char**>(argv)));
  EXPECT_EQ(option_manager_->mapper->opt_track.max_num_tracks, 500);
}

// Test Parse with multiple track establishment options
TEST_F(OptionManagerTest_43, ParseMultipleTrackEstablishmentOptions_43) {
  option_manager_->AddTrackEstablishmentOptions();
  const char* argv[] = {
      "test_program",
      "--TrackEstablishment.max_num_tracks=200",
      "--TrackEstablishment.max_num_view_per_track=50",
      "--TrackEstablishment.min_num_tracks_per_view=5"
  };
  EXPECT_NO_THROW(option_manager_->Parse(4, const_cast<char**>(argv)));
  EXPECT_EQ(option_manager_->mapper->opt_track.max_num_tracks, 200);
  EXPECT_EQ(option_manager_->mapper->opt_track.max_num_view_per_track, 50);
  EXPECT_EQ(option_manager_->mapper->opt_track.min_num_tracks_per_view, 5);
}

// Test that min_num_view_per_track is registered (it's referenced in AddTrackEstablishmentOptions)
TEST_F(OptionManagerTest_43, ParseMinNumViewPerTrack_43) {
  option_manager_->AddTrackEstablishmentOptions();
  const char* argv[] = {
      "test_program",
      "--TrackEstablishment.min_num_view_per_track=3"
  };
  EXPECT_NO_THROW(option_manager_->Parse(2, const_cast<char**>(argv)));
}

// Test adding multiple different option groups
TEST_F(OptionManagerTest_43, AddMultipleOptionGroups_43) {
  EXPECT_NO_THROW(option_manager_->AddViewGraphCalibrationOptions());
  EXPECT_NO_THROW(option_manager_->AddRelativePoseEstimationOptions());
  EXPECT_NO_THROW(option_manager_->AddRotationEstimatorOptions());
  EXPECT_NO_THROW(option_manager_->AddTrackEstablishmentOptions());
  EXPECT_NO_THROW(option_manager_->AddGlobalPositionerOptions());
  EXPECT_NO_THROW(option_manager_->AddBundleAdjusterOptions());
  EXPECT_NO_THROW(option_manager_->AddTriangulatorOptions());
  EXPECT_NO_THROW(option_manager_->AddInlierThresholdOptions());
}

// Test boundary: max_num_tracks set to 0
TEST_F(OptionManagerTest_43, ParseTrackEstablishmentBoundaryZero_43) {
  option_manager_->AddTrackEstablishmentOptions();
  const char* argv[] = {
      "test_program",
      "--TrackEstablishment.max_num_tracks=0"
  };
  EXPECT_NO_THROW(option_manager_->Parse(2, const_cast<char**>(argv)));
  EXPECT_EQ(option_manager_->mapper->opt_track.max_num_tracks, 0);
}

// Test boundary: negative value for min_num_tracks_per_view
TEST_F(OptionManagerTest_43, ParseTrackEstablishmentNegativeValue_43) {
  option_manager_->AddTrackEstablishmentOptions();
  const char* argv[] = {
      "test_program",
      "--TrackEstablishment.min_num_tracks_per_view=-100"
  };
  EXPECT_NO_THROW(option_manager_->Parse(2, const_cast<char**>(argv)));
  EXPECT_EQ(option_manager_->mapper->opt_track.min_num_tracks_per_view, -100);
}

}  // namespace
}  // namespace glomap
