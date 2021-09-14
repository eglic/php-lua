#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "php_ini.h"
#include "ext/standard/info.h"
#include "ext/standard/md5.h"
#include "ext/standard/sha1.h"
#include "ext/standard/base64.h"
#include "ext/standard/crc32.h"
#include "Zend/zend_exceptions.h"
#include "php_lua.h"
#include "lua_closure.h"


/** {{{ static int php_lua_md5(lua_State *L)
 */
int php_lua_md5( lua_State *L ) {
	zval rv;
	int i = 0 , j = 0;
	int nargs = lua_gettop( L );

	for ( i = 1 ; i <= nargs ; ++i ) {
		php_lua_get_zval_from_lua( L , i , NULL , &rv );
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
	return 0;
}
/* }}} */

/** {{{ static int php_lua_sha1(lua_State *L)
 */
int php_lua_sha1( lua_State *L ) {
	zval rv;
	int i = 0 , j = 0;
	int nargs = lua_gettop( L );

	for ( i = 1 ; i <= nargs ; ++i ) {
		php_lua_get_zval_from_lua( L , i , NULL , &rv );
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
	return 0;
}
/* }}} */
