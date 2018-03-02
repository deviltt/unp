<?php
	$mysqli = mysqli_connect("localhost", "root", "123456", "testDB");
	
	if(!$mysqli)
		die("connect error: " . mysqli_connect_error());
	else 
		echo "connect success" . "<br>";

	$sql = "create table testTable(
			id int not null primary key auto_increment,
			testField varchar(75)
		)";

	if(mysqli_query($mysqli, $sql)){
		echo "create success";
	}
	else
		echo "error: " . mysqli_error($mysqli);

	mysqli_close($mysqli);
?>
