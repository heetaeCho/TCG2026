// File: tests/ExceptionTranslatorRegistrar_1052.tests.cpp

#include <gtest/gtest.h>
#include <memory>
#include <string>
#include <typeindex>
#include <typeinfo>
#include <utility>

// ---- Test doubles for external dependencies in Catch::Detail ----
// These are collaborators (not the class under test) and are safe to fake.
namespace Catch { namespace Detail {

// Minimal base to accept unique_ptr polymorphically
struct ITranslatorBase { virtual ~ITranslatorBase() = default; };

// Template that records constructor usage for verification
template <typename T>
struct ExceptionTranslator : ITranslatorBase {
    using Fn = std::string(*)(T const&);
    Fn fn;
    explicit ExceptionTranslator(Fn f) : fn(f) {
        constructed_count++;
        last_ctor_called_with = reinterpret_cast<void*>(f);
    }
    static inline int constructed_count = 0;
    static inline void* last_ctor_called_with = nullptr;
};

// Provide the make_unique used by the header-under-test
template <typename T, typename... Args>
std::unique_ptr<T> make_unique(Args&&... args) {
    return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
}

// Spy for registerTranslatorImpl to verify calls
inline int register_call_count = 0;
inline std::type_index last_registered_type = std::type_index(typeid(void));

inline void registerTranslatorImpl(std::unique_ptr<ITranslatorBase> p) {
    register_call_count++;
    last_registered_type = std::type_index(typeid(*p));
    // Ownership is intentionally discarded here; we only observe the call.
}

}} // namespace Catch::Detail

// ---- Include the header under test AFTER fakes are visible ----
#include "Catch2/src/catch2/catch_translate_exception.hpp"

// ---- Test helpers (translate functions) ----
static std::string TranslateInt(const int& v) { return std::string("int:") + std::to_string(v); }
static std::string TranslateString(const std::string& s) { return std::string("str:") + s; }

class ExceptionTranslatorRegistrarTest_1052 : public ::testing::Test {
protected:
    void SetUp() override {
        using namespace Catch::Detail;
        register_call_count = 0;
        last_registered_type = std::type_index(typeid(void));
        // Reset per-T template statics we might use
        ExceptionTranslator<int>::constructed_count = 0;
        ExceptionTranslator<int>::last_ctor_called_with = nullptr;
        ExceptionTranslator<std::string>::constructed_count = 0;
        ExceptionTranslator<std::string>::last_ctor_called_with = nullptr;
    }
};

// [Normal operation] Registers exactly once with a valid translator for int
TEST_F(ExceptionTranslatorRegistrarTest_1052, RegistersTranslatorOnce_1052) {
    using namespace Catch;
    using Catch::Detail::ExceptionTranslator;

    ExceptionTranslatorRegistrar reg_int(&TranslateInt);

    EXPECT_EQ(Catch::Detail::register_call_count, 1);
    EXPECT_EQ(ExceptionTranslator<int>::constructed_count, 1);
    // Verify the function pointer was forwarded into the constructed translator
    EXPECT_EQ(ExceptionTranslator<int>::last_ctor_called_with,
              reinterpret_cast<void*>(&TranslateInt));
    // Type recorded by the spy should match the concrete translator type
    EXPECT_EQ(Catch::Detail::last_registered_type, std::type_index(typeid(ExceptionTranslator<int>)));
}

// [Type coverage] Independent registrations for different T
TEST_F(ExceptionTranslatorRegistrarTest_1052, RegistersDifferentTypesIndependently_1052) {
    using namespace Catch;
    using Catch::Detail::ExceptionTranslator;

    ExceptionTranslatorRegistrar reg_int(&TranslateInt);
    ExceptionTranslatorRegistrar reg_str(&TranslateString);

    EXPECT_EQ(Catch::Detail::register_call_count, 2);
    EXPECT_EQ(ExceptionTranslator<int>::constructed_count, 1);
    EXPECT_EQ(ExceptionTranslator<std::string>::constructed_count, 1);

    EXPECT_EQ(ExceptionTranslator<int>::last_ctor_called_with,
              reinterpret_cast<void*>(&TranslateInt));
    EXPECT_EQ(ExceptionTranslator<std::string>::last_ctor_called_with,
              reinterpret_cast<void*>(&TranslateString));
}

// [Boundary] Passing a nullptr function pointer is forwarded as-is to the collaborator
TEST_F(ExceptionTranslatorRegistrarTest_1052, ForwardsNullFunctionPointer_1052) {
    using namespace Catch;
    using Catch::Detail::ExceptionTranslator;

    // Note: The interface accepts a raw function pointer; nullptr is a valid value at the type level.
    // We only verify forwarding (no assumptions about internal handling).
    std::string (*nullFn)(int const&) = nullptr;

    ExceptionTranslatorRegistrar reg_null(nullFn);

    EXPECT_EQ(Catch::Detail::register_call_count, 1);
    EXPECT_EQ(ExceptionTranslator<int>::constructed_count, 1);
    EXPECT_EQ(ExceptionTranslator<int>::last_ctor_called_with,
              reinterpret_cast<void*>(nullptr));
}

// [Interaction count] Multiple constructions increment registration calls
TEST_F(ExceptionTranslatorRegistrarTest_1052, MultipleRegistrationsIncrementCount_1052) {
    using namespace Catch;

    ExceptionTranslatorRegistrar r1(&TranslateInt);
    ExceptionTranslatorRegistrar r2(&TranslateInt);
    ExceptionTranslatorRegistrar r3(&TranslateInt);

    EXPECT_EQ(Catch::Detail::register_call_count, 3);
}

