// TEST_ID: 10
// File: slice_to_const_base_test_10.cpp

#include <gtest/gtest.h>

#include <type_traits>
#include <utility>

#include "exiv2/slice.hpp"

namespace {

// A minimal storage template to satisfy the template-template parameter requirement.
// We do not assume anything about Exiv2 internals beyond what is needed to form types.
template <typename T, typename...>
struct TestStorage_10 {
  // Intentionally empty: tests below only require type formation, not construction.
};

// Expose protected to_const_base() (per the "Known or Inferred Dependencies" signature).
template <typename DataT>
struct ExposeToConstBase_10
    : public Exiv2::Internal::MutableSliceBase<TestStorage_10, DataT> {
  using Base = Exiv2::Internal::MutableSliceBase<TestStorage_10, DataT>;
  using Base::to_const_base;  // expose for testing
};

}  // namespace

TEST(SliceTest_10, ToConstBaseReturnTypeUsesConstDataType_10) {
  using DataT = unsigned char;
  using Exposed = ExposeToConstBase_10<DataT>;
  using Expected =
      Exiv2::Internal::ConstSliceBase<TestStorage_10, const DataT>;

  // Verify the declared/observable type contract: return type is ConstSliceBase<storage_type, const data_type>.
  static_assert(std::is_same_v<decltype(std::declval<const Exposed&>().to_const_base()),
                               Expected>,
                "to_const_base() must return ConstSliceBase<storage_type, const data_type>.");

  SUCCEED();
}

TEST(SliceTest_10, ToConstBaseIsNoexcept_10) {
  using DataT = unsigned char;
  using Exposed = ExposeToConstBase_10<DataT>;

  // Verify the declared exception specification.
  static_assert(noexcept(std::declval<const Exposed&>().to_const_base()),
                "to_const_base() must be noexcept.");

  SUCCEED();
}

TEST(SliceTest_10, ToConstBaseCallableOnConstObject_10) {
  using DataT = unsigned char;
  using Exposed = ExposeToConstBase_10<DataT>;

  // Ensure the expression is well-formed on a const object reference (observable API surface).
  using Ret = decltype(std::declval<const Exposed&>().to_const_base());
  static_assert(std::is_object_v<Ret>, "Return type of to_const_base() should be an object type.");

  SUCCEED();
}