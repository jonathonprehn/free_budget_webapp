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
	Import transactions downloaded from bank data
	<br />
	<br />
	Use the template until dynamic field mapping works. Dates must be in a text format with the form MM/DD/YYYY.
	</div>
	<div class="row">
	<?php
	try {
		$sql_conn = new mysqli("localhost", "free_budget_conn", "badpassword", "free_budget_db");
		if (mysqli_connect_error()) {
			die("Failed to connect to db: " . mysqli_connect_error());
		}
		$q = "select (select max(upload_date) from uploaded_files limit 1) as most_recent_upload, (select max(transaction_date) from imported_data limit 1) as most_recent_transaction;";
		$sel = $sql_conn->query($q);
		while ($row = $sel->fetch_assoc()) {
			echo "The most recent upload was on ".$row["most_recent_upload"]."<br />";
			echo "The most recent transaction in this upload was on ".$row["most_recent_transaction"]."<br />";
		}

	} catch(Exception $except) {
		//couldn't get info
	}	
	?>
	</div>
	<br />
	<div class="row">
	<form id="importFileForm" action="/cgi-bin/processTrans.cgi" method="post" enctype="multipart/form-data">
		<input  type="file" name="uploading">
		<input class="btn btn-info" type="submit" value="Submit">
	</form>
	</div>
</div>


<!--  other stuff down here -->
<script src="https://code.jquery.com/jquery-3.5.1.min.js" integrity="sha256-9/aliU8dGd2tb6OSsuzixeV4y/faTqgFtohetphbbj0=" crossorigin="anonymous"></script>
	<script src="https://cdnjs.cloudflare.com/ajax/libs/popper.js/1.12.9/umd/popper.min.js" integrity="sha384-ApNbgh9B+Y1QKtv3Rn7W3mgPxhU9K/ScQsAP7hUibX39j7fakFPskvXusvfa0b4Q" crossorigin="anonymous"></script>
	<script src="https://maxcdn.bootstrapcdn.com/bootstrap/4.0.0/js/bootstrap.min.js" integrity="sha384-JZR6Spejh4U02d8jOt6vLEHfe/JQGiRRSQQxSfFWpi1MquVdAyjUar5+76PVCmYl" crossorigin="anonymous"></script>
<script></script>

<script>
$( document ).ready(function() {
	console.log('ready');	
});
</script>

</body>
</html>
