<?php 

ini_set("include_path", getcwd()); 


$var1 = "Include Test";
$var2 = "Foo Bar";

// $str = "{ \"status\": 0, \"html\":". include("./template.php") ."}\n";

$str = require("./template.php"); 

// print $str;

?>
