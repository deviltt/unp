<?php
	$conn = mysqli_connect("localhost", "root", "123456", "testDB");

	if(!$conn)
		die("error: " . mysqli_connect_error());
	else
		echo "connect success" . "<br>";

	$add_text = mysqli_real_escape_string($_POST['testfield'], $conn);

	$sql = "insert into testTable (testField) values ('".$add_text."')";

	if(mysqli_query($conn, $sql))
		echo "a record has been inserted";
	else
		echo "error: " . mysqli_error($conn);

	mysqli_close($conn);
?>
