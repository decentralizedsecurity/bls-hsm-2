# bls-hsm-2. Implementing TF-M

This repository is an effort to move the implementation of a secure partition for the [bls-hsm](https://github.com/decentralizedsecurity/bls-hsm) project from SPM to TF-M. The idea is that the [blst](https://github.com/supranational/blst) functions that are used are executed in the secure partition.

Previously, when importing a static library (containing the blst functions) there is a problem with flash memory. This problem is detailed and solved in the following forum: https://devzone.nordicsemi.com/f/nordic-q-a/90871/problem-importing-a-library-into-tf-m-not-enough-space-to-import-i

Now, blst its imported. In `bls_hsm.h`, `blst_keygen` (a blst function) is executed correctly. However, when `blst_sign_pk_in_g1` is executed, there is a problem and the board. Therefore, I guess the problem is not in the import of the library, but must be related to memory. There is an entry in the Nordic Semiconductor forum aiming to solve this problem: https://devzone.nordicsemi.com/f/nordic-q-a/92220/board-reboots-when-a-function-is-executed-in-tf-m

However, in the project using SPM, [bls-hsm](https://github.com/decentralizedsecurity/bls-hsm), all the functions of the blst library did work correctly.

## How to reproduce the error
Build and execute application mycli. You will see that the board reboots.

## Notes
- The reboot of the board made me think that it might be a RAM problem. To do so, I set the value of the RAM assigned to the safe partition to an extremely high value,   by writing the following in prj.conf:
  ```
  CONFIG_PM_PARTITION_SIZE_TFM_SRAM=0x63000
  ```
  This did not solve the problem.

- mycli/main.c is provisional, to test all functions quickly. The idea is to make it similar or equal to the [`main.c` file of the original project](https://github.com/decentralizedsecurity/bls-hsm/blob/main/cli/src/main.c).

## How was the static libblst.a file generated?
By running the [`build_libs.sh`](https://github.com/decentralizedsecurity/bls-hsm/blob/main/build_libs.sh) script which can be found in the original project, [bls-hsm](https://github.com/decentralizedsecurity/bls-hsm)

## Useful information about the project:
- Using nRF5340DK development kit.
- nRF SDK v2.0.0
- The project is based on the example: TF-M Secure Partition Sample. 
