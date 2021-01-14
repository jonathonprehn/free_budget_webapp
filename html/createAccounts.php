<!DOCTYPE html>
<html>
<head>
	<title>free budget webapp</title>
	<meta charset="utf-8">
	<meta name="viewport" content="width=device-width, initial-scale=1.0">
	<link rel="stylesheet" href="https://maxcdn.bootstrapcdn.com/bootstrap/4.0.0/css/bootstrap.min.css" integrity="sha384-Gn5384xqQ1aoWXA+058RXPxPg6fy4IWvTNh0E263XmFcJlSAwiGgFAW/dAiS6JXm" crossorigin="anonymous">
	</head>
<body>
<?php
	require('common_functions.php');
	gen_nav_bar();
?>
<div class="container">
	<div class="row">
		<div class="col-12">
		<!-- make account form -->
		
		<form id="createAccountForm"  method="POST" action="/cgi-bin/createAccount.cgi">
			<label for="accountName">Account Name</label>
			<input type="text" name="accountName">
			<br />
			<label for="accountType">Account Type</label>
			<?php
			
			$account_type_query = "SELECT "
						."account_type_id "
						.",account_type_description "
						." FROM accounting_account_type;"; 
			$ddl_id = "accountType";
			$conn = new mysqli("localhost", "free_budget_conn", "badpassword", "free_budget_db");
			if (mysqli_connect_error()) {
				die("Failed to connect to db: " . mysqli_connect_error());
			}
			try {
				$sel = $conn->query($account_type_query);
				echo "<select id=\"" . $ddl_id . "\" name=\"" . $ddl_id . "\">";
				while ($row = $sel->fetch_assoc()) {
					echo "<option value=\"" . $row["account_type_id"] . "\">" . $row["account_type_description"] . "</option>";
				}
				echo "</select>";
			} catch(Exception $e) {
				echo "Error getting categories: " . $e->getMessage();
			}
			 
			?>
			<br />
			<label for="budgetCategory">Budget Category</label>
			<?php
			
			$budget_category_query = "SELECT "
						."category_id "
						.",category "
						." FROM budget_categories;"; 
			$ddl_id = "budgetCategory";
			try {
				$sel = $conn->query($budget_category_query);
				echo "<select id=\"" . $ddl_id . "\" name=\"" . $ddl_id . "\">";
				while ($row = $sel->fetch_assoc()) {
					echo "<option value=\"" . $row["category_id"] . "\">" . $row["category"] . "</option>";
				}
				echo "</select>";
			} catch(Exception $e) {
				echo "Error getting categories: " . $e->getMessage();
			}
			 
			?>
			<br />
			<label for="accountDesc">Account Description</label>
			<textarea  name="accountDesc" rows="2" cols="50"></textarea>
				
			<br />
			<button type="button" class="btn btn-info" id="createAccountButton">Create Account</button>
			
			<input type="hidden" name="accountingBook" value="1">
		</form>
		</div>
	</div>
</div>
<div class="row" style="height:15px"></div>
<div class="container" id="accountListShow">
	
</div>

<!--  other stuff down here -->
<script
                          src="https://code.jquery.com/jquery-3.5.1.min.js"
                          integrity="sha256-9/aliU8dGd2tb6OSsuzixeV4y/faTqgFtohetphbbj0="
                          crossorigin="anonymous"></script>
	<script src="https://cdnjs.cloudflare.com/ajax/libs/popper.js/1.12.9/umd/popper.min.js" integrity="sha384-ApNbgh9B+Y1QKtv3Rn7W3mgPxhU9K/ScQsAP7hUibX39j7fakFPskvXusvfa0b4Q" crossorigin="anonymous"></script>
	<script src="https://maxcdn.bootstrapcdn.com/bootstrap/4.0.0/js/bootstrap.min.js" integrity="sha384-JZR6Spejh4U02d8jOt6vLEHfe/JQGiRRSQQxSfFWpi1MquVdAyjUar5+76PVCmYl" crossorigin="anonymous"></script>
<script>
$( document ).ready(function() {
	function bindEvents() {
		$("#createAccountButton").on('click', function(evt) {
			var frm = $("#createAccountForm");
			var act = frm.attr('action');
			var formData = frm.serialize();
				
			$.ajax({
			method: "POST",
			url: act,
			data: formData,
			success:
			function(responseData) {
				console.log("success");
				console.log(responseData);
				$("#accountListShow").empty();
				$("#accountListShow").load("accountList.php");
			},
			error:
			function(responseData) {
				console.log("failed");
				console.log(responseData);
			}
			});
		});	
	}

	bindEvents();
	$("#accountListShow").empty();
	$("#accountListShow").load("accountList.php");
	//console.log("Loaded page into accountListShow");
	
});
</script>
</body>
</html>
