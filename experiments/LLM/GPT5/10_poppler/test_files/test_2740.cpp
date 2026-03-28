// grabArg_test_2740.cc
#include <gtest/gtest.h>

#include <cstring>
#include <string>

// Include the public interface first.
#include "utils/parseargs.h"

// Include implementation to access the static grabArg() in this TU.
#include "utils/parseargs.cc"

class GrabArgTest_2740 : public ::testing::Test {
protected:
  // Helper to build a mutable argv array (char*) from string literals.
  // Note: We only mutate the pointers (argv[i] = argv[i+n]) in grabArg,
  // not the pointed-to strings, so string literals are fine here.
  static void BuildArgv(const std::initializer_list<const char *> &in,
                        std::vector<char *> *out) {
    out->clear();
    out->reserve(in.size());
    for (auto *s : in) {
      out->push_back(const_cast<char *>(s));
    }
  }
};

TEST_F(GrabArgTest_2740, FlagSetsBoolTrueAndConsumesOneArg_2740) {
  bool flag = false;

  ArgDesc desc{};
  desc.kind = argFlag;
  desc.val = &flag;

  std::vector<char *> argvv;
  BuildArgv({"prog", "-flag", "rest"}, &argvv);
  int argc = static_cast<int>(argvv.size());

  ASSERT_FALSE(flag);

  const bool ok = grabArg(&desc, /*i=*/1, &argc, argvv.data());

  EXPECT_TRUE(ok);
  EXPECT_TRUE(flag);
  EXPECT_EQ(argc, 2);                 // consumed "-flag"
  EXPECT_STREQ(argvv[0], "prog");
  EXPECT_STREQ(argvv[1], "rest");     // shifted left
}

TEST_F(GrabArgTest_2740, IntParsesAndConsumesTwoArgs_2740) {
  int value = 0;

  ArgDesc desc{};
  desc.kind = argInt;
  desc.val = &value;

  std::vector<char *> argvv;
  BuildArgv({"prog", "-n", "123", "rest"}, &argvv);
  int argc = static_cast<int>(argvv.size());

  const bool ok = grabArg(&desc, /*i=*/1, &argc, argvv.data());

  EXPECT_TRUE(ok);
  EXPECT_EQ(value, 123);
  EXPECT_EQ(argc, 2);                 // consumed "-n" "123"
  EXPECT_STREQ(argvv[0], "prog");
  EXPECT_STREQ(argvv[1], "rest");
}

TEST_F(GrabArgTest_2740, IntMissingValueReturnsFalseAndConsumesOnlyOption_2740) {
  int value = 77;

  ArgDesc desc{};
  desc.kind = argInt;
  desc.val = &value;

  std::vector<char *> argvv;
  BuildArgv({"prog", "-n"}, &argvv);
  int argc = static_cast<int>(argvv.size());

  const bool ok = grabArg(&desc, /*i=*/1, &argc, argvv.data());

  EXPECT_FALSE(ok);
  EXPECT_EQ(argc, 1);                 // consumed "-n" only
  EXPECT_STREQ(argvv[0], "prog");
  // Value may or may not change depending on implementation; only verify observable ok/argc shift.
}

TEST_F(GrabArgTest_2740, IntNonIntValueReturnsFalseConsumesOnlyOptionKeepsValueArg_2740) {
  int value = 5;

  ArgDesc desc{};
  desc.kind = argInt;
  desc.val = &value;

  std::vector<char *> argvv;
  BuildArgv({"prog", "-n", "abc", "rest"}, &argvv);
  int argc = static_cast<int>(argvv.size());

  const bool ok = grabArg(&desc, /*i=*/1, &argc, argvv.data());

  EXPECT_FALSE(ok);
  EXPECT_EQ(argc, 3);                 // consumed "-n" only
  EXPECT_STREQ(argvv[0], "prog");
  EXPECT_STREQ(argvv[1], "abc");      // value arg shifted into option position
  EXPECT_STREQ(argvv[2], "rest");
}

TEST_F(GrabArgTest_2740, FpParsesAndConsumesTwoArgs_2740) {
  double value = 0.0;

  ArgDesc desc{};
  desc.kind = argFP;
  desc.val = &value;

  std::vector<char *> argvv;
  BuildArgv({"prog", "-x", "3.5", "rest"}, &argvv);
  int argc = static_cast<int>(argvv.size());

  const bool ok = grabArg(&desc, /*i=*/1, &argc, argvv.data());

  EXPECT_TRUE(ok);
  EXPECT_DOUBLE_EQ(value, 3.5);
  EXPECT_EQ(argc, 2);
  EXPECT_STREQ(argvv[1], "rest");
}

TEST_F(GrabArgTest_2740, FpInvalidReturnsFalseConsumesOnlyOption_2740) {
  double value = 9.0;

  ArgDesc desc{};
  desc.kind = argFP;
  desc.val = &value;

  std::vector<char *> argvv;
  BuildArgv({"prog", "-x", "not-a-fp", "rest"}, &argvv);
  int argc = static_cast<int>(argvv.size());

  const bool ok = grabArg(&desc, /*i=*/1, &argc, argvv.data());

  EXPECT_FALSE(ok);
  EXPECT_EQ(argc, 3);                 // consumed "-x" only
  EXPECT_STREQ(argvv[1], "not-a-fp");
  EXPECT_STREQ(argvv[2], "rest");
}

TEST_F(GrabArgTest_2740, StringCopiesAndNullTerminatesAndConsumesTwoArgs_2740) {
  char buf[8];
  std::memset(buf, 'Z', sizeof(buf));

  ArgDesc desc{};
  desc.kind = argString;
  desc.val = buf;
  desc.size = sizeof(buf);

  std::vector<char *> argvv;
  BuildArgv({"prog", "-s", "hello", "rest"}, &argvv);
  int argc = static_cast<int>(argvv.size());

  const bool ok = grabArg(&desc, /*i=*/1, &argc, argvv.data());

  EXPECT_TRUE(ok);
  EXPECT_STREQ(buf, "hello");
  EXPECT_EQ(argc, 2);
  EXPECT_STREQ(argvv[1], "rest");
}

TEST_F(GrabArgTest_2740, StringTruncatesToSizeMinusOneAndNullTerminates_2740) {
  char buf[4]; // can store up to 3 chars + '\0'
  std::memset(buf, 'X', sizeof(buf));

  ArgDesc desc{};
  desc.kind = argString;
  desc.val = buf;
  desc.size = sizeof(buf);

  std::vector<char *> argvv;
  BuildArgv({"prog", "-s", "abcdef", "rest"}, &argvv);
  int argc = static_cast<int>(argvv.size());

  const bool ok = grabArg(&desc, /*i=*/1, &argc, argvv.data());

  EXPECT_TRUE(ok);
  EXPECT_STREQ(buf, "abc");           // truncated
  EXPECT_EQ(argc, 2);
  EXPECT_STREQ(argvv[1], "rest");
}

TEST_F(GrabArgTest_2740, StringWithSizeOneBecomesEmptyString_2740) {
  char buf[1];
  buf[0] = 'Q';

  ArgDesc desc{};
  desc.kind = argString;
  desc.val = buf;
  desc.size = sizeof(buf);

  std::vector<char *> argvv;
  BuildArgv({"prog", "-s", "x", "rest"}, &argvv);
  int argc = static_cast<int>(argvv.size());

  const bool ok = grabArg(&desc, /*i=*/1, &argc, argvv.data());

  EXPECT_TRUE(ok);
  EXPECT_STREQ(buf, "");              // size-1 == 0 => always '\0'
  EXPECT_EQ(argc, 2);
  EXPECT_STREQ(argvv[1], "rest");
}

TEST_F(GrabArgTest_2740, StringMissingValueReturnsFalseConsumesOnlyOption_2740) {
  char buf[8];
  std::strcpy(buf, "orig");

  ArgDesc desc{};
  desc.kind = argString;
  desc.val = buf;
  desc.size = sizeof(buf);

  std::vector<char *> argvv;
  BuildArgv({"prog", "-s"}, &argvv);
  int argc = static_cast<int>(argvv.size());

  const bool ok = grabArg(&desc, /*i=*/1, &argc, argvv.data());

  EXPECT_FALSE(ok);
  EXPECT_EQ(argc, 1);
  EXPECT_STREQ(argvv[0], "prog");
}

TEST_F(GrabArgTest_2740, GooStringAssignsAndConsumesTwoArgs_2740) {
  GooString gs("old");

  ArgDesc desc{};
  desc.kind = argGooString;
  desc.val = &gs;

  std::vector<char *> argvv;
  BuildArgv({"prog", "-g", "new-value", "rest"}, &argvv);
  int argc = static_cast<int>(argvv.size());

  const bool ok = grabArg(&desc, /*i=*/1, &argc, argvv.data());

  EXPECT_TRUE(ok);
  EXPECT_STREQ(gs.c_str(), "new-value");
  EXPECT_EQ(argc, 2);
  EXPECT_STREQ(argvv[1], "rest");
}

TEST_F(GrabArgTest_2740, GooStringMissingValueReturnsFalseConsumesOnlyOption_2740) {
  GooString gs("keep");

  ArgDesc desc{};
  desc.kind = argGooString;
  desc.val = &gs;

  std::vector<char *> argvv;
  BuildArgv({"prog", "-g"}, &argvv);
  int argc = static_cast<int>(argvv.size());

  const bool ok = grabArg(&desc, /*i=*/1, &argc, argvv.data());

  EXPECT_FALSE(ok);
  EXPECT_EQ(argc, 1);
  EXPECT_STREQ(argvv[0], "prog");
  EXPECT_STREQ(gs.c_str(), "keep");
}

TEST_F(GrabArgTest_2740, UnknownKindConsumesOneArgAndWritesError_2740) {
  bool dummy = false;

  ArgDesc desc{};
  desc.kind = static_cast<ArgKind>(9999); // force default:
  desc.val = &dummy;

  std::vector<char *> argvv;
  BuildArgv({"prog", "-weird", "rest"}, &argvv);
  int argc = static_cast<int>(argvv.size());

  testing::internal::CaptureStderr();
  const bool ok = grabArg(&desc, /*i=*/1, &argc, argvv.data());
  const std::string err = testing::internal::GetCapturedStderr();

  EXPECT_TRUE(ok);          // ok remains true in the default branch
  EXPECT_EQ(argc, 2);       // consumed "-weird" only
  EXPECT_STREQ(argvv[1], "rest");
  EXPECT_NE(err.find("Internal error in arg table"), std::string::npos);
}