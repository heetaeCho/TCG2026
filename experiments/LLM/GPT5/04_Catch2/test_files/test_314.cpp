// File: test_single_value_generator_314.cpp

#include <gtest/gtest.h>
#include <memory>
#include <string>
#include <type_traits>

// Include the class under test
#include "catch2/generators/catch_generators.hpp"

namespace CG = Catch::Generators;

TEST(SingleValueGeneratorTest_314, GetReturnsConstructedValue_Int_314) {
    CG::SingleValueGenerator<int> gen(42);
    EXPECT_EQ(gen.get(), 42) << "get() should return the value provided at construction";
}

TEST(SingleValueGeneratorTest_314, GetReturnsConstructedValue_StringCopy_314) {
    std::string src = "hello";
    CG::SingleValueGenerator<std::string> gen(src); // copy-construct
    EXPECT_EQ(gen.get(), "hello");
    // Ensure original remains unchanged (observable wrt copying at the call site)
    EXPECT_EQ(src, "hello");
}

TEST(SingleValueGeneratorTest_314, MoveConstructorStoresValue_314) {
    std::string s = "moved";
    CG::SingleValueGenerator<std::string> gen(std::move(s)); // move-construct
    EXPECT_EQ(gen.get(), "moved");
    // We intentionally do not assert anything about 's' after move (moved-from is unspecified)
}

TEST(SingleValueGeneratorTest_314, SupportsMoveOnlyTypes_314) {
    auto up = std::make_unique<int>(123);
    CG::SingleValueGenerator<std::unique_ptr<int>> gen(std::move(up));
    // get() returns const&, so we can read through it
    ASSERT_NE(gen.get(), nullptr);
    EXPECT_EQ(*gen.get(), 123);
    // Ensure ownership moved (observable at call site)
    EXPECT_EQ(up, nullptr);
}

TEST(SingleValueGeneratorTest_314, NextAlwaysReturnsFalse_314) {
    CG::SingleValueGenerator<int> gen(7);
    // For a "single value" generator, advancing should not be possible.
    // We don't infer internal logic; we simply assert the public contract via return value.
    EXPECT_FALSE(gen.next());
    EXPECT_FALSE(gen.next()) << "Subsequent calls should continue to report no further values";
}

TEST(SingleValueGeneratorTest_314, GetReferenceIsStable_314) {
    CG::SingleValueGenerator<std::string> gen(std::string("stable"));
    auto const* addr1 = &gen.get();
    auto const* addr2 = &gen.get();
    EXPECT_EQ(addr1, addr2) << "get() should consistently return a reference to the stored value";
}

TEST(SingleValueGeneratorTest_314, GetReturnTypeIsConstRef_314) {
    CG::SingleValueGenerator<int> gen(5);
    // Compile-time check: get() returns T const&
    static_assert(std::is_same<decltype(gen.get()), int const&>::value,
                  "get() must return const reference to T");
    // Also assert constness at runtime by attempting read (write through const ref would not compile)
    EXPECT_EQ(gen.get(), 5);
}
