// SPDX-License-Identifier: GPL-2.0-or-later
// File: test_xmpkey_impl_ctor_2177.cpp

#include <gtest/gtest.h>

#include <string>

#include "exiv2/error.hpp"
#include "exiv2/properties.hpp"

namespace {

class XmpKeyImplTest_2177 : public ::testing::Test {
 protected:
  static constexpr const char* kNsUri = "http://example.com/ns/2177/";
  static constexpr const char* kPrefix = "t2177";

  void TearDown() override {
    // Best-effort cleanup in case a test registered a namespace.
    // (If not registered, Exiv2 may ignore or throw; we avoid depending on that.)
    try {
      Exiv2::XmpProperties::unregisterNs(std::string(kNsUri));
    } catch (...) {
    }
  }
};

TEST_F(XmpKeyImplTest_2177, ThrowsWhenNoNamespaceForPrefix_2177) {
  const std::string unknownPrefix = "definitely_not_registered_2177";
  const std::string property = "SomeProperty";

  EXPECT_THROW((Exiv2::XmpKey::Impl(unknownPrefix, property)), Exiv2::Error);
}

TEST_F(XmpKeyImplTest_2177, ThrowsWhenPrefixIsEmpty_2177) {
  const std::string emptyPrefix;
  const std::string property = "SomeProperty";

  EXPECT_THROW((Exiv2::XmpKey::Impl(emptyPrefix, property)), Exiv2::Error);
}

TEST_F(XmpKeyImplTest_2177, DoesNotThrowWhenNamespaceIsRegistered_2177) {
  Exiv2::XmpProperties::registerNs(std::string(kNsUri), std::string(kPrefix));

  EXPECT_NO_THROW({
    Exiv2::XmpKey::Impl impl(std::string(kPrefix), std::string("MyProperty"));
    EXPECT_EQ(impl.property_, "MyProperty");
  });
}

TEST_F(XmpKeyImplTest_2177, AllowsEmptyPropertyWhenNamespaceIsRegistered_2177) {
  Exiv2::XmpProperties::registerNs(std::string(kNsUri), std::string(kPrefix));

  EXPECT_NO_THROW({
    Exiv2::XmpKey::Impl impl(std::string(kPrefix), std::string());
    EXPECT_TRUE(impl.property_.empty());
  });
}

TEST_F(XmpKeyImplTest_2177, ThrowsAgainAfterNamespaceIsUnregistered_2177) {
  Exiv2::XmpProperties::registerNs(std::string(kNsUri), std::string(kPrefix));

  // Sanity: should succeed while registered.
  EXPECT_NO_THROW((Exiv2::XmpKey::Impl(std::string(kPrefix), std::string("P"))));

  // After unregistering, the constructor should become invalid again for that prefix.
  Exiv2::XmpProperties::unregisterNs(std::string(kNsUri));

  EXPECT_THROW((Exiv2::XmpKey::Impl(std::string(kPrefix), std::string("P"))), Exiv2::Error);
}

}  // namespace