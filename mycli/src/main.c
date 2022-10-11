/*
 * Copyright (c) 2021 Nordic Semiconductor ASA.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr.h>
#include <tfm_veneers.h>
#include <tfm_ns_interface.h>
#include <sys/printk.h>
#include <shell/shell.h>
#include <version.h>
#include <logging/log.h>
#include <stdlib.h>
#include <kernel.h>
#include <stdio.h>
#include <secure_services.h>
#include <pm_config.h>
#include <fw_info.h>
#include <drivers/uart.h>
#include <cJSON.h>
#include <string.h>
#ifdef CONFIG_USB
#include <usb/usb_device.h>
#endif

#include "bls_hsm_ns.h"

char buffer[2048] = "";

static uint32_t GetFreeMemorySize()
{
  uint32_t  i;
  uint32_t  len;
  uint8_t*  ptr;
 
  for(i=1;;i++)
  {
    len = i * 1024;
    ptr = (uint8_t*)malloc(len);
    if(!ptr){
      break;
    }
    free(ptr);
  }
 
  return i;
}

LOG_MODULE_REGISTER(app);

static int cmd_keygen(const struct shell *shell, size_t argc, char **argv)
{
    if(argc == 1){
        keygen("", buffer);
		//printk("Keystore size: %d\n", ret, get_keystore_length()); // MUST BE DELETED
    }else{
        keygen(argv[1], buffer);
    }
    printf(buffer);
    memset(buffer, 0, 2048);
    return 0;
}

static int cmd_signature_message(const struct shell *shell, size_t argc, char **argv, char* buff)
{
    if(signature(argv[1], argv[2], buffer) == 0){
        printf("Signature: \n");
        printf("%s%s\n", "0x", buffer);
    }else{
        printf(buffer);
    }
    memset(buffer, 0, 2048);
	return 0;
}

/*static int cmd_signature_verification(const struct shell *shell, size_t argc, char **argv, char* buff)
{
    verify(argv[1], argv[2], argv[3], buffer);
    printf(buffer);
    memset(buffer, 0, 2048);
	return 0;
}*/

/*static int cmd_get_keys(const struct shell *shell, size_t argc, char **argv, char* buff)
{
    print_keys_Json(buffer);
    printf(buffer);
    memset(buffer, 0, 2048);
	return 0;
}*/

static int cmd_reset(const struct shell *shell, size_t argc, char **argv, char* buff){
    resetc(buffer);
    printf(buffer);
    memset(buffer, 0, 2048);
    return 0;
}

static int cmd_prompt(const struct shell *shell, size_t argc, char **argv){
    ARG_UNUSED(argc);

    if(strcmp(argv[1], "on") == 0){
        shell_prompt_change(shell, "uart:~$ ");
    }else if(strcmp(argv[1], "off") == 0){
        shell_prompt_change(shell, "");
    }else{
        printf("Usage: prompt on/off\n");
    }
    return 0;
}

/*static int cmd_import(const struct shell *shell, size_t argc, char **argv){
    import(argv[1], buffer);
    printf(buffer);
    memset(buffer, 0, 2048);
    return 0;
}*/

SHELL_CMD_ARG_REGISTER(keygen, NULL, "Generates secret key and public key", cmd_keygen, 1, 1);

SHELL_CMD_ARG_REGISTER(signature, NULL, "Signs a message with a specific public key", cmd_signature_message, 3, 0);

//SHELL_CMD_ARG_REGISTER(verify, NULL, "Verifies the signature", cmd_signature_verification, 4, 0);

//SHELL_CMD_ARG_REGISTER(getkeys, NULL, "Returns the identifiers of the keys available to the signer", cmd_get_keys, 1, 0);

SHELL_CMD_ARG_REGISTER(reset, NULL, "Deletes all generated keys", cmd_reset, 1, 0);

SHELL_CMD_ARG_REGISTER(prompt, NULL, "Toggle prompt", cmd_prompt, 2, 0);

//SHELL_CMD_ARG_REGISTER(import, NULL, "Import secret key", cmd_import, 2, 0);

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
	printk("Keystore size: %d\n", get_keystore_length()); // MUST BE DELETED
	memset(buffer, 0, 2048);
	ret = keygen("", buffer);
	printk("Generated new pair of keys. Index = %d\n", ret);
	printk("Keystore size: %d\n", get_keystore_length()); // MUST BE DELETED
	memset(buffer, 0, 2048);

	// get_pk
	char pk[97];
	get_pk(0, pk);
	pk[96] = '\0';
	printk("Generated public key 0:\n%s\n", pk);

	// Get Free Memory Size
	ret = GetFreeMemorySize();
	printk("Free memory size: %d\n", ret);

	// sign_pk
	//char msg[] = "5656565656565656565656565656565656565656565656565656565656565656";
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
	printk("Keystore size: %d\n", get_keystore_length()); // MUST BE DELETED

	printk("!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
}
