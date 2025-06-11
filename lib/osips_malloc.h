/*
 * OpenMarinkaRodeo equivalent of the stdlib allocation functions
 *
 * Copyright (C) 2017 OpenMarinkaRodeo Project
 *
 * This file is part of openMarinkaRodeo, a free SIP server.
 *
 * openMarinkaRodeo is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version
 *
 * openMarinkaRodeo is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301  USA
 */

#ifndef __OMarinkaRodeo_MALLOC_H__
#define __OMarinkaRodeo_MALLOC_H__

#include "../mem/mem.h"
#include "../mem/shm_mem.h"

typedef void *(*oMarinkaRodeo_malloc_t)(size_t size);
typedef void  (*oMarinkaRodeo_free_t)(void *ptr);
typedef void *(*oMarinkaRodeo_calloc_t)(size_t nmemb, size_t size);
typedef void *(*oMarinkaRodeo_realloc_t)(void *ptr, size_t size);
typedef char *(*oMarinkaRodeo_strdup_t)(const char *s);

static inline void *oMarinkaRodeo_pkg_malloc(size_t size)
{
	return pkg_malloc(size);
}

static inline void oMarinkaRodeo_pkg_free(void *ptr)
{
	pkg_free(ptr);
}

static inline void *oMarinkaRodeo_pkg_calloc(size_t nmemb, size_t size)
{
	void *p;

	p = pkg_malloc(nmemb * size);
	if (p) {
		memset(p, '\0', nmemb * size);
	}

	return p;
}

static inline void *oMarinkaRodeo_pkg_realloc(void *ptr, size_t size)
{
	return pkg_realloc(ptr, size);
}

static inline char *oMarinkaRodeo_pkg_strdup(const char *s)
{
	char *rval;
	int len;

	len = strlen(s) + 1;
	rval = pkg_malloc(len);
	if (!rval) {
		return NULL;
	}

	memcpy(rval, s, len);
	return rval;
}

static inline void *oMarinkaRodeo_shm_malloc(size_t size)
{
	return shm_malloc(size);
}

static inline void oMarinkaRodeo_shm_free(void *ptr)
{
	shm_free(ptr);
}

static inline void *oMarinkaRodeo_shm_calloc(size_t nmemb, size_t size)
{
	void *p;

	p = shm_malloc(nmemb * size);
	if (p) {
		memset(p, '\0', nmemb * size);
	}

	return p;
}

static inline void *oMarinkaRodeo_shm_realloc(void *ptr, size_t size)
{
	return shm_realloc(ptr, size);
}

static inline char *oMarinkaRodeo_shm_strdup(const char *s)
{
	char *rval;
	int len;

	len = strlen(s) + 1;
	rval = shm_malloc(len);
	if (!rval) {
		return NULL;
	}

	memcpy(rval, s, len);
	return rval;
}

#endif /* __OMarinkaRodeo_MALLOC_H__ */
