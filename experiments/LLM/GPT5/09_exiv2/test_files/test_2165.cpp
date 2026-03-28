// SPDX-License-Identifier: GPL-2.0-or-later

#include <gtest/gtest.h>

#include <cstdint>
#include <cstring>
#include <iomanip>
#include <limits>
#include <ostream>
#include <sstream>
#include <string>
#include <vector>

#include "exiv2/value.hpp"
#include "exiv2/types.hpp"

namespace {

using Exiv2::byte;
using Exiv2::ByteOrder;
using Exiv2::DataValue;
using Exiv2::TypeId;

// Safely call copy() even if size() is 0.
static std::vector<byte> CopyOut(const Exiv2::Value& v, ByteOrder bo) {
  const size_t n = v.size();
  std::vector<byte> out(n);
  if (n == 0) return out;
  (void)v.copy(out.data(), bo);
  return out;
}

static std::string StreamWriteToString(Exiv2::Value& v) {
  std::ostringstream oss;
  v.write(oss);
  return oss.str();
}

// Compare two DataValue objects via only public/observable interface.
// This intentionally does NOT assume any semantic meaning of the bytes.
static void ExpectDataValueEquivalent(DataValue& a, DataValue& b, ByteOrder bo) {
  EXPECT_EQ(a.typeId(), b.typeId());
  EXPECT_EQ(a.ok(), b.ok());

  EXPECT_EQ(a.count(), b.count());
  EXPECT_EQ(a.size(), b.size());

  // String forms (both "whole" and n=0 element if supported).
  EXPECT_EQ(a.toString(), b.toString());
  EXPECT_EQ(a.toString(0), b.toString(0));

  // write(os)
  EXPECT_EQ(StreamWriteToString(a), StreamWriteToString(b));

  // Raw bytes copied out (if any)
  EXPECT_EQ(CopyOut(a, bo), CopyOut(b, bo));

  // Data area visibility (if used by implementation)
  EXPECT_EQ(a.sizeDataArea(), b.sizeDataArea());
  // dataArea() returns a DataBuf; compare by size and (if non-zero) bytes.
  const auto da = a.dataArea();
  const auto db = b.dataArea();
  EXPECT_EQ(da.size_, db.size_);
  if (da.size_ > 0 && da.pData_ != nullptr && db.pData_ != nullptr) {
    EXPECT_EQ(0, std::memcmp(da.pData_, db.pData_, da.size_));
  }
}

static std::vector<byte> MakeBytes(std::initializer_list<uint8_t> xs) {
  std::vector<byte> v;
  v.reserve(xs.size());
  for (auto x : xs) v.push_back(static_cast<byte>(x));
  return v;
}

}  // namespace

namespace Exiv2::test {

class DataValueTest_2165 : public ::testing::Test {};

TEST_F(DataValueTest_2165, CtorSetsTypeId_2165) {
  // Arrange
  const TypeId typeId = Exiv2::undefined;
  const ByteOrder bo = Exiv2::littleEndian;
  const std::vector<byte> buf = MakeBytes({0x00});

  // Act
  DataValue dv(buf.data(), buf.size(), bo, typeId);

  // Assert (observable through interface)
  EXPECT_EQ(dv.typeId(), typeId);
}

TEST_F(DataValueTest_2165, CtorIsEquivalentToDefaultCtorThenRead_2165) {
  // Arrange
  const TypeId typeId = Exiv2::undefined;
  const ByteOrder bo = Exiv2::littleEndian;
  const std::vector<byte> buf = MakeBytes({0x01, 0x02, 0x03, 0x04, 0xAA, 0x55});

  // Act
  DataValue ctorPath(buf.data(), buf.size(), bo, typeId);

  DataValue readPath(typeId);
  const int rc = readPath.read(buf.data(), buf.size(), bo);
  (void)rc;  // return code is observable; we just don't assume its meaning.

  // Assert
  ExpectDataValueEquivalent(ctorPath, readPath, bo);
}

TEST_F(DataValueTest_2165, CtorWithEmptyBufferDoesNotCrashAndMatchesRead_2165) {
  // Boundary: len == 0. We pass nullptr only when len==0.
  const TypeId typeId = Exiv2::undefined;
  const ByteOrder bo = Exiv2::littleEndian;

  DataValue ctorPath(nullptr, 0, bo, typeId);

  DataValue readPath(typeId);
  const int rc = readPath.read(nullptr, 0, bo);
  (void)rc;

  ExpectDataValueEquivalent(ctorPath, readPath, bo);
}

TEST_F(DataValueTest_2165, DifferentByteOrdersProduceSameAsExplicitReadForThatOrder_2165) {
  // We do NOT assert the two orders produce different results (that would infer semantics).
  // We only assert ctor-path equals read-path for each order.
  const TypeId typeId = Exiv2::undefined;
  const std::vector<byte> buf = MakeBytes({0x10, 0x20, 0x30, 0x40, 0xFE, 0xED, 0xBE, 0xEF});

  for (ByteOrder bo : {Exiv2::littleEndian, Exiv2::bigEndian}) {
    DataValue ctorPath(buf.data(), buf.size(), bo, typeId);

    DataValue readPath(typeId);
    const int rc = readPath.read(buf.data(), buf.size(), bo);
    (void)rc;

    ExpectDataValueEquivalent(ctorPath, readPath, bo);
  }
}

TEST_F(DataValueTest_2165, CtorWithLargeBufferMatchesRead_2165) {
  // Boundary-ish: larger input. Still black-box; we only compare ctor vs read.
  const TypeId typeId = Exiv2::undefined;
  const ByteOrder bo = Exiv2::littleEndian;

  std::vector<byte> buf(4096);
  for (size_t i = 0; i < buf.size(); ++i) {
    buf[i] = static_cast<byte>(i & 0xFF);
  }

  DataValue ctorPath(buf.data(), buf.size(), bo, typeId);

  DataValue readPath(typeId);
  const int rc = readPath.read(buf.data(), buf.size(), bo);
  (void)rc;

  ExpectDataValueEquivalent(ctorPath, readPath, bo);
}

TEST_F(DataValueTest_2165, CtorPropagatesObservableErrorStateSameAsRead_2165) {
  // Exceptional/error case (only if observable): feed a "possibly invalid" buffer and compare
  // constructor-path vs explicit read-path, including ok() and return codes.
  const TypeId typeId = Exiv2::undefined;
  const ByteOrder bo = Exiv2::littleEndian;

  // Intentionally odd buffer; we do not assume what is valid for the type.
  const std::vector<byte> buf = MakeBytes({0xFF, 0xFF, 0x00});

  DataValue ctorPath(buf.data(), buf.size(), bo, typeId);

  DataValue readPath(typeId);
  const int rcRead = readPath.read(buf.data(), buf.size(), bo);

  // We don't assert rcRead value, but we do ensure the states match.
  (void)rcRead;
  ExpectDataValueEquivalent(ctorPath, readPath, bo);
}

}  // namespace Exiv2::test