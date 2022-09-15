/*
 * Copyright (c) 2021 Nordic Semiconductor ASA.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr.h>
#include <tfm_veneers.h>
#include <tfm_ns_interface.h>

//#include "secure_partition_interface.h"
#include "bls_hsm_ns.h"

char buffer[2048] = "";

void main(void)
{
	/*uint8_t digest[32];

	for (int key = 0; key < 6; key++) {
		psa_status_t status = dp_secret_digest(key, digest, sizeof(digest));

		if (status != PSA_SUCCESS) {
			printk("Status: %d\n", status);
		} else {
			printk("Digest: ");
			for (int i = 0; i < 32; i++) {
				printk("%02x", digest[i]);
			}
			printk("\n");
		}
	}/**/
	printk("===========================>\n");

	int ret = 99;
	ret = keygen("", buffer);
	printk("ret = %d\n", ret);
	//printf(buffer);
    //memset(buffer, 0, 2048);
	printk("keystore size: %d\n", tfm_get_keystore_size()); // MUST BE DELETED

	ret = print_keys_Json(buffer);

	printk("!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
}
