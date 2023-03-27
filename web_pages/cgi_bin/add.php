<?PHP
// var_dump($_SERVER);

$user = "mohammed";

echo $user;

echo "Content-type: text/html\r\n";
echo "\r\n";
echo "<HTML>";
echo "<HEAD>";
echo "<TITLE>Test</TITLE>";
echo "</HEAD>";
echo "<BODY>";
echo "<H1>hello". $_GET["first_name"] ."</H1>";
echo "</BODY>";
echo "</HTML>";
?>