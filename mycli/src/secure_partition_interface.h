/*
 * Copyright (c) 2021 Nordic Semiconductor ASA.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include "tfm_api.h"

psa_status_t dp_secret_digest(uint32_t secret_index,
			      void *p_digest,
			      size_t digest_size);
int tfm_get_keystore_size();
int tfm_secure_keygen(char* info, size_t infosize);
