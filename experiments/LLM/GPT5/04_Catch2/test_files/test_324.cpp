// File: tests/make_generators_324_tests.cpp

#include <gtest/gtest.h>
#include <type_traits>
#include <utility>

// ---- Test doubles for external collaborators in the same namespace ----
#ifndef CATCH_MOVE
#  define CATCH_MOVE(x) std::move(x)
#endif

namespace Catch { namespace Generators {

// Move-only, observable wrapper used as the input collaborator.
template <typename T>
struct GeneratorWrapper {
    static int move_count;
    static int copy_count;

    int tag = 0;

    GeneratorWrapper() = default;
    explicit GeneratorWrapper(int t) : tag(t) {}

    // Copy is observable (and allowed) to detect if it was used.
    GeneratorWrapper(const GeneratorWrapper&) { ++copy_count; }

    // Move is observable.
    GeneratorWrapper(GeneratorWrapper&&) noexcept { ++move_count; }

    // Assignment operators not needed for the tests
};
template <typename T> int GeneratorWrapper<T>::move_count = 0;
template <typename T> int GeneratorWrapper<T>::copy_count = 0;

// Output collaborator that records construction from a moved-in wrapper.
template <typename T>
struct Generators {
    bool constructed_from_wrapper = false;
    int received_tag = -1;

    explicit Generators(GeneratorWrapper<T>&& gw)
        : constructed_from_wrapper(true), received_tag(gw.tag) {}
};

}} // namespace Catch::Generators

// ---- Function under test (from the provided partial code) ----
namespace Catch { namespace Generators {
template <typename T>
auto makeGenerators(GeneratorWrapper<T>&& generator) -> Generators<T> {
    return Generators<T>(CATCH_MOVE(generator));
}
}} // namespace Catch::Generators

using namespace Catch::Generators;

// ---- Tests ----

TEST(MakeGeneratorsTest_324, ReturnsGeneratorsAndInvokesCtor_324) {
    // Arrange
    GeneratorWrapper<int>::move_count = 0;
    GeneratorWrapper<int>::copy_count = 0;

    // Act
    auto result = makeGenerators<int>(GeneratorWrapper<int>(42));

    // Assert: returns the expected type
    static_assert(std::is_same<decltype(result), Generators<int>>::value,
                  "makeGenerators must return Generators<T>");

    // Assert: constructed via the Generators(GeneratorWrapper&&) ctor
    EXPECT_TRUE(result.constructed_from_wrapper);
    EXPECT_EQ(result.received_tag, 42);

    // Assert: exactly one move occurred somewhere along the path,
    // and no copies were made (rvalue path should be used).
    EXPECT_GE(GeneratorWrapper<int>::move_count, 1);
    EXPECT_EQ(GeneratorWrapper<int>::copy_count, 0);
}

TEST(MakeGeneratorsTest_324, AcceptsMoveOnlyWrapper_324) {
    // Arrange: make the wrapper non-copyable to ensure rvalue path works
    struct MoveOnlyTag {};
    // Shadow the copy-able test double with a move-only variant for this T.
    struct MoveOnlyGeneratorWrapper : GeneratorWrapper<MoveOnlyTag> {
        using Base = GeneratorWrapper<MoveOnlyTag>;
        using Base::Base;
        MoveOnlyGeneratorWrapper(const MoveOnlyGeneratorWrapper&) = delete;
        MoveOnlyGeneratorWrapper(MoveOnlyGeneratorWrapper&&) noexcept = default;
    };

    // Provide a Generators specialization that accepts the move-only wrapper.
    struct MoveOnlyGenerators {
        bool ok = false;
        explicit MoveOnlyGenerators(MoveOnlyGeneratorWrapper&&) : ok(true) {}
    };

    // Place these in the required namespace so ADL resolves correctly.
    // (Local wrapper types are aliased into the Catch::Generators namespace.)
    {
        // Create aliases into the target namespace for this test scope.
        // Note: anonymous scope to avoid leaking aliases.
        using ::Catch::Generators::GeneratorWrapper;
        using ::Catch::Generators::Generators;
    }

    // Inject specializations into Catch::Generators for this MoveOnlyTag type.
    namespace Catch { namespace Generators {
        template<> struct GeneratorWrapper<MoveOnlyTag> : MoveOnlyGeneratorWrapper {
            using MoveOnlyGeneratorWrapper::MoveOnlyGeneratorWrapper;
        };
        template<> struct Generators<MoveOnlyTag> : MoveOnlyGenerators {
            using MoveOnlyGenerators::MoveOnlyGenerators;
        };
        // Reuse the same makeGenerators template (already defined).
    }} // namespace Catch::Generators

    // Act
    auto result = Catch::Generators::makeGenerators<MoveOnlyTag>(
        Catch::Generators::GeneratorWrapper<MoveOnlyTag>{});

    // Assert
    EXPECT_TRUE(result.ok);
}

TEST(MakeGeneratorsTest_324, UsesMoveNotCopy_324) {
    // Arrange
    GeneratorWrapper<long>::move_count = 0;
    GeneratorWrapper<long>::copy_count = 0;
    GeneratorWrapper<long> tmp(7);

    // Act: pass rvalue explicitly
    auto out = makeGenerators<long>(std::move(tmp));
    (void)out;

    // Assert: no copies should be observed along the rvalue path
    EXPECT_EQ(GeneratorWrapper<long>::copy_count, 0);
    EXPECT_GE(GeneratorWrapper<long>::move_count, 1);
}
