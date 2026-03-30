// TEST_ID: 530
#include <gtest/gtest.h>

#include <cstring>
#include <sstream>
#include <string>

#include "yaml-cpp/emitter.h"
#include "yaml-cpp/emittermanip.h"

namespace {

class EmitterSetLocalValueTest_530 : public ::testing::Test {
 protected:
  static std::string Str(const YAML::Emitter& e) {
    const char* s = e.c_str();
    return s ? std::string(s) : std::string();
  }
};

TEST_F(EmitterSetLocalValueTest_530, ReturnsSameEmitterReference_530) {
  YAML::Emitter out;

  YAML::Emitter* p0 = &out;
  YAML::Emitter& r1 = out.SetLocalValue(YAML::BeginSeq);
  YAML::Emitter& r2 = out.SetLocalValue(YAML::EndSeq);

  EXPECT_EQ(p0, &r1);
  EXPECT_EQ(p0, &r2);
}

TEST_F(EmitterSetLocalValueTest_530, KeyDoesNotDirectlyChangeOutputOnFreshEmitter_530) {
  YAML::Emitter out;

  const std::string before = Str(out);
  const std::size_t size_before = out.size();

  out.SetLocalValue(YAML::Key);

  EXPECT_EQ(size_before, out.size());
  EXPECT_EQ(before, Str(out));
}

TEST_F(EmitterSetLocalValueTest_530, ValueDoesNotDirectlyChangeOutputOnFreshEmitter_530) {
  YAML::Emitter out;

  const std::string before = Str(out);
  const std::size_t size_before = out.size();

  out.SetLocalValue(YAML::Value);

  EXPECT_EQ(size_before, out.size());
  EXPECT_EQ(before, Str(out));
}

TEST_F(EmitterSetLocalValueTest_530, BeginDocChangesOutputFromEmpty_530) {
  YAML::Emitter out;

  ASSERT_EQ(0u, out.size());
  ASSERT_TRUE(Str(out).empty());

  out.SetLocalValue(YAML::BeginDoc);

  EXPECT_GT(out.size(), 0u);
  EXPECT_FALSE(Str(out).empty());
}

TEST_F(EmitterSetLocalValueTest_530, BeginSeqWriteScalarEndSeqProducesScalarInOutput_530) {
  YAML::Emitter out;

  const std::size_t size0 = out.size();

  out.SetLocalValue(YAML::BeginSeq);
  const std::size_t size_after_begin = out.size();
  EXPECT_GE(size_after_begin, size0);

  out.Write("a");
  const std::size_t size_after_write = out.size();
  EXPECT_GT(size_after_write, size_after_begin);

  out.SetLocalValue(YAML::EndSeq);
  const std::size_t size_after_end = out.size();
  EXPECT_GE(size_after_end, size_after_write);

  const std::string s = Str(out);
  EXPECT_NE(s.find("a"), std::string::npos);
  EXPECT_FALSE(s.empty());
}

TEST_F(EmitterSetLocalValueTest_530, BeginMapKeyValueWritePairsEndMapContainsKeyAndValue_530) {
  YAML::Emitter out;

  out.SetLocalValue(YAML::BeginMap);
  out.SetLocalValue(YAML::Key);
  out.Write("k");
  out.SetLocalValue(YAML::Value);
  out.Write("v");
  out.SetLocalValue(YAML::EndMap);

  const std::string s = Str(out);
  EXPECT_NE(s.find("k"), std::string::npos);
  EXPECT_NE(s.find("v"), std::string::npos);
  EXPECT_FALSE(s.empty());
  EXPECT_GT(out.size(), 0u);
}

TEST_F(EmitterSetLocalValueTest_530, NewlineAppendsNewlineCharacter_530) {
  YAML::Emitter out;

  out.Write("a");
  const std::size_t size_before_nl = out.size();

  out.SetLocalValue(YAML::Newline);
  const std::string s = Str(out);

  EXPECT_GT(out.size(), size_before_nl);
  ASSERT_FALSE(s.empty());
  EXPECT_EQ(s.back(), '\n');
}

TEST_F(EmitterSetLocalValueTest_530, MultipleNewlinesIncreaseSizeMonotonically_530) {
  YAML::Emitter out;

  out.Write("x");
  const std::size_t s1 = out.size();

  out.SetLocalValue(YAML::Newline);
  const std::size_t s2 = out.size();

  out.SetLocalValue(YAML::Newline);
  const std::size_t s3 = out.size();

  EXPECT_GT(s2, s1);
  EXPECT_GT(s3, s2);

  const std::string str = Str(out);
  // At least one newline should exist after writing and adding newlines.
  EXPECT_NE(str.find('\n'), std::string::npos);
}

TEST_F(EmitterSetLocalValueTest_530, DefaultManipulatorFlowDoesNotDirectlyChangeOutputOnFreshEmitter_530) {
  YAML::Emitter out;

  const std::string before = Str(out);
  const std::size_t size_before = out.size();

  out.SetLocalValue(YAML::Flow);  // hits default branch in SetLocalValue

  EXPECT_EQ(size_before, out.size());
  EXPECT_EQ(before, Str(out));
}

TEST_F(EmitterSetLocalValueTest_530, EndSeqWithoutBeginSeqDoesNotCrashAndIfBecomesBadThenFurtherSetLocalValueIsNoOp_530) {
  YAML::Emitter out;

  const std::string before = Str(out);
  const std::size_t size_before = out.size();

  // This may or may not be considered an error by the implementation.
  out.SetLocalValue(YAML::EndSeq);

  // If the emitter transitioned into a bad state, SetLocalValue should early-return without changing output.
  if (!out.good()) {
    const std::string after_endseq = Str(out);
    const std::size_t size_after_endseq = out.size();

    out.SetLocalValue(YAML::BeginSeq);

    EXPECT_EQ(size_after_endseq, out.size());
    EXPECT_EQ(after_endseq, Str(out));
  } else {
    // Even if it's still good, the call should be observable as safe and chainable.
    YAML::Emitter& r = out.SetLocalValue(YAML::BeginSeq);
    EXPECT_EQ(&r, &out);
  }

  // At minimum, original buffers should remain valid to query.
  (void)before;
  (void)size_before;
  EXPECT_NE(out.c_str(), nullptr);
}

}  // namespace