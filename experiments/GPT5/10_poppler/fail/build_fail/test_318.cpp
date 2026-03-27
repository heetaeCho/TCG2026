// SPDX-License-Identifier: GPL-2.0-or-later
// File: LinkSound_test_318.cpp
//
// Unit tests for LinkSound::getSynchronous()
// Interface under test (from poppler/Link.h):
//   class LinkSound { public: bool getSynchronous() const { return sync; } };
//
// Notes:
// - Treat LinkSound as a black box.
// - Build sound action objects using public/poppler types only (Object/Dict).
// - Use broad compatibility helpers because poppler Object/Dict APIs differ across versions.

#include <gtest/gtest.h>

#include <type_traits>
#include <utility>

#include "poppler/Link.h"

// Poppler commonly exposes these in global namespace in older trees.
#include "poppler/Object.h"
#include "poppler/Dict.h"

namespace {

// ---- SFINAE helpers to support multiple poppler Object/Dict APIs ----

template <typename T, typename = void>
struct has_initBool : std::false_type {};
template <typename T>
struct has_initBool<T, std::void_t<decltype(std::declval<T&>().initBool(true))>> : std::true_type {};

template <typename T, typename = void>
struct has_initName : std::false_type {};
template <typename T>
struct has_initName<T, std::void_t<decltype(std::declval<T&>().initName("Sound"))>> : std::true_type {};

template <typename T, typename = void>
struct has_initReal : std::false_type {};
template <typename T>
struct has_initReal<T, std::void_t<decltype(std::declval<T&>().initReal(0.5))>> : std::true_type {};

template <typename T, typename = void>
struct has_initDict : std::false_type {};
template <typename T>
struct has_initDict<T, std::void_t<decltype(std::declval<T&>().initDict(static_cast<XRef*>(nullptr)))>> : std::true_type {};

template <typename D, typename = void>
struct has_add_with_rvalue : std::false_type {};
template <typename D>
struct has_add_with_rvalue<D,
                          std::void_t<decltype(std::declval<D&>().add("Key", std::declval<Object&&>()))>>
    : std::true_type {};

template <typename D, typename = void>
struct has_add_with_lvalue : std::false_type {};
template <typename D>
struct has_add_with_lvalue<D, std::void_t<decltype(std::declval<D&>().add("Key", std::declval<Object*>()))>>
    : std::true_type {};

template <typename O, typename = void>
struct has_getDict : std::false_type {};
template <typename O>
struct has_getDict<O, std::void_t<decltype(std::declval<O&>().getDict())>> : std::true_type {};

static Object MakeBoolObject(bool v) {
  Object o;
  if constexpr (has_initBool<Object>::value) {
    o.initBool(v);
  } else {
    // Some poppler versions have constructors like Object(bool)
    // (If neither exists, compilation will fail, which is preferable to re-implementing behavior.)
    o = Object(v);
  }
  return o;
}

static Object MakeNameObject(const char* name) {
  Object o;
  if constexpr (has_initName<Object>::value) {
    o.initName(const_cast<char*>(name));
  } else {
    o = Object(objName);
    o.getName(); // touch to avoid unused warnings in some builds
    // If this path doesn't compile in your tree, prefer the initName() branch above.
  }
  return o;
}

static Object MakeRealObject(double v) {
  Object o;
  if constexpr (has_initReal<Object>::value) {
    o.initReal(v);
  } else {
    o = Object(v);
  }
  return o;
}

// Add entry to a Dict in a way that matches multiple poppler APIs.
static void DictAddCompat(Dict* dict, const char* key, Object&& val) {
  ASSERT_NE(dict, nullptr);
  if constexpr (has_add_with_rvalue<Dict>::value) {
    dict->add(key, std::move(val));
  } else if constexpr (has_add_with_lvalue<Dict>::value) {
    // Older APIs sometimes expect an Object* that they take ownership of.
    Object* heapObj = new Object(std::move(val));
    dict->add(key, heapObj);
  } else {
    // If your poppler tree uses a different method name/signature, update this helper,
    // but do not change LinkSound behavior assumptions.
    FAIL() << "Unsupported Dict::add signature in this poppler version";
  }
}

static Dict* GetDictCompat(Object& obj) {
  if constexpr (has_getDict<Object>::value) {
    return obj.getDict();
  } else {
    return nullptr;
  }
}

static Object MakeSoundActionDictObject(bool includeSynchronous, bool synchronousValue) {
  Object actionDictObj;

  // Many poppler versions support initDict(XRef*), where XRef can be null for synthetic objects.
  if constexpr (has_initDict<Object>::value) {
    actionDictObj.initDict(nullptr);
  } else {
    // If initDict isn't available, some trees provide constructors/factories.
    // Prefer initDict; if your tree doesn't support it, adapt this helper to your API.
    FAIL() << "Object::initDict(XRef*) not available in this poppler version";
  }

  Dict* dict = GetDictCompat(actionDictObj);
  ASSERT_NE(dict, nullptr);

  // Set /S /Sound (common for sound actions). Even if LinkSound ignores it, it should be safe.
  // This helps make the object resemble a real PDF Sound action dictionary.
  // If your version uses different keys, LinkSound should still remain robust.
  DictAddCompat(dict, "S", MakeNameObject("Sound"));

  if (includeSynchronous) {
    DictAddCompat(dict, "Synchronous", MakeBoolObject(synchronousValue));
  }

  return actionDictObj;
}

class LinkSoundTest_318 : public ::testing::Test {};

}  // namespace

// Normal operation: when the input object explicitly sets /Synchronous true,
// LinkSound::getSynchronous() should report true.
TEST_F(LinkSoundTest_318, GetSynchronous_TrueWhenKeyPresent_318) {
  Object action = MakeSoundActionDictObject(/*includeSynchronous=*/true, /*synchronousValue=*/true);

  LinkSound linkSound(&action);

  // If the object is well-formed enough, it should be OK; if your tree is stricter,
  // this expectation can be relaxed, but getSynchronous should still be callable.
  EXPECT_TRUE(linkSound.isOk());

  EXPECT_TRUE(linkSound.getSynchronous());
  // Determinism/idempotence boundary: calling multiple times should be stable.
  EXPECT_EQ(linkSound.getSynchronous(), linkSound.getSynchronous());
}

// Normal operation: when /Synchronous is explicitly false, getSynchronous should report false.
TEST_F(LinkSoundTest_318, GetSynchronous_FalseWhenKeyPresent_318) {
  Object action = MakeSoundActionDictObject(/*includeSynchronous=*/true, /*synchronousValue=*/false);

  LinkSound linkSound(&action);

  EXPECT_TRUE(linkSound.isOk());
  EXPECT_FALSE(linkSound.getSynchronous());
  EXPECT_EQ(linkSound.getSynchronous(), linkSound.getSynchronous());
}

// Boundary condition: dictionary present but /Synchronous missing.
// Observable expectation: getter should be callable and return a stable value.
// (Many implementations default missing boolean fields to false.)
TEST_F(LinkSoundTest_318, GetSynchronous_MissingKeyIsStable_318) {
  Object action = MakeSoundActionDictObject(/*includeSynchronous=*/false, /*synchronousValue=*/false);

  LinkSound linkSound(&action);

  // Regardless of isOk (implementation-defined), getSynchronous must be callable.
  const bool first = linkSound.getSynchronous();
  const bool second = linkSound.getSynchronous();
  EXPECT_EQ(first, second);

  // Prefer an explicit expectation for typical behavior; if your tree differs,
  // adjust to match the observable contract in your codebase.
  EXPECT_FALSE(first);
}

// Exceptional / error case: null input pointer.
// Observable behavior: construction should not crash; isOk should reflect failure if exposed;
// getSynchronous should remain callable and stable.
TEST_F(LinkSoundTest_318, NullObjectPointer_DoesNotCrash_318) {
  LinkSound linkSound(nullptr);

  EXPECT_FALSE(linkSound.isOk());

  const bool first = linkSound.getSynchronous();
  const bool second = linkSound.getSynchronous();
  EXPECT_EQ(first, second);

  // A safe default for an invalid action is typically "false".
  EXPECT_FALSE(first);
}