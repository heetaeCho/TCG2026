// TEST_ID: 359
// Unit tests for SampledFunction::getType()
// File: SampledFunction_getType_test_359.cpp

#include <gtest/gtest.h>

#include <memory>
#include <type_traits>

#if __has_include("poppler/Function.h")
#include "poppler/Function.h"
#elif __has_include("Function.h")
#include "Function.h"
#else
#error "Cannot find Function.h (expected poppler/Function.h or Function.h)"
#endif

// Poppler typically provides Object/Dict in Object.h (or similar). Try common include paths.
#if __has_include("poppler/Object.h")
#include "poppler/Object.h"
#elif __has_include("Object.h")
#include "Object.h"
#endif

namespace {

// --- Small compile-time detection helpers (C++17) ---

template <typename T, typename... Args>
struct is_nothrow_constructible_helper {
  static constexpr bool value = std::is_nothrow_constructible<T, Args...>::value;
};

template <typename DictT>
std::unique_ptr<DictT> MakeDictIfPossible() {
  // Prefer Dict(nullptr) if available, else Dict().
  if constexpr (std::is_constructible<DictT, std::nullptr_t>::value) {
    return std::unique_ptr<DictT>(new DictT(nullptr));
  } else if constexpr (std::is_default_constructible<DictT>::value) {
    return std::unique_ptr<DictT>(new DictT());
  } else {
    return nullptr;
  }
}

template <typename ObjectT, typename DictT>
ObjectT MakeFuncObjectAsNullOrDict(DictT* /*dict*/) {
  // Create a benign Object if possible.
  // We avoid assuming any specific "init" API exists; default construction is most common.
  if constexpr (std::is_default_constructible<ObjectT>::value) {
    return ObjectT();
  } else {
    // If Object isn't default-constructible in this build, this will hard-error anyway.
    // Keep as a last resort.
    return ObjectT();
  }
}

// Attempt to construct SampledFunction using the constructor (Object*, Dict*).
// If the build does not expose Object/Dict, the test compilation will fail; this is intentional
// because the interface snippet indicates this ctor exists in the real codebase.
std::unique_ptr<SampledFunction> TryMakeSampledFunction() {
#if defined(SampledFunction) || 1
  // If Dict/Object types are available, use them. Otherwise, pass nullptrs (best-effort).
  // The goal is to test *observable* behavior of getType(), not internals.
  //
  // NOTE: This assumes SampledFunction has a ctor: SampledFunction(Object* funcObj, Dict* dict)
  // as indicated in the provided dependency list.
  Dict* dictRaw = nullptr;
  Object* objRaw = nullptr;

  // Create Dict if type is known.
#ifdef Dict
  auto dictHolder = MakeDictIfPossible<Dict>();
  dictRaw = dictHolder.get();
#else
  std::unique_ptr<Dict> dictHolder;
  // If Dict isn't visible, keep nullptr.
#endif

#ifdef Object
  Object objHolder = MakeFuncObjectAsNullOrDict<Object, Dict>(dictRaw);
  objRaw = &objHolder;
#else
  // If Object isn't visible, keep nullptr.
#endif

  // We need storage duration long enough for ctor call; if Object exists, keep it alive.
#ifdef Object
  // Re-create with stable storage and construct.
  auto dictHolder2 =
#ifdef Dict
      MakeDictIfPossible<Dict>()
#else
      std::unique_ptr<Dict>()
#endif
      ;
  dictRaw = dictHolder2.get();

  auto objHolder2 = std::make_unique<Object>(MakeFuncObjectAsNullOrDict<Object, Dict>(dictRaw));
  objRaw = objHolder2.get();

  // Construct the SampledFunction, keeping helpers alive via a wrapper struct.
  struct Bundle {
    std::unique_ptr<Dict> dict;
    std::unique_ptr<Object> obj;
    std::unique_ptr<SampledFunction> func;
  };
  auto bundle = std::make_unique<Bundle>();
#ifdef Dict
  bundle->dict = MakeDictIfPossible<Dict>();
  dictRaw = bundle->dict.get();
#else
  dictRaw = nullptr;
#endif
  bundle->obj = std::make_unique<Object>(MakeFuncObjectAsNullOrDict<Object, Dict>(dictRaw));
  objRaw = bundle->obj.get();

  // If construction throws (uncommon in Poppler), let the test handle it.
  bundle->func = std::make_unique<SampledFunction>(objRaw, dictRaw);

  // Return only the function (bundle will be destroyed) -> can't.
  // So instead, don't use Bundle: just return function directly. But we must keep Object/Dict alive.
  // Simplest: allocate Object/Dict on heap and intentionally keep them alive for test lifetime
  // via shared_ptr captured by a custom deleter.
  //
  // Rebuild with shared ownership:
  auto dictSP =
#ifdef Dict
      std::shared_ptr<Dict>(MakeDictIfPossible<Dict>().release(), [](Dict* p) { delete p; })
#else
      std::shared_ptr<Dict>()
#endif
      ;

  auto objSP = std::shared_ptr<Object>(new Object(MakeFuncObjectAsNullOrDict<Object, Dict>(dictSP.get())),
                                       [](Object* p) { delete p; });

  // Construct SampledFunction and keep dict/object alive via a no-op deleter capturing shared_ptrs.
  SampledFunction* rawFunc = new SampledFunction(objSP.get(), dictSP.get());
  return std::unique_ptr<SampledFunction>(rawFunc);
#else
  // Fallback: attempt nullptr construction (best-effort).
  return std::make_unique<SampledFunction>(nullptr, nullptr);
#endif
#endif
}

class SampledFunctionTest_359 : public ::testing::Test {};

}  // namespace

TEST_F(SampledFunctionTest_359, GetTypeReturnsSampled_359) {
  std::unique_ptr<SampledFunction> func;
  ASSERT_NO_THROW(func = TryMakeSampledFunction());

  ASSERT_NE(func, nullptr);
  EXPECT_EQ(func->getType(), Function::Type::Sampled);
}

TEST_F(SampledFunctionTest_359, GetTypeWorksOnConstObject_359) {
  std::unique_ptr<SampledFunction> func;
  ASSERT_NO_THROW(func = TryMakeSampledFunction());
  ASSERT_NE(func, nullptr);

  const SampledFunction& cref = *func;
  EXPECT_EQ(cref.getType(), Function::Type::Sampled);
}

TEST_F(SampledFunctionTest_359, CopyPreservesTypeWhenAvailable_359) {
  std::unique_ptr<SampledFunction> func;
  ASSERT_NO_THROW(func = TryMakeSampledFunction());
  ASSERT_NE(func, nullptr);

  // copy() is part of the known interface in the dependency list.
  std::unique_ptr<Function> copied;
  ASSERT_NO_THROW(copied = func->copy());
  ASSERT_NE(copied, nullptr);

  EXPECT_EQ(copied->getType(), Function::Type::Sampled);
}

TEST_F(SampledFunctionTest_359, GetTypeIsStableAcrossMultipleCalls_359) {
  std::unique_ptr<SampledFunction> func;
  ASSERT_NO_THROW(func = TryMakeSampledFunction());
  ASSERT_NE(func, nullptr);

  const auto t1 = func->getType();
  const auto t2 = func->getType();
  const auto t3 = func->getType();

  EXPECT_EQ(t1, Function::Type::Sampled);
  EXPECT_EQ(t2, Function::Type::Sampled);
  EXPECT_EQ(t3, Function::Type::Sampled);
}