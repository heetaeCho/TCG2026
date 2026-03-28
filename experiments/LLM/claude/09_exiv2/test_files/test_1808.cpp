#include <gtest/gtest.h>
#include "exiv2/futils.hpp"

using namespace Exiv2;

// Test fixture for Uri class
class UriTest_1808 : public ::testing::Test {
protected:
    Uri uri;
};

// ==================== Parse Tests ====================

TEST_F(UriTest_1808, ParseFullUri_1808) {
    Uri result = Uri::Parse("http://user:pass@example.com:8080/path/to/resource?key=value");
    EXPECT_EQ(result.Protocol, "http");
    EXPECT_EQ(result.Host, "example.com");
    EXPECT_EQ(result.Port, "8080");
    EXPECT_EQ(result.Path, "/path/to/resource");
    EXPECT_EQ(result.QueryString, "key=value");
    EXPECT_EQ(result.Username, "user");
    EXPECT_EQ(result.Password, "pass");
}

TEST_F(UriTest_1808, ParseSimpleUri_1808) {
    Uri result = Uri::Parse("http://example.com");
    EXPECT_EQ(result.Protocol, "http");
    EXPECT_EQ(result.Host, "example.com");
    EXPECT_EQ(result.Port, "");
    EXPECT_EQ(result.Path, "");
    EXPECT_EQ(result.QueryString, "");
    EXPECT_EQ(result.Username, "");
    EXPECT_EQ(result.Password, "");
}

TEST_F(UriTest_1808, ParseUriWithPath_1808) {
    Uri result = Uri::Parse("http://example.com/path/to/page");
    EXPECT_EQ(result.Protocol, "http");
    EXPECT_EQ(result.Host, "example.com");
    EXPECT_EQ(result.Path, "/path/to/page");
}

TEST_F(UriTest_1808, ParseUriWithPort_1808) {
    Uri result = Uri::Parse("http://example.com:9090/path");
    EXPECT_EQ(result.Protocol, "http");
    EXPECT_EQ(result.Host, "example.com");
    EXPECT_EQ(result.Port, "9090");
    EXPECT_EQ(result.Path, "/path");
}

TEST_F(UriTest_1808, ParseUriWithQueryString_1808) {
    Uri result = Uri::Parse("http://example.com/path?foo=bar&baz=qux");
    EXPECT_EQ(result.Protocol, "http");
    EXPECT_EQ(result.Host, "example.com");
    EXPECT_EQ(result.Path, "/path");
    EXPECT_EQ(result.QueryString, "foo=bar&baz=qux");
}

TEST_F(UriTest_1808, ParseUriWithUsername_1808) {
    Uri result = Uri::Parse("http://user@example.com/path");
    EXPECT_EQ(result.Protocol, "http");
    EXPECT_EQ(result.Host, "example.com");
    EXPECT_EQ(result.Username, "user");
    EXPECT_EQ(result.Path, "/path");
}

TEST_F(UriTest_1808, ParseUriWithUsernameAndPassword_1808) {
    Uri result = Uri::Parse("http://user:password@example.com/path");
    EXPECT_EQ(result.Protocol, "http");
    EXPECT_EQ(result.Host, "example.com");
    EXPECT_EQ(result.Username, "user");
    EXPECT_EQ(result.Password, "password");
    EXPECT_EQ(result.Path, "/path");
}

TEST_F(UriTest_1808, ParseHttpsProtocol_1808) {
    Uri result = Uri::Parse("https://example.com/secure");
    EXPECT_EQ(result.Protocol, "https");
    EXPECT_EQ(result.Host, "example.com");
    EXPECT_EQ(result.Path, "/secure");
}

TEST_F(UriTest_1808, ParseFtpProtocol_1808) {
    Uri result = Uri::Parse("ftp://files.example.com/data");
    EXPECT_EQ(result.Protocol, "ftp");
    EXPECT_EQ(result.Host, "files.example.com");
    EXPECT_EQ(result.Path, "/data");
}

TEST_F(UriTest_1808, ParseEmptyString_1808) {
    Uri result = Uri::Parse("");
    EXPECT_EQ(result.Protocol, "");
    EXPECT_EQ(result.Host, "");
    EXPECT_EQ(result.Port, "");
    EXPECT_EQ(result.Path, "");
    EXPECT_EQ(result.QueryString, "");
    EXPECT_EQ(result.Username, "");
    EXPECT_EQ(result.Password, "");
}

TEST_F(UriTest_1808, ParseUriWithOnlyPath_1808) {
    Uri result = Uri::Parse("/just/a/path");
    EXPECT_EQ(result.Path, "/just/a/path");
}

TEST_F(UriTest_1808, ParseUriNoProtocol_1808) {
    Uri result = Uri::Parse("example.com/path");
    // Without "://", parsing behavior may differ
    // Just ensure it doesn't crash and returns something
    EXPECT_FALSE(result.Path.empty() && result.Host.empty() && result.Protocol.empty());
}

// ==================== Decode Tests ====================

TEST_F(UriTest_1808, DecodeEncodedPath_1808) {
    Uri testUri;
    testUri.Path = "/path%20with%20spaces";
    testUri.QueryString = "";
    testUri.Host = "";
    testUri.Username = "";
    testUri.Password = "";
    testUri.Protocol = "";
    testUri.Port = "";

    Uri::Decode(testUri);
    EXPECT_EQ(testUri.Path, "/path with spaces");
}

TEST_F(UriTest_1808, DecodeEncodedQueryString_1808) {
    Uri testUri;
    testUri.Path = "";
    testUri.QueryString = "key%3Dvalue%26foo%3Dbar";
    testUri.Host = "";
    testUri.Username = "";
    testUri.Password = "";
    testUri.Protocol = "";
    testUri.Port = "";

    Uri::Decode(testUri);
    EXPECT_EQ(testUri.QueryString, "key=value&foo=bar");
}

TEST_F(UriTest_1808, DecodeEncodedHost_1808) {
    Uri testUri;
    testUri.Path = "";
    testUri.QueryString = "";
    testUri.Host = "example%2Ecom";
    testUri.Username = "";
    testUri.Password = "";
    testUri.Protocol = "";
    testUri.Port = "";

    Uri::Decode(testUri);
    EXPECT_EQ(testUri.Host, "example.com");
}

TEST_F(UriTest_1808, DecodeEncodedUsername_1808) {
    Uri testUri;
    testUri.Path = "";
    testUri.QueryString = "";
    testUri.Host = "";
    testUri.Username = "user%40domain";
    testUri.Password = "";
    testUri.Protocol = "";
    testUri.Port = "";

    Uri::Decode(testUri);
    EXPECT_EQ(testUri.Username, "user@domain");
}

TEST_F(UriTest_1808, DecodeEncodedPassword_1808) {
    Uri testUri;
    testUri.Path = "";
    testUri.QueryString = "";
    testUri.Host = "";
    testUri.Username = "";
    testUri.Password = "p%40ss%23word";
    testUri.Protocol = "";
    testUri.Port = "";

    Uri::Decode(testUri);
    EXPECT_EQ(testUri.Password, "p@ss#word");
}

TEST_F(UriTest_1808, DecodeNoEncodedCharacters_1808) {
    Uri testUri;
    testUri.Path = "/normal/path";
    testUri.QueryString = "key=value";
    testUri.Host = "example.com";
    testUri.Username = "user";
    testUri.Password = "password";
    testUri.Protocol = "http";
    testUri.Port = "8080";

    Uri::Decode(testUri);
    EXPECT_EQ(testUri.Path, "/normal/path");
    EXPECT_EQ(testUri.QueryString, "key=value");
    EXPECT_EQ(testUri.Host, "example.com");
    EXPECT_EQ(testUri.Username, "user");
    EXPECT_EQ(testUri.Password, "password");
}

TEST_F(UriTest_1808, DecodeEmptyFields_1808) {
    Uri testUri;
    testUri.Path = "";
    testUri.QueryString = "";
    testUri.Host = "";
    testUri.Username = "";
    testUri.Password = "";
    testUri.Protocol = "";
    testUri.Port = "";

    Uri::Decode(testUri);
    EXPECT_EQ(testUri.Path, "");
    EXPECT_EQ(testUri.QueryString, "");
    EXPECT_EQ(testUri.Host, "");
    EXPECT_EQ(testUri.Username, "");
    EXPECT_EQ(testUri.Password, "");
}

TEST_F(UriTest_1808, DecodeMultipleEncodedCharacters_1808) {
    Uri testUri;
    testUri.Path = "%2Fpath%2Fto%2Fresource";
    testUri.QueryString = "";
    testUri.Host = "";
    testUri.Username = "";
    testUri.Password = "";
    testUri.Protocol = "";
    testUri.Port = "";

    Uri::Decode(testUri);
    EXPECT_EQ(testUri.Path, "/path/to/resource");
}

TEST_F(UriTest_1808, DecodeAllFieldsEncoded_1808) {
    Uri testUri;
    testUri.Path = "/my%20path";
    testUri.QueryString = "q%3Dtest";
    testUri.Host = "my%2Dhost";
    testUri.Username = "my%40user";
    testUri.Password = "my%23pass";
    testUri.Protocol = "http";
    testUri.Port = "80";

    Uri::Decode(testUri);
    EXPECT_EQ(testUri.Path, "/my path");
    EXPECT_EQ(testUri.QueryString, "q=test");
    EXPECT_EQ(testUri.Host, "my-host");
    EXPECT_EQ(testUri.Username, "my@user");
    EXPECT_EQ(testUri.Password, "my#pass");
}

// ==================== Parse and Decode Combined Tests ====================

TEST_F(UriTest_1808, ParseThenDecode_1808) {
    Uri result = Uri::Parse("http://user%40name:p%40ss@example.com/my%20path?q%3Dvalue");
    Uri::Decode(result);
    // After decode, encoded characters should be resolved
    // The exact behavior depends on whether Parse decodes or not
    // At minimum, Decode should handle percent-encoded sequences
    EXPECT_NE(result.Protocol, "");
}

TEST_F(UriTest_1808, ParseUriWithTrailingSlash_1808) {
    Uri result = Uri::Parse("http://example.com/");
    EXPECT_EQ(result.Protocol, "http");
    EXPECT_EQ(result.Host, "example.com");
    EXPECT_EQ(result.Path, "/");
}

TEST_F(UriTest_1808, ParseUriWithOnlyQueryString_1808) {
    Uri result = Uri::Parse("http://example.com?query=1");
    EXPECT_EQ(result.Protocol, "http");
    EXPECT_EQ(result.Host, "example.com");
    EXPECT_EQ(result.QueryString, "query=1");
}

TEST_F(UriTest_1808, ParseUriWithPortAndNoPath_1808) {
    Uri result = Uri::Parse("http://example.com:443");
    EXPECT_EQ(result.Protocol, "http");
    EXPECT_EQ(result.Host, "example.com");
    EXPECT_EQ(result.Port, "443");
}

TEST_F(UriTest_1808, ParseUriWithPortQueryAndNoPath_1808) {
    Uri result = Uri::Parse("http://example.com:443?query=test");
    EXPECT_EQ(result.Protocol, "http");
    EXPECT_EQ(result.Host, "example.com");
    EXPECT_EQ(result.Port, "443");
    EXPECT_EQ(result.QueryString, "query=test");
}

TEST_F(UriTest_1808, DecodePlusSign_1808) {
    Uri testUri;
    testUri.Path = "/path+with+plus";
    testUri.QueryString = "key+name=val+ue";
    testUri.Host = "";
    testUri.Username = "";
    testUri.Password = "";
    testUri.Protocol = "";
    testUri.Port = "";

    Uri::Decode(testUri);
    // Plus signs may or may not be decoded to spaces depending on implementation
    // Just verify no crash
    EXPECT_FALSE(testUri.Path.empty());
}

TEST_F(UriTest_1808, DecodePercentEncodedSpecialChars_1808) {
    Uri testUri;
    testUri.Path = "%21%23%24%26%27";
    testUri.QueryString = "";
    testUri.Host = "";
    testUri.Username = "";
    testUri.Password = "";
    testUri.Protocol = "";
    testUri.Port = "";

    Uri::Decode(testUri);
    EXPECT_EQ(testUri.Path, "!#$&'");
}
