// File: cgroup_subsys_parse_test_150.cc

#include "gtest/gtest.h"

#include <string>
#include <vector>

// Adjust this include as appropriate for your project structure.
// In upstream ninja, CGroupSubSys is defined in util.cc, but usually
// there is a header (e.g., "util.h") that declares it.
#include "util.h"

using std::string;
using std::vector;

class CGroupSubSysTest_150 : public ::testing::Test {
protected:
  CGroupSubSys cgroup_;
};

TEST_F(CGroupSubSysTest_150, ParseValidLineWithMultipleSubsystems_150) {
  // Normal case: multiple subsystems, simple name.
  string line = "7:cpu,cpuacct:/";

  bool result = cgroup_.parse(line);

  EXPECT_TRUE(result);
  EXPECT_EQ(7, cgroup_.id);
  EXPECT_EQ(string("/"), cgroup_.name);

  ASSERT_EQ(2u, cgroup_.subsystems.size());
  EXPECT_EQ(string("cpu"), cgroup_.subsystems[0]);
  EXPECT_EQ(string("cpuacct"), cgroup_.subsystems[1]);
}

TEST_F(CGroupSubSysTest_150, ParseValidLineWithSingleSubsystem_150) {
  // Normal case: single subsystem.
  string line = "5:memory:/user.slice";

  bool result = cgroup_.parse(line);

  EXPECT_TRUE(result);
  EXPECT_EQ(5, cgroup_.id);
  EXPECT_EQ(string("/user.slice"), cgroup_.name);

  ASSERT_EQ(1u, cgroup_.subsystems.size());
  EXPECT_EQ(string("memory"), cgroup_.subsystems[0]);
}

TEST_F(CGroupSubSysTest_150, ParseValidLineNameContainsColon_150) {
  // Boundary-style case: name part itself contains ':'.
  // The parser should treat only the first two ':' as separators.
  string line = "3:blkio:/foo:bar";

  bool result = cgroup_.parse(line);

  EXPECT_TRUE(result);
  EXPECT_EQ(3, cgroup_.id);
  // Everything after the second ':' belongs to the name.
  EXPECT_EQ(string("/foo:bar"), cgroup_.name);

  ASSERT_EQ(1u, cgroup_.subsystems.size());
  EXPECT_EQ(string("blkio"), cgroup_.subsystems[0]);
}

TEST_F(CGroupSubSysTest_150, ParseReturnsFalseWhenNoColonPresent_150) {
  // Error case: completely invalid format, no ':' at all.
  string line = "12345";

  bool result = cgroup_.parse(line);

  EXPECT_FALSE(result);
  // On failure we only check the return value; the contents of cgroup_
  // are not relied upon by this test.
}

TEST_F(CGroupSubSysTest_150, ParseReturnsFalseWhenSecondColonMissing_150) {
  // Error case: one colon, but missing the second one.
  string line = "7:cpu";

  bool result = cgroup_.parse(line);

  EXPECT_FALSE(result);
  // Again, we assert only the observable success/failure result.
}
