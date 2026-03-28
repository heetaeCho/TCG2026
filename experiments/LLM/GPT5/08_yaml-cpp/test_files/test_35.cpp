// TEST_ID: 35
#include <gtest/gtest.h>

#include <cmath>
#include <limits>
#include <sstream>
#include <string>

#include "yaml-cpp/emitter.h"

namespace {

class WriteStreamableTest_35 : public ::testing::Test {
protected:
  std::stringstream ss_;
  YAML::Emitter emitter_{ss_};

  std::string Out() const { return ss_.str(); }
};

TEST_F(WriteStreamableTest_35, ReturnsSelfReferenceForChaining_35) {
  YAML::Emitter* addr_before = &emitter_;
  YAML::Emitter& ref = emitter_.WriteStreamable(std::numeric_limits<double>::infinity());
  EXPECT_EQ(addr_before, &ref);
}

TEST_F(WriteStreamableTest_35, WritesQuietNaNAsDotNan_Float_35) {
  if (!std::numeric_limits<float>::has_quiet_NaN) {
    GTEST_SKIP() << "float quiet NaN not supported on this platform.";
  }

  const float nanv = std::numeric_limits<float>::quiet_NaN();
  emitter_.WriteStreamable(nanv);

  EXPECT_EQ(Out(), ".nan");
}

TEST_F(WriteStreamableTest_35, WritesPositiveInfinityAsDotInf_Double_35) {
  if (!std::numeric_limits<double>::has_infinity) {
    GTEST_SKIP() << "double infinity not supported on this platform.";
  }

  const double inf = std::numeric_limits<double>::infinity();
  emitter_.WriteStreamable(inf);

  EXPECT_EQ(Out(), ".inf");
}

TEST_F(WriteStreamableTest_35, WritesNegativeInfinityAsMinusDotInf_LongDouble_35) {
  if (!std::numeric_limits<long double>::has_infinity) {
    GTEST_SKIP() << "long double infinity not supported on this platform.";
  }

  const long double ninf = -std::numeric_limits<long double>::infinity();
  emitter_.WriteStreamable(ninf);

  EXPECT_EQ(Out(), "-.inf");
}

TEST_F(WriteStreamableTest_35, AppendsMultipleSpecialValuesInOrder_35) {
  // Build expected string based on what the platform supports.
  std::string expected;

  if (std::numeric_limits<double>::has_infinity) {
    emitter_.WriteStreamable(std::numeric_limits<double>::infinity());
    expected += ".inf";
  } else {
    GTEST_SKIP() << "infinity not supported on this platform.";
  }

  if (std::numeric_limits<double>::has_quiet_NaN) {
    emitter_.WriteStreamable(std::numeric_limits<double>::quiet_NaN());
    expected += ".nan";
  } else {
    // Still validate the first part if NaN isn't supported.
    EXPECT_EQ(Out(), expected);
    GTEST_SKIP() << "quiet NaN not supported on this platform.";
  }

  if (std::numeric_limits<double>::has_infinity) {
    emitter_.WriteStreamable(-std::numeric_limits<double>::infinity());
    expected += "-.inf";
  }

  EXPECT_EQ(Out(), expected);
}

TEST_F(WriteStreamableTest_35, IfEmitterNotGood_DoesNotModifyOutput_35) {
  // Try to create an emitter backed by a stream that's already in a bad state.
  std::ostringstream bad_stream;
  bad_stream.setstate(std::ios::badbit);

  YAML::Emitter e(bad_stream);
  const std::string before = bad_stream.str();

  // Only assert "no modification" when the emitter reports it's not good;
  // otherwise we can't observe/assume how 'good()' relates to the underlying stream.
  if (!e.good()) {
    e.WriteStreamable(std::numeric_limits<double>::infinity());
    EXPECT_EQ(bad_stream.str(), before);
  } else {
    SUCCEED() << "Emitter reports good(); cannot assert early-return behavior here.";
  }
}

}  // namespace
