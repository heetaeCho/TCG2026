// TEST_ID: 55
#include <gtest/gtest.h>

#include <climits>
#include <cstddef>
#include <limits>
#include <ostream>
#include <sstream>
#include <string>

#include "yaml-cpp/emitter.h"

namespace {

static std::string EmitterToString(YAML::Emitter& e) {
  const char* p = e.c_str();
  const std::size_t n = e.size();
  if (!p || n == 0) return std::string();
  return std::string(p, p + n);
}

// A streambuf that always fails writes (simulates an output error).
class AlwaysFailBuf : public std::streambuf {
 protected:
  int overflow(int /*ch*/) override { return traits_type::eof(); }
  std::streamsize xsputn(const char* /*s*/, std::streamsize /*count*/) override { return 0; }
};

class OperatorShiftUnsignedLongLongTest_55 : public ::testing::Test {};

}  // namespace

TEST_F(OperatorShiftUnsignedLongLongTest_55, ReturnsSameEmitterReference_55) {
  YAML::Emitter emitter;
  YAML::Emitter& ret = (emitter << static_cast<unsigned long long>(0));
  EXPECT_EQ(&ret, &emitter);
}

TEST_F(OperatorShiftUnsignedLongLongTest_55, MatchesWriteIntegralTypeOutput_SimpleValue_55) {
  const unsigned long long v = 123456789ULL;

  YAML::Emitter via_op;
  YAML::Emitter via_direct;

  (via_op << v);
  via_direct.WriteIntegralType(v);

  EXPECT_EQ(EmitterToString(via_op), EmitterToString(via_direct));
  EXPECT_EQ(via_op.good(), via_direct.good());
  EXPECT_EQ(via_op.GetLastError(), via_direct.GetLastError());
}

TEST_F(OperatorShiftUnsignedLongLongTest_55, MatchesWriteIntegralTypeOutput_Zero_55) {
  const unsigned long long v = 0ULL;

  YAML::Emitter via_op;
  YAML::Emitter via_direct;

  (via_op << v);
  via_direct.WriteIntegralType(v);

  EXPECT_EQ(EmitterToString(via_op), EmitterToString(via_direct));
  EXPECT_EQ(via_op.good(), via_direct.good());
}

TEST_F(OperatorShiftUnsignedLongLongTest_55, MatchesWriteIntegralTypeOutput_MaxValue_55) {
  const unsigned long long v = std::numeric_limits<unsigned long long>::max();

  YAML::Emitter via_op;
  YAML::Emitter via_direct;

  (via_op << v);
  via_direct.WriteIntegralType(v);

  EXPECT_EQ(EmitterToString(via_op), EmitterToString(via_direct));
  EXPECT_EQ(via_op.good(), via_direct.good());
}

TEST_F(OperatorShiftUnsignedLongLongTest_55, ChainingOperatorAppendsConsistentlyWithDirectCalls_55) {
  const unsigned long long a = 1ULL;
  const unsigned long long b = 42ULL;
  const unsigned long long c = 999999999999ULL;

  YAML::Emitter via_op;
  YAML::Emitter via_direct;

  via_op << a << b << c;

  via_direct.WriteIntegralType(a);
  via_direct.WriteIntegralType(b);
  via_direct.WriteIntegralType(c);

  EXPECT_EQ(EmitterToString(via_op), EmitterToString(via_direct));
  EXPECT_EQ(via_op.good(), via_direct.good());
}

TEST_F(OperatorShiftUnsignedLongLongTest_55, WorksWithStreamConstructorAndIsChainable_55) {
  std::stringstream ss;
  YAML::Emitter emitter(ss);

  YAML::Emitter& ret = (emitter << 7ULL << 8ULL);
  EXPECT_EQ(&ret, &emitter);

  // We don't assume how/when the Emitter writes into the provided stream; we only
  // check observable Emitter output stays consistent with itself.
  const std::string out = EmitterToString(emitter);
  EXPECT_FALSE(out.empty());
}

TEST_F(OperatorShiftUnsignedLongLongTest_55, OutputErrorDoesNotCrashAndReturnsReference_55) {
  AlwaysFailBuf buf;
  std::ostream failing_stream(&buf);
  YAML::Emitter emitter(failing_stream);

  // Observable requirement: should not crash; should return same emitter reference.
  EXPECT_NO_THROW({
    YAML::Emitter& ret = (emitter << 123ULL);
    EXPECT_EQ(&ret, &emitter);
  });

  // If an error becomes observable, ensure error reporting is coherent.
  if (!emitter.good()) {
    EXPECT_FALSE(emitter.GetLastError().empty());
  }
}
