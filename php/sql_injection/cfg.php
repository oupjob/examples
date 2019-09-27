<?php

/*
 * by AlexanderPHP
 * http://habrahabr.ru/post/148151/
 */

$dbhost = "localhost";
$dbusername = "admin";
$dbpass = "multiC";
$dbname = "sqlinj";

mysql_connect($dbhost, $dbusername, $dbpass);
mysql_select_db($dbname);
