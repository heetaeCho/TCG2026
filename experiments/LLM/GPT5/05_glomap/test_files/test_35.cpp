// option_manager_add_image_options_test_35.cc

#include <gtest/gtest.h>

#include <string>
#include <vector>

#include "glomap/controllers/option_manager.h"

using glomap::OptionManager;

namespace {

class OptionManagerAddImageOptionsTest_35 : public ::testing::Test {
 protected:
  OptionManagerAddImageOptionsTest_35()
      : option_manager_(false) {}  // Do not add all project options automatically.

  // Helper to build argc/argv style arrays from a list of strings.
  static void BuildArgv(const std::vector<std::string>& args,
                        int* argc,
                        std::vector<char*>* argv) {
    argv->clear();
    argv->reserve(args.size());
    for (const auto& s : args) {
      argv->push_back(const_cast<char*>(s.c_str()));
    }
    *argc = static_cast<int>(argv->size());
  }

  OptionManager option_manager_;
};

// Normal operation: after registering image options, Parse should accept
// --image_path and store the value into image_path.
TEST_F(OptionManagerAddImageOptionsTest_35,
       ParseSetsImagePathWhenImageOptionIsRegistered_35) {
  option_manager_.AddImageOptions();

  ASSERT_NE(option_manager_.image_path, nullptr);

  const std::string kImagePath = "/tmp/test_images_35";

  std::vector<std::string> args = {
      "glomap_test_35",
      "--image_path",
      kImagePath,
  };
  int argc = 0;
  std::vector<char*> argv;
  BuildArgv(args, &argc, &argv);

  option_manager_.Parse(argc, argv.data());

  EXPECT_EQ(*option_manager_.image_path, kImagePath);
}

// Boundary / idempotence: calling AddImageOptions multiple times should be safe
// and still result in a correctly parsed image_path.
TEST_F(OptionManagerAddImageOptionsTest_35,
       AddImageOptionsIsIdempotent_35) {
  option_manager_.AddImageOptions();
  option_manager_.AddImageOptions();  // Should have no adverse effect.

  ASSERT_NE(option_manager_.image_path, nullptr);

  const std::string kImagePath = "/tmp/test_images_idempotent_35";

  std::vector<std::string> args = {
      "glomap_test_35",
      "--image_path",
      kImagePath,
  };
  int argc = 0;
  std::vector<char*> argv;
  BuildArgv(args, &argc, &argv);

  option_manager_.Parse(argc, argv.data());

  EXPECT_EQ(*option_manager_.image_path, kImagePath);
}

// Error case: image_path is registered as a required option,
// so calling Parse without providing it should cause the process to exit
// with failure.
TEST_F(OptionManagerAddImageOptionsTest_35,
       MissingImagePathOptionCausesParseFailure_35) {
  option_manager_.AddImageOptions();

  std::vector<std::string> args = {
      "glomap_test_35",  // No --image_path provided
  };
  int argc = 0;
  std::vector<char*> argv;
  BuildArgv(args, &argc, &argv);

  // Parse is expected to terminate the process with EXIT_FAILURE
  // when required options are missing.
  ASSERT_EXIT(option_manager_.Parse(argc, argv.data()),
              ::testing::ExitedWithCode(EXIT_FAILURE),
              ".*");
}

}  // namespace
