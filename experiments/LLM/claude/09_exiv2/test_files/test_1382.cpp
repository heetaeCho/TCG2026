#include <gtest/gtest.h>
#include <sstream>
#include <exiv2/exiv2.hpp>

using namespace Exiv2;

class PrintLensSpecificationTest_1382 : public ::testing::Test {
protected:
    std::ostringstream os;

    // Helper to create URationalValue with 4 rational entries
    URationalValue makeValue(Rational r0, Rational r1, Rational r2, Rational r3) {
        URationalValue val;
        val.value_.push_back(URational(r0.first, r0.second));
        val.value_.push_back(URational(r1.first, r1.second));
        val.value_.push_back(URational(r2.first, r2.second));
        val.value_.push_back(URational(r3.first, r3.second));
        return val;
    }
};

// Test: All zeros should return "n/a"
TEST_F(PrintLensSpecificationTest_1382, AllZeros_ReturnsNA_1382) {
    auto val = makeValue({0, 1}, {0, 1}, {0, 1}, {0, 1});
    Internal::printLensSpecification(os, val, nullptr);
    EXPECT_EQ(os.str(), "n/a");
}

// Test: Wrong type (not unsignedRational) should return parenthesized value
TEST_F(PrintLensSpecificationTest_1382, WrongType_ReturnsParenthesized_1382) {
    UShortValue val;
    val.value_.push_back(1);
    val.value_.push_back(2);
    val.value_.push_back(3);
    val.value_.push_back(4);
    Internal::printLensSpecification(os, val, nullptr);
    std::string result = os.str();
    EXPECT_EQ(result.front(), '(');
    EXPECT_EQ(result.back(), ')');
}

// Test: Wrong count (not 4) should return parenthesized value
TEST_F(PrintLensSpecificationTest_1382, WrongCount_ReturnsParenthesized_1382) {
    URationalValue val;
    val.value_.push_back(URational(18, 1));
    val.value_.push_back(URational(55, 1));
    val.value_.push_back(URational(35, 10));
    // Only 3 values
    Internal::printLensSpecification(os, val, nullptr);
    std::string result = os.str();
    EXPECT_EQ(result.front(), '(');
    EXPECT_EQ(result.back(), ')');
}

// Test: Denominator zero with non-zero numerator should return parenthesized
TEST_F(PrintLensSpecificationTest_1382, DenominatorZero_ReturnsParenthesized_1382) {
    auto val = makeValue({18, 0}, {55, 1}, {35, 10}, {56, 10});
    Internal::printLensSpecification(os, val, nullptr);
    std::string result = os.str();
    EXPECT_EQ(result.front(), '(');
    EXPECT_EQ(result.back(), ')');
}

// Test: Normal zoom lens specification (e.g., 18-55mm F3.5-5.6)
TEST_F(PrintLensSpecificationTest_1382, NormalZoomLens_1382) {
    auto val = makeValue({18, 1}, {55, 1}, {35, 10}, {56, 10});
    Internal::printLensSpecification(os, val, nullptr);
    std::string result = os.str();
    EXPECT_NE(result.find("18"), std::string::npos);
    EXPECT_NE(result.find("55"), std::string::npos);
    EXPECT_NE(result.find("mm"), std::string::npos);
    EXPECT_NE(result.find("F"), std::string::npos);
}

// Test: Prime lens (same focal length, same f-number)
TEST_F(PrintLensSpecificationTest_1382, PrimeLens_1382) {
    auto val = makeValue({50, 1}, {50, 1}, {14, 10}, {14, 10});
    Internal::printLensSpecification(os, val, nullptr);
    std::string result = os.str();
    EXPECT_NE(result.find("50"), std::string::npos);
    EXPECT_NE(result.find("mm"), std::string::npos);
    EXPECT_NE(result.find("F"), std::string::npos);
    // For prime lens, focal length should not have a dash range
    // Count occurrences of "50" - should appear once in focal length portion
}

// Test: focalLength1 > focalLength2 (invalid order) should return parenthesized
TEST_F(PrintLensSpecificationTest_1382, FocalLengthReversed_ReturnsParenthesized_1382) {
    auto val = makeValue({55, 1}, {18, 1}, {35, 10}, {56, 10});
    Internal::printLensSpecification(os, val, nullptr);
    std::string result = os.str();
    EXPECT_EQ(result.front(), '(');
    EXPECT_EQ(result.back(), ')');
}

// Test: fNumber1 > fNumber2 (invalid order) should return parenthesized
TEST_F(PrintLensSpecificationTest_1382, FNumberReversed_ReturnsParenthesized_1382) {
    auto val = makeValue({18, 1}, {55, 1}, {56, 10}, {35, 10});
    Internal::printLensSpecification(os, val, nullptr);
    std::string result = os.str();
    EXPECT_EQ(result.front(), '(');
    EXPECT_EQ(result.back(), ')');
}

// Test: focalLength1 zero, focalLength2 non-zero
TEST_F(PrintLensSpecificationTest_1382, FocalLength1Zero_1382) {
    auto val = makeValue({0, 1}, {55, 1}, {35, 10}, {56, 10});
    Internal::printLensSpecification(os, val, nullptr);
    std::string result = os.str();
    EXPECT_NE(result.find("n/a"), std::string::npos);
    EXPECT_NE(result.find("mm"), std::string::npos);
}

// Test: focalLength2 zero, focalLength1 non-zero
TEST_F(PrintLensSpecificationTest_1382, FocalLength2Zero_1382) {
    auto val = makeValue({18, 1}, {0, 1}, {35, 10}, {56, 10});
    Internal::printLensSpecification(os, val, nullptr);
    std::string result = os.str();
    EXPECT_NE(result.find("18"), std::string::npos);
    EXPECT_NE(result.find("n/a"), std::string::npos);
    EXPECT_NE(result.find("mm"), std::string::npos);
}

// Test: fNumber1 zero, fNumber2 non-zero
TEST_F(PrintLensSpecificationTest_1382, FNumber1Zero_1382) {
    auto val = makeValue({18, 1}, {55, 1}, {0, 1}, {56, 10});
    Internal::printLensSpecification(os, val, nullptr);
    std::string result = os.str();
    EXPECT_NE(result.find("F"), std::string::npos);
    EXPECT_NE(result.find("n/a"), std::string::npos);
}

// Test: fNumber2 zero, fNumber1 non-zero
TEST_F(PrintLensSpecificationTest_1382, FNumber2Zero_1382) {
    auto val = makeValue({18, 1}, {55, 1}, {35, 10}, {0, 1});
    Internal::printLensSpecification(os, val, nullptr);
    std::string result = os.str();
    EXPECT_NE(result.find("F"), std::string::npos);
    EXPECT_NE(result.find("n/a"), std::string::npos);
}

// Test: Both f-numbers zero should not print F section
TEST_F(PrintLensSpecificationTest_1382, BothFNumbersZero_1382) {
    auto val = makeValue({18, 1}, {55, 1}, {0, 1}, {0, 1});
    Internal::printLensSpecification(os, val, nullptr);
    std::string result = os.str();
    EXPECT_NE(result.find("mm"), std::string::npos);
    EXPECT_EQ(result.find("F"), std::string::npos);
}

// Test: Second denominator zero should return parenthesized
TEST_F(PrintLensSpecificationTest_1382, SecondDenominatorZero_ReturnsParenthesized_1382) {
    auto val = makeValue({18, 1}, {55, 0}, {35, 10}, {56, 10});
    Internal::printLensSpecification(os, val, nullptr);
    std::string result = os.str();
    EXPECT_EQ(result.front(), '(');
    EXPECT_EQ(result.back(), ')');
}

// Test: Third denominator zero should return parenthesized
TEST_F(PrintLensSpecificationTest_1382, ThirdDenominatorZero_ReturnsParenthesized_1382) {
    auto val = makeValue({18, 1}, {55, 1}, {35, 0}, {56, 10});
    Internal::printLensSpecification(os, val, nullptr);
    std::string result = os.str();
    EXPECT_EQ(result.front(), '(');
    EXPECT_EQ(result.back(), ')');
}

// Test: Fourth denominator zero should return parenthesized
TEST_F(PrintLensSpecificationTest_1382, FourthDenominatorZero_ReturnsParenthesized_1382) {
    auto val = makeValue({18, 1}, {55, 1}, {35, 10}, {56, 0});
    Internal::printLensSpecification(os, val, nullptr);
    std::string result = os.str();
    EXPECT_EQ(result.front(), '(');
    EXPECT_EQ(result.back(), ')');
}

// Test: Equal focal lengths but different f-numbers
TEST_F(PrintLensSpecificationTest_1382, EqualFocalDifferentFNumber_1382) {
    auto val = makeValue({50, 1}, {50, 1}, {28, 10}, {56, 10});
    Internal::printLensSpecification(os, val, nullptr);
    std::string result = os.str();
    EXPECT_NE(result.find("50"), std::string::npos);
    EXPECT_NE(result.find("mm"), std::string::npos);
    EXPECT_NE(result.find("F"), std::string::npos);
}

// Test: Numerator zero with denominator zero should be okay (0/0 treated as 0)
TEST_F(PrintLensSpecificationTest_1382, ZeroOverZero_IsValid_1382) {
    auto val = makeValue({0, 0}, {0, 0}, {0, 0}, {0, 0});
    Internal::printLensSpecification(os, val, nullptr);
    std::string result = os.str();
    EXPECT_EQ(result, "n/a");
}

// Test: Large rational values
TEST_F(PrintLensSpecificationTest_1382, LargeRationalValues_1382) {
    auto val = makeValue({200, 1}, {400, 1}, {28, 10}, {56, 10});
    Internal::printLensSpecification(os, val, nullptr);
    std::string result = os.str();
    EXPECT_NE(result.find("200"), std::string::npos);
    EXPECT_NE(result.find("400"), std::string::npos);
    EXPECT_NE(result.find("mm"), std::string::npos);
}

// Test: Fractional focal lengths
TEST_F(PrintLensSpecificationTest_1382, FractionalFocalLengths_1382) {
    auto val = makeValue({185, 10}, {550, 10}, {35, 10}, {56, 10});
    Internal::printLensSpecification(os, val, nullptr);
    std::string result = os.str();
    EXPECT_NE(result.find("mm"), std::string::npos);
    EXPECT_NE(result.find("F"), std::string::npos);
}

// Test: focalLength1 == focalLength2, fNumber1 == fNumber2 (prime lens)
TEST_F(PrintLensSpecificationTest_1382, PrimeLensNoRange_1382) {
    auto val = makeValue({85, 1}, {85, 1}, {18, 10}, {18, 10});
    Internal::printLensSpecification(os, val, nullptr);
    std::string result = os.str();
    // Should contain "85" and "mm" and "F" but no dash in focal range
    EXPECT_NE(result.find("85"), std::string::npos);
    EXPECT_NE(result.find("mm"), std::string::npos);
}
