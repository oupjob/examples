<?php 

function f($n) {
	$a = ($n % 30) ? 1 : 0;
	$m = ((int)($n / 30)) + $a;
	return $m;
}

function g($begin) {
//	print(
}

print((string)f(60) . "\n");
print((string)f(35) . "\n");
print((string)f(11) . "\n");

?>
