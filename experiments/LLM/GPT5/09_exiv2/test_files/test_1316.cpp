// ***************************************************************** -*- C++ -*-
/*
 * Unit tests for Exiv2::XmpParser::terminate()
 * File: ./TestProjects/exiv2/src/xmp.cpp (interface from exiv2/xmp_exiv2.hpp)
 *
 * Constraints respected:
 *  - Treat implementation as black box (no private state access).
 *  - Verify observable behavior via public APIs (XmpProperties registry).
 *  - No mocking of internal behavior.
 */
// *****************************************************************

#include <gtest/gtest.h>

#include <exiv2/properties.hpp>
#include <exiv2/xmp_exiv2.hpp>

#include <string>

namespace {

using Exiv2::XmpParser;
using Exiv2::XmpProperties;

// Helper that attempts to determine if a prefix is registered by using only public APIs.
// We assume that an unknown prefix results in an empty namespace URI (common pattern),
// but we keep this helper narrow and only used for test assertions below.
bool isPrefixRegistered(const std::string& prefix) {
  std::string ns;
  EXPECT_NO_THROW(ns = XmpProperties::ns(prefix));
  return !ns.empty();
}

bool isNamespaceRegistered(const std::string& nsUri) {
  std::string prefix;
  EXPECT_NO_THROW(prefix = XmpProperties::prefix(nsUri));
  return !prefix.empty();
}

class XmpParserTerminateTest_1316 : public ::testing::Test {
 protected:
  void TearDown() override {
    // Ensure we leave global registry in a clean state for other tests.
    // (terminate() is expected to clear the registry; calling it here is safe/idempotent.)
    XmpParser parser;
    EXPECT_NO_THROW(parser.terminate());
    // Also exercise the static form if present/linked.
    EXPECT_NO_THROW(XmpParser::terminate());
  }
};

}  // namespace

TEST_F(XmpParserTerminateTest_1316, TerminateClearsRegisteredNamespaces_1316) {
  const std::string nsUri = "http://example.com/exiv2/test/terminate/1316/";
  const std::string prefix = "t1316";

  // Register a namespace via the public API and verify it is observable.
  ASSERT_NO_THROW(XmpProperties::registerNs(nsUri, prefix));

  // Observable checks (no reliance on internal storage details).
  {
    std::string observedNs;
    std::string observedPrefix;
    ASSERT_NO_THROW(observedNs = XmpProperties::ns(prefix));
    ASSERT_NO_THROW(observedPrefix = XmpProperties::prefix(nsUri));

    EXPECT_FALSE(observedNs.empty());
    EXPECT_FALSE(observedPrefix.empty());
    EXPECT_EQ(observedNs, nsUri);
    EXPECT_EQ(observedPrefix, prefix);
    EXPECT_TRUE(isPrefixRegistered(prefix));
    EXPECT_TRUE(isNamespaceRegistered(nsUri));
  }

  // Call the API under test.
  XmpParser parser;
  ASSERT_NO_THROW(parser.terminate());

  // After terminate(), the namespace registry should be cleared/unregistered.
  {
    std::string afterNs;
    std::string afterPrefix;
    ASSERT_NO_THROW(afterNs = XmpProperties::ns(prefix));
    ASSERT_NO_THROW(afterPrefix = XmpProperties::prefix(nsUri));

    EXPECT_TRUE(afterNs.empty());
    EXPECT_TRUE(afterPrefix.empty());
    EXPECT_FALSE(isPrefixRegistered(prefix));
    EXPECT_FALSE(isNamespaceRegistered(nsUri));
  }
}

TEST_F(XmpParserTerminateTest_1316, TerminateIsIdempotent_1316) {
  const std::string nsUri = "http://example.com/exiv2/test/terminate/idempotent/1316/";
  const std::string prefix = "t1316i";

  ASSERT_NO_THROW(XmpProperties::registerNs(nsUri, prefix));
  EXPECT_TRUE(isPrefixRegistered(prefix));
  EXPECT_TRUE(isNamespaceRegistered(nsUri));

  XmpParser parser;
  ASSERT_NO_THROW(parser.terminate());

  // Second call should not crash/throw (boundary/idempotence behavior).
  EXPECT_NO_THROW(parser.terminate());

  // Registry remains cleared.
  std::string afterNs;
  std::string afterPrefix;
  ASSERT_NO_THROW(afterNs = XmpProperties::ns(prefix));
  ASSERT_NO_THROW(afterPrefix = XmpProperties::prefix(nsUri));
  EXPECT_TRUE(afterNs.empty());
  EXPECT_TRUE(afterPrefix.empty());
}

TEST_F(XmpParserTerminateTest_1316, TerminateWithNoPriorRegistrationDoesNotThrow_1316) {
  // Boundary: terminating when there may be no custom registrations.
  XmpParser parser;
  EXPECT_NO_THROW(parser.terminate());

  // Also cover the static terminate() interface as declared in the header.
  EXPECT_NO_THROW(XmpParser::terminate());
}

TEST_F(XmpParserTerminateTest_1316, StaticTerminateClearsRegistry_1316) {
  const std::string nsUri = "http://example.com/exiv2/test/terminate/static/1316/";
  const std::string prefix = "t1316s";

  ASSERT_NO_THROW(XmpProperties::registerNs(nsUri, prefix));

  std::string observedNs;
  ASSERT_NO_THROW(observedNs = XmpProperties::ns(prefix));
  ASSERT_EQ(observedNs, nsUri);

  // Call static terminate() (declared in exiv2/xmp_exiv2.hpp).
  ASSERT_NO_THROW(XmpParser::terminate());

  std::string afterNs;
  std::string afterPrefix;
  ASSERT_NO_THROW(afterNs = XmpProperties::ns(prefix));
  ASSERT_NO_THROW(afterPrefix = XmpProperties::prefix(nsUri));
  EXPECT_TRUE(afterNs.empty());
  EXPECT_TRUE(afterPrefix.empty());
}