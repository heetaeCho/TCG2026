// File: test/emittermanip_alias_test.cpp
#include <gtest/gtest.h>

#include <string>
#include <type_traits>
#include <utility>

#include "yaml-cpp/emitter.h"
#include "yaml-cpp/emittermanip.h"

namespace {

std::string EmitToString(const YAML::_Alias& a) {
  YAML::Emitter out;
  out << a;
  return std::string(out.c_str());
}

}  // namespace

TEST(EmitterManipAliasTest_13, ReturnsAliasType_13) {
  auto a = YAML::Alias("foo");
  EXPECT_TRUE((std::is_same<decltype(a), YAML::_Alias>::value));
}

TEST(EmitterManipAliasTest_13, EmitsSameAsDirectConstruction_13) {
  const std::string content = "foo";

  const auto via_func = YAML::Alias(content);
  const YAML::_Alias via_ctor(content);

  EXPECT_EQ(EmitToString(via_func), EmitToString(via_ctor));
}

TEST(EmitterManipAliasTest_13, EmptyStringContent_13) {
  const std::string content;

  const auto via_func = YAML::Alias(content);
  const YAML::_Alias via_ctor(content);

  EXPECT_EQ(EmitToString(via_func), EmitToString(via_ctor));
}

TEST(EmitterManipAliasTest_13, SpecialCharactersContent_13) {
  const std::string content = "a b: c\t#[]{}";

  const auto via_func = YAML::Alias(content);
  const YAML::_Alias via_ctor(content);

  EXPECT_EQ(EmitToString(via_func), EmitToString(via_ctor));
}

TEST(EmitterManipAliasTest_13, CopyAndMovePreserveEmission_13) {
  const std::string content = "copy-move";

  const auto original = YAML::Alias(content);
  const auto copied = original;
  auto moved = YAML::Alias(content);
  auto moved_from = std::move(moved);

  const YAML::_Alias via_ctor(content);

  EXPECT_EQ(EmitToString(original), EmitToString(via_ctor));
  EXPECT_EQ(EmitToString(copied), EmitToString(via_ctor));
  EXPECT_EQ(EmitToString(moved_from), EmitToString(via_ctor));
}
