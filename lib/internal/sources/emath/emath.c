/*******************************************************************************
 * This internal C source file is part of the MIRAGE Game Engine and distributed
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

#include "../../../internal/types/types.h"

// // These functions return the minimum value between two values
// inline f32 emath_min_f32(f32 x, f32 y) {return x < y ? x : y;}
// inline f64 emath_min_f64(f64 x, f64 y) {return x < y ? x : y;}
// inline u8 emath_min_u8(u8 x, u8 y) {return x < y ? x : y;}
// inline u16 emath_min_u16(u16 x, u16 y) {return x < y ? x : y;}
// inline u32 emath_min_u32(u32 x, u32 y) {return x < y ? x : y;}
// inline u64 emath_min_u64(u64 x, u64 y) {return x < y ? x : y;}
// inline i8 emath_min_i8(i8 x, i8 y) {return x < y ? x : y;}
// inline i16 emath_min_i16(i16 x, i16 y) {return x < y ? x : y;}
// inline i32 emath_min_i32(i32 x, i32 y) {return x < y ? x : y;}
// inline i64 emath_min_i64(i64 x, i64 y) {return x < y ? x : y;}
// inline usize emath_min_usize(usize x, usize y) {return x < y ? x : y;}
// inline isize emath_min_isize(isize x, isize y) {return x < y ? x : y;}

// // These functions return the maximum value between two values
// inline f32 emath_max_f32(f32 x, f32 y) {return x > y ? x : y;}
// inline f64 emath_max_f64(f64 x, f64 y) {return x > y ? x : y;}
// inline u8 emath_max_u8(u8 x, u8 y) {return x > y ? x : y;}
// inline u16 emath_max_u16(u16 x, u16 y) {return x > y ? x : y;}
// inline u32 emath_max_u32(u32 x, u32 y) {return x > y ? x : y;}
// inline u64 emath_max_u64(u64 x, u64 y) {return x > y ? x : y;}
// inline i8 emath_max_i8(i8 x, i8 y) {return x > y ? x : y;}
// inline i16 emath_max_i16(i16 x, i16 y) {return x > y ? x : y;}
// inline i32 emath_max_i32(i32 x, i32 y) {return x > y ? x : y;}
// inline i64 emath_max_i64(i64 x, i64 y) {return x > y ? x : y;}
// inline usize emath_max_usize(usize x, usize y) {return x > y ? x : y;}
// inline isize emath_max_isize(isize x, isize y) {return x > y ? x : y;}

// These functions return the minimum value between two values
f32 emath_min_f32(f32 x, f32 y) {return x < y ? x : y;}
f64 emath_min_f64(f64 x, f64 y) {return x < y ? x : y;}
u8 emath_min_u8(u8 x, u8 y) {return x < y ? x : y;}
u16 emath_min_u16(u16 x, u16 y) {return x < y ? x : y;}
u32 emath_min_u32(u32 x, u32 y) {return x < y ? x : y;}
u64 emath_min_u64(u64 x, u64 y) {return x < y ? x : y;}
i8 emath_min_i8(i8 x, i8 y) {return x < y ? x : y;}
i16 emath_min_i16(i16 x, i16 y) {return x < y ? x : y;}
i32 emath_min_i32(i32 x, i32 y) {return x < y ? x : y;}
i64 emath_min_i64(i64 x, i64 y) {return x < y ? x : y;}
usize emath_min_usize(usize x, usize y) {return x < y ? x : y;}
isize emath_min_isize(isize x, isize y) {return x < y ? x : y;}

// These functions return the maximum value between two values
f32 emath_max_f32(f32 x, f32 y) {return x > y ? x : y;}
f64 emath_max_f64(f64 x, f64 y) {return x > y ? x : y;}
u8 emath_max_u8(u8 x, u8 y) {return x > y ? x : y;}
u16 emath_max_u16(u16 x, u16 y) {return x > y ? x : y;}
u32 emath_max_u32(u32 x, u32 y) {return x > y ? x : y;}
u64 emath_max_u64(u64 x, u64 y) {return x > y ? x : y;}
i8 emath_max_i8(i8 x, i8 y) {return x > y ? x : y;}
i16 emath_max_i16(i16 x, i16 y) {return x > y ? x : y;}
i32 emath_max_i32(i32 x, i32 y) {return x > y ? x : y;}
i64 emath_max_i64(i64 x, i64 y) {return x > y ? x : y;}
usize emath_max_usize(usize x, usize y) {return x > y ? x : y;}
isize emath_max_isize(isize x, isize y) {return x > y ? x : y;}

