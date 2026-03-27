// test_emitter_comment_operator_44.cpp
#include <gtest/gtest.h>

#include <sstream>
#include <string>

#include "yaml-cpp/emitter.h"
#include "yaml-cpp/emittermanip.h"

namespace {

class EmitterCommentOperatorTest_44 : public ::testing::Test {
 protected:
  static std::string MakeLongString(std::size_t n) {
    return std::string(n, 'x');
  }

  static std::string EmitWithOperator(const YAML::_Comment& c1) {
    std::stringstream ss;
    YAML::Emitter out(ss);
    out << c1;
    return std::string(out.c_str(), out.size());
  }

  static std::string EmitWithWrite(const YAML::_Comment& c1) {
    std::stringstream ss;
    YAML::Emitter out(ss);
    out.Write(c1);
    return std::string(out.c_str(), out.size());
  }

  static std::string EmitWithOperator(const YAML::_Comment& c1, const YAML::_Comment& c2) {
    std::stringstream ss;
    YAML::Emitter out(ss);
    out << c1 << c2;
    return std::string(out.c_str(), out.size());
  }

  static std::string EmitWithWrite(const YAML::_Comment& c1, const YAML::_Comment& c2) {
    std::stringstream ss;
    YAML::Emitter out(ss);
    out.Write(c1).Write(c2);
    return std::string(out.c_str(), out.size());
  }
};

TEST_F(EmitterCommentOperatorTest_44, ReturnsEmitterReference_44) {
  std::stringstream ss;
  YAML::Emitter out(ss);

  YAML::_Comment c("hello");

  YAML::Emitter& ret = (out << c);
  EXPECT_EQ(&ret, &out);
}

TEST_F(EmitterCommentOperatorTest_44, MatchesWriteSingleComment_44) {
  YAML::_Comment c("single comment");

  const std::string via_op = EmitWithOperator(c);
  const std::string via_write = EmitWithWrite(c);

  EXPECT_EQ(via_op, via_write);
}

TEST_F(EmitterCommentOperatorTest_44, SupportsChainingAndMatchesWrite_44) {
  YAML::_Comment c1("first");
  YAML::_Comment c2("second");

  const std::string via_op = EmitWithOperator(c1, c2);
  const std::string via_write = EmitWithWrite(c1, c2);

  EXPECT_EQ(via_op, via_write);
}

TEST_F(EmitterCommentOperatorTest_44, EmptyCommentMatchesWrite_44) {
  YAML::_Comment empty("");

  const std::string via_op = EmitWithOperator(empty);
  const std::string via_write = EmitWithWrite(empty);

  EXPECT_EQ(via_op, via_write);
}

TEST_F(EmitterCommentOperatorTest_44, LongCommentMatchesWrite_44) {
  YAML::_Comment long_c(MakeLongString(1u << 16));  // 65536 chars

  const std::string via_op = EmitWithOperator(long_c);
  const std::string via_write = EmitWithWrite(long_c);

  EXPECT_EQ(via_op, via_write);
}

}  // namespace
