// File: version_edit_get_internal_key_test.cc

#include <gtest/gtest.h>
#include <string>

// We provide minimal test doubles for the collaborators that
// GetInternalKey uses, without re-implementing its internal logic.
namespace leveldb {

// ---- Minimal Slice test double (only what we need) ----
class Slice {
 public:
  Slice() = default;
  explicit Slice(const std::string& s) : data_(s) {}
  // Helpers for verification in tests
  const std::string& str() const { return data_; }
  // Allow assignment/copy
  Slice(const Slice&) = default;
  Slice& operator=(const Slice&) = default;

 private:
  std::string data_;
};

// ---- Controllable stub for GetLengthPrefixedSlice ----
// These globals let tests control and observe behavior.
static bool g_glps_return = false;
static Slice g_glps_out;

// Signature matches the external collaborator used by GetInternalKey.
bool GetLengthPrefixedSlice(Slice* /*input*/, Slice* out) {
  *out = g_glps_out;        // Provide whatever the test configured
  return g_glps_return;     // Return as configured by the test
}

// ---- Controllable stub for InternalKey ----
class InternalKey {
 public:
  InternalKey() = default;

  // Configurable return and observable parameter
  bool DecodeFrom(const Slice& s) {
    ++g_decode_calls;
    g_last_decode_arg = s;
    return decode_return;
  }

  // Tests set this to control DecodeFrom's return value.
  bool decode_return = false;

  // Observability (global for simplicity; could also be static members)
  static int g_decode_calls;
  static Slice g_last_decode_arg;
};

// Define static storage
int InternalKey::g_decode_calls = 0;
Slice InternalKey::g_last_decode_arg;

}  // namespace leveldb

// Include the implementation under test AFTER providing the doubles above.
// The function under test is defined as:
// namespace leveldb {
//   static bool GetInternalKey(Slice* input, InternalKey* dst) { ... }
// }
#include "db/version_edit.cc"

namespace {

// Common fixture to reset controllable state between tests
class GetInternalKeyTest_340 : public ::testing::Test {
 protected:
  void SetUp() override {
    using namespace leveldb;
    // Reset stubs to safe defaults
    leveldb::g_glps_return = false;
    leveldb::g_glps_out = leveldb::Slice();  // empty
    leveldb::InternalKey::g_decode_calls = 0;
    leveldb::InternalKey::g_last_decode_arg = leveldb::Slice();
  }
};

// ---------------- Tests ----------------

// When GetLengthPrefixedSlice fails, GetInternalKey should return false
// and must not call InternalKey::DecodeFrom.
TEST_F(GetInternalKeyTest_340, ReturnsFalseWhenLengthPrefixedSliceFails_340) {
  using namespace leveldb;
  g_glps_return = false;                       // force collaborator to fail
  g_glps_out = Slice("ignored");               // should never be used
  Slice input;                                 // value irrelevant to the stub
  InternalKey dst;                             // DecodeFrom should NOT be called

  // Invoke
  bool ok = GetInternalKey(&input, &dst);

  // Verify observable behavior
  EXPECT_FALSE(ok);
  EXPECT_EQ(0, InternalKey::g_decode_calls) << "DecodeFrom must not be called when length-prefixed parse fails";
}

// When GetLengthPrefixedSlice succeeds, GetInternalKey should forward the
// Slice to InternalKey::DecodeFrom and return its result (true case).
TEST_F(GetInternalKeyTest_340, PropagatesDecodeResultTrueAndPassesSlice_340) {
  using namespace leveldb;
  g_glps_return = true;
  const std::string payload = "payload_for_decode";
  g_glps_out = Slice(payload);                 // what the collaborator yields

  Slice input;                                 // content irrelevant for this test
  InternalKey dst;
  dst.decode_return = true;                    // make DecodeFrom succeed

  bool ok = GetInternalKey(&input, &dst);

  EXPECT_TRUE(ok) << "Should propagate true from DecodeFrom";
  EXPECT_EQ(1, InternalKey::g_decode_calls) << "DecodeFrom should be called exactly once";
  EXPECT_EQ(payload, InternalKey::g_last_decode_arg.str()) << "Slice passed to DecodeFrom must match collaborator output";
}

// Same as above but when InternalKey::DecodeFrom returns false, that should be
// propagated by GetInternalKey.
TEST_F(GetInternalKeyTest_340, PropagatesDecodeResultFalseAndPassesSlice_340) {
  using namespace leveldb;
  g_glps_return = true;
  const std::string payload = "another_payload";
  g_glps_out = Slice(payload);

  Slice input;
  InternalKey dst;
  dst.decode_return = false;                   // make DecodeFrom fail

  bool ok = GetInternalKey(&input, &dst);

  EXPECT_FALSE(ok) << "Should propagate false from DecodeFrom";
  EXPECT_EQ(1, InternalKey::g_decode_calls) << "DecodeFrom should be called exactly once";
  EXPECT_EQ(payload, InternalKey::g_last_decode_arg.str()) << "Slice passed to DecodeFrom must match collaborator output";
}

}  // namespace
