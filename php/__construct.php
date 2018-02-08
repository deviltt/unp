<?php
	class Construct{
		
		private $title;
		private $isbin;
		private $author;

		function __construct($isbin){
			$this->title = get_title();
			$this->isbin = $isbin;
			echo "$this->isbin\n";
			$this->author = get_author();
		}
		
		function get_title(){
			$this->title = "heying";
			echo "title is $this->title\n";
		}

		function get_author(){
			$this->author = "tt";
			echo "author is $this->author\n";
		}
	}

	$book = new Construct("111");
?>
