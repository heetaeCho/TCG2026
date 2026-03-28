// test_emitter_operator_char_39.cpp
#include <gtest/gtest.h>

#include <sstream>
#include <string>

#include "yaml-cpp/emitter.h"

namespace {

static std::string DumpEmitterBuffer(const YAML::Emitter& e) {
  // Use size() so embedded '\0' is preserved.
  return std::string(e.c_str(), e.size());
}

class EmitterOperatorCharTest_39 : public ::testing::Test {};

TEST_F(EmitterOperatorCharTest_39, ReturnsSameEmitterReference_39) {
  YAML::Emitter emitter;
  YAML::Emitter* before = &emitter;

  YAML::Emitter& ret = (emitter << 'x');

  EXPECT_EQ(before, &ret);
  EXPECT_EQ(before, &emitter);
}

TEST_F(EmitterOperatorCharTest_39, MatchesWriteCharOutput_39) {
  YAML::Emitter via_op;
  YAML::Emitter via_write;

  ASSERT_NO_THROW(via_op << 'a');
  ASSERT_NO_THROW(via_write.Write('a'));

  EXPECT_EQ(via_op.size(), via_write.size());
  EXPECT_EQ(DumpEmitterBuffer(via_op), DumpEmitterBuffer(via_write));
}

TEST_F(EmitterOperatorCharTest_39, SupportsChainingAndMatchesWriteSequence_39) {
  YAML::Emitter via_op;
  YAML::Emitter via_write;

  ASSERT_NO_THROW(via_op << 'a' << 'b' << 'c');
  ASSERT_NO_THROW(via_write.Write('a').Write('b').Write('c'));

  EXPECT_EQ(via_op.size(), via_write.size());
  EXPECT_EQ(DumpEmitterBuffer(via_op), DumpEmitterBuffer(via_write));
}

TEST_F(EmitterOperatorCharTest_39, HandlesWhitespaceCharactersSameAsWrite_39) {
  YAML::Emitter via_op;
  YAML::Emitter via_write;

  const char chars[] = {' ', '\n', '\t'};
  for (char ch : chars) {
    ASSERT_NO_THROW(via_op << ch);
    ASSERT_NO_THROW(via_write.Write(ch));
  }

  EXPECT_EQ(via_op.size(), via_write.size());
  EXPECT_EQ(DumpEmitterBuffer(via_op), DumpEmitterBuffer(via_write));
}

TEST_F(EmitterOperatorCharTest_39, HandlesNullCharacterSameAsWrite_39) {
  YAML::Emitter via_op;
  YAML::Emitter via_write;

  const char nul = '\0';

  ASSERT_NO_THROW(via_op << nul);
  ASSERT_NO_THROW(via_write.Write(nul));

  EXPECT_EQ(via_op.size(), via_write.size());
  EXPECT_EQ(DumpEmitterBuffer(via_op), DumpEmitterBuffer(via_write));
}

TEST_F(EmitterOperatorCharTest_39, HandlesNonAsciiCharByteSameAsWrite_39) {
  YAML::Emitter via_op;
  YAML::Emitter via_write;

  // Use a byte value that may be negative if char is signed.
  const unsigned char u = 0xFF;
  const char ch = static_cast<char>(u);

  ASSERT_NO_THROW(via_op << ch);
  ASSERT_NO_THROW(via_write.Write(ch));

  EXPECT_EQ(via_op.size(), via_write.size());
  EXPECT_EQ(DumpEmitterBuffer(via_op), DumpEmitterBuffer(via_write));
}

}  // namespace
