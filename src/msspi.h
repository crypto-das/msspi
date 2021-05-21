#ifndef _MSSPI_H_INCLUDED_
#define _MSSPI_H_INCLUDED_

#define TLS1_VERSION    0x0301
#define TLS1_1_VERSION  0x0302
#define TLS1_2_VERSION  0x0303

#ifndef SECPKGCONTEXT_CIPHERINFO_V1

#define SECPKGCONTEXT_CIPHERINFO_V1 1
#define SZ_ALG_MAX_SIZE 64

#ifndef WIN32
typedef unsigned int DWORD;
#else
typedef unsigned long DWORD;
#endif

typedef wchar_t WCHAR;

typedef struct _SecPkgContext_CipherInfo
{
    DWORD dwVersion;
    DWORD dwProtocol;
    DWORD dwCipherSuite;
    DWORD dwBaseCipherSuite;
    WCHAR szCipherSuite[SZ_ALG_MAX_SIZE];
    WCHAR szCipher[SZ_ALG_MAX_SIZE];
    DWORD dwCipherLen;
    DWORD dwCipherBlockLen;
    WCHAR szHash[SZ_ALG_MAX_SIZE];
    DWORD dwHashLen;
    WCHAR szExchange[SZ_ALG_MAX_SIZE];
    DWORD dwMinExchangeLen;
    DWORD dwMaxExchangeLen;
    WCHAR szCertificate[SZ_ALG_MAX_SIZE];
    DWORD dwKeyType;
} SecPkgContext_CipherInfo, *PSecPkgContext_CipherInfo;

#endif /* SECPKGCONTEXT_CIPHERINFO_V1 */

#ifdef __cplusplus
extern "C" {
#endif

typedef struct MSSPI * MSSPI_HANDLE;

typedef int ( * msspi_read_cb )( void * cb_arg, void * buf, int len );
typedef int ( * msspi_write_cb )( void * cb_arg, const void * buf, int len );
typedef int ( * msspi_cert_cb )( void * cb_arg );

MSSPI_HANDLE msspi_open( void * cb_arg, msspi_read_cb, msspi_write_cb );

char msspi_set_hostname( MSSPI_HANDLE h, const char * hostName );
char msspi_set_cachestring( MSSPI_HANDLE h, const char * cacheString );
char msspi_set_alpn( MSSPI_HANDLE h, const char * alpn, unsigned len );
void msspi_set_certstore( MSSPI_HANDLE h, const char * store );
char msspi_set_mycert( MSSPI_HANDLE h, const char * clientCert, int len );
char msspi_add_mycert( MSSPI_HANDLE h, const char * clientCert, int len );
char msspi_set_mycert_pfx( MSSPI_HANDLE h, const char * pfx, int len, const char * password );
char msspi_add_mycert_pfx( MSSPI_HANDLE h, const char * pfx, int len, const char * password );
char msspi_set_mycert_options( MSSPI_HANDLE h, char silent, const char * pin, char selftest );
void msspi_set_peerauth( MSSPI_HANDLE h, char is_peerauth );
void msspi_set_cert_cb( MSSPI_HANDLE h, msspi_cert_cb );
void msspi_set_client( MSSPI_HANDLE h );
void msspi_set_version( MSSPI_HANDLE h, int min, int max );
char msspi_set_cipherlist( MSSPI_HANDLE h, const char * cipherlist );
char msspi_set_credprovider( MSSPI_HANDLE h, const char * credprovider );

int msspi_connect( MSSPI_HANDLE h );
int msspi_accept( MSSPI_HANDLE h );
int msspi_read( MSSPI_HANDLE h, void * buf, int len );
int msspi_write( MSSPI_HANDLE h, const void * buf, int len );
int msspi_shutdown( MSSPI_HANDLE h );

char msspi_random( void * buf, int len, char safe );

#define MSSPI_OK    ( 0 )
#define MSSPI_ERROR ( 1 << 31 )

#define MSSPI_READING ( 1 << 1 )
#define MSSPI_WRITING ( 1 << 2 )
#define MSSPI_X509_LOOKUP ( 1 << 3 )
#define MSSPI_SHUTDOWN_PROC ( 1 << 4 )
#define MSSPI_SENT_SHUTDOWN ( 1 << 5 )
#define MSSPI_RECEIVED_SHUTDOWN ( 1 << 6 )
#define MSSPI_LAST_PROC_WRITE ( 1 << 7 )

int msspi_state( MSSPI_HANDLE h );
int msspi_pending( MSSPI_HANDLE h );
int msspi_peek( MSSPI_HANDLE h, void * buf, int len );

PSecPkgContext_CipherInfo msspi_get_cipherinfo( MSSPI_HANDLE h );
const char * msspi_get_version( MSSPI_HANDLE h );
char msspi_get_mycert( MSSPI_HANDLE h, const char ** buf, int * len );
char msspi_get_peercerts( MSSPI_HANDLE h, const char ** bufs, int * lens, size_t * count );
char msspi_get_peerchain( MSSPI_HANDLE h, char online, const char ** bufs, int * lens, size_t * count );
char msspi_get_peernames( MSSPI_HANDLE h, const char ** subject, size_t * slen, const char ** issuer, size_t * ilen );
char msspi_get_issuerlist( MSSPI_HANDLE h, const char ** bufs, int * lens, size_t * count );
const char * msspi_get_alpn( MSSPI_HANDLE h );

#define MSSPI_VERIFY_OK                 0x00000000L
#define MSSPI_VERIFY_ERROR              0x00000001L
#ifndef TRUST_E_CERT_SIGNATURE
#define TRUST_E_CERT_SIGNATURE          0x80096004L
#define CRYPT_E_REVOKED                 0x80092010L
#define CERT_E_UNTRUSTEDROOT            0x800B0109L
#define CERT_E_UNTRUSTEDTESTROOT        0x800B010DL
#define CERT_E_CHAINING                 0x800B010AL
#define CERT_E_REVOCATION_FAILURE       0x800B010EL
#define CERT_E_WRONG_USAGE              0x800B0110L
#define CERT_E_EXPIRED                  0x800B0101L
#define CERT_E_INVALID_NAME             0x800B0114L
#define CERT_E_CN_NO_MATCH              0x800B010FL
#define CERT_E_INVALID_POLICY           0x800B0113L
#define TRUST_E_BASIC_CONSTRAINTS       0x80096019L
#define CERT_E_CRITICAL                 0x800B0105L
#define CERT_E_VALIDITYPERIODNESTING    0x800B0102L
#define CRYPT_E_NO_REVOCATION_CHECK     0x80092012L
#define CRYPT_E_REVOCATION_OFFLINE      0x80092013L
#define CERT_E_ROLE                     0x800B0103L
#endif

#ifndef SECBUFFER_ALERT
#define SECBUFFER_ALERT 17
#endif

unsigned msspi_verify( MSSPI_HANDLE h );
char msspi_verifypeer( MSSPI_HANDLE h, const char * store );

void msspi_close( MSSPI_HANDLE h );

#ifndef NO_MSSPI_CERT

typedef struct MSSPI_CERT * MSSPI_CERT_HANDLE;

MSSPI_CERT_HANDLE msspi_cert_open( const char * cert, size_t len );
MSSPI_CERT_HANDLE msspi_cert_next( MSSPI_CERT_HANDLE h );

char msspi_cert_subject( MSSPI_CERT_HANDLE ch, const char ** buf, size_t * len, char quotes );
char msspi_cert_issuer( MSSPI_CERT_HANDLE ch, const char ** buf, size_t * len, char quotes );
char msspi_cert_serial( MSSPI_CERT_HANDLE ch, const char ** buf, size_t * len );
char msspi_cert_keyid( MSSPI_CERT_HANDLE ch, const char ** buf, size_t * len );
char msspi_cert_sha1( MSSPI_CERT_HANDLE ch, const char ** buf, size_t * len );
char msspi_cert_alg_sig( MSSPI_CERT_HANDLE ch, const char ** buf, size_t * len );
char msspi_cert_alg_key( MSSPI_CERT_HANDLE ch, const char ** buf, size_t * len );
char msspi_cert_time_issued( MSSPI_CERT_HANDLE ch, struct tm * time );
char msspi_cert_time_expired( MSSPI_CERT_HANDLE ch, struct tm * time );

void msspi_cert_close( MSSPI_CERT_HANDLE ch );

#endif /* NO_MSSPI_CERT */

#ifdef __cplusplus
}
#endif

#endif /* _MSSPI_H_INCLUDED_ */
