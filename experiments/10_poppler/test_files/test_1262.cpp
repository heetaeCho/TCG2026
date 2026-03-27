#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include <cstdarg>

#include <cstdio>



// Mocking qvsnprintf to verify its interaction without re-implementing internal logic.

int qvsnprintf(char *str, size_t size, const char *format, va_list ap);



namespace Poppler {

    static int poppler_vasprintf(char **buf_ptr, const char *format, va_list ap);

}



// Mock function for qvsnprintf

class MockPopplerUtils {

public:

    MOCK_STATIC_METHOD4(qvsnprintf, int(char*, size_t, const char*, va_list));

};



TEST_F(PopplerUtilsTest_1262, NormalOperation_1262) {

    testing::StrictMock<MockPopplerUtils> mock;



    const char* format = "Hello, %s!";

    const char* arg = "World";

    size_t expected_size = 14; // "Hello, World!" + '\0'

    

    char buffer[expected_size];

    va_list ap;

    va_start(ap, arg);

    EXPECT_CALL(mock, qvsnprintf(buffer, expected_size, format, ap))

        .WillOnce(testing::Return(expected_size - 1));

    va_end(ap);



    char* buf_ptr = nullptr;

    va_start(ap, arg);

    int result = Poppler::poppler_vasprintf(&buf_ptr, format, ap);

    va_end(ap);



    EXPECT_EQ(result, expected_size - 1);

    delete[] buf_ptr;

}



TEST_F(PopplerUtilsTest_1262, BoundaryCondition_EmptyString_1262) {

    testing::StrictMock<MockPopplerUtils> mock;



    const char* format = "";

    

    size_t expected_size = 1; // Only '\0'

    

    char buffer[expected_size];

    va_list ap;

    va_start(ap, format);

    EXPECT_CALL(mock, qvsnprintf(buffer, expected_size, format, ap))

        .WillOnce(testing::Return(expected_size - 1));

    va_end(ap);



    char* buf_ptr = nullptr;

    va_start(ap, format);

    int result = Poppler::poppler_vasprintf(&buf_ptr, format, ap);

    va_end(ap);



    EXPECT_EQ(result, expected_size - 1);

    delete[] buf_ptr;

}



TEST_F(PopplerUtilsTest_1262, BoundaryCondition_MaxSize_1262) {

    testing::StrictMock<MockPopplerUtils> mock;



    const char* format = "%s";

    const char* arg = "A very long string that should push the boundaries of typical buffer sizes.";

    

    size_t expected_size = 78; // length of the argument + '\0'

    

    char buffer[expected_size];

    va_list ap;

    va_start(ap, arg);

    EXPECT_CALL(mock, qvsnprintf(buffer, expected_size, format, ap))

        .WillOnce(testing::Return(expected_size - 1));

    va_end(ap);



    char* buf_ptr = nullptr;

    va_start(ap, arg);

    int result = Poppler::poppler_vasprintf(&buf_ptr, format, ap);

    va_end(ap);



    EXPECT_EQ(result, expected_size - 1);

    delete[] buf_ptr;

}



TEST_F(PopplerUtilsTest_1262, ExceptionalCase_NullFormat_1262) {

    testing::StrictMock<MockPopplerUtils> mock;



    const char* format = nullptr;

    

    size_t expected_size = 1; // Only '\0'

    

    char buffer[expected_size];

    va_list ap;

    va_start(ap, format);

    EXPECT_CALL(mock, qvsnprintf(buffer, expected_size, format, ap))

        .WillOnce(testing::Return(expected_size - 1));

    va_end(ap);



    char* buf_ptr = nullptr;

    va_start(ap, format);

    int result = Poppler::poppler_vasprintf(&buf_ptr, format, ap);

    va_end(ap);



    EXPECT_EQ(result, expected_size - 1);

    delete[] buf_ptr;

}



// Mock implementation of qvsnprintf for testing purposes

int qvsnprintf(char *str, size_t size, const char *format, va_list ap) {

    return vsnprintf(str, size, format, ap);

}
