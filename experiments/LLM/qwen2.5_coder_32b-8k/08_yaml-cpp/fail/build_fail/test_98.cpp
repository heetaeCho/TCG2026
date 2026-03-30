#include <gtest/gtest.h>

#include "streamcharsource.h"

#include <sstream>



namespace YAML {

    class StreamMock : public Stream {

    public:

        MOCK_CONST_METHOD1(CharAt, char(size_t));

        MOCK_CONST_METHOD0(operator bool, bool());

        MOCK_METHOD0(get, char());

        MOCK_METHOD1(get, std::string(int));

        MOCK_METHOD1(eat, void(int));

        MOCK_METHOD0(peek, char());

        MOCK_METHOD0(mark, const Mark());

        MOCK_METHOD0(pos, int());

        MOCK_METHOD0(line, int());

        MOCK_METHOD0(column, int());

        MOCK_METHOD0(ResetColumn, void());

    };

}



using namespace YAML;



class StreamCharSourceTest_98 : public ::testing::Test {

protected:

    std::istringstream iss;

    StreamMock streamMock;

    StreamCharSource source;



    StreamCharSourceTest_98() : iss("test"), streamMock(iss), source(streamMock) {}

};



TEST_F(StreamCharSourceTest_98, OperatorBool_ReturnsTrueWhenStreamIsValid_98) {

    EXPECT_CALL(streamMock, operator bool()).WillOnce(::testing::Return(true));

    EXPECT_TRUE(static_cast<bool>(source));

}



TEST_F(StreamCharSourceTest_98, OperatorBool_ReturnsFalseWhenStreamIsInvalid_98) {

    EXPECT_CALL(streamMock, operator bool()).WillOnce(::testing::Return(false));

    EXPECT_FALSE(static_cast<bool>(source));

}



TEST_F(StreamCharSourceTest_98, OperatorIndex_ReturnsCorrectCharacter_98) {

    EXPECT_CALL(streamMock, CharAt(0)).WillOnce(::testing::Return('t'));

    EXPECT_EQ(source[0], 't');

}



TEST_F(StreamCharSourceTest_98, OperatorPlus_IncrementsOffset_98) {

    auto newSource = source + 1;

    EXPECT_EQ(newSource[0], streamMock.CharAt(1));

}



TEST_F(StreamCharSourceTest_98, OperatorIndex_OutOfBounds_ReturnsExpectedCharacter_98) {

    EXPECT_CALL(streamMock, CharAt(4)).WillOnce(::testing::Return('\0'));

    EXPECT_EQ(source[4], '\0');

}
