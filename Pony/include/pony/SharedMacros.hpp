/*
 * Copyright (C) 2017 by Godlike
 * This code is licensed under the MIT license (MIT) (http://opensource.org/licenses/MIT)
 */

#ifndef PONY_SHARED_MACROS_HPP
#define PONY_SHARED_MACROS_HPP

/**
 *  @brief CMake will define Pony_EXPORTS when building the library.
 */

#if defined(_WIN32) && defined(PONY_SHARED)
#ifdef Pony_EXPORTS
#define PONY_EXPORT __declspec(dllexport)
#else
#define PONY_EXPORT __declspec(dllimport)
#endif
#else
#define PONY_EXPORT
#endif

#endif // PONY_SHARED_MACROS_HPP
