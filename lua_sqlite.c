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
