# bls-hsm-2. Implementing TF-M

This repository is an effort to move the implementation of a secure partition for the [bls-hsm](https://github.com/decentralizedsecurity/bls-hsm) project from SPM to TF-M. The idea is that the blst functions that are used are executed in the secure partition.

Previously, when importing a static library (containing the blst functions) there is a problem with flash memory. This problem is detailed and solved in the following forum: https://devzone.nordicsemi.com/f/nordic-q-a/90871/problem-importing-a-library-into-tf-m-not-enough-space-to-import-i

Now, blst its imported. In `bls_hsm.h`, `blst_keygen` (a blst function) is executed correctly. However, when `blst_sign_pk_in_g1` is executed, there is a problem and the board. Therefore, I guess the problem is not in the import of the library, but must be related to memory.

## How to reproduce the error
Build and execute application mycli. You will see that the board reboots.

## Useful information about the project:
- Using nRF5340DK development kit.
- nRF SDK v2.0.0
- The project is based on the example: TF-M Secure Partition Sample. 
