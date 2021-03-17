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
		
	</div>
	</div>
</div>
<div id="unresolvedCorrelationsContainer" class="container">

</div>

<script src="https://code.jquery.com/jquery-3.5.1.min.js" integrity="sha256-9/aliU8dGd2tb6OSsuzixeV4y/faTqgFtohetphbbj0="  crossorigin="anonymous"></script>
<script src="https://cdnjs.cloudflare.com/ajax/libs/popper.js/1.12.9/umd/popper.min.js" integrity="sha384-ApNbgh9B+Y1QKtv3Rn7W3mgPxhU9K/ScQsAP7hUibX39j7fakFPskvXusvfa0b4Q" crossorigin="anonymous"></script>
	<script src="https://maxcdn.bootstrapcdn.com/bootstrap/4.0.0/js/bootstrap.min.js" integrity="sha384-JZR6Spejh4U02d8jOt6vLEHfe/JQGiRRSQQxSfFWpi1MquVdAyjUar5+76PVCmYl" crossorigin="anonymous"></script>
<script>
$( document ).ready(function() {
	
	$("#unresolvedCorrelationsContainer").empty();
	$("#unresolvedCorrelationsContainer").load("unresolvedCorrelationsList.php");
});

function doMap(prfx) {
	console.log("Doing mapping for " + prfx);
	var srcBankAccount = document.getElementById(prfx + "SrcBankAccount").innerHTML;
	var dstDescription = document.getElementById(prfx + "Description").innerHTML;
	var srcAccountId = document.getElementById(prfx + "SrcBankAccountLink").value;
	var srcLineTypeId = document.getElementById(prfx + "SrcBankLineType").value;
	var dstAccountId = document.getElementById(prfx + "DstAccountLink").value;
	var dstLineTypeId = document.getElementById(prfx + "DstLineType").value;
	var mapData = "srcBankAccountName=" + encodeURIComponent(srcBankAccount) + "&srcDesc=" + encodeURIComponent(dstDescription) + "&srcMappedAccount=" + encodeURIComponent(srcAccountId) + "&srcMappedLineType=" + encodeURIComponent(srcLineTypeId) + "&dstMappedAccount=" + encodeURIComponent(dstAccountId) + "&dstMappedLineType=" + encodeURIComponent(dstLineTypeId) + "";

	//doesn't make sense to map to the same account and line types
	//idea for future: allow for incoming transactions to be split
	if (dstAccountId != srcAccountId && srcLineTypeId != dstLineTypeId) {
		console.log("Sending POST data to cgi script:");
		console.log(mapData);
		//do it 
		$.ajax({
		method: "POST",
		url: "/cgi-bin/create_transaction_mapping.rb",
		data: mapData,
		success: function(respData) {
			console.log("success");	
			console.log(respData);
			//reload container with updated data
			$("#unresolvedCorrelationsContainer").empty();
			$("#unresolvedCorrelationsContainer").load("unresolvedCorrelationsList.php");

		},
		error: function(respData) {
			console.log("error");
			console.log(respData);
		}
		});
	}
}

</script>
</body>
</html>
