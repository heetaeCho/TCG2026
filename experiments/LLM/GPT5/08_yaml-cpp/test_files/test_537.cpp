// TEST_ID: 537
#include <gtest/gtest.h>

#include <sstream>
#include <string>

#include "yaml-cpp/emitter.h"

namespace {

class WriteCharTest_537 : public ::testing::Test {
 protected:
  static std::string EmitToString(char ch) {
    std::stringstream ss;
    YAML::Emitter out(ss);
    out.Write(ch);
    return ss.str();
  }

  static std::string EmitToString(const std::string& s) {
    std::stringstream ss;
    YAML::Emitter out(ss);
    for (char ch : s) out.Write(ch);
    return ss.str();
  }
};

TEST_F(WriteCharTest_537, ReturnsSelfForChaining_537) {
  std::stringstream ss;
  YAML::Emitter out(ss);

  YAML::Emitter& ref = out.Write('a');
  EXPECT_EQ(&ref, &out);

  YAML::Emitter& ref2 = out.Write('b');
  EXPECT_EQ(&ref2, &out);

  EXPECT_EQ(ss.str(), "ab");
}

TEST_F(WriteCharTest_537, WritesSingleChar_AppendsToOutput_537) {
  std::stringstream ss;
  YAML::Emitter out(ss);

  out.Write('x');

  EXPECT_EQ(ss.str(), "x");
  EXPECT_GE(out.size(), std::size_t{1});
  ASSERT_NE(out.c_str(), nullptr);
  EXPECT_NE(std::string(out.c_str()).find('x'), std::string::npos);
}

TEST_F(WriteCharTest_537, WritesMultipleChars_AppendsInOrder_537) {
  std::stringstream ss;
  YAML::Emitter out(ss);

  out.Write('a').Write('b').Write('c');

  EXPECT_EQ(ss.str(), "abc");
  EXPECT_GE(out.size(), std::size_t{3});
  ASSERT_NE(out.c_str(), nullptr);
  EXPECT_NE(std::string(out.c_str()).find("abc"), std::string::npos);
}

TEST_F(WriteCharTest_537, Boundary_WritesNewlineChar_537) {
  std::stringstream ss;
  YAML::Emitter out(ss);

  out.Write('\n');

  EXPECT_EQ(ss.str(), "\n");
  EXPECT_GE(out.size(), std::size_t{1});
}

TEST_F(WriteCharTest_537, ErrorCase_StreamInBadState_DoesNotWriteToStream_537) {
  std::stringstream ss;
  ss.setstate(std::ios::badbit);  // Force stream to be non-writable.

  YAML::Emitter out(ss);

  out.Write('a');
  out.Write('b');

  // Observable behavior: nothing should have been written to the underlying stream.
  EXPECT_TRUE(ss.str().empty());
}

TEST_F(WriteCharTest_537, ErrorCase_StreamInFailState_DoesNotWriteToStream_537) {
  std::stringstream ss;
  ss.setstate(std::ios::failbit);  // Another common error state.

  YAML::Emitter out(ss);

  out.Write('z');

  EXPECT_TRUE(ss.str().empty());
}

}  // namespace