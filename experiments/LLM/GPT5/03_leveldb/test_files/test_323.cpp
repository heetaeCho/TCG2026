// db/log_reader_destructor_test_323.cc
#include "db/log_reader.h"
#include <gtest/gtest.h>
#include <memory>
#include <type_traits>

namespace leveldb {
namespace log {

// --- Basic construction/destruction smoke tests ---

// Ensures that constructing and destroying a Reader with null collaborators
// (no usage) does not crash. This exercises the destructor path that deletes
// its internal backing storage.
TEST(ReaderTest_323, ConstructAndDestroy_NoCrash_323) {
  Reader* r = new Reader(/*file=*/nullptr, /*reporter=*/nullptr,
                         /*checksum=*/true, /*initial_offset=*/0);
  // If backing storage deletion were incorrect, sanitizers/builds may crash here.
  delete r;
}

// Stack allocation is a common usage; ensure automatic destruction is safe.
TEST(ReaderTest_323, StackLifetime_NoCrash_323) {
  Reader r(/*file=*/nullptr, /*reporter=*/nullptr,
           /*checksum=*/false, /*initial_offset=*/0);
  // Leaving scope should invoke ~Reader() safely.
}

// Using smart pointers should compile and destroy cleanly via `delete`.
TEST(ReaderTest_323, UniquePtrLifetime_NoCrash_323) {
  std::unique_ptr<Reader> r(
      new Reader(/*file=*/nullptr, /*reporter=*/nullptr,
                 /*checksum=*/true, /*initial_offset=*/12345)); // arbitrary non-zero
  // Destructor will run when unique_ptr goes out of scope.
}

// --- Interface properties (compile-time) ---

// Reader must not be copyable or assignable per the interface declarations.
TEST(ReaderTest_323, NonCopyableAndNonAssignable_323) {
  static_assert(!std::is_copy_constructible<Reader>::value,
                "Reader should not be copy-constructible");
  static_assert(!std::is_copy_assignable<Reader>::value,
                "Reader should not be copy-assignable");
  SUCCEED();  // If we compiled, the static_asserts were satisfied.
}

}  // namespace log
}  // namespace leveldb
