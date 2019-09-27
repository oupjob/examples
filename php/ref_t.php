<?php
$arr = array( 0 => 1, 1 => 3, 2 => 5);

class A {
    public $ref;
    
    function __construct(&$v) { 
    	$this->ref = $v;
	}
    
    function initRefA($v) {
        $this->ref = $v;
        $this->ref[2] = "ccc";
    }
    
    function initRefB(&$v) {
        $this->ref = $v;
        $this->ref[2] = "ddd";
    }
}

function f() {
	$v = array(0 => 5, 1 => 7);
	return $v;
}

$a = new A(f());
$a->ref[1] = "bbb";
var_dump($a->ref)

?>
