// File: option_manager_test_166.cc

#include <gtest/gtest.h>
#include <vector>
#include <string>

#include "glomap/controllers/option_manager.h"

#ifdef GLOMAP_HAS_GLOG   // If the project uses a dedicated macro, adjust/remove as needed.
#include <glog/logging.h>
#endif

namespace {

class OptionManagerTest_166 : public ::testing::Test {
 protected:
  // Use true here; behavior with false is tested separately.
  glomap::OptionManager manager_{true};
};

// Constructor should initialize all shared_ptr members.
TEST_F(OptionManagerTest_166, ConstructorInitializesSharedPointers_166) {
  EXPECT_NE(nullptr, manager_.database_path);
  EXPECT_NE(nullptr, manager_.image_path);
  EXPECT_NE(nullptr, manager_.mapper);
  EXPECT_NE(nullptr, manager_.gravity_refiner);
}

// Constructor with false should still construct a usable object.
TEST(OptionManagerStandalone_166, ConstructorWithFalseDoesNotThrow_166) {
  EXPECT_NO_THROW({
    glomap::OptionManager manager(false);
    EXPECT_NE(nullptr, manager.database_path);
    EXPECT_NE(nullptr, manager.image_path);
    EXPECT_NE(nullptr, manager.mapper);
    EXPECT_NE(nullptr, manager.gravity_refiner);
  });
}

// ResetOptions(true) is expected to reset path-related options.
TEST_F(OptionManagerTest_166, ResetOptionsWithResetPathsTrueClearsPaths_166) {
  // Arrange: set non-empty paths.
  *manager_.database_path = "custom_db_path";
  *manager_.image_path = "custom_image_path";

  // Act: reset with reset_paths = true.
  manager_.ResetOptions(true);

  // Assert: paths are reset (we only rely on observable public strings).
  EXPECT_TRUE(manager_.database_path->empty());
  EXPECT_TRUE(manager_.image_path->empty());
}

// ResetOptions(false) should keep existing paths unchanged.
TEST_F(OptionManagerTest_166, ResetOptionsWithResetPathsFalseKeepsPaths_166) {
  // Arrange: set non-empty paths.
  *manager_.database_path = "custom_db_path";
  *manager_.image_path = "custom_image_path";

  // Act: reset with reset_paths = false.
  manager_.ResetOptions(false);

  // Assert: paths are preserved.
  EXPECT_EQ("custom_db_path", *manager_.database_path);
  EXPECT_EQ("custom_image_path", *manager_.image_path);
}

// AddAllOptions should be callable multiple times without errors.
TEST_F(OptionManagerTest_166, AddAllOptionsIsIdempotent_166) {
  EXPECT_NO_THROW({
    manager_.AddAllOptions();
    manager_.AddAllOptions();
  });
}

// Parse should handle minimal argument list (no options) without throwing.
TEST_F(OptionManagerTest_166, ParseHandlesNoAdditionalArguments_166) {
  const char* arg0 = "program";
  char* argv[] = {const_cast<char*>(arg0)};
  int argc = 1;

  EXPECT_NO_THROW({
    manager_.Parse(argc, argv);
  });
}

#ifdef FLAGS_logtostderr  // If glog/gflags are available as used by OptionManager.

// Parse should respect registered default options "log_to_stderr" and "log_level".
TEST_F(OptionManagerTest_166, ParseUpdatesLogFlagsFromCommandLine_166) {
  // Save original values to restore after the test.
  bool original_logtostderr = FLAGS_logtostderr;
  int original_v = FLAGS_v;

  // Arrange: known starting values.
  FLAGS_logtostderr = false;
  FLAGS_v = 0;

  const char* arg0 = "program";
  const char* arg1 = "--log_to_stderr=true";
  const char* arg2 = "--log_level=2";

  std::vector<char*> argv_vec;
  argv_vec.push_back(const_cast<char*>(arg0));
  argv_vec.push_back(const_cast<char*>(arg1));
  argv_vec.push_back(const_cast<char*>(arg2));
  int argc = static_cast<int>(argv_vec.size());

  // Act: parse the command line.
  manager_.Parse(argc, argv_vec.data());

  // Assert: flags should be updated according to parsed options.
  EXPECT_TRUE(FLAGS_logtostderr);
  EXPECT_EQ(2, FLAGS_v);

  // Restore original values.
  FLAGS_logtostderr = original_logtostderr;
  FLAGS_v = original_v;
}

#endif  // FLAGS_logtostderr

}  // namespace
