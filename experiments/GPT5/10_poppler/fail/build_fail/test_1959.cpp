#include <gtest/gtest.h>
#include <string_view>
#include <string>

namespace CryptoSign {
    static std::string_view toStringView(const char *str) {
        if (str) {
            return std::string_view(str);
        }
        return {};
    }
}

TEST_F(CryptoSignTest_1959, toStringView_ReturnsNonEmptyStringView_WhenStringIsNotNull_1959) {
    const char* input = "Hello, World!";
    std::string_view result = CryptoSign::toStringView(input);
    EXPECT_EQ(result, "Hello, World!");
}

TEST_F(CryptoSignTest_1959, toStringView_ReturnsEmptyStringView_WhenStringIsNull_1959) {
    const char* input = nullptr;
    std::string_view result = CryptoSign::toStringView(input);
    EXPECT_TRUE(result.empty());
}

TEST_F(CryptoSignTest_1959, toStringView_ReturnsNonEmptyStringView_ForNonNullInput_1959) {
    const char* input = "Test String";
    std::string_view result = CryptoSign::toStringView(input);
    EXPECT_FALSE(result.empty());
    EXPECT_EQ(result, "Test String");
}

TEST_F(CryptoSignTest_1959, toStringView_ReturnsEmptyStringView_WhenInputIsNullptr_1959) {
    const char* input = nullptr;
    std::string_view result = CryptoSign::toStringView(input);
    EXPECT_TRUE(result.empty());
}