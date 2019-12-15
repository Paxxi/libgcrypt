#include <windows.h>

#ifdef MS_APP
#include <windows.security.cryptography.h>
using namespace Windows::Security::Cryptography;
#ifdef __cplusplus
extern "C" {
#endif

int
uwp_urandom(unsigned char* buffer, size_t size) {
	auto s = static_cast<unsigned int>(size);
	auto buf = ref new Platform::Array<unsigned char>(buffer, s);
	auto cryptoBuffer = CryptographicBuffer::GenerateRandom(s);
	CryptographicBuffer::CopyToByteArray(cryptoBuffer, &buf);
	return TRUE;
}

#ifdef __cplusplus
}
#endif

#endif