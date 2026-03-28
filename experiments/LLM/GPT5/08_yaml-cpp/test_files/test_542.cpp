// File: emitter_write_null_test_542.cpp
#include <gtest/gtest.h>
#include <yaml-cpp/yaml.h>

namespace {

class WriteNullTest_542 : public ::testing::Test {
protected:
  YAML::Emitter emitter;
};

TEST_F(WriteNullTest_542, WriteNullProducesScalarNull_542) {
  // Act: use the public interface that routes to Emitter::Write(const _Null&).
  emitter << YAML::Null;

  // Assert: emitter remains good and the output is the expected null scalar.
  EXPECT_TRUE(emitter.good());
  ASSERT_NE(emitter.c_str(), nullptr);

  // yaml-cpp's default null name is typically "null".
  // We only assert on the observable output.
  EXPECT_STREQ(emitter.c_str(), "null");
}

TEST_F(WriteNullTest_542, WriteNullCanBeChained_542) {
  // Act
  emitter << YAML::Null << YAML::Null;

  // Assert: chaining should work and remain in a good state.
  EXPECT_TRUE(emitter.good());
  ASSERT_NE(emitter.c_str(), nullptr);

  // Two consecutive scalars are separated by a document-friendly delimiter (usually a space).
  // We validate observable behavior without assuming internal formatting beyond the emitted string.
  const std::string out = emitter.c_str();
  EXPECT_FALSE(out.empty());
  EXPECT_NE(out.find("null"), std::string::npos);

  // Ensure both nulls appear.
  const auto first = out.find("null");
  ASSERT_NE(first, std::string::npos);
  const auto second = out.find("null", first + 1);
  EXPECT_NE(second, std::string::npos);
}

TEST_F(WriteNullTest_542, WriteNullIsNoOpWhenEmitterIsBad_542) {
  // Arrange: force an observable error state using the public interface.
  // Emitting an unmatched EndSeq is an error for the emitter state machine.
  emitter << YAML::EndSeq;
  EXPECT_FALSE(emitter.good());

  const std::string before = emitter.c_str() ? emitter.c_str() : "";

  // Act: call the null writer after the emitter is already in a bad state.
  emitter << YAML::Null;

  // Assert: still bad, and output should not change (no further writing when !good()).
  EXPECT_FALSE(emitter.good());
  const std::string after = emitter.c_str() ? emitter.c_str() : "";
  EXPECT_EQ(after, before);
}

}  // namespace