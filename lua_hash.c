#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "php_ini.h"
#include "ext/standard/info.h"
#include "ext/standard/basic_functions.h"
#include "ext/standard/md5.h"
#include "ext/standard/sha1.h"
#include "ext/standard/base64.h"
#include "ext/hash/php_hash.h"
#include "ext/hash/php_hash_adler32.h"
#include "ext/hash/php_hash_crc32.h"
#include "Zend/zend_exceptions.h"
#include "php_lua.h"
#include "lua_closure.h"

int php_lua_md5( lua_State *L ) {
	zval rv;
	int i = 0 , j = 0;
	int nargs = lua_gettop( L );

	if ( nargs < 1 ) {
		lua_pushnil( L );
		return 1;
	}

	php_lua_get_zval_from_lua( L , 1 , NULL , &rv );
	if ( Z_TYPE(rv) != IS_STRING || Z_STRLEN(rv) < 1 ) {
		lua_pushnil( L );
		return 1;
	}
	unsigned char bin[32];
	char txt[36];
	memset( bin , 0 , 32 );
	memset( txt , 0 , 36 );
	PHP_MD5_CTX md5;
	PHP_MD5InitArgs( &md5 , NULL );
	PHP_MD5Update( &md5 , Z_STRVAL( rv ) , Z_STRLEN( rv ) );
	PHP_MD5Final( bin , &md5 );
	for ( j = 0 ; j < 16 ; j++ )
		sprintf( txt + ( j << 1 ) , "%02x" , bin[j] );
	txt[32] = 0;
	zval_ptr_dtor( &rv );
	lua_pushstring( L , txt );
	return 1;

}

int php_lua_sha1( lua_State *L ) {
	zval rv;
	int i = 0 , j = 0;
	int nargs = lua_gettop( L );

	if ( nargs < 1 ) {
		lua_pushnil( L );
		return 1;
	}

	php_lua_get_zval_from_lua( L , 1 , NULL , &rv );
	if ( Z_TYPE(rv) != IS_STRING || Z_STRLEN(rv) < 1 ) {
		lua_pushnil( L );
		return 1;
	}
	unsigned char bin[32];
	char txt[42];
	memset( bin , 0 , 32 );
	memset( txt , 0 , 42 );
	PHP_SHA1_CTX md5;
	PHP_SHA1InitArgs( &md5 , NULL );
	PHP_SHA1Update( &md5 , Z_STRVAL( rv ) , Z_STRLEN( rv ) );
	PHP_SHA1Final( bin , &md5 );
	for ( j = 0 ; j < 20 ; j++ )
		sprintf( txt + ( j << 1 ) , "%02x" , bin[j] );
	txt[40] = 0;
	zval_ptr_dtor( &rv );
	lua_pushstring( L , txt );
	return 1;
}

int php_lua_crc32b( lua_State *L ) {
	zval rv;
	int i = 0 , j = 0;
	int nargs = lua_gettop( L );

	if ( nargs < 1 ) {
		lua_pushinteger( L , 0 );
		return 1;
	}

	php_lua_get_zval_from_lua( L , 1 , NULL , &rv );
	if ( Z_TYPE(rv) != IS_STRING || Z_STRLEN(rv) < 1 ) {
		lua_pushinteger( L , 0 );
		return 1;
	}
	unsigned char bin[4];
	memset( bin , 0 , 4 );
	PHP_CRC32_CTX md5;
	PHP_CRC32Init( &md5 , NULL );
	PHP_CRC32BUpdate( &md5 , Z_STRVAL( rv ) , Z_STRLEN( rv ) );
	PHP_CRC32LEFinal( bin , &md5 );
	zval_ptr_dtor( &rv );
	lua_pushinteger( L , *( (unsigned int*) ( bin ) ) );
	return 1;
}

int php_lua_adler32( lua_State *L ) {
	zval rv;
	int i = 0 , j = 0;
	int nargs = lua_gettop( L );

	if ( nargs < 1 ) {
		lua_pushinteger( L , 0 );
		return 1;
	}

	php_lua_get_zval_from_lua( L , 1 , NULL , &rv );
	if ( Z_TYPE(rv) != IS_STRING || Z_STRLEN(rv) < 1 ) {
		lua_pushinteger( L , 0 );
		return 1;
	}
	unsigned char bin[4];
	memset( bin , 0 , 4 );
	PHP_ADLER32_CTX md5;
	PHP_ADLER32Init( &md5 , NULL );
	PHP_ADLER32Update( &md5 , Z_STRVAL( rv ) , Z_STRLEN( rv ) );
	PHP_ADLER32Final( bin , &md5 );
	zval_ptr_dtor( &rv );
	lua_pushinteger( L , *( (unsigned int*) ( bin ) ) );
	return 1;
}

static const luaL_Reg php_lua_lib_hash[] =
	{
		{ "md5" , php_lua_md5 } ,
		{ "sha1" , php_lua_sha1 } ,
		{ "crc32b" , php_lua_crc32b } ,
		{ "adler32" , php_lua_adler32 } ,
		{ NULL , NULL } };

int luaopen_hash( lua_State *L ) {
	luaL_newlib( L , php_lua_lib_hash );
	return 1;
}

