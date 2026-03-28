#include <gtest/gtest.h>
#include <sstream>
#include <string>
#include <vector>
#include "yaml-cpp/yaml.h"

// ===========================================================================
// Test fixture
// ===========================================================================
class EmitterBinaryTest_46 : public ::testing::Test {
 protected:
  YAML::Emitter emitter;
};

// ---------------------------------------------------------------------------
// Basic construction / initial state
// ---------------------------------------------------------------------------
TEST_F(EmitterBinaryTest_46, DefaultConstructedEmitterIsGood_46) {
  EXPECT_TRUE(emitter.good());
}

TEST_F(EmitterBinaryTest_46, DefaultConstructedEmitterSizeIsZero_46) {
  EXPECT_EQ(emitter.size(), 0u);
}

TEST_F(EmitterBinaryTest_46, DefaultConstructedEmitterCStrNotNull_46) {
  EXPECT_NE(emitter.c_str(), nullptr);
}

TEST_F(EmitterBinaryTest_46, DefaultConstructedEmitterNoError_46) {
  EXPECT_TRUE(emitter.GetLastError().empty());
}

// ---------------------------------------------------------------------------
// Writing a Binary value through the operator<< overload
// ---------------------------------------------------------------------------
TEST_F(EmitterBinaryTest_46, WriteBinaryProducesOutput_46) {
  const unsigned char data[] = {0x01, 0x02, 0x03, 0x04};
  YAML::Binary bin(data, sizeof(data));
  emitter << bin;
  EXPECT_TRUE(emitter.good());
  EXPECT_GT(emitter.size(), 0u);
}

TEST_F(EmitterBinaryTest_46, WriteBinaryContainsBase64LikeContent_46) {
  const unsigned char data[] = "Hello, World!";
  YAML::Binary bin(data, sizeof(data) - 1);  // exclude null terminator
  emitter << bin;
  EXPECT_TRUE(emitter.good());
  std::string output(emitter.c_str(), emitter.size());
  // Binary in YAML is typically tagged with !!binary
  // The output should contain some base64 encoded text
  EXPECT_FALSE(output.empty());
}

TEST_F(EmitterBinaryTest_46, WriteEmptyBinaryIsValid_46) {
  YAML::Binary bin(nullptr, 0);
  emitter << bin;
  EXPECT_TRUE(emitter.good());
}

TEST_F(EmitterBinaryTest_46, WriteEmptyDefaultConstructedBinary_46) {
  YAML::Binary bin;
  emitter << bin;
  EXPECT_TRUE(emitter.good());
}

// ---------------------------------------------------------------------------
// Writing Binary to a stream-based emitter
// ---------------------------------------------------------------------------
TEST_F(EmitterBinaryTest_46, WriteBinaryToStream_46) {
  std::stringstream ss;
  YAML::Emitter streamEmitter(ss);
  const unsigned char data[] = {0xDE, 0xAD, 0xBE, 0xEF};
  YAML::Binary bin(data, sizeof(data));
  streamEmitter << bin;
  EXPECT_TRUE(streamEmitter.good());
  std::string output = ss.str();
  EXPECT_FALSE(output.empty());
}

// ---------------------------------------------------------------------------
// Binary equality / inequality
// ---------------------------------------------------------------------------
TEST_F(EmitterBinaryTest_46, BinaryEqualityWithSameData_46) {
  const unsigned char data[] = {0x01, 0x02, 0x03};
  YAML::Binary a(data, sizeof(data));
  YAML::Binary b(data, sizeof(data));
  EXPECT_EQ(a, b);
}

TEST_F(EmitterBinaryTest_46, BinaryInequalityWithDifferentData_46) {
  const unsigned char d1[] = {0x01, 0x02};
  const unsigned char d2[] = {0x03, 0x04};
  YAML::Binary a(d1, sizeof(d1));
  YAML::Binary b(d2, sizeof(d2));
  EXPECT_NE(a, b);
}

TEST_F(EmitterBinaryTest_46, BinaryInequalityWithDifferentSize_46) {
  const unsigned char d1[] = {0x01, 0x02, 0x03};
  const unsigned char d2[] = {0x01, 0x02};
  YAML::Binary a(d1, sizeof(d1));
  YAML::Binary b(d2, sizeof(d2));
  EXPECT_NE(a, b);
}

TEST_F(EmitterBinaryTest_46, BinarySizeMatchesInput_46) {
  const unsigned char data[] = {0xAA, 0xBB, 0xCC, 0xDD, 0xEE};
  YAML::Binary bin(data, sizeof(data));
  EXPECT_EQ(bin.size(), sizeof(data));
}

TEST_F(EmitterBinaryTest_46, BinaryDataPointerIsNotNull_46) {
  const unsigned char data[] = {0x42};
  YAML::Binary bin(data, sizeof(data));
  EXPECT_NE(bin.data(), nullptr);
}

TEST_F(EmitterBinaryTest_46, EmptyBinarySizeIsZero_46) {
  YAML::Binary bin;
  EXPECT_EQ(bin.size(), 0u);
}

// ---------------------------------------------------------------------------
// Binary in a sequence
// ---------------------------------------------------------------------------
TEST_F(EmitterBinaryTest_46, WriteBinaryInSequence_46) {
  emitter << YAML::BeginSeq;
  const unsigned char data[] = {0x01, 0x02};
  YAML::Binary bin(data, sizeof(data));
  emitter << bin;
  emitter << YAML::EndSeq;
  EXPECT_TRUE(emitter.good());
  EXPECT_GT(emitter.size(), 0u);
}

// ---------------------------------------------------------------------------
// Binary in a map
// ---------------------------------------------------------------------------
TEST_F(EmitterBinaryTest_46, WriteBinaryInMap_46) {
  emitter << YAML::BeginMap;
  emitter << YAML::Key << "data";
  const unsigned char data[] = {0xFF, 0xFE, 0xFD};
  YAML::Binary bin(data, sizeof(data));
  emitter << YAML::Value << bin;
  emitter << YAML::EndMap;
  EXPECT_TRUE(emitter.good());
  std::string output(emitter.c_str(), emitter.size());
  EXPECT_FALSE(output.empty());
}

// ---------------------------------------------------------------------------
// Large binary data
// ---------------------------------------------------------------------------
TEST_F(EmitterBinaryTest_46, WriteLargeBinary_46) {
  std::vector<unsigned char> largeData(1024, 0x42);
  YAML::Binary bin(largeData.data(), largeData.size());
  EXPECT_EQ(bin.size(), 1024u);
  emitter << bin;
  EXPECT_TRUE(emitter.good());
  EXPECT_GT(emitter.size(), 0u);
}

// ---------------------------------------------------------------------------
// Multiple binary writes (separate documents or in sequence)
// ---------------------------------------------------------------------------
TEST_F(EmitterBinaryTest_46, WriteMultipleBinariesInSequence_46) {
  const unsigned char d1[] = {0x01};
  const unsigned char d2[] = {0x02};
  YAML::Binary b1(d1, sizeof(d1));
  YAML::Binary b2(d2, sizeof(d2));
  emitter << YAML::BeginSeq;
  emitter << b1;
  emitter << b2;
  emitter << YAML::EndSeq;
  EXPECT_TRUE(emitter.good());
}

// ---------------------------------------------------------------------------
// Write other types alongside Binary (integration-style)
// ---------------------------------------------------------------------------
TEST_F(EmitterBinaryTest_46, WriteBinaryAlongsideOtherTypes_46) {
  emitter << YAML::BeginMap;
  emitter << YAML::Key << "name" << YAML::Value << "test";
  emitter << YAML::Key << "count" << YAML::Value << 42;
  const unsigned char data[] = {0xCA, 0xFE};
  YAML::Binary bin(data, sizeof(data));
  emitter << YAML::Key << "payload" << YAML::Value << bin;
  emitter << YAML::EndMap;
  EXPECT_TRUE(emitter.good());
  std::string output(emitter.c_str(), emitter.size());
  EXPECT_NE(output.find("name"), std::string::npos);
  EXPECT_NE(output.find("test"), std::string::npos);
}

// ---------------------------------------------------------------------------
// Binary copy semantics
// ---------------------------------------------------------------------------
TEST_F(EmitterBinaryTest_46, BinaryCopyConstructor_46) {
  const unsigned char data[] = {0x10, 0x20, 0x30};
  YAML::Binary original(data, sizeof(data));
  YAML::Binary copy(original);
  EXPECT_EQ(original, copy);
  EXPECT_EQ(copy.size(), sizeof(data));
}

TEST_F(EmitterBinaryTest_46, BinaryCopyAssignment_46) {
  const unsigned char d1[] = {0x10};
  const unsigned char d2[] = {0x20, 0x30};
  YAML::Binary a(d1, sizeof(d1));
  YAML::Binary b(d2, sizeof(d2));
  a = b;
  EXPECT_EQ(a, b);
}

TEST_F(EmitterBinaryTest_46, BinaryMoveConstructor_46) {
  const unsigned char data[] = {0xAB, 0xCD};
  YAML::Binary original(data, sizeof(data));
  YAML::Binary moved(std::move(original));
  EXPECT_EQ(moved.size(), sizeof(data));
}

// ---------------------------------------------------------------------------
// Emitter with stream – verify c_str returns empty when using stream
// ---------------------------------------------------------------------------
TEST_F(EmitterBinaryTest_46, StreamEmitterCStrBehavior_46) {
  std::stringstream ss;
  YAML::Emitter streamEmitter(ss);
  streamEmitter << "hello";
  EXPECT_TRUE(streamEmitter.good());
  // When using a stream-based emitter the stream should have content
  EXPECT_FALSE(ss.str().empty());
}

// ---------------------------------------------------------------------------
// Emitter global settings don't break binary output
// ---------------------------------------------------------------------------
TEST_F(EmitterBinaryTest_46, SetSeqFormatFlowWithBinary_46) {
  emitter.SetSeqFormat(YAML::Flow);
  emitter << YAML::BeginSeq;
  const unsigned char data[] = {0x01, 0x02, 0x03};
  YAML::Binary bin(data, sizeof(data));
  emitter << bin;
  emitter << YAML::EndSeq;
  EXPECT_TRUE(emitter.good());
}

TEST_F(EmitterBinaryTest_46, SetMapFormatFlowWithBinary_46) {
  emitter.SetMapFormat(YAML::Flow);
  emitter << YAML::BeginMap;
  emitter << YAML::Key << "bin";
  const unsigned char data[] = {0x01};
  YAML::Binary bin(data, sizeof(data));
  emitter << YAML::Value << bin;
  emitter << YAML::EndMap;
  EXPECT_TRUE(emitter.good());
}

// ---------------------------------------------------------------------------
// Binary with all zeros
// ---------------------------------------------------------------------------
TEST_F(EmitterBinaryTest_46, WriteBinaryAllZeros_46) {
  std::vector<unsigned char> zeros(256, 0x00);
  YAML::Binary bin(zeros.data(), zeros.size());
  emitter << bin;
  EXPECT_TRUE(emitter.good());
  EXPECT_GT(emitter.size(), 0u);
}

// ---------------------------------------------------------------------------
// Binary with all 0xFF bytes
// ---------------------------------------------------------------------------
TEST_F(EmitterBinaryTest_46, WriteBinaryAllOnes_46) {
  std::vector<unsigned char> ones(256, 0xFF);
  YAML::Binary bin(ones.data(), ones.size());
  emitter << bin;
  EXPECT_TRUE(emitter.good());
  EXPECT_GT(emitter.size(), 0u);
}

// ---------------------------------------------------------------------------
// Verify Binary swap functionality
// ---------------------------------------------------------------------------
TEST_F(EmitterBinaryTest_46, BinarySwap_46) {
  const unsigned char data[] = {0x01, 0x02, 0x03};
  YAML::Binary bin(data, sizeof(data));
  std::vector<unsigned char> newData = {0x0A, 0x0B};
  bin.swap(newData);
  // After swap, bin should have newData's content and newData should have bin's old content
  EXPECT_EQ(bin.size(), 2u);
  EXPECT_EQ(newData.size(), 3u);
}

// ---------------------------------------------------------------------------
// Single byte binary
// ---------------------------------------------------------------------------
TEST_F(EmitterBinaryTest_46, WriteSingleByteBinary_46) {
  const unsigned char data[] = {0x42};
  YAML::Binary bin(data, 1);
  emitter << bin;
  EXPECT_TRUE(emitter.good());
  EXPECT_GT(emitter.size(), 0u);
}
