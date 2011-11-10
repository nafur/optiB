<?php

$a = file($argv[1]);

$mode = 0;

$str = "graph {\n";

foreach ($a as $line)
{
	if ($mode == 1) ;//$str .= preg_replace("/(\\d+)/", "", $line);
	else if ($mode == 2) $str .= preg_replace("/(\\d+) (\\d+) (\\d+)/", "\\1 -- \\2 [label=\\3]", $line);

	if (trim($line) == "label") $mode = 1;
	else if (trim($line) == "weight") $mode = 2;
}

$str .= "\n}\n";

print($str);
?>
