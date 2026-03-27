// TEST_ID: 42
#include <gtest/gtest.h>

#include <sstream>
#include <string>

#include "yaml-cpp/emitter.h"
#include "yaml-cpp/emittermanip.h"

namespace {

class OperatorAnchorTest_42 : public ::testing::Test {
 protected:
  static std::string SafeCStr(const YAML::Emitter& e) {
    const char* p = e.c_str();
    return p ? std::string(p) : std::string();
  }
};

TEST_F(OperatorAnchorTest_42, ReturnsSameEmitterReference_42) {
  std::stringstream ss;
  YAML::Emitter emitter(ss);

  YAML::_Anchor a("anchor");
  YAML::Emitter& ref = (emitter << a);

  EXPECT_EQ(&ref, &emitter);
}

TEST_F(OperatorAnchorTest_42, MatchesDirectWriteWithStreamCtor_NormalAnchor_42) {
  std::stringstream ss_op;
  std::stringstream ss_write;

  YAML::Emitter e_op(ss_op);
  YAML::Emitter e_write(ss_write);

  const YAML::_Anchor a("A1");

  e_op << a;
  e_write.Write(a);

  EXPECT_EQ(ss_op.str(), ss_write.str());
  EXPECT_EQ(e_op.good(), e_write.good());
  EXPECT_EQ(e_op.GetLastError(), e_write.GetLastError());
}

TEST_F(OperatorAnchorTest_42, MatchesDirectWriteWithDefaultCtor_NormalAnchor_42) {
  YAML::Emitter e_op;
  YAML::Emitter e_write;

  const YAML::_Anchor a("A2");

  e_op << a;
  e_write.Write(a);

  EXPECT_EQ(e_op.size(), e_write.size());
  EXPECT_EQ(SafeCStr(e_op), SafeCStr(e_write));
  EXPECT_EQ(e_op.good(), e_write.good());
  EXPECT_EQ(e_op.GetLastError(), e_write.GetLastError());
}

TEST_F(OperatorAnchorTest_42, MatchesDirectWrite_EmptyAnchorContent_42) {
  std::stringstream ss_op;
  std::stringstream ss_write;

  YAML::Emitter e_op(ss_op);
  YAML::Emitter e_write(ss_write);

  const YAML::_Anchor empty("");

  e_op << empty;
  e_write.Write(empty);

  EXPECT_EQ(ss_op.str(), ss_write.str());
  EXPECT_EQ(e_op.good(), e_write.good());
  EXPECT_EQ(e_op.GetLastError(), e_write.GetLastError());
}

TEST_F(OperatorAnchorTest_42, MatchesDirectWrite_SpecialCharactersInAnchor_42) {
  std::stringstream ss_op;
  std::stringstream ss_write;

  YAML::Emitter e_op(ss_op);
  YAML::Emitter e_write(ss_write);

  const YAML::_Anchor special("a b\tc:[]{}#&*?\"'\\\n");

  e_op << special;
  e_write.Write(special);

  EXPECT_EQ(ss_op.str(), ss_write.str());
  EXPECT_EQ(e_op.good(), e_write.good());
  EXPECT_EQ(e_op.GetLastError(), e_write.GetLastError());
}

TEST_F(OperatorAnchorTest_42, MatchesDirectWrite_LongAnchorContent_42) {
  std::stringstream ss_op;
  std::stringstream ss_write;

  YAML::Emitter e_op(ss_op);
  YAML::Emitter e_write(ss_write);

  const std::string long_content(4096, 'x');
  const YAML::_Anchor long_anchor(long_content);

  e_op << long_anchor;
  e_write.Write(long_anchor);

  EXPECT_EQ(ss_op.str(), ss_write.str());
  EXPECT_EQ(e_op.good(), e_write.good());
  EXPECT_EQ(e_op.GetLastError(), e_write.GetLastError());
}

TEST_F(OperatorAnchorTest_42, ChainingOperatorMatchesSequentialWrite_42) {
  std::stringstream ss_op;
  std::stringstream ss_write;

  YAML::Emitter e_op(ss_op);
  YAML::Emitter e_write(ss_write);

  const YAML::_Anchor a1("A");
  const YAML::_Anchor a2("B");

  YAML::Emitter& chained = ((e_op << a1) << a2);
  EXPECT_EQ(&chained, &e_op);

  e_write.Write(a1);
  e_write.Write(a2);

  EXPECT_EQ(ss_op.str(), ss_write.str());
  EXPECT_EQ(e_op.good(), e_write.good());
  EXPECT_EQ(e_op.GetLastError(), e_write.GetLastError());
}

TEST_F(OperatorAnchorTest_42, AcceptsTemporaryAnchorObject_MatchesDirectWrite_42) {
  std::stringstream ss_op;
  std::stringstream ss_write;

  YAML::Emitter e_op(ss_op);
  YAML::Emitter e_write(ss_write);

  e_op << YAML::_Anchor("TMP");
  e_write.Write(YAML::_Anchor("TMP"));

  EXPECT_EQ(ss_op.str(), ss_write.str());
  EXPECT_EQ(e_op.good(), e_write.good());
  EXPECT_EQ(e_op.GetLastError(), e_write.GetLastError());
}

}  // namespace
