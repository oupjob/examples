<?php

/*
 * by AlexanderPHP
 * http://habrahabr.ru/post/148151/
 */
require_once 'cfg.php'; 

    function readline($prompt = null){
        if($prompt){
            echo $prompt;
        }
        $fp = fopen("php://stdin","r");
        $line = rtrim(fgets($fp, 1024));
        return $line;
    }

// if (!isset($_GET['user']))
//    die('Введите имя пользователя');

$user = readline("User: ");
$query = "SELECT * FROM news WHERE user='$user'";
$result = mysql_query("SETNAMES utf-8");
$result = mysql_query($query);
$row = mysql_fetch_array($result);

echo "ID: ".$row['id']."<br/>";
echo "Автор: ".$row['user'];
echo "\n", $row['text'], "\n";
