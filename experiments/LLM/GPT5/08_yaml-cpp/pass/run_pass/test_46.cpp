// File: yaml-cpp/test/emitter_operator_binary_test_46.cpp

#include <gtest/gtest.h>

#include <sstream>
#include <vector>

#include "yaml-cpp/binary.h"
#include "yaml-cpp/emitter.h"

namespace {

class EmitterOperatorBinaryTest_46 : public ::testing::Test {
 protected:
  static YAML::Binary MakeBinary(const std::vector<unsigned char>& bytes) {
    if (bytes.empty()) {
      return YAML::Binary(nullptr, 0);
    }
    return YAML::Binary(bytes.data(), bytes.size());
  }
};

TEST_F(EmitterOperatorBinaryTest_46, ReturnsSameEmitterReference_46) {
  std::ostringstream out;
  YAML::Emitter emitter(out);

  const std::vector<unsigned char> bytes = {0x00, 0x01, 0x7F, 0x80, 0xFF};
  YAML::Binary b = MakeBinary(bytes);

  YAML::Emitter& ret = (emitter << b);
  EXPECT_EQ(&ret, &emitter);
}

TEST_F(EmitterOperatorBinaryTest_46, ProducesSameOutputAsWriteForNonEmptyBinary_46) {
  const std::vector<unsigned char> bytes = {0x10, 0x20, 0x30, 0x40, 0x50};
  YAML::Binary b = MakeBinary(bytes);

  std::ostringstream out_op;
  YAML::Emitter emitter_op(out_op);
  emitter_op << b;

  std::ostringstream out_write;
  YAML::Emitter emitter_write(out_write);
  emitter_write.Write(b);

  // Compare observable results via emitter API.
  ASSERT_NE(emitter_op.c_str(), nullptr);
  ASSERT_NE(emitter_write.c_str(), nullptr);
  EXPECT_STREQ(emitter_op.c_str(), emitter_write.c_str());
  EXPECT_EQ(emitter_op.size(), emitter_write.size());
  EXPECT_EQ(emitter_op.good(), emitter_write.good());
  EXPECT_EQ(emitter_op.GetLastError(), emitter_write.GetLastError());

  // Also compare stream content as an external observable effect.
  EXPECT_EQ(out_op.str(), out_write.str());
}

TEST_F(EmitterOperatorBinaryTest_46, ProducesSameOutputAsWriteForEmptyBinary_46) {
  YAML::Binary empty;  // default ctor: Binary(nullptr, 0)

  std::ostringstream out_op;
  YAML::Emitter emitter_op(out_op);
  emitter_op << empty;

  std::ostringstream out_write;
  YAML::Emitter emitter_write(out_write);
  emitter_write.Write(empty);

  ASSERT_NE(emitter_op.c_str(), nullptr);
  ASSERT_NE(emitter_write.c_str(), nullptr);
  EXPECT_STREQ(emitter_op.c_str(), emitter_write.c_str());
  EXPECT_EQ(emitter_op.size(), emitter_write.size());
  EXPECT_EQ(emitter_op.good(), emitter_write.good());
  EXPECT_EQ(emitter_op.GetLastError(), emitter_write.GetLastError());

  EXPECT_EQ(out_op.str(), out_write.str());
}

TEST_F(EmitterOperatorBinaryTest_46, SupportsChainingAfterBinaryInsertion_46) {
  const std::vector<unsigned char> bytes = {0xAB, 0xCD, 0xEF};
  YAML::Binary b = MakeBinary(bytes);

  std::ostringstream out_op;
  YAML::Emitter emitter_op(out_op);
  (emitter_op << b) << 'X';

  std::ostringstream out_write;
  YAML::Emitter emitter_write(out_write);
  emitter_write.Write(b).Write('X');

  ASSERT_NE(emitter_op.c_str(), nullptr);
  ASSERT_NE(emitter_write.c_str(), nullptr);
  EXPECT_STREQ(emitter_op.c_str(), emitter_write.c_str());
  EXPECT_EQ(emitter_op.size(), emitter_write.size());
  EXPECT_EQ(emitter_op.good(), emitter_write.good());
  EXPECT_EQ(emitter_op.GetLastError(), emitter_write.GetLastError());

  EXPECT_EQ(out_op.str(), out_write.str());
}

TEST_F(EmitterOperatorBinaryTest_46, MatchesWriteBehaviorWhenUnderlyingStreamIsBad_46) {
  const std::vector<unsigned char> bytes = {0x01, 0x02, 0x03, 0x04};
  YAML::Binary b = MakeBinary(bytes);

  std::ostringstream out_op;
  out_op.setstate(std::ios::badbit);
  YAML::Emitter emitter_op(out_op);
  emitter_op << b;

  std::ostringstream out_write;
  out_write.setstate(std::ios::badbit);
  YAML::Emitter emitter_write(out_write);
  emitter_write.Write(b);

  // We don't assume what "bad stream" means for Emitter; we only require
  // that operator<< matches Write(binary) behavior under the same condition.
  ASSERT_NE(emitter_op.c_str(), nullptr);
  ASSERT_NE(emitter_write.c_str(), nullptr);
  EXPECT_STREQ(emitter_op.c_str(), emitter_write.c_str());
  EXPECT_EQ(emitter_op.size(), emitter_write.size());
  EXPECT_EQ(emitter_op.good(), emitter_write.good());
  EXPECT_EQ(emitter_op.GetLastError(), emitter_write.GetLastError());

  EXPECT_EQ(out_op.str(), out_write.str());
}

TEST_F(EmitterOperatorBinaryTest_46, HandlesLargerBinarySameAsWrite_46) {
  std::vector<unsigned char> bytes;
  bytes.reserve(4096);
  for (int i = 0; i < 4096; ++i) {
    bytes.push_back(static_cast<unsigned char>(i & 0xFF));
  }
  YAML::Binary b = MakeBinary(bytes);

  std::ostringstream out_op;
  YAML::Emitter emitter_op(out_op);
  emitter_op << b;

  std::ostringstream out_write;
  YAML::Emitter emitter_write(out_write);
  emitter_write.Write(b);

  ASSERT_NE(emitter_op.c_str(), nullptr);
  ASSERT_NE(emitter_write.c_str(), nullptr);
  EXPECT_STREQ(emitter_op.c_str(), emitter_write.c_str());
  EXPECT_EQ(emitter_op.size(), emitter_write.size());
  EXPECT_EQ(emitter_op.good(), emitter_write.good());
  EXPECT_EQ(emitter_op.GetLastError(), emitter_write.GetLastError());

  EXPECT_EQ(out_op.str(), out_write.str());
}

}  // namespace
