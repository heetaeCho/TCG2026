// -------------------------------------------------------------------------------------------------
// UNIT TESTS for Exiv2::ValueType<T>::ValueType(const byte*, size_t, ByteOrder, TypeId)
// TEST_ID = 2154
//
// File under test: exiv2/value.hpp
//
// Constraints note:
// - Treat implementation as a black box.
// - These tests validate only observable behavior through the public interface.
// - We avoid asserting exact parsing semantics; instead we compare constructor behavior
//   against an equivalent sequence using the public factory + read().
// -------------------------------------------------------------------------------------------------

#include <gtest/gtest.h>

#include <cstdint>
#include <cstring>
#include <memory>
#include <string>
#include <vector>

#include "exiv2/value.hpp"

namespace {

using Exiv2::ByteOrder;
using Exiv2::TypeId;
using Exiv2::Value;
using Exiv2::byte;

template <typename T>
static TypeId TypeForT() {
  // The header itself uses getType<T>() in ValueType<T>().
  // We rely only on this public mapping (no hardcoded TypeId enumerators).
  return Exiv2::getType<T>();
}

static std::vector<byte> MakeBytes(std::initializer_list<unsigned int> xs) {
  std::vector<byte> out;
  out.reserve(xs.size());
  for (auto v : xs) out.push_back(static_cast<byte>(v & 0xFFu));
  return out;
}

static std::vector<byte> CopyOut(Value& v, ByteOrder bo) {
  const size_t n = v.size();
  std::vector<byte> buf(n, 0);
  const size_t wrote = v.copy(buf.data(), bo);
  buf.resize(wrote);
  return buf;
}

class ValueTypeCtorBufTest_2154 : public ::testing::Test {};

TEST_F(ValueTypeCtorBufTest_2154, ConstructorSetsTypeIdToProvided_2154) {
  const auto bytes = MakeBytes({0x01, 0x00, 0x02, 0x00});
  const ByteOrder bo = Exiv2::littleEndian;

  const TypeId provided = TypeForT<std::uint16_t>();
  Exiv2::ValueType<std::uint16_t> v(bytes.data(), bytes.size(), bo, provided);

  EXPECT_EQ(v.typeId(), provided);
}

TEST_F(ValueTypeCtorBufTest_2154, ConstructorParsingMatchesFactoryThenRead_2154) {
  const auto bytes = MakeBytes({0x01, 0x00, 0x02, 0x00, 0x03, 0x00});
  const ByteOrder bo = Exiv2::littleEndian;
  const TypeId typeId = TypeForT<std::uint16_t>();

  // Path A: parse via constructor-under-test.
  Exiv2::ValueType<std::uint16_t> viaCtor(bytes.data(), bytes.size(), bo, typeId);

  // Path B: create via public factory then parse via public read().
  Value::UniquePtr viaFactory = Value::create(typeId);
  ASSERT_NE(viaFactory.get(), nullptr);
  (void)viaFactory->read(bytes.data(), bytes.size(), bo);

  // Observable equivalence checks (black-box): typeId, ok(), size/count, string, and copy().
  EXPECT_EQ(viaCtor.typeId(), viaFactory->typeId());
  EXPECT_EQ(viaCtor.ok(), viaFactory->ok());
  EXPECT_EQ(viaCtor.count(), viaFactory->count());
  EXPECT_EQ(viaCtor.size(), viaFactory->size());
  EXPECT_EQ(viaCtor.toString(), viaFactory->toString());

  const auto a = CopyOut(viaCtor, bo);
  const auto b = CopyOut(*viaFactory, bo);
  EXPECT_EQ(a, b);
}

TEST_F(ValueTypeCtorBufTest_2154, ZeroLengthBufferDoesNotCrashAndMatchesFactoryThenRead_2154) {
  const ByteOrder bo = Exiv2::littleEndian;
  const TypeId typeId = TypeForT<std::uint16_t>();

  // Using nullptr with len==0 should be safe for a well-behaved reader; this test asserts
  // only consistency with the public factory+read path (not a particular ok()/count()).
  Exiv2::ValueType<std::uint16_t> viaCtor(nullptr, 0, bo, typeId);

  Value::UniquePtr viaFactory = Value::create(typeId);
  ASSERT_NE(viaFactory.get(), nullptr);
  (void)viaFactory->read(nullptr, 0, bo);

  EXPECT_EQ(viaCtor.typeId(), viaFactory->typeId());
  EXPECT_EQ(viaCtor.ok(), viaFactory->ok());
  EXPECT_EQ(viaCtor.count(), viaFactory->count());
  EXPECT_EQ(viaCtor.size(), viaFactory->size());
  EXPECT_EQ(viaCtor.toString(), viaFactory->toString());

  const auto a = CopyOut(viaCtor, bo);
  const auto b = CopyOut(*viaFactory, bo);
  EXPECT_EQ(a, b);
}

TEST_F(ValueTypeCtorBufTest_2154, OddSizedBufferMatchesFactoryThenRead_2154) {
  // For uint16_t values, an odd byte count is a boundary condition.
  // We do NOT assume how Exiv2 handles this; we only require constructor behavior
  // matches the public factory+read behavior on the same input.
  const auto bytes = MakeBytes({0xAA, 0xBB, 0xCC});  // 3 bytes
  const ByteOrder bo = Exiv2::littleEndian;
  const TypeId typeId = TypeForT<std::uint16_t>();

  Exiv2::ValueType<std::uint16_t> viaCtor(bytes.data(), bytes.size(), bo, typeId);

  Value::UniquePtr viaFactory = Value::create(typeId);
  ASSERT_NE(viaFactory.get(), nullptr);
  (void)viaFactory->read(bytes.data(), bytes.size(), bo);

  EXPECT_EQ(viaCtor.ok(), viaFactory->ok());
  EXPECT_EQ(viaCtor.count(), viaFactory->count());
  EXPECT_EQ(viaCtor.size(), viaFactory->size());
  EXPECT_EQ(viaCtor.toString(), viaFactory->toString());

  const auto a = CopyOut(viaCtor, bo);
  const auto b = CopyOut(*viaFactory, bo);
  EXPECT_EQ(a, b);
}

TEST_F(ValueTypeCtorBufTest_2154, ProvidedTypeIdIsReflectedEvenIfDifferentFromTemplateT_2154) {
  // The constructor takes an explicit typeId; we only verify that the object reports
  // the provided typeId via the public accessor (no assumptions about parsing semantics).
  const auto bytes = MakeBytes({0x01, 0x00, 0x00, 0x00});
  const ByteOrder bo = Exiv2::littleEndian;

  const TypeId provided = TypeForT<std::uint32_t>();  // intentionally different from T=uint16_t
  Exiv2::ValueType<std::uint16_t> v(bytes.data(), bytes.size(), bo, provided);

  EXPECT_EQ(v.typeId(), provided);
}

}  // namespace