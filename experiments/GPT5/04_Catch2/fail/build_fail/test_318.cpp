// value_generator_tests_318.cpp
#include <gtest/gtest.h>
#include <type_traits>
#include <memory>
#include <string>

// Include path follows Catch2's public header layout.
// Adjust include path if your repo uses a different layout.
#include <catch2/generators/catch_generators.hpp>

using Catch::Generators::GeneratorWrapper;

class ValueGeneratorTest_318 : public ::testing::Test {};

// --- Type decay & signature checks ---

// Ensures return type is GeneratorWrapper<int> for various int forms.
TEST_F(ValueGeneratorTest_318, ReturnTypeDecaysToInt_318) {
    int i = 7;
    const int ci = 11;
    volatile int vi = 13;
    const volatile int cvi = 17;

    auto wi  = Catch::Generators::value(i);
    auto wci = Catch::Generators::value(ci);
    auto wvi = Catch::Generators::value(vi);
    auto wcvi = Catch::Generators::value(cvi);
    auto wl = Catch::Generators::value(42); // literal (rvalue)

    static_assert(std::is_same<decltype(wi),  GeneratorWrapper<int>>::value,  "lvalue int should decay to int");
    static_assert(std::is_same<decltype(wci), GeneratorWrapper<int>>::value,  "const int should decay to int");
    static_assert(std::is_same<decltype(wvi), GeneratorWrapper<int>>::value,  "volatile int should decay to int");
    static_assert(std::is_same<decltype(wcvi),GeneratorWrapper<int>>::value,  "cv int should decay to int");
    static_assert(std::is_same<decltype(wl),  GeneratorWrapper<int>>::value,  "rvalue int should decay to int");
}

// Arrays should decay to pointers.
TEST_F(ValueGeneratorTest_318, ReturnTypeDecaysArrayToPointer_318) {
    const char arr[] = "ok";
    auto w = Catch::Generators::value(arr);
    static_assert(std::is_same<decltype(w), GeneratorWrapper<const char*>>::value,
                  "array should decay to const char*");
}

// --- Normal operation ---

TEST_F(ValueGeneratorTest_318, YieldsProvidedIntAndNoNext_318) {
    auto w = Catch::Generators::value(123);
    auto& gen = w.get();                  // public interface
    EXPECT_EQ(gen.get(), 123);            // yields the provided value
    EXPECT_FALSE(gen.next());             // no next value for a single-value generator
}

TEST_F(ValueGeneratorTest_318, YieldsProvidedStringAndNoNext_318) {
    auto w = Catch::Generators::value(std::string("hello"));
    auto& gen = w.get();
    EXPECT_EQ(gen.get(), "hello");
    EXPECT_FALSE(gen.next());
}

// --- Boundary conditions ---

TEST_F(ValueGeneratorTest_318, HandlesEmptyString_318) {
    auto w = Catch::Generators::value(std::string{});
    auto& gen = w.get();
    EXPECT_EQ(gen.get(), "");   // empty string is yielded as-is
    EXPECT_FALSE(gen.next());
}

TEST_F(ValueGeneratorTest_318, HandlesNullPointer_318) {
    const char* p = nullptr;
    auto w = Catch::Generators::value(p);
    auto& gen = w.get();
    EXPECT_EQ(gen.get(), nullptr);   // nullptr propagated
    EXPECT_FALSE(gen.next());
}

TEST_F(ValueGeneratorTest_318, ArrayDecayPointerEquality_318) {
    const char arr[] = "ok";
    auto w = Catch::Generators::value(arr);
    auto& gen = w.get();
    // Expect pointer to first element (array-to-pointer decay)
    EXPECT_EQ(gen.get(), arr);
    EXPECT_FALSE(gen.next());
}

// --- Observable copy vs reference behavior ---

TEST_F(ValueGeneratorTest_318, StoresCopyOfLvalueNotReference_318) {
    std::string s = "alpha";
    auto w = Catch::Generators::value(s);  // pass lvalue
    s = "mutated";                         // mutate source after wrapping
    auto& gen = w.get();
    EXPECT_EQ(gen.get(), "alpha") << "Generator should hold decayed (copied) value, not a live reference";
    EXPECT_FALSE(gen.next());
}

// --- Move-only types ---

TEST_F(ValueGeneratorTest_318, SupportsMoveOnlyTypeUniquePtr_318) {
    auto w = Catch::Generators::value(std::make_unique<int>(777));
    auto& gen = w.get();
    ASSERT_NE(gen.get(), nullptr);
    EXPECT_EQ(*gen.get(), 777);
    EXPECT_FALSE(gen.next());
}
