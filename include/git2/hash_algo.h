/*
 * Copyright (C) the libgit2 contributors. All rights reserved.
 *
 * This file is part of libgit2, distributed under the GNU GPL v2 with
 * a Linking Exception. For full terms see the included COPYING file.
 */
#ifndef INCLUDE_git_hash_algo_h__
#define INCLUDE_git_hash_algo_h__

#include "common.h"
#include "types.h"

/**
 * @file git2/hash_algo.h
 * @brief Git hash algorithm routines
 * @defgroup git_hash_algo Git hash algorithm
 * @ingroup Git
 * @{
 */
GIT_BEGIN_DECL

/**
 * Hash algorithm in use.
 */
typedef enum {
	GIT_HASH_ALGO_UNKNOWN = 0,
	GIT_HASH_ALGO_SHA1,
	GIT_HASH_ALGO_SHA256,
} git_hash_algo;

/** @} */
GIT_END_DECL
#endif
