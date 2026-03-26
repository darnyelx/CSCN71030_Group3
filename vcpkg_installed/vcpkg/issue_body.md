Package: libpq[bonjour,core,lz4,openssl,zlib]:arm64-osx@18.3

**Host Environment**

- Host: arm64-osx
- Compiler: AppleClang 17.0.0.17000319
- CMake Version: 4.2.1
-    vcpkg-tool version: 2026-03-04-4b3e4c276b5b87a649e66341e11553e8c577459c
    vcpkg-scripts version: c27eeddba7 2026-03-25 (7 hours ago)

**To Reproduce**

`vcpkg install `

**Failure logs**

```
Downloading postgresql-18.3.tar.bz2, trying https://ftp.postgresql.org/pub/source/v18.3/postgresql-18.3.tar.bz2
Successfully downloaded postgresql-18.3.tar.bz2
-- Extracting source /Users/darnyelx/vcpkg/downloads/postgresql-18.3.tar.bz2
-- Applying patch unix/installdirs.patch
-- Applying patch unix/fix-configure.patch
-- Applying patch unix/single-linkage.patch
-- Applying patch unix/no-server-tools.patch
-- Applying patch unix/mingw-install.patch
-- Applying patch unix/mingw-static-importlib-fix.patch
-- Applying patch unix/python.patch
-- Applying patch windows/macro-def.patch
-- Applying patch windows/spin_delay.patch
-- Applying patch windows/tcl-9.0-alpha.patch
-- Applying patch windows/meson-vcpkg.patch
-- Applying patch windows/getopt.patch
-- Using source at /Users/darnyelx/vcpkg/buildtrees/libpq/src/tgresql-18-27989b1b15.clean
-- Getting CMake variables for arm64-osx
-- Loading CMake variables from /Users/darnyelx/vcpkg/buildtrees/libpq/cmake-get-vars_C_CXX-arm64-osx.cmake.log
-- Getting CMake variables for arm64-osx-dbg
-- Getting CMake variables for arm64-osx-rel
CMake Error at scripts/cmake/vcpkg_configure_make.cmake:721 (message):
  libpq requires autoconf from the system package manager (example: "sudo
  apt-get install autoconf")
Call Stack (most recent call first):
  ports/libpq/portfile.cmake:100 (vcpkg_configure_make)
  scripts/ports.cmake:206 (include)



```

**Additional context**

<details><summary>vcpkg.json</summary>

```
{
  "dependencies": [
    "libpqxx",
    "nlohmann-json"
  ],
  "version": "1",
  "name": "assignment"
}

```
</details>
