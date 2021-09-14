<?php
$br = (php_sapi_name() == "cli")? "":"<br>";

if(!extension_loaded('lua')) {
	dl('lua.' . PHP_SHLIB_SUFFIX);
}
$lua = new \Lua();
echo "php.md5 = " . md5('abcd') . "\n";
echo "php.sha1 = " . sha1('abcd') . "\n";
echo "php.crc32 = " . crc32('abcd') . "\n";
echo "php.crc32? = " . hexdec(hash('crc32','abcd')) . "\n";
echo "php.crc32b = " . hexdec(hash('crc32b','abcd')) . "\n";
echo "php.crc32c = " . hexdec(hash('crc32c','abcd')) . "\n";
echo "php.adler32 = " . hexdec(hash('adler32','abcd')) . "\n";
$lua->eval(
	"PLUGIN_NAME = 'test'\n" .
	"function getPluginInfo()\n" .
	"	return {name = 'test'}\n" .
	"end\n" .
	"function testVar()\n" .
	"	print('PLUGIN_NAME = ' , PLUGIN_NAME,'\\n')\n" .
	"end\n" .
	"print ('Hello',',','World','!','\\n')\n" .
	"print('hash.md5 = ' , hash.md5('abcd') , '\\n')\n".
	"print('hash.sha1 = ' , hash.sha1('abcd') , '\\n')\n" .
	"print('hash.crc32b = ' , hash.crc32b('abcd') , '\\n')\n".
	"print('hash.adler32 = ' , hash.adler32('abcd') , '\\n')\n" .
	""
);
var_dump($lua->call('getPluginInfo'));
var_dump($lua->PLUGIN_NAME);
$lua->PLUGIN_NAME = 'hello';
var_dump($lua->PLUGIN_NAME);
$lua->call('testVar');
