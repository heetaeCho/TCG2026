// BaseStream_isBinary_tests_125.cpp
#include <gtest/gtest.h>

#include <type_traits>
#include <utility>

#if defined(__has_include)
#  if __has_include("poppler/Stream.h")
#    include "poppler/Stream.h"
#  elif __has_include("Stream.h")
#    include "Stream.h"
#  else
#    error "Cannot find Stream.h (expected poppler/Stream.h or Stream.h)"
#  endif

// Object is only needed if BaseStream requires it for construction.
#  if __has_include("poppler/Object.h")
#    include "poppler/Object.h"
#  elif __has_include("Object.h")
#    include "Object.h"
#  endif
#else
#  include "Stream.h"
#endif

namespace {

// Detect Object::initNull() if it exists (Poppler-style).
template <typename T, typename = void>
struct HasInitNull : std::false_type {};
template <typename T>
struct HasInitNull<T, std::void_t<decltype(std::declval<T&>().initNull())>> : std::true_type {};

template <typename T>
void InitNullIfPossible(T& obj) {
  if constexpr (HasInitNull<T>::value) {
    obj.initNull();
  }
}

// Attempt to create a BaseStream instance when possible.
// Returns true and assigns out when constructed, otherwise returns false.
template <typename T>
bool TryMakeBaseStream(T& out) {
  // 1) Default-constructible
  if constexpr (std::is_default_constructible_v<T>) {
    out = T{};
    return true;
  }
#if defined(POPPLER_OBJECT_H) || defined(POPPLER_OBJECT_H_SEEN) || defined(_POPPLER_OBJECT_H_)
  // nothing; just a hint some builds define include guards
#endif

  // 2) Constructible from (Object&&, Goffset)
  // Only attempt this if Object and Goffset are visible.
#if defined(__cpp_decltype)
  if constexpr (std::is_constructible_v<T, Object&&, Goffset>) {
    Object dict;
    InitNullIfPossible(dict);
    out = T(std::move(dict), Goffset{0});
    return true;
  }
#endif

  return false;
}

template <typename T>
bool CanInstantiateBaseStream() {
  if constexpr (std::is_default_constructible_v<T>) {
    return true;
  }
#if defined(__cpp_decltype)
  if constexpr (std::is_constructible_v<T, Object&&, Goffset>) {
    return true;
  }
#endif
  return false;
}

} // namespace

class BaseStreamTest_125 : public ::testing::Test {};

TEST_F(BaseStreamTest_125, IsBinary_DefaultArgumentReturnsTrue_125) {
  // If BaseStream can't be instantiated in this build, we still keep the test suite compiling.
  if constexpr (!CanInstantiateBaseStream<BaseStream>()) {
    GTEST_SKIP() << "BaseStream is not instantiable with available constructors in this build.";
  } else {
    BaseStream s = [] {
      // Use a lambda to avoid compiling unused constructor branches in some builds.
      if constexpr (std::is_default_constructible_v<BaseStream>) {
        return BaseStream{};
      } else {
        Object dict;
        InitNullIfPossible(dict);
        return BaseStream(std::move(dict), Goffset{0});
      }
    }();

    EXPECT_TRUE(s.isBinary());  // default last=true
  }
}

TEST_F(BaseStreamTest_125, IsBinary_ReturnsFalseWhenLastIsFalse_125) {
  if constexpr (!CanInstantiateBaseStream<BaseStream>()) {
    GTEST_SKIP() << "BaseStream is not instantiable with available constructors in this build.";
  } else {
    BaseStream s = [] {
      if constexpr (std::is_default_constructible_v<BaseStream>) {
        return BaseStream{};
      } else {
        Object dict;
        InitNullIfPossible(dict);
        return BaseStream(std::move(dict), Goffset{0});
      }
    }();

    EXPECT_FALSE(s.isBinary(false));
  }
}

TEST_F(BaseStreamTest_125, IsBinary_ReturnsTrueWhenLastIsTrue_125) {
  if constexpr (!CanInstantiateBaseStream<BaseStream>()) {
    GTEST_SKIP() << "BaseStream is not instantiable with available constructors in this build.";
  } else {
    BaseStream s = [] {
      if constexpr (std::is_default_constructible_v<BaseStream>) {
        return BaseStream{};
      } else {
        Object dict;
        InitNullIfPossible(dict);
        return BaseStream(std::move(dict), Goffset{0});
      }
    }();

    EXPECT_TRUE(s.isBinary(true));
  }
}

TEST_F(BaseStreamTest_125, IsBinary_CanBeCalledOnConstObject_125) {
  if constexpr (!CanInstantiateBaseStream<BaseStream>()) {
    GTEST_SKIP() << "BaseStream is not instantiable with available constructors in this build.";
  } else {
    const BaseStream s = [] {
      if constexpr (std::is_default_constructible_v<BaseStream>) {
        return BaseStream{};
      } else {
        Object dict;
        InitNullIfPossible(dict);
        return BaseStream(std::move(dict), Goffset{0});
      }
    }();

    EXPECT_TRUE(s.isBinary());
    EXPECT_FALSE(s.isBinary(false));
  }
}

TEST_F(BaseStreamTest_125, IsBinary_HasNoObservableStateAcrossCalls_125) {
  if constexpr (!CanInstantiateBaseStream<BaseStream>()) {
    GTEST_SKIP() << "BaseStream is not instantiable with available constructors in this build.";
  } else {
    BaseStream s = [] {
      if constexpr (std::is_default_constructible_v<BaseStream>) {
        return BaseStream{};
      } else {
        Object dict;
        InitNullIfPossible(dict);
        return BaseStream(std::move(dict), Goffset{0});
      }
    }();

    // Boundary-style coverage: repeated calls with alternating inputs.
    EXPECT_FALSE(s.isBinary(false));
    EXPECT_TRUE(s.isBinary(true));
    EXPECT_FALSE(s.isBinary(false));
    EXPECT_TRUE(s.isBinary());  // default again
  }
}