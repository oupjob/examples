<?php

$arr = array("foo1" => "bar1", "foo3" => "bar3", "foo2" => "bar2");

$n = count($arr);
for($i = 0; $i < $n; ++$i) {
	print $arr[$i] . "\n"; // PHP Notice:  Undefined offset:
}

?>
