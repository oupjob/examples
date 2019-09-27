<?php 

ini_set("include_path", getcwd());

$message = "Hello, World!";

ob_start();
include("message_template.php");
$message = ob_get_clean();

$headers  = 'MIME-Version: 1.0' . "\r\n";
$headers .= 'Content-type: text/html; charset=iso-8859-1' . "\r\n";

$to = 'oup.job@mail.ru';
$subject = 'Test mail from PHP';

$res = mail($to, $subject, $message, $headers);
print(($res) ? "Mail has been sent\n" : "Mail has not been sent\n" );
?>
