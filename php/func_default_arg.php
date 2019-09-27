<?php
function f($n = 0, &$s1 = "", &$s2 = "", &$arr = NULL ) {
	if ($n) print("n = " . $n);
	if ($s1) print(" s1 = " . $s1);
	if ($s2) print(" s2 = " . $s2);
	if ($arr) print(" n = " . $arr);
	print "\n";
}

$S1 = "aaa";
$S2 = "bbb";
$A = array(0=>1);
f(1);
f(1, $S1);
f(1, $S1, $S2);
f($S1, $A);

?>