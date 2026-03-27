#include <gtest/gtest.h>

#include "glomap/controllers/global_mapper.h"
#include "glomap/estimators/global_positioning.h"

namespace glomap {

class GlobalMapperTest_115 : public ::testing::Test {
protected:
  // 헬퍼: 비어있는 입력 컨테이너들을 준비
  void CreateEmptyInputs(colmap::Database& database,
                         ViewGraph& view_graph,
                         std::unordered_map<rig_t, Rig>& rigs,
                         std::unordered_map<camera_t, Camera>& cameras,
                         std::unordered_map<frame_t, Frame>& frames,
                         std::unordered_map<image_t, Image>& images,
                         std::unordered_map<track_t, Track>& tracks) {
    // 여기서는 단순히 비어있는 컨테이너만 사용한다.
    (void)database;
    (void)view_graph;
    (void)rigs;
    (void)cameras;
    (void)frames;
    (void)images;
    (void)tracks;
  }
};

// 모든 스테이지를 스킵하면 파이프라인이 즉시 성공해야 함
TEST_F(GlobalMapperTest_115, SolveReturnsTrueWhenAllStagesSkipped_115) {
  GlobalMapperOptions options;

  // 모든 처리 단계 스킵
  options.skip_preprocessing          = true;
  options.skip_view_graph_calibration = true;
  options.skip_relative_pose_estimation = true;
  options.skip_rotation_averaging     = true;
  options.skip_track_establishment    = true;
  options.skip_global_positioning     = true;
  options.skip_bundle_adjustment      = true;
  options.skip_retriangulation        = true;
  options.skip_pruning                = true;  // 기본값이지만 명시적으로 설정

  GlobalMapper mapper(options);

  colmap::Database database;
  ViewGraph view_graph;
  std::unordered_map<rig_t, Rig> rigs;
  std::unordered_map<camera_t, Camera> cameras;
  std::unordered_map<frame_t, Frame> frames;
  std::unordered_map<image_t, Image> images;
  std::unordered_map<track_t, Track> tracks;

  CreateEmptyInputs(database, view_graph, rigs, cameras, frames, images, tracks);

  const bool result =
      mapper.Solve(database, view_graph, rigs, cameras, frames, images, tracks);

  EXPECT_TRUE(result);
}

// GlobalPositioning 단계가 활성화되어 있고,
// constraint_type 이 ONLY_POINTS 가 아니면 바로 false 를 반환해야 함
TEST_F(GlobalMapperTest_115,
       SolveReturnsFalseWhenConstraintTypeIsNotOnlyPoints_115) {
  GlobalMapperOptions options;

  // 이전 단계들은 모두 스킵해서, 반드시 global positioning 블록까지 도달하도록 설정
  options.skip_preprocessing          = true;
  options.skip_view_graph_calibration = true;
  options.skip_relative_pose_estimation = true;
  options.skip_rotation_averaging     = true;
  options.skip_track_establishment    = true;

  // Global positioning 단계는 수행
  options.skip_global_positioning     = false;

  // 이후 단계는 테스트 단순화를 위해 스킵
  options.skip_bundle_adjustment      = true;
  options.skip_retriangulation        = true;
  options.skip_pruning                = true;

  // 코드 내부 조건:
  // if (options_.opt_gp.constraint_type != GlobalPositionerOptions::ConstraintType::ONLY_POINTS)
  //   return false;
  options.opt_gp.constraint_type =
      GlobalPositionerOptions::ConstraintType::ONLY_CAMERAS;

  GlobalMapper mapper(options);

  colmap::Database database;
  ViewGraph view_graph;
  std::unordered_map<rig_t, Rig> rigs;
  std::unordered_map<camera_t, Camera> cameras;
  std::unordered_map<frame_t, Frame> frames;
  std::unordered_map<image_t, Image> images;
  std::unordered_map<track_t, Track> tracks;

  CreateEmptyInputs(database, view_graph, rigs, cameras, frames, images, tracks);

  const bool result =
      mapper.Solve(database, view_graph, rigs, cameras, frames, images, tracks);

  EXPECT_FALSE(result);
}

// GlobalPositioning 이 스킵되면, constraint_type 이 ONLY_POINTS 가 아니어도
// 해당 제약은 검사되지 않고 전체 Solve 는 성공해야 함
TEST_F(GlobalMapperTest_115,
       SolveIgnoresConstraintTypeWhenGlobalPositioningSkipped_115) {
  GlobalMapperOptions options;

  // 모든 단계 스킵
  options.skip_preprocessing          = true;
  options.skip_view_graph_calibration = true;
  options.skip_relative_pose_estimation = true;
  options.skip_rotation_averaging     = true;
  options.skip_track_establishment    = true;
  options.skip_global_positioning     = true;  // 핵심: global positioning 을 스킵
  options.skip_bundle_adjustment      = true;
  options.skip_retriangulation        = true;
  options.skip_pruning                = true;

  // constraint_type 을 "잘못된" 값으로 설정하지만,
  // skip_global_positioning 이 true 이므로 코드 상에서 검사되지 않아야 한다.
  options.opt_gp.constraint_type =
      GlobalPositionerOptions::ConstraintType::ONLY_CAMERAS;

  GlobalMapper mapper(options);

  colmap::Database database;
  ViewGraph view_graph;
  std::unordered_map<rig_t, Rig> rigs;
  std::unordered_map<camera_t, Camera> cameras;
  std::unordered_map<frame_t, Frame> frames;
  std::unordered_map<image_t, Image> images;
  std::unordered_map<track_t, Track> tracks;

  CreateEmptyInputs(database, view_graph, rigs, cameras, frames, images, tracks);

  const bool result =
      mapper.Solve(database, view_graph, rigs, cameras, frames, images, tracks);

  EXPECT_TRUE(result);
}

}  // namespace glomap
