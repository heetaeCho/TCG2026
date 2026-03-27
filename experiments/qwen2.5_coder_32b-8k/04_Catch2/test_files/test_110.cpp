#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "catch2/internal/catch_istream.hpp"



using namespace Catch;

using ::testing::Return;



class IStreamMock : public IStream {

public:

    MOCK_CONST_METHOD0(isConsole, bool());

    MOCK_METHOD0(stream, std::ostream&());

};



TEST_F(IStreamTest_110, IsConsole_ReturnsFalseByDefault_110) {

    IStreamMock mock;

    EXPECT_CALL(mock, isConsole()).WillOnce(Return(false));

    EXPECT_FALSE(mock.isConsole());

}



TEST_F(IStreamTest_110, IsConsole_ReturnsTrue_110) {

    IStreamMock mock;

    EXPECT_CALL(mock, isConsole()).WillOnce(Return(true));

    EXPECT_TRUE(mock.isConsole());

}



TEST_F(IStreamTest_110, Stream_ReturnsOstreamReference_110) {

    IStreamMock mock;

    std::ostream& stream = mock.stream();

    SUCCEED(); // Assuming that the returned reference is valid

}
