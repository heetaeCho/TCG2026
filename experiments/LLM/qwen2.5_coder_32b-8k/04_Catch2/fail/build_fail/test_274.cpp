#include <gtest/gtest.h>

#include "catch2/catch_tostring.hpp"



namespace Catch {

    class ReusableStringStreamMock : public ReusableStringStream {

    public:

        MOCK_METHOD(void, str, (const std::string &str), (override));

        MOCK_METHOD(const std::string&, str, (), (const, override));

        MOCK_METHOD(std::ostream&, get, (), (override));

        MOCK_METHOD(ReusableStringStream&, operator<<, (bool const& value), (override));

        MOCK_METHOD(ReusableStringStream&, operator<<, (std::nullptr_t), (override));

        MOCK_METHOD(ReusableStringStream&, operator<<, (int const& value), (override));

        MOCK_METHOD(ReusableStringStream&, operator<<, (long const& value), (override));

        MOCK_METHOD(ReusableStringStream&, operator<<, (long long const& value), (override));

        MOCK_METHOD(ReusableStringStream&, operator<<, (unsigned int const& value), (override));

        MOCK_METHOD(ReusableStringStream&, operator<<, (unsigned long const& value), (override));

        MOCK_METHOD(ReusableStringStream&, operator<<, (unsigned long long const& value), (override));

        MOCK_METHOD(ReusableStringStream&, operator<<, (char const& value), (override));

        MOCK_METHOD(ReusableStringStream&, operator<<, (signed char const& value), (override));

        MOCK_METHOD(ReusableStringStream&, operator<<, (unsigned char const& value), (override));

        MOCK_METHOD(ReusableStringStream&, operator<<, (float const& value), (override));

        MOCK_METHOD(ReusableStringStream&, operator<<, (double const& value), (override));

    };

}



using namespace Catch;



TEST(StringMakerUnsignedLongLongTest_274, Convert_NormalValue_274) {

    ReusableStringStreamMock rssMock;

    EXPECT_CALL(rssMock, get()).WillRepeatedly(testing::ReturnRef(std::cout));



    std::string result = StringMaker<unsigned long long>::convert(100ULL);

    EXPECT_EQ(result, "100");

}



TEST(StringMakerUnsignedLongLongTest_274, Convert_HexThresholdValue_274) {

    ReusableStringStreamMock rssMock;

    EXPECT_CALL(rssMock, get()).WillRepeatedly(testing::ReturnRef(std::cout));



    std::string result = StringMaker<unsigned long long>::convert(255ULL);

    EXPECT_EQ(result, "255 (0xff)");

}



TEST(StringMakerUnsignedLongLongTest_274, Convert_AboveHexThresholdValue_274) {

    ReusableStringStreamMock rssMock;

    EXPECT_CALL(rssMock, get()).WillRepeatedly(testing::ReturnRef(std::cout));



    std::string result = StringMaker<unsigned long long>::convert(256ULL);

    EXPECT_EQ(result, "256 (0x100)");

}



TEST(StringMakerUnsignedLongLongTest_274, Convert_MaxValue_274) {

    ReusableStringStreamMock rssMock;

    EXPECT_CALL(rssMock, get()).WillRepeatedly(testing::ReturnRef(std::cout));



    std::string result = StringMaker<unsigned long long>::convert(ULLONG_MAX);

    EXPECT_EQ(result, "18446744073709551615 (0xffffffffffffffff)");

}
