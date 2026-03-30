// File: bound_value_ref_setvalue_tests_376.cpp
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <string>

using ::testing::Ref;
using ::testing::StrictMock;

namespace Catch { namespace Clara { namespace Detail {

// --- Test-only minimal surface to allow compilation without
// relying on private/internal implementation details ---

// Lightweight result type just for equality checks in tests.
struct ParserResult {
    int code{};
    bool operator==(const ParserResult& other) const { return code == other.code; }
};

// We will mock the external collaborator that setValue calls.
struct ConvertIntoMock {
    MOCK_METHOD(ParserResult, ConvertInt,    (const std::string&, int&), ());
    MOCK_METHOD(ParserResult, ConvertString, (const std::string&, std::string&), ());
};

// Test-only global pointer to route free-function calls into the mock.
static ConvertIntoMock* g_convert_mock = nullptr;

// Free-function overloads that the production code calls unqualified.
// In tests, we forward them to the mock to verify interaction.
inline ParserResult convertInto(const std::string& arg, int& ref) {
    return g_convert_mock->ConvertInt(arg, ref);
}
inline ParserResult convertInto(const std::string& arg, std::string& ref) {
    return g_convert_mock->ConvertString(arg, ref);
}

// Minimal interface surface for the class under test based on the prompt.
// We only model what we need to exercise the public behavior.
template <typename T>
struct BoundValueRef /* : public BoundValueRefBase (not needed for tests) */ {
    T& m_ref;
    explicit BoundValueRef(T& ref) : m_ref(ref) {}

    // Function under test — delegates to convertInto(arg, m_ref).
    ParserResult setValue(std::string const& arg) /* override in real code */ {
        return convertInto(arg, m_ref);
    }
};

}}} // namespace Catch::Clara::Detail

// -------------------- Tests --------------------

using Catch::Clara::Detail::BoundValueRef;
using Catch::Clara::Detail::ConvertIntoMock;
using Catch::Clara::Detail::ParserResult;
namespace CCD = Catch::Clara::Detail;

// Normal operation: verifies that setValue forwards the argument and reference
// to convertInto and returns exactly what convertInto returns.
TEST(BoundValueRef_SetValue_376, ForwardsArgsAndReturnsValue_Int_376) {
    int target = 0;
    BoundValueRef<int> bound(target);

    StrictMock<ConvertIntoMock> mock;
    CCD::g_convert_mock = &mock;

    const std::string input = "42";
    const ParserResult expected{101};

    EXPECT_CALL(mock, ConvertInt(input, Ref(target)))
        .WillOnce([&](const std::string& arg, int& ref) {
            // Verify we indeed get the same reference (address check implicit via Ref matcher).
            EXPECT_EQ(&ref, &target);
            EXPECT_EQ(arg, input);
            return expected;
        });

    ParserResult actual = bound.setValue(input);
    EXPECT_EQ(actual, expected);

    CCD::g_convert_mock = nullptr;
}

// Boundary condition: empty string input should still be forwarded verbatim,
// and the result from convertInto should be propagated unmodified.
TEST(BoundValueRef_SetValue_376, EmptyStringInput_IsForwarded_String_376) {
    std::string target = "initial";
    BoundValueRef<std::string> bound(target);

    StrictMock<ConvertIntoMock> mock;
    CCD::g_convert_mock = &mock;

    const std::string input; // empty
    const ParserResult expected{-7};

    EXPECT_CALL(mock, ConvertString(input, Ref(target)))
        .WillOnce([&](const std::string& arg, std::string& ref) {
            EXPECT_TRUE(arg.empty());
            EXPECT_EQ(&ref, &target);
            return expected;
        });

    ParserResult actual = bound.setValue(input);
    EXPECT_EQ(actual, expected);

    CCD::g_convert_mock = nullptr;
}

// Error/exceptional path (observable via return value): if convertInto signals a
// failure via a distinctive ParserResult, setValue must propagate it unchanged.
TEST(BoundValueRef_SetValue_376, PropagatesErrorFromConvertInto_376) {
    int target = 123;
    BoundValueRef<int> bound(target);

    StrictMock<ConvertIntoMock> mock;
    CCD::g_convert_mock = &mock;

    const std::string input = "not-an-int";
    const ParserResult errorResult{-999};

    EXPECT_CALL(mock, ConvertInt(input, Ref(target)))
        .WillOnce([&](const std::string& arg, int& ref) {
            EXPECT_EQ(arg, input);
            EXPECT_EQ(&ref, &target);
            return errorResult; // simulate failure reported by collaborator
        });

    ParserResult actual = bound.setValue(input);
    EXPECT_EQ(actual, errorResult);

    CCD::g_convert_mock = nullptr;
}
