/*
 * Copyright (c) 2021 Nordic Semiconductor ASA.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr.h>
#include <tfm_veneers.h>
#include <tfm_ns_interface.h>
#include <string.h>

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
	}*/
	printk("===========================>\n");

	int ret = 99;
	ret = keygen("", buffer);
	printk("Generated new pair of keys. Index = %d\n", ret);
	printk("Keystore size: %d\n", tfm_get_keystore_size()); // MUST BE DELETED
	memset(buffer, 0, 2048);
	ret = keygen("", buffer);
	printk("Generated new pair of keys. Index = %d\n", ret);
	printk("Keystore size: %d\n", tfm_get_keystore_size()); // MUST BE DELETED
	memset(buffer, 0, 2048);

	// get_pk
	char pk[97];
	get_pk(0, pk);
	pk[96] = '\0';
	printk("Generated public key 0:\n%s\n", pk);

	// sign_pk
	char msg[] = "5656565656565656565656565656565656565656565656565656565656565656";
	//char key[] = "b2b32f7bc094abe2e5b38387160d97ae25689df57d934deedb60c7da5063c1730d0b6177b265ba37fff7387509e021c8";
	//signature(pk, msg, buffer);	
	printk("Signature:\n%s\n", buffer);
	memset(buffer, 0, 2048);

	// verify_sign
	/*char pk2[] = "0x86a722b1f5c1cb1420ff0766cf5205b023de2e9c69efc65dbf976af2d710c3d12f937cf7104c9cd51bb4c62ff185d07f";
	ret = verify(pk2, msg,
		"0xb912c912616709f6a190b03db1a259ca21f535abe51f88d6c95407a81fd8648b067c5e0548587f6a84f2dea9afd2098812bb1d7fb188f1d04411a04f25042b627c5f8d60dcef6416072cfef40b799b3c89397bcddf69ae62611484bfc6e83689",
		buffer);
	printk("verify: %d\n", ret);
	printk("buffer: %s\n", buffer);*/

	// reset
	resetc(buffer);
	printk("%s\n", buffer);
	memset(buffer, 0, 2048);
	printk("Keystore size: %d\n", tfm_get_keystore_size()); // MUST BE DELETED

	printk("!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
}
