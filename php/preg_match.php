<?php

$str = "123_0.jpg";
$matches = array();

$re = "/(\d+)_/";

echo "re = $re, quoted_re = ", preg_quote("(\d+)\\_"), "\n";

preg_match($re, $str, $matches);
var_dump($matches);


?>
