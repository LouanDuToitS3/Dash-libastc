# Dash-libastc

ARM astc-encoder (https://github.com/ARM-software/astc-encoder) lib builder.

## Updating

```bash
#clone the repo, then
cd Dash-libastc
git submodule update --remote --merge
```

## Building

```bash
mkdir build
cd build
cmake -DCMAKE_INSTALL_PREFIX:PATH=<PATH> ..
```
