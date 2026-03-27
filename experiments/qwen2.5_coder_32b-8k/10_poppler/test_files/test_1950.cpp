#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include <optional>



using namespace ::testing;



// Mock class for testing the isValidResult function

class ResultValidatorMock {

public:

    MOCK_CONST_METHOD1(isValidResult, bool(int));

};



// Test fixture for the hasValidResult function

template<typename Result>

class HasValidResultTest : public Test {

protected:

    NiceMock<ResultValidatorMock> mock_validator;

    

    bool hasValidResult(const std::optional<Result>& result) const {

        if (!result) {

            return false;

        }

        return mock_validator.isValidResult(result.value());

    }

};



// Normal operation tests

TEST_F(HasValidResultTest_1950, ValidResult_ReturnsTrue_1950) {

    EXPECT_CALL(mock_validator, isValidResult(42)).WillOnce(Return(true));

    EXPECT_TRUE(hasValidResult(std::optional<int>(42)));

}



TEST_F(HasValidResultTest_1950, InvalidResult_ReturnsFalse_1950) {

    EXPECT_CALL(mock_validator, isValidResult(42)).WillOnce(Return(false));

    EXPECT_FALSE(hasValidResult(std::optional<int>(42)));

}



// Boundary conditions tests

TEST_F(HasValidResultTest_1950, EmptyOptional_ReturnsFalse_1950) {

    EXPECT_FALSE(hasValidResult(std::optional<int>()));

}



// Exceptional or error cases tests

// Since the function does not throw exceptions based on the given signature,

// no exceptional or error case tests are applicable here.



// Verification of external interactions tests

TEST_F(HasValidResultTest_1950, CallsIsValidResultWithCorrectValue_1950) {

    EXPECT_CALL(mock_validator, isValidResult(42)).Times(1);

    hasValidResult(std::optional<int>(42));

}



TEST_F(HasValidResultTest_1950, DoesNotCallIsValidResultForEmptyOptional_1950) {

    EXPECT_CALL(mock_validator, isValidResult(_)).Times(0);

    hasValidResult(std::optional<int>());

}
