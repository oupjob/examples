<?php 

require_once("PHPExcel/Classes/PHPExcel.php");

$no_empty_flag = false;
$empty_flag = false;

$excel = PHPExcel_IOFactory::load('vip_shoes.xlsx');
foreach($excel->getWorksheetIterator() as $worksheet) {
    $lists[] = $worksheet->toArray();
    foreach($lists as $list){
        echo "<table border=\"1\">\n";
        // Перебор строк
        foreach($list as $row){
            echo "\t<tr>\n";
            // Перебор столбцов
            foreach($row as $col){
                if ($col) {
                    $no_empty_flag = true;
                } else if ($no_empty_flag) {
                    $empty_flag = true;
                    break;
                }
                echo "\t\t<td>".$col."</td>\n";
            }
            echo "\t</tr>\n";
            if ($empty_flag) break;
        }
        echo "</table>\n";
        break;
    }
    break;
}

?>
