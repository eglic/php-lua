#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "php_ini.h"
#include "ext/standard/info.h"
#include "Zend/zend_exceptions.h"
#include "php_lua.h"
#include "lua_closure.h"

/** {{{ static int php_lua_print(lua_State *L)
 */
int php_lua_print( lua_State *L ) {
	zval rv;
	int i = 0;
	int nargs = lua_gettop( L );

	for ( i = 1 ; i <= nargs ; ++i ) {
		php_lua_get_zval_from_lua( L , i , NULL , &rv );
		zend_print_zval_r( &rv , 1 );
		zval_ptr_dtor( &rv );
	}
	return 0;
}
/* }}} */
