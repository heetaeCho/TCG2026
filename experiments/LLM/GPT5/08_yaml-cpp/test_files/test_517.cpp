// TEST_ID: 517
#include <gtest/gtest.h>

#include <limits>
#include <ostream>
#include <sstream>
#include <type_traits>
#include <vector>

#include "yaml-cpp/emitter.h"

namespace {

class EmitterSetOutputCharsetTest_517 : public ::testing::Test {
 protected:
  static YAML::EMITTER_MANIP ManipFromInt(int v) {
    return static_cast<YAML::EMITTER_MANIP>(v);
  }
};

TEST_F(EmitterSetOutputCharsetTest_517, ReturnTypeIsBool_517) {
  static_assert(std::is_same_v<decltype(std::declval<YAML::Emitter&>().SetOutputCharset(
                                    std::declval<YAML::EMITTER_MANIP>())),
                                bool>,
                "Emitter::SetOutputCharset must return bool");
}

TEST_F(EmitterSetOutputCharsetTest_517, DefaultConstructedEmitter_AllowsCalling_NoThrow_517) {
  YAML::Emitter out;

  EXPECT_NO_THROW({
    (void)out.SetOutputCharset(ManipFromInt(0));
  });
}

TEST_F(EmitterSetOutputCharsetTest_517, StreamConstructedEmitter_AllowsCalling_NoThrow_517) {
  std::ostringstream oss;
  YAML::Emitter out(oss);

  EXPECT_NO_THROW({
    (void)out.SetOutputCharset(ManipFromInt(0));
  });
}

TEST_F(EmitterSetOutputCharsetTest_517, RepeatedCallSameValue_ReturnIsConsistent_517) {
  YAML::Emitter out;
  const YAML::EMITTER_MANIP value = ManipFromInt(0);

  bool first = false;
  bool second = false;

  ASSERT_NO_THROW({ first = out.SetOutputCharset(value); });
  ASSERT_NO_THROW({ second = out.SetOutputCharset(value); });

  // Same input should produce a consistent, observable result.
  EXPECT_EQ(first, second);

  // If the API reports success, the emitter should remain in a usable state.
  if (first) {
    EXPECT_TRUE(out.good());
    EXPECT_TRUE(out.GetLastError().empty());
  }
}

TEST_F(EmitterSetOutputCharsetTest_517, ExtremeValue_DoesNotCrash_AndOnFailureHasObservableSignal_517) {
  YAML::Emitter out;

  const int kExtreme = std::numeric_limits<int>::max();
  const YAML::EMITTER_MANIP extreme = ManipFromInt(kExtreme);

  bool ok = true;
  ASSERT_NO_THROW({ ok = out.SetOutputCharset(extreme); });

  // If it fails, we should be able to observe *something* via the public API.
  if (!ok) {
    const bool hasObservableSignal = (!out.good()) || (!out.GetLastError().empty());
    EXPECT_TRUE(hasObservableSignal);
  }
}

TEST_F(EmitterSetOutputCharsetTest_517, MultipleValues_DoNotThrow_AndSuccessDoesNotDegradeState_517) {
  YAML::Emitter out;

  const std::vector<int> candidates = {
      -1, 0, 1, 2, std::numeric_limits<int>::min(), std::numeric_limits<int>::max()
  };

  for (int v : candidates) {
    const YAML::EMITTER_MANIP m = ManipFromInt(v);

    bool ok = true;
    ASSERT_NO_THROW({ ok = out.SetOutputCharset(m); }) << "v=" << v;

    if (ok) {
      EXPECT_TRUE(out.good()) << "v=" << v;
      EXPECT_TRUE(out.GetLastError().empty()) << "v=" << v;
    }
  }
}

}  // namespace