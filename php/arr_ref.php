<?php 

$arr = array('aaa', 'bbb');

function & f($i) {
	return $arr[$i]; 
}

$a = f(0);
$a = '111';

var_dump($arr);

?>
