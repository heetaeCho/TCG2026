#include <gtest/gtest.h>

#include <cstring>
#include <limits>
#include <string>

#include "yaml-cpp/emitter.h"
#include "yaml-cpp/emittermanip.h"

namespace {

class EmitterWriteCharPtrTest_534 : public ::testing::Test {
 protected:
  YAML::Emitter emitter_;
};

TEST_F(EmitterWriteCharPtrTest_534, WriteReturnsSameEmitterReference_534) {
  YAML::Emitter* before = &emitter_;
  YAML::Emitter& ret = emitter_.Write("abc", 3);
  EXPECT_EQ(before, &ret);
}

TEST_F(EmitterWriteCharPtrTest_534, WriteEmptySizeDoesNotChangeOutput_534) {
  emitter_.Write("abc", 3);
  const std::string before(emitter_.c_str(), emitter_.size());

  emitter_.Write("SHOULD_NOT_APPEAR", 0);
  const std::string after(emitter_.c_str(), emitter_.size());

  EXPECT_EQ(before, after);
}

TEST_F(EmitterWriteCharPtrTest_534, WriteUsesOnlyProvidedSizePrefix_534) {
  const char* str = "abcdef";
  emitter_.Write(str, 3);

  const std::string out(emitter_.c_str(), emitter_.size());
  EXPECT_EQ(out, "abc");
}

TEST_F(EmitterWriteCharPtrTest_534, MultipleWritesAppendInOrder_534) {
  emitter_.Write("abc", 3);
  emitter_.Write("XYZ", 3);

  const std::string out(emitter_.c_str(), emitter_.size());
  EXPECT_EQ(out, "abcXYZ");
}

TEST_F(EmitterWriteCharPtrTest_534, WritePreservesEmbeddedNullBytes_534) {
  // "A\0B" with size 3 should write 3 bytes including the embedded '\0'.
  const char buf[3] = {'A', '\0', 'B'};
  emitter_.Write(buf, 3);

  ASSERT_EQ(emitter_.size(), static_cast<std::size_t>(3));
  const std::string out(emitter_.c_str(), emitter_.size());

  ASSERT_EQ(out.size(), 3u);
  EXPECT_EQ(out[0], 'A');
  EXPECT_EQ(out[1], '\0');
  EXPECT_EQ(out[2], 'B');
}

TEST_F(EmitterWriteCharPtrTest_534, SingleQuotedStringFormatWrapsWithSingleQuotesForSimpleText_534) {
  ASSERT_TRUE(emitter_.SetStringFormat(YAML::SingleQuoted));

  emitter_.Write("abc", 3);
  const std::string out(emitter_.c_str(), emitter_.size());

  ASSERT_GE(out.size(), 2u);
  EXPECT_EQ(out.front(), '\'');
  EXPECT_EQ(out.back(), '\'');
  EXPECT_EQ(out.substr(1, out.size() - 2), "abc");
}

TEST_F(EmitterWriteCharPtrTest_534, DoubleQuotedStringFormatWrapsWithDoubleQuotesForSimpleText_534) {
  ASSERT_TRUE(emitter_.SetStringFormat(YAML::DoubleQuoted));

  emitter_.Write("abc", 3);
  const std::string out(emitter_.c_str(), emitter_.size());

  ASSERT_GE(out.size(), 2u);
  EXPECT_EQ(out.front(), '"');
  EXPECT_EQ(out.back(), '"');
  EXPECT_EQ(out.substr(1, out.size() - 2), "abc");
}

TEST_F(EmitterWriteCharPtrTest_534, WriteLongStringIncreasesOutputSize_534) {
  // We don't assume how it is formatted; we only check the observable effect:
  // writing N bytes results in non-empty output and size grows.
  std::string long_str(1500, 'a');
  const std::size_t before = emitter_.size();

  emitter_.Write(long_str.data(), long_str.size());

  EXPECT_GT(emitter_.size(), before);
  EXPECT_FALSE(std::string(emitter_.c_str(), emitter_.size()).empty());
}

TEST_F(EmitterWriteCharPtrTest_534, IfEmitterBecomesBadWriteDoesNotModifyOutput_534) {
  // Try to induce an error through public API. If this build of yaml-cpp
  // treats these values as valid, skip the test (error path not observable).
  const std::string baseline(emitter_.c_str(), emitter_.size());

  // Attempt a likely-invalid indent. We intentionally do not assume behavior.
  const bool set_ok = emitter_.SetIndent(std::numeric_limits<std::size_t>::max());

  if (set_ok && emitter_.good()) {
    GTEST_SKIP() << "Could not observe an error state via public API in this build.";
  }

  emitter_.Write("abc", 3);
  const std::string after(emitter_.c_str(), emitter_.size());
  EXPECT_EQ(after, baseline);
}

}  // namespace