<?php
	class TEST{
		var $title;
		var $url;

		function set_title($temp){
			$this->title = $temp;
		}

		function print_title(){
			echo $this->title . "\n";
		}

		function set_url($temp){
			$this->url = $temp;
		}

		function print_url(){
			echo $this->url . "\n";
		}
	}

	$taobao = new TEST;

	$taobao->set_title("taobao");
	$taobao->print_title();
	$taobao->set_url("www.taobao.com");
	$taobao->print_url();
?>
