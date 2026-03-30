// File: compiler_dtor_tests_288.cc
#include <type_traits>
#include "gtest/gtest.h"

// Pull in the public class declaration/definition as provided.
#include "../../TestProjects/re2/re2/compile.cc"  // adjust include path if needed

namespace {

using re2::Compiler;

// ---------- Compile-time interface checks ----------

TEST(CompilerTest_288, CopyCtorIsDeleted_288) {
  static_assert(!std::is_copy_constructible<Compiler>::value,
                "Compiler must not be copy-constructible");
}

TEST(CompilerTest_288, CopyAssignIsDeleted_288) {
  static_assert(!std::is_copy_assignable<Compiler>::value,
                "Compiler must not be copy-assignable");
}

TEST(CompilerTest_288, HasVirtualDestructor_288) {
  // The destructor uses 'override' in the interface; ensure it’s virtual.
  static_assert(std::has_virtual_destructor<Compiler>::value,
                "Compiler should have a virtual destructor");
}

// ---------- Runtime smoke tests for construction/destruction ----------

TEST(CompilerTest_288, StackConstructAndDestroyDoesNotCrash_288) {
  // Observed behavior: constructing and allowing destruction should be safe.
  // We do not assert internal effects; just verify no crash.
  Compiler c;
  SUCCEED();
}

TEST(CompilerTest_288, HeapConstructAndDeleteDoesNotCrash_288) {
  // Create/destroy via heap to exercise ~Compiler(); ensure no crash.
  auto* c = new Compiler();
  delete c;
  SUCCEED();
}

}  // namespace
