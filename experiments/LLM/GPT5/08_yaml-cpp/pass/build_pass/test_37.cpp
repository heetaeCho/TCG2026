// File: test/emitter_operator_string_test_37.cpp

#include <gtest/gtest.h>

#include <sstream>
#include <string>

#include "yaml-cpp/emitter.h"

namespace {

static std::string EmitterBytes(const YAML::Emitter& e) {
  // Preserve embedded '\0' by using size().
  return std::string(e.c_str(), e.size());
}

}  // namespace

TEST(EmitterOperatorStringTest_37, ReturnsSameEmitterReference_37) {
  std::stringstream ss;
  YAML::Emitter emitter(ss);

  std::string v = "hello";

  YAML::Emitter* ret = &(emitter << v);
  EXPECT_EQ(ret, &emitter);
}

TEST(EmitterOperatorStringTest_37, WritesStringToEmitterBuffer_37) {
  std::stringstream ss;
  YAML::Emitter emitter(ss);

  std::string v = "abc";
  emitter << v;

  EXPECT_EQ(EmitterBytes(emitter), "abc");
}

TEST(EmitterOperatorStringTest_37, AppendsOnMultipleInsertions_37) {
  std::stringstream ss;
  YAML::Emitter emitter(ss);

  std::string a = "A";
  std::string b = "B";
  emitter << a;
  emitter << b;

  EXPECT_EQ(EmitterBytes(emitter), "AB");
}

TEST(EmitterOperatorStringTest_37, HandlesEmptyString_37) {
  std::stringstream ss;
  YAML::Emitter emitter(ss);

  const std::string before = EmitterBytes(emitter);

  std::string empty;
  emitter << empty;

  // Should be safe to write an empty string; observable result should not add bytes.
  EXPECT_EQ(EmitterBytes(emitter), before);
}

TEST(EmitterOperatorStringTest_37, PreservesEmbeddedNullBytes_37) {
  std::stringstream ss;
  YAML::Emitter emitter(ss);

  std::string with_null;
  with_null.push_back('x');
  with_null.push_back('\0');
  with_null.push_back('y');

  emitter << with_null;

  const std::string out = EmitterBytes(emitter);
  ASSERT_EQ(out.size(), with_null.size());
  EXPECT_EQ(out[0], 'x');
  EXPECT_EQ(out[1], '\0');
  EXPECT_EQ(out[2], 'y');
}

TEST(EmitterOperatorStringTest_37, SupportsChaining_37) {
  std::stringstream ss;
  YAML::Emitter emitter(ss);

  std::string a = "foo";
  std::string b = "bar";

  emitter << a << b;

  EXPECT_EQ(EmitterBytes(emitter), "foobar");
}

TEST(EmitterOperatorStringTest_37, DoesNotThrowWhenStreamIsBad_37) {
  std::stringstream ss;
  ss.setstate(std::ios::badbit);  // make the underlying stream "bad"
  YAML::Emitter emitter(ss);

  std::string v = "data";

  EXPECT_NO_THROW({
    YAML::Emitter* ret = &(emitter << v);
    EXPECT_EQ(ret, &emitter);
  });
}
