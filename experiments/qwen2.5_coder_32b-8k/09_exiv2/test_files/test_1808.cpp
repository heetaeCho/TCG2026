#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/futils.hpp"



namespace {



using namespace Exiv2;



class UriTest_1808 : public ::testing::Test {

protected:

    void SetUp() override {

        // Setup code if needed

    }



    void TearDown() override {

        // Teardown code if needed

    }

};



TEST_F(UriTest_1808, Decode_EmptyUriComponents_1808) {

    Uri uri;

    uri.QueryString = "";

    uri.Path = "";

    uri.Host = "";

    uri.Username = "";

    uri.Password = "";



    Uri::Decode(uri);



    EXPECT_EQ("", uri.QueryString);

    EXPECT_EQ("", uri.Path);

    EXPECT_EQ("", uri.Host);

    EXPECT_EQ("", uri.Username);

    EXPECT_EQ("", uri.Password);

}



TEST_F(UriTest_1808, Decode_PercentEncodedUriComponents_1808) {

    Uri uri;

    uri.QueryString = "param%20value";

    uri.Path = "/path/to/resource%20with%20spaces";

    uri.Host = "example%2ecom";

    uri.Username = "user%name";

    uri.Password = "p%40ssword";



    Uri::Decode(uri);



    EXPECT_EQ("param value", uri.QueryString);

    EXPECT_EQ("/path/to/resource with spaces", uri.Path);

    EXPECT_EQ("example.com", uri.Host);

    EXPECT_EQ("user%name", uri.Username); // Percent decoding should not apply to usernames

    EXPECT_EQ("p@ssword", uri.Password);   // Percent decoding should apply to passwords

}



TEST_F(UriTest_1808, Decode_UriWithNoPercentEncoding_1808) {

    Uri uri;

    uri.QueryString = "param=value";

    uri.Path = "/path/to/resource";

    uri.Host = "example.com";

    uri.Username = "username";

    uri.Password = "password";



    Uri::Decode(uri);



    EXPECT_EQ("param=value", uri.QueryString);

    EXPECT_EQ("/path/to/resource", uri.Path);

    EXPECT_EQ("example.com", uri.Host);

    EXPECT_EQ("username", uri.Username);

    EXPECT_EQ("password", uri.Password);

}



TEST_F(UriTest_1808, Decode_BoundaryCases_1808) {

    Uri uri;

    uri.QueryString = "%";

    uri.Path = "/%";

    uri.Host = "ex%ample.com";

    uri.Username = "%user";

    uri.Password = "p%";



    Uri::Decode(uri);



    EXPECT_EQ("%", uri.QueryString); // Invalid percent encoding should remain unchanged

    EXPECT_EQ("/%", uri.Path);       // Invalid percent encoding should remain unchanged

    EXPECT_EQ("ex%ample.com", uri.Host);

    EXPECT_EQ("%user", uri.Username);  // Percent decoding should not apply to usernames

    EXPECT_EQ("p%", uri.Password);     // Invalid percent encoding should remain unchanged

}



} // namespace
