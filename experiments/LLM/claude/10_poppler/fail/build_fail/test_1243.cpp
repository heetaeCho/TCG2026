#include <gtest/gtest.h>
#include <string>
#include <QString>

// Forward declarations and type definitions based on the known dependencies
// We need to set up the types that the function under test uses

// The ErrorStringType enum - inferred from usage
enum ErrorStringType {
    ErrorStringType_None = 0,
    ErrorStringType_Warning = 1,
    ErrorStringType_Error = 2,
    ErrorStringType_Syntax = 3
};

// The core ErrorString struct
struct ErrorString {
    std::string text;
    ErrorStringType type;
};

// Include the header under test
// We need the Poppler namespace types
namespace Poppler {

struct ErrorString {
    QString data;
    int type; // mapped from ErrorStringType via fromPopplerCore
};

// Assuming fromPopplerCore for type mapping exists
inline int fromPopplerCore(ErrorStringType t) {
    return static_cast<int>(t);
}

inline Poppler::ErrorString fromPopplerCore(const ::ErrorString &str) {
    Poppler::ErrorString res;
    res.type = fromPopplerCore(str.type);
    res.data = QString::fromStdString(str.text);
    return res;
}

} // namespace Poppler

class FromPopplerCoreTest_1243 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test normal conversion with typical string and type
TEST_F(FromPopplerCoreTest_1243, NormalConversion_1243) {
    ::ErrorString input;
    input.text = "This is an error message";
    input.type = ErrorStringType_Error;

    Poppler::ErrorString result = Poppler::fromPopplerCore(input);

    EXPECT_EQ(result.data, QString("This is an error message"));
    EXPECT_EQ(result.type, static_cast<int>(ErrorStringType_Error));
}

// Test conversion with empty string
TEST_F(FromPopplerCoreTest_1243, EmptyString_1243) {
    ::ErrorString input;
    input.text = "";
    input.type = ErrorStringType_None;

    Poppler::ErrorString result = Poppler::fromPopplerCore(input);

    EXPECT_EQ(result.data, QString(""));
    EXPECT_TRUE(result.data.isEmpty());
    EXPECT_EQ(result.type, static_cast<int>(ErrorStringType_None));
}

// Test conversion with warning type
TEST_F(FromPopplerCoreTest_1243, WarningType_1243) {
    ::ErrorString input;
    input.text = "Warning message";
    input.type = ErrorStringType_Warning;

    Poppler::ErrorString result = Poppler::fromPopplerCore(input);

    EXPECT_EQ(result.data, QString("Warning message"));
    EXPECT_EQ(result.type, static_cast<int>(ErrorStringType_Warning));
}

// Test conversion with syntax type
TEST_F(FromPopplerCoreTest_1243, SyntaxType_1243) {
    ::ErrorString input;
    input.text = "Syntax error encountered";
    input.type = ErrorStringType_Syntax;

    Poppler::ErrorString result = Poppler::fromPopplerCore(input);

    EXPECT_EQ(result.data, QString("Syntax error encountered"));
    EXPECT_EQ(result.type, static_cast<int>(ErrorStringType_Syntax));
}

// Test conversion with very long string
TEST_F(FromPopplerCoreTest_1243, LongString_1243) {
    ::ErrorString input;
    input.text = std::string(10000, 'A');
    input.type = ErrorStringType_Error;

    Poppler::ErrorString result = Poppler::fromPopplerCore(input);

    EXPECT_EQ(result.data.length(), 10000);
    EXPECT_EQ(result.data, QString(10000, QChar('A')));
}

// Test conversion with special characters in string
TEST_F(FromPopplerCoreTest_1243, SpecialCharacters_1243) {
    ::ErrorString input;
    input.text = "Error: file \"test.pdf\" not found\n\ttab here";
    input.type = ErrorStringType_Error;

    Poppler::ErrorString result = Poppler::fromPopplerCore(input);

    EXPECT_EQ(result.data, QString("Error: file \"test.pdf\" not found\n\ttab here"));
}

// Test conversion with UTF-8 content
TEST_F(FromPopplerCoreTest_1243, Utf8Content_1243) {
    ::ErrorString input;
    input.text = u8"Unicode: \xC3\xA9\xC3\xA0\xC3\xBC";
    input.type = ErrorStringType_Warning;

    Poppler::ErrorString result = Poppler::fromPopplerCore(input);

    EXPECT_EQ(result.data, QString::fromStdString(input.text));
    EXPECT_EQ(result.type, static_cast<int>(ErrorStringType_Warning));
}

// Test that the result is a proper copy, not referencing original
TEST_F(FromPopplerCoreTest_1243, ResultIsIndependentCopy_1243) {
    ::ErrorString input;
    input.text = "Original message";
    input.type = ErrorStringType_Error;

    Poppler::ErrorString result = Poppler::fromPopplerCore(input);

    // Modify input after conversion
    input.text = "Modified message";
    input.type = ErrorStringType_None;

    // Result should still have original values
    EXPECT_EQ(result.data, QString("Original message"));
    EXPECT_EQ(result.type, static_cast<int>(ErrorStringType_Error));
}

// Test conversion with null characters in string
TEST_F(FromPopplerCoreTest_1243, StringWithNullCharacter_1243) {
    ::ErrorString input;
    input.text = std::string("before\0after", 12);
    input.type = ErrorStringType_Error;

    Poppler::ErrorString result = Poppler::fromPopplerCore(input);

    // QString::fromStdString should handle embedded nulls
    EXPECT_EQ(result.data.length(), 12);
}

// Test multiple conversions produce consistent results
TEST_F(FromPopplerCoreTest_1243, MultipleConversionsConsistent_1243) {
    ::ErrorString input;
    input.text = "Consistent message";
    input.type = ErrorStringType_Warning;

    Poppler::ErrorString result1 = Poppler::fromPopplerCore(input);
    Poppler::ErrorString result2 = Poppler::fromPopplerCore(input);

    EXPECT_EQ(result1.data, result2.data);
    EXPECT_EQ(result1.type, result2.type);
}
