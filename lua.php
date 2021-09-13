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
	"print 'Hello,World'"
);
var_dump($lua);
var_dump($lua->call('getPluginInfo'));
var_dump($lua->PLUGIN_NAME);
$lua->PLUGIN_NAME = 'hello';
var_dump($lua->PLUGIN_NAME);
