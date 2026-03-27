#include <gtest/gtest.h>
#include <string>
#include <algorithm>
#include <Exiv2/futils.hpp>

namespace Exiv2 {

// Test case for normal URI parsing with full information
TEST_F(UriParseTest_1809, ParseNormalUri_1809) {
    std::string uri = "http://username:password@host:80/path?query=1";
    Uri result = Uri::Parse(uri);
    
    EXPECT_EQ(result.Protocol, "http");
    EXPECT_EQ(result.Username, "username");
    EXPECT_EQ(result.Password, "password");
    EXPECT_EQ(result.Host, "host");
    EXPECT_EQ(result.Port, "80");
    EXPECT_EQ(result.Path, "/path");
    EXPECT_EQ(result.QueryString, "query=1");
}

// Test case for URI with no username and password
TEST_F(UriParseTest_1810, ParseUriWithoutAuth_1810) {
    std::string uri = "http://host:80/path?query=1";
    Uri result = Uri::Parse(uri);

    EXPECT_EQ(result.Protocol, "http");
    EXPECT_EQ(result.Username, "");
    EXPECT_EQ(result.Password, "");
    EXPECT_EQ(result.Host, "host");
    EXPECT_EQ(result.Port, "80");
    EXPECT_EQ(result.Path, "/path");
    EXPECT_EQ(result.QueryString, "query=1");
}

// Test case for URI with empty string
TEST_F(UriParseTest_1811, ParseEmptyUri_1811) {
    std::string uri = "";
    Uri result = Uri::Parse(uri);
    
    EXPECT_EQ(result.Protocol, "");
    EXPECT_EQ(result.Username, "");
    EXPECT_EQ(result.Password, "");
    EXPECT_EQ(result.Host, "");
    EXPECT_EQ(result.Port, "");
    EXPECT_EQ(result.Path, "");
    EXPECT_EQ(result.QueryString, "");
}

// Test case for URI with no protocol
TEST_F(UriParseTest_1812, ParseUriWithoutProtocol_1812) {
    std::string uri = "host:80/path?query=1";
    Uri result = Uri::Parse(uri);
    
    EXPECT_EQ(result.Protocol, "");
    EXPECT_EQ(result.Username, "");
    EXPECT_EQ(result.Password, "");
    EXPECT_EQ(result.Host, "host");
    EXPECT_EQ(result.Port, "80");
    EXPECT_EQ(result.Path, "/path");
    EXPECT_EQ(result.QueryString, "query=1");
}

// Test case for URI with default port for http
TEST_F(UriParseTest_1813, ParseUriWithDefaultHttpPort_1813) {
    std::string uri = "http://host/path?query=1";
    Uri result = Uri::Parse(uri);
    
    EXPECT_EQ(result.Protocol, "http");
    EXPECT_EQ(result.Username, "");
    EXPECT_EQ(result.Password, "");
    EXPECT_EQ(result.Host, "host");
    EXPECT_EQ(result.Port, "80");  // Default port for http
    EXPECT_EQ(result.Path, "/path");
    EXPECT_EQ(result.QueryString, "query=1");
}

// Test case for URI with a custom port
TEST_F(UriParseTest_1814, ParseUriWithCustomPort_1814) {
    std::string uri = "http://host:8080/path?query=1";
    Uri result = Uri::Parse(uri);
    
    EXPECT_EQ(result.Protocol, "http");
    EXPECT_EQ(result.Username, "");
    EXPECT_EQ(result.Password, "");
    EXPECT_EQ(result.Host, "host");
    EXPECT_EQ(result.Port, "8080");  // Custom port
    EXPECT_EQ(result.Path, "/path");
    EXPECT_EQ(result.QueryString, "query=1");
}

// Test case for URI with missing path
TEST_F(UriParseTest_1815, ParseUriWithoutPath_1815) {
    std::string uri = "http://host:80?query=1";
    Uri result = Uri::Parse(uri);

    EXPECT_EQ(result.Protocol, "http");
    EXPECT_EQ(result.Username, "");
    EXPECT_EQ(result.Password, "");
    EXPECT_EQ(result.Host, "host");
    EXPECT_EQ(result.Port, "80");
    EXPECT_EQ(result.Path, "");
    EXPECT_EQ(result.QueryString, "query=1");
}

// Test case for URI with no query string
TEST_F(UriParseTest_1816, ParseUriWithoutQuery_1816) {
    std::string uri = "http://host:80/path";
    Uri result = Uri::Parse(uri);

    EXPECT_EQ(result.Protocol, "http");
    EXPECT_EQ(result.Username, "");
    EXPECT_EQ(result.Password, "");
    EXPECT_EQ(result.Host, "host");
    EXPECT_EQ(result.Port, "80");
    EXPECT_EQ(result.Path, "/path");
    EXPECT_EQ(result.QueryString, "");
}

// Test case for malformed URI (missing ':' after protocol)
TEST_F(UriParseTest_1817, ParseMalformedUri_1817) {
    std::string uri = "http//host:80/path?query=1";  // Missing '://'
    Uri result = Uri::Parse(uri);

    EXPECT_EQ(result.Protocol, "");
    EXPECT_EQ(result.Username, "");
    EXPECT_EQ(result.Password, "");
    EXPECT_EQ(result.Host, "http//host");
    EXPECT_EQ(result.Port, "80");
    EXPECT_EQ(result.Path, "/path");
    EXPECT_EQ(result.QueryString, "query=1");
}

// Test case for URI with only protocol
TEST_F(UriParseTest_1818, ParseUriWithOnlyProtocol_1818) {
    std::string uri = "http://";
    Uri result = Uri::Parse(uri);

    EXPECT_EQ(result.Protocol, "http");
    EXPECT_EQ(result.Username, "");
    EXPECT_EQ(result.Password, "");
    EXPECT_EQ(result.Host, "");
    EXPECT_EQ(result.Port, "80");
    EXPECT_EQ(result.Path, "");
    EXPECT_EQ(result.QueryString, "");
}

}  // namespace Exiv2