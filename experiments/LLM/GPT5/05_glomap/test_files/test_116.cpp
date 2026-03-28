// File: track_retriangulation_test_116.cc

#include <gtest/gtest.h>

#include "glomap/controllers/track_retriangulation.h"
#include "glomap/scene/frame.h"
#include "glomap/scene/image.h"

// If these typedefs / forward declarations are not pulled transitively,
// include or forward-declare them as needed in your real project.
using glomap::TriangulatorOptions;

class RetriangulateTracksTest_116 : public ::testing::Test {
protected:
  TriangulatorOptions options_;
  colmap::Database database_;

  std::unordered_map<rig_t, glomap::Rig> rigs_;
  std::unordered_map<camera_t, glomap::Camera> cameras_;
  std::unordered_map<frame_t, glomap::Frame> frames_;
  std::unordered_map<image_t, glomap::Image> images_;
  std::unordered_map<track_t, glomap::Track> tracks_;

  void SetUp() override {
    // Use default TriangulatorOptions; tests treat RetriangulateTracks as a black box.
  }
};

//------------------------------------------------------------------------------
// Normal operation: empty scene should be handled without crashing and
// (under normal conditions) report success.
//------------------------------------------------------------------------------
TEST_F(RetriangulateTracksTest_116, ReturnsTrueOnEmptyInputs_116) {
  const bool result = glomap::RetriangulateTracks(
      options_, database_, rigs_, cameras_, frames_, images_, tracks_);

  // We expect that an empty scene can be processed successfully.
  EXPECT_TRUE(result);
}

//------------------------------------------------------------------------------
// Normal operation + observable side-effect:
// Images that are initially registered but not present in the database cache
// are internally de-registered and then re-registered at the end of the
// function. We cannot observe the temporary state, but we can verify that
// the frame ends up registered again after the call.
//------------------------------------------------------------------------------
TEST_F(RetriangulateTracksTest_116,
       KeepsFrameRegisteredForImageNotInDatabase_116) {
  // Create a frame that starts as registered.
  glomap::Frame frame;
  frame.is_registered = true;
  const frame_t frame_id = 1;
  frames_.emplace(frame_id, frame);

  // Create an image associated with that frame.
  const image_t image_id = 10;
  const camera_t camera_id = 5;
  glomap::Image image(image_id, camera_id, "test_image.jpg");

  // Make sure the image is linked to the frame; how IsRegistered() is
  // implemented is internal, we only set fields that are publicly visible.
  image.frame_id = frame_id;
  image.frame_ptr = &frames_.at(frame_id);

  images_.emplace(image_id, image);

  // Call the function under test.
  const bool result = glomap::RetriangulateTracks(
      options_, database_, rigs_, cameras_, frames_, images_, tracks_);

  // We expect the overall pipeline to succeed.
  EXPECT_TRUE(result);

  // The frame should end up registered (even if it was temporarily changed
  // inside RetriangulateTracks).
  EXPECT_TRUE(frames_.at(frame_id).is_registered);
}

//------------------------------------------------------------------------------
// Boundary / no-op style scenario:
// When there are no registered images (or no triangulation happens),
// RetriangulateTracks should not unexpectedly remove existing tracks.
// We only check that the number of tracks is preserved as an observable effect.
//------------------------------------------------------------------------------
TEST_F(RetriangulateTracksTest_116,
       DoesNotModifyTrackCountWhenNoImages_116) {
  // Add a single dummy track. Its internal content is opaque to the test.
  const track_t track_id = 42;
  tracks_.emplace(track_id, glomap::Track{});

  const std::size_t tracks_count_before = tracks_.size();

  const bool result = glomap::RetriangulateTracks(
      options_, database_, rigs_, cameras_, frames_, images_, tracks_);

  // We expect the call to succeed.
  EXPECT_TRUE(result);

  // And we expect that the number of tracks is not reduced as a side-effect
  // in this degenerate case.
  EXPECT_EQ(tracks_count_before, tracks_.size());
}
