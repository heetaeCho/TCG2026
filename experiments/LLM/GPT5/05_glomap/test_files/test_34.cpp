// File: ./TestProjects/glomap/tests/option_manager_add_database_options_test_34.cc

#include <gtest/gtest.h>

#include "glomap/controllers/option_manager.h"

namespace glomap {

class OptionManagerTest_34 : public ::testing::Test {
 protected:
  OptionManagerTest_34()
      : option_manager_(/*add_project_options=*/false) {}

  void SetUp() override {
    // Ensure a clean state before each test. This only uses the public API.
    option_manager_.Reset();
  }

  OptionManager option_manager_;
};

// Normal operation:
// Verifies that after registering database options, parsing a command line
// with --database_path sets the public database_path member.
TEST_F(OptionManagerTest_34, ParseSetsDatabasePathWhenOptionRegistered_34) {
  option_manager_.AddDatabaseOptions();

  const std::string kDbPath = "database_34.db";  // No directory component.

  const char* argv[] = {"glomap_test_34", "--database_path", kDbPath.c_str()};
  const int argc = static_cast<int>(sizeof(argv) / sizeof(argv[0]));

  // Act: parse options through the public interface.
  option_manager_.Parse(argc, const_cast<char**>(argv));

  // Assert: observable state via public member.
  ASSERT_NE(option_manager_.database_path, nullptr);
  EXPECT_EQ(kDbPath, *option_manager_.database_path);
}

// Boundary / idempotence:
// Calling AddDatabaseOptions multiple times should be safe and effectively a
// no-op after the first call (no duplicate registration / no crash).
TEST_F(OptionManagerTest_34, MultipleCallsAreIdempotent_34) {
  const std::string kDbPath = "database_twice_34.db";

  // First registration.
  option_manager_.AddDatabaseOptions();
  // Second registration should be ignored via the public API contract.
  option_manager_.AddDatabaseOptions();

  const char* argv[] = {"glomap_test_34", "--database_path", kDbPath.c_str()};
  const int argc = static_cast<int>(sizeof(argv) / sizeof(argv[0]));

  // Should still parse successfully.
  option_manager_.Parse(argc, const_cast<char**>(argv));

  ASSERT_NE(option_manager_.database_path, nullptr);
  EXPECT_EQ(kDbPath, *option_manager_.database_path);
}

// Interaction / boundary condition:
// AddAllOptions already registers the database option internally.
// An additional explicit AddDatabaseOptions() call must not break parsing.
TEST_F(OptionManagerTest_34, AddAllOptionsThenAddDatabaseOptionsStillParses_34) {
  const std::string kDbPath = "database_all_options_34.db";

  // Register all options (including database options) via public API.
  option_manager_.AddAllOptions();
  // Calling AddDatabaseOptions again should be a no-op.
  option_manager_.AddDatabaseOptions();

  const char* argv[] = {"glomap_test_34", "--database_path", kDbPath.c_str()};
  const int argc = static_cast<int>(sizeof(argv) / sizeof(argv[0]));

  option_manager_.Parse(argc, const_cast<char**>(argv));

  ASSERT_NE(option_manager_.database_path, nullptr);
  EXPECT_EQ(kDbPath, *option_manager_.database_path);
}

}  // namespace glomap
