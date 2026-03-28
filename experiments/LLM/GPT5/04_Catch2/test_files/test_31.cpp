// File: make_unique_tests_31.cpp
#include <gtest/gtest.h>
#include <string>
#include <stdexcept>
#include "Catch2/src/catch2/internal/catch_unique_ptr.hpp"

namespace {

using Catch::Detail::make_unique;

// --- Helpers used only to observe externally visible behavior ---

struct DefaultConstructible31 {
    int v = 0;
};

struct Widget31 {
    int a;
    std::string b;
    Widget31(int aa, std::string bb) : a(aa), b(std::move(bb)) {}
};

struct MoveOnly31 {
    int x;
    explicit MoveOnly31(int v) : x(v) {}
    MoveOnly31(const MoveOnly31&) = delete;
    MoveOnly31& operator=(const MoveOnly31&) = delete;
    MoveOnly31(MoveOnly31&&) = default;
    MoveOnly31& operator=(MoveOnly31&&) = default;
};

struct Holder31 {
    MoveOnly31 m;
    explicit Holder31(MoveOnly31&& mm) : m(std::move(mm)) {}
};

struct ThrowsOnCtor31 {
    ThrowsOnCtor31() { throw std::runtime_error("boom"); }
};

struct Tracker31 {
    static int live;
    Tracker31() { ++live; }
    ~Tracker31() { --live; }
    Tracker31(const Tracker31&) = delete;
    Tracker31& operator=(const Tracker31&) = delete;
};
int Tracker31::live = 0;

// --- Tests ---

TEST(MakeUniqueTest_31, DefaultConstructsNonNull_31) {
    auto p = make_unique<DefaultConstructible31>();
    EXPECT_NE(p.get(), nullptr);
    EXPECT_EQ(p->v, 0);
}

TEST(MakeUniqueTest_31, ForwardsArgumentsToConstructor_31) {
    auto p = make_unique<Widget31>(42, std::string("hello"));
    ASSERT_NE(p.get(), nullptr);
    EXPECT_EQ(p->a, 42);
    EXPECT_EQ(p->b, "hello");
}

TEST(MakeUniqueTest_31, PerfectForwardingWithMoveOnlyArgument_31) {
    auto p = make_unique<Holder31>(MoveOnly31{7}); // rvalue should be perfectly forwarded
    ASSERT_NE(p.get(), nullptr);
    EXPECT_EQ(p->m.x, 7);
}

TEST(MakeUniqueTest_31, PropagatesConstructorExceptions_31) {
    EXPECT_THROW({
        auto p = make_unique<ThrowsOnCtor31>();
        (void)p; // avoid unused warning
    }, std::runtime_error);
}

TEST(MakeUniqueTest_31, DestructorInvokedExactlyOnce_31) {
    EXPECT_EQ(Tracker31::live, 0);
    {
        auto p = make_unique<Tracker31>();
        EXPECT_EQ(Tracker31::live, 1); // constructed
        EXPECT_NE(p.get(), nullptr);
    }
    EXPECT_EQ(Tracker31::live, 0); // destroyed once after leaving scope
}

TEST(MakeUniqueTest_31, UniqueOwnershipTransfersOnMove_31) {
    auto p1 = make_unique<int>(5);
    ASSERT_NE(p1.get(), nullptr);
    auto p2 = std::move(p1);  // move-construct
    EXPECT_EQ(p1.get(), nullptr); // source released
    ASSERT_NE(p2.get(), nullptr);
    EXPECT_EQ(*p2, 5);
}

} // namespace
