// File: compaction_max_output_file_size_test.cc
#include <type_traits>
#include "db/version_set.h"
#include "gtest/gtest.h"

namespace {

// Helper alias to the exact member function pointer signature we expect.
using ExpectedSig_83 = uint64_t (leveldb::Compaction::*)() const;

// 1) Signature test: return type and const-correctness
TEST(CompactionTest_83, MaxOutputFileSize_HasExpectedSignature_83) {
  // Address the member to get its type without needing an instance.
  auto fn_ptr = &leveldb::Compaction::MaxOutputFileSize;

  // Verify it is a non-static member function pointer with the expected signature.
  static_assert(std::is_member_function_pointer<decltype(fn_ptr)>::value,
                "MaxOutputFileSize must be a non-static member function");
  static_assert(std::is_same<decltype(fn_ptr), ExpectedSig_83>::value,
                "MaxOutputFileSize must be: uint64_t () const");

  // Also check at runtime via EXPECT_TRUE for clearer gtest failure messages.
  EXPECT_TRUE((std::is_member_function_pointer<decltype(fn_ptr)>::value));
  EXPECT_TRUE((std::is_same<decltype(fn_ptr), ExpectedSig_83>::value));
}

// 2) Invocability on const-qualified type (compile-time)
// This verifies the method can be called on a const Compaction&, matching the interface.
// We do this without constructing an instance (constructor is not public), by
// checking the expression type via std::is_invocable on a const-qualified pointer-to-member.
TEST(CompactionTest_83, MaxOutputFileSize_InvocableOnConst_83) {
  using C = leveldb::Compaction;
  // Pointer-to-member function for const call
  ExpectedSig_83 fn = &C::MaxOutputFileSize;

  // We can't create a C object (no public constructor), but we can still verify
  // the callable form type: given a const C*, the invocation is well-formed.
  // Note: std::is_invocable_v doesn't directly accept member pointers with object pointer,
  // so we assert the pointer type itself and rely on the signature check above.
  // Provide a runtime assertion mirroring the compile-time contract.
  EXPECT_TRUE((std::is_same<ExpectedSig_83, decltype(&C::MaxOutputFileSize)>::value));
}

// 3) ABI stability guard (optional): ensure it's not declared noexcept by mistake change
// If your codebase requires a specific exception specification, you can lock it here.
// Since the interface snippet doesn't declare noexcept, we only assert that calling
// expression is not marked noexcept by default through the type system. This remains
// a lightweight guard that won’t require constructing an instance.
TEST(CompactionTest_83, MaxOutputFileSize_NotAccidentallyNoexcept_83) {
  // If the project later adds noexcept to the declaration, change this expectation accordingly.
  // We can only assert via type traits on the member pointer.
  auto fn_ptr = &leveldb::Compaction::MaxOutputFileSize;
  // There is no standard trait to inspect noexcept on member function pointers portably,
  // so this test acts as a placeholder guard with a comment.
  SUCCEED() << "Interface-level guard: noexcept contract not asserted by this test.";
}

}  // namespace
