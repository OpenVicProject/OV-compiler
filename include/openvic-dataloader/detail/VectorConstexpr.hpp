#pragma once

// THANK YOU APPLE FOR YOUR UTTER DISREGARD FOR C++20

#if __cpp_lib_constexpr_vector >= 201907L
#define OVDL_VECTOR_CONSTEXPR constexpr
#else
#define OVDL_VECTOR_CONSTEXPR inline
#endif