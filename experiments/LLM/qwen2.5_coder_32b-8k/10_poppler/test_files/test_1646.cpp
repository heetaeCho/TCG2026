#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "TestProjects/poppler/poppler/Decrypt.cc"

#include "TestProjects/poppler/goo/GooString.h"



using namespace testing;



// Mock for sha256, sha384, and sha512 functions

class HashMock {

public:

    MOCK_METHOD3(sha256Mock, void(const unsigned char*, int, unsigned char*));

    MOCK_METHOD3(sha384Mock, void(const unsigned char*, int, unsigned char*));

    MOCK_METHOD3(sha512Mock, void(const unsigned char*, int, unsigned char*));

};



HashMock* hashMock = nullptr;



void sha256(const unsigned char *input, int length, unsigned char *output) {

    hashMock->sha256Mock(input, length, output);

}



void sha384(const unsigned char *input, int length, unsigned char *output) {

    hashMock->sha384Mock(input, length, output);

}



void sha512(const unsigned char *input, int length, unsigned char *output) {

    hashMock->sha512Mock(input, length, output);

}



TEST(Revision6HashTest_1646, NormalOperationWithUserKey_1646) {

    HashMock mock;

    hashMock = &mock;



    GooString password("password");

    unsigned char K[32] = {0};

    const char* userKey = "userKey";

    

    EXPECT_CALL(mock, sha256Mock(_, _, _)).Times(1);

    revision6Hash(&password, K, userKey);

}



TEST(Revision6HashTest_1646, NormalOperationWithoutUserKey_1646) {

    HashMock mock;

    hashMock = &mock;



    GooString password("password");

    unsigned char K[32] = {0};

    

    EXPECT_CALL(mock, sha256Mock(_, _, _)).Times(1);

    revision6Hash(&password, K, nullptr);

}



TEST(Revision6HashTest_1646, BoundaryConditionEmptyPassword_1646) {

    HashMock mock;

    hashMock = &mock;



    GooString password("");

    unsigned char K[32] = {0};

    

    EXPECT_CALL(mock, sha256Mock(_, _, _)).Times(1);

    revision6Hash(&password, K, nullptr);

}



TEST(Revision6HashTest_1646, BoundaryConditionEmptyUserKey_1646) {

    HashMock mock;

    hashMock = &mock;



    GooString password("password");

    unsigned char K[32] = {0};

    const char* userKey = "";

    

    EXPECT_CALL(mock, sha256Mock(_, _, _)).Times(1);

    revision6Hash(&password, K, userKey);

}



TEST(Revision6HashTest_1646, Sha384CalledBasedOnRemainder_1646) {

    HashMock mock;

    hashMock = &mock;



    GooString password("somePassword");

    unsigned char K[32] = {0};

    

    EXPECT_CALL(mock, sha384Mock(_, _, _)).Times(1);

    revision6Hash(&password, K, nullptr);

}



TEST(Revision6HashTest_1646, Sha512CalledBasedOnRemainder_1646) {

    HashMock mock;

    hashMock = &mock;



    GooString password("anotherPassword");

    unsigned char K[32] = {0};

    

    EXPECT_CALL(mock, sha512Mock(_, _, _)).Times(1);

    revision6Hash(&password, K, nullptr);

}
