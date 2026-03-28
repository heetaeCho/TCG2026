// Object_getRef_ut_104.cpp
#include <gtest/gtest.h>

#include <type_traits>
#include <utility>

// Poppler
#include "poppler/Object.h"

namespace {

// --- Detection helpers (so tests compile across Poppler variants) ---

template <typename T, typename = void>
struct has_num_member : std::false_type {};
template <typename T>
struct has_num_member<T, std::void_t<decltype(std::declval<T&>().num)>> : std::true_type {};

template <typename T, typename = void>
struct has_gen_member : std::false_type {};
template <typename T>
struct has_gen_member<T, std::void_t<decltype(std::declval<T&>().gen)>> : std::true_type {};

static Object MakeRefObjectOrSkip(int num, int gen) {
  // Many Poppler versions provide Object(Ref) or similar; others may not.
  if constexpr (std::is_constructible_v<Object, Ref>) {
    Ref r{};
    if constexpr (has_num_member<Ref>::value) r.num = num;
    if constexpr (has_gen_member<Ref>::value) r.gen = gen;
    return Object(r);
  } else {
    GTEST_SKIP() << "This Poppler build does not expose a public Object(Ref) constructor; "
                    "cannot construct a ref Object via the public interface for getRef() normal-case testing.";
  }
}

#if GTEST_HAS_DEATH_TEST
static void ExpectGetRefDies(const Object &o) {
  // OBJECT_TYPE_CHECK is typically an assert/abort-style check.
  // Use a broad matcher to avoid coupling to exact messages.
  EXPECT_DEATH(
      {
        // NOLINTNEXTLINE(clang-analyzer-deadcode.DeadStores)
        volatile Ref r = o.getRef();
        (void)r;
      },
      ".*");
}
#endif

} // namespace

class ObjectGetRefTest_104 : public ::testing::Test {};

// -------------------- Death / error-path tests --------------------

#if GTEST_HAS_DEATH_TEST
TEST_F(ObjectGetRefTest_104, GetRefDiesWhenNotRef_Bool_104) {
  Object o(true);
  ExpectGetRefDies(o);
}

TEST_F(ObjectGetRefTest_104, GetRefDiesWhenNotRef_Int_104) {
  Object o(123);
  ExpectGetRefDies(o);
}

TEST_F(ObjectGetRefTest_104, GetRefDiesWhenNotRef_Null_104) {
  Object o = Object::null();
  ExpectGetRefDies(o);
}
#endif

// -------------------- Normal-operation tests (if constructible) --------------------

TEST_F(ObjectGetRefTest_104, GetRefReturnsSameValueAsAccessors_104) {
  Object o = MakeRefObjectOrSkip(/*num=*/7, /*gen=*/3);

  const Ref r = o.getRef();

  // Verify observable consistency via public accessors.
  // We avoid assuming Ref field names exist; only compare via getRefNum/getRefGen.
  EXPECT_EQ(o.getRefNum(), r.num);
  EXPECT_EQ(o.getRefGen(), r.gen);
}

TEST_F(ObjectGetRefTest_104, GetRefSurvivesMoveConstruction_104) {
  Object src = MakeRefObjectOrSkip(/*num=*/42, /*gen=*/0);

  Object moved(std::move(src));

  const Ref r = moved.getRef();
  EXPECT_EQ(moved.getRefNum(), r.num);
  EXPECT_EQ(moved.getRefGen(), r.gen);
}

#if GTEST_HAS_DEATH_TEST
TEST_F(ObjectGetRefTest_104, GetRefNumDiesWhenNotRef_104) {
  Object o(false);
  EXPECT_DEATH(
      {
        // NOLINTNEXTLINE(clang-analyzer-deadcode.DeadStores)
        volatile int n = o.getRefNum();
        (void)n;
      },
      ".*");
}

TEST_F(ObjectGetRefTest_104, GetRefGenDiesWhenNotRef_104) {
  Object o(0);
  EXPECT_DEATH(
      {
        // NOLINTNEXTLINE(clang-analyzer-deadcode.DeadStores)
        volatile int g = o.getRefGen();
        (void)g;
      },
      ".*");
}
#endif