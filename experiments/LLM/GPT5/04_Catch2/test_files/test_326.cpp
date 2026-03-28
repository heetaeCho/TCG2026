// File: make_generators_tests_326.cpp
#include <gtest/gtest.h>
#include <memory>
#include <string>

// Header under test
#include "catch2/generators/catch_generators.hpp"

using namespace Catch::Generators;

// ---------- Helper types for observable effects ----------

// Move-only payload holder to verify perfect forwarding of rvalues into T
struct MoveOnlyBox {
    std::unique_ptr<int> ptr;
    explicit MoveOnlyBox(std::unique_ptr<int>&& p) : ptr(std::move(p)) {}
    int value() const { return ptr ? *ptr : -1; }
};

// Source type with both copy and move paths
struct Source {
    int id;
    explicit Source(int i) : id(i) {}
    Source(const Source&)            = default;
    Source(Source&&) noexcept        = default;
};

// Destination type that records whether it was constructed from lvalue or rvalue
struct RecordConstruct {
    bool fromMove = false;
    int  id = -1;

    RecordConstruct(const Source& s) : fromMove(false), id(s.id) {}
    RecordConstruct(Source&& s)      : fromMove(true),  id(s.id) {}
};

// ---------- Test fixture ----------
class MakeGeneratorsTest_326 : public ::testing::Test {};

// [Normal] Conversion happens via T(U) and yields that value exactly once.
TEST_F(MakeGeneratorsTest_326, ConvertsCStrToStdString_326) {
    auto gen = makeGenerators(as<std::string>{}, "hello");
    ASSERT_TRUE(gen.next());                // first (and only) value is available
    EXPECT_EQ(gen.get(), std::string("hello"));
    EXPECT_FALSE(gen.next());               // no more values
}

// [Boundary/Forwarding] Rvalue is perfectly forwarded into T's ctor (move-only).
TEST_F(MakeGeneratorsTest_326, ForwardsRvalueMoveOnly_326) {
    std::unique_ptr<int> up = std::make_unique<int>(7);

    auto gen = makeGenerators(as<MoveOnlyBox>{}, std::move(up));

    // The source unique_ptr was moved-from when passed as rvalue.
    EXPECT_EQ(up, nullptr);

    ASSERT_TRUE(gen.next());
    EXPECT_EQ(gen.get().value(), 7);
    EXPECT_FALSE(gen.next());
}

// [Forwarding] Lvalue -> lvalue-ctor used; Rvalue -> rvalue-ctor used.
TEST_F(MakeGeneratorsTest_326, UsesLvalueOrRvalueCtorAsAppropriate_326) {
    // Lvalue case
    Source s1{5};
    auto gen1 = makeGenerators(as<RecordConstruct>{}, s1);
    ASSERT_TRUE(gen1.next());
    EXPECT_FALSE(gen1.get().fromMove);
    EXPECT_EQ(gen1.get().id, 5);
    EXPECT_FALSE(gen1.next());

    // Rvalue case
    Source s2{9};
    auto gen2 = makeGenerators(as<RecordConstruct>{}, std::move(s2));
    ASSERT_TRUE(gen2.next());
    EXPECT_TRUE(gen2.get().fromMove);
    EXPECT_EQ(gen2.get().id, 9);
    EXPECT_FALSE(gen2.next());
}

// [Sequencing] Returned generator yields the converted first value,
// then continues with additional provided generators in order.
TEST_F(MakeGeneratorsTest_326, PreservesOrderWithAdditionalGenerators_326) {
    auto gen = makeGenerators(as<int>{}, 1, value(2), value(3));

    ASSERT_TRUE(gen.next());  EXPECT_EQ(gen.get(), 1);
    ASSERT_TRUE(gen.next());  EXPECT_EQ(gen.get(), 2);
    ASSERT_TRUE(gen.next());  EXPECT_EQ(gen.get(), 3);
    EXPECT_FALSE(gen.next());
}
