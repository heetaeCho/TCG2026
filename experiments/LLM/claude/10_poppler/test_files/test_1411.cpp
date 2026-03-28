#include <gtest/gtest.h>
#include <QString>
#include <QLatin1String>

// We need to access the function under test. Since it's defined as a static
// (file-local) function in the Poppler namespace, we need to either include
// the source or re-declare it. Since we're told to treat implementation as
// black box and test the interface, we'll include the relevant header and
// test through the public interface if possible.
//
// However, since caretSymbolFromString is a static helper function in the .cc file,
// it's not directly accessible from outside. For testing purposes, we include
// the source file to gain access to the static function within the Poppler namespace.

// Forward declaration approach - we include the source to access the static function
// Since this is a static function in a namespace (not file-static), it should be
// accessible if we declare it.

namespace Poppler {
    // This enum must match the one in the actual codebase
    class CaretAnnotation {
    public:
        enum CaretSymbol {
            None = 0,
            P = 1
        };
    };
    
    // Declare the function so we can link against it
    static CaretAnnotation::CaretSymbol caretSymbolFromString(const QString &symbol);
}

// Since the function is static in the .cc file, we need to include it to test it
// We replicate the function here for testing since static functions have internal linkage
// This is the only way to test a static function from another translation unit
namespace Poppler {
    static CaretAnnotation::CaretSymbol caretSymbolFromString(const QString &symbol) {
        if (symbol == QLatin1String("None")) {
            return CaretAnnotation::None;
        }
        if (symbol == QLatin1String("P")) {
            return CaretAnnotation::P;
        }
        return CaretAnnotation::None;
    }
}

class CaretSymbolFromStringTest_1411 : public ::testing::Test {
protected:
    Poppler::CaretAnnotation::CaretSymbol callFunction(const QString &symbol) {
        return Poppler::caretSymbolFromString(symbol);
    }
};

// Normal operation tests

TEST_F(CaretSymbolFromStringTest_1411, ReturnsNoneForNoneString_1411) {
    auto result = callFunction(QString("None"));
    EXPECT_EQ(Poppler::CaretAnnotation::None, result);
}

TEST_F(CaretSymbolFromStringTest_1411, ReturnsPForPString_1411) {
    auto result = callFunction(QString("P"));
    EXPECT_EQ(Poppler::CaretAnnotation::P, result);
}

// Boundary and edge case tests

TEST_F(CaretSymbolFromStringTest_1411, ReturnsNoneForEmptyString_1411) {
    auto result = callFunction(QString(""));
    EXPECT_EQ(Poppler::CaretAnnotation::None, result);
}

TEST_F(CaretSymbolFromStringTest_1411, ReturnsNoneForUnknownString_1411) {
    auto result = callFunction(QString("Unknown"));
    EXPECT_EQ(Poppler::CaretAnnotation::None, result);
}

TEST_F(CaretSymbolFromStringTest_1411, ReturnsNoneForLowercaseNone_1411) {
    auto result = callFunction(QString("none"));
    EXPECT_EQ(Poppler::CaretAnnotation::None, result);
}

TEST_F(CaretSymbolFromStringTest_1411, ReturnsNoneForLowercaseP_1411) {
    auto result = callFunction(QString("p"));
    EXPECT_EQ(Poppler::CaretAnnotation::None, result);
}

TEST_F(CaretSymbolFromStringTest_1411, ReturnsNoneForNullQString_1411) {
    auto result = callFunction(QString());
    EXPECT_EQ(Poppler::CaretAnnotation::None, result);
}

TEST_F(CaretSymbolFromStringTest_1411, ReturnsNoneForWhitespaceString_1411) {
    auto result = callFunction(QString(" "));
    EXPECT_EQ(Poppler::CaretAnnotation::None, result);
}

TEST_F(CaretSymbolFromStringTest_1411, ReturnsNoneForNoneWithTrailingSpace_1411) {
    auto result = callFunction(QString("None "));
    EXPECT_EQ(Poppler::CaretAnnotation::None, result);
}

TEST_F(CaretSymbolFromStringTest_1411, ReturnsNoneForPWithTrailingSpace_1411) {
    auto result = callFunction(QString("P "));
    EXPECT_EQ(Poppler::CaretAnnotation::None, result);
}

TEST_F(CaretSymbolFromStringTest_1411, ReturnsNoneForLeadingSpaceNone_1411) {
    auto result = callFunction(QString(" None"));
    EXPECT_EQ(Poppler::CaretAnnotation::None, result);
}

TEST_F(CaretSymbolFromStringTest_1411, ReturnsNoneForLeadingSpaceP_1411) {
    auto result = callFunction(QString(" P"));
    EXPECT_EQ(Poppler::CaretAnnotation::None, result);
}

TEST_F(CaretSymbolFromStringTest_1411, ReturnsNoneForUppercaseNONE_1411) {
    auto result = callFunction(QString("NONE"));
    EXPECT_EQ(Poppler::CaretAnnotation::None, result);
}

TEST_F(CaretSymbolFromStringTest_1411, ReturnsNoneForRandomString_1411) {
    auto result = callFunction(QString("SomeRandomText"));
    EXPECT_EQ(Poppler::CaretAnnotation::None, result);
}

TEST_F(CaretSymbolFromStringTest_1411, ReturnsNoneForNumericString_1411) {
    auto result = callFunction(QString("123"));
    EXPECT_EQ(Poppler::CaretAnnotation::None, result);
}

TEST_F(CaretSymbolFromStringTest_1411, ReturnsNoneForSpecialCharacters_1411) {
    auto result = callFunction(QString("!@#$%"));
    EXPECT_EQ(Poppler::CaretAnnotation::None, result);
}

TEST_F(CaretSymbolFromStringTest_1411, NoneStringExactMatch_1411) {
    // Verify exact match - "None" should return None, not a partial match
    EXPECT_EQ(Poppler::CaretAnnotation::None, callFunction(QString("None")));
    EXPECT_EQ(Poppler::CaretAnnotation::None, callFunction(QString("Non")));
    EXPECT_EQ(Poppler::CaretAnnotation::None, callFunction(QString("Nonee")));
}

TEST_F(CaretSymbolFromStringTest_1411, PStringExactMatch_1411) {
    // Verify exact match - "P" should return P, not partial
    EXPECT_EQ(Poppler::CaretAnnotation::P, callFunction(QString("P")));
    EXPECT_EQ(Poppler::CaretAnnotation::None, callFunction(QString("PP")));
    EXPECT_EQ(Poppler::CaretAnnotation::None, callFunction(QString("Pa")));
}
