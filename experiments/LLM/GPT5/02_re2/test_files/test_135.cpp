// File: regexp_status_test_135.cc
#include <gtest/gtest.h>
#include "re2/regexp.h"

namespace {

using re2::RegexpStatus;

// A small fixture in case future tests need common setup.
class RegexpStatusTest_135 : public ::testing::Test {};

// [Behavior] Destructor should safely handle when no tmp is set (nullptr).
TEST_F(RegexpStatusTest_135, DtorHandlesNullTmp_135) {
  // Construct and immediately destroy; should not crash.
  RegexpStatus status;
  // No explicit assertions: success is "no crash / no ASAN error".
}

// [Behavior] Destructor should delete a heap-allocated string set via set_tmp.
TEST_F(RegexpStatusTest_135, DtorDeletesOwnedTmpOnce_135) {
  auto* s = new std::string("owned-by-status");
  {
    RegexpStatus status;
    status.set_tmp(s);
    // Going out of scope should delete the std::string exactly once.
    // We can’t directly assert on delete count without intrusive hooks;
    // the observable contract we can verify here is simply that this does not crash.
  }
  // If the destructor attempted a double delete or skipped delete entirely,
  // sanitizers / valgrind in CI would catch it. In plain runs, this must not crash.
}

// [Behavior] Copy should not cause double free upon destruction of both objects.
TEST_F(RegexpStatusTest_135, CopyThenDestroyBoth_NoDoubleFree_135) {
  auto* s = new std::string("copy-source-buffer");
  RegexpStatus src;
  src.set_tmp(s);

  RegexpStatus dst;
  // Exercise the public Copy API. We do not assume deep/shallow semantics,
  // only that destroying both objects afterward is safe (no double delete).
  dst.Copy(src);

  // Scope exit: both destructors run; test passes if no crash / no sanitizer errors.
}

// [Behavior] Copy when source has no tmp should still be safe.
TEST_F(RegexpStatusTest_135, CopyFromNullTmpSource_135) {
  RegexpStatus src;  // tmp_ is effectively null by default usage
  RegexpStatus dst;
  dst.Copy(src);
  // Scope exit: no crash.
}

// [Behavior] Overwriting tmp with nullptr should be safe to destroy.
// (We only check that it does not crash. We do not assert on ownership policy.)
TEST_F(RegexpStatusTest_135, SetTmpNullThenDestroy_135) {
  auto* s = new std::string("maybe-detached");
  RegexpStatus status;
  status.set_tmp(s);
  status.set_tmp(nullptr);  // Observable contract: must remain safe to destroy.
  // Scope exit: no crash (leak detection left to external tools if used).
}

}  // namespace
