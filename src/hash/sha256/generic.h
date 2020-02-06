/*
 * Copyright (C) the libgit2 contributors. All rights reserved.
 *
 * This file is part of libgit2, distributed under the GNU GPL v2 with
 * a Linking Exception. For full terms see the included COPYING file.
 */

#ifndef INCLUDE_hash_sha256_generic_h__
#define INCLUDE_hash_sha256_generic_h__

#include "hash/sha256.h"

struct git_hash_sha256_ctx {
	uint32_t state[8];
	uint64_t size;
	uint32_t offset;
	uint8_t buf[64];
};

#endif
