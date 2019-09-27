<?php
    var_dump(glob("tmp*/*_*"));
    var_dump(copy("tmp1/0_0", "tmp2/0_0"));
    var_dump(glob("tmp2/\d+_\d+"));
?>
