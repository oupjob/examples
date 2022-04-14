<?php

class Point
{
    private $x;
    private $y;
    
    function __construct($x = 0, $y = 0) 
    {
        $this->x = $x;
        $this->y = $y;
    }
    
    function x() 
    { 
        return $this->x; 
    }
    
    function y() 
    { 
        return $this->y; 
    }
    
    function str() 
    { 
        return '(x: ' . $this->x . ', y: ' . $this->y . ')'; 
    }
    
    function fromFileString($handle)
    {
        
    }
    
    function toFileString($handle) 
    {
    
    }
}

// $fh = fopen("point.json", "w");
print(json_encode(new Point(1, 2)));
$d = json_decode('{ "a": [1, 1], "b": [2,2] }');

var_dump($d->a);

?>
