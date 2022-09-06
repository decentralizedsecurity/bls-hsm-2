# tfm-test

This repository is an effort to move the implementation of a secure partition for the [bls-hsm](https://github.com/decentralizedsecurity/bls-hsm) project from SPM to TF-M. The idea is that the blst functions that are used are executed in the secure partition.

When importing a static library (containing the blst functions) there is a problem with flash memory. This problem is detailed in the following forum: https://devzone.nordicsemi.com/f/nordic-q-a/90871/problem-importing-a-library-into-tf-m-not-enough-space-to-import-i

## How to reproduce the error:
If you do a build of the application (mycli), no problem is shown. In order to reproduce the error, lines 48, 49, 50 and 51 of secure_partition/CMakeLists.txt must be uncommented.
https://github.com/Pablosanserr/tfm-test/blob/ea84b72612f2c8083fd846f718df5f58887fca76/secure_partition/CMakeLists.txt#L48-L51

## Useful information about the project:
- Using nRF5340DK development kit.
- nRF SDK v2.0.0
- The project is based on the example: TF-M Secure Partition Sample. 
