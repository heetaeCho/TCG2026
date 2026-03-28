// TEST_ID: 540
// File: ./TestProjects/yaml-cpp/test/emitter_write_tag_test.cpp

#include <gtest/gtest.h>

#include <sstream>
#include <string>

#include "yaml-cpp/emitter.h"
#include "yaml-cpp/emittermanip.h"

namespace {

class WriteTagTest_540 : public ::testing::Test {
 protected:
  static std::string StrOrEmpty_540(const char* s) { return s ? std::string(s) : std::string(); }
};

TEST_F(WriteTagTest_540, ReturnsSelfReference_540) {
  std::stringstream ss;
  YAML::Emitter emitter(ss);

  YAML::_Tag tag("!", "foo", YAML::_Tag::Type::Verbatim);

  YAML::Emitter& ret = emitter.Write(tag);
  EXPECT_EQ(&ret, &emitter);
}

TEST_F(WriteTagTest_540, WritesVerbatimTagToProvidedStreamAndStaysGood_540) {
  std::stringstream ss;
  YAML::Emitter emitter(ss);

  YAML::_Tag tag("!", "mytag", YAML::_Tag::Type::Verbatim);
  emitter.Write(tag);

  EXPECT_TRUE(emitter.good()) << emitter.GetLastError();
  EXPECT_TRUE(emitter.GetLastError().empty());

  const std::string out = ss.str();
  EXPECT_FALSE(out.empty());
}

TEST_F(WriteTagTest_540, WritesPrimaryHandleTagToProvidedStreamAndStaysGood_540) {
  std::stringstream ss;
  YAML::Emitter emitter(ss);

  // Primary handle tags typically look like "!!something".
  YAML::_Tag tag("!!", "map", YAML::_Tag::Type::PrimaryHandle);
  emitter.Write(tag);

  EXPECT_TRUE(emitter.good()) << emitter.GetLastError();
  EXPECT_TRUE(emitter.GetLastError().empty());

  const std::string out = ss.str();
  EXPECT_FALSE(out.empty());
}

TEST_F(WriteTagTest_540, WritingSecondTagSetsInvalidTagError_540) {
  std::stringstream ss;
  YAML::Emitter emitter(ss);

  YAML::_Tag tag1("!", "t1", YAML::_Tag::Type::Verbatim);
  YAML::_Tag tag2("!", "t2", YAML::_Tag::Type::Verbatim);

  emitter.Write(tag1);
  ASSERT_TRUE(emitter.good()) << emitter.GetLastError();

  const std::string before = ss.str();

  emitter.Write(tag2);

  EXPECT_FALSE(emitter.good());
  EXPECT_EQ(emitter.GetLastError(), std::string("invalid tag"));

  // Once the error occurs, the observable output should not grow due to the failed write.
  const std::string after = ss.str();
  EXPECT_EQ(after, before);
}

TEST_F(WriteTagTest_540, WhenAlreadyInErrorStateWriteDoesNotChangeOutput_540) {
  std::stringstream ss;
  YAML::Emitter emitter(ss);

  YAML::_Tag tag1("!", "t1", YAML::_Tag::Type::Verbatim);
  YAML::_Tag tag2("!", "t2", YAML::_Tag::Type::Verbatim);

  emitter.Write(tag1);
  emitter.Write(tag2);  // forces "invalid tag"
  ASSERT_FALSE(emitter.good());
  ASSERT_EQ(emitter.GetLastError(), std::string("invalid tag"));

  const std::string before = ss.str();

  // Attempt another write while not good: should be a no-op (observable via output).
  YAML::_Tag tag3("!", "t3", YAML::_Tag::Type::Verbatim);
  emitter.Write(tag3);

  EXPECT_FALSE(emitter.good());
  EXPECT_EQ(emitter.GetLastError(), std::string("invalid tag"));
  EXPECT_EQ(ss.str(), before);
}

TEST_F(WriteTagTest_540, WorksWithDefaultEmitterBuffer_540) {
  YAML::Emitter emitter;  // uses internal buffer

  YAML::_Tag tag("!", "local", YAML::_Tag::Type::Verbatim);
  emitter.Write(tag);

  EXPECT_TRUE(emitter.good()) << emitter.GetLastError();

  EXPECT_NE(emitter.size(), 0u);
  EXPECT_FALSE(StrOrEmpty_540(emitter.c_str()).empty());
}

TEST_F(WriteTagTest_540, EmptyContentDoesNotCrashAndKeepsInterfaceConsistent_540) {
  std::stringstream ss;
  YAML::Emitter emitter(ss);

  YAML::_Tag tag("!", "", YAML::_Tag::Type::Verbatim);
  emitter.Write(tag);

  // We only assert that the call is safe and the interface remains usable.
  // Whether this is considered an error is implementation-defined; we don't infer it.
  (void)emitter.good();
  (void)emitter.GetLastError();
  (void)ss.str();
}

}  // namespace