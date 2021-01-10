<!DOCTYPE html>
<html>
<head>
	<title>free budget webapp</title>
	<meta charset="utf-8">
	<meta name="viewport" content="width=device-width, initial-scale=1.0">
	<link rel="stylesheet" href="https://maxcdn.bootstrapcdn.com/bootstrap/4.0.0/css/bootstrap.min.css" integrity="sha384-Gn5384xqQ1aoWXA+058RXPxPg6fy4IWvTNh0E263XmFcJlSAwiGgFAW/dAiS6JXm" crossorigin="anonymous">
	</head>
<body>

<div class="container">
	<div class="row">
		<div class="col-12">
		<!-- make account form -->
		
		<form id="createCategoryForm"  method="POST" action="/cgi-bin/createCategory.cgi">
			<label for="categoryName">Category Name</label>
			<input id="categoryNameInput" type="text" name="categoryName">
			<br />
			<label for="categoryDesc">Category Description</label>
			<input id="categoryDescInput" type="text" name="categoryDesc">
			<br />
			<input class="btn btn-info" type="submit" value="Submit">
		</form>
		</div>
	</div>
</div>
<div class="row" style="height:15px"></div>
<div class="container" id="categoryListShow">

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
		$("#createCategoryForm").submit(function(evt) {
			evt.preventDefault();
			var form = $(this);
			var act = form.attr("action");
			var formData = form.serialize();
				
			//console.log("making POST to " + act);
			//console.log("Form data: " + formData);
			$.ajax({
			method: "POST",
			url: act,
			data: formData,
			success: 
			function(responseData) {
				console.log("successful");
				console.log(responseData);
				//reload page
				$("#categoryListShow").empty();
				$("#categoryListShow").load("categoryList.php");
			},
			function(responseData) {
				console.log("failed");
				console.log(responseData);
			}
			});
		});
	}
	
	bindEvents();
	$("#categoryListShow").empty();
	$("#categoryListShow").load("categoryList.php");
});

function deleteCategory(cat) {
	var act = "/cgi-bin/deleteCategory.cgi";
	//console.log("Deleting '" + cat + "'");	
	//console.log("making POST to " + act);
	$.ajax({
	method: "POST",
	url: act,
	data: cat,
	success: 
	function(responseData) {
		console.log("successful");
		console.log(responseData);
		//reload page
		$("#categoryListShow").empty();
		$("#categoryListShow").load("categoryList.php");
	},
	error:
	function(responseData) {
		console.log("failed");
		console.log(responseData);
	}
	});
}

</script>
</body>
</html>
