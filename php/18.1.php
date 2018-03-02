<?php
	$mysqli = mysqli_connect("localhost", "root", "123456");

	if(!$mysqli)
		echo "connect error: " . mysqli_connect_error()
	else
		echo "connect success" . "<br>";

	$sql = "create database testDB";

	if(mysqli_query($mysqli, $sql))
		echo "create success";
	else
		echo "error: " . mysqli_error();

	mysqli_close($mysqli);
?>
