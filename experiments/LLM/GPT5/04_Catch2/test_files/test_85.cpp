// File: convert_nullptr_test_85.cpp
#include <gtest/gtest.h>
#include <string>
#include <type_traits>

// SUT header (as provided)
namespace Catch {
    static std::string convert(std::nullptr_t) {
        using namespace std::string_literals;
        return "nullptr"s;
    }
}

// ---------------------- Tests ----------------------

TEST(ConvertNullptrTest_85, ReturnsExactString_85) {
    // Normal operation: converting nullptr yields the literal "nullptr"
    EXPECT_EQ("nullptr", Catch::convert(nullptr));
}

TEST(ConvertNullptrTest_85, CVQualifiedNullptrArg_85) {
    // Boundary: cv-qualified std::nullptr_t should be accepted via decay/copy and produce same result
    const std::nullptr_t cnull = nullptr;
    volatile std::nullptr_t vnull = nullptr;
    const volatile std::nullptr_t cvnull = nullptr;

    EXPECT_EQ("nullptr", Catch::convert(cnull));
    EXPECT_EQ("nullptr", Catch::convert(vnull));
    EXPECT_EQ("nullptr", Catch::convert(cvnull));
}

TEST(ConvertNullptrTest_85, NotEmptyAndNotZeroString_85) {
    // Sanity checks on observable output
    auto out = Catch::convert(nullptr);
    EXPECT_FALSE(out.empty());
    EXPECT_NE("0", out);          // ensure it is not confused with numeric zero
    EXPECT_NE("(null)", out);     // nor common C-style null prints
}

TEST(ConvertNullptrTest_85, NoThrowOnConversion_85) {
    // Exceptional case coverage: function should not throw for nullptr input
    EXPECT_NO_THROW({
        auto out = Catch::convert(nullptr);
        (void)out;
    });
}

TEST(ConvertNullptrTest_85, ReturnTypeIsStdString_85) {
    // Interface contract: return type is std::string (compile-time observable)
    static_assert(std::is_same<decltype(Catch::convert(nullptr)), std::string>::value,
                  "Catch::convert(nullptr_t) must return std::string");
    SUCCEED(); // Keep the test visible in gtest output
}
