/*
 * Copyright (c) 2021 Nordic Semiconductor ASA
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <psa/crypto.h>
#include <stdbool.h>
#include <stdint.h>
#include "tfm_secure_api.h"
#include "tfm_api.h"

#include "../lib/bls_hsm.h"

#define NUM_SECRETS 5

struct dp_secret {
	uint8_t secret[16];
};

struct dp_secret secrets[NUM_SECRETS] = {
	{ {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15} },
	{ {1, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15} },
	{ {2, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15} },
	{ {3, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15} },
	{ {4, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15} },
};

typedef void (*psa_write_callback_t)(void *handle, uint8_t *digest,
				     uint32_t digest_size);

static psa_status_t tfm_dp_secret_digest(uint32_t secret_index,
			size_t digest_size, size_t *p_digest_size,
			psa_write_callback_t callback, void *handle)
{
	uint8_t digest[32];
	psa_status_t status;

	/* Check that secret_index is valid. */
	if (secret_index >= NUM_SECRETS) {
		return PSA_ERROR_INVALID_ARGUMENT;
	}

	/* Check that digest_size is valid. */
	if (digest_size != sizeof(digest)) {
		return PSA_ERROR_INVALID_ARGUMENT;
	}

	status = psa_hash_compute(PSA_ALG_SHA_256, secrets[secret_index].secret,
				sizeof(secrets[secret_index].secret), digest,
				digest_size, p_digest_size);

	if (status != PSA_SUCCESS) {
		return status;
	}
	if (*p_digest_size != digest_size) {
		return PSA_ERROR_PROGRAMMER_ERROR;
	}

	callback(handle, digest, digest_size);

	return PSA_SUCCESS;
}

#include "tfm_memory_utils.h"

void psa_write_digest(void *handle, uint8_t *digest, uint32_t digest_size)
{
	tfm_memcpy(handle, digest, digest_size);
}

psa_status_t tfm_dp_secret_digest_req(psa_invec *in_vec, size_t in_len,
				      psa_outvec *out_vec, size_t out_len)
{
	uint32_t secret_index;

	if ((in_len != 1) || (out_len != 1)) {
		/* The number of arguments are incorrect */
		return PSA_ERROR_PROGRAMMER_ERROR;
	}

	if (in_vec[0].len != sizeof(secret_index)) {
		/* The input argument size is incorrect */
		return PSA_ERROR_PROGRAMMER_ERROR;
	}

	secret_index = *((uint32_t *)in_vec[0].base);

	return tfm_dp_secret_digest(secret_index, out_vec[0].len,
				    &out_vec[0].len, psa_write_digest,
				    (void *)out_vec[0].base);
}


psa_status_t tfm_dp_req_mngr_init(void){
	return PSA_SUCCESS;
}

psa_status_t tfm_get_keystore_size_req(psa_invec *in_vec, size_t in_len,
				      psa_outvec *out_vec, size_t size_len){
	uint32_t ksize = get_keystore_size();
	tfm_memcpy((void*) out_vec[0].base, &ksize, out_vec[0].len);
	return PSA_SUCCESS;
}

psa_status_t tfm_secure_keygen_req(psa_invec *in_vec, size_t in_len,
				      psa_outvec *out_vec, size_t size_len){
	uint32_t index = 44; //secure_keygen(in_vec[0].base);
	tfm_memcpy((void*) out_vec[0].base, &index, out_vec[0].len);
	return PSA_SUCCESS;
}

// WIP
psa_status_t tfm_get_key_req(psa_invec *in_vec, size_t in_len,
				      psa_outvec *out_vec, size_t size_len){
	uint32_t index = 67;
	tfm_memcpy((void*) out_vec[0].base, &index, out_vec[0].len);
	return PSA_SUCCESS;
}