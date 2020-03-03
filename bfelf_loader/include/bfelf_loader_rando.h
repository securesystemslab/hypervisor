/*
 * Bareflank Hypervisor
 * Copyright (C) 2017 Assured Information Security, Inc.
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
 */

/**
 * @file bfelf_loader_rando.h
 */

/* ---------------------------------------------------------------------------------------------- */
/* Load-Time Randomization Supports                                                                 */
/* ---------------------------------------------------------------------------------------------- */

/* @cond */
#ifndef MAX_LT_RANDO_NUM_BUCKETS
#define MAX_LT_RANDO_NUM_BUCKETS  (256U)
#endif
#ifndef MAX_LT_RANDO_BUCKET_NUM_ENTS
#define MAX_LT_RANDO_BUCKET_NUM_ENTS  (256U)
#endif

struct bfelf_lt_rando_entry_t {
  uint32_t key;
  uint64_t cookie;
};
struct bfelf_lt_rando_bucket_t {
  struct bfelf_lt_rando_entry_t entries[MAX_LT_RANDO_BUCKET_NUM_ENTS];
  uint32_t num_entries;
};

// The provided hash algorithm will trim hash to (less than) 32-bit
// at the end, so it's okay to truncate here
static inline uint32_t private_hash32(const char* s) {
  return (uint32_t)private_hash(s);
}

struct bfelf_lt_rando_t {
  struct bfelf_lt_rando_bucket_t buckets[MAX_LT_RANDO_NUM_BUCKETS];
};

// @return zero if found
static inline int
private_lt_rando_cookie_query(struct bfelf_lt_rando_t* lt_rando,
                              const char* s, uint64_t* cookie) {
  uint32_t hash = private_hash32(s);
  struct bfelf_lt_rando_bucket_t* bucket
    = &lt_rando->buckets[hash % MAX_LT_RANDO_NUM_BUCKETS];
  int i;

  for(i = 0; i < bucket->num_entries; ++i) {
    struct bfelf_lt_rando_entry_t* entry = &bucket->entries[i];
    if(entry->key == hash) {
      *cookie = entry->cookie;
      return 0;
    }
  }
  return 1;
}

// @return the cookie value
static uint64_t
private_lt_rando_cookie_add(struct bfelf_lt_rando_t* lt_rando, const char* s) {
  uint32_t hash = private_hash32(s);
  struct bfelf_lt_rando_bucket_t* bucket
    = &lt_rando->buckets[hash % MAX_LT_RANDO_NUM_BUCKETS];
  // TODO: Truncate to [text_begin, text_end)
  uint64_t new_cookie = platform_get_random_int64();
  struct bfelf_lt_rando_entry_t* new_entry
    = &bucket->entries[bucket->num_entries++];

  new_entry->key = hash;
  new_entry->cookie = new_cookie;

  return new_cookie;
}
/* @endcond */
