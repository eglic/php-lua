# PHP Lua
[![Build Status](https://secure.travis-ci.org/laruence/php-lua.png)](https://travis-ci.org/laruence/php-lua)

This extension embeds the lua interpreter and offers an OO-API to lua variables and functions.

"Lua is a powerful, fast, light-weight, embeddable scripting language." 

### Changed by eglic

- remove supporting for lua 5.0.2
- migrate to php-8.1.0
- some test script to debug
- export function from php to lua
	- md5
	- sha1
	- ...
- TODO
  - file system operation
  - file rw operation
  - database operation
  - redis operation
  - curl functions
  - wrap of any php functions 