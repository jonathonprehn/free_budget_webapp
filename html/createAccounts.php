<!DOCTYPE html>
<html>
<head>
	<title>free budget webapp</title>
	<meta charset="utf-8">
	<meta name="viewport" content="width=device-width, initial-scale=1.0">
	<link rel="stylesheet" href="https://maxcdn.bootstrapcdn.com/bootstrap/4.0.0/css/bootstrap.min.css" integrity="sha384-Gn5384xqQ1aoWXA+058RXPxPg6fy4IWvTNh0E263XmFcJlSAwiGgFAW/dAiS6JXm" crossorigin="anonymous">
	</head>
<body>
<!--
<nav class="navbar navbar-expand-lg navbar-light bg-light">
  <a class="navbar-brand" href="#">Budget</a>
     <button class="navbar-toggler" type="button" data-toggle="collapse" data-target="#navbarSupportedContent" aria-controls="navbarSupportedContent" aria-expanded="false" aria-label="Toggle navigation"> 
        <span class="navbar-toggler-icon"></span>
     </button>
     <div class="collapse navbar-collapse" id="navbarSupportedContent">
         <ul class="navbar-nav mr-auto"> 
	  <li class="nav-item active">
           <a class="nav-link" href="#">Home <span class="sr-only">(current)</span></a>
          </li>
          <li class="nav-item">
           <a class="nav-link" href="uploadTransactions.html">Upload Transactions</a>
          </li> 
	 </ul>
     </div>
</nav>
-->
<div class="container">
	<div class="row">
		<div class="col-2">
			<a href="uploadTransactions.html">Upload</a>	
		</div>
		<div class="col-2">
			Create:<br />
			<ul>
			<li><a href="createAccount.html">Accounts</a><li>
			</ul>	
		</div>
		<div class="col-2">
			
		</div>
		<div class="col-2">

		</div>
		<div class="col-2">
			
		</div>
		<div class="col-2">

		</div>
	</div>
</div>
<div class="container">
	<div class="row">
		<div class="col-12">
		<!-- make account form -->
		
		<form id="createAccountForm"  method="POST" action="createAccount.cgi">
			<label for="accountName">Account Name</label>
			<input type="text" name="accountName">
			<label for="">Account Type</label>
			<!--todo: dropdown-->
			<label for="">Budget Category</label>
			<!--todo: dropdown-->
			<label for="accountDesc">Account Description</label>
			<textarea  name="accountDesc" rows="2" cols="50"></textarea>
			
			<br />
			<input type="submit" text="Submit">
		</form>
		</div>
	</div>
</div>
<div class="row" style="height:15px"></div>
<div class="container">
	<div class="row">
		<div class="col-12">
		<h5>Existing accounts</h5>
		<!-- list existing accounts -->
		<table class="table">
		<tr>
		<th>Account Name</th>
		<th>Account Type</th>
		<th>Budget Category</th>
		<th>Description</th>
		<th>Total Debits</th>
		<th>Total Credits</th>
		<th>Balance</th>
		</tr>	
		<?php
		$account_query = ""; //TODO

		?>
		</table>
		</div>
	</div>
</div>

<!--  other stuff down here -->
<script src="https://code.jquery.com/jquery-3.2.1.slim.min.js" integrity="sha384-KJ3o2DKtIkvYIK3UENzmM7KCkRr/rE9/Qpg6aAZGJwFDMVNA/GpGFF93hXpG5KkN" crossorigin="anonymous"></script>
	<script src="https://cdnjs.cloudflare.com/ajax/libs/popper.js/1.12.9/umd/popper.min.js" integrity="sha384-ApNbgh9B+Y1QKtv3Rn7W3mgPxhU9K/ScQsAP7hUibX39j7fakFPskvXusvfa0b4Q" crossorigin="anonymous"></script>
	<script src="https://maxcdn.bootstrapcdn.com/bootstrap/4.0.0/js/bootstrap.min.js" integrity="sha384-JZR6Spejh4U02d8jOt6vLEHfe/JQGiRRSQQxSfFWpi1MquVdAyjUar5+76PVCmYl" crossorigin="anonymous"></script>
<script>

	function bindEvents() {
		
	}

	bindEvents();

</script>
</body>
</html>
