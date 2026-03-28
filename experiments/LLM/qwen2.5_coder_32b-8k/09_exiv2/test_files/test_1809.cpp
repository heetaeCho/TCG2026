#include <gtest/gtest.h>

#include "exiv2/futils.hpp"



namespace {



class UriTest_1809 : public ::testing::Test {

protected:

    Exiv2::Uri uri;

};



TEST_F(UriTest_1809, Parse_EmptyString_ReturnsEmptyUri_1809) {

    auto result = uri.Parse("");

    EXPECT_TRUE(result.Protocol.empty());

    EXPECT_TRUE(result.Host.empty());

    EXPECT_TRUE(result.Port.empty());

    EXPECT_TRUE(result.Path.empty());

    EXPECT_TRUE(result.QueryString.empty());

    EXPECT_TRUE(result.Username.empty());

    EXPECT_TRUE(result.Password.empty());

}



TEST_F(UriTest_1809, Parse_HttpSchemeWithoutPath_ReturnsCorrectUri_1809) {

    auto result = uri.Parse("http://example.com");

    EXPECT_EQ(result.Protocol, "http:");

    EXPECT_EQ(result.Host, "example.com");

    EXPECT_EQ(result.Port, "80");

    EXPECT_TRUE(result.Path.empty());

    EXPECT_TRUE(result.QueryString.empty());

}



TEST_F(UriTest_1809, Parse_HttpSchemeWithPort_ReturnsCorrectUri_1809) {

    auto result = uri.Parse("http://example.com:8080");

    EXPECT_EQ(result.Protocol, "http:");

    EXPECT_EQ(result.Host, "example.com");

    EXPECT_EQ(result.Port, "8080");

    EXPECT_TRUE(result.Path.empty());

    EXPECT_TRUE(result.QueryString.empty());

}



TEST_F(UriTest_1809, Parse_HttpSchemeWithUsernameAndPassword_ReturnsCorrectUri_1809) {

    auto result = uri.Parse("http://user:pass@example.com");

    EXPECT_EQ(result.Protocol, "http:");

    EXPECT_EQ(result.Host, "example.com");

    EXPECT_EQ(result.Port, "80");

    EXPECT_TRUE(result.Path.empty());

    EXPECT_TRUE(result.QueryString.empty());

    EXPECT_EQ(result.Username, "user");

    EXPECT_EQ(result.Password, "pass");

}



TEST_F(UriTest_1809, Parse_HttpSchemeWithPath_ReturnsCorrectUri_1809) {

    auto result = uri.Parse("http://example.com/path/to/resource");

    EXPECT_EQ(result.Protocol, "http:");

    EXPECT_EQ(result.Host, "example.com");

    EXPECT_EQ(result.Port, "80");

    EXPECT_EQ(result.Path, "/path/to/resource");

    EXPECT_TRUE(result.QueryString.empty());

}



TEST_F(UriTest_1809, Parse_HttpSchemeWithQueryString_ReturnsCorrectUri_1809) {

    auto result = uri.Parse("http://example.com?query=param");

    EXPECT_EQ(result.Protocol, "http:");

    EXPECT_EQ(result.Host, "example.com");

    EXPECT_EQ(result.Port, "80");

    EXPECT_TRUE(result.Path.empty());

    EXPECT_EQ(result.QueryString, "?query=param");

}



TEST_F(UriTest_1809, Parse_FtpScheme_ReturnsCorrectUri_1809) {

    auto result = uri.Parse("ftp://example.com:21/path/to/resource?query=param");

    EXPECT_EQ(result.Protocol, "ftp:");

    EXPECT_EQ(result.Host, "example.com");

    EXPECT_EQ(result.Port, "21");

    EXPECT_EQ(result.Path, "/path/to/resource");

    EXPECT_EQ(result.QueryString, "?query=param");

}



TEST_F(UriTest_1809, Parse_HttpsScheme_ReturnsCorrectUri_1809) {

    auto result = uri.Parse("https://example.com:443/secure/path?query=secure");

    EXPECT_EQ(result.Protocol, "https:");

    EXPECT_EQ(result.Host, "example.com");

    EXPECT_EQ(result.Port, "443");

    EXPECT_EQ(result.Path, "/secure/path");

    EXPECT_EQ(result.QueryString, "?query=secure");

}



TEST_F(UriTest_1809, Parse_NoScheme_ReturnsCorrectUri_1809) {

    auto result = uri.Parse("example.com/path/to/resource?query=param");

    EXPECT_TRUE(result.Protocol.empty());

    EXPECT_EQ(result.Host, "example.com");

    EXPECT_TRUE(result.Port.empty());

    EXPECT_EQ(result.Path, "/path/to/resource");

    EXPECT_EQ(result.QueryString, "?query=param");

}



TEST_F(UriTest_1809, Parse_MissingPort_ReturnsDefaultHttpPort_1809) {

    auto result = uri.Parse("http://example.com/path/to/resource?query=param");

    EXPECT_EQ(result.Protocol, "http:");

    EXPECT_EQ(result.Host, "example.com");

    EXPECT_EQ(result.Port, "80");

    EXPECT_EQ(result.Path, "/path/to/resource");

    EXPECT_EQ(result.QueryString, "?query=param");

}



TEST_F(UriTest_1809, Parse_NoPath_ReturnsCorrectUri_1809) {

    auto result = uri.Parse("http://example.com?query=param");

    EXPECT_EQ(result.Protocol, "http:");

    EXPECT_EQ(result.Host, "example.com");

    EXPECT_EQ(result.Port, "80");

    EXPECT_TRUE(result.Path.empty());

    EXPECT_EQ(result.QueryString, "?query=param");

}



TEST_F(UriTest_1809, Parse_NoQueryString_ReturnsCorrectUri_1809) {

    auto result = uri.Parse("http://example.com/path/to/resource");

    EXPECT_EQ(result.Protocol, "http:");

    EXPECT_EQ(result.Host, "example.com");

    EXPECT_EQ(result.Port, "80");

    EXPECT_EQ(result.Path, "/path/to/resource");

    EXPECT_TRUE(result.QueryString.empty());

}



TEST_F(UriTest_1809, Parse_NoUserInfo_ReturnsCorrectUri_1809) {

    auto result = uri.Parse("http://example.com:8080/path/to/resource?query=param");

    EXPECT_EQ(result.Protocol, "http:");

    EXPECT_EQ(result.Host, "example.com");

    EXPECT_EQ(result.Port, "8080");

    EXPECT_EQ(result.Path, "/path/to/resource");

    EXPECT_EQ(result.QueryString, "?query=param");

    EXPECT_TRUE(result.Username.empty());

    EXPECT_TRUE(result.Password.empty());

}



} // namespace
