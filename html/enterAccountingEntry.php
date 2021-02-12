<!DOCTYPE html>
<html>
<head>
	<title>free budget webapp</title>
	<meta charset="utf-8">
	<meta name="viewport" content="width=device-width, initial-scale=1.0">
	<link rel="stylesheet" href="https://maxcdn.bootstrapcdn.com/bootstrap/4.0.0/css/bootstrap.min.css" integrity="sha384-Gn5384xqQ1aoWXA+058RXPxPg6fy4IWvTNh0E263XmFcJlSAwiGgFAW/dAiS6JXm" crossorigin="anonymous">
	<style>
	.hdr-row-entry {
		border-bottom: solid black 1px;
	}
	.hdr-row-entry th {
		text-align: center;
	}
	#enterLineError {
		color:red;
	}
	</style>
	</head>
<body>
<?php
	require('common_functions.php');
	gen_nav_bar();
?>
<div class="container">
	<div class="row">	
	<div class="col-12">
		<table class="table" id="accountingEntry">
		<tr class="hdr-row-entry">
			<th>Account (Type)</th>
			<th>Debits</th>
			<th>Credits</th>
		</tr>
		<tr id="enterLineRow">
			<td>
			<!--Generate add account line-->
			<?php
			$conn = new mysqli("localhost", "free_budget_conn", "badpassword", "free_budget_db");
			if (mysqli_connect_error()) {
				die("Failed to connect to db: " . mysqli_connect_error());
			}
			$ddl_id = "accountNameDropdownEnter";
			$account_book_id = 1;
			$account_query = "SELECT a.account_name, b.account_type_description FROM accounting_accounts AS a LEFT JOIN accounting_account_type AS b ON a.rel_account_type_id = b.account_type_id WHERE a.rel_accounting_book_id = ".$account_book_id.";";
			try {
				$sel = $conn->query($account_query);
				echo "<select id=\"" . $ddl_id . "\" name=\"" . $ddl_id . "\">";
				while ($row = $sel->fetch_assoc()) {
					echo "<option value=\"" . $row["account_name"] . ",".$row["account_type_description"]."\">" . $row["account_name"] . " (" . $row["account_type_description"] .  ")</option>";
				}
				echo "</select>";
			} catch(Exception $e) {
				echo "Error in getting list of accounts for dropdown: " . $e->getMessage();
			}
			?>
			</td>
			<td>
			<!-- HTML5 number type -->
			<input type="number" name="debitTextBoxEnter" id="debitTextBoxEnter">
			</td>
			<td>
			<!-- HTML5 number type -->
			<input type="number" name="creditTextBoxEnter" id="creditTextBoxEnter">
			</td>
		</tr>
		<tr>
		<td>
		<div id="enterLineError"></div>
		</td>
		<td></td>
		<td>
		<button type="button" id="enterLineButton" class="btn">Enter Line</button>
		</td>
		</tr>	
		</table>	
	</div>
	</div>
	<div class="row">
		<label for="memoTextBox" >Memo:&nbsp;</label>
		<input type="text" name="memoTextBox" id="memoTextBox">
	</div>
	<br />
	<div class="row">
		<button type="button" id="commitEntryButton" class="btn">Commit Entry</button>	
	</div>
</div>

<script src="https://code.jquery.com/jquery-3.5.1.min.js" integrity="sha256-9/aliU8dGd2tb6OSsuzixeV4y/faTqgFtohetphbbj0="  crossorigin="anonymous"></script>
<script src="https://cdnjs.cloudflare.com/ajax/libs/popper.js/1.12.9/umd/popper.min.js" integrity="sha384-ApNbgh9B+Y1QKtv3Rn7W3mgPxhU9K/ScQsAP7hUibX39j7fakFPskvXusvfa0b4Q" crossorigin="anonymous"></script>
	<script src="https://maxcdn.bootstrapcdn.com/bootstrap/4.0.0/js/bootstrap.min.js" integrity="sha384-JZR6Spejh4U02d8jOt6vLEHfe/JQGiRRSQQxSfFWpi1MquVdAyjUar5+76PVCmYl" crossorigin="anonymous"></script>
<script>
$( document ).ready(function() {
	
	var lineInfo = []; //on this page only

	function countExistingLines() {
		//not the most efficient
		let s = 0; //will not exist, but will let the 0 case occur more easily
		var elementId = "entryLine" + s;
		var elem;
		while (( elem = document.getElementById(elementId) ) != null) {
			s++;
			elementId = "entryLine" + s;
		}
		return s+1;
	}

	function createLine(accName, accType, debit, credit) {
		//create a tr tag and enter the values 
		let currentCount = countExistingLines();
		let newId = "entryLine" + (currentCount + 1);
		let tr = document.createElement("tr");
		tr.id = newId;
		let accNameNode = document.createElement("td");
		accNameNode.innerHTML = accName + " (" + accType + ")";
		tr.appendChild(accNameNode);
		let debitNode = document.createElement("td");
		debitNode.innerHTML = debit;
		tr.appendChild(debitNode);
		let creditNode = document.createElement("td");
		creditNode.innerHTML = credit;
		tr.appendChild(creditNode);
				
		// insert the tr tag before the one with the input elements
		let insertRow = document.getElementById("enterLineRow");
		//document.body.insertBefore(tr, insertRow);
		let insertRowParent  = insertRow.parentNode;
		//console.log("Parent:");
		//console.log(entryTbl);
		//console.log("reference node:");
		//console.log(insertRow);
		//console.log("inserting: ");
		//console.log(tr);
		insertRowParent.insertBefore(tr, insertRow);
		lineInfo.push([newId, accName, accType, debit, credit]);
		console.log("Inserted row into accounting entry");
	}

	function removeRow(elemRow) {
		//delete tr
		var elemId = elemRow.id;
	 	var par = elemRow.parentNode;
		par.removeChild(elemRow);
		
		//delete from array
		var removing = null;
		var i = 0;
		while (i < lineInfo.length) {
			if (lineInfo[i][0] == elemId) {
				removing = lineInfo[i];
				break;
			}
			i++;
		}
		if (removing != null) {
			lineInfo.remove(removing);
		}	
	}

	$("#enterLineButton").on('click', function(evt) {
		//is the information valid?
		var accountInfo = document.getElementById("accountNameDropdownEnter").value;
		var accountName = accountInfo.split(",")[0];
		var accountType = accountInfo.split(",")[1];
		var debit = document.getElementById("debitTextBoxEnter").value;
		var credit = document.getElementById("creditTextBoxEnter").value;

		//simplify if by setting zeroes to ""
		if (debit == "0") debit = "";
		if (credit == "0") credit = "";

		console.log("Line info");
		console.log("Account: " + accountName);
		console.log("Account type: " + accountType);
		console.log("Debit: " + debit);
		console.log("Credit: " + credit);
		var errMsg = document.getElementById("enterLineError");
		if (debit != "" && credit != "") {
			errMsg.innerHTML = "An account line should only have a debit or a credit, not both";
		}
		else if (debit == "" && credit == "") {
			errMsg.innerHTML = "Must enter a debit or a credit";
		}
		else if ((debit != "" && credit == "") || (debit == "" && credit != "")) {
			errMsg.innerHTML = "";
			createLine(accountName, accountType, debit, credit);	
		}
		document.getElementById("debitTextBoxEnter").value = "";
		document.getElementById("creditTextBoxEnter").value = "";
		
	});


	$("#commitEntryButton").on('click', function(evt) { 
		//validate that the debits and credits line up
		let valid = false;

		/*
		let linesOnPage = [];
		let currentEntryId = "";
		let s = 1;
		var elem;
		currentEntryId = "entryLine" + s;
		while( (elem = document.getElementById(currentEntryId) ) != null) {
			linesOnPage.push(elem);
			s++;
			currentEntryId = "entryLine" + s;
		}
		 */

		console.log("Lines on page count: " + lineInfo.length);
		let totalDebits = 0;
		let totalCredits = 0;
		for (var i = 0; i < lineInfo.length; i++) {
			let nodeList = lineInfo[i];
			console.log(nodeList);
			let debitStr = nodeList[3];
			let creditStr = nodeList[4];
			let parsedDebit = parseInt(debitStr);
			let parsedCredit = parseInt(creditStr);
			if (!isNaN(parsedDebit)) {
				totalDebits += parsedDebit;
			}
			if (!isNaN(parsedCredit)) {
				totalCredits += parsedCredit;
			}
		}
		console.log("Total debits: " + totalDebits);
		console.log("Total credits: " + totalCredits);
		valid = totalDebits == totalCredits;

		var errMsg = document.getElementById("enterLineError");
		if (valid) {
			errMsg.innerHTML = "";
			// do an ajax call to 
			// a CGI program that will
			// enter the line into the database
			
			//format as expected in CGI program:
			//
			//<which-book-id>&<account-name>&<credit|debit>;<amount>&<next-with-same-pattern>&...
			let bookId = 1; //TODO: get book id from however its getting done

			let memoTxtBox = document.getElementById("memoTextBox");
			
			let postData = "" + bookId + "&" + encodeURIComponent(memoTxtBox.value) + "&" ;
			for (var i = 0; i < lineInfo.length; i++) {
				let nodeList = lineInfo[i];
				//console.log(nodeList);
				let debitStr = nodeList[3];
				let creditStr = nodeList[4];
				let accountName = encodeURIComponent(nodeList[1]);
				let parsedDebit = parseInt(debitStr);
				let parsedCredit = parseInt(creditStr);
				let lineInfoStr = "";
				if (!isNaN(parsedDebit)) {
					lineInfoStr = accountName + ";debit;" + parsedDebit;
				}
				if (!isNaN(parsedCredit)) {
					lineInfoStr = accountName + ";credit;" + parsedCredit;
				}
				postData += lineInfoStr;
				if (i < lineInfo.length - 1) {
					postData += "&";
				}
			}

			memoTxtBox.value = "";

			console.log("POST data for entry:");
			console.log(postData);

			$.ajax({
			method: "POST",
			url: "/cgi-bin/manualAccountingEntry.cgi",
			data: postData,
			success: function(responseData) {
				console.log("success");
				console.log(responseData);
			},
			error: function(responseData) {
				console.log("error");
				console.log(responseData);
			}
			});

			//let insertRow = document.getElementById("enterLineRow");
			// remove the lines from the table, reset the page state
			for(var i = 0; i < lineInfo.length; i++) {
				var lineNodeId = lineInfo[i][0];
				console.log(lineNodeId);
				let rw = document.getElementById(lineNodeId);
				console.log(rw);
				if (rw) {	
					rw.parentNode.removeChild(rw);
				}
			}
			lineInfo = [];

		} else {
			errMsg.innerHTML = "Total debits must be equal to total credits";
		}
	});
});

</script>
</body>
</html>
