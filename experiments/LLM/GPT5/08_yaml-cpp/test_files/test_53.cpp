// File: test/emitter_operator_unsigned_long_test_53.cpp

#include <gtest/gtest.h>

#include <limits>
#include <sstream>
#include <string>

#include "yaml-cpp/emitter.h"

namespace {

class EmitterOperatorUnsignedLongTest_53 : public ::testing::Test {
 protected:
  static std::string SafeStr(const YAML::Emitter& e) {
    const char* p = e.c_str();
    return p ? std::string(p) : std::string();
  }
};

TEST_F(EmitterOperatorUnsignedLongTest_53, ReturnsSameEmitterReference_53) {
  YAML::Emitter emitter;
  YAML::Emitter& ret = (emitter << static_cast<unsigned long>(1));
  EXPECT_EQ(&ret, &emitter);
}

TEST_F(EmitterOperatorUnsignedLongTest_53, DoesNotThrowForCommonValues_53) {
  YAML::Emitter emitter;

  EXPECT_NO_THROW(emitter << static_cast<unsigned long>(0));
  EXPECT_NO_THROW(emitter << static_cast<unsigned long>(1));
  EXPECT_NO_THROW(emitter << static_cast<unsigned long>(42));
  EXPECT_NO_THROW(emitter << std::numeric_limits<unsigned long>::max());
}

TEST_F(EmitterOperatorUnsignedLongTest_53, WritingZeroProducesNonEmptyOutput_53) {
  YAML::Emitter emitter;

  const std::size_t before_size = emitter.size();
  const std::string before = SafeStr(emitter);

  emitter << static_cast<unsigned long>(0);

  const std::size_t after_size = emitter.size();
  const std::string after = SafeStr(emitter);

  EXPECT_GE(after_size, before_size);
  EXPECT_NE(after, before);
  EXPECT_FALSE(after.empty());
}

TEST_F(EmitterOperatorUnsignedLongTest_53, MultipleInsertionsChangeOutputMonotonically_53) {
  YAML::Emitter emitter;

  emitter << static_cast<unsigned long>(1);
  const std::size_t size_after_1 = emitter.size();
  const std::string out_after_1 = SafeStr(emitter);

  emitter << static_cast<unsigned long>(2);
  const std::size_t size_after_2 = emitter.size();
  const std::string out_after_2 = SafeStr(emitter);

  EXPECT_GE(size_after_2, size_after_1);
  EXPECT_NE(out_after_2, out_after_1);
  EXPECT_FALSE(out_after_2.empty());
}

TEST_F(EmitterOperatorUnsignedLongTest_53, CanBeChainedAndStillReturnsEmitter_53) {
  YAML::Emitter emitter;

  YAML::Emitter& ret =
      (emitter << static_cast<unsigned long>(1) << static_cast<unsigned long>(2));

  EXPECT_EQ(&ret, &emitter);
  EXPECT_FALSE(SafeStr(emitter).empty());
}

TEST_F(EmitterOperatorUnsignedLongTest_53, WorksWhenConstructedWithOstream_53) {
  std::ostringstream os;
  YAML::Emitter emitter(os);

  emitter << static_cast<unsigned long>(123);

  // Observable behavior through the public interface.
  EXPECT_FALSE(SafeStr(emitter).empty());
  EXPECT_GE(emitter.size(), std::size_t{1});

  // Also observable via the provided ostream sink (implementation-defined exact formatting).
  EXPECT_FALSE(os.str().empty());
}

TEST_F(EmitterOperatorUnsignedLongTest_53, MaxUnsignedLongProducesSomeOutput_53) {
  YAML::Emitter emitter;

  const auto v = std::numeric_limits<unsigned long>::max();
  emitter << v;

  EXPECT_FALSE(SafeStr(emitter).empty());
  EXPECT_GE(emitter.size(), std::size_t{1});
}

}  // namespace
