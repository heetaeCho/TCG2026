// TEST_ID: 385
// File: PostScriptFunction_getCodeString_tests.cpp

#include <gtest/gtest.h>

#include <type_traits>
#include <utility>

// Poppler headers
#include "poppler/Function.h"

namespace {

using ::PostScriptFunction;
using ::GooString;

TEST(PostScriptFunctionTest_385, GetCodeString_HasExpectedMemberFunctionPointerType_385) {
  // Verify the exact signature of getCodeString() from the public interface.
  using Expected = const GooString* (PostScriptFunction::*)() const;

  static_assert(std::is_same_v<decltype(&PostScriptFunction::getCodeString), Expected>,
                "PostScriptFunction::getCodeString must have signature "
                "'const GooString* () const'.");

  SUCCEED();
}

TEST(PostScriptFunctionTest_385, GetCodeString_ReturnTypeIsPointerToConstGooString_385) {
  // Verify return type is exactly const GooString* (not GooString*, not reference, etc.).
  using Ret = decltype(std::declval<const PostScriptFunction&>().getCodeString());
  static_assert(std::is_same_v<Ret, const GooString*>,
                "getCodeString() must return 'const GooString*'.");

  SUCCEED();
}

TEST(PostScriptFunctionTest_385, GetCodeString_IsCallableOnConstInstance_385) {
  // This test validates const-correctness (callable on const object) in an unevaluated context.
  (void)sizeof(decltype(std::declval<const PostScriptFunction&>().getCodeString()));
  SUCCEED();
}

TEST(PostScriptFunctionTest_385, GetCodeString_IsPubliclyAccessible_385) {
  // Taking the address of the member function is only possible if it's accessible.
  auto ptr = &PostScriptFunction::getCodeString;
  (void)ptr;
  SUCCEED();
}

}  // namespace