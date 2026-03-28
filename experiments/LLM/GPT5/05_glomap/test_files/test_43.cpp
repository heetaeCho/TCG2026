// File: option_manager_add_track_establishment_options_test_43.cc

#include <gtest/gtest.h>

#include "glomap/controllers/option_manager.h"
#include "glomap/controllers/global_mapper.h"

#include <memory>
#include <vector>
#include <string>

namespace {

class OptionManagerTest_43 : public ::testing::Test {
protected:
  void SetUp() override {
    option_manager_ =
        std::make_unique<glomap::OptionManager>(false /*add_project_options*/);
    option_manager_->mapper =
        std::make_shared<glomap::GlobalMapperOptions>();
  }

  std::unique_ptr<glomap::OptionManager> option_manager_;
};

// Normal operation: options registered so that Parse() can override
// TrackEstablishment-related fields from command line.
TEST_F(OptionManagerTest_43,
       AddTrackEstablishmentOptions_ParsesCommandLineValues_43) {
  ASSERT_NE(option_manager_->mapper, nullptr);

  // Check initial values (from GlobalMapperOptions / TrackEstablishmentOptions).
  const int initial_min_tracks_per_view =
      option_manager_->mapper->opt_track.min_num_tracks_per_view;
  const int initial_max_view_per_track =
      option_manager_->mapper->opt_track.max_num_view_per_track;
  const int initial_max_tracks =
      option_manager_->mapper->opt_track.max_num_tracks;

  // Register track establishment options.
  option_manager_->AddTrackEstablishmentOptions();

  // Prepare command-line arguments that should be understood by OptionManager.
  std::vector<std::string> args = {
      "program",
      "--TrackEstablishment.min_num_tracks_per_view=5",
      // This option is registered in AddTrackEstablishmentOptions, but we do
      // not need to inspect its underlying field to keep the test independent
      // of internal struct layout.
      "--TrackEstablishment.min_num_view_per_track=7",
      "--TrackEstablishment.max_num_view_per_track=15",
      "--TrackEstablishment.max_num_tracks=12345"};

  std::vector<char*> argv;
  argv.reserve(args.size());
  for (auto& s : args) {
    argv.push_back(const_cast<char*>(s.c_str()));
  }
  int argc = static_cast<int>(argv.size());

  // Parse should succeed and update the mapper options accordingly.
  option_manager_->Parse(argc, argv.data());

  EXPECT_NE(option_manager_->mapper->opt_track.min_num_tracks_per_view,
            initial_min_tracks_per_view);
  EXPECT_NE(option_manager_->mapper->opt_track.max_num_view_per_track,
            initial_max_view_per_track);
  EXPECT_NE(option_manager_->mapper->opt_track.max_num_tracks,
            initial_max_tracks);

  EXPECT_EQ(option_manager_->mapper->opt_track.min_num_tracks_per_view, 5);
  EXPECT_EQ(option_manager_->mapper->opt_track.max_num_view_per_track, 15);
  EXPECT_EQ(option_manager_->mapper->opt_track.max_num_tracks, 12345);
}

// Boundary behavior: calling AddTrackEstablishmentOptions should *not* change
// the existing option values by itself (i.e., without Parse()).
TEST_F(OptionManagerTest_43,
       AddTrackEstablishmentOptions_DoesNotChangeValuesWithoutParse_43) {
  ASSERT_NE(option_manager_->mapper, nullptr);

  // Capture current values.
  const int before_min_tracks_per_view =
      option_manager_->mapper->opt_track.min_num_tracks_per_view;
  const int before_max_view_per_track =
      option_manager_->mapper->opt_track.max_num_view_per_track;
  const int before_max_tracks =
      option_manager_->mapper->opt_track.max_num_tracks;

  // Register options but do not parse any command line.
  option_manager_->AddTrackEstablishmentOptions();

  // Values should remain unchanged.
  EXPECT_EQ(option_manager_->mapper->opt_track.min_num_tracks_per_view,
            before_min_tracks_per_view);
  EXPECT_EQ(option_manager_->mapper->opt_track.max_num_view_per_track,
            before_max_view_per_track);
  EXPECT_EQ(option_manager_->mapper->opt_track.max_num_tracks,
            before_max_tracks);
}

// Exceptional / idempotency case: calling AddTrackEstablishmentOptions()
// multiple times should be safe (guarded by the internal flag) and not throw.
TEST_F(OptionManagerTest_43,
       AddTrackEstablishmentOptions_IsIdempotentOnMultipleCalls_43) {
  ASSERT_NE(option_manager_->mapper, nullptr);

  // First call should succeed.
  EXPECT_NO_THROW(option_manager_->AddTrackEstablishmentOptions());

  // Capture values after first registration.
  const int after_first_min_tracks_per_view =
      option_manager_->mapper->opt_track.min_num_tracks_per_view;
  const int after_first_max_view_per_track =
      option_manager_->mapper->opt_track.max_num_view_per_track;
  const int after_first_max_tracks =
      option_manager_->mapper->opt_track.max_num_tracks;

  // Second call should be a no-op and must not throw.
  EXPECT_NO_THROW(option_manager_->AddTrackEstablishmentOptions());

  // Values should remain unchanged after the second call.
  EXPECT_EQ(option_manager_->mapper->opt_track.min_num_tracks_per_view,
            after_first_min_tracks_per_view);
  EXPECT_EQ(option_manager_->mapper->opt_track.max_num_view_per_track,
            after_first_max_view_per_track);
  EXPECT_EQ(option_manager_->mapper->opt_track.max_num_tracks,
            after_first_max_tracks);
}

}  // namespace
