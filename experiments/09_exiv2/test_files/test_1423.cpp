#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "tags_int.cpp"



namespace Exiv2 {

    class ValueMock : public Value {

    public:

        MOCK_CONST_METHOD0(size, size_t());

        MOCK_CONST_METHOD0(typeId, TypeId());

        MOCK_CONST_METHOD0(toString, std::string());

    };

}



using namespace ::testing;

using namespace Exiv2;



class PrintXmpVersionTest_1423 : public Test {

protected:

    NiceMock<ValueMock> mockValue;

};



TEST_F(PrintXmpVersionTest_1423, NormalOperation_XmpText_1423) {

    EXPECT_CALL(mockValue, size()).WillOnce(Return(4));

    EXPECT_CALL(mockValue, typeId()).WillOnce(Return(xmpText));

    EXPECT_CALL(mockValue, toString()).WillOnce(Return("1.0.0.0"));



    std::ostringstream os;

    Internal::printXmpVersion(os, mockValue, nullptr);

    EXPECT_EQ("1.0", os.str());

}



TEST_F(PrintXmpVersionTest_1423, InvalidSize_1423) {

    EXPECT_CALL(mockValue, size()).WillOnce(Return(5));

    EXPECT_CALL(mockValue, typeId()).WillOnce(Return(xmpText));



    std::ostringstream os;

    Internal::printXmpVersion(os, mockValue, nullptr);

    EXPECT_EQ("(1)", os.str());  // Assuming the mock returns 1 for some value

}



TEST_F(PrintXmpVersionTest_1423, InvalidTypeId_1423) {

    EXPECT_CALL(mockValue, size()).WillOnce(Return(4));

    EXPECT_CALL(mockValue, typeId()).WillOnce(Return(string));



    std::ostringstream os;

    Internal::printXmpVersion(os, mockValue, nullptr);

    EXPECT_EQ("(1)", os.str());  // Assuming the mock returns 1 for some value

}



TEST_F(PrintXmpVersionTest_1423, BoundarySizeZero_1423) {

    EXPECT_CALL(mockValue, size()).WillOnce(Return(0));

    EXPECT_CALL(mockValue, typeId()).WillOnce(Return(xmpText));



    std::ostringstream os;

    Internal::printXmpVersion(os, mockValue, nullptr);

    EXPECT_EQ("(1)", os.str());  // Assuming the mock returns 1 for some value

}



TEST_F(PrintXmpVersionTest_1423, BoundarySizeMax_1423) {

    EXPECT_CALL(mockValue, size()).WillOnce(Return(std::numeric_limits<size_t>::max()));

    EXPECT_CALL(mockValue, typeId()).WillOnce(Return(xmpText));



    std::ostringstream os;

    Internal::printXmpVersion(os, mockValue, nullptr);

    EXPECT_EQ("(1)", os.str());  // Assuming the mock returns 1 for some value

}
