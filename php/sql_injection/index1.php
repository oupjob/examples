<?php

/*
 * by AlexanderPHP
 * http://habrahabr.ru/post/148151/
 */
require_once 'cfg.php'; 

// if (!isset($_GET['id']))
//    die('Введите ID');

$id = readline('id : ');
$query = "SELECT * FROM news WHERE id=$id";
$result = mysql_query("SETNAMES utf-8");
$result = mysql_query($query);
$row = mysql_fetch_array($result);
if(!$row)
    die('Статья не найдена');


echo "ID: ".$row['id']."<br/>";
echo "Автор: ".$row['user']."<br/>";
echo $row['text'];
