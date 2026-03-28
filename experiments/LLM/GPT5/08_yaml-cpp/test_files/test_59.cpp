// File: test/emitter_indent_operator_test.cpp

#include <gtest/gtest.h>

#include <sstream>
#include <string>

#include "yaml-cpp/emitter.h"
#include "yaml-cpp/emittermanip.h"

namespace {

struct Snapshot {
  bool good;
  std::string err;
  std::string out;
};

static Snapshot RunWithOperatorIndent(int indent_value, const std::string& payload) {
  std::stringstream ss;
  YAML::Emitter e(ss);

  // Use the operator<< under test
  YAML::_Indent ind(indent_value);
  YAML::Emitter& ret = (e << ind);
  (void)ret;

  // Exercise observable behavior via public API
  e.Write(payload);

  Snapshot s;
  s.good = e.good();
  s.err = e.GetLastError();
  s.out = ss.str();
  return s;
}

static Snapshot RunWithDirectSetLocalIndent(int indent_value, const std::string& payload) {
  std::stringstream ss;
  YAML::Emitter e(ss);

  YAML::_Indent ind(indent_value);
  YAML::Emitter& ret = e.SetLocalIndent(ind);
  (void)ret;

  e.Write(payload);

  Snapshot s;
  s.good = e.good();
  s.err = e.GetLastError();
  s.out = ss.str();
  return s;
}

}  // namespace

// TEST_ID = 59

TEST(EmitterIndentOperatorTest_59, ReturnsSameEmitterReference_59) {
  std::stringstream ss;
  YAML::Emitter e(ss);

  YAML::_Indent ind(2);
  YAML::Emitter& ret = (e << ind);

  EXPECT_EQ(&ret, &e);
}

TEST(EmitterIndentOperatorTest_59, IsChainableWithWrite_59) {
  std::stringstream ss;
  YAML::Emitter e(ss);

  YAML::_Indent ind(4);
  YAML::Emitter& ret = ((e << ind).Write("hello", 5));

  EXPECT_EQ(&ret, &e);
  EXPECT_EQ(ss.str(), "hello");
}

TEST(EmitterIndentOperatorTest_59, MatchesDirectSetLocalIndentForZero_59) {
  const auto via_op = RunWithOperatorIndent(0, "x");
  const auto via_direct = RunWithDirectSetLocalIndent(0, "x");

  EXPECT_EQ(via_op.good, via_direct.good);
  EXPECT_EQ(via_op.err, via_direct.err);
  EXPECT_EQ(via_op.out, via_direct.out);
}

TEST(EmitterIndentOperatorTest_59, MatchesDirectSetLocalIndentForPositiveIndent_59) {
  const auto via_op = RunWithOperatorIndent(2, "payload");
  const auto via_direct = RunWithDirectSetLocalIndent(2, "payload");

  EXPECT_EQ(via_op.good, via_direct.good);
  EXPECT_EQ(via_op.err, via_direct.err);
  EXPECT_EQ(via_op.out, via_direct.out);
}

TEST(EmitterIndentOperatorTest_59, MatchesDirectSetLocalIndentForNegativeIndent_59) {
  // Boundary / potential error-case input: negative indent.
  const auto via_op = RunWithOperatorIndent(-1, "z");
  const auto via_direct = RunWithDirectSetLocalIndent(-1, "z");

  // We don't assume whether this is accepted or rejected; we only require the operator
  // path to behave the same as the direct API path (observable via public methods).
  EXPECT_EQ(via_op.good, via_direct.good);
  EXPECT_EQ(via_op.err, via_direct.err);
  EXPECT_EQ(via_op.out, via_direct.out);
}

TEST(EmitterIndentOperatorTest_59, MatchesDirectSetLocalIndentForLargeIndent_59) {
  // Boundary input: very large indent.
  const int kLargeIndent = 1'000'000;

  const auto via_op = RunWithOperatorIndent(kLargeIndent, "data");
  const auto via_direct = RunWithDirectSetLocalIndent(kLargeIndent, "data");

  EXPECT_EQ(via_op.good, via_direct.good);
  EXPECT_EQ(via_op.err, via_direct.err);
  EXPECT_EQ(via_op.out, via_direct.out);
}

TEST(EmitterIndentOperatorTest_59, OperatorDoesNotPreventSubsequentWrites_59) {
  std::stringstream ss;
  YAML::Emitter e(ss);

  YAML::_Indent ind(3);
  e << ind;

  // Multiple writes should still be possible via the public API.
  e.Write("A");
  e.Write('B');
  e.Write(std::string("C"));

  EXPECT_EQ(ss.str(), "ABC");
}

TEST(EmitterIndentOperatorTest_59, OperatorAndDirectCallStayConsistentAfterMultipleWrites_59) {
  const std::string payload1 = "one";
  const std::string payload2 = "two";

  // Operator path
  std::stringstream ss_op;
  YAML::Emitter e_op(ss_op);
  e_op << YAML::_Indent(1);
  e_op.Write(payload1);
  e_op.Write(payload2);
  const bool good_op = e_op.good();
  const std::string err_op = e_op.GetLastError();
  const std::string out_op = ss_op.str();

  // Direct path
  std::stringstream ss_direct;
  YAML::Emitter e_direct(ss_direct);
  e_direct.SetLocalIndent(YAML::_Indent(1));
  e_direct.Write(payload1);
  e_direct.Write(payload2);
  const bool good_direct = e_direct.good();
  const std::string err_direct = e_direct.GetLastError();
  const std::string out_direct = ss_direct.str();

  EXPECT_EQ(good_op, good_direct);
  EXPECT_EQ(err_op, err_direct);
  EXPECT_EQ(out_op, out_direct);
}
