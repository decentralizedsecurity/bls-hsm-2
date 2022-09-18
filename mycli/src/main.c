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
	printk("Generated new pair of keys. Index = %d\n", ret);
	printk("Keystore size: %d\n", tfm_get_keystore_size()); // MUST BE DELETED

	ret = print_keys_Json(buffer);

	// get_pk
	char pk[96];
	get_pk(0, pk);
	printk("Generated public key:\n%.96s\n", pk);/**/

	// sign_pk
	char msg[] = "5656565656565656565656565656565656565656565656565656565656565656";
	char buff[99];
	//char key[] = "b2b32f7bc094abe2e5b38387160d97ae25689df57d934deedb60c7da5063c1730d0b6177b265ba37fff7387509e021c8";
	//printk("Key: %.96s\n", key);
	//signature(pk, msg, buff);	
	//printk("Signature:\n%.32s\n", buff);

	// verify_sign
	ret = verify(pk, msg,
		"0xb912c912616709f6a190b03db1a259ca21f535abe51f88d6c95407a81fd8648b067c5e0548587f6a84f2dea9afd2098812bb1d7fb188f1d04411a04f25042b627c5f8d60dcef6416072cfef40b799b3c89397bcddf69ae62611484bfc6e83689",
		buffer);
	printk("verify: %d\n", ret);

	printk("!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
}
