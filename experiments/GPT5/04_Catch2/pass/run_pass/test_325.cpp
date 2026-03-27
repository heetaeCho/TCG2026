// File: tests/make_generators_325_tests.cpp
#include <gtest/gtest.h>

#include <catch2/generators/catch_generators.hpp>
#include <type_traits>
#include <memory>
#include <string>

namespace CG = Catch::Generators;

class MakeGeneratorsTest_325 : public ::testing::Test {};

// [Normal] Single value -> returns Generators of decayed T (int)
TEST_F(MakeGeneratorsTest_325, ReturnsGeneratorsOfDecayedT_Int_325) {
    auto g = CG::makeGenerators(123);
    using GType = decltype(g);
    EXPECT_TRUE((std::is_same<GType, CG::Generators<int>>::value));
}

// [Boundary] String literal -> decays from const char[N] to const char*
TEST_F(MakeGeneratorsTest_325, ReturnsGeneratorsOfDecayedT_StringLiteral_325) {
    auto g = CG::makeGenerators("hello");
    using GType = decltype(g);
    EXPECT_TRUE((std::is_same<GType, CG::Generators<const char*>>::value));
}

// [Normal] Lvalue input -> still decays (no reference types in Generators<T>)
TEST_F(MakeGeneratorsTest_325, LvalueInputDecaysToValueType_325) {
    std::string s = "catch2";
    auto g = CG::makeGenerators(s);
    using GType = decltype(g);
    EXPECT_TRUE((std::is_same<GType, CG::Generators<std::string>>::value));
}

// [Boundary] Const lvalue input -> decays constness appropriately
TEST_F(MakeGeneratorsTest_325, ConstLvalueInputDecays_325) {
    const int ci = 7;
    auto g = CG::makeGenerators(ci);
    using GType = decltype(g);
    EXPECT_TRUE((std::is_same<GType, CG::Generators<int>>::value));
}

// [Normal] Perfect forwarding: accepts move-only types (e.g., std::unique_ptr)
TEST_F(MakeGeneratorsTest_325, AcceptsMoveOnlyTypes_325) {
    auto g = CG::makeGenerators(std::make_unique<int>(42));
    using GType = decltype(g);
    // Return type should carry the move-only type:
    EXPECT_TRUE((std::is_same<GType, CG::Generators<std::unique_ptr<int>>>::value));

    // Also verify it's movable (useful for pipelines). This is an interface-level property.
    EXPECT_TRUE((std::is_move_constructible<GType>::value));
    auto moved = std::move(g);
    (void)moved; // silence unused warning
    SUCCEED();
}

// [Normal] Combining with additional generators via parameter pack compiles and yields expected type
TEST_F(MakeGeneratorsTest_325, CombinesWithAdditionalGenerators_325) {
    auto g = CG::makeGenerators(1, CG::value(2), CG::value(3));
    using GType = decltype(g);
    EXPECT_TRUE((std::is_same<GType, CG::Generators<int>>::value));
}
