for i in TestSuite/*.pas; do
	echo "testing $i"
	java ParserMain <  $i
done