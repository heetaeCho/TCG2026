#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "tags_int.cpp"



namespace Exiv2 {

    class Value {

    public:

        virtual ~Value() = default;

        virtual operator std::string() const = 0;

    };



    class MockValue : public Value {

    public:

        MOCK_METHOD(std::string, operator(), (), const);

    };

}



using namespace ::testing;



class PrintValueTest_1372 : public Test {

protected:

    NiceMock<Exiv2::MockValue> mock_value_;

    std::ostringstream os_;

};



TEST_F(PrintValueTest_1372, NormalOperation_1372) {

    EXPECT_CALL(mock_value_, operator()()).WillOnce(Return("test_string"));

    Exiv2::Internal::printValue(os_, mock_value_, nullptr);

    EXPECT_EQ(os_.str(), "test_string");

}



TEST_F(PrintValueTest_1372, EmptyString_1372) {

    EXPECT_CALL(mock_value_, operator()()).WillOnce(Return(""));

    Exiv2::Internal::printValue(os_, mock_value_, nullptr);

    EXPECT_EQ(os_.str(), "");

}



TEST_F(PrintValueTest_1372, NumericValue_1372) {

    EXPECT_CALL(mock_value_, operator()()).WillOnce(Return("12345"));

    Exiv2::Internal::printValue(os_, mock_value_, nullptr);

    EXPECT_EQ(os_.str(), "12345");

}



TEST_F(PrintValueTest_1372, SpecialCharacters_1372) {

    EXPECT_CALL(mock_value_, operator()()).WillOnce(Return("special!@#"));

    Exiv2::Internal::printValue(os_, mock_value_, nullptr);

    EXPECT_EQ(os_.str(), "special!@#");

}



TEST_F(PrintValueTest_1372, NullptrExifData_1372) {

    EXPECT_CALL(mock_value_, operator()()).WillOnce(Return("test_string"));

    Exiv2::Internal::printValue(os_, mock_value_, nullptr);

    EXPECT_EQ(os_.str(), "test_string");

}
