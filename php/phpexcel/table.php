<?php
require_once("PHPExcel/Classes/PHPExcel.php");

$excel = PHPExcel_IOFactory::load('vip_shoes.xlsx');

$rows = $excel->setActiveSheetIndex(0)->getHighestRow();
$cols = PHPExcel_Cell::columnIndexFromString($excel->setActiveSheetIndex(0)->getHighestColumn());

print "dim = ($rows, $cols)\n";

$excel->getActiveSheet()->getCellByColumnAndRow(1, 8)->getValue();

$table_begin = false;
$table_end = false;
$first_row = false;

$fd = fopen("delivery.html", 'w');

fwrite($fd, "<table>\n");
for ($i = 0; $i < $rows; ++$i) {
	$row_tag = ($first_row) ? "\t<th>\n" : "\t<tr>\n";
	fwrite($fd, $row_tag);
	print "\n";
	for ($j = 0; $j < $cols; ++$j) {
		$cell = $excel->getActiveSheet()->getCellByColumnAndRow($j, $i);
		$value = $cell->getValue();	
		print ("$i, $j -> $value\n");

		if ($value == "TABLE_BEGIN") {
			$table_begin = true;
			$first_row = true;
		} else if (!$table_begin) {
			continue;
		}
		if ($value == "TABLE_END" && $table_begin) {
			$table_end = true;
			break;
		}

		$style = $cell->getStyle();
		
		// var_dump($style);
		if ($j == 12) break;
	}
	$first_row = "false";
	$row_tag = ($first_row) ? "\t</th>\n" : "\t</tr>\n";
	fwrite($fd, "\t<tr>\n");
	if ($table_end) 
		break;
	if ($i == 20) break;
}

fwrite($fd, "</table>\n");
fclose($fd);

?>
