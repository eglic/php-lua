<?php
$br = (php_sapi_name() == "cli")? "":"<br>";

if(!extension_loaded('lua')) {
	dl('lua.' . PHP_SHLIB_SUFFIX);
}
$lua = new \Lua();
$lua->eval(
	"PLUGIN_NAME = 'test'\n" .
	"function getPluginInfo()\n" .
	"	return {name = 'test'}\n" .
	"end\n" .
	"function testVar()\n" .
	"	print('PLUGIN_NAME = ' , PLUGIN_NAME,'\\n')\n" .
	"end\n" .
	"print ('Hello',',','World','!','\\n')\n" .
	"print(md5('abcd') , '\\n')".
	"print(sha1('abcd') , '\\n')"
);
var_dump($lua->call('getPluginInfo'));
var_dump($lua->PLUGIN_NAME);
$lua->PLUGIN_NAME = 'hello';
var_dump($lua->PLUGIN_NAME);
$lua->call('testVar');
