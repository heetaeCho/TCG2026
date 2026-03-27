// parseargs_test_2737.cc
#include <gtest/gtest.h>

#include <cstring>
#include <string>
#include <vector>

#include "parseargs.h"  // ArgDesc, ArgKind, parseArgs()

namespace {

struct ArgvBuilder {
  std::vector<std::string> storage;
  std::vector<char *> argv; // includes trailing nullptr for convenience

  explicit ArgvBuilder(std::initializer_list<const char *> items) {
    storage.reserve(items.size());
    argv.reserve(items.size() + 1);
    for (const char *s : items) {
      storage.emplace_back(s ? s : "");
    }
    for (auto &str : storage) {
      // parseArgs expects char* argv[]; it only shifts pointers and compares strings.
      argv.push_back(const_cast<char *>(str.c_str()));
    }
    argv.push_back(nullptr);
  }

  char **data() { return argv.data(); }
};

const ArgDesc *EmptyArgDescs() {
  // Sentinel-only array: ensures findArg can iterate safely without relying on nullptr args.
  static ArgDesc empty[] = {
      {nullptr, static_cast<ArgKind>(0), nullptr, nullptr},
  };
  return empty;
}

} // namespace

class ParseArgsTest_2737 : public ::testing::Test {};

// Normal: if "--" is present, parseArgs must remove it, shift argv left, decrement argc, and stop parsing.
TEST_F(ParseArgsTest_2737, RemovesDoubleDashAndShiftsRemainingArguments_2737) {
  ArgvBuilder b({"prog", "a", "--", "b", "c"});
  int argc = 5;

  const bool ok = parseArgs(EmptyArgDescs(), &argc, b.data());

  EXPECT_TRUE(ok);
  ASSERT_EQ(argc, 4); // "--" removed

  EXPECT_STREQ(b.data()[0], "prog");
  EXPECT_STREQ(b.data()[1], "a");
  EXPECT_STREQ(b.data()[2], "b");
  EXPECT_STREQ(b.data()[3], "c");
}

// Boundary: "--" immediately after program name.
TEST_F(ParseArgsTest_2737, RemovesDoubleDashWhenItIsFirstNonProgramArgument_2737) {
  ArgvBuilder b({"prog", "--", "x"});
  int argc = 3;

  const bool ok = parseArgs(EmptyArgDescs(), &argc, b.data());

  EXPECT_TRUE(ok);
  ASSERT_EQ(argc, 2);

  EXPECT_STREQ(b.data()[0], "prog");
  EXPECT_STREQ(b.data()[1], "x");
}

// Boundary: "--" as the last argument => only argc decreases, nothing else to shift.
TEST_F(ParseArgsTest_2737, RemovesDoubleDashWhenItIsLastArgument_2737) {
  ArgvBuilder b({"prog", "x", "--"});
  int argc = 3;

  const bool ok = parseArgs(EmptyArgDescs(), &argc, b.data());

  EXPECT_TRUE(ok);
  ASSERT_EQ(argc, 2);

  EXPECT_STREQ(b.data()[0], "prog");
  EXPECT_STREQ(b.data()[1], "x");
}

// Boundary: no arguments besides program name => unchanged, ok remains true.
TEST_F(ParseArgsTest_2737, NoArgumentsDoesNothingAndReturnsTrue_2737) {
  ArgvBuilder b({"prog"});
  int argc = 1;

  const bool ok = parseArgs(EmptyArgDescs(), &argc, b.data());

  EXPECT_TRUE(ok);
  EXPECT_EQ(argc, 1);
  EXPECT_STREQ(b.data()[0], "prog");
}

// Normal: if no arg matches any ArgDesc, parseArgs should leave argv/argc unchanged and still return true.
// (We use an empty ArgDesc list so any non-"--" token is treated as non-matching.)
TEST_F(ParseArgsTest_2737, UnknownArgumentsRemainUntouchedWhenNoMatchingDescriptors_2737) {
  ArgvBuilder b({"prog", "-x", "123", "--not-sentinel", "zzz"});
  int argc = 5;

  const bool ok = parseArgs(EmptyArgDescs(), &argc, b.data());

  EXPECT_TRUE(ok);
  EXPECT_EQ(argc, 5);

  EXPECT_STREQ(b.data()[0], "prog");
  EXPECT_STREQ(b.data()[1], "-x");
  EXPECT_STREQ(b.data()[2], "123");
  EXPECT_STREQ(b.data()[3], "--not-sentinel");
  EXPECT_STREQ(b.data()[4], "zzz");
}

// Boundary/behavioral: only the first "--" should be removed because parseArgs breaks after handling it.
TEST_F(ParseArgsTest_2737, StopsParsingAtFirstDoubleDashOnlyFirstIsRemoved_2737) {
  ArgvBuilder b({"prog", "a", "--", "b", "--", "c"});
  int argc = 6;

  const bool ok = parseArgs(EmptyArgDescs(), &argc, b.data());

  EXPECT_TRUE(ok);
  ASSERT_EQ(argc, 5);

  // After removing the first "--", the later "--" should still be present.
  EXPECT_STREQ(b.data()[0], "prog");
  EXPECT_STREQ(b.data()[1], "a");
  EXPECT_STREQ(b.data()[2], "b");
  EXPECT_STREQ(b.data()[3], "--");
  EXPECT_STREQ(b.data()[4], "c");
}