/*******************************************************************************
 * This internal C header file is part of the MIRAGE Game Engine and distributed
 * under the MIT License, any question or modification regarding this file
 * should be done on the official comunication channels, mainly on github.com.
 *
 * This file is concerned about the math logic of the game engine that are
 * not covered by standard C math library, like:
 *  - min and max
 *  - others
 * please be aware of the constant change of this engine internals as it's 
 * always evolving to be more error-prone and easy to use, so expect to have big
 * changes between releases.
 *                                                  - The MIRAGE Developer Team
*******************************************************************************/
#ifndef EMATH_H
#define EMATH_H

#include "../types/types.h"
#define GENERIC_MAX(x, y) ({\
    __auto_type __x = (x);\
    __auto_type __y = (y);\
    __x > __y ? __X : __y;})

#define GENERIC_MIN(x, y) ({\
    __auto_type __x = (x);\
    __auto_type __y = (y);\
    __x < __y ? __X : __y;})

// // These functions return the minimum value between two values
// extern inline f32 emath_min_f32(f32 x, f32 y);
// extern inline f64 emath_min_f64(f64 x, f64 y);
// extern inline u8 emath_min_u8(u8 x, u8 y);
// extern inline u16 emath_min_u16(u16 x, u16 y);
// extern inline u32 emath_min_u32(u32 x, u32 y);
// extern inline u64 emath_min_u64(u64 x, u64 y);
// extern inline i8 emath_min_i8(i8 x, i8 y);
// extern inline i16 emath_min_i16(i16 x, i16 y);
// extern inline i32 emath_min_i32(i32 x, i32 y);
// extern inline i64 emath_min_i64(i64 x, i64 y);
// extern inline usize emath_min_usize(usize x, usize y);
// extern inline isize emath_min_isize(isize x, isize y);

// // These functions return the maximum value between two values
// extern inline f32 emath_max_f32(f32 x, f32 y);
// extern inline f64 emath_max_f64(f64 x, f64 y);
// extern inline u8 emath_max_u8(u8 x, u8 y);
// extern inline u16 emath_max_u16(u16 x, u16 y);
// extern inline u32 emath_max_u32(u32 x, u32 y);
// extern inline u64 emath_max_u64(u64 x, u64 y);
// extern inline i8 emath_max_i8(i8 x, i8 y);
// extern inline i16 emath_max_i16(i16 x, i16 y);
// extern inline i32 emath_max_i32(i32 x, i32 y);
// extern inline i64 emath_max_i64(i64 x, i64 y);
// extern inline usize emath_max_usize(usize x, usize y);
// extern inline isize emath_max_isize(isize x, isize y);

// These functions return the minimum value between two values
f32 emath_min_f32(f32 x, f32 y);
f64 emath_min_f64(f64 x, f64 y);
u8 emath_min_u8(u8 x, u8 y);
u16 emath_min_u16(u16 x, u16 y);
u32 emath_min_u32(u32 x, u32 y);
u64 emath_min_u64(u64 x, u64 y);
i8 emath_min_i8(i8 x, i8 y);
i16 emath_min_i16(i16 x, i16 y);
i32 emath_min_i32(i32 x, i32 y);
i64 emath_min_i64(i64 x, i64 y);
usize emath_min_usize(usize x, usize y);
isize emath_min_isize(isize x, isize y);

// These functions return the maximum value between two values
f32 emath_max_f32(f32 x, f32 y);
f64 emath_max_f64(f64 x, f64 y);
u8 emath_max_u8(u8 x, u8 y);
u16 emath_max_u16(u16 x, u16 y);
u32 emath_max_u32(u32 x, u32 y);
u64 emath_max_u64(u64 x, u64 y);
i8 emath_max_i8(i8 x, i8 y);
i16 emath_max_i16(i16 x, i16 y);
i32 emath_max_i32(i32 x, i32 y);
i64 emath_max_i64(i64 x, i64 y);
usize emath_max_usize(usize x, usize y);
isize emath_max_isize(isize x, isize y);


#endif

