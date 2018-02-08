<?php
	class Employee{
				
		private $name;

		function __construct($name){
			$this->name = $name;
			echo "$this->name\n";
		}
	}

	$employee = new Employee("tt");
?>
