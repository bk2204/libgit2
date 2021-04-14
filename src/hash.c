/*
 * Copyright (C) the libgit2 contributors. All rights reserved.
 *
 * This file is part of libgit2, distributed under the GNU GPL v2 with
 * a Linking Exception. For full terms see the included COPYING file.
 */

#include "hash.h"

int git_hash_global_init(void)
{
	return git_hash_sha1_global_init();
}

int git_hash_ctx_init(git_hash_ctx *ctx)
{
	int error;

	if ((error = git_hash_sha1_ctx_init(&ctx->sha1)) < 0)
		return error;

	ctx->algo = GIT_HASH_ALGO_SHA1;

	return 0;
}

void git_hash_ctx_cleanup(git_hash_ctx *ctx)
{
	switch (ctx->algo) {
		case GIT_HASH_ALGO_SHA1:
			git_hash_sha1_ctx_cleanup(&ctx->sha1);
			return;
		case GIT_HASH_ALGO_SHA256:
			git_hash_sha256_ctx_cleanup(&ctx->sha256);
			return;
		default:
			/* unreachable */ ;
	}
}

int git_hash_init(git_hash_ctx *ctx)
{
	switch (ctx->algo) {
		case GIT_HASH_ALGO_SHA1:
			return git_hash_sha1_init(&ctx->sha1);
		case GIT_HASH_ALGO_SHA256:
			return git_hash_sha256_init(&ctx->sha256);
		default:
			/* unreachable */ ;
	}
	GIT_ASSERT(0);
	return -1;
}

int git_hash_update(git_hash_ctx *ctx, const void *data, size_t len)
{
	switch (ctx->algo) {
		case GIT_HASH_ALGO_SHA1:
			return git_hash_sha1_update(&ctx->sha1, data, len);
		case GIT_HASH_ALGO_SHA256:
			return git_hash_sha256_update(&ctx->sha256, data, len);
		default:
			/* unreachable */ ;
	}
	GIT_ASSERT(0);
	return -1;
}

int git_hash_final(git_oid *out, git_hash_ctx *ctx)
{
	out->hash_algo = ctx->algo;
	switch (ctx->algo) {
		case GIT_HASH_ALGO_SHA1:
			return git_hash_sha1_final(out, &ctx->sha1);
		case GIT_HASH_ALGO_SHA256:
			return git_hash_sha256_final(out, &ctx->sha256);
		default:
			/* unreachable */ ;
	}
	GIT_ASSERT(0);
	return -1;
}

int git_hash_buf(git_oid *out, const void *data, size_t len)
{
	git_hash_ctx ctx;
	int error = 0;

	if (git_hash_ctx_init(&ctx) < 0)
		return -1;

	if ((error = git_hash_update(&ctx, data, len)) >= 0)
		error = git_hash_final(out, &ctx);

	git_hash_ctx_cleanup(&ctx);

	return error;
}

size_t git_hash_len(git_hash_algo algo)
{
	switch (algo) {
		case GIT_HASH_ALGO_SHA1:
		default:
			return 20;
		case GIT_HASH_ALGO_SHA256:
			return 32;
	}
}

size_t git_hash_len_hex(git_hash_algo algo)
{
	switch (algo) {
		case GIT_HASH_ALGO_SHA1:
		default:
			return 40;
		case GIT_HASH_ALGO_SHA256:
			return 64;
	}
}

const char *git_hash_zero_value(git_hash_algo algo)
{
	switch (algo) {
		case GIT_HASH_ALGO_SHA1:
			return GIT_OID_HEX_ZERO;
		case GIT_HASH_ALGO_SHA256:
			return GIT_OID_HEX_ZERO_SHA256;
		default:
			assert(0);
			return NULL;
	}
}

int git_hash_vec(git_oid *out, git_buf_vec *vec, size_t n)
{
	git_hash_ctx ctx;
	size_t i;
	int error = 0;

	if (git_hash_ctx_init(&ctx) < 0)
		return -1;

	for (i = 0; i < n; i++) {
		if ((error = git_hash_update(&ctx, vec[i].data, vec[i].len)) < 0)
			goto done;
	}

	error = git_hash_final(out, &ctx);

done:
	git_hash_ctx_cleanup(&ctx);

	return error;
}
