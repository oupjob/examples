<?php
class A {
    public $x_;
    private $y_;
    
    const E_OK = 0;
    
    function __construct($x = 2, $y = 1) {
        if ($x) {
            $x_ = $x;
            print "x = " . $x_ . "\n";
        }
        
        if ($y) {
            $y_ = $y;
            print "y = " . $y_ . "\n";
        }
        
        throw new Exception("Just Exception");
    }
}

class B extends A {
    function __construct($x = 2, $y = 1) {
        echo "E_OK = ", A::E_OK, "\n";
    }
}

try {
    $b = new B();
    $a = new A(1);
} catch (Exception $e) {
    echo $e->getMessage();
}



?>

