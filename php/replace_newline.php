<?php 

$s = "aaaa\n\n\nbbbbb\n\ncccc\n";

print preg_replace("/\n{2,}/", "\n > ", $s);

?>
