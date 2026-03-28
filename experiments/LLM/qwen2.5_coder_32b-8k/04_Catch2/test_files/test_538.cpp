#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "catch2/internal/catch_jsonwriter.hpp"



namespace Catch {

    class MockOstream : public std::ostream {

    public:

        using std::ostream::ostream;

        MOCK_METHOD(std::ostream&, write, (const char* s, std::streamsize n), (override));

    };

}



using namespace ::testing;



class JsonValueWriterTest_538 : public Test {

protected:

    NiceMock<Catch::MockOstream> mockOs;

    Catch::JsonValueWriter writer{mockOs};

};



TEST_F(JsonValueWriterTest_538, WriteTrueInvokesWriteImplWithTrueString_538) {

    EXPECT_CALL(mockOs, write(StrEq("true"), Eq(4)));

    std::move(writer).write(true);

}



TEST_F(JsonValueWriterTest_538, WriteFalseInvokesWriteImplWithFalseString_538) {

    EXPECT_CALL(mockOs, write(StrEq("false"), Eq(5)));

    std::move(writer).write(false);

}
