/*
 * Copyright (c) 2021 Nordic Semiconductor ASA.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <tfm_veneers.h>
#include <tfm_ns_interface.h>

#include "secure_partition_interface.h"

psa_status_t dp_secret_digest(uint32_t secret_index,
			void *p_digest,
			size_t digest_size)
{
	psa_status_t status;
	psa_invec in_vec[] = {
		{ .base = &secret_index, .len = sizeof(secret_index) },
	};

	psa_outvec out_vec[] = {
		{ .base = p_digest, .len = digest_size }
	};

	status = tfm_ns_interface_dispatch(
				(veneer_fn)tfm_dp_secret_digest_req_veneer,
				(uint32_t)in_vec,  IOVEC_LEN(in_vec),
				(uint32_t)out_vec, IOVEC_LEN(out_vec));

	return status;
}

int tfm_get_keystore_size(){
	uint32_t size;
	psa_status_t status;
	psa_invec out_vec[] = {
		{ .base = &size, .len = sizeof(size) },
	};

	status = tfm_ns_interface_dispatch(
				(veneer_fn)tfm_get_keystore_size_req_veneer,
				NULL,  0,
				(uint32_t)out_vec, IOVEC_LEN(out_vec));

	return size;
}

int tfm_store_pk(char* public_key_hex){
	return 0;
}

int tfm_get_key(int index, char* public_key_hex){
	return 0;
}

int tfm_secure_keygen(char* info, size_t infosize){
	uint32_t index;
	psa_status_t status;

    psa_invec in_vec[] = {
		{ .base = info, .len = infosize }
	};

	psa_invec out_vec[] = {
		{ .base = &index, .len = sizeof(index) },
	};

	status = tfm_ns_interface_dispatch(
				(veneer_fn)tfm_secure_keygen_req_veneer,
				(uint32_t)in_vec, IOVEC_LEN(in_vec),
				(uint32_t)out_vec, IOVEC_LEN(out_vec));

	return index;
}

int tfm_sign_pk(char* pk, char* msg, char* sign){
	return 0;
}

int tfm_verify_sign(char* pk, char* msg, char* sig){
	return 0;
}

void tfm_reset(){
	
}

int tfm_import_sk(char* sk){
	return 0;
}
