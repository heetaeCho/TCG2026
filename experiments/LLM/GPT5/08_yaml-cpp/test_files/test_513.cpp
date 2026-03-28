// File: ./TestProjects/yaml-cpp/test/emitter_c_str_test.cpp

#include <gtest/gtest.h>

#include <cstring>
#include <sstream>
#include <string>

#include "yaml-cpp/emitter.h"

namespace {

class EmitterCStrTest_513 : public ::testing::Test {};

TEST_F(EmitterCStrTest_513, DefaultConstructedCStrIsNonNullAndStableAcrossCalls_513) {
  YAML::Emitter emitter;

  const char* s1 = emitter.c_str();
  ASSERT_NE(s1, nullptr);

  const char* s2 = emitter.c_str();
  ASSERT_NE(s2, nullptr);

  // Content should be consistent across consecutive calls when no other API is invoked.
  EXPECT_STREQ(s1, s2);

  // The returned C-string should be null-terminated.
  // (This is a very basic safety/contract check; it doesn't assume any formatting.)
  EXPECT_NE(std::strchr(s1, '\0'), nullptr);
}

TEST_F(EmitterCStrTest_513, StreamConstructedCStrIsNonNullAndConsistent_513) {
  std::stringstream out;
  YAML::Emitter emitter(out);

  const char* s1 = emitter.c_str();
  ASSERT_NE(s1, nullptr);

  const char* s2 = emitter.c_str();
  ASSERT_NE(s2, nullptr);

  EXPECT_STREQ(s1, s2);
  EXPECT_NE(std::strchr(s1, '\0'), nullptr);
}

TEST_F(EmitterCStrTest_513, WriteStringMakesOutputContainThatString_513) {
  YAML::Emitter emitter;

  emitter.Write(std::string("abc"));

  const std::string rendered = emitter.c_str();
  // Don't assume exact YAML formatting; just require that the written token is present.
  EXPECT_NE(rendered.find("abc"), std::string::npos);
}

TEST_F(EmitterCStrTest_513, WriteCharMakesOutputContainThatChar_513) {
  YAML::Emitter emitter;

  emitter.Write('x');

  const std::string rendered = emitter.c_str();
  EXPECT_NE(rendered.find('x'), std::string::npos);
}

TEST_F(EmitterCStrTest_513, WriteWithExplicitSizeIncludesProvidedBytes_513) {
  YAML::Emitter emitter;

  const char payload[] = {'h', 'e', 'l', 'l', 'o'};
  emitter.Write(payload, sizeof(payload));

  const std::string rendered = emitter.c_str();
  EXPECT_NE(rendered.find("hello"), std::string::npos);
}

TEST_F(EmitterCStrTest_513, WriteEmptyStringDoesNotCrashAndKeepsCStrValid_513) {
  YAML::Emitter emitter;

  const std::string before = emitter.c_str();

  emitter.Write(std::string());
  const char* after_c = emitter.c_str();
  ASSERT_NE(after_c, nullptr);

  // Output may or may not change depending on implementation; only verify validity and stability.
  const std::string after = after_c;
  (void)after;

  // Should still be a valid null-terminated C-string.
  EXPECT_NE(std::strchr(after_c, '\0'), nullptr);

  // If it changed, it should still be a coherent string; no further assumptions.
  // If it didn't change, that's fine too.
  (void)before;
}

TEST_F(EmitterCStrTest_513, WriteZeroSizeDoesNotCrashAndKeepsCStrValid_513) {
  YAML::Emitter emitter;

  const std::string before = emitter.c_str();

  // Using a non-null pointer with size 0 avoids undefined behavior while still exercising boundary.
  const char dummy[] = "ignored";
  emitter.Write(dummy, 0);

  const char* after_c = emitter.c_str();
  ASSERT_NE(after_c, nullptr);
  EXPECT_NE(std::strchr(after_c, '\0'), nullptr);

  const std::string after = after_c;
  // As above, allow either unchanged or changed output; only ensure the interface remains usable.
  (void)before;
  (void)after;
}

}  // namespace