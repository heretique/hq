#pragma once

//#include <cinttypes>
#include <cstddef>
#include <cstdint>

// Types
using uint = unsigned int;

using i8  = int8_t;
using i16 = int16_t;
using i32 = int32_t;
using i64 = int64_t;
using u8  = uint8_t;
using u16 = uint16_t;
using u32 = uint32_t;
using u64 = uint64_t;

using uptr = uintptr_t;

#define SERIALIZE(x) serializer(x, #x)

// https://foonathan.net/2020/09/move-forward/
// Move replacement for std::move, like Type obj = MOVE(other_obj);
#define MOVE(...) static_cast<std::remove_reference_t<decltype(__VA_ARGS__)>&&>(__VA_ARGS__)

// Forward, use like  fn(FWD(args)...);
#define FWD(...) static_cast<decltype(__VA_ARGS__) &&>(__VA_ARGS__)
