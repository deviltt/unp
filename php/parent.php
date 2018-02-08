<?php
	class Employee{
				
		private $name;

		function __construct($name){
			$this->name = $name;
			echo "employee's name :$this->name\n";
		}
	}

	class ceo extends Employee{
		
		private $Ceo;
		
		function __construct($Ceo){
			parent::__construct($Ceo);
			$this->Ceo = $Ceo;
			echo "$this->Ceo\n";
		}
	}

	$employee = new ceo("tt");
?>
