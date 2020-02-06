/*
 * Copyright (C) the libgit2 contributors. All rights reserved.
 *
 * This file is part of libgit2, distributed under the GNU GPL v2 with
 * a Linking Exception. For full terms see the included COPYING file.
 */

#ifndef INCLUDE_hash_sha256_h__
#define INCLUDE_hash_sha256_h__

#include "common.h"

typedef struct git_hash_sha256_ctx git_hash_sha256_ctx;

#include "sha256/generic.h"

int git_hash_sha256_global_init(void);

int git_hash_sha256_ctx_init(git_hash_sha256_ctx *ctx);
void git_hash_sha256_ctx_cleanup(git_hash_sha256_ctx *ctx);

int git_hash_sha256_init(git_hash_sha256_ctx *c);
int git_hash_sha256_update(git_hash_sha256_ctx *c, const void *data, size_t len);
int git_hash_sha256_final(git_oid *out, git_hash_sha256_ctx *c);

#endif
