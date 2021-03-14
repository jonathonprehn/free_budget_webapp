<?php

function gen_nav_bar() {
	echo '<nav class="navbar navbar-expand-lg navbar-light bg-light">'
 . '<a class="navbar-brand" href="index.php">Free Budget</a>'
 . '<button class="navbar-toggler" type="button" data-toggle="collapse" data-target="#navbarNavDropdown" aria-controls="navbarNavDropdown" aria-expanded="false" aria-label="Toggle navigation">'
 .   '<span class="navbar-toggler-icon"></span>'
 .'</button>'
 .'<div class="collapse navbar-collapse" id="navbarNavDropdown">'
 .  '<ul class="navbar-nav">'
 .     '<li class="nav-item dropdown">'
 .       '<a class="nav-link dropdown-toggle" href="#" id="navbarDropdownMenuLink" data-toggle="dropdown" aria-haspopup="true" aria-expanded="false">'
 .         'Data entry'
 .       '</a>'
 .       '<div class="dropdown-menu" aria-labelledby="navbarDropdownMenuLink">'
 .         '<a class="dropdown-item" href="enterAccountingEntry.php">Manual entry</a>'
 .         '<a class="dropdown-item" href="uploadTransactions.php">Import transactions</a>'
 .         '<a class="dropdown-item" href="resolveCorrelations.php">Resolve correlations</a>' /*TODO: number of correlations to resolve*/
 .       '</div>'
 .     '</li>'
 .     '<li class="nav-item dropdown">'
 .       '<a class="nav-link dropdown-toggle" href="#" id="navbarDropdownMenuLink" data-toggle="dropdown" aria-haspopup="true" aria-expanded="false">'
 .         'Create'
 .       '</a>'
 .       '<div class="dropdown-menu" aria-labelledby="navbarDropdownMenuLink">'
 .         '<a class="dropdown-item" href="manageCategories.php">Create Categories</a>'
 .         '<a class="dropdown-item" href="createAccounts.php">Create Accounts</a>'
 .       '</div>'
 .     '</li>'
 .     '<li class="nav-item dropdown">'
 .       '<a class="nav-link dropdown-toggle" href="#" id="navbarDropdownMenuLink" data-toggle="dropdown" aria-haspopup="true" aria-expanded="false">'
 .         'Budget'
 .       '</a>'
 .       '<div class="dropdown-menu" aria-labelledby="navbarDropdownMenuLink">'
 .         '<a class="dropdown-item" href="#">Manage Budgets</a>'
 .         '<a class="dropdown-item" href="#">Budget breakdown</a>'
 .       '</div>'
 .     '</li>'
 .     '<li class="nav-item dropdown">'
 .       '<a class="nav-link dropdown-toggle" href="#" id="navbarDropdownMenuLink" data-toggle="dropdown" aria-haspopup="true" aria-expanded="false">'
 .         'Accounting'
 .       '</a>'
 .       '<div class="dropdown-menu" aria-labelledby="navbarDropdownMenuLink">'
 .         '<a class="dropdown-item" href="#">Manage Books</a>'
 .         '<a class="dropdown-item" href="#">Accounting Ledger</a>'
 .         '<a class="dropdown-item" href="#">Accounting Journal</a>'
 .       '</div>'
 .     '</li>'
 .   '</ul>'
 . '</div>'
 .'</nav>';
}


function make_account_type_dropdown($sql_conn, $element_id) {
	$account_type_query = "SELECT "
			."account_type_id "
			.",account_type_description "
			." FROM accounting_account_type;"; 	
	try {
		$sel = $sql_conn->query($account_type_query);
		echo "<select id=\"" . $element_id . "\" name=\"" . $element_id . "\">";
		while ($row = $sel->fetch_assoc()) {
			echo "<option value=\"" . $row["account_type_id"] . "\">" . $row["account_type_description"] . "</option>";
		}
		echo "</select>";
	} catch(Exception $e) {
		echo "Error creating account type dropdown: " . $e->getMessage();
	}
}

function make_line_type_dropdown($sql_conn, $element_id) {
	$line_type_query = "SELECT "
			." line_type_id "
			.",line_type_description "
			." FROM accounting_line_type;"; 	
	try {
		$sel = $sql_conn->query($line_type_query);
		echo "<select id=\"" . $element_id . "\" name=\"" . $element_id . "\">";
		while ($row = $sel->fetch_assoc()) {
			echo "<option value=\"" . $row["line_type_id"] . "\">" . $row["line_type_description"] . "</option>";
		}
		echo "</select>";
	} catch(Exception $e) {
		echo "Error creating account type dropdown: " . $e->getMessage();
	}
}

function make_account_dropdown($sql_conn, $element_id, $book_id) {
	$accounts_query = "SELECT "
			." account_id "
			.",account_name "
			." FROM accounting_accounts WHERE rel_accounting_book_id = ".$book_id.";"; 	
	try {
		$sel = $sql_conn->query($accounts_query);
		echo "<select id=\"" . $element_id . "\" name=\"" . $element_id . "\">";
		while ($row = $sel->fetch_assoc()) {
			echo "<option value=\"" . $row["account_id"] . "\">" . $row["account_name"] . "</option>";
		}
		echo "</select>";
	} catch(Exception $e) {
		echo "Error creating account type dropdown: " . $e->getMessage();
	}
}

//this has a different value in the manual accounting entry page!
function make_account_with_type_dropdown($sql_conn, $element_id, $book_id) {

	$accounts_query = "SELECT a.account_id, a.account_name, b.account_type_description FROM accounting_accounts AS a LEFT JOIN accounting_account_type AS b ON a.rel_account_type_id = b.account_type_id WHERE a.rel_accounting_book_id = ".$book_id.";";
	try {
		$sel = $sql_conn->query($accounts_query);
		echo "<select id=\"" . $element_id . "\" name=\"" . $element_id . "\">";
		while ($row = $sel->fetch_assoc()) {
			echo "<option value=\"" . $row["account_id"] . "\">" . $row["account_name"] . " (" . $row["account_type_description"] .  ")</option>";
		}
		echo "</select>";
	} catch(Exception $e) {
		echo "Error creating account type dropdown: " . $e->getMessage();
	}


}

?>
