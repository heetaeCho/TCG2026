#include <gtest/gtest.h>
#include <string>

// Replicate the Uri class based on the provided implementation
namespace Exiv2 {

class Uri {
 public:
  std::string QueryString;
  std::string Path;
  std::string Protocol;
  std::string Host;
  std::string Port;
  std::string Username;
  std::string Password;

  static Uri Parse(const std::string& uri) {
    Uri result;
    if (uri.empty())
      return result;

    auto uriEnd = uri.end();
    auto queryStart = std::find(uri.begin(), uriEnd, '?');
    auto protocolStart = uri.begin();
    auto protocolEnd = std::find(protocolStart, uriEnd, ':');

    if (protocolEnd != uriEnd) {
      auto prot = std::string(protocolEnd, uriEnd);
      if (prot.starts_with("://")) {
        result.Protocol = std::string(protocolStart, protocolEnd);
        protocolEnd += 3;
      } else
        protocolEnd = uri.begin();
    } else
      protocolEnd = uri.begin();

    auto authStart = protocolEnd;
    auto authEnd = std::find(protocolEnd, uriEnd, '@');
    if (authEnd != uriEnd) {
      auto userStart = authStart;
      if (auto userEnd = std::find(authStart, authEnd, ':'); userEnd != authEnd) {
        result.Username = std::string(userStart, userEnd);
        ++userEnd;
        result.Password = std::string(userEnd, authEnd);
      } else {
        result.Username = std::string(authStart, authEnd);
      }
      ++authEnd;
    } else {
      authEnd = protocolEnd;
    }

    auto hostStart = authEnd;
    auto pathStart = std::find(hostStart, uriEnd, '/');
    auto hostEnd = std::find(authEnd, (pathStart != uriEnd) ? pathStart : queryStart, ':');

    if (hostStart < hostEnd) {
      result.Host = std::string(hostStart, hostEnd);
    }

    if ((hostEnd != uriEnd) && (*hostEnd == ':')) {
      ++hostEnd;
      auto portEnd = (pathStart != uriEnd) ? pathStart : queryStart;
      if (hostEnd < portEnd) {
        result.Port = std::string(hostEnd, portEnd);
      }
    }

    if (result.Port.empty() && result.Protocol == "http")
      result.Port = "80";

    if (pathStart < queryStart) {
      result.Path = std::string(pathStart, queryStart);
    }

    if (queryStart != uriEnd)
      result.QueryString = std::string(queryStart, uri.end());

    return result;
  }
};

}  // namespace Exiv2

class UriParseTest_1809 : public ::testing::Test {
 protected:
  Exiv2::Uri uri;
};

// Test empty URI
TEST_F(UriParseTest_1809, EmptyUri_1809) {
  uri = Exiv2::Uri::Parse("");
  EXPECT_EQ(uri.Protocol, "");
  EXPECT_EQ(uri.Host, "");
  EXPECT_EQ(uri.Port, "");
  EXPECT_EQ(uri.Path, "");
  EXPECT_EQ(uri.QueryString, "");
  EXPECT_EQ(uri.Username, "");
  EXPECT_EQ(uri.Password, "");
}

// Test full HTTP URI with all components
TEST_F(UriParseTest_1809, FullHttpUri_1809) {
  uri = Exiv2::Uri::Parse("http://user:pass@example.com:8080/path/to/resource?key=value");
  EXPECT_EQ(uri.Protocol, "http");
  EXPECT_EQ(uri.Username, "user");
  EXPECT_EQ(uri.Password, "pass");
  EXPECT_EQ(uri.Host, "example.com");
  EXPECT_EQ(uri.Port, "8080");
  EXPECT_EQ(uri.Path, "/path/to/resource");
  EXPECT_EQ(uri.QueryString, "?key=value");
}

// Test simple HTTP URI without auth
TEST_F(UriParseTest_1809, SimpleHttpUri_1809) {
  uri = Exiv2::Uri::Parse("http://example.com/path");
  EXPECT_EQ(uri.Protocol, "http");
  EXPECT_EQ(uri.Host, "example.com");
  EXPECT_EQ(uri.Path, "/path");
  EXPECT_EQ(uri.Username, "");
  EXPECT_EQ(uri.Password, "");
}

// Test HTTP default port
TEST_F(UriParseTest_1809, HttpDefaultPort_1809) {
  uri = Exiv2::Uri::Parse("http://example.com/path");
  EXPECT_EQ(uri.Protocol, "http");
  EXPECT_EQ(uri.Port, "80");
}

// Test HTTPS URI (no default port for non-http)
TEST_F(UriParseTest_1809, HttpsUri_1809) {
  uri = Exiv2::Uri::Parse("https://example.com/path");
  EXPECT_EQ(uri.Protocol, "https");
  EXPECT_EQ(uri.Host, "example.com");
  EXPECT_EQ(uri.Path, "/path");
  // Port should be empty since protocol is not "http"
  EXPECT_EQ(uri.Port, "");
}

// Test URI with explicit port overrides http default
TEST_F(UriParseTest_1809, ExplicitPortOverridesDefault_1809) {
  uri = Exiv2::Uri::Parse("http://example.com:9090/path");
  EXPECT_EQ(uri.Port, "9090");
}

// Test URI with username only (no password)
TEST_F(UriParseTest_1809, UsernameOnlyNoPassword_1809) {
  uri = Exiv2::Uri::Parse("http://user@example.com/path");
  EXPECT_EQ(uri.Username, "user");
  EXPECT_EQ(uri.Password, "");
  EXPECT_EQ(uri.Host, "example.com");
}

// Test URI with username and password
TEST_F(UriParseTest_1809, UsernameAndPassword_1809) {
  uri = Exiv2::Uri::Parse("http://user:password@example.com/path");
  EXPECT_EQ(uri.Username, "user");
  EXPECT_EQ(uri.Password, "password");
  EXPECT_EQ(uri.Host, "example.com");
}

// Test URI with query string only (no path)
TEST_F(UriParseTest_1809, QueryStringNoPath_1809) {
  uri = Exiv2::Uri::Parse("http://example.com?query=1");
  EXPECT_EQ(uri.Protocol, "http");
  EXPECT_EQ(uri.Host, "example.com");
  EXPECT_EQ(uri.QueryString, "?query=1");
  EXPECT_EQ(uri.Path, "");
}

// Test URI with no protocol
TEST_F(UriParseTest_1809, NoProtocol_1809) {
  uri = Exiv2::Uri::Parse("example.com/path");
  EXPECT_EQ(uri.Protocol, "");
  EXPECT_EQ(uri.Host, "example.com");
  EXPECT_EQ(uri.Path, "/path");
}

// Test URI with path only
TEST_F(UriParseTest_1809, PathOnly_1809) {
  uri = Exiv2::Uri::Parse("/path/to/file");
  EXPECT_EQ(uri.Protocol, "");
  EXPECT_EQ(uri.Host, "");
  EXPECT_EQ(uri.Path, "/path/to/file");
}

// Test URI with query string and path
TEST_F(UriParseTest_1809, PathAndQueryString_1809) {
  uri = Exiv2::Uri::Parse("http://example.com/path?key=value&other=123");
  EXPECT_EQ(uri.Path, "/path");
  EXPECT_EQ(uri.QueryString, "?key=value&other=123");
}

// Test URI host without path
TEST_F(UriParseTest_1809, HostOnly_1809) {
  uri = Exiv2::Uri::Parse("http://example.com");
  EXPECT_EQ(uri.Protocol, "http");
  EXPECT_EQ(uri.Host, "example.com");
  EXPECT_EQ(uri.Port, "80");
  EXPECT_EQ(uri.Path, "");
}

// Test URI with port but no path
TEST_F(UriParseTest_1809, PortNoPath_1809) {
  uri = Exiv2::Uri::Parse("http://example.com:8080");
  EXPECT_EQ(uri.Host, "example.com");
  EXPECT_EQ(uri.Port, "8080");
  EXPECT_EQ(uri.Path, "");
}

// Test FTP protocol
TEST_F(UriParseTest_1809, FtpProtocol_1809) {
  uri = Exiv2::Uri::Parse("ftp://files.example.com/pub/file.txt");
  EXPECT_EQ(uri.Protocol, "ftp");
  EXPECT_EQ(uri.Host, "files.example.com");
  EXPECT_EQ(uri.Path, "/pub/file.txt");
  EXPECT_EQ(uri.Port, "");
}

// Test URI with trailing slash
TEST_F(UriParseTest_1809, TrailingSlash_1809) {
  uri = Exiv2::Uri::Parse("http://example.com/");
  EXPECT_EQ(uri.Host, "example.com");
  EXPECT_EQ(uri.Path, "/");
  EXPECT_EQ(uri.Port, "80");
}

// Test URI with multiple path segments
TEST_F(UriParseTest_1809, MultiplePathSegments_1809) {
  uri = Exiv2::Uri::Parse("http://example.com/a/b/c/d");
  EXPECT_EQ(uri.Path, "/a/b/c/d");
}

// Test URI with empty password (colon present but no password)
TEST_F(UriParseTest_1809, EmptyPassword_1809) {
  uri = Exiv2::Uri::Parse("http://user:@example.com/path");
  EXPECT_EQ(uri.Username, "user");
  EXPECT_EQ(uri.Password, "");
  EXPECT_EQ(uri.Host, "example.com");
}

// Test complex query string
TEST_F(UriParseTest_1809, ComplexQueryString_1809) {
  uri = Exiv2::Uri::Parse("http://example.com/path?a=1&b=2&c=3");
  EXPECT_EQ(uri.QueryString, "?a=1&b=2&c=3");
}

// Test URI with colon in path but no protocol
TEST_F(UriParseTest_1809, ColonInPathNoProtocol_1809) {
  uri = Exiv2::Uri::Parse("example.com:8080/path");
  // "example.com" has colon but no "://" so protocol should be empty
  EXPECT_EQ(uri.Protocol, "");
}

// Test just a hostname (no protocol, no path)
TEST_F(UriParseTest_1809, JustHostname_1809) {
  uri = Exiv2::Uri::Parse("example.com");
  EXPECT_EQ(uri.Protocol, "");
  EXPECT_EQ(uri.Host, "example.com");
  EXPECT_EQ(uri.Path, "");
}

// Test URI with port, auth, path, and query
TEST_F(UriParseTest_1809, AllComponents_1809) {
  uri = Exiv2::Uri::Parse("https://admin:secret@myhost.com:443/api/v1?token=abc");
  EXPECT_EQ(uri.Protocol, "https");
  EXPECT_EQ(uri.Username, "admin");
  EXPECT_EQ(uri.Password, "secret");
  EXPECT_EQ(uri.Host, "myhost.com");
  EXPECT_EQ(uri.Port, "443");
  EXPECT_EQ(uri.Path, "/api/v1");
  EXPECT_EQ(uri.QueryString, "?token=abc");
}

// Test URI with @ in query string but no auth
TEST_F(UriParseTest_1809, AtSignInUri_1809) {
  uri = Exiv2::Uri::Parse("http://user@example.com");
  EXPECT_EQ(uri.Username, "user");
  EXPECT_EQ(uri.Host, "example.com");
  EXPECT_EQ(uri.Port, "80");
}

// Test URI with only protocol
TEST_F(UriParseTest_1809, OnlyProtocol_1809) {
  uri = Exiv2::Uri::Parse("http://");
  EXPECT_EQ(uri.Protocol, "http");
  EXPECT_EQ(uri.Host, "");
  EXPECT_EQ(uri.Port, "80");
}

// Test port with query string no path
TEST_F(UriParseTest_1809, PortQueryNoPath_1809) {
  uri = Exiv2::Uri::Parse("http://example.com:3000?q=test");
  EXPECT_EQ(uri.Host, "example.com");
  EXPECT_EQ(uri.Port, "3000");
  EXPECT_EQ(uri.QueryString, "?q=test");
  EXPECT_EQ(uri.Path, "");
}

// Test URI with numeric host (IP address)
TEST_F(UriParseTest_1809, IpAddressHost_1809) {
  uri = Exiv2::Uri::Parse("http://192.168.1.1:8080/resource");
  EXPECT_EQ(uri.Protocol, "http");
  EXPECT_EQ(uri.Host, "192.168.1.1");
  EXPECT_EQ(uri.Port, "8080");
  EXPECT_EQ(uri.Path, "/resource");
}

// Test URI with only a slash
TEST_F(UriParseTest_1809, OnlySlash_1809) {
  uri = Exiv2::Uri::Parse("/");
  EXPECT_EQ(uri.Protocol, "");
  EXPECT_EQ(uri.Host, "");
  EXPECT_EQ(uri.Path, "/");
}

// Test URI with only a question mark
TEST_F(UriParseTest_1809, OnlyQuestionMark_1809) {
  uri = Exiv2::Uri::Parse("?");
  EXPECT_EQ(uri.QueryString, "?");
  EXPECT_EQ(uri.Path, "");
  EXPECT_EQ(uri.Host, "");
}

// Test single character URI
TEST_F(UriParseTest_1809, SingleCharacter_1809) {
  uri = Exiv2::Uri::Parse("a");
  EXPECT_EQ(uri.Protocol, "");
  EXPECT_EQ(uri.Host, "a");
  EXPECT_EQ(uri.Path, "");
}

// Test that http without explicit port gets 80, but with explicit port keeps it
TEST_F(UriParseTest_1809, HttpPortBehavior_1809) {
  auto uri1 = Exiv2::Uri::Parse("http://host.com");
  EXPECT_EQ(uri1.Port, "80");

  auto uri2 = Exiv2::Uri::Parse("http://host.com:1234");
  EXPECT_EQ(uri2.Port, "1234");

  auto uri3 = Exiv2::Uri::Parse("https://host.com");
  EXPECT_EQ(uri3.Port, "");
}

// Test URI with deep nested path
TEST_F(UriParseTest_1809, DeepNestedPath_1809) {
  uri = Exiv2::Uri::Parse("http://example.com/a/b/c/d/e/f/g");
  EXPECT_EQ(uri.Path, "/a/b/c/d/e/f/g");
}

// Test auth with special characters in password
TEST_F(UriParseTest_1809, SpecialCharsInPassword_1809) {
  uri = Exiv2::Uri::Parse("http://user:p%40ssw0rd@example.com/path");
  EXPECT_EQ(uri.Username, "user");
  EXPECT_EQ(uri.Password, "p%40ssw0rd");
  EXPECT_EQ(uri.Host, "example.com");
}
