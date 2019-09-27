<?php

function f() {
	static $n = 0;
	$n++;
	print "$n\n";
}

f();
f();
f();

?>
