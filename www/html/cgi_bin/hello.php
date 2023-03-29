<?PHP

$query=mb_split("&", $_SERVER['QUERY_STRING']);
if(!empty($query)) foreach ($query as $qr){
    $vars=mb_split('=',$qr);
    $_GET[$vars[0]]=$vars[1];
}

$entityBody = stream_get_contents(STDIN);
echo "entityBody: " . $entityBody;
$body = mb_split("&", $entityBody);
if(!empty($body)) foreach ($body as $qr){
    $vars=mb_split('=',$qr);
    $_POST[$vars[0]]=$vars[1];
}

echo "Content-type: text/html\r\n";
echo "\r\n";
echo "<HTML>";
echo "<HEAD>";
echo "<TITLE>Test</TITLE>";
echo "</HEAD>";
echo "<BODY>";
if ($_SERVER['REQUEST_METHOD'] == 'GET')
    echo "<H1>hello ". $_GET["first_name"] . " " . $_GET["last_name"] . "</H1>";
else
    echo "<H1>hello ". $_POST["first_name"] . " " . $_POST["last_name"] . "</H1>";
echo "</BODY>";
echo "</HTML>";
?>