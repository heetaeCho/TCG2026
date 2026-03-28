#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "value.cpp"



using namespace Exiv2;

using namespace testing;



class StringValueBaseTest_804 : public Test {

protected:

    StringValueBase stringValueBase;

};



TEST_F(StringValueBaseTest_804, ReadValidBuffer_804) {

    const char* expected = "test";

    byte buf[] = {'t', 'e', 's', 't'};

    size_t len = sizeof(buf);

    

    int result = stringValueBase.read(buf, len, ByteOrder::bigEndian);



    EXPECT_EQ(result, 0);

    EXPECT_EQ(stringValueBase.value_, expected);

}



TEST_F(StringValueBaseTest_804, ReadEmptyBuffer_804) {

    byte buf[] = {};

    size_t len = sizeof(buf);

    

    int result = stringValueBase.read(buf, len, ByteOrder::bigEndian);



    EXPECT_EQ(result, 0);

    EXPECT_EQ(stringValueBase.value_, "");

}



TEST_F(StringValueBaseTest_804, ReadNullBuffer_804) {

    byte* buf = nullptr;

    size_t len = 10;

    

    int result = stringValueBase.read(buf, len, ByteOrder::bigEndian);



    EXPECT_EQ(result, 0);

    EXPECT_EQ(stringValueBase.value_, "");

}



TEST_F(StringValueBaseTest_804, ReadBufferWithNullCharacters_804) {

    const char* expected = "te\0st";

    byte buf[] = {'t', 'e', '\0', 's', 't'};

    size_t len = sizeof(buf);

    

    int result = stringValueBase.read(buf, len, ByteOrder::bigEndian);



    EXPECT_EQ(result, 0);

    EXPECT_EQ(stringValueBase.value_, std::string(expected, len));

}
