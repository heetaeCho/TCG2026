// File: ./TestProjects/yaml-cpp/test/emitter_binary_write_test_543.cpp

#include <gtest/gtest.h>

#include <cstddef>
#include <cstring>
#include <sstream>
#include <string>
#include <vector>

#include "yaml-cpp/binary.h"
#include "yaml-cpp/emitter.h"

namespace {

class EmitterBinaryWriteTest_543 : public ::testing::Test {
 protected:
  static std::string AsString(const YAML::Emitter& e) {
    const char* p = e.c_str();
    return p ? std::string(p) : std::string();
  }

  static bool ContainsBinaryTag(const std::string& out) {
    // The implementation calls Write(SecondaryTag("binary")), but the exact tag spelling
    // (e.g., "!!binary" vs. the full tag URI) is an observable formatting choice.
    return out.find("!!binary") != std::string::npos ||
           out.find("tag:yaml.org,2002:binary") != std::string::npos;
  }
};

TEST_F(EmitterBinaryWriteTest_543, WriteBinaryReturnsSameEmitterReference_543) {
  std::stringstream ss;
  YAML::Emitter emitter(ss);

  const unsigned char data[] = {0x00, 0x01, 0x02};
  YAML::Binary bin(data, sizeof(data));

  YAML::Emitter& ret = emitter.Write(bin);
  EXPECT_EQ(&ret, &emitter);
}

TEST_F(EmitterBinaryWriteTest_543, WriteBinaryProducesSomeOutputAndRemainsGood_543) {
  std::stringstream ss;
  YAML::Emitter emitter(ss);

  const unsigned char data[] = {0xDE, 0xAD, 0xBE, 0xEF};
  YAML::Binary bin(data, sizeof(data));

  EXPECT_TRUE(emitter.good());

  const std::string before = AsString(emitter);
  const std::size_t before_size = emitter.size();

  emitter.Write(bin);

  EXPECT_TRUE(emitter.good());
  EXPECT_GE(emitter.size(), before_size);

  const std::string after = AsString(emitter);
  EXPECT_NE(after, before);
  EXPECT_FALSE(after.empty());
}

TEST_F(EmitterBinaryWriteTest_543, WriteBinaryEmitsBinaryTagInOutput_543) {
  std::stringstream ss;
  YAML::Emitter emitter(ss);

  const unsigned char data[] = {0x10, 0x20};
  YAML::Binary bin(data, sizeof(data));

  emitter.Write(bin);

  const std::string out = AsString(emitter);
  EXPECT_TRUE(ContainsBinaryTag(out)) << "Output was: " << out;
}

TEST_F(EmitterBinaryWriteTest_543, WriteEmptyBinaryDoesNotCrashAndEmitsBinaryTag_543) {
  std::stringstream ss;
  YAML::Emitter emitter(ss);

  YAML::Binary empty;  // size 0

  emitter.Write(empty);

  EXPECT_TRUE(emitter.good());
  const std::string out = AsString(emitter);
  EXPECT_TRUE(ContainsBinaryTag(out)) << "Output was: " << out;
}

TEST_F(EmitterBinaryWriteTest_543, LargerBinaryTendsToIncreaseOutputSize_543) {
  std::stringstream ss;
  YAML::Emitter emitter(ss);

  const unsigned char small_data[] = {0x01};
  YAML::Binary small_bin(small_data, sizeof(small_data));
  emitter.Write(small_bin);

  const std::size_t size_after_small = emitter.size();
  const std::string out_after_small = AsString(emitter);

  // Write a bigger binary to the same emitter; we don't assume exact encoding,
  // only that writing more data should generally not produce less total output.
  std::vector<unsigned char> big_data(64, 0xAB);
  YAML::Binary big_bin(big_data.data(), big_data.size());
  emitter.Write(big_bin);

  const std::size_t size_after_big = emitter.size();
  const std::string out_after_big = AsString(emitter);

  EXPECT_GE(size_after_big, size_after_small);
  EXPECT_NE(out_after_big, out_after_small);
}

TEST_F(EmitterBinaryWriteTest_543, WhenEmitterIsNotGoodWriteBinaryIsNoOpForObservableState_543) {
  // Put the underlying stream into a bad state before giving it to the emitter.
  std::stringstream ss;
  ss.setstate(std::ios::badbit);

  YAML::Emitter emitter(ss);

  // If construction already yields !good(), the implementation should early-return
  // from Write(Binary) after attempting to write the tag.
  const bool initial_good = emitter.good();
  const std::size_t initial_size = emitter.size();
  const std::string initial_out = AsString(emitter);

  const unsigned char data[] = {0xAA, 0xBB, 0xCC};
  YAML::Binary bin(data, sizeof(data));

  YAML::Emitter& ret = emitter.Write(bin);

  EXPECT_EQ(&ret, &emitter);

  // We only assert stability for observable state, without assuming any specific error text.
  EXPECT_EQ(emitter.good(), initial_good);
  EXPECT_EQ(emitter.size(), initial_size);
  EXPECT_EQ(AsString(emitter), initial_out);
}

}  // namespace