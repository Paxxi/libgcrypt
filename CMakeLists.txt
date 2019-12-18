cmake_minimum_required(VERSION 3.0)

project(libgcrypt VERSION 1.7.6 LANGUAGES C CXX)

find_package(libgpg-error 1.36.0 NO_MODULE REQUIRED)
find_package(iconv NO_MODULE REQUIRED)

if(MSVC)
  set(CMAKE_DEBUG_POSTFIX "d")
endif()

file(COPY mpi/generic/mpi-asm-defs.h DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/mpi) 

add_library(libgcrypt
  cipher/arcfour.c
  cipher/bithelp.h
  cipher/blake2.c
  cipher/blowfish.c
  cipher/bufhelp.h
  cipher/camellia-glue.c
  cipher/camellia.c
  cipher/camellia.h
  cipher/cast5.c
  cipher/chacha20.c
  cipher/cipher-aeswrap.c
  cipher/cipher-cbc.c
  cipher/cipher-ccm.c
  cipher/cipher-cfb.c
  cipher/cipher-cmac.c
  cipher/cipher-ctr.c
  cipher/cipher-gcm-intel-pclmul.c
  cipher/cipher-gcm.c
  cipher/cipher-internal.h
  cipher/cipher-ocb.c
  cipher/cipher-ofb.c
  cipher/cipher-poly1305.c
  cipher/cipher-selftest.c
  cipher/cipher-selftest.h
  cipher/cipher-xts.c
  cipher/cipher.c
  cipher/crc-intel-pclmul.c
  cipher/crc.c
  cipher/des.c
  cipher/dsa-common.c
  cipher/dsa.c
  cipher/ecc-common.h
  cipher/ecc-curves.c
  cipher/ecc-ecdsa.c
  cipher/ecc-eddsa.c
  cipher/ecc-gost.c
  cipher/ecc-misc.c
  cipher/ecc.c
  cipher/elgamal.c
  cipher/gost-s-box.c
  cipher/gost.h
  cipher/gost28147.c
  cipher/gostr3411-94.c
  cipher/hash-common.c
  cipher/hash-common.h
  cipher/hmac-tests.c
  cipher/idea.c
  cipher/kdf-internal.h
  cipher/kdf.c
  cipher/keccak.c
  cipher/keccak_permute_32.h
  cipher/keccak_permute_64.h
  cipher/mac-cmac.c
  cipher/mac-gmac.c
  cipher/mac-hmac.c
  cipher/mac-internal.h
  cipher/mac-poly1305.c
  cipher/mac.c
  cipher/md.c
  cipher/md4.c
  cipher/md5.c
  cipher/poly1305-internal.h
  cipher/poly1305.c
  cipher/primegen.c
  cipher/pubkey-internal.h
  cipher/pubkey-util.c
  cipher/pubkey.c
  cipher/rfc2268.c
  cipher/rijndael-aesni.c
  cipher/rijndael-armv8-ce.c
  cipher/rijndael-internal.h
  cipher/rijndael-padlock.c
  cipher/rijndael-ssse3-amd64.c
  cipher/rijndael-tables.h
  cipher/rijndael.c
  cipher/rmd160.c
  cipher/rsa-common.c
  cipher/rsa.c
  cipher/salsa20.c
  cipher/scrypt.c
  cipher/seed.c
  cipher/serpent.c
  cipher/sha1.c
  cipher/sha1.h
  cipher/sha256.c
  cipher/sha512.c
  cipher/stribog.c
  cipher/tiger.c
  cipher/twofish.c
  cipher/whirlpool.c
  cmake/config.h
  cmake/gcrypt.h
  cmake/gost-sb.h
  cmake/libgcrypt.def
  cmake/mod-source-info.h
  cmake/version.h
  compat/compat.c
  compat/libcompat.h
  mpi/ec-ed25519.c
  mpi/ec-internal.h
  mpi/ec.c
  mpi/generic/mpih-add1.c
  mpi/generic/mpih-lshift.c
  mpi/generic/mpih-mul1.c
  mpi/generic/mpih-mul2.c
  mpi/generic/mpih-mul3.c
  mpi/generic/mpih-rshift.c
  mpi/generic/mpih-sub1.c
  mpi/generic/udiv-w-sdiv.c
  mpi/longlong.h
  mpi/mpi-add.c
  mpi/mpi-asm-defs.h
  mpi/mpi-bit.c
  mpi/mpi-cmp.c
  mpi/mpi-div.c
  mpi/mpi-gcd.c
  mpi/mpi-inline.c
  mpi/mpi-inline.h
  mpi/mpi-internal.h
  mpi/mpi-inv.c
  mpi/mpi-mod.c
  mpi/mpi-mpow.c
  mpi/mpi-mul.c
  mpi/mpi-pow.c
  mpi/mpi-scan.c
  mpi/mpicoder.c
  mpi/mpih-div.c
  mpi/mpih-mul.c
  mpi/mpiutil.c
  random/jitterentropy-base-user.h
  random/jitterentropy-base.c
  random/jitterentropy.h
  random/rand-internal.h
  random/random-csprng.c
  random/random-drbg.c
  random/random-system.c
  random/random.c
  random/random.h
  random/rndhw.c
  random/rndw32.c
  random/rndjent.c
  src/cipher-proto.h
  src/cipher.h
  src/context.c
  src/context.h
  src/ec-context.h
  src/fips.c
  src/g10lib.h
  src/gcrypt-int.h
  src/global.c
  src/hmac256.c
  src/hmac256.h
  src/hwf-common.h
  src/hwf-x86.c
  src/hwfeatures.c
  src/misc.c
  src/missing-string.c
  src/mpi.h
  src/secmem.c
  src/secmem.h
  src/sexp.c
  src/stdmem.c
  src/stdmem.h
  src/types.h
  src/visibility.c
  src/visibility.h
)

if(WINDOWS_STORE)
  target_sources(libgcrypt PRIVATE
    src/uwp_compat.cpp
  )
  target_compile_definitions(libgcrypt
    PRIVATE
      MS_APP
  )
endif()

set_target_properties(libgcrypt PROPERTIES LINK_FLAGS "/DEF:\"libgcrypt.def\"")

target_link_libraries(libgcrypt
  PRIVATE
    $<$<CONFIG:Debug>:vccorlibd.lib>
    $<$<CONFIG:RelWithDebInfo>:vccorlib.lib>
    $<$<CONFIG:Debug>:msvcrtd.lib>
    $<$<CONFIG:RelWithDebInfo>:msvcrt.lib>
    libgpg-error::libgpg-error
    iconv::iconv
    ws2_32.lib
    version.lib
    shlwapi.lib
    Advapi32.lib
    Kernel32.lib
)

target_link_options(libgcrypt PRIVATE
  /NODEFAULTLIB:vccorlibd
  /NODEFAULTLIB:msvcrtd
  /NODEFAULTLIB:vccorlib
  /NODEFAULTLIB:msvcrt
  /INCREMENTAL:NO
  /debug:full
)
target_compile_definitions(libgcrypt
  PRIVATE
  HAVE_CONFIG_H
  _CRT_SECURE_NO_WARNINGS
  _CRT_NONSTDC_NO_WARNINGS
  __i386__
  __builtin_bswap32=_byteswap_ulong
  __builtin_bswap64=_byteswap_uint64
  asm=__asm__
)
 target_compile_options(libgcrypt
  PRIVATE
  /sdl-
  /ZW
  /EHsc
  /MP
)

target_include_directories(libgcrypt
  PRIVATE
  $<BUILD_INTERFACE:.;cmake;src;mpi;${CMAKE_CURRENT_BINARY_DIR}>
  INTERFACE
  $<INSTALL_INTERFACE:include/libgcrypt>
)

include(CMakePackageConfigHelpers)
write_basic_package_version_file(
  ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}-config-version.cmake
  VERSION ${PROJECT_VERSION}
  COMPATIBILITY AnyNewerVersion
)

install(TARGETS ${PROJECT_NAME} EXPORT ${PROJECT_NAME}
  RUNTIME DESTINATION bin
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib
)

install(FILES cmake/gcrypt.h DESTINATION include/libgcrypt)

if(MSVC)
  set_target_properties(${PROJECT_NAME}
    PROPERTIES
      COMPILE_PDB_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}
      COMPILE_PDB_NAME ${PROJECT_NAME}
      COMPILE_PDB_NAME_DEBUG ${PROJECT_NAME}d
  )
  install(FILES
    ${PROJECT_BINARY_DIR}/RelWithDebInfo/libgcrypt.pdb
    DESTINATION lib
    CONFIGURATIONS RelWithDebInfo
  )
  install(FILES
    ${PROJECT_BINARY_DIR}/Debug/libgcryptd.pdb
    DESTINATION lib
    CONFIGURATIONS Debug
  )
endif()

install(EXPORT ${PROJECT_NAME}
  FILE
    ${PROJECT_NAME}.cmake
  NAMESPACE
    ${PROJECT_NAME}::
  DESTINATION
    lib/cmake/${PROJECT_NAME}
)

install(
  FILES
    cmake/${PROJECT_NAME}-config.cmake
    ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}-config-version.cmake
  DESTINATION
    lib/cmake/${PROJECT_NAME}
)