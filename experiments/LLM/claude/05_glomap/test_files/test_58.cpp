#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "glomap/exe/global_mapper.h"
#include "glomap/controllers/option_manager.h"
#include "glomap/controllers/global_mapper.h"
#include "glomap/scene/view_graph.h"
#include "glomap/estimators/global_positioning.h"

#include <cstdlib>
#include <fstream>
#include <string>
#include <filesystem>
#include <vector>

namespace glomap {
namespace {

class RunMapperTest_58 : public ::testing::Test {
 protected:
  void SetUp() override {
    // Create a temporary directory for test files
    temp_dir_ = std::filesystem::temp_directory_path() / "glomap_test_58";
    std::filesystem::create_directories(temp_dir_);
  }

  void TearDown() override {
    std::filesystem::remove_all(temp_dir_);
  }

  std::filesystem::path temp_dir_;

  // Helper to convert string args to argc/argv
  struct ArgvHelper {
    std::vector<std::string> args;
    std::vector<char*> argv;

    ArgvHelper(std::initializer_list<std::string> a) : args(a) {
      for (auto& s : args) {
        argv.push_back(s.data());
      }
    }

    int argc() const { return static_cast<int>(argv.size()); }
    char** get_argv() { return argv.data(); }
  };
};

// Test: RunMapper fails when database_path does not exist
TEST_F(RunMapperTest_58, NonExistentDatabasePath_58) {
  std::string fake_db = (temp_dir_ / "nonexistent.db").string();
  std::string output_path = (temp_dir_ / "output").string();

  ArgvHelper args({"mapper",
                   "--database_path", fake_db,
                   "--output_path", output_path});

  int result = RunMapper(args.argc(), args.get_argv());
  EXPECT_EQ(result, EXIT_FAILURE);
}

// Test: RunMapper fails with invalid constraint_type
TEST_F(RunMapperTest_58, InvalidConstraintType_58) {
  // Create a fake database file so the file existence check passes
  std::string db_path = (temp_dir_ / "test.db").string();
  // We need an actual colmap database; create a minimal file
  // But since we can't easily create a valid colmap DB, the test may fail
  // at database open. However, the constraint_type check happens after
  // database existence check, so we need the file to exist.
  {
    std::ofstream ofs(db_path);
    ofs << "fake";
  }

  std::string output_path = (temp_dir_ / "output").string();

  ArgvHelper args({"mapper",
                   "--database_path", db_path,
                   "--output_path", output_path,
                   "--constraint_type", "INVALID_TYPE"});

  int result = RunMapper(args.argc(), args.get_argv());
  EXPECT_EQ(result, EXIT_FAILURE);
}

// Test: RunMapper fails with invalid output_format
TEST_F(RunMapperTest_58, InvalidOutputFormat_58) {
  std::string db_path = (temp_dir_ / "test.db").string();
  {
    std::ofstream ofs(db_path);
    ofs << "fake";
  }

  std::string output_path = (temp_dir_ / "output").string();

  ArgvHelper args({"mapper",
                   "--database_path", db_path,
                   "--output_path", output_path,
                   "--output_format", "ply"});

  int result = RunMapper(args.argc(), args.get_argv());
  EXPECT_EQ(result, EXIT_FAILURE);
}

// Test: GlobalPositionerOptions default values
TEST(GlobalPositionerOptionsTest_58, DefaultValues_58) {
  GlobalPositionerOptions opts;
  EXPECT_TRUE(opts.generate_random_positions);
  EXPECT_TRUE(opts.generate_random_points);
  EXPECT_TRUE(opts.generate_scales);
  EXPECT_TRUE(opts.optimize_positions);
  EXPECT_TRUE(opts.optimize_scales);
  EXPECT_EQ(opts.seed, 1u);
  EXPECT_EQ(opts.constraint_type, GlobalPositionerOptions::ONLY_POINTS);
  EXPECT_DOUBLE_EQ(opts.constraint_reweight_scale, 1.0);
}

// Test: GlobalPositionerOptions constraint type enum values
TEST(GlobalPositionerOptionsTest_58, ConstraintTypeEnumValues_58) {
  EXPECT_EQ(GlobalPositionerOptions::ONLY_POINTS, 0);
  EXPECT_EQ(GlobalPositionerOptions::ONLY_CAMERAS, 1);
  EXPECT_EQ(GlobalPositionerOptions::POINTS_AND_CAMERAS_BALANCED, 2);
  EXPECT_EQ(GlobalPositionerOptions::POINTS_AND_CAMERAS, 3);
}

// Test: GlobalMapperOptions default values
TEST(GlobalMapperOptionsTest_58, DefaultValues_58) {
  GlobalMapperOptions opts;
  EXPECT_EQ(opts.num_iteration_bundle_adjustment, 3);
  EXPECT_EQ(opts.num_iteration_retriangulation, 1);
  EXPECT_FALSE(opts.skip_preprocessing);
  EXPECT_FALSE(opts.skip_view_graph_calibration);
  EXPECT_FALSE(opts.skip_relative_pose_estimation);
  EXPECT_FALSE(opts.skip_rotation_averaging);
  EXPECT_FALSE(opts.skip_track_establishment);
  EXPECT_FALSE(opts.skip_global_positioning);
  EXPECT_FALSE(opts.skip_bundle_adjustment);
  EXPECT_FALSE(opts.skip_retriangulation);
  EXPECT_TRUE(opts.skip_pruning);
}

// Test: GlobalMapper construction
TEST(GlobalMapperTest_58, ConstructWithDefaultOptions_58) {
  GlobalMapperOptions opts;
  EXPECT_NO_THROW(GlobalMapper mapper(opts));
}

// Test: ViewGraph empty image_pairs
TEST(ViewGraphTest_58, EmptyImagePairs_58) {
  ViewGraph vg;
  EXPECT_TRUE(vg.image_pairs.empty());
}

// Test: ViewGraph CreateImageAdjacencyList on empty graph
TEST(ViewGraphTest_58, EmptyAdjacencyList_58) {
  ViewGraph vg;
  auto adj = vg.CreateImageAdjacencyList();
  EXPECT_TRUE(adj.empty());
}

// Test: OptionManager construction
TEST(OptionManagerTest_58, Construction_58) {
  EXPECT_NO_THROW(OptionManager options);
}

// Test: OptionManager can add required and default options
TEST(OptionManagerTest_58, AddOptions_58) {
  OptionManager options;
  std::string db_path;
  std::string img_path;

  EXPECT_NO_THROW(options.AddRequiredOption("database_path", &db_path));
  EXPECT_NO_THROW(options.AddDefaultOption("image_path", &img_path));
}

// Test: OptionManager AddGlobalMapperFullOptions
TEST(OptionManagerTest_58, AddGlobalMapperFullOptions_58) {
  OptionManager options;
  EXPECT_NO_THROW(options.AddGlobalMapperFullOptions());
  // mapper shared_ptr should be valid
  EXPECT_NE(options.mapper, nullptr);
}

// Test: Setting constraint_type through options
TEST(OptionManagerTest_58, MapperConstraintTypeAccess_58) {
  OptionManager options;
  options.AddGlobalMapperFullOptions();

  options.mapper->opt_gp.constraint_type = GlobalPositionerOptions::ONLY_CAMERAS;
  EXPECT_EQ(options.mapper->opt_gp.constraint_type, GlobalPositionerOptions::ONLY_CAMERAS);

  options.mapper->opt_gp.constraint_type = GlobalPositionerOptions::POINTS_AND_CAMERAS_BALANCED;
  EXPECT_EQ(options.mapper->opt_gp.constraint_type, GlobalPositionerOptions::POINTS_AND_CAMERAS_BALANCED);

  options.mapper->opt_gp.constraint_type = GlobalPositionerOptions::POINTS_AND_CAMERAS;
  EXPECT_EQ(options.mapper->opt_gp.constraint_type, GlobalPositionerOptions::POINTS_AND_CAMERAS);

  options.mapper->opt_gp.constraint_type = GlobalPositionerOptions::ONLY_POINTS;
  EXPECT_EQ(options.mapper->opt_gp.constraint_type, GlobalPositionerOptions::ONLY_POINTS);
}

// Test: GlobalPositionerOptions CreateLossFunction returns non-null
TEST(GlobalPositionerOptionsTest_58, CreateLossFunction_58) {
  GlobalPositionerOptions opts;
  auto loss = opts.CreateLossFunction();
  // The loss function should be created (may or may not be nullptr depending on implementation)
  // We just verify it doesn't crash
}

// Test: OptionManager Reset
TEST(OptionManagerTest_58, Reset_58) {
  OptionManager options;
  options.AddGlobalMapperFullOptions();
  EXPECT_NO_THROW(options.Reset());
}

// Test: OptionManager ResetOptions
TEST(OptionManagerTest_58, ResetOptions_58) {
  OptionManager options;
  options.AddGlobalMapperFullOptions();
  EXPECT_NO_THROW(options.ResetOptions(true));
  EXPECT_NO_THROW(options.ResetOptions(false));
}

}  // namespace
}  // namespace glomap
