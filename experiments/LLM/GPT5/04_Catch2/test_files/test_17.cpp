// File: tests/xmlwriter_scopedelement_writeAttribute_sfinae_17.cpp

#include <gtest/gtest.h>
#include <type_traits>
#include <string>

// Use the real interfaces from your codebase.
#include "catch2/internal/catch_xmlwriter.hpp"
#include "catch2/internal/catch_stringref.hpp"

namespace {

using Catch::StringRef;
using Catch::XmlWriter;

using SE = XmlWriter::ScopedElement;

// Helper aliases to shorten is_invocable checks
template <typename T>
using IsInvocableAttr =
    std::is_invocable<decltype(&SE::writeAttribute), SE&, StringRef, const T&>;

template <typename T>
constexpr bool IsAttrInvocableV = IsInvocableAttr<T>::value;

// ---- TESTS ----

TEST(XmlWriterScopedElement_SFINAE_17, InvocableWithInt_17) {
  // int is NOT convertible to StringRef -> templated overload should be enabled.
  static_assert(!std::is_convertible<int, StringRef>::value, "sanity check");
  static_assert(IsAttrInvocableV<int>, "writeAttribute(name, int) must be invocable");
  SUCCEED(); // compile-time assertion is the core check
}

TEST(XmlWriterScopedElement_SFINAE_17, InvocableWithDouble_17) {
  // double is NOT convertible to StringRef -> templated overload should be enabled.
  static_assert(!std::is_convertible<double, StringRef>::value, "sanity check");
  static_assert(IsAttrInvocableV<double>, "writeAttribute(name, double) must be invocable");
  SUCCEED();
}

TEST(XmlWriterScopedElement_SFINAE_17, InvocableWithCString_17) {
  // const char* IS convertible to StringRef -> templated overload must be SFINAE-excluded,
  // but the non-template (StringRef, StringRef) keeps the call valid.
  static_assert(std::is_convertible<const char*, StringRef>::value, "sanity check");
  static_assert(IsAttrInvocableV<const char*>,
                "writeAttribute(name, const char*) must be invocable via the non-template overload");
  SUCCEED();
}

TEST(XmlWriterScopedElement_SFINAE_17, InvocableWithStdString_17) {
  // std::string IS convertible to StringRef (via StringRef(std::string const&)).
  // Templated overload excluded; non-template overload keeps the call valid.
  static_assert(std::is_convertible<const std::string&, StringRef>::value, "sanity check");
  static_assert(IsAttrInvocableV<std::string>,
                "writeAttribute(name, std::string) must be invocable via the non-template overload");
  SUCCEED();
}

TEST(XmlWriterScopedElement_SFINAE_17, NotInvocableWithWrongArity_17) {
  // Ensure obviously incorrect arity is rejected.
  static_assert(
      !std::is_invocable<decltype(&SE::writeAttribute), SE&, StringRef>::value,
      "writeAttribute must require 2 arguments (name, attribute)");
  SUCCEED();
}

// (Optional) Demonstrate that the exact non-template overload (StringRef, StringRef) exists.
TEST(XmlWriterScopedElement_SFINAE_17, HasStringRefStringRefOverload_17) {
  using NonTemplatePtr =
      SE& (SE::*)(StringRef, StringRef);
  // This static_cast must succeed if the non-template overload exists.
  NonTemplatePtr p = static_cast<NonTemplatePtr>(&SE::writeAttribute);
  (void)p;
  SUCCEED();
}

} // namespace
