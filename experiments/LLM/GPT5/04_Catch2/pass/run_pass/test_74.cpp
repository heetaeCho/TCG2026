// RawMemoryToString_tests_74.cpp
#include <gtest/gtest.h>
#include "catch2/catch_tostring.hpp"

namespace {

using Catch::Detail::rawMemoryToString;

struct WithPadding {
    char c;
    int  i;
};

struct NonCopyable {
    NonCopyable() = default;
    NonCopyable(const NonCopyable&) = delete;
    int value{7};
};

struct EmptyStruct {};

// --- Tests ---

TEST(RawMemoryToStringTest_74, ForwardsToPointerOverload_Int_74) {
    int x = 42;
    EXPECT_NO_THROW({
        const std::string byT     = rawMemoryToString(x);
        const std::string byPtrSz = rawMemoryToString(&x, sizeof(x));
        EXPECT_EQ(byT, byPtrSz);
    });
}

TEST(RawMemoryToStringTest_74, ForwardsToPointerOverload_Double_74) {
    double d = 3.141592653589793;
    EXPECT_NO_THROW({
        const std::string byT     = rawMemoryToString(d);
        const std::string byPtrSz = rawMemoryToString(&d, sizeof(d));
        EXPECT_EQ(byT, byPtrSz);
    });
}

TEST(RawMemoryToStringTest_74, ForwardsToPointerOverload_StructWithPadding_74) {
    WithPadding wp{'A', 12345};
    EXPECT_NO_THROW({
        const std::string byT     = rawMemoryToString(wp);
        const std::string byPtrSz = rawMemoryToString(&wp, sizeof(wp));
        EXPECT_EQ(byT, byPtrSz);
    });
}

TEST(RawMemoryToStringTest_74, WorksWithConstObject_74) {
    const long long ll = -9876543210LL;
    EXPECT_NO_THROW({
        const std::string byT     = rawMemoryToString(ll);
        const std::string byPtrSz = rawMemoryToString(&ll, sizeof(ll));
        EXPECT_EQ(byT, byPtrSz);
    });
}

TEST(RawMemoryToStringTest_74, WorksWithNonCopyableType_74) {
    NonCopyable nc;
    EXPECT_NO_THROW({
        const std::string byT     = rawMemoryToString(nc);
        const std::string byPtrSz = rawMemoryToString(&nc, sizeof(nc));
        EXPECT_EQ(byT, byPtrSz);
    });
}

TEST(RawMemoryToStringTest_74, HandlesEmptyLikeType_SizeIsNonZero_74) {
    EmptyStruct e{};
    // We do not assert the format/content—only that forwarding is identical.
    EXPECT_NO_THROW({
        const std::string byT     = rawMemoryToString(e);
        const std::string byPtrSz = rawMemoryToString(&e, sizeof(e));
        EXPECT_EQ(byT, byPtrSz);
    });
}

TEST(RawMemoryToStringTest_74, DeterministicForSameObject_74) {
    WithPadding wp{'Z', 777};
    const std::string first  = rawMemoryToString(wp);
    const std::string second = rawMemoryToString(wp);
    EXPECT_EQ(first, second);

    // And still equal to the pointer+size form.
    EXPECT_EQ(first, rawMemoryToString(&wp, sizeof(wp)));
}

} // namespace
